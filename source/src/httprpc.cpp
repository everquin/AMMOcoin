// Copyright (c) 2015-2017 The Bitcoin Core developers
// Copyright (c) 2017-2021 The AMMOcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "httprpc.h"

#include "chainparams.h"
#include "crypto/hmac_sha256.h"
#include "guiinterface.h"
#include "httpserver.h"
#include "key_io.h"
#include "rpc/protocol.h"
#include "rpc/server.h"
#include "random.h"
#include "sync.h"
#include "util/system.h"
#include "utilstrencodings.h"
#include "utiltime.h"

#include <map>

#include <boost/algorithm/string.hpp> // boost::trim

/** Simple one-shot callback timer to be used by the RPC mechanism to e.g.
 * re-lock the wellet.
 */
class HTTPRPCTimer : public RPCTimerBase
{
public:
    HTTPRPCTimer(struct event_base* eventBase, std::function<void(void)>& func, int64_t millis) :
        ev(eventBase, false, func)
    {
        struct timeval tv;
        tv.tv_sec = millis/1000;
        tv.tv_usec = (millis%1000)*1000;
        ev.trigger(&tv);
    }
private:
    HTTPEvent ev;
};

class HTTPRPCTimerInterface : public RPCTimerInterface
{
public:
    HTTPRPCTimerInterface(struct event_base* base) : base(base)
    {
    }
    const char* Name()
    {
        return "HTTP";
    }
    RPCTimerBase* NewTimer(std::function<void(void)>& func, int64_t millis)
    {
        return new HTTPRPCTimer(base, func, millis);
    }
private:
    struct event_base* base;
};


/* Pre-base64-encoded authentication token */
static std::string strRPCUserColonPass;
/* Stored RPC timer interface (for unregistration) */
static std::unique_ptr<HTTPRPCTimerInterface> httpRPCTimerInterface;

/* Per-peer auth-failure tracking. Defends against brute-forcing the
 * rpcuser/rpcpassword shared secret — the prior protection (a 250 ms
 * sleep per attempt) was insufficient with 4 worker threads. */
namespace {
struct AuthFailState {
    int64_t firstFailMicros = 0;
    int64_t lockoutUntilMicros = 0;
    int failCount = 0;
};
static std::map<std::string, AuthFailState> g_authFails;
static RecursiveMutex cs_authFails;

static const int     DEFAULT_RPC_AUTH_MAX_FAILS   = 5;
static const int64_t DEFAULT_RPC_AUTH_FAIL_WINDOW = 60;    // seconds
static const int64_t DEFAULT_RPC_AUTH_LOCKOUT     = 300;   // seconds

static bool IsAuthLockedOut(const std::string& peerIp)
{
    LOCK(cs_authFails);
    auto it = g_authFails.find(peerIp);
    if (it == g_authFails.end()) return false;
    int64_t now = GetTimeMicros();
    if (it->second.lockoutUntilMicros > 0) {
        if (now < it->second.lockoutUntilMicros) return true;
        g_authFails.erase(it);  // lockout expired
    }
    return false;
}

static void RecordAuthFailure(const std::string& peerIp)
{
    int maxFails = gArgs.GetArg("-rpcauthmaxfails", DEFAULT_RPC_AUTH_MAX_FAILS);
    // -rpcauthmaxfails=0 disables the lockout entirely. Useful when the
    // RPC port sits behind a trusted reverse proxy whose source IP would
    // otherwise cause all clients to share a single failure bucket.
    if (maxFails <= 0) return;

    LOCK(cs_authFails);
    int64_t now = GetTimeMicros();
    int64_t windowMicros = gArgs.GetArg("-rpcauthfailwindow", DEFAULT_RPC_AUTH_FAIL_WINDOW) * 1000000LL;
    int64_t lockoutMicros = gArgs.GetArg("-rpcauthlockout", DEFAULT_RPC_AUTH_LOCKOUT) * 1000000LL;

    AuthFailState& s = g_authFails[peerIp];
    if (s.failCount == 0 || (now - s.firstFailMicros) > windowMicros) {
        s.firstFailMicros = now;
        s.failCount = 1;
    } else {
        s.failCount++;
    }
    if (s.failCount >= maxFails && s.lockoutUntilMicros == 0) {
        s.lockoutUntilMicros = now + lockoutMicros;
        LogPrintf("ThreadRPCServer: locking out %s for %d seconds "
                  "after %d failed auth attempts\n",
                  peerIp, lockoutMicros / 1000000, s.failCount);
    }
}

static void RecordAuthSuccess(const std::string& peerIp)
{
    LOCK(cs_authFails);
    g_authFails.erase(peerIp);
}
}  // namespace

static void JSONErrorReply(HTTPRequest* req, const UniValue& objError, const UniValue& id)
{
    // Send error reply from json-rpc error object
    int nStatus = HTTP_INTERNAL_SERVER_ERROR;
    int code = find_value(objError, "code").get_int();

    if (code == RPC_INVALID_REQUEST)
        nStatus = HTTP_BAD_REQUEST;
    else if (code == RPC_METHOD_NOT_FOUND)
        nStatus = HTTP_NOT_FOUND;

    std::string strReply = JSONRPCReply(NullUniValue, objError, id);

    req->WriteHeader("Content-Type", "application/json");
    req->WriteReply(nStatus, strReply);
}

//This function checks username and password against -rpcauth
//entries from config file.
static bool multiUserAuthorized(std::string strUserPass)
{
    if (strUserPass.find(':') == std::string::npos) {
        return false;
    }
    std::string strUser = strUserPass.substr(0, strUserPass.find(':'));
    std::string strPass = strUserPass.substr(strUserPass.find(':') + 1);

    for (const std::string& strRPCAuth : gArgs.GetArgs("-rpcauth")) {
        //Search for multi-user login/pass "rpcauth" from config
        std::vector<std::string> vFields;
        boost::split(vFields, strRPCAuth, boost::is_any_of(":$"));
        if (vFields.size() != 3) {
            //Incorrect formatting in config file
            continue;
        }

        std::string strName = vFields[0];
        if (!TimingResistantEqual(strName, strUser)) {
            continue;
        }

        std::string strSalt = vFields[1];
        std::string strHash = vFields[2];

        static const unsigned int KEY_SIZE = 32;
        unsigned char out[KEY_SIZE];

        CHMAC_SHA256(reinterpret_cast<const unsigned char*>(strSalt.c_str()), strSalt.size()).Write(reinterpret_cast<const unsigned char*>(strPass.c_str()), strPass.size()).Finalize(out);
        std::vector<unsigned char> hexvec(out, out+KEY_SIZE);
        std::string strHashFromPass = HexStr(hexvec);

        if (TimingResistantEqual(strHashFromPass, strHash)) {
            return true;
        }
    }
    return false;
}

static bool RPCAuthorized(const std::string& strAuth, std::string& strAuthUsernameOut)
{
    if (strRPCUserColonPass.empty()) // Belt-and-suspenders measure if InitRPCAuthentication was not called
        return false;
    if (strAuth.substr(0, 6) != "Basic ")
        return false;
    std::string strUserPass64 = strAuth.substr(6);
    boost::trim(strUserPass64);
    std::string strUserPass = DecodeBase64(strUserPass64);

    if (strUserPass.find(':') != std::string::npos)
        strAuthUsernameOut = strUserPass.substr(0, strUserPass.find(':'));

    //Check if authorized under single-user field
    if (TimingResistantEqual(strUserPass, strRPCUserColonPass)) {
        return true;
    }
    return multiUserAuthorized(strUserPass);
}

static bool HTTPReq_JSONRPC(HTTPRequest* req, const std::string &)
{
    // JSONRPC handles only POST
    if (req->GetRequestMethod() != HTTPRequest::POST) {
        req->WriteReply(HTTP_BAD_METHOD, "JSONRPC server handles only POST requests");
        return false;
    }
    // Resolve peer IP up-front for the lockout tracker. Use just the IP
    // (not IP:port), since attackers cycle source ports trivially.
    const std::string peerIp = req->GetPeer().ToStringIP();

    // Hard-reject already-locked-out peers before even parsing the header,
    // so the lockout actually limits work performed per request.
    if (IsAuthLockedOut(peerIp)) {
        req->WriteReply(HTTP_UNAUTHORIZED);
        return false;
    }

    // Check authorization
    std::pair<bool, std::string> authHeader = req->GetHeader("authorization");
    if (!authHeader.first) {
        req->WriteReply(HTTP_UNAUTHORIZED);
        return false;
    }

    JSONRPCRequest jreq;
    if (!RPCAuthorized(authHeader.second, jreq.authUser)) {
        LogPrintf("ThreadRPCServer incorrect password attempt from %s\n", req->GetPeer().ToString());

        RecordAuthFailure(peerIp);

        /* Deter brute-forcing. The per-IP lockout above is the real
         * defense; this sleep slows the first few attempts before the
         * lockout kicks in. */
        MilliSleep(250);

        req->WriteReply(HTTP_UNAUTHORIZED);
        return false;
    }

    // Clear any stale failure record on successful auth.
    RecordAuthSuccess(peerIp);

    try {
        // Parse request
        UniValue valRequest;
        if (!valRequest.read(req->ReadBody()))
            throw JSONRPCError(RPC_PARSE_ERROR, "Parse error");

        // Set the URI
        jreq.URI = req->GetURI();

        std::string strReply;
        // singleton request
        if (valRequest.isObject()) {
            jreq.parse(valRequest);

            UniValue result = tableRPC.execute(jreq);

            // Send reply
            strReply = JSONRPCReply(result, NullUniValue, jreq.id);

        // array of requests
        } else if (valRequest.isArray())
            strReply = JSONRPCExecBatch(valRequest.get_array());
        else
            throw JSONRPCError(RPC_PARSE_ERROR, "Top-level object parse error");

        req->WriteHeader("Content-Type", "application/json");
        req->WriteReply(HTTP_OK, strReply);
    } catch (const UniValue& objError) {
        JSONErrorReply(req, objError, jreq.id);
        return false;
    } catch (const std::exception& e) {
        JSONErrorReply(req, JSONRPCError(RPC_PARSE_ERROR, e.what()), jreq.id);
        return false;
    }
    return true;
}

static bool InitRPCAuthentication()
{
    if (gArgs.GetArg("-rpcpassword", "") == "")
    {
        LogPrintf("No rpcpassword set - using random cookie authentication\n");
        if (!GenerateAuthCookie(&strRPCUserColonPass)) {
            uiInterface.ThreadSafeMessageBox(
                _("Error: A fatal internal error occurred, see debug.log for details"), // Same message as AbortNode
                "", CClientUIInterface::MSG_ERROR);
            return false;
        }
    } else {
        LogPrintf("Config options rpcuser and rpcpassword will soon be deprecated. Locally-run instances may remove rpcuser to use cookie-based auth, or may be replaced with rpcauth. Please see share/rpcuser for rpcauth auth generation.\n");
        strRPCUserColonPass = gArgs.GetArg("-rpcuser", "") + ":" + gArgs.GetArg("-rpcpassword", "");
    }
    return true;
}

bool StartHTTPRPC()
{
    LogPrint(BCLog::RPC, "Starting HTTP RPC server\n");
    if (!InitRPCAuthentication())
        return false;

    RegisterHTTPHandler("/", true, HTTPReq_JSONRPC);
#ifdef ENABLE_WALLET
    // ifdef can be removed once we switch to better endpoint support and API versioning
    RegisterHTTPHandler("/wallet/", false, HTTPReq_JSONRPC);
#endif
    assert(EventBase());
    httpRPCTimerInterface = std::make_unique<HTTPRPCTimerInterface>(EventBase());
    RPCSetTimerInterface(httpRPCTimerInterface.get());
    return true;
}

void InterruptHTTPRPC()
{
    LogPrint(BCLog::RPC, "Interrupting HTTP RPC server\n");
}

void StopHTTPRPC()
{
    LogPrint(BCLog::RPC, "Stopping HTTP RPC server\n");
    UnregisterHTTPHandler("/", true);
    if (httpRPCTimerInterface) {
        RPCUnsetTimerInterface(httpRPCTimerInterface.get());
        httpRPCTimerInterface.reset();
    }
}

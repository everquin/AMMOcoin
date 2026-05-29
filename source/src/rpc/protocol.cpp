// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2021 The AMMOcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "rpc/protocol.h"

#include "random.h"
#include "tinyformat.h"
#include "util/system.h"
#include "utilstrencodings.h"
#include "utiltime.h"

#include <cerrno>
#include <cstring>
#ifndef WIN32
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

/**
 * JSON-RPC protocol.  AMMOcoin speaks version 1.0 for maximum compatibility,
 * but uses JSON-RPC 1.1/2.0 standards for parts of the 1.0 standard that were
 * unspecified (HTTP errors and contents of 'error').
 *
 * 1.0 spec: http://json-rpc.org/wiki/specification
 * 1.2 spec: http://jsonrpc.org/historical/json-rpc-over-http.html
 * http://www.codeproject.com/KB/recipes/JSON_Spirit.aspx
 */

UniValue JSONRPCRequestObj(const std::string& strMethod, const UniValue& params, const UniValue& id)
{
    UniValue request(UniValue::VOBJ);
    request.pushKV("method", strMethod);
    request.pushKV("params", params);
    request.pushKV("id", id);
    return request;
}

UniValue JSONRPCReplyObj(const UniValue& result, const UniValue& error, const UniValue& id)
{
    UniValue reply(UniValue::VOBJ);
    if (!error.isNull())
        reply.pushKV("result", NullUniValue);
    else
        reply.pushKV("result", result);
    reply.pushKV("error", error);
    reply.pushKV("id", id);
    return reply;
}

std::string JSONRPCReply(const UniValue& result, const UniValue& error, const UniValue& id)
{
    UniValue reply = JSONRPCReplyObj(result, error, id);
    return reply.write() + "\n";
}

UniValue JSONRPCError(int code, const std::string& message)
{
    UniValue error(UniValue::VOBJ);
    error.pushKV("code", code);
    error.pushKV("message", message);
    return error;
}

/** Username used when cookie authentication is in use (arbitrary, only for
 * recognizability in debugging/logging purposes)
 */
static const std::string COOKIEAUTH_USER = "__cookie__";
/** Default name for auth cookie file */
static const std::string COOKIEAUTH_FILE = ".cookie";

fs::path GetAuthCookieFile()
{
    fs::path path(gArgs.GetArg("-rpccookiefile", COOKIEAUTH_FILE));
    return AbsPathForConfigVal(path);
}

bool GenerateAuthCookie(std::string *cookie_out)
{
    const size_t COOKIE_SIZE = 32;
    unsigned char rand_pwd[COOKIE_SIZE];
    GetRandBytes(rand_pwd, COOKIE_SIZE);
    std::string cookie = COOKIEAUTH_USER + ":" + HexStr(rand_pwd);
    fs::path filepath = GetAuthCookieFile();

#ifndef WIN32
    // POSIX: do not rely on the process umask alone — -sysperms skips it.
    // Unlink any stale cookie (e.g. from a crashed prior run), then create
    // the file with O_EXCL + 0600 and fchmod() for belt-and-suspenders.
    fs::remove(filepath);
    int fd = ::open(filepath.string().c_str(),
                    O_CREAT | O_EXCL | O_WRONLY | O_CLOEXEC,
                    S_IRUSR | S_IWUSR);
    if (fd < 0) {
        LogPrintf("Unable to open cookie authentication file %s for writing: %s\n",
                  filepath.string(), std::strerror(errno));
        return false;
    }
    if (::fchmod(fd, S_IRUSR | S_IWUSR) != 0) {
        LogPrintf("Unable to fchmod cookie authentication file %s: %s\n",
                  filepath.string(), std::strerror(errno));
        ::close(fd);
        ::unlink(filepath.string().c_str());
        return false;
    }
    ssize_t written = ::write(fd, cookie.data(), cookie.size());
    int closeRc = ::close(fd);
    if (written != (ssize_t)cookie.size() || closeRc != 0) {
        LogPrintf("Failed to write cookie authentication file %s\n", filepath.string());
        ::unlink(filepath.string().c_str());
        return false;
    }
#else
    // Windows: rely on user-profile ACLs (the cookie sits under %APPDATA%).
    // The process umask path above is POSIX-only.
    fsbridge::ofstream file;
    file.open(filepath);
    if (!file.is_open()) {
        LogPrintf("Unable to open cookie authentication file %s for writing\n", filepath.string());
        return false;
    }
    file << cookie;
    file.close();
#endif

    LogPrintf("Generated RPC authentication cookie %s\n", filepath.string());

    if (cookie_out)
        *cookie_out = cookie;
    return true;
}

bool GetAuthCookie(std::string *cookie_out)
{
    fsbridge::ifstream file;
    std::string cookie;
    fs::path filepath = GetAuthCookieFile();
    file.open(filepath);
    if (!file.is_open())
        return false;
    std::getline(file, cookie);
    file.close();

    if (cookie_out)
        *cookie_out = cookie;
    return true;
}

void DeleteAuthCookie()
{
    try {
        fs::remove(GetAuthCookieFile());
    } catch (const fs::filesystem_error& e) {
        LogPrintf("%s: Unable to remove random auth cookie file: %s\n", __func__, fsbridge::get_filesystem_error_message(e));
    }
}

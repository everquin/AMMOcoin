# ❓ AMMOcoin Frequently Asked Questions

Quick answers to the most commonly asked questions about AMMOcoin. Find instant solutions and clarifications here.

## 🚀 Getting Started

### What is AMMOcoin?
**AMMOcoin** is a decentralized cryptocurrency built on Proof of Stake consensus, featuring staking, masternodes and governance voting. It offers fast 3-minute block times and focuses on community-driven development. AMMOcoin is Proudly Worthless™: it is worth nothing in money, permanently. The project sells nothing, publishes no price and promises no return.

### Do I need to upgrade to v1.1.1?
**Yes - everyone must upgrade.** v1.1.1 is a hard fork: Proof-of-Stake from block 2,776, no mining after. It uses new network magic bytes, so v1.1.1 nodes do not connect to v1.0 or v1.1.0 nodes. It also uses a new data folder (`~/.ammocoin11`, `~/Library/Application Support/AMMOcoin11`, `%APPDATA%\AMMOcoin11`) - copy your `wallet.dat` across. See the [v1.1.1 Release Notes](release-notes/RELEASE_NOTES_v1.1.1.md).

### How do I get started with AMMOcoin?
1. **Download** the wallet from official sources
2. **Install** and sync with the network
3. **Encrypt** your wallet with a strong password
4. **Backup** your wallet.dat file securely
5. **Start staking** or consider running a masternode

### Can I get AMMO?
**The AMMOcoin project sells nothing.** It has never held an ICO or token sale, does not list AMMO on any exchange and runs no exchange. AMMO reaches people through taking part, never through a sale by the project:
- **v1.0 holders**: balances from the v1.0 snapshot are airdropped to the same addresses (send nothing)
- **Staking**: the wallet that makes a block receives the staker share set by the code (there is no mining after the v1.1.1 fork)
- **Masternodes**: enabled masternodes take their turn in the payment queue
- **Contributions**: development and community work can receive awards from the contributor reserve or approved treasury proposals
- **GLiBz**: NUGGETS from activity on GLiBz can be swapped for AMMO under the GLiBz swap rules; paid-for NUGGETS can never reach AMMO

Any exchange listing can only happen through an explicit masternode governance vote (DAO Command). The project publishes no price for AMMO.

### Is AMMOcoin safe to use?
Yes, when following security best practices:
- ✅ **Encrypt your wallet**
- ✅ **Backup regularly**
- ✅ **Keep software updated**
- ✅ **Use official sources only**
- ✅ **Never share private keys**

## 💰 Wallet Questions

### How do I backup my wallet?
```bash
# Method 1: Backup wallet.dat
ammocoin-cli backupwallet "backup_YYYYMMDD.dat"

# Method 2: Export private keys
ammocoin-cli dumpwallet "keys_backup.txt"

# Store backups in multiple secure locations
```

### I forgot my wallet password. Can it be recovered?
**❌ No.** Wallet passwords cannot be recovered by anyone, including the development team. This is by design for security. Your only option is to restore from a backup made before encryption.

### How do I restore my wallet?
```bash
# Stop wallet
ammocoin-cli stop

# Replace wallet file
cp your_backup.dat ~/.ammocoin11/wallet.dat

# Restart and rescan
ammocoind -rescan
```

### Why is my balance showing as 0?
Common causes:
- **Wallet not synced** - Wait for full blockchain download
- **Wrong network** - Ensure you're on mainnet, not testnet
- **Corrupted wallet** - Restore from backup
- **Need rescan** - Run `ammocoind -rescan`

### How long does wallet sync take?
- **Initial sync**: 1-4 hours (depending on internet/hardware)
- **SSD vs HDD**: SSD is 3-5x faster
- **Daily sync**: 1-5 minutes if wallet was offline <24 hours

## 🎯 Staking Questions

### What is staking?
**Staking** is keeping AMMO coins in an online, unlocked-for-staking wallet so it helps secure the network. Your mature coins have a chance to make new blocks, which is how you and your crew run the network.

### What does a staked block pay?
- **Code terms only**: each block pays the masternode selected by the payment queue its share (`nMNBlockReward`) and the staker the rest of the issuance set by `GetBlockValue()`. The docs state no amounts and nothing is promised.
- **How often you stake**: ~480 blocks/day network-wide; your expected share of blocks = your weight / network weight
- **Factors**: Your coin amount, network weight, uptime
- **Frequency**: Small amounts may stake weekly/monthly
- **Maturity**: Staked coins are ordinary coins and add to your staking weight once they have 600 confirmations

### What's the minimum amount needed for staking?
- **Technical minimum**: there is no minimum balance in the code; coins need 600 confirmations
- **In practice**: the fewer coins you stake, the less often your wallet makes a block

### Why isn't my wallet staking?
Check these common issues:
```bash
# Verify staking is enabled
ammocoin-cli getstakingstatus

# Common problems:
# - Wallet locked (unlock for staking)
# - Coins too new (need 600 confirmations, ~30 hours)
# - Network disconnected (check peers)
# - Insufficient mature coins
```

### How do I unlock my wallet for staking?
```bash
# Unlock for staking only (secure)
ammocoin-cli walletpassphrase "your_password" 0 true

# The 'true' parameter means "staking only"
# 0 = stay unlocked until the wallet is locked or restarted
```

### My coins aren't staking after days/weeks. Why?
- **Small amounts** may take weeks or months to stake
- **Network weight** affects frequency - more network stakes = longer waits
- **Maturity** resets when you stake or move coins - each UTXO needs 600 confirmations again
- **Consider** combining small UTXOs

## 🏛️ Masternode Questions

### What is a masternode?
A **masternode** is a special type of node that provides enhanced services to the network (governance voting, budget finalization) and takes its turn in the masternode payment queue while it keeps 10,000 AMMO collateral in its owner's wallet.

### What do I need to run a masternode?
- **Collateral**: Exactly 10,000 AMMO, kept in your own wallet
- **Hosting**: a small VPS with a public IP, paid by you to your hosting provider
- **Setup Time**: 2-4 hours initial setup
- **Technical Knowledge**: Basic Linux command line skills

### How does the masternode payment queue work?
- **Share**: the masternode share of a block is set by the code (`nMNBlockReward`, `GetMasternodePayment()`); it changes at block 3,715,200 (`nNewMNBlockReward`)
- **Turns**: with N enabled masternodes, each one takes its turn about once every N blocks
- **Nothing promised**: frequency depends on how many masternodes are enabled and on your uptime
- **Requirements**: public, routable IP on port 37020 (127.0.0.1 or private IPs give "Invalid IP address")

### Can I stake without keeping my wallet online? (cold staking)
**Yes.** On an always-on staking node run `ammocoin-cli getnewstakingaddress`, then from your owner wallet run `ammocoin-cli delegatestake "S_STAKING_ADDRESS" AMOUNT` (add an owner address and `true` for `ext_owner` if the owner address is offline). The staking node can stake but cannot spend. Check with `getcoldstakingbalance` and `listcoldutxos` on the staking node, `getdelegatedbalance` in the owner wallet, and `getstakingstatus`.

### Can I run multiple masternodes?
**Yes!** Each requires:
- Separate 10,000 AMMO collateral
- Separate VPS/server
- Unique configuration
- Individual monitoring

### What happens if my masternode goes offline?
- **Short downtime** (<1 hour): Usually no penalty
- **Extended downtime**: Status changes to EXPIRED
- **Turn missed**: A node that is not enabled skips its turn in the queue
- **Restart**: Can restart anytime, returns to queue

### Can I spend my masternode collateral?
**Yes**, but it will immediately disable your masternode. The 10,000 AMMO must remain untouched in your wallet for the masternode to stay active.

## 🌐 Network Questions

### What are AMMOcoin's key specifications?
| Specification | Value |
|---------------|-------|
| **Block Time** | 3 minutes |
| **Total Supply** | 9,999,999,999 AMMO |
| **Consensus** | Proof of Stake |
| **Masternode Collateral** | 10,000 AMMO |
| **Network Port** | 37020 |
| **RPC Port** | 51473 |
| **Protocol Version** | 70927 |
| **Stake Maturity** | 600 confirmations |
| **Issuance** | Declining schedule in `GetBlockValue()`, unchanged by the fork |
| **Seed Nodes** | seed1.ammocoin.org (78.141.194.140), seed2.ammocoin.org (104.238.165.56) |

### How do I check if I'm on the correct network?
```bash
# Check network info
ammocoin-cli getnetworkinfo

# Verify chain
ammocoin-cli getblockchaininfo | grep chain
# Should show "main" not "test" or "regtest"

# Check protocol version
# Should be 70927 or higher

# Check you are past the PoS fork (v1.1.1 only)
ammocoin-cli getblockcount
# Stuck at 2775 = old software, upgrade to v1.1.1
```

### What's the difference between mainnet and testnet?
- **Mainnet**: Real network with real AMMO coins
- **Testnet**: Test network for development, coins have no value
- **Configuration**: Add `testnet=1` to use testnet
- **Data**: Stored in separate directories

### How many peers should I have?
- **Minimum**: 3-8 peers for basic operation
- **Good**: 10-20 peers for stable operation
- **Optimal**: 20-50 peers for best performance
- **Too many**: 100+ may slow performance

## 🗳️ Governance Questions

### What is AMMOcoin governance?
The **governance system** allows masternode operators to vote on proposals for network development, budget allocation, and protocol changes.

### Who can vote?
Only **masternode operators** can vote. Each masternode gets exactly one vote, regardless of additional holdings.

### How do I create a proposal?
1. **Discuss** with community first
2. **Create** detailed proposal document
3. **Pay** proposal fee (50 AMMO)
4. **Submit** via wallet or command line
5. **Promote** to masternode operators

### What types of proposals are accepted?
- **Development**: New features, bug fixes
- **Marketing**: Promotion campaigns
- **Integration**: Partnerships; any exchange listing is only possible through such a vote (the project itself runs no exchange and seeks no listing)
- **Community**: Events, education
- **Operations**: Infrastructure, legal

### How long does voting take?
- **Submission**: Proposal must be at least 24 hours old to enter a budget
- **Discussion**: 7 days recommended
- **Voting Period**: Until the target superblock (every 43,200 blocks, ~90 days)
- **Implementation**: Varies by proposal

## 🔧 Technical Questions

### Which operating systems are supported?
- **Windows**: Windows 10, 11 (64-bit)
- **macOS**: 10.14+ (Mojave and newer)
- **Linux**: glibc 2.34+ required - Ubuntu 22.04+ (24.04 tested), Debian 12+. Ubuntu 18.04/20.04 cannot run v1.1.1 binaries
- **ARM**: Raspberry Pi 4 with 4GB+ RAM

### How much disk space do I need?
- **Current blockchain**: small (the v1.1 chain restarted from a new genesis in 2026)
- **Recommended**: 20GB+ free space to allow for growth and logs
- **Sapling parameters**: ~50MB in `~/.ammocoin-params`
- **Pruning**: Not supported

### Can I run AMMOcoin on a Raspberry Pi?
**Yes!** Requirements:
- **Model**: Raspberry Pi 4 with 4GB+ RAM
- **Storage**: Fast SD card (Class 10) or USB 3.0 SSD
- **Network**: Stable internet connection
- **OS**: Raspberry Pi OS or Ubuntu

### What ports does AMMOcoin use?
- **P2P Network**: 37020 (must be open for incoming connections)
- **RPC**: 51473 (localhost only by default)
- **Testnet**: 37022 (P2P), 51475 (RPC)

### How do I enable remote RPC access?
```bash
# Add to ammocoin.conf (SECURITY RISK - use carefully)
rpcallowip=192.168.1.0/24  # Allow local network
rpcbind=0.0.0.0           # Listen on all interfaces

# Better: Use SSH tunnel instead
ssh -L 51473:localhost:51473 user@remote_server
```

## 🔐 Security Questions

### How do I keep my AMMO safe?
1. **Encrypt wallet** with strong password
2. **Backup regularly** to multiple locations
3. **Use official software** only
4. **Never share** private keys or passwords
5. **Keep software updated**
6. **Use hardware wallets** for large amounts

### Is it safe to leave my wallet online for staking?
**Generally yes**, but take precautions:
- ✅ **Use "staking only" unlock** (not full unlock)
- ✅ **Keep firewall active**
- ✅ **Use updated antivirus**
- ✅ **Regular backups**
- ✅ **Monitor for suspicious activity**

### What if I suspect my wallet is compromised?
**Immediate actions**:
1. **Disconnect** from internet
2. **Stop** wallet software
3. **Scan** for malware
4. **Move funds** to new wallet (if still accessible)
5. **Report incident** to security team

### Should I use a VPN with AMMOcoin?
**Not required** for security, but may help with:
- **Privacy**: Hide your IP from peers
- **Access**: Bypass regional restrictions
- **Censorship**: Access blocked networks
- **Note**: May slow sync speed

## 💸 Transaction Questions

### How long do transactions take?
- **Send time**: Instant
- **First confirmation**: ~3 minutes (1 block)
- **Recommended**: 6 confirmations (~18 minutes)
- **InstantSend**: Near-instant (masternode feature)

### What are transaction fees?
- **Standard fee**: 0.01 AMMO
- **Minimum fee**: 0.001 AMMO
- **Large transactions**: May require higher fees
- **Fee calculation**: Based on transaction size, not amount

### Why is my transaction taking so long?
Common causes:
- **Low fee**: Increase fee for faster confirmation
- **Network congestion**: Wait for congestion to clear
- **Disconnected**: Check peer connections
- **Wrong fee**: Some wallets calculate fees incorrectly

### Can I cancel a transaction?
- **Unconfirmed**: May be possible with `abandontransaction`
- **Confirmed**: Cannot be reversed (blockchain is immutable)
- **Prevention**: Always double-check before sending

## 🛠️ Troubleshooting Questions

### My wallet won't start. What should I do?
1. **Check** if another instance is running
2. **Remove** lock files (`~/.ammocoin11/.lock`)
3. **Under systemd?** "Cannot find the Sapling parameters" means the unit needs `Environment=HOME=/root` (or the service user's home)
4. **Try** `ammocoind -reindex`
5. **Check** available disk space
6. **Review** error messages in debug.log

### Why do I keep losing peer connections?
- **Firewall blocking**: Open port 37020
- **ISP issues**: Try VPN or different network
- **Outdated software**: v1.0/v1.1.0 nodes cannot connect to v1.1.1 - upgrade
- **Poor internet**: Check connection stability

### My balance disappeared after an update. Help!
**Don't panic!** Common solutions:
1. **New data folder** - v1.1.1 uses `~/.ammocoin11`; copy your `wallet.dat` from `~/.ammocoin`
2. **Wait for sync** - Might still be downloading blocks
3. **Rescan blockchain** - `ammocoind -rescan`
4. **Check network** - Ensure on mainnet, not testnet
5. **Restore backup** - If rescan doesn't work

### How do I report a bug?
1. **Search** existing issues on GitHub
2. **Gather** information (OS, version, error messages)
3. **Include** relevant log excerpts
4. **Provide** steps to reproduce
5. **Submit** detailed bug report

## 🪙 Proudly Worthless™

### Is AMMOcoin an investment?
**No. AMMO is Proudly Worthless™: worth nothing in money, permanently.** The project assigns AMMO no value, publishes no price, and promises no return, yield, profit or price. Nothing in these documents is an offer to sell anything or investment advice. AMMO exists to be used: staking, masternodes, governance and the GLiBz closed loop.

### Does AMMO have a price?
No. The project publishes no price, target or valuation for AMMO and does not comment on what it might be worth. Member-to-member trades are the members' own business; the project sets no price and is not a party.

### Do I have tax obligations on AMMO I receive?
Possibly - rules differ by country. Keep a record of every stake and payment you receive (date, amount, transaction hash) and ask a tax professional. *AMMO is not a proponent of its network being used to circumvent or bypass an individual's local, state or federal tax or financial reporting obligations. Every individual is responsible for their own actions.*

### Should I stake or run a masternode?
Depends on your situation:

**Staking** if you have:
- Less than 10,000 AMMO
- Limited technical knowledge
- Prefer simplicity

**Masternode** if you have:
- 10,000+ AMMO available (exact collateral: 10,000 AMMO)
- Technical skills for setup
- Want governance voting rights
- Willing to manage VPS

## 🆘 Support Questions

### Where can I get help?
- **Documentation**: Read this FAQ and guides first
- **Community**: https://ammocoin.org/community
- **GitHub**: Technical issues and bug reports (https://github.com/everquin/AMMOcoin/issues)

AMMOcoin has no official Discord or Telegram. Anyone offering "support" there, or asking for coins, keys or wallet files, is not the project.

### How do I stay updated with AMMOcoin news?
- **Official Website**: ammocoin.org
- **X**: x.com/ammocoin
- **GitHub Releases**: github.com/everquin/AMMOcoin/releases

### What should I include when asking for help?
- **Operating system** and version
- **AMMOcoin version**
- **Exact error messages**
- **What you were trying to do**
- **What you've already tried**
- **Relevant log excerpts**

### Is there a bug bounty program?
Check the official website and GitHub for current bug bounty programs. Serious security vulnerabilities should be reported privately to security@ammocoin.org.

## 🔄 Migration (v1.0 → v1.1)

### How do I get my v1.0 balance on v1.1?
**You don't need to send anything.** v1.0 balances from the snapshot at **block 434,881** are **airdropped to the same addresses** on v1.1.

1. **Back up** your v1.0 `wallet.dat` and keep it - the same keys control your v1.1 balance
2. **Install v1.1.1** from the official GitHub release
3. **Copy** a backup of the v1.0 `wallet.dat` into the v1.1.1 data folder (`~/.ammocoin11` on Linux)
4. **Start** the node and let it sync - your balance appears on your v1.0 addresses

See [v1.0 Balance Airdrop](migration/V1.0_BALANCE_AIRDROP.md) for details.

### Someone emailed me a "disposal address" to send my v1.0 coins to. Is that legitimate?
**❌ No - it is a scam.** The old disposal-address / email process is superseded. Never send coins, private keys or your wallet file to anyone.

### What if my balance is missing after sync?
Use the fallback **signed-message claim**: sign a message with your v1.0 address (`ammocoin-cli signmessage "V1.0_ADDRESS" "message"` on your v1.0 wallet) and submit it through the official channel announced on GitHub. A signature proves ownership without revealing your key.

### What is the migration deadline?
**There is no deadline.**

### What about masternodes?
v1.0 masternode configurations do not carry over. Once your airdropped balance is on v1.1 (at least 10,000 AMMO), set up a **fresh masternode** on v1.1.1 - see the [Masternode Setup Guide](03-masternode-setup.md).

### Where can I download v1.1.1?
From the official [GitHub Releases page](https://github.com/everquin/AMMOcoin/releases/tag/v1.1.1), with SHA256 checksums and a signed checksums file. Do not install binaries from any other source.

---

## 🔍 Still Need Help?

### Quick Solutions Checklist
- [ ] Restarted wallet software
- [ ] Checked internet connection
- [ ] Verified latest software version
- [ ] Reviewed debug.log for errors
- [ ] Searched this FAQ and documentation

### Community Support
If you can't find your answer here:
1. **Search** existing discussions
2. **Ask** in community channels
3. **Provide** detailed information
4. **Be patient** - volunteers help when available
5. **Help others** once you learn

### Emergency Support
For critical security issues or major bugs affecting the network, contact emergency@ammocoin.org with detailed information.

**💡 Remember: Most questions have been asked before. Search first, then ask with specific details for fastest help.**

---

*Back to [Documentation Hub](./README.md) for more detailed guides.*
# ❓ AMMOcoin Frequently Asked Questions

Quick answers to the most commonly asked questions about AMMOcoin. Find instant solutions and clarifications here.

## 🚀 Getting Started

### What is AMMOcoin?
**AMMOcoin** is a decentralized cryptocurrency built on Proof of Stake consensus, featuring masternodes, governance voting, and staking rewards. It offers fast 3-minute block times and focuses on community-driven development.

### Do I need to upgrade to v1.1.1?
**Yes - everyone must upgrade.** v1.1.1 (upcoming) is a hard fork: Proof-of-Stake from block 2,776, no mining after. It uses new network magic bytes, so v1.1.1 nodes do not connect to v1.0 or v1.1.0 nodes. It also uses a new data folder (`~/.ammocoincore`, `~/Library/Application Support/AMMOcoinCore`, `%APPDATA%\AMMOcoinCore`) - copy your `wallet.dat` across. See the [v1.1.1 Release Notes](release-notes/RELEASE_NOTES_v1.1.1.md).

### How do I get started with AMMOcoin?
1. **Download** the wallet from official sources
2. **Install** and sync with the network
3. **Encrypt** your wallet with a strong password
4. **Backup** your wallet.dat file securely
5. **Start staking** or consider running a masternode

### Where can I buy AMMOcoin?
**The AMMOcoin project does not sell AMMO**, has never held an ICO or token sale, and does not list AMMO on any exchange. AMMO is received, not bought from the project:
- **Staking**: Stakers who create a block receive the staker share set by the code (there is no mining after the v1.1.1 fork)
- **Masternodes**: Enabled masternodes receive the masternode payment when they reach the front of the queue
- **Contributions**: Development and community work can be rewarded from the reserves or by approved treasury proposals
- **GLiBz**: NUGGETS *earned* through activity on GLiBz can be swapped for AMMO; purchased NUGGETS can never reach AMMO

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
cp your_backup.dat ~/.ammocoincore/wallet.dat

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
**Staking** is holding AMMO coins in your wallet to help secure the network and earn rewards. Your coins have a chance to create new blocks and earn block rewards.

### How much can I earn from staking?
- **Block reward (v1.1.1)**: 250 AMMO per block today (the fork keeps the original schedule; 225 AMMO from block 86,401, 45 AMMO from 151,201); when a masternode is paid it gets 3 AMMO and the staker keeps 247 AMMO
- **Network issuance**: ~480 blocks/day, so ~120,000 AMMO/day today is shared by all stakers and masternodes - how many blocks you stake depends on your share of the coins being staked (expected share of blocks = your weight / network weight)
- **Factors**: Your coin amount, network weight, uptime
- **Frequency**: Small amounts may stake weekly/monthly
- **Maturity**: Rewards are ordinary coins and add to your staking weight once they have 600 confirmations

### What's the minimum amount needed for staking?
- **Technical minimum**: 1 AMMO
- **Practical minimum**: 100+ AMMO for regular rewards
- **Recommended**: 1,000+ AMMO for frequent rewards

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
- **Consider** combining small amounts or getting more AMMO

## 🏛️ Masternode Questions

### What is a masternode?
A **masternode** is a special type of node that provides enhanced services to the network (governance voting, budget finalization) and earns a fixed payment in return for maintaining 10,000 AMMO collateral.

### How much does it cost to run a masternode?
- **Collateral**: Exactly 10,000 AMMO
- **VPS Costs**: $5-20/month for hosting
- **Setup Time**: 2-4 hours initial setup
- **Technical Knowledge**: Basic Linux command line skills

### How are masternodes paid?
- **Payment**: 3 AMMO per paid block (6 AMMO only after block 3,715,200)
- **Network total**: ~480 blocks/day x 3 AMMO = ~1,440 AMMO/day shared by all enabled masternodes
- **Payment Frequency**: depends on how many masternodes are enabled
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
- **Payment missed**: You lose that round's reward
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
| **Block Reward** | 250 AMMO today (3 masternode / 247 staker); original schedule kept after the fork |
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
- **Integration**: Partnerships; any exchange listing is only possible through such a vote
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
2. **Remove** lock files (`~/.ammocoincore/.lock`)
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
1. **New data folder** - v1.1.1 uses `~/.ammocoincore`; copy your `wallet.dat` from `~/.ammocoin`
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

## 📈 Value Questions

### Is AMMOcoin a good investment?
**AMMO is not an investment, and the AMMOcoin project makes no claims about its value.** The project assigns AMMO no value, publishes no price, and promises no return, yield, profit or price. Nothing in these documents is an offer to sell anything or investment advice. AMMO exists to be used: staking, masternodes, governance and the GLiBz closed loop.

### What is AMMOcoin's price?
The project publishes no price, target or valuation for AMMO and does not comment on what it might be worth. Member-to-member trades are the members' own business; the project sets no price and is not a party.

### Do I have tax obligations on AMMO I receive?
Possibly - rules differ by country. Keep a record of every reward (date, amount, transaction hash) and ask a tax professional. *AMMO is not a proponent of its network being used to circumvent or bypass an individual's local, state or federal tax or financial reporting obligations. Every individual is responsible for their own actions.*

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
- **Discord**: Join official server for community help
- **Telegram**: Active support groups
- **Forum**: forum.ammocoin.org for detailed discussions
- **GitHub**: Technical issues and bug reports

### How do I stay updated with AMMOcoin news?
- **Official Website**: ammocoin.org
- **Twitter**: @AMMOcoinOfficial
- **Discord**: Official server announcements
- **Reddit**: r/AMMOcoin
- **Telegram**: Official channels

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
2. **Install v1.1.1 (upcoming)** when it is released
3. **Copy** a backup of the v1.0 `wallet.dat` into the v1.1.1 data folder (`~/.ammocoincore` on Linux)
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
v1.1.1 is **not released yet**. When it is, binaries will be published on the official [GitHub Releases page](https://github.com/everquin/AMMOcoin/releases). Do not install binaries from any other source.

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
# ❓ AMMOcoin Frequently Asked Questions

Quick answers to the most commonly asked questions about AMMOcoin. Find instant solutions and clarifications here.

## 🚀 Getting Started

### What is AMMOcoin?
**AMMOcoin** is a decentralized cryptocurrency built on Proof of Stake consensus, featuring masternodes, governance voting, and staking rewards. It offers fast 3-minute block times and focuses on community-driven development.

### How do I get started with AMMOcoin?
1. **Download** the wallet from official sources
2. **Install** and sync with the network
3. **Encrypt** your wallet with a strong password
4. **Backup** your wallet.dat file securely
5. **Start staking** or consider running a masternode

### Where can I buy AMMOcoin?
- **Exchanges**: Check CoinMarketCap for current listings
- **DEX Trading**: Decentralized exchange pairs
- **OTC Trading**: Direct peer-to-peer trades
- **Mining/Staking**: Earn through network participation

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
cp your_backup.dat ~/.ammocoin/wallet.dat

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
- **Annual Return**: ~8-12% per year
- **Factors**: Your coin amount, network weight, uptime
- **Frequency**: Small amounts may stake weekly/monthly
- **Compounding**: Rewards automatically increase your staking weight

### What's the minimum amount needed for staking?
- **Technical minimum**: 1 AMMO
- **Practical minimum**: 100+ AMMO for regular rewards
- **Recommended**: 1,000+ AMMO for frequent rewards

### Why isn't my wallet staking?
Check these common issues:
```bash
# Verify staking is enabled
ammocoin-cli getstakinginfo

# Common problems:
# - Wallet locked (unlock for staking)
# - Coins too new (wait 8+ hours)
# - Network disconnected (check peers)
# - Insufficient mature coins
```

### How do I unlock my wallet for staking?
```bash
# Unlock for staking only (secure)
ammocoin-cli walletpassphrase "your_password" 999999 true

# The 'true' parameter means "staking only"
# 999999 = stay unlocked for ~11 days
```

### My coins aren't staking after days/weeks. Why?
- **Small amounts** may take weeks or months to stake
- **Network weight** affects frequency - more network stakes = longer waits
- **Coin age** resets when you stake, starting the wait over
- **Consider** combining small amounts or getting more AMMO

## 🏛️ Masternode Questions

### What is a masternode?
A **masternode** is a special type of node that provides enhanced services to the network (InstantSend, governance voting) and earns premium rewards in return for maintaining 10,000 AMMO collateral.

### How much does it cost to run a masternode?
- **Collateral**: Exactly 10,000 AMMO
- **VPS Costs**: $5-20/month for hosting
- **Setup Time**: 2-4 hours initial setup
- **Technical Knowledge**: Basic Linux command line skills

### What returns can I expect from a masternode?
- **Annual Returns**: ~15-25% per year
- **Monthly Rewards**: ~100-200 AMMO (varies with network size)
- **Payment Frequency**: Every 12-24 hours typically
- **Break-even**: ~2-3 years (excluding AMMO price appreciation)

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
| **Protocol Version** | 70920 |

### How do I check if I'm on the correct network?
```bash
# Check network info
ammocoin-cli getnetworkinfo

# Verify chain
ammocoin-cli getblockchaininfo | grep chain
# Should show "main" not "test" or "regtest"

# Check protocol version
# Should be 70920 or higher
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
3. **Pay** proposal fee (5 AMMO)
4. **Submit** via wallet or command line
5. **Promote** to masternode operators

### What types of proposals are accepted?
- **Development**: New features, bug fixes
- **Marketing**: Promotion campaigns
- **Integration**: Exchange listings, partnerships
- **Community**: Events, education
- **Operations**: Infrastructure, legal

### How long does voting take?
- **Submission**: Immediate
- **Discussion**: 7 days recommended
- **Voting Period**: 30 days
- **Implementation**: Varies by proposal

## 🔧 Technical Questions

### Which operating systems are supported?
- **Windows**: Windows 10, 11 (64-bit)
- **macOS**: 10.14+ (Mojave and newer)
- **Linux**: Ubuntu 18.04+, CentOS 7+, Debian 9+
- **ARM**: Raspberry Pi 4 with 4GB+ RAM

### How much disk space do I need?
- **Current blockchain**: ~15GB
- **Growth rate**: ~2GB per year
- **Recommended**: 50GB+ free space
- **Pruning**: Can reduce to ~2GB with pruning enabled

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
2. **Remove** lock files (`~/.ammocoin/.lock`)
3. **Try** `ammocoind -reindex`
4. **Check** available disk space
5. **Review** error messages in debug.log

### Why do I keep losing peer connections?
- **Firewall blocking**: Open port 37020
- **ISP issues**: Try VPN or different network
- **Outdated software**: Update to latest version
- **Poor internet**: Check connection stability

### My balance disappeared after an update. Help!
**Don't panic!** Common solutions:
1. **Wait for sync** - Might still be downloading blocks
2. **Rescan blockchain** - `ammocoind -rescan`
3. **Check network** - Ensure on mainnet, not testnet
4. **Restore backup** - If rescan doesn't work

### How do I report a bug?
1. **Search** existing issues on GitHub
2. **Gather** information (OS, version, error messages)
3. **Include** relevant log excerpts
4. **Provide** steps to reproduce
5. **Submit** detailed bug report

## 📈 Investment Questions

### Is AMMOcoin a good investment?
**We cannot provide investment advice.** Consider:
- **Technology**: Strong blockchain with active development
- **Community**: Growing user and developer base
- **Use cases**: Staking, masternodes, governance
- **Risks**: Cryptocurrency investments are high-risk
- **Research**: Do your own thorough research

### What factors affect AMMOcoin's price?
- **Adoption**: More users = higher demand
- **Development**: New features and improvements
- **Market sentiment**: General crypto market trends
- **Competition**: Other similar cryptocurrencies
- **Regulations**: Government policies on crypto

### Should I stake or run a masternode?
Depends on your situation:

**Staking** if you have:
- Less than 10,000 AMMO
- Limited technical knowledge
- Prefer simplicity

**Masternode** if you have:
- 100,000+ AMMO available
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
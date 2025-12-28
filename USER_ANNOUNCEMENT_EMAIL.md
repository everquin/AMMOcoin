# AMMOcoin v1.1.0 Migration - User Announcement Email

---

**Subject:** AMMOcoin v1.1.0 Upgrade Available - Important Migration Information

---

Dear AMMOcoin Community Member,

We are excited to announce the release of **AMMOcoin v1.1.0**, a major upgrade bringing significant improvements to privacy, performance, and security.

## What's New in v1.1.0

**Enhanced Privacy:**
- Sapling shielded transactions for improved privacy
- Updated to latest PIVX 5.x codebase

**Improved Performance:**
- Faster blockchain synchronization
- Optimized staking mechanism
- Reduced memory usage

**Multi-Platform Support:**
- Windows x64
- macOS (Intel & Apple Silicon)
- Linux x86_64
- ARM64/Raspberry Pi

**Enhanced Security:**
- Latest cryptographic libraries
- Improved network protocol
- Modern masternode system

## Important: Migration Required

Due to fundamental improvements in the blockchain protocol, **you must migrate your AMMOcoin holdings from v1.0 to v1.1.0**.

### Timeline

- **v1.1.0 Network Launch:** [INSERT DATE]
- **Migration Window:** 90 days
- **v1.0 Network Sunset:** [INSERT DATE + 90 DAYS]

### Your Funds Are Safe

All balances from v1.0 blockchain at block height 434,881 have been preserved and will be available in v1.1.0.

**Snapshot Details:**
- Block Height: 434,881
- Block Hash: `c23bdb63ff149251b4cdcf401d579118342cf3ca4af1df0e34f4ecbdce2067d9`
- Date: [INSERT SNAPSHOT DATE]
- Total Supply: 232,397,748 AMMO

## How to Migrate

We've made migration as simple as possible. Choose the method that works best for you:

### Method 1: Wallet Import (Recommended - Easiest)

1. Download and install AMMOcoin v1.1.0
2. Launch the new wallet
3. Go to File → Import Wallet
4. Select your v1.0 wallet.dat file
5. Your balance will appear automatically

**Time required:** 5-10 minutes

### Method 2: Private Key Import (Most Flexible)

1. In your v1.0 wallet: Tools → Debug Console
2. Type: `dumpprivkey "YOUR_ADDRESS"`
3. Save the private key securely
4. Install AMMOcoin v1.1.0
5. In v1.1.0 wallet: Tools → Debug Console
6. Type: `importprivkey "YOUR_PRIVATE_KEY"`
7. Your balance will appear after sync

**Time required:** 10-15 minutes

### Method 3: Manual Backup & Restore (Most Secure)

Full step-by-step instructions are provided in the included migration guide.

**Time required:** 15-20 minutes

## Download AMMOcoin v1.1.0

**Choose your platform:**

### Windows
- **Windows x64:** [DOWNLOAD LINK]
- **Size:** ~XX MB
- **SHA256:** [CHECKSUM]

### macOS
- **macOS (Universal):** [DOWNLOAD LINK]
- **Size:** ~XX MB
- **SHA256:** [CHECKSUM]

### Linux
- **Linux x86_64:** [DOWNLOAD LINK]
- **Size:** ~XX MB
- **SHA256:** [CHECKSUM]

### ARM64/Raspberry Pi
- **ARM64:** [DOWNLOAD LINK]
- **Size:** ~XX MB
- **SHA256:** [CHECKSUM]

**Verify Downloads:**
Always verify the SHA256 checksum to ensure your download is authentic.

## Detailed Migration Guide

A comprehensive migration guide is attached to this email:
**USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.pdf**

This guide includes:
- Detailed migration instructions for each method
- Screenshots and examples
- Troubleshooting tips
- Security best practices
- FAQ

## For Large Holders (Top 61)

If you're one of our top 61 holders, your balance has been pre-distributed to the v1.1.0 genesis block. Simply:

1. Download and install AMMOcoin v1.1.0
2. Import your v1.0 private key
3. Your full balance will be available immediately (no sync required)

**Your address and amount:** [Will be sent in separate personalized email]

## For Small Balance Holders

If your v1.0 balance is under 200,000 AMMO, you'll claim your funds from the migration fund:

1. Install AMMOcoin v1.1.0
2. Generate a new address
3. Sign a message with your v1.0 address to prove ownership
4. Submit your claim via our web form or email
5. We'll verify and send your funds (usually within 24 hours)

**Claim form:** [LINK TO CLAIM FORM]

This process ensures security and prevents fraud.

## Need Help?

We're here to help you every step of the way!

### Support Options:

**Email Support:**
- Send questions to: support@ammocoin.org
- Response time: Usually within 24 hours

**1-on-1 Assistance:**
- Available for complex migrations
- Schedule a call: [CALENDLY LINK or EMAIL]

**Community Support:**
- Discord: [LINK]
- Telegram: [LINK]
- Forum: [LINK]

**Documentation:**
- Website: https://ammocoin.org
- Migration Guide: [LINK]
- FAQ: [LINK]

## Important Security Reminders

**Protect Your Private Keys:**
- Never share your private keys with anyone
- We will NEVER ask for your private keys
- Store backups in multiple secure locations

**Verify Before You Act:**
- Always verify SHA256 checksums
- Only download from official sources
- Beware of phishing emails

**Official Communication Channels:**
- Email: @ammocoin.org domain only
- Website: https://ammocoin.org
- Any other source should be verified with us first

## Migration Incentive

**Early Migration Bonus:**
Migrate within the first 30 days and receive a 2% bonus on your holdings!

**Bonus tiers:**
- Days 1-30: +2% bonus
- Days 31-60: +1% bonus
- Days 61-90: Standard migration (no bonus)

The earlier you migrate, the more you receive!

## What Happens to v1.0?

**v1.0 Timeline:**
- **Now - Day 90:** Both networks operational
- **Day 91:** v1.0 network sunset begins
- **Day 120:** v1.0 network fully shut down

**Important:** Any funds not migrated by Day 90 will require manual assistance and may incur delays.

## Frequently Asked Questions

**Q: Do I need to migrate if I'm just holding?**
A: Yes, everyone must migrate. The v1.0 network will be shut down after 90 days.

**Q: What happens to my masternode?**
A: You'll need to set up a new v1.1.0 masternode. Full instructions are in the migration guide.

**Q: Can I keep using v1.0?**
A: Yes, for the next 90 days. But we recommend migrating as soon as possible.

**Q: Will my addresses change?**
A: No! v1.1.0 uses the same address format, so your addresses work in both versions.

**Q: Is this safe?**
A: Absolutely. Your private keys work in both versions, and we've preserved all balances.

**Q: What if I miss the 90-day window?**
A: Contact us at support@ammocoin.org. We'll help you recover your funds, though it may take longer.

**Q: Are there any fees?**
A: Migration is completely free. Standard transaction fees apply for normal operations.

## Technical Details (For Advanced Users)

**Network Specifications:**
- Network ID: v1.1.0
- Genesis Hash: `000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845`
- P2P Port: 37020
- RPC Port: 37021
- Base58 Prefix: 23 (same as v1.0, addresses start with 'A')

**Seed Nodes:**
- seed1.ammocoin.org:37020
- seed2.ammocoin.org:37020
- seed3.ammocoin.org:37020

**GitHub Repository:**
- https://github.com/ammocoin/ammocoin

## Thank You

Thank you for being part of the AMMOcoin community. This upgrade represents months of development work and brings AMMOcoin up to modern standards while maintaining the values that make our community special.

We're excited about the future of AMMOcoin, and we're grateful to have you with us on this journey.

If you have any questions or concerns, please don't hesitate to reach out. We're committed to making this migration as smooth as possible for everyone.

Best regards,

**The AMMOcoin Development Team**

---

**Important Links:**
- Website: https://ammocoin.org
- Downloads: https://ammocoin.org/downloads
- Migration Guide: https://ammocoin.org/migration
- Support: support@ammocoin.org
- GitHub: https://github.com/ammocoin/ammocoin

---

**P.S.** Don't wait until the last minute! The migration process is simple, and early migrators receive bonus rewards. Download v1.1.0 today and secure your bonus!

---

*This is an official communication from the AMMOcoin Development Team. Please verify the sender address is @ammocoin.org.*

*If you received this email in error or wish to unsubscribe, please reply with "UNSUBSCRIBE" in the subject line.*

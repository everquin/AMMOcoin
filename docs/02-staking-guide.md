# 🎯 AMMOcoin Staking Guide

Earn passive income by staking your AMMOcoin! This guide explains everything you need to know about Proof of Stake rewards.

> ⚠️ **v1.1.1 (upcoming):** the network switches to Proof-of-Stake at **block 2,776**. There is no mining after the fork - staking is the only way new blocks are made. You must run **v1.1.1** to stake; v1.0 and v1.1.0 nodes cannot connect to the new network. See [Release Notes v1.1.1](release-notes/RELEASE_NOTES_v1.1.1_DRAFT.md).

## 🤔 What is Staking?

**Staking** is the process of holding AMMO coins in your wallet to help secure the network and earn rewards. From block 2,776 AMMOcoin is pure Proof-of-Stake: staking requires no special hardware - just your coins and an online wallet.

### How Staking Works
1. **Hold** AMMO coins in your wallet
2. **Keep** wallet online and unlocked for staking
3. **Earn** block rewards when your coins are selected
4. **Compound** rewards by continuing to stake

### Staking Benefits
- 💰 **Passive Income** - Earn rewards while you sleep
- 🔒 **Network Security** - Help secure the AMMOcoin network
- 🌱 **Eco-Friendly** - No energy-intensive hashing
- 📈 **Compound Growth** - Reinvest rewards automatically

## 🎰 Staking Rewards & Economics

### Reward Structure
The PoS fork does not change the reward schedule. Blocks keep paying the original v1.1 amounts: **250 AMMO** per block up to block 86,400, then 225 AMMO up to 151,200, 45 AMMO up to 302,400, and lower after that (see `GetBlockValue` in `source/src/validation.cpp`).

| Recipient | Per block (today, up to block 86,400) |
|-----------|-----------|
| Staker (block creator) | **247 AMMO** (250 AMMO if no masternode is paid in that block) |
| Masternode | **3 AMMO** (6 AMMO only after block 3,715,200) |

Treasury superblocks (every 43,200 blocks) only pay approved proposals. Transaction fees also go to the staker.

There is no fixed APY - your return depends on how much of the network's coins are staking. See the formula under [Reward Estimation](#reward-estimation).

### Factors Affecting Rewards
- **Maturity** - Each UTXO must have **600 confirmations** (about 30 hours) before it can stake
- **Network Weight** - Total coins staking network-wide
- **Wallet Uptime** - More online time = more opportunities
- **Coin Amount** - More coins = higher chance of rewards

## 🚀 How to Start Staking

### Prerequisites
- ✅ AMMOcoin wallet installed and synced
- ✅ Wallet encrypted with strong password
- ✅ AMMO that has at least **600 confirmations**
- ✅ Stable internet connection

### Step-by-Step Setup

#### 1. Prepare Your Coins
```
Maturity: 600 confirmations per UTXO before it can stake (~30 hours at 3-minute blocks)
More coins = higher chance of being selected
```

#### 2. Enable Staking in Wallet
1. **Open** AMMOcoin wallet
2. **Ensure** wallet is fully synced
3. **Go to** Settings → Options
4. **Check** "Enable staking" option
5. **Restart** wallet if prompted

#### 3. Unlock Wallet for Staking
1. **Click** Settings → "Unlock Wallet for Staking Only"
2. **Enter** your wallet password
3. **Check** "For staking only" option
4. **Set** unlock duration (recommend: permanent)
5. **Click** OK

Command line equivalent (unlock for staking only, no timeout):
```bash
./ammocoin-cli walletpassphrase "YOUR_PASSPHRASE" 0 true
```

#### 4. Verify Staking Status
Look for staking indicators:
- 🟢 **Green arrow** in status bar = Staking active
- ⏸️ **Pause symbol** = Staking paused
- 🔒 **Lock symbol** = Wallet locked (staking disabled)

### GUI Staking Setup
1. **Navigate** to "Staking" tab in wallet
2. **View** staking statistics:
   - Your weight vs network weight
   - Expected time to next reward
   - 24h/30d staking statistics
3. **Monitor** staking status actively

## 📊 Understanding Staking Mechanics

### Maturity & Weight
**Maturity** determines when a coin can stake:
- Each UTXO needs **600 confirmations** before it is eligible
- A UTXO that stakes (or is spent) starts again at 0 confirmations
- Older coins do **not** get extra weight - weight is the UTXO amount

### Staking Weight
```
Your Staking Weight = Sum of your mature UTXO amounts
Network Weight = Sum of all staking weights
Your Chance = Your Weight / Network Weight
```

### Block Selection Process
1. **Network** selects staker based on weight
2. **Selected** staker creates new block
3. **Reward** distributed to block creator
4. **Process** repeats every ~3 minutes

## 💡 Optimization Strategies

### Maximize Staking Rewards

#### 1. Optimal Coin Management
- **Split** large amounts into smaller UTXOs (1,000-10,000 AMMO each)
- **Avoid** micro-transactions that create dust
- **Consolidate** very small amounts periodically

#### 2. Wallet Management
```bash
# Set the stake split threshold (stake outputs larger than this are split)
./ammocoin-cli setstakesplitthreshold 5000

# Check staking status
./ammocoin-cli getstakingstatus

# View coin splits
./ammocoin-cli listunspent
```

#### 3. Uptime Optimization
- **24/7 Operation** - Keep wallet online continuously
- **Stable Connection** - Reliable internet required
- **UPS Backup** - Protect against power outages
- **VPS Hosting** - Consider cloud hosting for reliability

### Advanced Staking Setup

#### Cold Staking (Advanced Users)
Cold staking lets an always-on **staking server** stake your coins while the keys stay in your **owner wallet**. The server can stake but cannot spend.

1. **On the staking server** (online v1.1.1 node), create a staking address:
   ```bash
   ./ammocoin-cli getnewstakingaddress
   # returns an S... address
   ```
2. **In the owner wallet**, delegate coins to it:
   ```bash
   ./ammocoin-cli delegatestake "S_STAKING_ADDRESS" 5000
   # with a specific owner address:
   ./ammocoin-cli delegatestake "S_STAKING_ADDRESS" 5000 "A_OWNER_ADDRESS"
   # owner address not in this wallet (e.g. an offline wallet): set ext_owner=true
   ./ammocoin-cli delegatestake "S_STAKING_ADDRESS" 5000 "A_OFFLINE_OWNER_ADDRESS" true
   ```
3. **On the staking server**, whitelist the owner address so its delegations are staked, then check:
   ```bash
   ./ammocoin-cli delegatoradd "A_OWNER_ADDRESS"
   ./ammocoin-cli listcoldutxos           # delegated UTXOs
   ./ammocoin-cli getcoldstakingbalance   # coins delegated to this server
   ./ammocoin-cli getstakingstatus
   ```
4. **In the owner wallet**, check `./ammocoin-cli getdelegatedbalance`. Delegated coins still need 600 confirmations before they stake.

#### Multi-Wallet Staking
- **Run** multiple wallet instances
- **Split** coins across wallets
- **Increase** chances of frequent rewards
- **Manage** through different IP addresses

## 🔧 Staking Configuration

### Basic Configuration (ammocoin.conf)
```conf
# Enable staking
staking=1

# Network settings
server=1
listen=1
maxconnections=50

# Security
rpcuser=yourusername
rpcpassword=strongpassword
rpcallowip=127.0.0.1
```

### Advanced Staking Settings
```conf
# Minimum value allowed for the stake split threshold
minstakesplit=1000

# Cold staking support (default on; set 0 to disable)
coldstaking=1
```
The stake split threshold itself is set with `setstakesplitthreshold <amount>`. Cold staking is set up with RPC commands, not config entries - see [Cold Staking](#cold-staking-advanced-users).

## 📈 Monitoring Your Staking

### Wallet Indicators
- **Staking Status** - Active/Inactive indicator
- **Network Weight** - Total network staking power
- **Expected Time** - Estimated time to next reward
- **Recent Rewards** - Last staking transactions

### Command Line Monitoring
```bash
# Check staking status
./ammocoin-cli getstakingstatus

# View recent staking rewards
./ammocoin-cli listtransactions "" 10

# Check wallet balance
./ammocoin-cli getbalance

# View coin maturity
./ammocoin-cli listunspent
```

### Key Metrics to Track
1. **Staking Weight Percentage** - Your share of network
2. **Average Reward Frequency** - How often you earn
3. **Annual Percentage Yield** - Your effective return
4. **Wallet Uptime** - Connection reliability

## 🛠️ Troubleshooting Staking Issues

### Common Problems & Solutions

#### ❌ Staking Not Active
**Symptoms**: No green staking arrow, "Staking: Off"
**Solutions**:
1. **Unlock** wallet for staking only
2. **Check** staking=1 in config
3. **Verify** wallet is synced
4. **Restart** wallet application

#### ❌ No Staking Rewards
**Symptoms**: Staking active but no rewards received
**Solutions**:
1. **Wait** - Small amounts may take weeks
2. **Check** coin maturity (600+ confirmations - see `confirmations` in `listunspent`)
3. **Improve** uptime - keep wallet online
4. **Split** large coin amounts

#### ❌ Low Staking Weight
**Symptoms**: Very low expected time, poor performance
**Solutions**:
1. **Increase** coin amount
2. **Wait** for UTXOs to reach 600 confirmations
3. **Optimize** UTXO sizes
4. **Check** network weight trends

#### ❌ Frequent Disconnections
**Symptoms**: Wallet loses sync, staking stops
**Solutions**:
1. **Check** internet connection stability
2. **Configure** firewall for port 37020
3. **Add** reliable peer nodes (seed1 `78.141.194.140:37020`, seed2 `104.238.165.56:37020`)
4. **Consider** VPS hosting

### Debug Commands
```bash
# Detailed staking info
./ammocoin-cli getstakingstatus

# Check peer connections
./ammocoin-cli getpeerinfo

# Verify blockchain sync
./ammocoin-cli getblockchaininfo

# Check wallet status
./ammocoin-cli getwalletinfo
```

## 📊 Staking Calculators & Tools

### Reward Estimation
**Formula**: Annual Rewards = (Your Coins / Network Weight) × Annual Block Rewards

**Example Calculation**:
```
Your Coins: 10,000 AMMO
Network Weight: 50,000,000 AMMO (example only)
Your Share: 10,000 / 50,000,000 = 0.02%
Annual Blocks: 175,200 (1 block per 3 min)
Staker Reward: 247 AMMO per block (250 AMMO minus 3 AMMO masternode payment)
Expected Annual: 175,200 × 247 × 0.0002 = ~8,655 AMMO
Annual Return: 8,655 / 10,000 = ~87%
```

This assumes every block pays 250 AMMO. That holds only up to block 86,400 (about 6 months after the fork); after that the block value drops to 225 AMMO, then 45 AMMO from block 151,201, so a real year earns less. The network weight is also an example only: the more coins stake, the smaller your share.

```
```

### Online Tools
- **AMMOcoin Block Explorer** - View network statistics
- **Staking Calculator** - Estimate rewards
- **Network Monitoring** - Track network health

## 🔐 Staking Security

### Security Best Practices
1. **🔒 Encrypted Wallet** - Always encrypt with strong password
2. **🔐 Unlock for Staking Only** - Never unlock fully online
3. **💾 Regular Backups** - Backup wallet.dat frequently
4. **🔥 Firewall Protection** - Configure network security
5. **🛡️ Antivirus Active** - Protect against malware

### Cold Staking Security
- **Keep** private keys offline
- **Use** dedicated staking node
- **Monitor** remotely for security
- **Separate** staking and holding wallets

## 💰 Tax Considerations

### Staking Rewards as Income
- **Record** all staking rewards received
- **Track** fair market value at receipt time
- **Calculate** annual staking income
- **Consult** tax professional for advice

### Record Keeping
- Date and time of reward
- Amount of AMMO received
- USD value at time of receipt
- Transaction hash for verification

## 🎯 Advanced Staking Strategies

### Portfolio Allocation
- **80%** - Long-term staking (large UTXOs)
- **15%** - Active trading/liquidity
- **5%** - Experimental/new features

### Compound Staking
1. **Reinvest** all staking rewards
2. **Combine** small rewards periodically
3. **Optimize** UTXO sizes regularly
4. **Track** compound growth over time

### Multi-Strategy Approach
- **Combine** staking with masternode rewards
- **Diversify** across different wallets
- **Balance** security with earning potential

---

## ✅ Staking Checklist

- [ ] Wallet installed and fully synced
- [ ] Running v1.1.1 and synced past block 2,775
- [ ] Coins have 600+ confirmations
- [ ] Wallet encrypted with strong password
- [ ] Staking enabled in settings
- [ ] Wallet unlocked for staking only
- [ ] Green staking indicator visible
- [ ] Stable internet connection confirmed
- [ ] Backup created and stored safely
- [ ] Monitoring setup configured

**🎉 Congratulations! You're now earning passive income through AMMOcoin staking.**

---

*Next: Learn about [Masternodes](./03-masternode-setup.md) for higher rewards with larger investments.*
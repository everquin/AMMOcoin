# 🎯 AMMOcoin Staking Guide

Earn passive income by staking your AMMOcoin! This guide explains everything you need to know about Proof of Stake rewards.

## 🤔 What is Staking?

**Staking** is the process of holding AMMO coins in your wallet to help secure the network and earn rewards. Unlike mining, staking requires no special hardware - just your coins and an online wallet.

### How Staking Works
1. **Hold** AMMO coins in your wallet
2. **Keep** wallet online and unlocked for staking
3. **Earn** block rewards when your coins are selected
4. **Compound** rewards by continuing to stake

### Staking Benefits
- 💰 **Passive Income** - Earn rewards while you sleep
- 🔒 **Network Security** - Help secure the AMMOcoin network
- 🌱 **Eco-Friendly** - No energy-intensive mining
- 📈 **Compound Growth** - Reinvest rewards automatically

## 🎰 Staking Rewards & Economics

### Reward Structure
| Staking Amount | Annual Return (APY) | Monthly Rewards* |
|----------------|-------------------|------------------|
| 100 AMMO | ~8-12% | 0.67-1.0 AMMO |
| 1,000 AMMO | ~8-12% | 6.7-10 AMMO |
| 10,000 AMMO | ~8-12% | 67-100 AMMO |
| 100,000 AMMO | ~8-12% | 667-1,000 AMMO |

*Estimates based on current network conditions

### Factors Affecting Rewards
- **Coin Age** - Older coins have higher priority
- **Network Weight** - Total coins staking network-wide
- **Wallet Uptime** - More online time = more opportunities
- **Coin Amount** - More coins = higher chance of rewards

## 🚀 How to Start Staking

### Prerequisites
- ✅ AMMOcoin wallet installed and synced
- ✅ Wallet encrypted with strong password
- ✅ At least 1 AMMO (minimum staking amount)
- ✅ Stable internet connection

### Step-by-Step Setup

#### 1. Prepare Your Coins
```
Minimum staking: 1 AMMO
Recommended: 100+ AMMO for regular rewards
Optimal: 1,000+ AMMO for daily rewards
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

### Coin Age & Weight
**Coin Age** determines staking priority:
- Coins gain "age" after 8 hours (maturation time)
- Maximum effective age: 30 days
- Older coins have higher selection probability
- Used coins reset to 0 age

### Staking Weight
```
Your Staking Weight = (Coin Amount) × (Coin Age)
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
# Split coins for optimal staking (CLI command)
./ammocoin-cli splitstakingutxos 5000

# Check staking info
./ammocoin-cli getstakinginfo

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
1. **Setup** hot wallet on VPS/dedicated machine
2. **Delegate** staking rights from cold wallet
3. **Keep** coins secure offline
4. **Earn** rewards while maintaining security

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

# Optimize for staking
stakeminconfirmations=1
stakecachesize=2000

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
# Reserve balance (don't stake these coins)
reservebalance=100

# Minimum stake split size
minstakesplit=1000

# Stake split threshold
stakesplitthreshold=2000

# Cold staking
coldstaking=1
coldstakingaddress=your_cold_address
```

## 📈 Monitoring Your Staking

### Wallet Indicators
- **Staking Status** - Active/Inactive indicator
- **Network Weight** - Total network staking power
- **Expected Time** - Estimated time to next reward
- **Recent Rewards** - Last staking transactions

### Command Line Monitoring
```bash
# Check staking status
./ammocoin-cli getstakinginfo

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
2. **Check** coin maturity (>8 hours old)
3. **Improve** uptime - keep wallet online
4. **Split** large coin amounts

#### ❌ Low Staking Weight
**Symptoms**: Very low expected time, poor performance
**Solutions**:
1. **Increase** coin amount
2. **Age** coins by waiting
3. **Optimize** UTXO sizes
4. **Check** network weight trends

#### ❌ Frequent Disconnections
**Symptoms**: Wallet loses sync, staking stops
**Solutions**:
1. **Check** internet connection stability
2. **Configure** firewall for port 37020
3. **Add** reliable peer nodes
4. **Consider** VPS hosting

### Debug Commands
```bash
# Detailed staking info
./ammocoin-cli getstakinginfo

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
Network Weight: 50,000,000 AMMO
Your Share: 10,000 / 50,000,000 = 0.02%
Annual Blocks: 175,200 (1 block per 3 min)
Block Reward: ~5 AMMO average
Expected Annual: 175,200 × 5 × 0.0002 = 175 AMMO
Annual Return: 175 / 10,000 = 1.75%
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
- [ ] Minimum coins available (1+ AMMO)
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
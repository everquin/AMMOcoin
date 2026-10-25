# 🎯 AMMOcoin Staking Guide

Stake your AMMOcoin to help secure the network. This guide explains how Proof of Stake works and how blocks are made, in the terms the code uses.

> AMMOcoin is Proudly Worthless™: the project sells nothing, publishes no price and promises no return. Staking is how you and your crew run the network, not a source of income.

> ⚠️ **v1.1.1:** the network switches to Proof-of-Stake at **block 2,776**. There is no mining after the fork - staking is the only way new blocks are made. You must run **v1.1.1** to stake; v1.0 and v1.1.0 nodes cannot connect to the new network. See [Release Notes v1.1.1](release-notes/RELEASE_NOTES_v1.1.1.md).

## 🤔 What is Staking?

**Staking** is the process of holding AMMO coins in an online wallet so that it takes part in making blocks and securing the network. From block 2,776 AMMOcoin is pure Proof-of-Stake: staking requires no special hardware - just your coins and an online wallet.

### How Staking Works
1. **Hold** AMMO coins in your wallet
2. **Keep** wallet online and unlocked for staking
3. **Make blocks** when your coins are selected
4. **Keep staking** - coins from a staked block are ordinary coins and can stake once they mature

### Staking Benefits
- 🔒 **Network Security** - Help secure the AMMOcoin network
- 🌱 **Eco-Friendly** - No energy-intensive hashing
- 🧱 **Block Production** - Stakers create the blocks
- 🤝 **Run it with your crew** - Every staking wallet that stays online helps keep the network producing blocks

## 🧱 How Blocks Are Paid (code terms)

### Block Issuance
The PoS fork does not change the issuance schedule. It is the original declining schedule set by `GetBlockValue()` in `source/src/validation.cpp`. Each block pays the masternode selected by the payment queue its share (`nMNBlockReward`, via `GetMasternodePayment()`), and the staker that makes the block receives the rest. This guide states no amounts: read them from the code.

Treasury superblocks (every 43,200 blocks) only pay proposals approved by masternode vote. In Proof-of-Stake blocks transaction fees are not paid to the staker; they are removed from circulation (`source/src/validation.cpp`, "PoS stage destroys fees").

There is no fixed rate and nothing is promised. How often you make a block depends on your share of the coins staking network-wide and on keeping your wallet online. See [Block Share Estimation](#block-share-estimation).

### Factors Affecting How Often You Stake
- **Maturity** - Each UTXO must have **600 confirmations** (about 30 hours) before it can stake
- **Network Weight** - Total coins staking network-wide
- **Wallet Uptime** - More online time = more opportunities
- **Coin Amount** - More mature coins = higher chance of making a block

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
   - Expected time to next stake
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
3. **Block** paid out as the code sets
4. **Process** repeats every ~3 minutes

## 💡 Optimization Strategies

### Stake Reliably

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
- **Spread** staking across machines
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
- **Expected Time** - Estimated time to next stake
- **Recent Stakes** - Last staking transactions

### Command Line Monitoring
```bash
# Check staking status
./ammocoin-cli getstakingstatus

# View recent staking transactions
./ammocoin-cli listtransactions "" 10

# Check wallet balance
./ammocoin-cli getbalance

# View coin maturity
./ammocoin-cli listunspent
```

### Key Metrics to Track
1. **Staking Weight Share** - Your weight / network weight
2. **Blocks Created** - How many blocks your wallet has staked
3. **Expected Time to Stake** - Shown by the wallet, based on your weight
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

#### ❌ No Stakes
**Symptoms**: Staking active but no blocks staked
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

### Block Share Estimation
Staking is a lottery weighted by coins. Each block goes to one staker, chosen in proportion to the weight of mature coins staking.

**Expected share of blocks** = Your Weight / Network Weight

**Expected stakes per day** = Expected share × Blocks per day (480 at one block per 3 minutes)

**Example**:
```
Your Weight:      10,000 AMMO
Network Weight:   250,000,000 AMMO (example figure only)
Expected share:   10,000 / 250,000,000 = 0.004% of blocks
Blocks per day:   480
Expected stakes:  480 x 0.00004 = ~0.019 per day, i.e. about one block every 52 days
```

Each block you stake pays the staker share set by `GetBlockValue()` minus `GetMasternodePayment()` at that height. These are averages, not promises: the network weight changes as others stake, the block value falls over time, and you only stake while your wallet is online and unlocked.

### Online Tools
- **AMMOcoin Block Explorer** - View network statistics
- **`getstakingstatus`** - Check that your wallet is staking
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

### Staked Blocks
- **Record** every staked block (stake transaction) your wallet receives
- **Consult** a tax professional about how staking is treated where you live

### Record Keeping
- Date and time of the stake
- Amount of AMMO received
- Transaction hash for verification

*AMMO is not a proponent of its network being used to circumvent or bypass an individual's local, state or federal tax or financial reporting obligations. Every individual is responsible for their own actions.* The AMMOcoin project publishes no price for AMMO; it is your responsibility to work out what your local rules require.

## 🎯 Staking Practices

### UTXO Management
1. **Combine** many small UTXOs periodically
2. **Optimize** UTXO sizes regularly
3. **Remember** that moving coins resets their maturity (600 confirmations)

### Combining with Masternodes
- Masternode collateral is locked and is not used for staking; stake with your other coins
- **Balance** security with uptime: a wallet only stakes while it is online and unlocked for staking

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

**🎉 Congratulations! Your wallet is now staking and helping secure the AMMOcoin network.**

---

*Next: Learn about [Masternodes](./03-masternode-setup.md), which provide network services and receive the masternode share of each block.*
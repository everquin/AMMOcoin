# AMMOcoin v1.1.1 (upcoming) - Proof-of-Stake Hard Fork

**Status:** DRAFT - v1.1.1 is not released yet. Download links and SHA256 checksums will be added when the signed release is published on GitHub. Do not install binaries from any other source.
**Release Type:** Mandatory hard fork - every node, wallet, staker, masternode and seed must upgrade
**Fork Height:** Block 2,776

---

## ⚠️ Everyone Must Upgrade

The v1.1 chain stopped at block 2,775 after its Proof-of-Work phase. v1.1.1 switches the network to **Proof-of-Stake from block 2,776**. There is no mining after the fork.

- **New network magic bytes** (`c7 9a e3 b5`). v1.1.1 nodes do **not** connect to v1.0 or v1.1.0 nodes, and v1.1.0 nodes cannot follow the PoS chain.
- A v1.1.0 node left running will sit at block 2,775 with no peers. Stop it and install v1.1.1.
- The genesis block is unchanged: `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

---

## What Changes

| | v1.1.0 | v1.1.1 (upcoming) |
|---|---|---|
| Consensus | Proof-of-Work | **Proof-of-Stake from block 2,776** (no mining) |
| Network magic | v1.0-compatible | `c7 9a e3 b5` (separate network) |
| Default data folder | `.ammocoin` / `AMMOcoin` | `.ammocoin11` / `AMMOcoin11` (see below) |
| Fixed seed nodes | 78.141.194.140, 147.182.245.102 (dead) | 78.141.194.140, 104.238.165.56, 207.246.95.210, 45.76.116.97, 144.202.79.114 (DNS: seed1-3.ammocoin.org) |
| Linux binaries | glibc 2.31+ | **glibc 2.34+** (Ubuntu 22.04 or newer) |

Other fixes in this release:
- Restart crash after the fork fixed (the node asserted on every restart once the Zerocoin upgrade height was active).
- Linux build fixed for glibc 2.36+ (Ubuntu 24.04).
- Rewards keep the original schedule after the fork (250 AMMO per block, 3 AMMO to masternodes, budget at 20%). Reward heights are now separate from the upgrade heights (`nRewardZCV2Height` 1,153,160 and `nRewardV55Height` 3,715,200 on mainnet), so activating every upgrade at block 2,776 does not change what blocks pay.

---

## Network Parameters (mainnet)

| Parameter | Value |
|---|---|
| P2P port | **37020** |
| RPC port | **51473** |
| Block time (target spacing) | 3 minutes |
| Stake maturity | **600 confirmations** (about 30 hours) before a UTXO can stake |
| Masternode collateral | **10,000 AMMO** (15 confirmations) |
| Block reward | Unchanged by the fork: **250 AMMO** per block up to block 86,400, then 225 AMMO, 45 AMMO from block 151,201, and the rest of the original schedule |
| Masternode payment | **3 AMMO** per paid block, taken out of the block reward; the staker keeps the rest (247 AMMO today). 6 AMMO only after block 3,715,200 |
| Treasury (budget) | Superblocks every 43,200 blocks (about 90 days), up to 20% of the block value x 43,200 (50 AMMO x 43,200 = 2,160,000 AMMO per cycle today), paid only to approved proposals |
| DNS seeds | seed1.ammocoin.org, seed2.ammocoin.org |
| Fixed seeds | 78.141.194.140 (seed1), 104.238.165.56 (seed2.ammocoin.org) |

> Some older documents list port 37019 or RPC 51474. Those are wrong for mainnet. Use **37020** (P2P) and **51473** (RPC).

---

## New Data Folder

v1.1.1 uses a new default data directory so it never mixes with v1.0 or v1.1.0 data:

| OS | v1.1.1 data folder | Old folder (v1.0 / v1.1.0) |
|---|---|---|
| Linux | `~/.ammocoin11` | `~/.ammocoin` |
| macOS | `~/Library/Application Support/AMMOcoin11` | `~/Library/Application Support/AMMOcoin` |
| Windows | `%APPDATA%\AMMOcoin11` | `%APPDATA%\AMMOcoin` |

Sapling parameters are stored separately: Linux `~/.ammocoin-params`, macOS `~/Library/Application Support/AMMOcoinParams`, Windows `%APPDATA%\AMMOcoinParams`.

> **Pre-release testers:** early v1.1.1 test builds used magic `a3 4d b1 e7` and the folder `.ammocoincore` / `AMMOcoinCore`. Release builds use neither and cannot connect to that test network. See [MAINNET_SEPARATION.md](../MAINNET_SEPARATION.md).

**Upgrading a v1.1.0 node:**
1. Stop the old node: `ammocoin-cli stop`
2. Back up your v1.1.0 `wallet.dat` (and your v1.0 `wallet.dat` if you still have one - keep both).
3. Create the new folder and copy over only what you need: `ammocoin.conf`, `masternode.conf` (masternodes), and `wallet.dat`.
4. Check `ammocoin.conf` uses `port=37020` / `rpcport=51473` and remove any `addnode=147.182.245.102`.
5. Start v1.1.1 and let it sync from the seeds. Do not copy `blocks/` or `chainstate/` from v1.1.0.

If you want to keep using the old location, start the node with `-datadir=<old folder>`, but a fresh folder is recommended.

---

## Operating System Requirements

- **Linux:** the release binaries need **glibc 2.34 or newer** - Ubuntu 22.04 LTS or newer (Ubuntu 24.04 LTS is tested), Debian 12 or newer.
- **Ubuntu 18.04 and 20.04 cannot run v1.1.1 binaries.** Upgrade or reinstall the OS (a fresh Ubuntu 24.04 VPS is the simplest path). Check with `ldd --version`.
- macOS and Windows: see the release page when it is published.

---

## How to Stake

1. Install v1.1.1 and fully sync.
2. Hold AMMO in your wallet. Each UTXO needs **600 confirmations** before it can stake.
3. Unlock the wallet for staking only:
   ```bash
   ammocoin-cli walletpassphrase "YOUR_PASSPHRASE" 0 true
   ```
4. Check:
   ```bash
   ammocoin-cli getstakingstatus
   ```
   `staking_status: true` means the wallet is staking. The wallet must stay online.

## How to Cold Stake

Cold staking lets an always-on node stake your coins while the keys stay in your own (owner) wallet. The staking node can stake but cannot spend.

On the **staking server** (online node):
```bash
ammocoin-cli getnewstakingaddress
# returns an S... address
```

Also on the staking server, whitelist the owner address (the address the coins are delegated from). Without this the server does not stake the delegated coins:
```bash
ammocoin-cli delegatoradd "A_OWNER_ADDRESS"
```

In the **owner wallet**:
```bash
ammocoin-cli delegatestake "S_STAKING_ADDRESS" 5000
# optional owner address:  delegatestake "S_STAKING_ADDRESS" 5000 "A_OWNER_ADDRESS"
# owner address not in this wallet (e.g. offline):  add ext_owner=true
ammocoin-cli delegatestake "S_STAKING_ADDRESS" 5000 "A_OFFLINE_OWNER_ADDRESS" true
```

Check:
```bash
ammocoin-cli getcoldstakingbalance   # on the staking server: coins delegated to it
ammocoin-cli getdelegatedbalance     # in the owner wallet: coins it has delegated
ammocoin-cli listcoldutxos           # on the staking server
ammocoin-cli getstakingstatus        # on the staking server
```

## How to Run a Masternode

Masternodes need **10,000 AMMO** collateral and a VPS with a **public, routable IP** on port **37020**. 127.0.0.1 or private addresses (10.x, 172.16-31.x, 192.168.x) are rejected with `Invalid IP address`.

In the **controller wallet**:
```bash
ammocoin-cli getnewaddress "mn1"
ammocoin-cli sendtoaddress "ADDRESS_FROM_ABOVE" 10000
# wait 15 confirmations
ammocoin-cli createmasternodekey          # save this key
ammocoin-cli getmasternodeoutputs         # collateral txid and index
```

Controller `masternode.conf` (one line per masternode):
```
mn1 YOUR_VPS_IP:37020 MASTERNODE_PRIVKEY COLLATERAL_TXID COLLATERAL_INDEX
```

VPS `ammocoin.conf`:
```
server=1
listen=1
masternode=1
masternodeprivkey=MASTERNODE_PRIVKEY
masternodeaddr=YOUR_VPS_IP:37020
externalip=YOUR_VPS_IP
```

Start it from the controller wallet, then check on the VPS:
```bash
ammocoin-cli startmasternode alias false mn1    # controller
ammocoin-cli getmasternodestatus                # VPS
ammocoin-cli listmasternodes                    # either
```

There is no `masternode genkey` command and no `createwallet` command in AMMOcoin.

## systemd (Linux servers)

The service must set `HOME`, otherwise the node exits with `Cannot find the Sapling parameters`. Tested unit (`/etc/systemd/system/ammocoind.service`):

```ini
[Unit]
Description=AMMOcoin daemon
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
User=root
Environment=HOME=/root
ExecStart=/opt/ammocoin-v1.1.1/bin/ammocoind -datadir=/root/.ammocoin11 -daemon=0
ExecStop=/opt/ammocoin-v1.1.1/bin/ammocoin-cli -datadir=/root/.ammocoin11 stop
Restart=on-failure
TimeoutStopSec=120

[Install]
WantedBy=multi-user.target
```

If the service runs as another user, set `User=` and `Environment=HOME=` to that user and point `-datadir` at their home.

---

## v1.0 Holders: Balance Airdrop

v1.0 balances from the snapshot at **block 434,881** are airdropped to the **same addresses** on v1.1.

- **Keep your v1.0 `wallet.dat`.** The same keys control your airdropped balance on v1.1. Import it into v1.1.1 (copy it into the new data folder) after backing it up.
- **Send nothing anywhere.** There is no disposal address. Anyone who emails you an address to send coins to is attempting a scam.
- If an address was missed, a **signed-message claim** (proving you own the v1.0 address with `signmessage`) is the fallback.
- **No deadline.**

Details: [v1.0 Balance Airdrop](../migration/V1.0_BALANCE_AIRDROP.md). The earlier disposal-address / email process is **superseded**.

---

## Block 1 Premine

The 250,000,000 AMMO distribution premine is in block 1, paid to `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u`.

---

## Upgrade Checklist

- [ ] Back up every `wallet.dat` (v1.0 and v1.1.0) to offline storage
- [ ] Linux: confirm glibc 2.34+ (`ldd --version`); upgrade from Ubuntu 18.04/20.04 first
- [ ] Stop the old node
- [ ] Install v1.1.1 (only from the official GitHub release, once published)
- [ ] Move `ammocoin.conf`, `masternode.conf`, `wallet.dat` into the new data folder
- [ ] Ports 37020 / 51473; remove 147.182.245.102 and 37019 from configs
- [ ] systemd units: add `Environment=HOME=...`
- [ ] Start, sync, then `getblockcount` should go past 2,775
- [ ] Re-unlock for staking / restart masternodes from the controller

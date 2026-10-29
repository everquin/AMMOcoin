**Mandatory upgrade.** v1.1.1 is a hard fork: Proof-of-Stake from block 2,776. Every node, wallet and masternode must upgrade.

# AMMOcoin v1.1.1 - Proof-of-Stake Hard Fork

**Release type:** Mandatory hard fork. Every node, wallet, staker, masternode and seed must upgrade.
**Fork height:** block 2,776
**Source branch:** `v1.1.1-pos-fork` (changes since the `v1.1.0` tag)

> AMMOcoin is network software. These notes describe what the code does. They are not an offer, not investment advice and not a promise of any return, price or value. They state no block subsidy or payment amounts: those are set by the code (`GetBlockValue()` in `source/src/validation.cpp`), and what any node receives depends on network participation and uptime.

---

## Everyone Must Upgrade

The v1.1 chain stopped at block 2,775 after its Proof-of-Work phase. v1.1.1 switches the network to **Proof-of-Stake from block 2,776**. There is no mining after the fork.

- **New network magic bytes** (`c7 9a e3 b5`). v1.1.1 nodes do **not** connect to v1.0 or v1.1.0 nodes, and v1.1.0 nodes cannot follow the PoS chain.
- A v1.1.0 node left running sits at block 2,775 with no peers. Stop it and install v1.1.1.
- The genesis block is unchanged: `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

---

## What Changes

| | v1.1.0 | v1.1.1 |
|---|---|---|
| Consensus | Proof-of-Work | **Proof-of-Stake from block 2,776** (no mining) |
| Network magic | v1.0-compatible | `c7 9a e3 b5` (separate network) |
| Default data folder | `.ammocoin` / `AMMOcoin` | `.ammocoin11` / `AMMOcoin11` (see below) |
| Fixed seed nodes | 78.141.194.140, 147.182.245.102 (dead) | 78.141.194.140, 104.238.165.56, 207.246.95.210, 45.76.116.97, 144.202.79.114 (DNS: seed1-3.ammocoin.org) |
| Linux binaries | glibc 2.31+ | **glibc 2.34+** (Ubuntu 22.04 or newer) |
| macOS | ARM64 only, ad-hoc signed | **ARM64 and x86_64, Developer ID signed and notarized, macOS 13 or newer** |
| Linux GUI wallet | not shipped | **Qt wallet tarball and AppImage** (x86_64 and ARM64) |
| Node installer | manual | **`install-node.sh`** one-command installer |

### Consensus and node

- **PoS activation at block 2,776** (`ade7fc983`). On mainnet every network upgrade through v5.6 (PoS, PoS v2, Zerocoin/ZC v2/ZC public, BIP65, v3.4, v4.0, v5.0-v5.6, which bring cold staking and Sapling) activates at the fork height; v6.0 stays off. Testnet activates at block 201, regtest at 251.
- **Block subsidy schedule unchanged by the fork** (`0f7d10faf`). The subsidy code no longer follows the upgrade heights; it uses its own heights (`nRewardZCV2Height` 1,153,160 and `nRewardV55Height` 3,715,200 on mainnet), so activating every upgrade at block 2,776 does not change the schedule. Without this fix, post-fork blocks would have used the stage the schedule sets for block 3,715,200. Covered by `source/src/test/budget_tests.cpp`.
- **Restart crash after the fork fixed** (`ca41fe1b9`). The node asserted on every restart once the Zerocoin upgrade height was active (`invalid_out::LoadOutpoints` treated AMMOcoin's empty compiled-in list as a load failure).
- **Testnet and regtest genesis fixed** (`afd323157`) for AMMOcoin's own genesis block.
- **Pre-production hardening** (`116e04583`, no consensus change): OP_RETURN size check fixed in `sendopreturn` / `createrawtransaction` (oversized payloads no longer build scripts that fail to relay), `-datacarrier=0` honored, per-IP RPC authentication lockout (`-rpcauthmaxfails`), HTTP body cap 8 MiB by default (`-rpcmaxbodysize`), RPC cookie file created with mode 0600.
- **Database fixes carried from the v1.1.0 rebuilds** (`33c9af0b6`, `e4628fcce`): LevelDB block database corruption on shutdown, and a block index serialization version mismatch.
- **scrypt** uses a private `be32enc` so macOS builds no longer depend on the SDK (`581b91306`).

---

## Network Parameters (mainnet)

| Parameter | Value |
|---|---|
| P2P port | **37020** |
| RPC port | **51473** |
| Block time (target spacing) | 3 minutes |
| Stake maturity | **600 confirmations** (about 30 hours) before a UTXO can stake; minimum stake age 1 hour |
| Masternode collateral | **10,000 AMMO** (15 confirmations) |
| Block subsidy | Unchanged by the fork: the original declining schedule in `GetBlockValue()` (`source/src/validation.cpp`) |
| Masternode payment | A fixed share of each block's subsidy (`nMNBlockReward`), paid to the masternode selected by the payment queue; the staker receives the rest. The share changes at block 3,715,200 (`nNewMNBlockReward`) |
| Treasury (budget) | Superblocks every **43,200 blocks** (about 90 days), paid only to proposals approved by masternode vote, within the budget limit set in the code |
| DNS seeds | seed1.ammocoin.org, seed2.ammocoin.org |
| Fixed seeds | 78.141.194.140 (seed1), 104.238.165.56 (seed2), 207.246.95.210 / 45.76.116.97 / 144.202.79.114 (seed3.ammocoin.org) |

> Some older documents list port 37019 or RPC 51474. Those are wrong for mainnet. Use **37020** (P2P) and **51473** (RPC).

How often a given wallet stakes or a given masternode is paid depends on the total stake weight and the number of enabled masternodes on the network, and on the node staying online. The project does not estimate or promise any rate.

---

## Masternode Payment Queue

- Each block pays the masternode selected by the payment queue its share of the block subsidy (`nMNBlockReward`); the staker receives the rest.
- Collateral is **10,000 AMMO** (`nMNCollateralAmt`) kept in your own controller wallet with 15 confirmations. It is never sent to the project or locked by anyone else.
- The masternode must have a **public, routable IPv4** on port **37020**. 127.0.0.1 and private ranges are rejected with `Invalid IP address`.
- With N enabled masternodes, each one is paid about once every N blocks while it stays enabled.
- From block 3,715,200 (`nRewardV55Height`) the masternode share changes to `nNewMNBlockReward`, as in the original schedule.

Setup: [Masternode guide](../03-masternode-setup.md). Controller `masternode.conf` line: `mn1 YOUR_VPS_IP:37020 MASTERNODE_PRIVKEY COLLATERAL_TXID COLLATERAL_INDEX` (key from `createmasternodekey`, outputs from `getmasternodeoutputs`).

---

## Cold Staking

Cold staking is active from the fork. An always-on node stakes your coins while the keys stay in your own (owner) wallet; the staking node can stake but cannot spend.

On the **staking server**:
```bash
ammocoin-cli getnewstakingaddress          # returns an S... address
ammocoin-cli delegatoradd "A_OWNER_ADDRESS" # required: the server only stakes owners it has added
```

In the **owner wallet**:
```bash
ammocoin-cli delegatestake "S_STAKING_ADDRESS" 5000
# with an explicit owner address:            delegatestake "S_STAKING_ADDRESS" 5000 "A_OWNER_ADDRESS"
# owner address not in this wallet (offline): add ext_owner=true
ammocoin-cli delegatestake "S_STAKING_ADDRESS" 5000 "A_OFFLINE_OWNER_ADDRESS" true
```

Check:
```bash
ammocoin-cli getcoldstakingbalance   # staking server: coins delegated to it
ammocoin-cli getdelegatedbalance     # owner wallet: coins it has delegated
ammocoin-cli listcoldutxos           # staking server
ammocoin-cli getstakingstatus        # staking server
```

Regular (hot) staking: hold AMMO in an online wallet, unlock for staking only with `ammocoin-cli walletpassphrase "YOUR_PASSPHRASE" 0 true`, and check `getstakingstatus` (`staking_status: true`).

---

## Sapling Parameters

v1.1.1 needs the two Sapling zk-SNARK parameter files (about 50 MB). Without them the node stops at startup with `Cannot find the Sapling parameters`.

| File | SHA256 |
|---|---|
| `sapling-spend.params` | `8e48ffd23abb3a5fd9c5589204f32d9c31285a04b78096ba40a79b75677efc13` |
| `sapling-output.params` | `2f0ebbcbb9bb0bcffe95a397e7eba89c29eb4dde6191c339db88570e3f3fb0e4` |

Where they come from in each package:

- **Windows Setup.exe**, **macOS AMMOcoin-Qt.app**, **Linux AppImage** and **.deb**: bundled; nothing to do. The .deb installs them to `/usr/share/ammocoin`.
- **Linux tarballs**: run `bin/ammocoin-fetch-params` (or `install-desktop.sh` for the Qt tarball).
- **Windows zip**: run `install-params.bat` once.
- **macOS command-line `ammocoind`**: run `./fetch-params.sh` once.

All fetch helpers download from `https://download.z.cash/downloads/` and check the SHA256 values above. Parameter folders: Linux `~/.ammocoin-params`, macOS `~/Library/Application Support/AMMOcoinParams`, Windows `%APPDATA%\AMMOcoinParams`.

Sapling shielding is optional. AMMO transactions are transparent by default; the shield and unshield sides of a shielded transfer are visible, and peers see your IP address.

---

## Downloads (platform builds)

All packages are built by GitHub Actions from the tagged source and listed in `AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt` on the release page.

| Platform | Files | Notes |
|---|---|---|
| Linux x86_64 (daemon) | `AMMOcoin-v1.1.1-Linux-x86_64.tar.gz`, `.zip`, `AMMOcoin-v1.1.1-Linux-amd64.deb` | `ammocoind`, `ammocoin-cli`, `ammocoin-tx`. The .deb installs an `ammocoind` systemd service running as user `ammocoin` |
| Linux ARM64 (daemon) | `AMMOcoin-v1.1.1-Linux-ARM64.tar.gz`, `.zip`, `AMMOcoin-v1.1.1-Linux-arm64.deb` | Raspberry Pi 4/5 with a 64-bit OS, ARM64 servers |
| Linux x86_64 (Qt wallet) | `AMMOcoin-v1.1.1-Linux-x86_64-Qt.tar.gz`, `AMMOcoin-v1.1.1-Linux-x86_64-Qt.AppImage` | AppImage needs no setup and includes the Sapling parameters |
| Linux ARM64 (Qt wallet) | `AMMOcoin-v1.1.1-Linux-ARM64-Qt.tar.gz`, `AMMOcoin-v1.1.1-Linux-ARM64-Qt.AppImage` | as above |
| Windows x86_64 | `AMMOcoin-v1.1.1-Windows-x86_64-Setup.exe`, `.zip`, `.tar.gz` | Setup.exe installs the wallet, Start-menu shortcuts, an uninstaller and the Sapling parameters |
| macOS Apple Silicon | `AMMOcoin-v1.1.1-macOS-ARM64.dmg`, `.tar.gz`, `.zip`, `.SHA256` | Developer ID signed (hardened runtime) and notarized by Apple; **macOS 13 or newer** |
| macOS Intel | `AMMOcoin-v1.1.1-macOS-x86_64.dmg`, `.tar.gz`, `.zip`, `.SHA256` | Signed and notarized; macOS 13 or newer. Also runs on Apple Silicon under Rosetta 2, more slowly |

Per-platform `…-CHECKSUM.txt` files (Linux, Windows) and `….SHA256` files (macOS) are attached next to the packages.

Linux requirements: glibc 2.34 or newer (Ubuntu 22.04+, Debian 12+, Fedora 35+, Raspberry Pi OS bookworm 64-bit). The Qt wallet also needs an X11 or Wayland (XWayland) desktop with libxcb, fontconfig and freetype. Check glibc with `getconf GNU_LIBC_VERSION`.

Build and packaging changes in this release: from-source macOS dependencies targeting macOS 13.0 with an `otool` check that no binary needs a newer macOS (`7cd50d1f9`), Developer ID signing and notarization (`569e23d08`, `02cf87334`), the qsvg image plugin bundled in the app (`66c251d0a`), Linux Qt wallet tarball and AppImage for x86_64 and ARM64 (`a77794aa9`, `6f2d64acf`), a working and tested .deb plus Linux and Windows archives (`406692f85`, `51a26f16d`), NSIS Start-menu fix (`13c867b74`), libevent built for glibc 2.36+ (`1033c92a3`), clean `v1.1.1` version strings with no `-dirty` suffix (`7ed89aacb`, `336002a05`, `ee338296a`), regtest smoke tests of the daemon and GUI on Linux and macOS (`b38e15be9`), and the combined checksums file with a cross-check of the per-platform checksum files (`2b8a2461c`, `f9343b63f`).

### Verify before you install

1. Download the package, `AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt` and, when present, `AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt.sig` from the **same** release.
2. If the `.sig` is published, verify it with `scripts/release/verify-release.sh` from this repository at the `v1.1.1` tag ([SIGNING.md](../release/SIGNING.md)).
3. Check the file: `sha256sum -c AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt --ignore-missing` (macOS: `shasum -a 256 -c --ignore-missing AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt`).

If either check fails, do not run the file.

---

## One-Command Node Installer (`install-node.sh`)

`scripts/deployment/install-node.sh` sets up a v1.1.1 node on Ubuntu 22.04+ / Debian 12+ (`17c3efbcf`, `fad0f623b`, `eff92db63`):

```bash
sudo ./install-node.sh --tarball <file-or-url> --sha256 <hex from the release page> \
     [--role node|coldstaker|masternode] [--mnkey <masternode key>] [--ip <public IPv4>] [--dry-run]
```

- Refuses to run without a SHA256 and stops on a checksum mismatch.
- Checks glibc 2.34+ (via `getconf`) before installing.
- Installs to `/opt/ammocoin-<version>` and creates a dedicated `ammocoin` user (home `/var/lib/ammocoin`, data `/var/lib/ammocoin/.ammocoin11`).
- Fetches and verifies the Sapling parameters.
- Writes `ammocoin.conf` for the chosen role (RPC bound to 127.0.0.1 with a random password; an existing config is kept).
- Installs and starts the `ammocoind` systemd service and opens TCP 37020 in `ufw` when ufw is active.
- Roles: `node` (default; stakes coins sent to its own wallet), `coldstaker` (stakes coins delegated from an offline wallet; prints the `getnewstakingaddress` / `delegatestake` / `delegatoradd` steps), `masternode` (needs `--mnkey` from `createmasternodekey` and a public IPv4; the collateral stays in your controller wallet).
- `--dry-run` prints every command without changing the system.

---

## New Data Folder

v1.1.1 uses a new default data directory so it never mixes with v1.0 or v1.1.0 data:

| OS | v1.1.1 data folder | Old folder (v1.0 / v1.1.0) |
|---|---|---|
| Linux | `~/.ammocoin11` | `~/.ammocoin` |
| macOS | `~/Library/Application Support/AMMOcoin11` | `~/Library/Application Support/AMMOcoin` |
| Windows | `%APPDATA%\AMMOcoin11` | `%APPDATA%\AMMOcoin` |

The pre-release lab network (`a3 4d b1 e7`, `~/.ammocoincore` / `AMMOcoinCore`) is a separate test network. v1.1.1 does not connect to it or read its folders. The Qt wallet also keeps its settings under a new name (`AMMOcoin11-Qt`), so it never reopens an older wallet's folder. Details: `docs/MAINNET_SEPARATION.md`.

---

## Upgrading and Migrating

### From v1.1.0

1. Stop the old node: `ammocoin-cli stop`
2. Back up your v1.1.0 `wallet.dat` (and your v1.0 `wallet.dat` if you still have one; keep both).
3. Install v1.1.1 from the official release and verify the checksum.
4. Create the new data folder and copy over only `ammocoin.conf`, `masternode.conf` (masternodes) and `wallet.dat`.
5. Check `ammocoin.conf` uses `port=37020` / `rpcport=51473`; remove any `addnode=147.182.245.102` and any port 37019.
6. Start v1.1.1 and let it sync from the seeds. Do **not** copy `blocks/` or `chainstate/` from v1.1.0.
7. `ammocoin-cli getblockcount` should go past 2,775.
8. Stakers: unlock for staking and check `getstakingstatus`. Masternodes: restart from the controller (`startmasternode alias false <alias>`).

To keep using the old location, start with `-datadir=<old folder>`; a fresh folder is recommended.

### systemd units you wrote yourself

The service must set `HOME`, otherwise the node exits with `Cannot find the Sapling parameters`:

```ini
[Service]
Type=simple
User=root
Environment=HOME=/root
ExecStart=/opt/ammocoin-v1.1.1/bin/ammocoind -datadir=/root/.ammocoin11 -daemon=0
ExecStop=/opt/ammocoin-v1.1.1/bin/ammocoin-cli -datadir=/root/.ammocoin11 stop
Restart=on-failure
TimeoutStopSec=120
```

If the service runs as another user, set `User=` and `Environment=HOME=` to that user. The .deb and `install-node.sh` already do this.

### From v1.0: balance airdrop

v1.0 balances from the snapshot at **v1.0 block 434,881** are airdropped to the **same addresses** on v1.1.

- **Keep your v1.0 `wallet.dat`.** The same keys control the airdropped balance. Copy a backup into the v1.1.1 data folder before first start, or import the keys with `importprivkey`.
- **Send nothing anywhere.** There is no disposal address, no registration and no fee. Anyone who asks you to send coins, keys or wallet files is attempting a scam.
- If an address was missed, a **signed-message claim** (`signmessage` with the v1.0 address) is the fallback.
- **No deadline.**

Details: [v1.0 Balance Airdrop](../migration/V1.0_BALANCE_AIRDROP.md). The earlier disposal-address / email process is **withdrawn**.

### Block 1 reserve

The 250,000,000 AMMO block-1 reserve is paid to `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u`. The airdrop is paid from it first. `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME` is only the unspendable genesis output.

### Upgrade checklist

- [ ] Back up every `wallet.dat` (v1.0 and v1.1.0) to offline storage
- [ ] Linux: confirm glibc 2.34+ (`getconf GNU_LIBC_VERSION`); upgrade from Ubuntu 18.04/20.04 first
- [ ] Stop the old node
- [ ] Install v1.1.1 from the official GitHub release and verify the checksum
- [ ] Move `ammocoin.conf`, `masternode.conf`, `wallet.dat` into the new data folder
- [ ] Ports 37020 / 51473; remove 147.182.245.102 and 37019 from configs
- [ ] Your own systemd units: add `Environment=HOME=...`
- [ ] Start, sync, `getblockcount` past 2,775
- [ ] Re-unlock for staking / restart masternodes from the controller

---

## Known Issues

- **Ubuntu 18.04 and 20.04 cannot run the release binaries** (glibc 2.34+ needed). Upgrade the OS or use a fresh Ubuntu 22.04/24.04 VPS. `install-node.sh` stops with a clear error on these systems.
- **Stake maturity is 600 confirmations** (about 30 hours). Newly received or newly delegated coins do not stake before that.
- **Cold staking needs `delegatoradd`** on the staking server. Without it the server does not stake the delegated coins.
- **Port 37020 conflict:** if the .deb's `ammocoind` service runs on a desktop, the Qt wallet on the same machine cannot bind 37020. Stop it first: `sudo systemctl disable --now ammocoind`.
- **Missing Sapling parameters** stop startup with `Cannot find the Sapling parameters`. Use the fetch helper for your package (see above); custom systemd units must set `HOME`.
- **macOS:** the ARM64 package does not run on Intel Macs; the x86_64 package runs on Apple Silicon only under Rosetta 2. macOS 12 and older are not supported. A macOS build made without the signing secrets is ad-hoc signed and blocked by Gatekeeper; such builds are never published as the release.
- **Masternodes behind NAT or on private IPs** are rejected (`Invalid IP address`). A public IPv4 is required.
- **Old documents and the v1.1.0 white papers** list wrong ports (37019 / 51474), the dead seed 147.182.245.102 and withdrawn claims. They are marked superseded; the 2nd Edition white paper and these notes follow the code.
- There is no `masternode genkey` command (use `createmasternodekey`) and no `createwallet` command.

---

## Documentation

- [Wallet setup](../01-wallet-setup.md), [Staking](../02-staking-guide.md), [Masternodes](../03-masternode-setup.md), [Node setup](../04-node-setup.md), [CLI reference](../05-terminal-commands.md), [DAO](../06-dao-participation.md), [Security](../08-security-guide.md), [Troubleshooting](../09-troubleshooting.md), [FAQ](../10-faq.md)
- [White paper, 2nd Edition (v1.1.1)](../whitepapers/AMMOcoin_Whitepaper_2ndEdition_v1.1.1.md)
- [Release signing](../release/SIGNING.md) and [release checklist](../RELEASE_CHECKLIST_1.1.1.md)

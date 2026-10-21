# v1.1.1 Mainnet Separation

v1.1.1 mainnet has its own network identity, so it can never peer with or share data with older AMMOcoin networks.

## What changed

| | v1.0 / v1.1.0 | v1.1.1 lab network (pre-release test fleet) | v1.1.1 mainnet (this release) |
|---|---|---|---|
| Message-start ("magic") bytes | `76 63 7a f3` | `a3 4d b1 e7` | **`c7 9a e3 b5`** |
| Linux data folder | `~/.ammocoin` | `~/.ammocoincore` | **`~/.ammocoin11`** |
| macOS data folder | `~/Library/Application Support/AMMOcoin` | `~/Library/Application Support/AMMOcoinCore` | **`~/Library/Application Support/AMMOcoin11`** |
| Windows data folder | `%APPDATA%\AMMOcoin` | `%APPDATA%\AMMOcoinCore` | **`%APPDATA%\AMMOcoin11`** |
| Qt settings (org / app) | `AMMOcoin` / `AMMOcoin-Qt` | `AMMOcoinCore` / `AMMOcoin-Qt` | **`AMMOcoin11` / `AMMOcoin11-Qt`** |

These are the same in every column:

- P2P port **37020**, RPC port **51473**
- Genesis block, consensus parameters, DNS and fixed seeds
- Config file name `ammocoin.conf`
- Sapling parameters folder (`~/.ammocoin-params`, `AMMOcoinParams`). Every version can share these files, and their location does not depend on the data folder.

Testnet and regtest magic are unchanged.

## Why

v1.0 and v1.1.1 used the same port, and older builds also shared the magic bytes and data folder. That allowed:

- **Accidental peering.** A node with the old magic could handshake with a v1.1.1 node and swap addresses and block headers from a different chain, filling `peers.dat` with nodes from the wrong network.
- **Data mixing.** Opening a v1.0 data folder with v1.1.1, or the reverse, puts block files, chainstate and `peers.dat` from two different chains in one folder.
- **Shared GUI settings.** The Qt wallet saves the chosen data folder (`strDataDir`) in QSettings. If the settings namespace is shared, a new GUI quietly reopens the old folder. On macOS the settings file is keyed by domain plus app name (`org.ammocoin.AMMOcoin-Qt`), so the lab build's change to the org name alone did not separate the settings there. The app name is now `AMMOcoin11-Qt` as well.

New magic bytes make the networks reject each other at the first message. The new folders and settings namespace keep each chain's data on disk apart. The new bytes all have the high bit set, so they are not printable ASCII. They also differ from every AMMOcoin and PIVX value (PIVX main/test/regtest: `90 c4 fd e9` / `f5 e6 d5 ca` / `a1 cf 7e ac`).

## Migration for users

- **Your balance is airdropped to the same addresses on v1.1.** You need the private keys for your v1.0 addresses. You do not need any v1.0 chain data.
- **v1.1.1 starts with a new, empty data folder.** It does not read or change the old v1.0 folder. Keep the old folder, or at least its `wallet.dat`, as a backup.
- **To use an existing wallet:**
  1. Stop every running wallet or node.
  2. Copy `wallet.dat` from the old folder into the new folder. Copy `ammocoin.conf` and `masternode.conf` too, if you use them. Do **not** copy `blocks/`, `chainstate/`, `peers.dat` or `banlist.dat`.
  3. Start v1.1.1. It syncs the v1.1 chain from scratch and rescans the wallet.
- **Or import keys only:** on v1.0, run `dumpprivkey <address>` (or `dumpwallet <file>`). On v1.1.1, run `importprivkey <key>` (or `importwallet <file>`). Do this on a machine you trust, and delete any dump file afterwards.
- If you set `-datadir` or `datadir=` yourself, nothing changes for you. Point it at a folder that only v1.1.1 uses.

## Lab network (pre-release test fleet)

The test fleet running now uses the lab values (`a3 4d b1 e7`, `.ammocoincore`). It is **not compatible** with this branch. A node built from this branch will not connect to it, and it ignores the lab data folders. To move a lab node to the new network, install a build from this branch with a new data folder (`~/.ammocoin11`). You can copy its `wallet.dat` over if you want to keep the keys.

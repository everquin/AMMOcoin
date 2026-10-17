AMMOcoin Core v1.1.1 for macOS - @ARCH@
=====================================

Requirements: a Mac with an @ARCHDESC@ CPU running macOS @MINOS@ or newer.
Use AMMOcoin-v1.1.1-macOS-ARM64 on Apple Silicon and -x86_64 on Intel Macs.
(The ARM64 package does not run on Intel Macs; the x86_64 package also runs
on Apple Silicon under Rosetta 2, but more slowly.)

Contents
--------
  AMMOcoin-Qt.app        Graphical wallet (DMG only). Drag it to /Applications.
  bin/ammocoind          Full node / wallet daemon
  bin/ammocoin-cli       RPC command-line client
  bin/ammocoin-tx        Raw transaction utility
  fetch-params.sh        Downloads + verifies the Sapling parameters
  README.txt             This file

@FIRST_LAUNCH@

Sapling parameters
------------------
AMMOcoin needs two zk-SNARK parameter files (about 50 MB):

  ~/Library/Application Support/AMMOcoinParams/sapling-spend.params
  ~/Library/Application Support/AMMOcoinParams/sapling-output.params

* AMMOcoin-Qt.app already contains both files and uses them automatically
  when the folder above is missing. Nothing to do.
* The command-line ammocoind needs them in the folder above. Run once:

      ./fetch-params.sh

  It downloads from https://download.z.cash/downloads/ and checks SHA256:
    sapling-spend.params  8e48ffd23abb3a5fd9c5589204f32d9c31285a04b78096ba40a79b75677efc13
    sapling-output.params 2f0ebbcbb9bb0bcffe95a397e7eba89c29eb4dde6191c339db88570e3f3fb0e4
  Files that are already present and correct are left untouched.

Data directory
--------------
  ~/Library/Application Support/AMMOcoinCore/
  (wallet.dat, ammocoin.conf, blocks, debug.log). Back up wallet.dat.
  v1.1.1 uses this NEW folder; it does not read the old v1.0/v1.1.0 folder
  ~/Library/Application Support/AMMOcoin/. To keep using an existing wallet,
  stop the old wallet and copy its wallet.dat into AMMOcoinCore first.

Command-line quick start
------------------------
  ./bin/ammocoind -daemon
  ./bin/ammocoin-cli getblockchaininfo
  ./bin/ammocoin-cli getwalletinfo
  ./bin/ammocoin-cli stop

Network: mainnet P2P port 37020, RPC port 51473. v1.1.1 is the mandatory
Proof-of-Stake hard fork (PoS from block 2,776); v1.1.0 nodes cannot follow
the chain.

Verify the download
-------------------
  shasum -a 256 -c AMMOcoin-v1.1.1-macOS-ARM64.SHA256

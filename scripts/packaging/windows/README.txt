AMMOcoin v1.1.1 for Windows (64-bit)
====================================

v1.1.1 is the Proof-of-Stake hard fork release. Wallets older than v1.1.1 are on a dead chain.

Easiest: use AMMOcoin-v1.1.1-Windows-x86_64-Setup.exe from the same release. It installs the
wallet, Start-menu shortcuts, an uninstaller, and the Sapling parameters.

Using this zip instead
----------------------
  1. Unpack the zip anywhere (for example C:\AMMOcoin).
  2. Double-click install-params.bat once. It downloads (~50 MB) and SHA-256 verifies the Sapling
     parameters into %APPDATA%\AMMOcoinParams. Without them the wallet stops at startup with
     "Cannot find the Sapling parameters".
     Offline? Copy sapling-spend.params and sapling-output.params (from the Setup.exe install,
     another PC's %APPDATA%\AMMOcoinParams, or https://download.z.cash/downloads/) into
     %APPDATA%\AMMOcoinParams yourself.
  3. Start bin\ammocoin-qt.exe (GUI wallet), or bin\ammocoind.exe + bin\ammocoin-cli.exe.

Wallet and blockchain data: %APPDATA%\AMMOcoinCore (back up wallet.dat).
Ports: P2P 37020, RPC 51473 (localhost only).
Guides: https://github.com/everquin/AMMOcoin/tree/main/docs

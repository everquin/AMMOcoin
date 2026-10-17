AMMOcoin v1.1.1 wallet (GUI) for Linux (@ARCH@)
===============================================

v1.1.1 is the Proof-of-Stake hard fork release. Wallets older than v1.1.1 are on a dead chain.

Requirements
------------
  glibc 2.34 or newer (Ubuntu 22.04+, Debian 12+, Fedora 35+, Raspberry Pi OS bookworm 64-bit)
  and a normal X11 or Wayland (XWayland) desktop. Check glibc with: getconf GNU_LIBC_VERSION
  Qt is built in; the only system libraries used are glibc, libxcb, fontconfig and freetype,
  which every desktop has. On a minimal system: sudo apt install libxcb1 libfontconfig1 libfreetype6
  (plus the libxcb-* packages `ldd bin/ammocoin-qt` reports as "not found", if any).

Contents
--------
  bin/ammocoin-qt              the wallet
  bin/ammocoin-fetch-params    downloads + SHA-256 verifies the Sapling parameters
  install-desktop.sh           fetches the parameters and adds the wallet to your app menu
  share/applications/ammocoin-qt.desktop, share/icons/.../ammocoin.png
  README.txt                   this file

Start
-----
  ./install-desktop.sh         # once: parameters (~50 MB download) + menu entry
  ./bin/ammocoin-qt            # or start "AMMOcoin Wallet" from the menu

Without the Sapling parameters the wallet stops at startup with "Cannot find the Sapling
parameters". ./bin/ammocoin-fetch-params puts them in ~/.ammocoin-params; if you installed the
AMMOcoin .deb they are already in /usr/share/ammocoin and are found automatically.

Easier: the AMMOcoin-v1.1.1-Linux-@ARCH@-Qt.AppImage from the same release needs no setup
(chmod +x it and run it; it includes the parameters).

Data: wallet and blockchain in ~/.ammocoincore (back up wallet.dat). Ports: P2P 37020, RPC 51473.
If the AMMOcoin .deb's background node (ammocoind service) is running on this machine, stop it
first (sudo systemctl disable --now ammocoind) or the wallet cannot use port 37020.
Guides: https://github.com/everquin/AMMOcoin/tree/main/docs

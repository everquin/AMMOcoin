AMMOcoin v1.1.1 for Linux (@ARCH@)
===================================

v1.1.1 is the Proof-of-Stake hard fork release. Nodes older than v1.1.1 are on a dead chain.

Requirements
------------
  glibc 2.34 or newer: Ubuntu 22.04+, Debian 12+, Fedora 35+, Raspberry Pi OS 12 (bookworm, 64-bit)+.
  Check with:  getconf GNU_LIBC_VERSION
  Ubuntu 18.04/20.04 and Debian 11 are too old: the binaries fail with "GLIBC_2.34 not found".
  Everything else (Boost, OpenSSL, BerkeleyDB, libstdc++ ...) is linked statically.

Contents
--------
  bin/ammocoind               the node (headless; this archive has no GUI wallet)
  bin/ammocoin-cli            RPC client
  bin/ammocoin-tx             offline transaction tool
  bin/ammocoin-fetch-params   downloads + SHA-256 verifies the Sapling parameters
  install-node.sh             one-command server install (systemd service, dedicated user)
  README.txt                  this file

1. Run a server node (recommended for VPS / always-on machines)
---------------------------------------------------------------
  sudo ./install-node.sh --tarball AMMOcoin-v1.1.1-Linux-@ARCH@.tar.gz --sha256 <sha256 from the release page>
      [--role node|coldstaker|masternode] [--mnkey <key>] [--ip <public IPv4>]

It creates the "ammocoin" user (HOME /var/lib/ammocoin), fetches and verifies the Sapling
parameters, writes /var/lib/ammocoin/.ammocoincore/ammocoin.conf (random RPC password),
installs the ammocoind systemd service and opens P2P port 37020. Run ./install-node.sh --help.
On Debian/Ubuntu you can instead install the .deb from the same release (apt install ./AMMOcoin-v1.1.1-Linux-*.deb).

2. Run it as your own user
--------------------------
  ./bin/ammocoin-fetch-params          # once: puts the params in ~/.ammocoin-params (~50 MB download)
  ./bin/ammocoind -daemon              # data folder: ~/.ammocoincore
  ./bin/ammocoin-cli getblockcount
  ./bin/ammocoin-cli stop

Without the parameters the node stops at startup with
"Cannot find the Sapling parameters in the following directory". Offline machines: copy
sapling-spend.params and sapling-output.params (from https://download.z.cash/downloads/ or the
.deb's /usr/share/ammocoin) into ~/.ammocoin-params; ammocoin-fetch-params --check verifies them.

Ports: P2P 37020 (open it for inbound peers), RPC 51473 (keep it on localhost).
Guides: https://github.com/everquin/AMMOcoin/tree/main/docs

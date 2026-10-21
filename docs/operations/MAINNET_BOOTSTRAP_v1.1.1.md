# Bootstrapping v1.1.1 mainnet with blocks 1-2,775

v1.1.1 uses new network magic (`c7 9a e3 b5`), so it cannot download the existing v1.1 chain (blocks 1-2,775, mined under v1.1.0) from v1.1.0 nodes. Block files on disk also start every block with the old magic (`76 63 7a f3`), so `-loadblock` on an old `blk00000.dat` finds nothing.

The first v1.1.1 nodes therefore import a converted copy of seed1's block file. After that, every other v1.1.1 node syncs from them over P2P as usual.

## Make the bootstrap file

```bash
# on any machine with seed1's v1.1.0 blocks/blk00000.dat (chain data only, no wallet)
python3 scripts/migration/v110-blocks-to-v111-bootstrap.py blk00000.dat bootstrap-v111.dat
# -> 2787 blocks, 500808 bytes, sha256 4a6067f50d5310ab1fe30143aec08f08683e20677c97dcb2b0680196ffcc2d7d
```

The file holds 2,787 block records: the 2,776 blocks of the chain (genesis to 2,775) plus 11 stale blocks above 2,775. v1.1.1 rejects those because they are Proof-of-Work blocks after the fork (`CheckWork : incorrect proof of work ... at 2776`). That rejection is expected.

## Import

```bash
sudo -u ammocoin HOME=/var/lib/ammocoin /opt/ammocoin-v1.1.1/bin/ammocoind \
  -datadir=/var/lib/ammocoin/.ammocoin11 -daemon -connect=0 -listen=0 \
  -loadblock=/var/lib/ammocoin/bootstrap-v111.dat
ammocoin-cli getblockcount      # 2775
ammocoin-cli getbestblockhash   # 000000669cf82a6a3c44eb01f6db927f933d2e5e1284b6cf6d7967b2f567ecc8
ammocoin-cli stop
```

`-connect=0 -listen=0` keeps the node offline during the import. Start it normally afterwards. The node does not need the file again.

## Status (2026-10-21)

Tested with the v1.1.1-rc build (`v1.1.1.0-bfb41ea`). Imported and verified at 2,775 / `000000669cf8…` on the new seeds ammo-02 (Dallas), ammo-03 (New York) and ammo-08 (Sydney), and on the explorer node ammo-05. All four are stopped until the fleet switch. seed1 and seed2 import the same file when they move to v1.1.1.

# AMMOcoin v1.0 to v1.1.0 User Migration Guide

**Network Launch:** January 3, 2026
**Migration Deadline:** April 3, 2026 (90 days)
**Migration Method:** On-chain transfer via disposal wallet

---

## Overview

AMMOcoin v1.1.0 is a **completely new blockchain** — it is NOT an upgrade of v1.0. The two networks are separate and incompatible.

A **250,000,000 AMMO distribution fund** in the v1.1.0 genesis block covers all v1.0 balances. To receive your coins on v1.1.0, you transfer your v1.0 AMMO to a team-controlled **disposal wallet** on the v1.0 chain. Once the team confirms your transfer on-chain, the equivalent amount is sent to your v1.1.0 address(es) from the distribution fund.

This creates **immutable proof on both blockchains** — your v1.0 send transaction and the matching v1.1.0 distribution transaction form a permanent, auditable record of the migration.

**What v1.1.0 brings:**
- Modern PIVX 5.x codebase
- Sapling privacy (zkSNARK shielded transactions)
- Improved performance and security
- Pre-built binaries for all platforms (macOS, Windows, Linux x86_64, ARM64)

---

## How Migration Works

```
v1.0 Chain                              v1.1.0 Chain
──────────                              ────────────
Your v1.0 wallet                        250M AMMO distribution fund
      │                                        │
      ▼                                        ▼
Send AMMO to ──► Disposal Wallet    Team sends ──► Your v1.1.0 address(es)
(on-chain tx)    (team-controlled)  (on-chain tx)  (you specify how to split)
```

Both transactions are recorded on their respective blockchains — immutable and independently verifiable.

---

## Before You Start

### Back Up Your v1.0 Wallet

**Without your v1.0 wallet.dat, you cannot send your coins to the disposal wallet.**

```bash
# Stop v1.0 daemon
ammocoin-cli stop

# Create backup
cp ~/.ammocoin/wallet.dat ~/ammocoin-v1.0-wallet-backup-$(date +%Y%m%d).dat

# Verify backup exists
ls -lh ~/ammocoin-v1.0-wallet-backup-*.dat
```

Store copies in multiple safe locations (USB drive, encrypted cloud storage, etc.).

---

## Step 1: Download and Install v1.1.0

Pre-built binaries are available for all platforms. Download from the [GitHub Release page](https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0) or the [AMMOcoin Downloads page](https://www.ammocoin.org/downloads.html).

### macOS (Apple Silicon)

Download and open the `.dmg` installer:
```
AMMOcoin-v1.1.0-macOS-ARM64.dmg
SHA256: 08dfb0be819eba85c3238f916e7c2464d1333f97a71a4c1caa0d9ebcea6fd7b6
```
Drag AMMOcoin to your Applications folder.

Or use the `.tar.gz` for CLI-only:
```bash
curl -LO https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
shasum -a 256 AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
# Expected: f314ff670ad1088cc64516be4b2f7667974f9937a3c2e1683844e5500cb709dd
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
sudo cp AMMOcoin-v1.1.0-macOS-ARM64/ammocoind AMMOcoin-v1.1.0-macOS-ARM64/ammocoin-cli /usr/local/bin/
```

### Windows

Download and run the installer:
```
AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe
SHA256: 82f7a652b0c388e69f1a03be8eff11a514195c02f5f91357cf588f7a698a31c8
```
The NSIS installer includes the Qt wallet, daemon, CLI tools, Sapling parameters, and Start Menu shortcuts.

### Linux x86_64

**Option A: .deb package (Ubuntu/Debian — recommended)**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-amd64.deb
sha256sum AMMOcoin-v1.1.0-Linux-amd64.deb
# Expected: ae32a07effe874cf925e9e7c8dc604189f38113c54264ac47564a4e88fb53259
sudo dpkg -i AMMOcoin-v1.1.0-Linux-amd64.deb
```

**Option B: .tar.gz**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
# Expected: 41111899895744cf945079c544766199cc9e30398d2e239d76adf742a37f0b40
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx
```

### Linux ARM64 (Raspberry Pi 4/5)

**Option A: .deb package**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-arm64.deb
sha256sum AMMOcoin-v1.1.0-Linux-arm64.deb
# Expected: d4ded3c4d368ce1fe7f40d998c924a61419c481242e7420fcdf2ac7925b073f3
sudo dpkg -i AMMOcoin-v1.1.0-Linux-arm64.deb
```

**Option B: .tar.gz**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
sha256sum AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
# Expected: 42678ae20253b9acaa35732835a2a2a0ee552bb9a6b809ee683b5377d3f45014
tar -xzf AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx
```

### All Checksums

See [AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt) for a complete list.

### Start the v1.1.0 Node

```bash
# Start daemon
ammocoind -daemon

# Wait for startup, then verify correct genesis block
ammocoin-cli getblockhash 0
# Must return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

---

## Step 2: Generate v1.1.0 Receiving Address(es)

Create one or more addresses in your v1.1.0 wallet where your migrated coins will be sent:

```bash
ammocoin-cli getnewaddress "Migration"
# Example output: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n
```

You can create multiple addresses if you want your balance split across them (e.g., a staking address and a masternode collateral address).

Back up your v1.1.0 wallet after generating addresses:
```bash
ammocoin-cli backupwallet ~/ammocoin-v1.1.0-wallet-backup.dat
```

---

## Step 3: Email the Team

Email **transfermy@ammocoin.org** with the subject line: **v1.0 Transfer Request**

Include:
1. **Amount you will send** from your v1.0 wallet
2. **v1.1.0 receiving address(es)** and how to distribute the amount between them

**Example — single address:**
```
I will be sending 50,000 AMMO from my v1.0 wallet to the disposal address.

Please send the full amount to:
  Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n — 50,000 AMMO
```

**Example — multiple addresses:**
```
I will be sending 60,000 AMMO from my v1.0 wallet to the disposal address.

Please distribute as follows:
  Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n — 40,000 AMMO (staking)
  Ah2mX9cL4sD1eW6hK9jB2nRvT3xYz7kQ2 — 10,000 AMMO (masternode collateral)
  Aj4pR8dN5tF2gH7iK3lM6oQ9sU1wX0yZ8 — 10,000 AMMO (savings)
```

The team will reply with the **v1.0 disposal wallet address** to send your coins to.

---

## Step 4: Send v1.0 AMMO to Disposal Wallet

Once you receive the disposal wallet address from the team, send your v1.0 AMMO:

```bash
# Using v1.0 CLI
ammocoin-cli sendtoaddress "DISPOSAL_WALLET_ADDRESS" 50000

# Or send your entire balance
BALANCE=$(ammocoin-cli getbalance)
ammocoin-cli sendtoaddress "DISPOSAL_WALLET_ADDRESS" $BALANCE "" "" true
# The 'true' at the end subtracts the fee from the amount sent
```

**Save the transaction ID (txid)** — this is your on-chain proof of transfer:
```bash
# View your most recent transaction
ammocoin-cli listtransactions "*" 1
```

You can send in multiple transactions if you prefer. Each transfer will be matched with an equivalent v1.1.0 distribution.

---

## Step 5: Receive Your v1.1.0 AMMO

Once the team confirms your v1.0 transfer on-chain, they will send the equivalent amount to your specified v1.1.0 address(es). This typically takes **24-48 hours**.

```bash
# Check your v1.1.0 balance
ammocoin-cli getbalance

# View recent transactions
ammocoin-cli listtransactions "*" 10
```

The team will email you confirmation with the v1.1.0 transaction ID(s) for your records.

---

## Masternode Operators

If you ran a masternode on v1.0, you must set up a **fresh masternode on v1.1.0** after transferring your collateral:

1. **Transfer your v1.0 balance** (follow Steps 1-5 above)
   - In your email, specify at least 10,000 AMMO to a dedicated masternode collateral address
2. **Set up a new VPS** running v1.1.0 (or upgrade your existing VPS)
3. **Configure the masternode** following the standard v1.1.0 masternode setup process
4. **Lock collateral** (10,000 AMMO) in your v1.1.0 wallet
5. **Start the masternode**

Your v1.0 masternode configuration does not carry over. Contact transfermy@ammocoin.org if you need help with masternode setup.

---

## Verification Checklist

After completing migration:

- [ ] v1.1.0 node running and synced (`ammocoin-cli getblockchaininfo`)
- [ ] v1.1.0 balance received matches the amount you sent on v1.0 (`ammocoin-cli getbalance`)
- [ ] You have the v1.0 txid (proof of disposal transfer) saved
- [ ] You have the v1.1.0 txid (proof of distribution) saved
- [ ] Can send a small test transaction on v1.1.0
- [ ] Wallet encrypted (`ammocoin-cli encryptwallet "passphrase"` if not already)
- [ ] v1.1.0 wallet backed up
- [ ] v1.0 wallet backup stored safely (keep it!)

---

## Troubleshooting

### "Transaction not confirming on v1.0"

Ensure your v1.0 node is synced and has peers:
```bash
ammocoin-cli getinfo
ammocoin-cli getpeerinfo
```

If no peers, add seed nodes to your v1.0 config.

### "I sent the wrong amount"

No problem. You can send additional transfers to the disposal wallet at any time. Email transfermy@ammocoin.org to update your distribution instructions.

### "I want to change my v1.1.0 receiving addresses"

Email transfermy@ammocoin.org before the team processes your transfer. Once the v1.1.0 distribution is sent, it cannot be reversed.

### "Cannot connect to v1.1.0 daemon"

Ensure v1.1.0 is running:
```bash
ammocoind -daemon
sleep 5
ammocoin-cli getinfo
```

### Node not syncing / no peers

Add seed nodes to your config file (`~/.ammocoin/ammocoin.conf`):
```
addnode=seed1.ammocoin.org:37020
addnode=seed2.ammocoin.org:37020
```

---

## FAQ

**Q: Can I send my v1.0 AMMO in multiple transactions?**
A: Yes. Send as many transfers as you like to the disposal wallet. Each will be matched with an equivalent v1.1.0 distribution. Just email transfermy@ammocoin.org with updated instructions for each transfer.

**Q: Can I split my balance across multiple v1.1.0 addresses?**
A: Yes. In your email, specify each v1.1.0 address and the amount to send to each. For example, you could put 10,000 AMMO toward masternode collateral and the rest into a staking address.

**Q: What if I miss the deadline?**
A: The migration period closes April 3, 2026. After that, unclaimed funds return to the community treasury. Contact transfermy@ammocoin.org if you need an extension.

**Q: What if I'm running a masternode?**
A: You must set up a fresh masternode on v1.1.0 after transferring your collateral. See the Masternode Operators section above.

**Q: Do I need to re-download the entire blockchain?**
A: Yes, v1.1.0 is a new blockchain starting from a new genesis block.

**Q: What happens to my v1.0 coins after I send them to the disposal wallet?**
A: They remain in the disposal wallet permanently on the v1.0 chain as an immutable record of your migration. The v1.0 network will eventually be shut down.

**Q: What happens to transaction history?**
A: v1.0 transaction history does not carry over. The v1.1.0 blockchain starts fresh.

**Q: Is there a minimum transfer amount?**
A: No. You can transfer any amount.

---

## Security Best Practices

1. **Never share your private keys** with anyone
2. **Verify checksums** of all downloaded binaries before installing
3. **Back up before making changes** — both v1.0 and v1.1.0 wallets
4. **Confirm the disposal wallet address** with the team before sending — do not trust addresses from unofficial sources
5. **Save all transaction IDs** from both chains for your records
6. **Keep your v1.0 wallet backup** even after successful migration

---

## Timeline

| Milestone | Date | Status |
|-----------|------|--------|
| v1.0 Snapshot (Block 434,881) | December 22, 2025 | Complete |
| v1.1.0 Network Launch | January 3, 2026 | Complete |
| Migration Period Opens | January 3, 2026 | Complete |
| **Migration Period Closes** | **April 3, 2026** | Active |
| Distribution Complete | May 2026 | Pending |

---

## Getting Help

- **Email:** transfermy@ammocoin.org
- **GitHub Issues:** https://github.com/everquin/AMMOcoin/issues
- **Documentation:** [Migration docs](https://github.com/everquin/AMMOcoin/tree/main/docs/migration)

**Questions?** Contact transfermy@ammocoin.org

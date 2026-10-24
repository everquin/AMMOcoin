# QuarterMaster pledge: how to sign yours

For the founding contributors who agreed to fund the QuarterMaster reserve
(decision AMMO-D-2026-10-18-12). Takes about ten minutes. You sign one
message with your own key. **You never send coins, and you never send your
wallet, your private key or your passphrase to anyone.**

## What you are agreeing to

Your v1.1 airdrop is paid to the same address you held on v1.0. With a
pledge, it is paid **minus your pledge** — 33.121679% of your snapshot
balance. The pledged AMMO stays in the block-1 reserve for the QuarterMaster
reserve. You receive nothing in return for it: no tier position, no reward,
no payment. The signature is the public proof that you agreed.

## 1. Find your line

Open [`data/quartermaster-pledges.csv`](data/quartermaster-pledges.csv) and
find your address. Copy the **message** column for your address exactly —
every character, on one line. Your pledge amount is in it.

## 2. Sign it, offline

You need three things: a **copy** of your `wallet.dat` (or the private key
for your address), any AMMOcoin wallet program, and your wallet passphrase if
it is encrypted. No network and no synced chain are needed — v1.0 and v1.1.x
use the same keys, addresses and message-signing format, so the v1.0 network
does not have to be running.

**Program:** the v1.0 wallet you already have, or v1.1.0 / v1.1.1 from the
official GitHub releases (`https://github.com/everquin/AMMOcoin/releases`).

**Always work on a copy, in a new empty folder.** Newer wallets may upgrade
an old wallet file when they open it, and v1.1.0 uses the same default
folder as v1.0 — so never point it at your original folder.

```bash
mkdir ~/ammo-pledge
cp <path to your old folder>/wallet.dat ~/ammo-pledge/
ammocoind -datadir=$HOME/ammo-pledge -connect=0 -listen=0 -daemon        # offline: no peers, no sync
ammocoin-cli -datadir=$HOME/ammo-pledge walletpassphrase "<passphrase>" 300   # only if encrypted
ammocoin-cli -datadir=$HOME/ammo-pledge signmessage "<your address>" "<your message, exactly>"
ammocoin-cli -datadir=$HOME/ammo-pledge stop
```

On Windows use `%USERPROFILE%\ammo-pledge` and the `.exe` names.

**Desktop app instead:** start it with `-datadir=<the new folder> -connect=0`
(AMMOcoin-Qt), then File → Sign message: paste your address and the message,
click *Sign Message*, copy the signature. It will say it is out of sync —
ignore that; signing doesn't need the chain.

**Only have the private key** (paper wallet, or an old `dumpprivkey`)? Start
the same offline wallet with an empty folder, then
`ammocoin-cli -datadir=$HOME/ammo-pledge importprivkey "<key>" "" false`
and sign as above. Type the key yourself; never paste it into chat, email or
a website.

Afterwards you can delete the `~/ammo-pledge` folder (your original wallet
is untouched).

## 3. Send back only two things

Your **address** and the **signature** (a line of letters ending in `=`).
That is all. The signature reveals nothing secret and will be published.

## 4. What happens next

Every signature is checked with `scripts/migration/verify-pledges.py`. The
airdrop is built only when all pledges are signed. The pledges, signatures
and the airdrop reconciliation are published in
[`../compliance/AIRDROPS.md`](../compliance/AIRDROPS.md).

If you can't find or open the key for your address, say so — don't hand the
wallet to someone else to sign for you. A pledge counts only when the holder
signs it.

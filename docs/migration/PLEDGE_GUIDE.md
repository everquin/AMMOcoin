# QuarterMaster pledge: how to sign yours

For the early contributors who agreed to fund the QuarterMaster reserve
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

## 2. Sign it, offline if you like

Any wallet that holds the key for that address works, **v1.0 or v1.1.1**
(same keys, same signing format). It does not need to be synced or online,
and the v1.0 network does not need to be running.

**Qt wallet:** File → Sign message. Paste your address, paste the message,
click *Sign Message*, copy the signature.

**Command line** (start the wallet, unlock it if encrypted, then):

```bash
ammocoin-cli signmessage "<your address>" "<the message, exactly>"
```

If your key is only in an old v1.0 `wallet.dat`, you can start v1.0 offline
on a copy of it just to sign. Don't copy v1.0 `blocks/` or `chainstate/`
anywhere.

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

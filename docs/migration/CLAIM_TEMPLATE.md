# Airdrop claim: what to send

Use this only if your v1.0 balance did not appear after a full v1.1.1 sync ([V1.0_BALANCE_AIRDROP.md](V1.0_BALANCE_AIRDROP.md)).

## 1. Sign the message

On a v1.0 wallet that holds the key (offline is fine). Copy the text exactly, and use the same address for both where you can:

```bash
ammocoin-cli signmessage "YOUR_V1.0_ADDRESS" "AMMOcoin v1.1 airdrop claim: YOUR_V1.0_ADDRESS pay YOUR_V1.1_ADDRESS"
```

## 2. Email it to claims@ammocoin.org

Subject: `Airdrop claim`

```
v1.0 address: YOUR_V1.0_ADDRESS
v1.1 address: YOUR_V1.1_ADDRESS
Message:      AMMOcoin v1.1 airdrop claim: YOUR_V1.0_ADDRESS pay YOUR_V1.1_ADDRESS
Signature:    THE_SIGNATURE_FROM_STEP_1
```

Send only these four lines. A signature reveals nothing secret. **Never** include a private key, seed phrase, wallet file or passphrase, and never send coins or a fee. Nobody from AMMOcoin will ask for them.

## 3. What happens next

- You get a reply with a claim number, such as `C-0001`.
- The claim's status is listed in the public [claims log](CLAIMS_LOG.md) under that number, without your email or addresses.
- If the checks pass, the missing amount is paid to the v1.1 address you named, in the next payout batch. There is no deadline.

Don't post claims in GitHub Issues: Issues are public, and anything posted there can be seen and copied by anyone. Issues are for technical bugs only.

---

## For the project: reply templates

**Acknowledgement** (send from claims@ammocoin.org):

> Thanks, your AMMOcoin airdrop claim is received as **C-NNNN**. Its status will be listed under that number in the public claims log, https://github.com/everquin/AMMOcoin/blob/main/docs/migration/CLAIMS_LOG.md, without your email or addresses. We will never ask for your private key, seed phrase, wallet file or any coins.

**Outcome:** state the status and, if paid, the txid; if rejected, the reason from the claims log list and how to resend (for example "the message text must match exactly").

**Private record:** keep the sender's email and the claim's addresses and signature only in the owner's private claims records (`verify-claim.py --claims` CSV and the mailbox), never in this repository.

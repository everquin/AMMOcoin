#!/usr/bin/env python3
"""
AMMOcoin v1.1.0 - Migration Fund Claim Verification Script

Verifies that a user owns a v1.0 address and calculates the exact amount
they're entitled to claim from the migration fund.

Usage:
    # Interactive mode
    python3 verify-claim.py

    # Command line mode
    python3 verify-claim.py --address <v1.0_address> --signature <signature> --message <message>

    # Process claim and send funds
    python3 verify-claim.py --address <v1.0_address> --signature <sig> --message <msg> --send --v1.1-address <new_address>
"""

import json
import subprocess
import sys
from datetime import datetime
from pathlib import Path
from typing import Dict, Optional, Tuple


class ClaimVerifier:
    """Verifies and processes migration fund claims"""

    def __init__(self, cli_path: str = "./ammocoin-apps-from-ammocoin/src/ammocoin-cli"):
        self.cli_path = Path(cli_path)
        self.claims_file = Path("migration-fund-claims.json")
        self.processed_claims_file = Path("processed-claims.json")
        self.migration_fund_address = "Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs"

        if not self.claims_file.exists():
            raise FileNotFoundError("migration-fund-claims.json not found")

        # Load claims data
        with open(self.claims_file, 'r') as f:
            self.claims_data = json.load(f)

        self.balances = {item["address"]: float(item["balance"])
                        for item in self.claims_data.get("claims", [])}

        # Load processed claims
        self.processed_claims = self._load_processed_claims()

    def _load_processed_claims(self) -> Dict:
        """Load record of already processed claims"""
        if self.processed_claims_file.exists():
            with open(self.processed_claims_file, 'r') as f:
                return json.load(f)
        return {"claims": []}

    def _save_processed_claim(self, claim_record: Dict):
        """Save a processed claim to the log"""
        self.processed_claims["claims"].append(claim_record)

        with open(self.processed_claims_file, 'w') as f:
            json.dump(self.processed_claims, f, indent=2)

    def run_cli(self, *args) -> Tuple[bool, str]:
        """Run ammocoin-cli command and return (success, output)"""
        try:
            cmd = [str(self.cli_path)] + list(args)
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=30
            )

            if result.returncode == 0:
                return True, result.stdout.strip()
            else:
                return False, result.stderr.strip()

        except subprocess.TimeoutExpired:
            return False, "Command timed out"
        except Exception as e:
            return False, str(e)

    def check_address_balance(self, address: str) -> Optional[float]:
        """Check if address is in migration fund and return balance"""
        balance = self.balances.get(address)

        if balance is None:
            return None

        # Check if already claimed
        for claim in self.processed_claims["claims"]:
            if claim.get("v1_0_address") == address:
                print(f"⚠️  This address has already claimed funds on {claim.get('timestamp')}")
                print(f"   TXID: {claim.get('txid')}")
                return None

        return balance

    def verify_message_signature(self, address: str, signature: str, message: str) -> bool:
        """
        Verify that a message was signed by the owner of an address

        Note: This uses verifymessage which works the same in v1.0 and v1.1.0
        since both use the same address format
        """
        success, output = self.run_cli("verifymessage", address, signature, message)

        if success:
            try:
                result = output.strip().lower()
                return result == "true"
            except:
                pass

        return False

    def send_claim_payment(self, v1_1_address: str, amount: float) -> Optional[str]:
        """
        Send claim payment from migration fund to user's v1.1.0 address
        Returns txid on success, None on failure
        """
        # Validate v1.1.0 address
        success, output = self.run_cli("validateaddress", v1_1_address)
        if not success:
            print(f"❌ Could not validate address: {output}")
            return None

        try:
            validation = json.loads(output)
            if not validation.get("isvalid"):
                print(f"❌ Invalid v1.1.0 address: {v1_1_address}")
                return None
        except:
            print("❌ Error parsing address validation")
            return None

        # Send payment
        amount_str = f"{amount:.8f}"
        success, output = self.run_cli("sendtoaddress", v1_1_address, amount_str)

        if success:
            txid = output.strip()
            print(f"✅ Payment sent!")
            print(f"   Amount: {amount:,.8f} AMMO")
            print(f"   To: {v1_1_address}")
            print(f"   TXID: {txid}")
            return txid
        else:
            print(f"❌ Failed to send payment: {output}")
            return None

    def verify_and_process_claim(self, v1_0_address: str, signature: str,
                                 message: str, v1_1_address: Optional[str] = None,
                                 send: bool = False) -> Dict:
        """
        Verify a claim and optionally process payment

        Returns:
            Dict with verification results
        """
        result = {
            "valid": False,
            "v1_0_address": v1_0_address,
            "balance": 0.0,
            "error": None,
            "txid": None
        }

        print("\n" + "=" * 60)
        print("🔍 CLAIM VERIFICATION")
        print("=" * 60)
        print(f"v1.0 Address: {v1_0_address}")

        # Step 1: Check if address is eligible
        balance = self.check_address_balance(v1_0_address)

        if balance is None:
            result["error"] = "Address not found in migration fund or already claimed"
            print(f"\n❌ {result['error']}")
            return result

        result["balance"] = balance
        print(f"✅ Address found in migration fund")
        print(f"   Claimable amount: {balance:,.8f} AMMO")

        # Step 2: Verify signature
        print(f"\n🔐 Verifying signature...")
        print(f"   Message: '{message}'")

        if not self.verify_message_signature(v1_0_address, signature, message):
            result["error"] = "Invalid signature - user does not own this address"
            print(f"\n❌ {result['error']}")
            return result

        print("✅ Signature verified - user owns this address")
        result["valid"] = True

        # Step 3: Send payment if requested
        if send:
            if not v1_1_address:
                result["error"] = "No v1.1.0 address provided for payment"
                print(f"\n❌ {result['error']}")
                return result

            print(f"\n💸 Processing payment...")
            txid = self.send_claim_payment(v1_1_address, balance)

            if txid:
                result["txid"] = txid

                # Record the claim
                claim_record = {
                    "v1_0_address": v1_0_address,
                    "v1_1_address": v1_1_address,
                    "amount": balance,
                    "txid": txid,
                    "timestamp": datetime.now().isoformat(),
                    "message": message,
                    "signature": signature
                }

                self._save_processed_claim(claim_record)
                print(f"\n💾 Claim recorded in {self.processed_claims_file}")

            else:
                result["error"] = "Payment failed"
                result["valid"] = False

        else:
            print("\n✅ Claim verified successfully")
            print("   Use --send flag to process payment")

        print("=" * 60 + "\n")
        return result

    def interactive_mode(self):
        """Interactive claim verification"""
        print("\n🎯 AMMOcoin Migration Fund - Interactive Claim Verification")
        print("=" * 60)

        # Get v1.0 address
        v1_0_address = input("\nEnter v1.0 address: ").strip()

        # Check balance
        balance = self.check_address_balance(v1_0_address)

        if balance is None:
            print("\n❌ Address not eligible for migration fund claim")
            return

        print(f"\n✅ Address eligible for {balance:,.8f} AMMO")

        # Explain signature process
        print("\n📝 To verify ownership, you need to sign a message with this address.")
        print("   In your v1.0 wallet, use: signmessage <address> <message>")
        print("   Or in ammocoin-cli: ammocoin-cli signmessage <address> <message>")

        # Get signature details
        message = input("\nEnter the message you signed: ").strip()
        signature = input("Enter the signature: ").strip()

        # Verify
        if not self.verify_message_signature(v1_0_address, signature, message):
            print("\n❌ Invalid signature!")
            return

        print("\n✅ Signature verified!")

        # Ask about payment
        send_payment = input("\nProcess payment now? (y/n): ").strip().lower()

        if send_payment == 'y':
            v1_1_address = input("Enter your v1.1.0 address to receive funds: ").strip()

            result = self.verify_and_process_claim(
                v1_0_address,
                signature,
                message,
                v1_1_address,
                send=True
            )

            if result.get("txid"):
                print("\n🎉 Claim processed successfully!")
            else:
                print(f"\n❌ Claim failed: {result.get('error')}")
        else:
            print("\n✅ Claim verified but not processed")

    def show_statistics(self):
        """Show migration fund statistics"""
        total_claims = len(self.balances)
        total_amount = sum(self.balances.values())
        processed = len(self.processed_claims["claims"])
        processed_amount = sum(c["amount"] for c in self.processed_claims["claims"])
        remaining = total_claims - processed
        remaining_amount = total_amount - processed_amount

        print("\n📊 MIGRATION FUND STATISTICS")
        print("=" * 60)
        print(f"Migration fund address: {self.migration_fund_address}")
        print(f"\nTotal eligible addresses: {total_claims:,}")
        print(f"Total fund amount:        {total_amount:,.8f} AMMO")
        print(f"\nProcessed claims:         {processed:,}")
        print(f"Processed amount:         {processed_amount:,.8f} AMMO")
        print(f"\nRemaining claims:         {remaining:,}")
        print(f"Remaining amount:         {remaining_amount:,.8f} AMMO")
        print("=" * 60 + "\n")


def main():
    """Main entry point"""
    import argparse

    parser = argparse.ArgumentParser(
        description="Verify and process AMMOcoin migration fund claims"
    )
    parser.add_argument(
        "--address",
        help="v1.0 address making the claim"
    )
    parser.add_argument(
        "--signature",
        help="Signature proving ownership of v1.0 address"
    )
    parser.add_argument(
        "--message",
        help="Message that was signed"
    )
    parser.add_argument(
        "--v1.1-address",
        dest="v1_1_address",
        help="v1.1.0 address to receive funds"
    )
    parser.add_argument(
        "--send",
        action="store_true",
        help="Actually send the payment (requires --v1.1-address)"
    )
    parser.add_argument(
        "--stats",
        action="store_true",
        help="Show migration fund statistics"
    )
    parser.add_argument(
        "--cli-path",
        default="./ammocoin-apps-from-ammocoin/src/ammocoin-cli",
        help="Path to ammocoin-cli binary"
    )

    args = parser.parse_args()

    try:
        verifier = ClaimVerifier(cli_path=args.cli_path)

        # Show statistics if requested
        if args.stats:
            verifier.show_statistics()
            return 0

        # Command line mode
        if args.address and args.signature and args.message:
            result = verifier.verify_and_process_claim(
                args.address,
                args.signature,
                args.message,
                args.v1_1_address,
                send=args.send
            )

            if result["valid"]:
                if result.get("txid"):
                    print(f"✅ Claim processed: {result['txid']}")
                    return 0
                else:
                    print(f"✅ Claim verified: {result['balance']:,.8f} AMMO")
                    return 0
            else:
                print(f"❌ Claim invalid: {result.get('error')}")
                return 1

        # Interactive mode
        else:
            verifier.interactive_mode()
            return 0

    except FileNotFoundError as e:
        print(f"\n❌ Error: {e}")
        return 1
    except KeyboardInterrupt:
        print("\n\nAborted by user")
        return 130
    except Exception as e:
        print(f"\n❌ Unexpected error: {e}")
        import traceback
        traceback.print_exc()
        return 1


if __name__ == "__main__":
    sys.exit(main())

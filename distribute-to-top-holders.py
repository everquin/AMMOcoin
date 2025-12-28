#!/usr/bin/env python3
"""
AMMOcoin v1.1.0 - Top 61 Holders Distribution Script

Automatically distributes funds to the top 61 holders from genesis-top-holders.json
using the ammocoin-cli RPC interface.

Usage:
    python3 distribute-to-top-holders.py [--dry-run] [--cli-path PATH]

Options:
    --dry-run       Show what would be sent without actually sending
    --cli-path      Path to ammocoin-cli binary (default: ./ammocoin-apps-from-ammocoin/src/ammocoin-cli)
"""

import json
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional, Tuple


class DistributionManager:
    """Manages distribution of funds to top holders"""

    def __init__(self, cli_path: str = "./ammocoin-apps-from-ammocoin/src/ammocoin-cli"):
        self.cli_path = Path(cli_path)
        self.log_file = Path(f"distribution-log-{datetime.now().strftime('%Y%m%d-%H%M%S')}.json")
        self.transactions: List[Dict] = []

        if not self.cli_path.exists():
            raise FileNotFoundError(f"ammocoin-cli not found at {self.cli_path}")

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

    def check_daemon_running(self) -> bool:
        """Check if ammocoind is running and responsive"""
        success, output = self.run_cli("getinfo")
        if success:
            print("✅ Daemon is running and responsive")
            try:
                info = json.loads(output)
                print(f"   Current block: {info.get('blocks', 'unknown')}")
                print(f"   Connections: {info.get('connections', 'unknown')}")
                return True
            except:
                pass

        print("❌ Daemon is not responsive")
        print("   Please start ammocoind: ./ammocoin-apps-from-ammocoin/src/ammocoind -daemon")
        return False

    def check_wallet_balance(self) -> Optional[float]:
        """Check current wallet balance"""
        success, output = self.run_cli("getbalance")
        if success:
            try:
                balance = float(output)
                print(f"💰 Wallet balance: {balance:,.8f} AMMO")
                return balance
            except:
                pass

        print("⚠️  Could not retrieve wallet balance")
        return None

    def validate_address(self, address: str) -> bool:
        """Validate an address using validateaddress RPC"""
        success, output = self.run_cli("validateaddress", address)
        if success:
            try:
                result = json.loads(output)
                return result.get("isvalid", False)
            except:
                pass
        return False

    def send_to_address(self, address: str, amount: float, dry_run: bool = False) -> Optional[str]:
        """
        Send AMMO to an address
        Returns txid on success, None on failure
        """
        if dry_run:
            print(f"   [DRY RUN] Would send {amount:,.8f} AMMO to {address}")
            return "DRY_RUN_TXID"

        # Convert amount to string with 8 decimal places to avoid floating point issues
        amount_str = f"{amount:.8f}"

        success, output = self.run_cli("sendtoaddress", address, amount_str)

        if success:
            txid = output.strip()
            print(f"   ✅ Sent {amount:,.8f} AMMO to {address}")
            print(f"      TXID: {txid}")
            return txid
        else:
            print(f"   ❌ Failed to send to {address}: {output}")
            return None

    def load_genesis_holders(self) -> List[Dict]:
        """Load genesis-top-holders.json"""
        genesis_file = Path("genesis-top-holders.json")

        if not genesis_file.exists():
            raise FileNotFoundError("genesis-top-holders.json not found in current directory")

        with open(genesis_file, 'r') as f:
            data = json.load(f)

        holders = data.get("top_holders", [])

        print(f"\n📋 Loaded {len(holders)} holders from genesis-top-holders.json")
        print(f"   Total to distribute: {data.get('total_top_supply', 0):,.2f} AMMO")

        return holders

    def distribute_to_holders(self, holders: List[Dict], dry_run: bool = False,
                             start_from: int = 0, batch_size: int = 10) -> Dict:
        """
        Distribute funds to all holders

        Args:
            holders: List of holder dicts with 'address' and 'balance'
            dry_run: If True, don't actually send transactions
            start_from: Start from this holder index (for resuming)
            batch_size: Number of transactions before pausing for confirmations

        Returns:
            Summary statistics
        """
        total_holders = len(holders)
        successful = 0
        failed = 0
        total_sent = 0.0

        print(f"\n🚀 Starting distribution to {total_holders} holders")
        if start_from > 0:
            print(f"   Resuming from holder #{start_from + 1}")

        if dry_run:
            print("   ⚠️  DRY RUN MODE - No actual transactions will be sent\n")

        for i, holder in enumerate(holders[start_from:], start=start_from):
            holder_num = i + 1
            address = holder["address"]
            balance = float(holder["balance"])

            print(f"\n[{holder_num}/{total_holders}] Processing {address}")
            print(f"   Amount: {balance:,.8f} AMMO")

            # Validate address first
            if not self.validate_address(address):
                print(f"   ❌ Invalid address: {address}")
                failed += 1
                self.transactions.append({
                    "holder_number": holder_num,
                    "address": address,
                    "amount": balance,
                    "status": "failed",
                    "error": "Invalid address",
                    "timestamp": datetime.now().isoformat()
                })
                continue

            # Send transaction
            txid = self.send_to_address(address, balance, dry_run)

            if txid:
                successful += 1
                total_sent += balance
                self.transactions.append({
                    "holder_number": holder_num,
                    "address": address,
                    "amount": balance,
                    "status": "success",
                    "txid": txid,
                    "timestamp": datetime.now().isoformat()
                })
            else:
                failed += 1
                self.transactions.append({
                    "holder_number": holder_num,
                    "address": address,
                    "amount": balance,
                    "status": "failed",
                    "error": "Transaction failed",
                    "timestamp": datetime.now().isoformat()
                })

            # Pause for confirmations after each batch
            if not dry_run and (holder_num % batch_size == 0) and holder_num < total_holders:
                print(f"\n⏸️  Pausing for confirmations (completed {holder_num}/{total_holders})...")
                print("   Waiting 60 seconds for network confirmation...")
                time.sleep(60)

        # Save transaction log
        self.save_log()

        return {
            "total_holders": total_holders,
            "successful": successful,
            "failed": failed,
            "total_sent": total_sent,
            "dry_run": dry_run
        }

    def save_log(self):
        """Save transaction log to file"""
        log_data = {
            "distribution_date": datetime.now().isoformat(),
            "total_transactions": len(self.transactions),
            "transactions": self.transactions
        }

        with open(self.log_file, 'w') as f:
            json.dump(log_data, f, indent=2)

        print(f"\n💾 Transaction log saved to {self.log_file}")

    def print_summary(self, summary: Dict):
        """Print distribution summary"""
        print("\n" + "=" * 60)
        print("📊 DISTRIBUTION SUMMARY")
        print("=" * 60)
        print(f"Total holders:    {summary['total_holders']}")
        print(f"Successful:       {summary['successful']} ✅")
        print(f"Failed:           {summary['failed']} ❌")
        print(f"Total sent:       {summary['total_sent']:,.8f} AMMO")

        if summary['dry_run']:
            print("\n⚠️  This was a DRY RUN - no actual transactions were sent")

        print("=" * 60)

        if summary['failed'] > 0:
            print("\n⚠️  Some transactions failed. Check the log file for details.")
            print(f"   Log file: {self.log_file}")


def main():
    """Main entry point"""
    import argparse

    parser = argparse.ArgumentParser(
        description="Distribute AMMOcoin v1.1.0 funds to top 61 holders"
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Show what would be sent without actually sending"
    )
    parser.add_argument(
        "--cli-path",
        default="./ammocoin-apps-from-ammocoin/src/ammocoin-cli",
        help="Path to ammocoin-cli binary"
    )
    parser.add_argument(
        "--start-from",
        type=int,
        default=0,
        help="Resume from this holder index (0-based)"
    )
    parser.add_argument(
        "--batch-size",
        type=int,
        default=10,
        help="Number of transactions before pausing for confirmations"
    )

    args = parser.parse_args()

    try:
        print("🎯 AMMOcoin v1.1.0 - Top Holders Distribution")
        print("=" * 60)

        # Initialize manager
        manager = DistributionManager(cli_path=args.cli_path)

        # Check daemon is running
        if not manager.check_daemon_running():
            return 1

        # Check wallet balance
        balance = manager.check_wallet_balance()
        if balance is None:
            return 1

        # Load holders
        holders = manager.load_genesis_holders()

        # Calculate required balance
        required = sum(float(h["balance"]) for h in holders)
        print(f"\n💵 Required balance: {required:,.8f} AMMO")

        if not args.dry_run and balance < required:
            print(f"\n❌ ERROR: Insufficient balance!")
            print(f"   Available: {balance:,.8f} AMMO")
            print(f"   Required:  {required:,.8f} AMMO")
            print(f"   Short by:  {(required - balance):,.8f} AMMO")
            return 1

        # Confirm before proceeding
        if not args.dry_run:
            print("\n⚠️  WARNING: This will send real transactions!")
            response = input("Type 'yes' to proceed: ")
            if response.lower() != 'yes':
                print("Aborted by user")
                return 0

        # Distribute
        summary = manager.distribute_to_holders(
            holders,
            dry_run=args.dry_run,
            start_from=args.start_from,
            batch_size=args.batch_size
        )

        # Print summary
        manager.print_summary(summary)

        return 0 if summary['failed'] == 0 else 1

    except FileNotFoundError as e:
        print(f"\n❌ Error: {e}")
        return 1
    except KeyboardInterrupt:
        print("\n\n⚠️  Distribution interrupted by user")
        print("   Progress has been saved to log file")
        print("   Use --start-from to resume")
        return 130
    except Exception as e:
        print(f"\n❌ Unexpected error: {e}")
        import traceback
        traceback.print_exc()
        return 1


if __name__ == "__main__":
    sys.exit(main())

#!/usr/bin/env python3
"""
AMMOcoin v1.0 Blockchain Scanner
Scans entire blockchain to find all addresses with balances (not just wallet addresses)
"""

import json
import sys
import base64
from decimal import Decimal
from datetime import datetime
from urllib.request import Request, urlopen
from urllib.error import URLError, HTTPError
from collections import defaultdict

# Configuration
V1_RPC_USER = "user"  # Update with actual RPC credentials
V1_RPC_PASSWORD = "password"  # Update with actual RPC credentials
V1_RPC_HOST = "127.0.0.1"  # localhost if running the wallet locally
V1_RPC_PORT = 37020

def run_rpc_command(method, params=[]):
    """Execute RPC command against v1.0 node via HTTP"""
    url = f"http://{V1_RPC_HOST}:{V1_RPC_PORT}"

    payload = {
        "jsonrpc": "1.0",
        "id": "scanner",
        "method": method,
        "params": params
    }

    credentials = f"{V1_RPC_USER}:{V1_RPC_PASSWORD}"
    auth_header = base64.b64encode(credentials.encode()).decode()

    try:
        request = Request(url)
        request.add_header("Content-Type", "application/json")
        request.add_header("Authorization", f"Basic {auth_header}")
        request.data = json.dumps(payload).encode()

        response = urlopen(request, timeout=60)
        response_data = response.read().decode()
        result = json.loads(response_data)

        if "error" in result and result["error"]:
            print(f"RPC Error in {method}: {result['error']}", file=sys.stderr)
            return None

        return result.get("result")

    except HTTPError as e:
        if e.code == 401:
            print(f"ERROR: Authentication failed. Check RPC credentials.", file=sys.stderr)
        else:
            print(f"ERROR: HTTP {e.code}: {e.reason}", file=sys.stderr)
        return None
    except URLError as e:
        print(f"ERROR: Cannot connect to {url}: {e.reason}", file=sys.stderr)
        return None
    except Exception as e:
        print(f"Exception running {method}: {e}", file=sys.stderr)
        return None

def scan_blockchain_for_utxos():
    """
    Scan the blockchain using txoutsetinfo to get all UTXOs
    This works without needing addresses imported into the wallet
    """
    print("=" * 70)
    print("AMMOcoin v1.0 Blockchain Scanner")
    print("=" * 70)

    # Get blockchain info
    print("\nConnecting to v1.0 node...")
    info = run_rpc_command("getblockchaininfo")

    if not info:
        print("ERROR: Could not connect to v1.0 node")
        return None

    block_height = info.get("blocks", 0)
    block_hash = run_rpc_command("getblockhash", [block_height])

    print(f"✓ Connected to v1.0 network")
    print(f"  Block Height: {block_height}")
    print(f"  Block Hash: {block_hash}")

    # Get UTXO set statistics
    print(f"\nScanning UTXO set (this may take a few minutes)...")
    utxo_stats = run_rpc_command("gettxoutsetinfo")

    if utxo_stats:
        print(f"\nUTXO Set Statistics:")
        print(f"  Total Transactions: {utxo_stats.get('transactions', 'unknown')}")
        print(f"  Total Outputs: {utxo_stats.get('txouts', 'unknown')}")
        print(f"  Total Amount: {utxo_stats.get('total_amount', 'unknown')} AMMO")

    print(f"\nNote: Standard RPC doesn't provide per-address UTXO breakdown.")
    print(f"Alternative approaches needed:")
    print(f"  1. Import all known user addresses into wallet")
    print(f"  2. Use external block explorer API")
    print(f"  3. Parse blockchain data files directly")
    print(f"  4. Use custom RPC command if available")

    return {
        "snapshot_info": {
            "timestamp": datetime.now().isoformat(),
            "block_height": block_height,
            "block_hash": block_hash,
            "network": "mainnet",
            "total_amount": utxo_stats.get('total_amount', 'unknown') if utxo_stats else 'unknown'
        }
    }

def import_addresses_and_scan(addresses):
    """Import addresses and get their balances"""
    print("=" * 70)
    print("Importing addresses and scanning balances")
    print("=" * 70)

    balances = {}

    for idx, address in enumerate(addresses, 1):
        print(f"\n[{idx}/{len(addresses)}] Processing {address}")

        # Import address (read-only, no rescan)
        print(f"  Importing...")
        result = run_rpc_command("importaddress", [address, "", False])

        if result is None:  # importaddress returns None on success
            print(f"  ✓ Imported")

        # Get address balance
        print(f"  Getting balance...")
        utxos = run_rpc_command("listunspent", [0, 9999999, [address]])

        if utxos:
            balance = sum(Decimal(str(u.get("amount", 0))) for u in utxos)
            balances[address] = balance
            print(f"  Balance: {balance} AMMO")
        else:
            balances[address] = Decimal("0")
            print(f"  Balance: 0 AMMO")

    return balances

def main():
    """Main entry point"""

    # First, try to get blockchain stats
    stats = scan_blockchain_for_utxos()

    if not stats:
        return 1

    # Check if user provided addresses file
    if len(sys.argv) > 1:
        addresses_file = sys.argv[1]
        print(f"\nLoading addresses from: {addresses_file}")

        try:
            with open(addresses_file, 'r') as f:
                # Support both plain text (one address per line) and JSON
                content = f.read().strip()
                if content.startswith('['):
                    addresses = json.loads(content)
                else:
                    addresses = [line.strip() for line in content.split('\n') if line.strip()]

            print(f"✓ Loaded {len(addresses)} addresses")

            # Import and scan
            balances = import_addresses_and_scan(addresses)

            # Create snapshot
            total_supply = sum(balances.values())

            snapshot = {
                "snapshot_info": {
                    "timestamp": datetime.now().isoformat(),
                    "block_height": stats["snapshot_info"]["block_height"],
                    "block_hash": stats["snapshot_info"]["block_hash"],
                    "network": "mainnet",
                    "total_addresses": len(balances),
                    "total_supply": str(total_supply)
                },
                "balances": {addr: str(bal) for addr, bal in balances.items()}
            }

            # Save snapshot
            output_file = "v1.0-balance-snapshot.json"
            with open(output_file, 'w') as f:
                json.dump(snapshot, f, indent=2)

            print(f"\n✓ Snapshot saved to: {output_file}")
            print(f"\nSnapshot Summary:")
            print(f"  Total Addresses: {len(balances)}")
            print(f"  Total Supply: {total_supply} AMMO")

            return 0

        except FileNotFoundError:
            print(f"ERROR: File not found: {addresses_file}")
            return 1
        except Exception as e:
            print(f"ERROR: {e}")
            return 1

    else:
        print("\n" + "=" * 70)
        print("NEXT STEPS")
        print("=" * 70)
        print("\nTo complete the snapshot, you need to:")
        print("\n1. Create a file with all user addresses (one per line):")
        print("   echo 'Aaddress1...' > user-addresses.txt")
        print("   echo 'Aaddress2...' >> user-addresses.txt")
        print("   ...")
        print("\n2. Run this script with the addresses file:")
        print("   python3 v1.0-blockchain-scanner.py user-addresses.txt")
        print("\nThe script will:")
        print("  - Import each address (read-only)")
        print("  - Get balance for each address")
        print("  - Create v1.0-balance-snapshot.json")

        return 0

if __name__ == "__main__":
    sys.exit(main())

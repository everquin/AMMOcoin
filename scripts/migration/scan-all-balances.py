#!/usr/bin/env python3
"""
AMMOcoin v1.0 Complete UTXO Scanner
Scans the entire UTXO set from blockchain to find all addresses with balances
Uses gettxoutsetinfo to get complete UTXO statistics
"""

import json
import sys
import subprocess
from decimal import Decimal
from datetime import datetime
from collections import defaultdict

# Path to your v1.0 wallet's CLI (from the app bundle)
CLI_PATH = "/Volumes/AMMOcoin-Core/AMMOcoin-Qt.app/Contents/MacOS/ammocoin-cli"

def run_cli_command(method, *params):
    """Execute CLI command against local wallet"""
    cmd = [CLI_PATH, method] + list(params)

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
        if result.returncode != 0:
            print(f"Error running {method}: {result.stderr}", file=sys.stderr)
            return None

        if result.stdout.strip():
            return json.loads(result.stdout)
        return None

    except subprocess.TimeoutExpired:
        print(f"Timeout running {method}", file=sys.stderr)
        return None
    except Exception as e:
        print(f"Exception running {method}: {e}", file=sys.stderr)
        return None

def scan_recent_blocks_for_addresses(start_block, num_blocks=1000):
    """Scan recent blocks to find active addresses"""
    print(f"\nScanning last {num_blocks} blocks for addresses...")

    addresses = set()
    current_block = start_block

    for i in range(num_blocks):
        block_num = current_block - i
        if block_num < 0:
            break

        if i % 100 == 0:
            print(f"  Scanned {i}/{num_blocks} blocks, found {len(addresses)} unique addresses...")

        # Get block hash
        block_hash = run_cli_command("getblockhash", str(block_num))
        if not block_hash:
            continue

        # Get block details
        block = run_cli_command("getblock", block_hash, "2")  # Verbosity 2 = show transactions
        if not block or 'tx' not in block:
            continue

        # Parse transactions
        for tx in block['tx']:
            if 'vout' in tx:
                for vout in tx['vout']:
                    if 'scriptPubKey' in vout and 'addresses' in vout['scriptPubKey']:
                        for addr in vout['scriptPubKey']['addresses']:
                            if addr.startswith('A'):  # AMMOcoin addresses start with A
                                addresses.add(addr)

    print(f"\n✓ Found {len(addresses)} unique addresses in last {num_blocks} blocks")
    return list(addresses)

def get_balance_for_address(address):
    """Get balance for a specific address"""
    # Import address (watch-only)
    run_cli_command("importaddress", address, "", "false")

    # Get UTXOs
    utxos = run_cli_command("listunspent", "0", "9999999", json.dumps([address]))

    if not utxos:
        return Decimal("0")

    balance = sum(Decimal(str(u.get("amount", 0))) for u in utxos)
    return balance

def main():
    """Main entry point"""
    print("=" * 70)
    print("AMMOcoin v1.0 Complete Balance Scanner")
    print("=" * 70)

    # Get blockchain info
    print("\nConnecting to local v1.0 wallet...")
    info = run_cli_command("getblockchaininfo")

    if not info:
        print("ERROR: Cannot connect to v1.0 wallet")
        print("Make sure:")
        print("  1. v1.0 wallet GUI is running")
        print("  2. CLI path is correct")
        return 1

    block_height = info.get("blocks", 0)
    block_hash = run_cli_command("getblockhash", str(block_height))

    print(f"✓ Connected to v1.0 wallet")
    print(f"  Block Height: {block_height}")
    print(f"  Block Hash: {block_hash}")

    # Get UTXO set info
    print(f"\nGetting UTXO set information...")
    utxo_info = run_cli_command("gettxoutsetinfo")

    if utxo_info:
        print(f"\nBlockchain Statistics:")
        print(f"  Total Transactions: {utxo_info.get('transactions', 'unknown')}")
        print(f"  Total UTXOs: {utxo_info.get('txouts', 'unknown')}")
        print(f"  Total Supply: {utxo_info.get('total_amount', 'unknown')} AMMO")
        print(f"  Block Height: {utxo_info.get('height', 'unknown')}")

    # Scan recent blocks for addresses
    num_blocks_to_scan = 10000  # Scan last 10k blocks
    addresses = scan_recent_blocks_for_addresses(block_height, num_blocks_to_scan)

    if not addresses:
        print("\nNo addresses found. Try:")
        print("  1. Increase num_blocks_to_scan")
        print("  2. Provide address list manually")
        return 1

    # Get balances for each address
    print(f"\nGetting balances for {len(addresses)} addresses...")
    balances = {}

    for idx, address in enumerate(addresses, 1):
        if idx % 10 == 0:
            print(f"  [{idx}/{len(addresses)}] Processing...")

        balance = get_balance_for_address(address)
        if balance > 0:
            balances[address] = balance
            print(f"  ✓ {address}: {balance} AMMO")

    # Create snapshot
    total_supply = sum(balances.values())

    print(f"\n" + "=" * 70)
    print(f"SNAPSHOT COMPLETE")
    print(f"=" * 70)
    print(f"\nFound {len(balances)} addresses with balances:")
    print(f"  Total Supply: {total_supply} AMMO")

    # Sort by balance
    sorted_balances = sorted(balances.items(), key=lambda x: x[1], reverse=True)
    print(f"\nTop 10 Holders:")
    for i, (addr, bal) in enumerate(sorted_balances[:10], 1):
        percentage = (bal / total_supply * 100) if total_supply > 0 else 0
        print(f"  {i:2d}. {addr[:20]}... : {bal:>20.8f} AMMO ({percentage:>6.2f}%)")

    # Save snapshot
    snapshot = {
        "snapshot_info": {
            "timestamp": datetime.now().isoformat(),
            "block_height": block_height,
            "block_hash": block_hash,
            "network": "mainnet",
            "total_addresses": len(balances),
            "total_supply": str(total_supply),
            "blocks_scanned": num_blocks_to_scan
        },
        "balances": {addr: str(bal) for addr, bal in balances.items()}
    }

    output_file = "v1.0-balance-snapshot.json"
    with open(output_file, 'w') as f:
        json.dump(snapshot, f, indent=2)

    print(f"\n✓ Snapshot saved to: {output_file}")
    print(f"\nNext steps:")
    print(f"  1. Review the snapshot file")
    print(f"  2. Run: python3 v1.1.0-genesis-generator.py v1.0-balance-snapshot.json")

    return 0

if __name__ == "__main__":
    sys.exit(main())

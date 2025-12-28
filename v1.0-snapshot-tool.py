#!/usr/bin/env python3
"""
AMMOcoin v1.0 Balance Snapshot Tool
Connects to v1.0 node and exports all addresses with balances for v1.1.0 migration
"""

import json
import sys
import base64
from decimal import Decimal
from datetime import datetime
from urllib.request import Request, urlopen
from urllib.error import URLError, HTTPError

# Configuration
V1_RPC_USER = "user"  # Update with actual RPC credentials
V1_RPC_PASSWORD = "password"  # Update with actual RPC credentials
V1_RPC_HOST = "node1.ammocoin.org"
V1_RPC_PORT = 37020

def run_rpc_command(method, params=[]):
    """Execute RPC command against v1.0 node via HTTP"""
    url = f"http://{V1_RPC_HOST}:{V1_RPC_PORT}"

    payload = {
        "jsonrpc": "1.0",
        "id": "snapshot-tool",
        "method": method,
        "params": params
    }

    # Create authentication header
    credentials = f"{V1_RPC_USER}:{V1_RPC_PASSWORD}"
    auth_header = base64.b64encode(credentials.encode()).decode()

    try:
        request = Request(url)
        request.add_header("Content-Type", "application/json")
        request.add_header("Authorization", f"Basic {auth_header}")
        request.data = json.dumps(payload).encode()

        response = urlopen(request, timeout=30)
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

def get_blockchain_info():
    """Get current blockchain state"""
    return run_rpc_command("getblockchaininfo")

def get_all_utxos():
    """Get all unspent outputs from the blockchain"""
    # This gets UTXOs from the wallet
    utxos = run_rpc_command("listunspent", ["0", "9999999"])
    return utxos if utxos else []

def get_address_balances():
    """Get balances for all addresses"""
    balances = {}

    # Get all UTXOs
    utxos = get_all_utxos()

    print(f"Found {len(utxos)} UTXOs")

    for utxo in utxos:
        address = utxo.get("address")
        amount = Decimal(str(utxo.get("amount", 0)))

        if address:
            if address not in balances:
                balances[address] = Decimal("0")
            balances[address] += amount

    return balances

def export_snapshot(filename="v1.0-balance-snapshot.json"):
    """Export complete balance snapshot"""
    print("=" * 60)
    print("AMMOcoin v1.0 Balance Snapshot Tool")
    print("=" * 60)

    # Get blockchain info
    print("\nConnecting to v1.0 network...")
    info = get_blockchain_info()

    if not info:
        print("ERROR: Could not connect to v1.0 node", file=sys.stderr)
        print("Please check:")
        print("  1. Node is running at node1.ammocoin.org:37020")
        print("  2. RPC credentials are correct (V1_RPC_USER and V1_RPC_PASSWORD)")
        print("  3. Node allows RPC connections from this IP")
        return False

    block_height = info.get("blocks", 0)
    block_hash = run_rpc_command("getblockhash", [str(block_height)])

    print(f"✓ Connected to v1.0 network")
    print(f"  Block Height: {block_height}")
    print(f"  Block Hash: {block_hash}")

    # Get all address balances
    print("\nExtracting balances...")
    balances = get_address_balances()

    if not balances:
        print("WARNING: No balances found. This might mean:")
        print("  1. No wallet is loaded")
        print("  2. RPC access is limited")
        print("  3. Need to scan blockchain directly")
        return False

    # Calculate totals
    total_addresses = len(balances)
    total_supply = sum(balances.values())

    print(f"\n✓ Snapshot complete:")
    print(f"  Total Addresses: {total_addresses}")
    print(f"  Total Supply: {total_supply} AMMO")
    print(f"  Average Balance: {total_supply / total_addresses if total_addresses > 0 else 0} AMMO")

    # Find largest holders
    sorted_balances = sorted(balances.items(), key=lambda x: x[1], reverse=True)
    print(f"\n  Top 5 Holders:")
    for i, (addr, bal) in enumerate(sorted_balances[:5], 1):
        print(f"    {i}. {addr[:20]}... : {bal} AMMO")

    # Create snapshot data
    snapshot = {
        "snapshot_info": {
            "timestamp": datetime.now().isoformat(),
            "block_height": block_height,
            "block_hash": block_hash,
            "network": "mainnet",
            "total_addresses": total_addresses,
            "total_supply": str(total_supply)
        },
        "balances": {addr: str(bal) for addr, bal in balances.items()}
    }

    # Export to file
    with open(filename, 'w') as f:
        json.dump(snapshot, f, indent=2)

    print(f"\n✓ Snapshot saved to: {filename}")
    print(f"\nNext steps:")
    print(f"  1. Review the snapshot file")
    print(f"  2. Verify total supply matches expected value")
    print(f"  3. Generate v1.1.0 genesis with these balances")

    return True

if __name__ == "__main__":
    success = export_snapshot()
    sys.exit(0 if success else 1)

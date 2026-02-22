#!/usr/bin/env python3
"""
AMMOcoin Migration Verification Tool
Compares v1.0 snapshot balances with v1.1.0 actual balances to verify migration success
"""

import json
import sys
import base64
from decimal import Decimal
from urllib.request import Request, urlopen
from urllib.error import URLError, HTTPError

# Configuration
V1_1_RPC_USER = "user"  # Update with v1.1.0 RPC credentials
V1_1_RPC_PASSWORD = "password"
V1_1_RPC_HOST = "127.0.0.1"
V1_1_RPC_PORT = 51473

def run_rpc_command(host, port, user, password, method, params=[]):
    """Execute RPC command"""
    url = f"http://{host}:{port}"

    payload = {
        "jsonrpc": "1.0",
        "id": "verify-tool",
        "method": method,
        "params": params
    }

    credentials = f"{user}:{password}"
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
            return None

        return result.get("result")

    except Exception:
        return None

def load_snapshot(filename="v1.0-balance-snapshot.json"):
    """Load v1.0 balance snapshot"""
    try:
        with open(filename, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"ERROR: Snapshot file not found: {filename}")
        return None

def get_v1_1_balance(address):
    """Get balance for an address from v1.1.0 node"""
    # Import the address (read-only)
    run_rpc_command(V1_1_RPC_HOST, V1_1_RPC_PORT, V1_1_RPC_USER, V1_1_RPC_PASSWORD,
                   "importaddress", [address, "", False])

    # Get balance
    utxos = run_rpc_command(V1_1_RPC_HOST, V1_1_RPC_PORT, V1_1_RPC_USER, V1_1_RPC_PASSWORD,
                           "listunspent", [0, 9999999, [address]])

    if not utxos:
        return Decimal("0")

    total = Decimal("0")
    for utxo in utxos:
        total += Decimal(str(utxo.get("amount", 0)))

    return total

def verify_migration(snapshot_file="v1.0-balance-snapshot.json"):
    """Verify that all v1.0 balances are present in v1.1.0"""

    print("=" * 70)
    print("AMMOcoin Migration Verification Tool")
    print("=" * 70)

    # Load snapshot
    print(f"\nLoading v1.0 snapshot: {snapshot_file}")
    snapshot = load_snapshot(snapshot_file)

    if not snapshot:
        return False

    balances = snapshot.get("balances", {})
    snapshot_info = snapshot.get("snapshot_info", {})

    print(f"✓ Loaded snapshot")
    print(f"  Block Height: {snapshot_info.get('block_height')}")
    print(f"  Total Addresses: {len(balances)}")
    print(f"  Total Supply: {snapshot_info.get('total_supply')} AMMO")

    # Test v1.1.0 connection
    print(f"\nConnecting to v1.1.0 node ({V1_1_RPC_HOST}:{V1_1_RPC_PORT})...")
    info = run_rpc_command(V1_1_RPC_HOST, V1_1_RPC_PORT, V1_1_RPC_USER, V1_1_RPC_PASSWORD,
                          "getblockchaininfo")

    if not info:
        print("ERROR: Cannot connect to v1.1.0 node")
        print("Please check:")
        print("  1. v1.1.0 node is running")
        print("  2. RPC credentials are correct")
        print("  3. RPC port is accessible")
        return False

    print(f"✓ Connected to v1.1.0")
    print(f"  Block Height: {info.get('blocks', 0)}")
    print(f"  Chain: {info.get('chain', 'unknown')}")

    # Verify each address
    print(f"\nVerifying {len(balances)} addresses...")
    print("-" * 70)

    mismatches = []
    missing = []
    verified = []

    for idx, (address, v1_balance) in enumerate(balances.items(), 1):
        v1_balance_decimal = Decimal(v1_balance)

        print(f"\n[{idx}/{len(balances)}] {address}")
        print(f"  v1.0 Balance: {v1_balance_decimal:.8f} AMMO")

        v1_1_balance = get_v1_1_balance(address)
        print(f"  v1.1.0 Balance: {v1_1_balance:.8f} AMMO")

        if v1_1_balance == Decimal("0") and v1_balance_decimal > Decimal("0"):
            print(f"  ❌ MISSING IN v1.1.0")
            missing.append({
                "address": address,
                "v1_balance": str(v1_balance_decimal),
                "v1_1_balance": "0"
            })
        elif v1_1_balance != v1_balance_decimal:
            print(f"  ❌ MISMATCH")
            mismatches.append({
                "address": address,
                "v1_balance": str(v1_balance_decimal),
                "v1_1_balance": str(v1_1_balance),
                "difference": str(v1_1_balance - v1_balance_decimal)
            })
        else:
            print(f"  ✓ VERIFIED")
            verified.append(address)

    # Summary
    print("\n" + "=" * 70)
    print("VERIFICATION SUMMARY")
    print("=" * 70)
    print(f"\nTotal Addresses: {len(balances)}")
    print(f"  ✓ Verified: {len(verified)}")
    print(f"  ❌ Mismatches: {len(mismatches)}")
    print(f"  ❌ Missing: {len(missing)}")

    if mismatches:
        print("\nMISMATCHES:")
        for m in mismatches:
            print(f"  {m['address']}")
            print(f"    v1.0: {m['v1_balance']} AMMO")
            print(f"    v1.1.0: {m['v1_1_balance']} AMMO")
            print(f"    Difference: {m['difference']} AMMO")

    if missing:
        print("\nMISSING ADDRESSES:")
        for m in missing:
            print(f"  {m['address']}: {m['v1_balance']} AMMO")

    # Calculate totals
    v1_total = sum(Decimal(b) for b in balances.values())
    v1_1_total = sum(get_v1_1_balance(addr) for addr in balances.keys())

    print(f"\nTOTAL SUPPLY VERIFICATION:")
    print(f"  v1.0 Total: {v1_total:.8f} AMMO")
    print(f"  v1.1.0 Total: {v1_1_total:.8f} AMMO")

    if v1_total == v1_1_total:
        print(f"  ✓ TOTALS MATCH")
    else:
        diff = v1_1_total - v1_total
        print(f"  ❌ TOTALS DO NOT MATCH")
        print(f"     Difference: {diff:.8f} AMMO")

    # Final verdict
    print("\n" + "=" * 70)
    if len(verified) == len(balances) and v1_total == v1_1_total:
        print("✅ MIGRATION SUCCESSFUL - All balances verified!")
        print("=" * 70)
        return True
    else:
        print("❌ MIGRATION INCOMPLETE - Issues found!")
        print("=" * 70)
        print("\nPlease review mismatches and missing addresses above.")
        print("Do not proceed with production deployment until resolved.")
        return False

def main():
    """Main entry point"""
    if len(sys.argv) > 1:
        snapshot_file = sys.argv[1]
    else:
        snapshot_file = "v1.0-balance-snapshot.json"

    success = verify_migration(snapshot_file)
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()

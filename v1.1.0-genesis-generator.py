#!/usr/bin/env python3
"""
AMMOcoin v1.1.0 Genesis Block Generator
Takes v1.0 balance snapshot and generates C++ code for v1.1.0 genesis block
"""

import json
import sys
from decimal import Decimal
from datetime import datetime

def load_snapshot(filename="v1.0-balance-snapshot.json"):
    """Load v1.0 balance snapshot"""
    try:
        with open(filename, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"ERROR: Snapshot file not found: {filename}")
        print("Please run v1.0-snapshot-tool.py first to create the snapshot.")
        return None
    except json.JSONDecodeError as e:
        print(f"ERROR: Invalid JSON in snapshot file: {e}")
        return None

def generate_genesis_code(snapshot):
    """Generate C++ code for genesis block with pre-allocated balances"""

    balances = snapshot.get("balances", {})
    snapshot_info = snapshot.get("snapshot_info", {})

    if not balances:
        print("ERROR: No balances found in snapshot")
        return None

    total_addresses = len(balances)
    total_supply = Decimal(snapshot_info.get("total_supply", "0"))
    block_height = snapshot_info.get("block_height", 0)
    block_hash = snapshot_info.get("block_hash", "unknown")

    print("=" * 70)
    print("AMMOcoin v1.1.0 Genesis Block Code Generator")
    print("=" * 70)
    print(f"\nSnapshot Info:")
    print(f"  v1.0 Block Height: {block_height}")
    print(f"  v1.0 Block Hash: {block_hash}")
    print(f"  Total Addresses: {total_addresses}")
    print(f"  Total Supply: {total_supply} AMMO")
    print(f"\nGenerating genesis block code...")

    # Generate C++ code
    cpp_code = []

    # Header comment
    cpp_code.append("// AMMOcoin v1.1.0 Genesis Block with v1.0 Balance Migration")
    cpp_code.append(f"// Snapshot taken at v1.0 block height: {block_height}")
    cpp_code.append(f"// Snapshot block hash: {block_hash}")
    cpp_code.append(f"// Migration date: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    cpp_code.append(f"// Total addresses: {total_addresses}")
    cpp_code.append(f"// Total supply: {total_supply} AMMO")
    cpp_code.append("")

    # Genesis timestamp (current time)
    genesis_time = int(datetime.now().timestamp())

    # Genesis message
    cpp_code.append("CMainParams()")
    cpp_code.append("{")
    cpp_code.append('    strNetworkID = "main";')
    cpp_code.append("")
    cpp_code.append("    // Genesis block construction with v1.0 balance migration")
    cpp_code.append('    const char* pszTimestamp = "AMMOcoin v1.1.0 - Balance Migration from v1.0";')
    cpp_code.append("")
    cpp_code.append("    CMutableTransaction txNew;")
    cpp_code.append("    txNew.vin.resize(1);")
    cpp_code.append(f"    txNew.vout.resize({total_addresses});")
    cpp_code.append("")
    cpp_code.append("    // Genesis input")
    cpp_code.append("    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4)")
    cpp_code.append("        << std::vector<unsigned char>((const unsigned char*)pszTimestamp,")
    cpp_code.append("                                      (const unsigned char*)pszTimestamp + strlen(pszTimestamp));")
    cpp_code.append("")
    cpp_code.append(f"    // Pre-allocate all {total_addresses} v1.0 balances")

    # Sort addresses by balance (largest first) for clarity
    sorted_balances = sorted(balances.items(), key=lambda x: Decimal(x[1]), reverse=True)

    # Generate output for each address
    for idx, (address, balance) in enumerate(sorted_balances):
        balance_decimal = Decimal(balance)
        cpp_code.append(f"")
        cpp_code.append(f"    // Address {idx + 1}: {address}")
        cpp_code.append(f"    // Balance: {balance_decimal} AMMO")
        cpp_code.append(f"    txNew.vout[{idx}].nValue = {balance_decimal} * COIN;")
        cpp_code.append(f'    txNew.vout[{idx}].scriptPubKey = GetScriptForDestination(')
        cpp_code.append(f'        DecodeDestination("{address}"));')

    cpp_code.append("")
    cpp_code.append("    // Create genesis block")
    cpp_code.append("    genesis.vtx.push_back(std::make_shared<const CTransaction>(std::move(txNew)));")
    cpp_code.append("    genesis.hashPrevBlock.SetNull();")
    cpp_code.append("    genesis.nVersion = 1;")
    cpp_code.append(f"    genesis.nTime    = {genesis_time};")
    cpp_code.append("    genesis.nBits    = 0x1e0ffff0;")
    cpp_code.append("    genesis.nNonce   = 0;  // Will be computed")
    cpp_code.append("")
    cpp_code.append("    // Compute merkle root")
    cpp_code.append("    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);")
    cpp_code.append("")
    cpp_code.append("    // Mine genesis block (find valid nNonce)")
    cpp_code.append("    // NOTE: You need to run the genesis miner to find the correct nNonce")
    cpp_code.append("    // and hashGenesisBlock values. Uncomment the mining code below:")
    cpp_code.append("    /*")
    cpp_code.append("    printf(\"Mining genesis block...\\n\");")
    cpp_code.append("    while (UintToArith256(genesis.GetHash()) > UintToArith256(consensus.powLimit)) {")
    cpp_code.append("        genesis.nNonce++;")
    cpp_code.append("        if (genesis.nNonce % 10000 == 0)")
    cpp_code.append('            printf("nNonce: %u\\n", genesis.nNonce);')
    cpp_code.append("    }")
    cpp_code.append('    printf("Genesis block mined!\\n");')
    cpp_code.append('    printf("nNonce: %u\\n", genesis.nNonce);')
    cpp_code.append('    printf("Genesis hash: %s\\n", genesis.GetHash().ToString().c_str());')
    cpp_code.append('    printf("Merkle root: %s\\n", genesis.hashMerkleRoot.ToString().c_str());')
    cpp_code.append("    */")
    cpp_code.append("")
    cpp_code.append("    // After mining, set the values:")
    cpp_code.append("    // genesis.nNonce = [computed value];")
    cpp_code.append("    // consensus.hashGenesisBlock = uint256S(\"[computed hash]\");")
    cpp_code.append("    // assert(genesis.hashMerkleRoot == uint256S(\"[computed merkle root]\"));")
    cpp_code.append("    // assert(consensus.hashGenesisBlock == uint256S(\"[computed hash]\"));")
    cpp_code.append("}")

    return "\n".join(cpp_code)

def save_genesis_code(code, filename="v1.1.0-genesis-code.cpp"):
    """Save generated C++ code to file"""
    with open(filename, 'w') as f:
        f.write(code)
    print(f"\n✓ Genesis block code saved to: {filename}")
    print(f"\nNext steps:")
    print(f"  1. Review the generated C++ code")
    print(f"  2. Insert into chainparams.cpp (CMainParams constructor)")
    print(f"  3. Uncomment the mining code to find nNonce and genesis hash")
    print(f"  4. Recompile ammocoind")
    print(f"  5. Run once to mine genesis, then remove mining code")
    print(f"  6. Set final nNonce and hashGenesisBlock values")
    print(f"  7. Recompile and test")

def generate_balance_summary(snapshot):
    """Generate a human-readable summary of the snapshot"""
    balances = snapshot.get("balances", {})
    snapshot_info = snapshot.get("snapshot_info", {})

    total_supply = Decimal(snapshot_info.get("total_supply", "0"))
    sorted_balances = sorted(balances.items(), key=lambda x: Decimal(x[1]), reverse=True)

    summary = []
    summary.append("=" * 70)
    summary.append("AMMOcoin v1.0 → v1.1.0 Migration Balance Summary")
    summary.append("=" * 70)
    summary.append(f"\nSnapshot Info:")
    summary.append(f"  Timestamp: {snapshot_info.get('timestamp', 'unknown')}")
    summary.append(f"  Block Height: {snapshot_info.get('block_height', 0)}")
    summary.append(f"  Block Hash: {snapshot_info.get('block_hash', 'unknown')}")
    summary.append(f"  Network: {snapshot_info.get('network', 'unknown')}")
    summary.append(f"\nBalance Statistics:")
    summary.append(f"  Total Addresses: {len(balances)}")
    summary.append(f"  Total Supply: {total_supply} AMMO")

    if balances:
        avg_balance = total_supply / len(balances)
        summary.append(f"  Average Balance: {avg_balance:.8f} AMMO")
        summary.append(f"  Largest Balance: {Decimal(sorted_balances[0][1]):.8f} AMMO")
        summary.append(f"  Smallest Balance: {Decimal(sorted_balances[-1][1]):.8f} AMMO")

    summary.append(f"\nTop 10 Holders:")
    for i, (addr, bal) in enumerate(sorted_balances[:10], 1):
        percentage = (Decimal(bal) / total_supply * 100) if total_supply > 0 else 0
        summary.append(f"  {i:2d}. {addr[:20]}...{addr[-10:]} : {Decimal(bal):>20.8f} AMMO ({percentage:>6.2f}%)")

    return "\n".join(summary)

def main():
    """Main entry point"""
    if len(sys.argv) > 1:
        snapshot_file = sys.argv[1]
    else:
        snapshot_file = "v1.0-balance-snapshot.json"

    print(f"Loading snapshot from: {snapshot_file}")
    snapshot = load_snapshot(snapshot_file)

    if not snapshot:
        return 1

    # Generate and display summary
    summary = generate_balance_summary(snapshot)
    print(summary)

    # Save summary to file
    with open("v1.1.0-migration-summary.txt", 'w') as f:
        f.write(summary)
    print(f"\n✓ Summary saved to: v1.1.0-migration-summary.txt")

    # Generate genesis code
    code = generate_genesis_code(snapshot)

    if not code:
        return 1

    # Save genesis code
    save_genesis_code(code)

    print("\n✓ Genesis block generator completed successfully!")
    return 0

if __name__ == "__main__":
    sys.exit(main())

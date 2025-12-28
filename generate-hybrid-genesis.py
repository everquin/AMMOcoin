#!/usr/bin/env python3
"""
AMMOcoin v1.1.0 Hybrid Genesis Block Generator
Creates genesis with top holders + migration fund for remaining addresses
"""

import json
import sys
from decimal import Decimal
from datetime import datetime

def load_snapshot(filename="v1.0-complete-balance-snapshot.json"):
    """Load v1.0 balance snapshot"""
    with open(filename, 'r') as f:
        return json.load(f)

def generate_hybrid_genesis(snapshot, top_n=61):
    """
    Generate genesis block with:
    - Top N addresses (largest holders)
    - One migration fund address for remaining supply
    """

    balances = {addr: Decimal(bal) for addr, bal in snapshot['balances'].items()}
    snapshot_info = snapshot['snapshot_info']

    # Sort by balance
    sorted_balances = sorted(balances.items(), key=lambda x: x[1], reverse=True)

    # Split into top holders and small holders
    top_holders = dict(sorted_balances[:top_n])
    remaining_holders = dict(sorted_balances[top_n:])

    top_supply = sum(top_holders.values())
    remaining_supply = sum(remaining_holders.values())
    total_supply = sum(balances.values())

    print("=" * 70)
    print("AMMOcoin v1.1.0 Hybrid Genesis Block Generator")
    print("=" * 70)
    print(f"\nSnapshot Info:")
    print(f"  v1.0 Block Height: {snapshot_info['block_height']}")
    print(f"  v1.0 Block Hash: {snapshot_info['block_hash']}")
    print(f"  Total Addresses: {len(balances):,}")
    print(f"  Total Supply: {total_supply:,.8f} AMMO")
    print()
    print(f"Genesis Distribution:")
    print(f"  Top {top_n} addresses: {len(top_holders):,} addresses = {top_supply:,.8f} AMMO ({top_supply/total_supply*100:.2f}%)")
    print(f"  Migration Fund: {len(remaining_holders):,} addresses = {remaining_supply:,.8f} AMMO ({remaining_supply/total_supply*100:.2f}%)")
    print()

    # Generate C++ code
    cpp_lines = []

    # Header
    cpp_lines.append("// AMMOcoin v1.1.0 Genesis Block - Hybrid Migration")
    cpp_lines.append(f"// Snapshot: v1.0 block {snapshot_info['block_height']} ({snapshot_info['block_hash'][:16]}...)")
    cpp_lines.append(f"// Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S UTC')}")
    cpp_lines.append(f"// Top {top_n} holders: {top_supply:,.2f} AMMO ({top_supply/total_supply*100:.1f}%)")
    cpp_lines.append(f"// Migration fund: {remaining_supply:,.2f} AMMO ({remaining_supply/total_supply*100:.1f}%) for {len(remaining_holders):,} addresses")
    cpp_lines.append("")

    # Genesis transaction setup
    cpp_lines.append("const char* pszTimestamp = \"AMMOcoin v1.1.0 Genesis - June 2021 - Privacy Enhanced\";")
    cpp_lines.append("CMutableTransaction txNew;")
    cpp_lines.append("txNew.nTime = 1623089845;")
    cpp_lines.append("txNew.vin.resize(1);")
    cpp_lines.append(f"txNew.vout.resize({top_n + 1});  // {top_n} top holders + 1 migration fund")
    cpp_lines.append("")
    cpp_lines.append("// Genesis input")
    cpp_lines.append("txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4)")
    cpp_lines.append("    << vector<unsigned char>((const unsigned char*)pszTimestamp,")
    cpp_lines.append("                              (const unsigned char*)pszTimestamp + strlen(pszTimestamp));")
    cpp_lines.append("")

    # Top holders
    cpp_lines.append(f"// === TOP {top_n} HOLDERS ({top_supply:,.2f} AMMO - {top_supply/total_supply*100:.1f}%) ===")
    cpp_lines.append("")

    for idx, (address, balance) in enumerate(top_holders.items()):
        cpp_lines.append(f"// Rank {idx + 1}: {address} = {balance:,.8f} AMMO")
        cpp_lines.append(f"txNew.vout[{idx}].nValue = {int(balance * Decimal('100000000'))}LL;  // {balance} AMMO")
        cpp_lines.append(f"txNew.vout[{idx}].scriptPubKey = GetScriptForDestination(DecodeDestination(\"{address}\"));")
        cpp_lines.append("")

    # Migration fund
    migration_idx = top_n
    migration_address = "MIGRATION_FUND_ADDRESS_TO_BE_GENERATED"  # Placeholder
    cpp_lines.append(f"// === MIGRATION FUND ({remaining_supply:,.2f} AMMO - {remaining_supply/total_supply*100:.1f}%) ===")
    cpp_lines.append(f"// Covers {len(remaining_holders):,} remaining addresses")
    cpp_lines.append(f"// Address range: {Decimal(sorted_balances[-1][1]):,.8f} to {Decimal(sorted_balances[top_n][1]):,.8f} AMMO")
    cpp_lines.append(f"txNew.vout[{migration_idx}].nValue = {int(remaining_supply * Decimal('100000000'))}LL;  // {remaining_supply} AMMO")
    cpp_lines.append(f"txNew.vout[{migration_idx}].scriptPubKey = GetScriptForDestination(DecodeDestination(\"{migration_address}\"));")
    cpp_lines.append("")

    # Genesis block construction
    cpp_lines.append("// Build genesis block")
    cpp_lines.append("genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));")
    cpp_lines.append("genesis.hashPrevBlock.SetNull();")
    cpp_lines.append("genesis.nVersion = 1;")
    cpp_lines.append("genesis.nTime = 1623089845;")
    cpp_lines.append("genesis.nBits = 0x1e0ffff0;")
    cpp_lines.append("genesis.nNonce = 0;  // TO BE MINED")
    cpp_lines.append("")
    cpp_lines.append("genesis.hashMerkleRoot = BlockMerkleRoot(genesis);")
    cpp_lines.append("")
    cpp_lines.append("// Mine genesis: uncomment to find nNonce")
    cpp_lines.append("/*")
    cpp_lines.append("printf(\"Mining genesis block...\\n\");")
    cpp_lines.append("while (UintToArith256(genesis.GetHash()) > UintToArith256(consensus.powLimit)) {")
    cpp_lines.append("    genesis.nNonce++;")
    cpp_lines.append("    if (genesis.nNonce % 100000 == 0)")
    cpp_lines.append("        printf(\"nNonce: %u\\n\", genesis.nNonce);")
    cpp_lines.append("}")
    cpp_lines.append("printf(\"\\nGenesis mined!\\n\");")
    cpp_lines.append("printf(\"nNonce: %u\\n\", genesis.nNonce);")
    cpp_lines.append("printf(\"Hash: %s\\n\", genesis.GetHash().ToString().c_str());")
    cpp_lines.append("printf(\"Merkle: %s\\n\", genesis.hashMerkleRoot.ToString().c_str());")
    cpp_lines.append("*/")
    cpp_lines.append("")
    cpp_lines.append("// After mining, update these values:")
    cpp_lines.append("// genesis.nNonce = XXXXX;")
    cpp_lines.append("// hashGenesisBlock = genesis.GetHash();")
    cpp_lines.append("// assert(hashGenesisBlock == uint256S(\"0x...\"));")
    cpp_lines.append("// assert(genesis.hashMerkleRoot == uint256S(\"0x...\"));")

    return "\n".join(cpp_lines), top_holders, remaining_holders

def save_migration_data(top_holders, remaining_holders):
    """Save data for migration fund verification"""

    # Save top holders list
    top_list = []
    for idx, (addr, bal) in enumerate(sorted(top_holders.items(),
                                             key=lambda x: x[1], reverse=True), 1):
        top_list.append({
            "rank": idx,
            "address": addr,
            "balance": str(bal)
        })

    with open("genesis-top-holders.json", 'w') as f:
        json.dump({
            "count": len(top_list),
            "total_supply": str(sum(top_holders.values())),
            "addresses": top_list
        }, f, indent=2)

    print(f"✓ Top holders list saved to: genesis-top-holders.json")

    # Save migration fund addresses
    migration_list = []
    for addr, bal in sorted(remaining_holders.items(),
                           key=lambda x: x[1], reverse=True):
        migration_list.append({
            "address": addr,
            "balance": str(bal)
        })

    with open("migration-fund-claims.json", 'w') as f:
        json.dump({
            "count": len(migration_list),
            "total_supply": str(sum(remaining_holders.values())),
            "addresses": migration_list
        }, f, indent=2)

    print(f"✓ Migration fund claims saved to: migration-fund-claims.json")

    # Generate migration statistics
    stats = []
    stats.append("=" * 70)
    stats.append("AMMOcoin v1.1.0 Migration Fund Statistics")
    stats.append("=" * 70)
    stats.append("")
    stats.append(f"Top Holders (in genesis):")
    stats.append(f"  Addresses: {len(top_holders):,}")
    stats.append(f"  Supply: {sum(top_holders.values()):,.8f} AMMO")
    stats.append(f"  Percentage: {sum(top_holders.values()) / (sum(top_holders.values()) + sum(remaining_holders.values())) * 100:.2f}%")
    stats.append("")
    stats.append(f"Migration Fund (claim required):")
    stats.append(f"  Addresses: {len(remaining_holders):,}")
    stats.append(f"  Supply: {sum(remaining_holders.values()):,.8f} AMMO")
    stats.append(f"  Percentage: {sum(remaining_holders.values()) / (sum(top_holders.values()) + sum(remaining_holders.values())) * 100:.2f}%")
    stats.append("")

    # Balance distribution
    balances_sorted = sorted(remaining_holders.values(), reverse=True)
    stats.append(f"Migration Fund Distribution:")
    stats.append(f"  Largest claim: {balances_sorted[0]:,.8f} AMMO")
    stats.append(f"  Median claim: {balances_sorted[len(balances_sorted)//2]:,.8f} AMMO")
    stats.append(f"  Smallest claim: {balances_sorted[-1]:,.8f} AMMO")
    stats.append(f"  Average claim: {sum(remaining_holders.values()) / len(remaining_holders):,.8f} AMMO")

    stats_text = "\n".join(stats)
    print("\n" + stats_text)

    with open("migration-statistics.txt", 'w') as f:
        f.write(stats_text)

    print(f"\n✓ Statistics saved to: migration-statistics.txt")

def main():
    snapshot_file = "v1.0-complete-balance-snapshot.json"

    print(f"Loading snapshot from: {snapshot_file}\n")
    snapshot = load_snapshot(snapshot_file)

    # Generate genesis with top 61 addresses
    genesis_code, top_holders, remaining_holders = generate_hybrid_genesis(snapshot, top_n=61)

    # Save genesis code
    with open("v1.1.0-hybrid-genesis.cpp", 'w') as f:
        f.write(genesis_code)

    print(f"\n✓ Genesis code saved to: v1.1.0-hybrid-genesis.cpp")
    print(f"  Lines of code: {len(genesis_code.splitlines())}")
    print(f"  Genesis outputs: 62 (61 holders + 1 migration fund)")

    # Save migration data
    save_migration_data(top_holders, remaining_holders)

    print("\n" + "=" * 70)
    print("Next Steps:")
    print("=" * 70)
    print("1. Generate migration fund address:")
    print("   ammocoind -daemon")
    print("   ammocoin-cli getnewaddress 'Migration Fund'")
    print("   ammocoin-cli dumpprivkey <address>  # SAVE THIS SECURELY!")
    print("")
    print("2. Update genesis code with migration fund address")
    print("   Replace MIGRATION_FUND_ADDRESS_TO_BE_GENERATED")
    print("")
    print("3. Insert genesis code into chainparams.cpp")
    print("   File: ammocoin-source/src/chainparams.cpp")
    print("   Location: CMainParams() constructor")
    print("")
    print("4. Compile and mine genesis:")
    print("   cd ammocoin-source")
    print("   make clean && make -j8")
    print("   ./src/ammocoind -printtoconsole  # Will mine genesis")
    print("")
    print("5. Update genesis with mined values")
    print("6. Recompile and test")
    print("7. Build cross-platform binaries")
    print("=" * 70)

    return 0

if __name__ == "__main__":
    sys.exit(main())

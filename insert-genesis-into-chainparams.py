#!/usr/bin/env python3
"""
Insert hybrid genesis block into chainparams.cpp
"""

import re
import shutil
from pathlib import Path

def main():
    chainparams_path = Path("ammocoin-source/src/chainparams.cpp")
    genesis_path = Path("v1.1.0-hybrid-genesis.cpp")
    backup_path = Path("ammocoin-source/src/chainparams.cpp.backup")

    # Read files
    print(f"Reading {chainparams_path}...")
    with open(chainparams_path, 'r') as f:
        chainparams = f.read()

    print(f"Reading {genesis_path}...")
    with open(genesis_path, 'r') as f:
        genesis_code = f.read()

    # Backup original
    print(f"Creating backup at {backup_path}...")
    shutil.copy(chainparams_path, backup_path)

    # Extract just the transaction construction from genesis code
    # Remove the "Build genesis block" section and everything after
    genesis_tx_lines = []
    for line in genesis_code.split('\n'):
        if '// Build genesis block' in line:
            break
        if line.startswith('//') or line.strip() == '':
            genesis_tx_lines.append('        ' + line)  # Add indentation
        elif line.strip():
            genesis_tx_lines.append('        ' + line)

    genesis_tx_code = '\n'.join(genesis_tx_lines)

    # Find the section to replace in chainparams.cpp
    # We want to replace from "const char* pszTimestamp" to "genesis.vtx.push_back(txNew);"

    # Pattern to match the old genesis transaction
    old_pattern = r'([ ]*const char\* pszTimestamp = .*?\n.*?genesis\.vtx\.push_back\(txNew\);)'

    # The replacement includes our transaction code plus the push_back line
    replacement = genesis_tx_code + '\n        genesis.vtx.push_back(txNew);'

    # Perform replacement
    new_chainparams = re.sub(old_pattern, replacement, chainparams, flags=re.DOTALL)

    if new_chainparams == chainparams:
        print("ERROR: Could not find genesis transaction section to replace!")
        print("Pattern not matched. Manual insertion required.")
        return 1

    # Now update the genesis block parameters
    # Change nNonce to 0 and comment out the assertions
    new_chainparams = re.sub(
        r'genesis\.nNonce = \d+;',
        'genesis.nNonce = 0;  // TO BE MINED',
        new_chainparams
    )

    # Comment out the hash assertions
    new_chainparams = re.sub(
        r'(\s+)(assert\(hashGenesisBlock.*?\);)',
        r'\1// \2  // Uncomment after mining',
        new_chainparams
    )
    new_chainparams = re.sub(
        r'(\s+)(assert\(genesis\.hashMerkleRoot.*?\);)',
        r'\1// \2  // Uncomment after mining',
        new_chainparams
    )

    # Write the new file
    print(f"Writing updated {chainparams_path}...")
    with open(chainparams_path, 'w') as f:
        f.write(new_chainparams)

    print("\n✓ Genesis block successfully inserted into chainparams.cpp!")
    print(f"✓ Backup saved to: {backup_path}")
    print("\nNext steps:")
    print("1. Review the changes:")
    print(f"   diff {backup_path} {chainparams_path} | head -50")
    print("2. Compile the code:")
    print("   cd ammocoin-source && make clean && make -j8")
    print("3. Mine the genesis block (see instructions)")

    return 0

if __name__ == "__main__":
    exit(main())

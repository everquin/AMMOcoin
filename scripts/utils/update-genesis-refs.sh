#!/bin/bash
# update-genesis-refs.sh
# Automated script to replace old/broken genesis hashes with correct v1.1.0 genesis

OLD_V10="000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845"
OLD_BROKEN="0000075a4b9573ee2b4401c0ae785fb451d8355c91b6ed7d7a3420fe590cad58"
OLD_1000AMMO="00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434"
OLD_250M_NOPK="00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162"
NEW_CORRECT="000005cb7068246016a7cc43aedde75eee3de551f24afca2b0dc28cfc4fb3329"

echo "========================================="
echo "AMMOcoin v1.1.0 Genesis Hash Update Script"
echo "========================================="
echo ""
echo "OLD v1.0 genesis:        $OLD_V10"
echo "OLD BROKEN v1.1.0:       $OLD_BROKEN"
echo "OLD 1000 AMMO genesis:   $OLD_1000AMMO"
echo "OLD 250M (no PK) genesis: $OLD_250M_NOPK"
echo "CORRECT v1.1.0 genesis:  $NEW_CORRECT (250M premine, Option 2.5)"
echo ""

# Count files that will be updated
echo "Scanning for files to update..."
MD_COUNT=$(find . -name "*.md" -type f -not -path "./.git/*" -not -path "./source/target/*" | xargs grep -l "$OLD_V10\|$OLD_BROKEN\|$OLD_1000AMMO\|$OLD_250M_NOPK" 2>/dev/null | wc -l)
SH_COUNT=$(find ./scripts -name "*.sh" -type f 2>/dev/null | xargs grep -l "$OLD_V10\|$OLD_BROKEN\|$OLD_1000AMMO\|$OLD_250M_NOPK" 2>/dev/null | wc -l)

echo "Found $MD_COUNT markdown files to update"
echo "Found $SH_COUNT shell scripts to update"
echo ""

# Update .md files
echo "Updating .md files..."
find . -name "*.md" -type f -not -path "./.git/*" -not -path "./source/target/*" -not -path "./V1.1.0_GENESIS_BLOCK_AUTHORITY.md" -print0 | while IFS= read -r -d '' file; do
    if grep -q "$OLD_V10\|$OLD_BROKEN\|$OLD_1000AMMO\|$OLD_250M_NOPK" "$file" 2>/dev/null; then
        echo "  Updating: $file"
        sed -i '' "s/$OLD_V10/$NEW_CORRECT/g" "$file"
        sed -i '' "s/$OLD_BROKEN/$NEW_CORRECT/g" "$file"
        sed -i '' "s/$OLD_1000AMMO/$NEW_CORRECT/g" "$file"
        sed -i '' "s/$OLD_250M_NOPK/$NEW_CORRECT/g" "$file"
    fi
done

# Update shell scripts
echo ""
echo "Updating shell scripts..."
find ./scripts -name "*.sh" -type f -print0 2>/dev/null | while IFS= read -r -d '' file; do
    if grep -q "$OLD_V10\|$OLD_BROKEN\|$OLD_1000AMMO\|$OLD_250M_NOPK" "$file" 2>/dev/null; then
        echo "  Updating: $file"
        sed -i '' "s/$OLD_V10/$NEW_CORRECT/g" "$file"
        sed -i '' "s/$OLD_BROKEN/$NEW_CORRECT/g" "$file"
        sed -i '' "s/$OLD_1000AMMO/$NEW_CORRECT/g" "$file"
        sed -i '' "s/$OLD_250M_NOPK/$NEW_CORRECT/g" "$file"
    fi
done

echo ""
echo "========================================="
echo "Update complete!"
echo "========================================="
echo ""
echo "Verifying no old hashes remain..."
REMAINING=$(grep -r "$OLD_V10\|$OLD_BROKEN\|$OLD_1000AMMO\|$OLD_250M_NOPK" --include="*.md" --include="*.sh" --exclude-dir=".git" --exclude-dir="target" --exclude="V1.1.0_GENESIS_BLOCK_AUTHORITY.md" . 2>/dev/null | wc -l)

if [ "$REMAINING" -eq 0 ]; then
    echo "✅ SUCCESS: No old genesis hashes found!"
else
    echo "⚠️  WARNING: $REMAINING occurrences of old hashes still found"
    echo "Run the following to see them:"
    echo "  grep -r '$OLD_V10\|$OLD_BROKEN\|$OLD_1000AMMO\|$OLD_250M_NOPK' --include='*.md' --include='*.sh' --exclude-dir='.git' --exclude-dir='target' --exclude='V1.1.0_GENESIS_BLOCK_AUTHORITY.md' ."
fi

echo ""
echo "All files have been updated with correct v1.1.0 genesis hash (Option 2.5):"
echo "$NEW_CORRECT"
echo ""
echo "This is the 250M AMMO distribution premine genesis for manual v1.0 user migration."

#!/bin/bash
# update-genesis-refs.sh
# Automated script to replace old/broken genesis hashes with correct v1.1.0 genesis

OLD_V10="000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845"
OLD_BROKEN="0000075a4b9573ee2b4401c0ae785fb451d8355c91b6ed7d7a3420fe590cad58"
NEW_CORRECT="00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434"

echo "========================================="
echo "AMMOcoin v1.1.0 Genesis Hash Update Script"
echo "========================================="
echo ""
echo "OLD v1.0 genesis:        $OLD_V10"
echo "BROKEN v1.1.0 genesis:   $OLD_BROKEN"
echo "CORRECT v1.1.0 genesis:  $NEW_CORRECT"
echo ""

# Count files that will be updated
echo "Scanning for files to update..."
MD_COUNT=$(find . -name "*.md" -type f -not -path "./.git/*" -not -path "./ammocoin-apps-from-ammocoin/target/*" | xargs grep -l "$OLD_V10\|$OLD_BROKEN" 2>/dev/null | wc -l)
SH_COUNT=$(find ./scripts -name "*.sh" -type f 2>/dev/null | xargs grep -l "$OLD_V10\|$OLD_BROKEN" 2>/dev/null | wc -l)

echo "Found $MD_COUNT markdown files to update"
echo "Found $SH_COUNT shell scripts to update"
echo ""

# Update .md files
echo "Updating .md files..."
find . -name "*.md" -type f -not -path "./.git/*" -not -path "./ammocoin-apps-from-ammocoin/target/*" -print0 | while IFS= read -r -d '' file; do
    if grep -q "$OLD_V10\|$OLD_BROKEN" "$file" 2>/dev/null; then
        echo "  Updating: $file"
        sed -i '' "s/$OLD_V10/$NEW_CORRECT/g" "$file"
        sed -i '' "s/$OLD_BROKEN/$NEW_CORRECT/g" "$file"
    fi
done

# Update shell scripts
echo ""
echo "Updating shell scripts..."
find ./scripts -name "*.sh" -type f -print0 2>/dev/null | while IFS= read -r -d '' file; do
    if grep -q "$OLD_V10\|$OLD_BROKEN" "$file" 2>/dev/null; then
        echo "  Updating: $file"
        sed -i '' "s/$OLD_V10/$NEW_CORRECT/g" "$file"
        sed -i '' "s/$OLD_BROKEN/$NEW_CORRECT/g" "$file"
    fi
done

echo ""
echo "========================================="
echo "Update complete!"
echo "========================================="
echo ""
echo "Verifying no old hashes remain..."
REMAINING=$(grep -r "$OLD_V10\|$OLD_BROKEN" --include="*.md" --include="*.sh" --exclude-dir=".git" --exclude-dir="target" . 2>/dev/null | wc -l)

if [ "$REMAINING" -eq 0 ]; then
    echo "✅ SUCCESS: No old genesis hashes found!"
else
    echo "⚠️  WARNING: $REMAINING occurrences of old hashes still found"
    echo "Run the following to see them:"
    echo "  grep -r '$OLD_V10\|$OLD_BROKEN' --include='*.md' --include='*.sh' --exclude-dir='.git' --exclude-dir='target' ."
fi

echo ""
echo "All files have been updated with correct v1.1.0 genesis hash:"
echo "$NEW_CORRECT"

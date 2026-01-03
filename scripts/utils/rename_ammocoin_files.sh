#!/bin/bash

# AMMOcoin Final Branding Sweep - Rename all PIVX files/folders
echo "🔧 AMMOcoin Final Branding Sweep"
echo "==============================="
echo "Renaming all files and folders with PIVX in their names..."

# Function to rename files
rename_files() {
    find . -name "*pivx*" -o -name "*PIVX*" | while read file; do
        if [ -f "$file" ] || [ -d "$file" ]; then
            # Create new name by replacing pivx/PIVX with ammocoin/AMMOcoin
            newfile=$(echo "$file" | sed 's/pivx/ammocoin/g' | sed 's/PIVX/AMMOcoin/g')

            if [ "$file" != "$newfile" ]; then
                # Create directory if it doesn't exist
                newdir=$(dirname "$newfile")
                if [ ! -d "$newdir" ]; then
                    mkdir -p "$newdir"
                fi

                echo "Renaming: $file -> $newfile"
                mv "$file" "$newfile"
            fi
        fi
    done
}

# Rename files (may need multiple passes due to directory structure)
echo "Pass 1: Renaming files..."
rename_files

echo "Pass 2: Final cleanup..."
rename_files

echo "Pass 3: Ensuring completion..."
rename_files

# Check if any PIVX files remain
remaining=$(find . -name "*pivx*" -o -name "*PIVX*" | wc -l)
echo ""
echo "✅ Branding sweep complete!"
echo "Files with PIVX names remaining: $remaining"

if [ $remaining -eq 0 ]; then
    echo "🎉 SUCCESS: All PIVX file/folder names have been updated to AMMOcoin!"
else
    echo "⚠️  Some files may need manual attention:"
    find . -name "*pivx*" -o -name "*PIVX*"
fi
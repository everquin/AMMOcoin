#!/bin/bash
# Cleanup script for /releases folder after GitHub Release is created
# This removes binary directories and keeps only archives and documentation

set -e

RELEASES_DIR="/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases"

cd "$RELEASES_DIR"

echo "🧹 Cleaning up releases folder..."
echo ""

# Remove binary directories (binaries are now on GitHub Releases)
echo "Removing binary directories..."

if [ -d "AMMOcoin-macOS-ARM64" ]; then
    rm -rf AMMOcoin-macOS-ARM64/
    echo "  ✅ Removed AMMOcoin-macOS-ARM64/"
fi

if [ -d "AMMOcoin-Windows-x86_64" ]; then
    rm -rf AMMOcoin-Windows-x86_64/
    echo "  ✅ Removed AMMOcoin-Windows-x86_64/"
fi

if [ -d "Windows-Binaries" ]; then
    rm -rf Windows-Binaries/
    echo "  ✅ Removed Windows-Binaries/"
fi

echo ""
echo "📦 Keeping archive files:"
ls -lh *.tar.gz *.zip 2>/dev/null | awk '{print "  " $9 " (" $5 ")"}'

echo ""
echo "📄 Keeping documentation:"
ls -lh *.md *.txt *.sh 2>/dev/null | awk '{print "  " $9 " (" $5 ")"}'

echo ""
echo "✅ Cleanup complete!"
echo ""
echo "Files remaining in /releases:"
ls -lh

echo ""
echo "Total disk space used:"
du -sh .

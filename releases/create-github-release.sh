#!/bin/bash
# AMMOcoin v1.1.0 GitHub Release Creation Script

set -e

RELEASE_TAG="v1.1.0"
RELEASE_NAME="AMMOcoin v1.1.0 - Multi-Platform Release"
RELEASE_DIR="/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases"

cd "$RELEASE_DIR"

echo "Creating GitHub release for AMMOcoin v1.1.0..."

# Create the release with notes from RELEASE_NOTES_v1.1.0.md
gh release create "$RELEASE_TAG" \
  --title "$RELEASE_NAME" \
  --notes-file RELEASE_NOTES_v1.1.0.md \
  --repo everquin/AMMOcoin \
  AMMOcoin-macOS-ARM64.tar.gz \
  AMMOcoin-macOS-ARM64.zip \
  AMMOcoin-Linux-x86_64.tar.gz \
  AMMOcoin-Windows-x86_64.tar.gz \
  AMMOcoin-Windows-x86_64.zip \
  AMMOcoin-ALL-PLATFORMS-CHECKSUMS.txt

echo ""
echo "✅ GitHub release created successfully!"
echo ""
echo "Release URL: https://github.com/everquin/AMMOcoin/releases/tag/$RELEASE_TAG"
echo ""
echo "Uploaded files:"
echo "  - AMMOcoin-macOS-ARM64.tar.gz (4.0 MB)"
echo "  - AMMOcoin-macOS-ARM64.zip (4.0 MB)"
echo "  - AMMOcoin-Linux-x86_64.tar.gz (112 MB)"
echo "  - AMMOcoin-Windows-x86_64.tar.gz (17 MB)"
echo "  - AMMOcoin-Windows-x86_64.zip (17 MB)"
echo "  - AMMOcoin-ALL-PLATFORMS-CHECKSUMS.txt"
echo ""

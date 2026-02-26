#!/bin/bash
# Download Linux binaries from Vultr VM
# Run this from your local terminal

VM_IP="48.141.194.140"
LOCAL_DIR="/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/binaries-linux-v1.1.0"

echo "Downloading Linux binaries from VM..."

# Create directory
mkdir -p "$LOCAL_DIR"

# Download all three binaries
scp root@$VM_IP:/opt/AMMOcoin/ammocoin-source/src/ammocoind "$LOCAL_DIR/"
scp root@$VM_IP:/opt/AMMOcoin/ammocoin-source/src/ammocoin-cli "$LOCAL_DIR/"
scp root@$VM_IP:/opt/AMMOcoin/ammocoin-source/src/ammocoin-tx "$LOCAL_DIR/"

echo ""
echo "Download complete! Verifying..."
ls -lh "$LOCAL_DIR/"

echo ""
echo "Checking binary versions..."
"$LOCAL_DIR/ammocoind" --version 2>/dev/null || echo "Binary downloaded (version check requires dependencies)"

echo ""
echo "Next: Run this script from Claude Code to package the binaries"

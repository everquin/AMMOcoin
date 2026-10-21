#!/bin/sh
# Set up the AMMOcoin wallet from this folder for the current user:
#   1. install/verify the Sapling parameters in ~/.ammocoin-params (downloads ~50 MB once)
#   2. add "AMMOcoin Wallet" to the application menu (~/.local/share/applications)
# Run it from the unpacked folder:  ./install-desktop.sh
set -e
HERE=$(cd "$(dirname "$0")" && pwd)
"$HERE/bin/ammocoin-fetch-params"

DATA=${XDG_DATA_HOME:-$HOME/.local/share}
mkdir -p "$DATA/applications" "$DATA/icons/hicolor/256x256/apps"
cp "$HERE/share/icons/hicolor/256x256/apps/ammocoin.png" "$DATA/icons/hicolor/256x256/apps/ammocoin.png"
sed "s|^Exec=ammocoin-qt|Exec=\"$HERE/bin/ammocoin-qt\"|" "$HERE/share/applications/ammocoin-qt.desktop" \
  > "$DATA/applications/ammocoin-qt.desktop"
command -v update-desktop-database >/dev/null 2>&1 && update-desktop-database "$DATA/applications" >/dev/null 2>&1 || true
echo "Added \"AMMOcoin Wallet\" to your applications menu. Start it from there or run: $HERE/bin/ammocoin-qt"

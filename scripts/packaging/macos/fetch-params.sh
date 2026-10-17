#!/bin/bash
# AMMOcoin - download and verify the Sapling zk-SNARK parameters (macOS).
# Only needed for the command-line ammocoind / ammocoin-qt run outside the app
# bundle: AMMOcoin-Qt.app already ships both files inside Contents/Resources.
#
# Usage: ./fetch-params.sh [target-dir]
#   default target: ~/Library/Application Support/AMMOcoinParams
set -euo pipefail

DIR="${1:-$HOME/Library/Application Support/AMMOcoinParams}"
BASE_URL="https://download.z.cash/downloads"

SPEND_NAME=sapling-spend.params
SPEND_SHA=8e48ffd23abb3a5fd9c5589204f32d9c31285a04b78096ba40a79b75677efc13
OUTPUT_NAME=sapling-output.params
OUTPUT_SHA=2f0ebbcbb9bb0bcffe95a397e7eba89c29eb4dde6191c339db88570e3f3fb0e4

mkdir -p "$DIR"

fetch() {
    local name="$1" sha="$2" dest="$DIR/$1"
    if [ -f "$dest" ]; then
        if [ "$(shasum -a 256 "$dest" | awk '{print $1}')" = "$sha" ]; then
            echo "OK      $dest (already present, checksum verified)"
            return 0
        fi
        echo "WARNING $dest exists but its checksum is wrong; re-downloading." >&2
    fi
    local tmp="$dest.part"
    echo "Fetching $name ..."
    curl --fail --location --retry 3 --progress-bar -o "$tmp" "$BASE_URL/$name"
    if [ "$(shasum -a 256 "$tmp" | awk '{print $1}')" != "$sha" ]; then
        rm -f "$tmp"
        echo "ERROR   checksum mismatch for $name - aborting." >&2
        exit 1
    fi
    mv -f "$tmp" "$dest"
    echo "OK      $dest"
}

fetch "$OUTPUT_NAME" "$OUTPUT_SHA"
fetch "$SPEND_NAME"  "$SPEND_SHA"
echo "Sapling parameters are ready in: $DIR"

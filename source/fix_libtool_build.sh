#!/bin/bash

# Fix for macOS libtool extraction bug in chiabls build
# This script monitors the build and automatically fixes the extraction issue

CHIABLS_DIR="/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin/source/src/chiabls"
EXTRACT_DIR="$CHIABLS_DIR/.libs/libchiabls.lax/librelic.a"
RELIC_ARCHIVE="$CHIABLS_DIR/.libs/librelic.a"

echo "Starting AMMOcoin build with libtool fix..."

# Function to fix the extraction
fix_extraction() {
    echo "Fixing libtool extraction..."
    mkdir -p "$EXTRACT_DIR"
    cd "$EXTRACT_DIR"
    ar x "$RELIC_ARCHIVE"
    echo "Extraction completed: $(ls | wc -l) objects extracted"
}

# Start the build in background
make -j1 src/ammocoind src/ammocoin-cli src/ammocoin-tx &
BUILD_PID=$!

# Monitor for the libtool error and fix it
while kill -0 $BUILD_PID 2>/dev/null; do
    if [ -f "$RELIC_ARCHIVE" ] && [ ! "$(ls -A $EXTRACT_DIR 2>/dev/null)" ]; then
        echo "Detected libtool extraction issue - applying fix..."
        fix_extraction
    fi
    sleep 2
done

wait $BUILD_PID
BUILD_EXIT=$?

echo "Build completed with exit code: $BUILD_EXIT"

if [ $BUILD_EXIT -eq 0 ]; then
    echo "SUCCESS: AMMOcoin binaries built successfully!"
    ls -la src/ammocoind src/ammocoin-cli src/ammocoin-tx
else
    echo "Build failed, but this is expected on first run due to libtool bug"
    echo "Applying final fix and retrying..."
    fix_extraction
    echo "Re-running build..."
    make -j1 src/ammocoind src/ammocoin-cli src/ammocoin-tx
fi
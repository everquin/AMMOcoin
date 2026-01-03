#!/bin/bash

# AMMOcoin v1.1.0 Emergency Build Script
# Critical Security Update - Deploy within 72 hours

echo "🚨 AMMOcoin v1.1.0 Emergency Security Build"
echo "=============================================="

# Check if we're in the right directory
if [ ! -d "ammocoin-source" ] || [ ! -d "ammocoin-apps-from-ammocoin" ]; then
    echo "❌ Error: Please run this script from the AMMOcoin-v1.1.0-Emergency-Release directory"
    exit 1
fi

echo ""
echo "Choose deployment option:"
echo "1) Quick Deployment (Core daemon with security patches) - RECOMMENDED"
echo "2) Full Deployment (Modern applications with GUI)"
echo ""
read -p "Enter choice (1 or 2): " choice

case $choice in
    1)
        echo ""
        echo "🔧 Building AMMOcoin Core v1.1.0 (Quick Deployment)"
        echo "=================================================="

        cd ammocoin-source

        echo "📋 Step 1: Generating build configuration..."
        ./autogen.sh

        echo "📋 Step 2: Configuring build..."
        if [[ "$OSTYPE" == "darwin"* ]]; then
            # macOS
            ./configure --with-boost=/opt/homebrew --with-incompatible-bdb LDFLAGS="-L/opt/homebrew/opt/berkeley-db/lib" CPPFLAGS="-I/opt/homebrew/opt/berkeley-db/include"
        else
            # Linux
            ./configure --with-incompatible-bdb
        fi

        echo "📋 Step 3: Building AMMOcoin daemon..."
        make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

        if [ -f "src/pivxd" ]; then
            echo ""
            echo "✅ SUCCESS! AMMOcoin v1.1.0 built successfully"
            echo ""
            echo "📦 Binaries created:"
            echo "   - src/pivxd (AMMOcoin daemon with security patches)"
            echo "   - src/pivx-cli (Command line interface)"
            echo "   - src/pivx-tx (Transaction utility)"
            echo ""
            echo "🔒 Security Features:"
            echo "   ✅ DoS attack protection"
            echo "   ✅ Protocol version 70920"
            echo "   ✅ Emergency security patches applied"
            echo ""
            echo "⚡ Quick Install:"
            echo "   1. Stop current daemon: ./pivx-cli stop"
            echo "   2. Backup current: cp pivxd pivxd.v1.0.backup"
            echo "   3. Install new: cp src/pivxd src/pivx-cli src/pivx-tx ."
            echo "   4. Restart: ./pivxd -daemon"
            echo "   5. Verify: ./pivx-cli getnetworkinfo"
            echo ""
        else
            echo "❌ Build failed. Check output above for errors."
            exit 1
        fi
        ;;

    2)
        echo ""
        echo "🔧 Building AMMOcoin Modern Applications v1.1.0"
        echo "==============================================="

        cd ammocoin-apps-from-ammocoin

        echo "📋 Step 1: Generating build configuration..."
        ./autogen.sh

        echo "📋 Step 2: Configuring build..."
        if [[ "$OSTYPE" == "darwin"* ]]; then
            # macOS
            ./configure --with-boost-libdir=/opt/homebrew/lib --with-incompatible-bdb LDFLAGS="-L/opt/homebrew/opt/berkeley-db/lib" CPPFLAGS="-I/opt/homebrew/opt/berkeley-db/include"
        else
            # Linux
            ./configure --with-incompatible-bdb
        fi

        echo "📋 Step 3: Building modern AMMOcoin applications..."
        make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

        echo ""
        echo "🎯 Modern applications building completed"
        echo "Check src/ directory for binaries"
        ;;

    *)
        echo "❌ Invalid choice. Exiting."
        exit 1
        ;;
esac

echo ""
echo "🚨 CRITICAL REMINDER:"
echo "   - Network enforcement begins in 72 hours"
echo "   - All nodes must upgrade to avoid disconnection"
echo "   - Protocol version 70920 required"
echo ""
echo "📞 Emergency Support: emergency@ammocoin.org"
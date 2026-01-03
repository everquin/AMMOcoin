# AMMOcoin v1.1.0 Cross-Compilation Guide

Complete guide for building AMMOcoin binaries for all platforms from Linux.

## Prerequisites

All dependencies should be installed by running `BUILDME.sh` first.

## Platform 1: Linux Native (ARM64 & x86_64)

### ARM64 (Current System)
```bash
cd /media/psf/CRUCIAL_2TB/"  _GITHUB"/AMMOcoin/ammocoin-apps-from-ammocoin
./configure --prefix=/usr/local --enable-wallet --with-incompatible-bdb
make -j$(nproc)
```

### x86_64 Linux (via Gitian)
```bash
cd /media/psf/CRUCIAL_2TB/"  _GITHUB"/AMMOcoin/ammocoin-apps-from-ammocoin/contrib/gitian-descriptors
# Build using Gitian Docker
docker run -it --rm -v $(pwd):/build ubuntu:22.04 bash
# Inside container:
apt-get update && apt-get install -y git
git clone https://github.com/devrandom/gitian-builder
cd gitian-builder
./bin/make-base-vm --docker
# Build Linux
./bin/gbuild ../ammocoin-apps-from-ammocoin/contrib/gitian-descriptors/gitian-linux.yml
```

## Platform 2: Windows EXE (Cross-Compilation)

### Method 1: Using depends system (Recommended)
```bash
cd /media/psf/CRUCIAL_2TB/"  _GITHUB"/AMMOcoin/ammocoin-apps-from-ammocoin

# Install Windows cross-compilation tools
sudo apt-get install -y \
    g++-mingw-w64-x86-64 \
    mingw-w64-x86-64-dev \
    nsis

# Build Windows dependencies
cd depends
make HOST=x86_64-w64-mingw32 -j$(nproc)
cd ..

# Configure for Windows
./configure \
    --prefix=`pwd`/depends/x86_64-w64-mingw32 \
    --enable-wallet \
    --with-incompatible-bdb \
    --disable-online-rust

# Build Windows binaries
make -j$(nproc)

# Binaries will be in src/ as:
# - ammocoind.exe
# - ammocoin-cli.exe
# - ammocoin-tx.exe
```

### Method 2: Using Gitian (Deterministic Builds)
```bash
cd /media/psf/CRUCIAL_2TB/"  _GITHUB"/AMMOcoin

# Build using Gitian
docker run -it --rm -v $(pwd):/build ubuntu:22.04 bash

# Inside container, follow Gitian Windows descriptor
./contrib/gitian-descriptors/gitian-win.yml
```

### Method 3: Docker Build (Easiest)
```bash
# Create Windows build Dockerfile
docker build -f Dockerfile.windows -t ammocoin-windows-builder .
docker run --rm -v $(pwd)/windows-binaries:/output ammocoin-windows-builder
```

**Output**: Windows binaries in `windows-binaries-v1.1.0/`

## Platform 3: macOS DMG (Cross-Compilation)

### Method 1: Using OSXCross (Linux → macOS)

#### Step 1: Install OSXCross
```bash
cd /tmp
git clone https://github.com/tpoechtrager/osxcross
cd osxcross

# Download macOS SDK (requires MacOSX SDK .tar.xz file)
# Place MacOSX11.3.sdk.tar.xz (or similar) in tarballs/

# Build OSXCross
UNATTENDED=1 ./build.sh

# Add to PATH
export PATH="/tmp/osxcross/target/bin:$PATH"
```

#### Step 2: Build macOS dependencies
```bash
cd /media/psf/CRUCIAL_2TB/"  _GITHUB"/AMMOcoin/ammocoin-apps-from-ammocoin/depends

# Build for macOS
make HOST=x86_64-apple-darwin19 -j$(nproc)
```

#### Step 3: Configure and build
```bash
cd /media/psf/CRUCIAL_2TB/"  _GITHUB"/AMMOcoin/ammocoin-apps-from-ammocoin

./configure \
    --prefix=`pwd`/depends/x86_64-apple-darwin19 \
    --enable-wallet \
    --with-incompatible-bdb \
    --disable-online-rust

make -j$(nproc)

# Create DMG
make deploy
```

### Method 2: Using Gitian (Deterministic)
```bash
cd /media/psf/CRUCIAL_2TB/"  _GITHUB"/AMMOcoin

# Use Gitian OSX descriptor
./contrib/gitian-descriptors/gitian-osx.yml
```

**Output**: macOS DMG in `osx-binaries-v1.1.0/`

### Method 3: Native macOS Build (Recommended for DMG)

Since you have access to macOS (the CRUCIAL_2TB volume), the cleanest approach for macOS binaries is to build natively on Mac:

```bash
# On your Mac:
cd "/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin"

# Install Xcode Command Line Tools
xcode-select --install

# Install Homebrew dependencies
brew install automake berkeley-db@4 libtool boost miniupnpc pkg-config python qt libevent qrencode libsodium gmp

# Configure
./autogen.sh
./configure \
    --with-boost=/opt/homebrew/opt/boost \
    --with-qrencode \
    --with-incompatible-bdb \
    LDFLAGS="-L/opt/homebrew/opt/berkeley-db@4/lib" \
    CPPFLAGS="-I/opt/homebrew/opt/berkeley-db@4/include"

# Build
make -j$(sysctl -n hw.ncpu)

# Create DMG
make deploy

# DMG will be in src/ as AMMOcoin-Qt.dmg
```

## Quick Reference: All Platform Builds

### Complete Build Matrix

| Platform | Architecture | Build Method | Output |
|----------|-------------|--------------|---------|
| Linux | ARM64 | Native | ammocoin{d,cli,tx} |
| Linux | x86_64 | Gitian/Docker | ammocoin{d,cli,tx} |
| Windows | x86_64 | MinGW Cross | ammocoin{d,cli,tx}.exe |
| macOS | x86_64 | Native/OSXCross | AMMOcoin-Qt.dmg |
| macOS | ARM64 (M1+) | Native | AMMOcoin-Qt.dmg |

## Automated Multi-Platform Build Script

```bash
#!/bin/bash
# Build all platforms

# 1. Linux ARM64 (native)
./configure --enable-wallet --with-incompatible-bdb
make -j$(nproc)
mv src/ammocoin* /output/linux-arm64/

# 2. Windows x86_64 (cross)
make distclean
cd depends && make HOST=x86_64-w64-mingw32 -j$(nproc) && cd ..
./configure --prefix=`pwd`/depends/x86_64-w64-mingw32
make -j$(nproc)
mv src/ammocoin*.exe /output/windows-x86_64/

# 3. Linux x86_64 (cross)
make distclean
cd depends && make HOST=x86_64-pc-linux-gnu -j$(nproc) && cd ..
./configure --prefix=`pwd`/depends/x86_64-pc-linux-gnu
make -j$(nproc)
mv src/ammocoin* /output/linux-x86_64/

echo "All binaries built successfully!"
```

## Troubleshooting

### Missing Dependencies
```bash
# Install all cross-compilation tools
sudo apt-get install -y \
    g++-mingw-w64-x86-64 \
    g++-aarch64-linux-gnu \
    g++-arm-linux-gnueabihf
```

### Berkeley DB Issues
```bash
# Use --with-incompatible-bdb flag
./configure --with-incompatible-bdb
```

### Rust/Sapling Issues
```bash
# Disable online Rust builds
./configure --disable-online-rust
```

## Next Steps

1. **Build Linux binaries**: Run `sudo bash BUILDME.sh`
2. **Build Windows EXE**: Follow Windows cross-compilation above
3. **Build macOS DMG**: Use native Mac build or OSXCross
4. **Package for release**: Create archives with version numbers
5. **Test on target platforms**: Deploy and verify functionality

## Build Output Structure

```
AMMOcoin-v1.1.0-binaries/
├── linux-arm64/
│   ├── ammocoind
│   ├── ammocoin-cli
│   └── ammocoin-tx
├── linux-x86_64/
│   ├── ammocoind
│   ├── ammocoin-cli
│   └── ammocoin-tx
├── windows-x86_64/
│   ├── ammocoind.exe
│   ├── ammocoin-cli.exe
│   └── ammocoin-tx.exe
└── macos/
    └── AMMOcoin-Qt.dmg
```

## Code Signing (Optional)

### Windows
```bash
osslsigncode sign -certs cert.pem -key key.pem \
    -n "AMMOcoin" -i https://ammocoin.org \
    -in ammocoind.exe -out ammocoind-signed.exe
```

### macOS
```bash
codesign --deep --force --verify --verbose \
    --sign "Developer ID Application: Your Name" \
    AMMOcoin-Qt.app
```

---

**Status**: Ready for cross-compilation after Linux native build completes.

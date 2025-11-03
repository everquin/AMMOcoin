# AMMOcoin v1.1.0 - Windows & macOS Build Instructions

## ✅ COMPLETED: Linux Build
All 3 Linux ARM64 binaries successfully built:
- ✅ `ammocoind` (243MB)
- ✅ `ammocoin-cli` (20MB)
- ✅ `ammocoin-tx` (34MB)

**Location**: `/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/linux-binaries-v1.1.0/`

---

## 🔄 PENDING: Windows & macOS Builds

Both builds require manual steps due to sudo/permission requirements.

---

# Phase 2: Windows Build (EXE Files)

## Prerequisites Required:
The Windows cross-compilation needs MinGW tools installed with sudo access.

## Step 1: Install MinGW Tools

Run this command in your Linux VM terminal:

```bash
sudo apt-get update && sudo apt-get install -y \
    g++-mingw-w64-x86-64 \
    mingw-w64-x86-64-dev \
    nsis \
    zip
```

**Time**: ~5 minutes
**Password**: Your parallels user sudo password will be required

## Step 2: Run Windows Build Script

After MinGW is installed, run:

```bash
cd "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin"
bash build-windows-cross.sh
```

**Duration**: 20-35 minutes
**Steps it performs**:
1. Builds Windows dependencies using depends system
2. Cross-compiles all source code for Windows x86_64
3. Creates three .exe files: `ammocoind.exe`, `ammocoin-cli.exe`, `ammocoin-tx.exe`
4. Strips debugging symbols to reduce size
5. Creates deployment ZIP package

**Expected Output**:
```
windows-binaries-v1.1.0/
├── ammocoind.exe
├── ammocoin-cli.exe
├── ammocoin-tx.exe
└── AMMOcoin-v1.1.0-Windows-x86_64.zip
```

---

# Phase 3: macOS Build (DMG Installer)

## Prerequisites Required:
**IMPORTANT**: This build **MUST** run on your Mac, not in the Linux VM.

## Step 1: Open Mac Terminal

On your Mac (not in Parallels VM), open Terminal.app and navigate to:

```bash
cd "/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin"
```

## Step 2: Install Homebrew (if not installed)

Check if Homebrew is installed:
```bash
brew --version
```

If not installed, install it:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## Step 3: Run macOS Build Script

```bash
bash build-macos-native.sh
```

**Duration**: 30-45 minutes
**Steps it performs**:
1. Installs all Homebrew dependencies (Berkeley DB, Qt5, Boost, Rust, etc.)
2. Configures build for macOS
3. Compiles all source code natively
4. Creates macOS application bundle (AMMOcoin-Qt.app)
5. Generates DMG installer
6. Copies command-line tools

**Expected Output**:
```
macos-binaries-v1.1.0/
├── AMMOcoin-Qt.app          (GUI application)
├── AMMOcoin-Qt.dmg          (Installer)
├── ammocoind                 (Daemon)
├── ammocoin-cli              (RPC client)
└── ammocoin-tx               (Transaction tool)
```

---

# Alternative: Manual Build Steps

If the automated scripts fail, here are the manual commands:

## Windows Manual Build:

```bash
# After installing MinGW tools:
cd "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin"

# Build Windows dependencies
cd depends
make HOST=x86_64-w64-mingw32 -j4
cd ..

# Configure for Windows
make distclean || true
./autogen.sh
CONFIG_SITE=$(pwd)/depends/x86_64-w64-mingw32/share/config.site \
./configure \
    --prefix=/ \
    --disable-ccache \
    --disable-maintainer-mode \
    --disable-dependency-tracking \
    --enable-reduce-exports \
    --disable-bench \
    --disable-gui-tests \
    --disable-online-rust

# Build Windows binaries
export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/parallels/.cargo/bin"
make -j4 V=1

# Package binaries
mkdir -p "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/windows-binaries-v1.1.0"
cp src/*.exe "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/windows-binaries-v1.1.0/"
```

## macOS Manual Build (on Mac):

```bash
cd "/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin"

# Install dependencies via Homebrew
brew install \
    automake \
    berkeley-db@4 \
    libtool \
    boost \
    miniupnpc \
    pkg-config \
    python \
    qt@5 \
    libevent \
    qrencode \
    libsodium \
    gmp \
    zeromq \
    protobuf

# Install Rust if needed
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source "$HOME/.cargo/env"

# Configure and build
make distclean || true
./autogen.sh
./configure \
    --prefix=/usr/local \
    --enable-wallet \
    --with-gui=qt5 \
    --with-qrencode \
    --with-incompatible-bdb \
    --disable-online-rust \
    LDFLAGS="-L/opt/homebrew/opt/berkeley-db@4/lib -L/opt/homebrew/lib" \
    CPPFLAGS="-I/opt/homebrew/opt/berkeley-db@4/include -I/opt/homebrew/include" \
    PKG_CONFIG_PATH="/opt/homebrew/opt/qt@5/lib/pkgconfig"

# Build (use all CPU cores)
make -j$(sysctl -n hw.ncpu) V=1

# Create DMG
make deploy

# Package binaries
mkdir -p "/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin/macos-binaries-v1.1.0"
cp src/ammocoind src/ammocoin-cli src/ammocoin-tx "/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin/macos-binaries-v1.1.0/"
cp -r AMMOcoin-Qt.app AMMOcoin-Qt.dmg "/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin/macos-binaries-v1.1.0/" || true
```

---

# Expected Final Output

After completing all builds, you will have:

```
/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/
│
├── linux-binaries-v1.1.0/          ✅ COMPLETE
│   ├── ammocoind          (243MB)
│   ├── ammocoin-cli        (20MB)
│   └── ammocoin-tx         (34MB)
│
├── windows-binaries-v1.1.0/        🔄 PENDING (requires MinGW install)
│   ├── ammocoind.exe
│   ├── ammocoin-cli.exe
│   ├── ammocoin-tx.exe
│   └── AMMOcoin-v1.1.0-Windows-x86_64.zip
│
└── macos-binaries-v1.1.0/          🔄 PENDING (requires Mac build)
    ├── AMMOcoin-Qt.app
    ├── AMMOcoin-Qt.dmg
    ├── ammocoind
    ├── ammocoin-cli
    └── ammocoin-tx
```

---

# Troubleshooting

## Windows Build Issues:

### Error: "mingw32-g++: command not found"
**Solution**: Install MinGW tools (Step 1 above)

### Error: "depends build fails"
**Solution**: The depends system builds all libraries from source. This can take 15-20 minutes. Be patient and check logs in `depends/work/*/` directories.

### Error: Rust compilation fails
**Solution**: Ensure Rust is installed and in PATH:
```bash
source "$HOME/.cargo/env"
rustc --version  # Should show version 1.83.0 or newer
```

## macOS Build Issues:

### Error: "Homebrew not found"
**Solution**: Install Homebrew first (Step 2 above)

### Error: "Qt5 not found"
**Solution**: Install Qt5 and set PKG_CONFIG_PATH:
```bash
brew install qt@5
export PKG_CONFIG_PATH="/opt/homebrew/opt/qt@5/lib/pkgconfig"
```

### Error: "Berkeley DB incompatible"
**Solution**: Use the `--with-incompatible-bdb` flag (already in script)

### Error: "make deploy fails"
**Solution**: Check that `macdeployqt` is available:
```bash
/opt/homebrew/opt/qt@5/bin/macdeployqt --version
```

---

# Verification Steps

## Test Windows Binaries (in Wine on Linux):

```bash
sudo apt-get install wine
wine "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/windows-binaries-v1.1.0/ammocoin-cli.exe" --version
```

## Test macOS Binaries (on Mac):

```bash
"/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin/macos-binaries-v1.1.0/ammocoind" --version
"/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin/macos-binaries-v1.1.0/ammocoin-cli" --version
open "/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin/macos-binaries-v1.1.0/AMMOcoin-Qt.app"
```

---

# Summary

| Platform | Status | Time | Requirements |
|----------|--------|------|--------------|
| **Linux ARM64** | ✅ Complete | ~6 hours | Done |
| **Windows x86_64** | 🔄 Ready | ~30 min | MinGW install + run script |
| **macOS Universal** | 🔄 Ready | ~40 min | Run on Mac + Homebrew |

**Total Build Time (all platforms)**: ~7-8 hours (including troubleshooting)

**Next Action**:
1. Install MinGW on Linux VM with sudo
2. Run `build-windows-cross.sh`
3. Switch to Mac and run `build-macos-native.sh`

---

## Build Scripts Ready at:
- **Linux**: ✅ Binaries already built in `linux-binaries-v1.1.0/`
- **Windows**: `build-windows-cross.sh` (ready to run after MinGW install)
- **macOS**: `build-macos-native.sh` (ready to run on Mac)

All Makefile.am fixes from Linux build are already applied and will work for Windows/Mac!

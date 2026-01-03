# AMMOcoin Cross-Platform Build System

This directory contains Docker-based cross-compilation infrastructure for building AMMOcoin binaries on multiple platforms from a single macOS development environment.

## Supported Platforms

| Platform | Architecture | Status | Output Files |
|----------|-------------|--------|--------------|
| **Linux x64** | Ubuntu 20.04 | ✅ Ready | `ammocoind`, `ammocoin-cli`, `ammocoin-tx` |
| **Windows x64** | MinGW cross-compile | ✅ Ready | `ammocoind.exe`, `ammocoin-cli.exe`, `ammocoin-tx.exe` |
| **ARM64/Raspberry Pi** | aarch64-linux | ✅ Ready | `ammocoind`, `ammocoin-cli`, `ammocoin-tx` |

## Quick Start

### Build All Platforms

```bash
# Build binaries for all supported platforms
./build-all-platforms.sh

# Output will be in ../releases/ directory
# - AMMOcoin-v1.1.0-linux-x64.zip
# - AMMOcoin-v1.1.0-windows-x64.zip
# - AMMOcoin-v1.1.0-arm64.zip
# - AMMOcoin-v1.1.0-MultiPlatform.zip
```

### Build Specific Platform

```bash
# Build only Linux x64
docker build -t ammocoin-build-linux -f Dockerfile.linux ../source
docker run --rm -v "$(pwd)/../releases:/output" ammocoin-build-linux

# Build only Windows x64
docker build -t ammocoin-build-windows -f Dockerfile.windows ../source
docker run --rm -v "$(pwd)/../releases:/output" ammocoin-build-windows

# Build only ARM64/Raspberry Pi
docker build -t ammocoin-build-arm64 -f Dockerfile.arm64 ../source
docker run --rm -v "$(pwd)/../releases:/output" ammocoin-build-arm64
```

## Prerequisites

### System Requirements
- **Docker**: Latest version installed and running
- **Source Code**: Complete AMMOcoin source in `../source/`
- **Disk Space**: ~2GB for Docker images and build cache
- **Memory**: 4GB+ RAM recommended for parallel builds

### Installation (macOS)
```bash
# Install Docker Desktop
brew install --cask docker

# Start Docker Desktop
open /Applications/Docker.app

# Verify Docker is running
docker --version
docker info
```

## Build Configuration

### Linux x64 (Dockerfile.linux)
- **Base**: Ubuntu 20.04
- **Compiler**: GCC 9.4+
- **Dependencies**: OpenSSL, Berkeley DB, Boost, libevent
- **Target**: x86_64-linux-gnu
- **Output**: Native Linux ELF binaries

### Windows x64 (Dockerfile.windows)
- **Base**: Ubuntu 20.04 with MinGW
- **Compiler**: MinGW-w64 cross-compiler
- **Dependencies**: Cross-compiled Windows libraries
- **Target**: x86_64-w64-mingw32
- **Output**: Windows PE executables (.exe)

### ARM64/Raspberry Pi (Dockerfile.arm64)
- **Base**: Ubuntu 20.04
- **Compiler**: GCC aarch64 cross-compiler
- **Dependencies**: ARM64 cross-compiled libraries
- **Target**: aarch64-linux-gnu
- **Output**: ARM64 ELF binaries

## Build Process

### 1. Docker Image Creation
Each Dockerfile creates a complete build environment with:
- Cross-compilation toolchain
- Required dependencies (OpenSSL, Berkeley DB, Boost)
- Build configuration and scripts
- AMMOcoin source code

### 2. Compilation
The build process:
1. Runs `make clean` to ensure fresh build
2. Configures with platform-specific settings
3. Compiles using `make -j$(nproc)` for parallel build
4. Installs binaries to `/build/{platform}/bin/`

### 3. Output Collection
- Binaries are copied to mounted output directory
- Platform-specific packages are created
- Version information and checksums are generated

## Output Structure

```
releases/
├── linux-x64/
│   ├── ammocoind
│   ├── ammocoin-cli
│   └── ammocoin-tx
├── windows-x64/
│   ├── ammocoind.exe
│   ├── ammocoin-cli.exe
│   └── ammocoin-tx.exe
├── arm64/
│   ├── ammocoind
│   ├── ammocoin-cli
│   └── ammocoin-tx
├── AMMOcoin-v1.1.0-linux-x64.zip
├── AMMOcoin-v1.1.0-windows-x64.zip
├── AMMOcoin-v1.1.0-arm64.zip
├── AMMOcoin-v1.1.0-MultiPlatform.zip
└── VERSION.txt
```

## Configuration Details

### Common Build Flags
- `--disable-tests`: Skip test suite compilation
- `--disable-bench`: Skip benchmark tools
- `--enable-wallet`: Include wallet functionality
- `--without-gui`: Command-line only (no Qt GUI)
- `--with-incompatible-bdb`: Use available Berkeley DB version

### Platform-Specific Settings

#### Linux
```bash
./configure \
    --disable-tests \
    --disable-bench \
    --enable-wallet \
    --without-gui \
    --without-miniupnpc \
    --prefix=/build/linux-x64
```

#### Windows
```bash
./configure \
    --host=x86_64-w64-mingw32 \
    --disable-tests \
    --disable-bench \
    --enable-wallet \
    --without-gui \
    --without-miniupnpc \
    --with-incompatible-bdb \
    --prefix=/build/windows-x64
```

#### ARM64
```bash
./configure \
    --host=aarch64-linux-gnu \
    --disable-tests \
    --disable-bench \
    --enable-wallet \
    --without-gui \
    --without-miniupnpc \
    --with-incompatible-bdb \
    --prefix=/build/arm64
```

## Testing Cross-Compiled Binaries

### Linux x64
```bash
# Test on Ubuntu/Debian system
chmod +x ammocoind ammocoin-cli ammocoin-tx
./ammocoind --version
./ammocoin-cli --version
```

### Windows x64
```bash
# Test on Windows 10/11
ammocoind.exe --version
ammocoin-cli.exe --version
```

### ARM64/Raspberry Pi
```bash
# Test on Raspberry Pi 4/5 with 64-bit OS
chmod +x ammocoind ammocoin-cli ammocoin-tx
./ammocoind --version
./ammocoin-cli --version
```

## Troubleshooting

### Docker Issues
```bash
# Check Docker status
docker info

# Clean Docker cache if build fails
docker system prune -a

# View build logs
docker build --no-cache -t test-build -f Dockerfile.linux ../source
```

### Build Failures
- Ensure source code is complete in `../source/`
- Check available disk space (builds require ~1GB temporary space)
- Verify Docker has sufficient memory allocation (4GB+ recommended)

### Missing Dependencies
The Dockerfiles include all required dependencies. If builds fail:
1. Check the Dockerfile for the specific platform
2. Ensure base Ubuntu image is accessible
3. Review build logs for specific error messages

## Customization

### Adding New Platforms
To add support for additional platforms:

1. Create new `Dockerfile.{platform}`
2. Install appropriate cross-compilation toolchain
3. Add build configuration in `build-all-platforms.sh`
4. Test compilation and binary execution

### Modifying Build Options
Edit the configure flags in each Dockerfile to change:
- GUI support (`--with-gui` / `--without-gui`)
- Wallet features (`--enable-wallet` / `--disable-wallet`)
- Network features (`--with-miniupnpc` / `--without-miniupnpc`)
- Testing (`--enable-tests` / `--disable-tests`)

## Performance Notes

### Build Times
- **Linux x64**: ~15-20 minutes
- **Windows x64**: ~20-25 minutes (cross-compilation overhead)
- **ARM64**: ~25-30 minutes (cross-compilation overhead)
- **Total (all platforms)**: ~45-60 minutes

### Optimization
- Use `docker build --cache-from` for faster rebuilds
- Parallel builds with `make -j$(nproc)` reduce compilation time
- Docker layer caching speeds up dependency installation

## Version Information

- **AMMOcoin Version**: v1.1.0
- **Docker Base**: Ubuntu 20.04 LTS
- **Build System**: GNU Autotools with cross-compilation
- **Supported Since**: October 2024

---

*This cross-compilation system enables AMMOcoin to be easily distributed across all major computing platforms while maintaining consistent build quality and security.*
# AMMOcoin Scripts

This directory contains all build, deployment, packaging, and utility scripts for AMMOcoin v1.1.0.

## Directory Structure

### `build/` - Build Scripts
Scripts for compiling AMMOcoin binaries across different platforms.

**Multi-Platform:**
- `build-all.sh` - Build for all supported platforms
- `BUILDME.sh` - Quick build script
- `EMERGENCY_BUILD.sh` - Emergency build with minimal dependencies

**Platform-Specific:**
- `build-macos-native.sh` - Build for macOS ARM64 (M1/M2/M3)
- `build-linux.sh` - Build for Linux x86_64
- `build-arm64.sh` - Build for ARM64 platforms
- `build-native-linux.sh` - Native Linux build
- `build-windows.sh` - Standard Windows cross-compilation
- `build-windows-cross.sh` - Windows cross-compilation alternative
- `build-windows-NOW.sh` - Quick Windows build

**Utilities:**
- `install-deps-and-build.sh` - Install dependencies and build

### `deployment/` - Deployment Scripts
Scripts for deploying and managing AMMOcoin nodes.

- `deploy-seed-node.sh` - Deploy a seed node
- `setup-seed-node.sh` - Setup and configure seed node
- `deploy-and-start-network.sh` - Deploy and start network
- `vultr-quick-build.sh` - Quick build on Vultr VPS

### `packaging/` - Packaging Scripts
Scripts for packaging and distributing binaries.

- `PACKAGE_LINUX_BINARIES.sh` - Package Linux binaries for release
- `DOWNLOAD_LINUX_BINARIES.sh` - Download pre-built Linux binaries

### `utils/` - Utility Scripts
Miscellaneous utility scripts for development and maintenance.

- `update-genesis-refs.sh` - Update genesis block references
- `rename_ammocoin_files.sh` - Rename AMMOcoin files
- `test-local-macos.sh` - Test local macOS node

---

## Usage Examples

### Building Binaries

**Build all platforms:**
```bash
./scripts/build/build-all.sh
```

**Build for macOS (native):**
```bash
./scripts/build/build-macos-native.sh
```

**Build for Linux:**
```bash
./scripts/build/build-linux.sh
```

**Build for Windows:**
```bash
./scripts/build/build-windows.sh
```

### Deploying Nodes

**Setup a seed node:**
```bash
./scripts/deployment/setup-seed-node.sh
```

**Deploy on Vultr VPS:**
```bash
./scripts/deployment/vultr-quick-build.sh
```

### Packaging Releases

**Package Linux binaries:**
```bash
./scripts/packaging/PACKAGE_LINUX_BINARIES.sh
```

### Utilities

**Update genesis references:**
```bash
./scripts/utils/update-genesis-refs.sh
```

**Test local macOS node:**
```bash
./scripts/utils/test-local-macos.sh
```

---

## Development Workflow

1. **Install Dependencies**: Use `scripts/build/install-deps-and-build.sh`
2. **Build Binaries**: Use platform-specific build scripts
3. **Test Locally**: Use `scripts/utils/test-local-macos.sh` or similar
4. **Package**: Use `scripts/packaging/PACKAGE_LINUX_BINARIES.sh`
5. **Deploy**: Use deployment scripts for production nodes

---

## Script Organization (January 3, 2026)

All scripts were reorganized from root directory into this structured format for better maintainability and clarity. Scripts maintain the same functionality but are now properly categorized.

**Version**: v1.1.0
**Last Updated**: January 3, 2026

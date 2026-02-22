# AMMOcoin v1.1.0 - Official Binary Releases

**Download the latest release at:** [github.com/everquin/AMMOcoin-v1.1.0/releases](https://github.com/everquin/AMMOcoin-v1.1.0/releases)

---

## Available Platforms

### macOS ARM64 (Apple Silicon)
**Recommended for:** MacBook Pro/Air M1/M2/M3, Mac Mini M1/M2, Mac Studio

- **File:** `AMMOcoin-v1.1.0-macOS-ARM64.tar.gz` (4 MB) or `.zip`
- **Contents:** ammocoind, ammocoin-cli, ammocoin-tx
- **Minimum OS:** macOS 11 (Big Sur) or later
- **Installation time:** 5-10 minutes

[Download macOS ARM64](https://github.com/everquin/AMMOcoin-v1.1.0/releases/latest)

---

### Linux x86_64
**Recommended for:** Ubuntu 20.04+, Debian 11+, RHEL 8+, CentOS 8+

- **File:** `AMMOcoin-v1.1.0-Linux-x86_64.tar.gz` (112 MB)
- **Contents:** ammocoind, ammocoin-cli, ammocoin-tx (statically linked)
- **Minimum OS:** Ubuntu 20.04, Debian 11, or equivalent
- **Installation time:** 5-10 minutes

[Download Linux x86_64](https://github.com/everquin/AMMOcoin-v1.1.0/releases/latest)

---

### Windows x86_64
**Recommended for:** Windows 10 64-bit, Windows 11

- **File:** `AMMOcoin-v1.1.0-Windows-x86_64.zip` (17 MB) or `.tar.gz`
- **Contents:** ammocoind.exe, ammocoin-cli.exe, ammocoin-tx.exe
- **Minimum OS:** Windows 10 64-bit or Windows 11
- **Installation time:** 5-10 minutes

[Download Windows x86_64](https://github.com/everquin/AMMOcoin-v1.1.0/releases/latest)

---

## Quick Start

### macOS
```bash
# Download and extract
curl -LO https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
cd AMMOcoin-v1.1.0-macOS-ARM64/bin

# Remove quarantine (first time only)
sudo xattr -r -d com.apple.quarantine .

# Start the daemon
./ammocoind -daemon

# Check status
./ammocoin-cli getinfo
```

### Linux
```bash
# Download and extract
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
cd bin

# Make executable (if needed)
chmod +x ammocoind ammocoin-cli ammocoin-tx

# Start the daemon
./ammocoind -daemon

# Check status
./ammocoin-cli getinfo
```

### Windows
1. Download `AMMOcoin-v1.1.0-Windows-x86_64.zip`
2. Extract the zip file
3. Navigate to the `bin` directory
4. Double-click `ammocoind.exe` or run from Command Prompt:
   ```
   ammocoind.exe -daemon
   ```
5. Check status (in a new Command Prompt):
   ```
   ammocoin-cli.exe getinfo
   ```

---

## Verify Your Download

**ALWAYS verify the integrity of your download before running!**

### Download the checksums file:
[AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt)

### Verify on macOS/Linux:
```bash
sha256sum AMMOcoin-v1.1.0-*.tar.gz
```

### Verify on Windows:
```powershell
certutil -hashfile AMMOcoin-v1.1.0-Windows-x86_64.zip SHA256
```

Compare the output with the checksums file.

---

## Expected Checksums

```
# macOS ARM64
578eead2eb47d1ed7258d091e9581891390894ed17e3e03c32eac5d98c56e9a0  AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
c744c0212ce29d52eab09cfc4b18c92722447e4002754e8ec3c2a6780262e043  AMMOcoin-v1.1.0-macOS-ARM64.zip

# Linux x86_64
db7b90a98da45080467bb03a11e0de60bffe962888288ba74edb6eb4e646942c  AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Windows x86_64
2b450c699d15c5e2d00caab51a97da1f245f13dcb11580329d875ff26d013c71  AMMOcoin-v1.1.0-Windows-x86_64.tar.gz
6e643a98e97ba698b4b55cf324706186739f1f0f7ec97d2a3176b1227ec1dcee  AMMOcoin-v1.1.0-Windows-x86_64.zip
```

---

## Network Information

- **Genesis Block Hash:** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
- **Merkle Root:** `a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab`
- **Nonce:** `1299391`
- **P2P Port:** 44444
- **RPC Port:** 44445

---

## Configuration

Create `ammocoin.conf` in your data directory:

**Data directory locations:**
- **macOS:** `~/Library/Application Support/AMMOcoin/`
- **Linux:** `~/.ammocoin/`
- **Windows:** `%APPDATA%\AMMOcoin\`

**Minimal configuration:**
```conf
rpcuser=yourusername
rpcpassword=yourpassword
rpcallowip=127.0.0.1
listen=1
server=1
```

---

## Troubleshooting

### macOS: "Cannot be opened because the developer cannot be verified"
```bash
sudo xattr -r -d com.apple.quarantine /path/to/AMMOcoin-v1.1.0-macOS-ARM64
```

### Linux: "Permission denied"
```bash
chmod +x ammocoind ammocoin-cli ammocoin-tx
```

### Windows: "VCRUNTIME140.dll was not found"
Install the [Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x64.exe)

### All platforms: "Could not bind to port"
Another instance of ammocoind is already running. Stop it first:
```bash
./ammocoin-cli stop
```

---

## Building from Source

If binaries are not available for your platform, see the build guides:

- **Linux:** [BUILD_FROM_SOURCE_LINUX.md](../BUILD_FROM_SOURCE_LINUX.md)
- **Windows:** [BUILD_FROM_SOURCE_WINDOWS.md](../BUILD_FROM_SOURCE_WINDOWS.md)
- **Raspberry Pi:** [BUILD_FROM_SOURCE_RASPBERRY_PI.md](../BUILD_FROM_SOURCE_RASPBERRY_PI.md)

---

## Important Notes

1. **New Genesis Block:** v1.1.0 uses a completely new blockchain. It is NOT compatible with v1.0 data.

2. **Backup Your v1.0 Wallet:** If you have funds in v1.0, back up your wallet.dat before upgrading.

3. **Fresh Start:** v1.1.0 starts with block 0. You will need to sync the entire blockchain.

4. **Network Compatibility:** Ensure you're running v1.1.0 to connect to the correct network. Check the genesis hash.

---

## Support

- **Website:** [ammocoin.org](https://ammocoin.org)
- **Documentation:** [GitHub Repository](https://github.com/everquin/AMMOcoin-v1.1.0)
- **Issues:** [GitHub Issues](https://github.com/everquin/AMMOcoin-v1.1.0/issues)
- **Community:** See [ammocoin.org/community.html](https://ammocoin.org/community.html)

---

## File Size Reference

| Platform | tar.gz | zip |
|----------|--------|-----|
| macOS ARM64 | 4.0 MB | 4.0 MB |
| Linux x86_64 | 112 MB | - |
| Windows x86_64 | 17 MB | 17 MB |

**Why is Linux larger?**
The Linux build includes statically linked dependencies (Boost, OpenSSL, etc.) to ensure compatibility across different distributions.

---

**Last Updated:** January 5, 2026
**Release:** v1.1.0
**Repository:** [github.com/everquin/AMMOcoin-v1.1.0](https://github.com/everquin/AMMOcoin-v1.1.0)

# Contributing to AMMOcoin

Thank you for your interest in contributing to AMMOcoin! This project welcomes contributions from developers, testers, documentation writers, and community members.

## 📚 **Quick Links**

- **📖 [Complete Contributing Guide](docs/developer/CONTRIBUTING.md)** - Detailed contribution process
- **🏗️ [Build Instructions](docs/developer/BUILD.md)** - How to build from source
- **🔧 [API Documentation](docs/developer/API.md)** - Technical reference
- **👥 [User Guide](docs/user/USER_GUIDE.md)** - Using AMMOcoin features

## 🚀 **Getting Started**

### 1. **Choose Your Contribution Type**
- **🐛 Bug Fixes** - Fix issues and improve stability
- **✨ New Features** - Add functionality and enhancements
- **📖 Documentation** - Improve guides and references
- **🧪 Testing** - Write tests and report bugs
- **🌍 Community** - Help users and spread awareness

### 2. **Set Up Development Environment**
```bash
# Fork and clone
git clone https://github.com/yourusername/AMMOcoin.git
cd AMMOcoin

# Install dependencies (macOS)
brew install boost berkeley-db@4 libevent libsodium zeromq gmp openssl rust

# Build
./autogen.sh
./configure --disable-tests --disable-bench --enable-wallet --without-gui
make -j4
```

### 3. **Make Your Contribution**
```bash
# Create feature branch
git checkout -b feature/your-improvement

# Make changes, test thoroughly
make check

# Commit with clear message
git commit -m "Add your improvement description"

# Push and create PR
git push origin feature/your-improvement
```

## 🎯 **What We Need**

### **High Priority**
- 🔐 Security reviews and audits
- 🧪 Test coverage improvements
- 📖 Documentation enhancements
- 🐛 Bug fixes and stability improvements

### **Feature Development**
- 💰 Wallet functionality improvements
- 🛡️ Privacy feature enhancements
- 🏛️ Masternode tooling
- ⚡ Performance optimizations

### **Community Contributions**
- 📝 Tutorials and guides
- 🌍 Translation support
- 💬 User support
- 📢 Community outreach

## 📋 **Contribution Standards**

### **Code Quality**
- ✅ C++14 standard compliance
- ✅ Unit tests for new features
- ✅ Documentation updates
- ✅ No compiler warnings
- ✅ Memory leak free

### **Pull Request Process**
1. **Fork** the repository
2. **Create** feature branch from `main`
3. **Test** changes thoroughly
4. **Update** relevant documentation
5. **Submit** PR with clear description

### **Review Criteria**
- **Functionality**: Does it work as intended?
- **Security**: No security vulnerabilities
- **Performance**: No unnecessary overhead
- **Compatibility**: Maintains backward compatibility
- **Documentation**: Adequate documentation provided

## 🐛 **Reporting Issues**

### **Bug Reports**
Use our [issue template](.github/ISSUE_TEMPLATE.md) and include:
- AMMOcoin version
- Operating system
- Steps to reproduce
- Expected vs actual behavior
- Error messages/logs

### **Security Issues**
For security vulnerabilities:
- **Don't** create public issues
- **Email**: security@ammocoin.org
- **Include**: Detailed vulnerability description
- **Wait**: For coordinated disclosure

## 🌟 **Recognition**

Contributors are recognized through:
- **Git commit history** - Permanent record
- **Release notes** - Major contributor acknowledgment
- **Community recognition** - Public appreciation
- **Maintainer status** - For significant long-term contributors

## 📞 **Getting Help**

### **Technical Questions**
- [GitHub Discussions](https://github.com/everquin/AMMOcoin/discussions)
- [Developer Documentation](docs/developer/)
- [Build Instructions](docs/developer/BUILD.md)

### **Community Support**
- [User Guide](docs/user/USER_GUIDE.md)
- [Community Channels](docs/README.md#community--support)
- [FAQ](docs/user/FAQ.md)

---

## 📖 **Documentation Structure**

```
docs/
├── user/                    # End-user documentation
│   ├── INSTALLATION.md      # Setup instructions
│   ├── USER_GUIDE.md        # Feature usage
│   └── SECURITY.md          # Security practices
├── developer/               # Developer resources
│   ├── BUILD.md             # Build instructions
│   ├── CONTRIBUTING.md      # Detailed contribution guide
│   └── API.md               # Technical reference
└── deployment/              # Production deployment
    ├── PRODUCTION.md        # Enterprise setup
    └── CONFIG.md            # Configuration reference
```

**Ready to contribute?** Start with our [detailed contributing guide](docs/developer/CONTRIBUTING.md)!

---

**AMMOcoin is built by the community, for the community. Every contribution matters!** 🚀
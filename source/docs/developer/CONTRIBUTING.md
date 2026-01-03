# Contributing to AMMOcoin

We welcome contributions to AMMOcoin! This document explains the process and guidelines for contributing to the project.

## 🤝 **How to Contribute**

### Ways to Contribute
- **Code**: Bug fixes, features, optimizations
- **Documentation**: Guides, API docs, tutorials
- **Testing**: Bug reports, test cases, QA
- **Community**: Support, discussions, feedback

### Getting Started
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 🔧 **Development Process**

### Setting Up Development Environment
```bash
# Clone your fork
git clone https://github.com/yourusername/AMMOcoin-v1.1.0.git
cd AMMOcoin-v1.1.0

# Add upstream remote
git remote add upstream https://github.com/everquin/AMMOcoin-v1.1.0.git

# Create development branch
git checkout -b feature/your-feature-name
```

### Code Standards
- **Language**: C++14 standard
- **Style**: Follow existing codebase conventions
- **Comments**: Document complex logic
- **Headers**: Include necessary headers only

### Commit Guidelines
```bash
# Good commit messages:
"Fix memory leak in wallet encryption"
"Add Sapling transaction validation"
"Update documentation for masternode setup"

# Use present tense, imperative mood
# Keep first line under 72 characters
# Include detailed description if needed
```

## 🧪 **Testing Requirements**

### Before Submitting
- [ ] Code compiles without warnings
- [ ] Unit tests pass (`make check`)
- [ ] Functional tests pass
- [ ] No memory leaks detected
- [ ] Documentation updated

### Writing Tests
```bash
# Add unit tests for new features
src/test/your_feature_tests.cpp

# Add functional tests if needed
test/functional/feature_your_feature.py
```

### Running Tests
```bash
# Unit tests
make check

# Functional tests
test/functional/test_runner.py

# Specific test
test/functional/wallet_basic.py
```

## 📝 **Pull Request Process**

### Before Creating PR
1. **Sync with upstream**
   ```bash
   git fetch upstream
   git rebase upstream/main
   ```

2. **Test thoroughly**
   ```bash
   make clean
   ./configure --enable-tests
   make -j$(nproc)
   make check
   ```

3. **Update documentation** if needed

### PR Description Template
```markdown
## Description
Brief description of changes

## Motivation
Why is this change needed?

## Testing
How was this tested?

## Checklist
- [ ] Code compiles cleanly
- [ ] Tests pass
- [ ] Documentation updated
- [ ] No breaking changes
```

### Review Process
- Maintainers will review your PR
- Address feedback promptly
- Keep discussions professional
- Be patient with review process

## 🐛 **Bug Reports**

### Before Reporting
- Search existing issues
- Try latest version
- Gather relevant information

### Bug Report Template
```markdown
## Bug Description
Clear description of the issue

## Steps to Reproduce
1. Step one
2. Step two
3. Issue occurs

## Expected Behavior
What should happen

## Actual Behavior
What actually happens

## Environment
- OS:
- Version:
- Build info:

## Additional Context
Any other relevant information
```

## 💡 **Feature Requests**

### Proposing Features
1. **Open discussion** before implementing
2. **Create issue** with detailed proposal
3. **Get community feedback**
4. **Implement if approved**

### Feature Request Template
```markdown
## Feature Summary
Brief description of feature

## Motivation
Why is this feature needed?

## Implementation Ideas
How could this be implemented?

## Alternatives
Other approaches considered?
```

## 📖 **Documentation**

### Documentation Standards
- **Clear and concise** writing
- **Complete examples** with code
- **Up-to-date** information
- **Beginner-friendly** when possible

### Documentation Types
- **User guides**: How to use features
- **Developer docs**: Technical details
- **API reference**: Complete command list
- **Tutorials**: Step-by-step walkthroughs

## 🔒 **Security**

### Security Issues
- **Don't create public issues** for security vulnerabilities
- **Email directly**: security@ammocoin.org
- **Provide details**: Steps to reproduce, impact assessment
- **Coordinate disclosure**: Work with maintainers on timeline

### Security Review
- All cryptographic changes require review
- Security-sensitive code needs extra scrutiny
- Performance changes should be benchmarked

## 🌍 **Community Guidelines**

### Code of Conduct
- **Be respectful** and inclusive
- **Help newcomers** learn and contribute
- **Focus on technical merit** of contributions
- **Avoid personal attacks** or discrimination

### Communication Channels
- **GitHub Issues**: Bug reports, feature requests
- **Pull Requests**: Code contributions
- **Discussions**: General questions and ideas

## 🏷️ **Labels and Workflow**

### Issue Labels
- `bug`: Something isn't working
- `enhancement`: New feature or improvement
- `documentation`: Documentation needs
- `good first issue`: Good for newcomers
- `help wanted`: Community help needed

### PR Labels
- `ready for review`: Ready for maintainer review
- `needs work`: Changes requested
- `approved`: Approved for merge
- `breaking change`: Breaking API change

## 🚀 **Release Process**

### Version Numbers
- **Major**: Breaking changes (X.0.0)
- **Minor**: New features (X.Y.0)
- **Patch**: Bug fixes (X.Y.Z)

### Release Branches
- `main`: Development branch
- `release-X.Y`: Release preparation
- `hotfix-X.Y.Z`: Critical fixes

## 📚 **Learning Resources**

### Getting Started
- [Build Instructions](BUILD.md)
- [API Documentation](API.md)
- [User Guide](../user/USER_GUIDE.md)

### Technical Background
- **Bitcoin**: Understanding base protocol
- **Zcash**: Sapling privacy technology
- **Proof-of-Stake**: Consensus mechanism
- **C++14**: Language features used

### Development Tools
- **Git**: Version control
- **GDB**: Debugging
- **Valgrind**: Memory checking
- **Static analysis**: Code quality

---

## 🎯 **Next Steps**

Ready to contribute? Here's how to start:

1. **Browse issues** labeled "good first issue"
2. **Join discussions** on topics you're interested in
3. **Read the codebase** to understand architecture
4. **Start small** with documentation or minor fixes
5. **Ask questions** when you need help

**Thank you for contributing to AMMOcoin!** 🚀

---

**Contact**: For questions about contributing, open an issue or reach out through our community channels.
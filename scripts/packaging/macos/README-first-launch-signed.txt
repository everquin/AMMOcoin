First launch
------------
AMMOcoin-Qt.app and the command-line tools are signed with the AMMOcoin
developer's Apple Developer ID and notarized by Apple.

  GUI:  The app and the DMG carry a stapled notarization ticket, so they open
        normally, even offline.
  CLI:  The ammocoind / ammocoin-cli / ammocoin-tx binaries are notarized too,
        but plain executables in a .tar.gz or .zip cannot carry a stapled
        ticket. The first time you run one, macOS checks the notarization
        online; without an internet connection it may refuse to start it.
        If that happens, connect once, or run:
          xattr -dr com.apple.quarantine /path/to/the/extracted/folder
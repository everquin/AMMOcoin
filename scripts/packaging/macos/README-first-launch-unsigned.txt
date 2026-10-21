First launch (unsigned build)
-----------------------------
This build is ad-hoc signed but NOT signed with a Developer ID or notarized
by Apple, so Gatekeeper will refuse to open it the first time. To allow it:

  GUI:  Right-click (or Control-click) AMMOcoin-Qt.app > Open > Open.
        On recent macOS you may instead need System Settings > Privacy &
        Security > "Open Anyway" after the first attempt.
  CLI:  xattr -dr com.apple.quarantine /path/to/the/extracted/folder
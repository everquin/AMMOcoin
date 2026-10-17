#!/usr/bin/env bash
# Keep CI version strings clean: v1.1.1.0-<sha>, not v1.1.1.0-<sha>-dirty.
#
# share/genbuild.sh appends "-dirty" when `git diff-index HEAD` reports any change. configure
# rewrites several files that are committed to git (AC_CONFIG_FILES outputs: share/setup.nsi,
# share/qt/Info.plist, test/config.ini, contrib/devtools/split-debug.sh, univalue's .pc files and
# univalue-config.h, chiabls relic_conf.h ...), so every CI build was stamped dirty. This marks
# each tracked file that now differs from HEAD as assume-unchanged (the source checkout itself
# is untouched) and fails if anything still differs. Run it after configure and again before
# re-stamping if make modified more files. Prints the files it marked.
set -euo pipefail
cd "$(git rev-parse --show-toplevel)"

git update-index -q --refresh >/dev/null 2>&1 || true
if git diff-index --quiet HEAD --; then
  echo "mark-tracked-build-outputs: no tracked files modified"
  exit 0
fi
echo "mark-tracked-build-outputs: build-generated tracked files (marked assume-unchanged):"
git diff-index --name-status HEAD -- | sed 's/^/  /'
git diff-index -z --name-only HEAD -- | xargs -0 git update-index --assume-unchanged --

if ! git diff-index --quiet HEAD --; then
  echo "mark-tracked-build-outputs: still differs from HEAD (staged changes?):" >&2
  git diff-index --name-status HEAD -- >&2
  exit 1
fi

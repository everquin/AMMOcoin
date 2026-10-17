#!/usr/bin/env bash
# Fail the build if the stamped version is "-dirty" or missing.
#   scripts/ci/check-build-version.sh <path/to/src/obj/build.h> [binary ...]
# build.h is written by share/genbuild.sh; each binary must embed the same clean version string.
set -euo pipefail
BUILD_H=${1:?path to src/obj/build.h}; shift
[ -f "$BUILD_H" ] || { echo "check-build-version: $BUILD_H not found" >&2; exit 1; }
echo "build.h: $(cat "$BUILD_H")"
if grep -q -- '-dirty' "$BUILD_H"; then
  echo "check-build-version: version is -dirty; tracked files changed during the build:" >&2
  git -C "$(dirname "$BUILD_H")" diff-index --name-status HEAD -- >&2 || true
  exit 1
fi
grep -qE 'BUILD_SUFFIX|BUILD_DESC' "$BUILD_H" \
  || { echo "check-build-version: no git version info in build.h" >&2; exit 1; }
for bin in "$@"; do
  v=$(strings "$bin" | grep -oE 'v[0-9]+\.[0-9]+\.[0-9]+(\.[0-9]+)?(-[0-9a-f]{7,40})?(-dirty)?' | grep -E -- '-[0-9a-f]{7,}|^v[0-9]+\.[0-9]+\.[0-9]+$' | sort -u | head -5 || true)
  echo "$bin: ${v:-<no version string found>}"
  if echo "$v" | grep -q -- '-dirty'; then
    echo "check-build-version: $bin embeds a -dirty version" >&2
    exit 1
  fi
done

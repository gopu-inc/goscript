#!/bin/sh
set -eu

BIN_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
GOSCRIPT_SHARE_DIR=${GOSCRIPT_SHARE_DIR:-"$BIN_DIR/../share/goscript"}
GD_BIN=${GOSCRIPT_BIN:-"$BIN_DIR/gd"}
if [ ! -x "$GD_BIN" ] && [ -x "$GD_BIN.exe" ]; then
    GD_BIN="$GD_BIN.exe"
fi
export GOSCRIPT_SHARE_DIR

exec "$GD_BIN" "$GOSCRIPT_SHARE_DIR/golem-cli.gjs" "$@"

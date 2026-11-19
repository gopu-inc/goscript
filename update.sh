#!/bin/sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
INSTALL_SCRIPT=${GOSCRIPT_INSTALL_SCRIPT:-https://gsql-badge.onrender.com/install.sh}

if [ "${GOSCRIPT_UPDATE_FROM_SOURCE:-0}" = "1" ]; then
    exec "$SCRIPT_DIR/install.sh"
fi

if command -v curl >/dev/null 2>&1; then
    curl -fsSL "$INSTALL_SCRIPT" | sh
    exit $?
fi

printf 'curl is required to update Goscript and Golem.\n' >&2
exit 1

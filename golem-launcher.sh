#!/bin/sh
set -eu

BIN_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
DEFAULT_SHARE_DIR="$BIN_DIR/../share/goscript"
GOSCRIPT_SHARE_DIR=${GOSCRIPT_SHARE_DIR:-"$DEFAULT_SHARE_DIR"}
# Une variable GOSCRIPT_SHARE_DIR héritée du shell (ex. « export GOSCRIPT_SHARE_DIR=~/goscript/lib »)
# peut pointer vers un dossier qui ne contient pas golem-cli.gjs. On le signale et on retombe
# sur le dossier installé avec ce lanceur au lieu d'échouer avec « Cannot open ».
if [ ! -f "$GOSCRIPT_SHARE_DIR/golem-cli.gjs" ] && [ -f "$DEFAULT_SHARE_DIR/golem-cli.gjs" ]; then
    printf 'golem: GOSCRIPT_SHARE_DIR=%s ne contient pas golem-cli.gjs; utilisation de %s\n' \
        "$GOSCRIPT_SHARE_DIR" "$DEFAULT_SHARE_DIR" >&2
    printf "golem: pour supprimer cet avertissement, lancez : unset GOSCRIPT_SHARE_DIR\n" >&2
    GOSCRIPT_SHARE_DIR=$DEFAULT_SHARE_DIR
fi
GOSCRIPT_PREFIX=${GOSCRIPT_PREFIX:-"$(CDPATH= cd -- "$BIN_DIR/.." && pwd)"}
PREFIX=${PREFIX:-$GOSCRIPT_PREFIX}
GD_BIN=${GOSCRIPT_BIN:-"$BIN_DIR/gd"}
if [ ! -x "$GD_BIN" ] && [ -x "$GD_BIN.exe" ]; then
    GD_BIN="$GD_BIN.exe"
fi
export GOSCRIPT_SHARE_DIR GOSCRIPT_PREFIX PREFIX

if [ "${1:-}" = install ] && [ "${2:-}" = goscript ]; then
    if [ "$#" -gt 3 ]; then
        printf 'Usage: golem install goscript [version]\n' >&2
        exit 2
    fi
    if [ "$#" -eq 3 ]; then
        GOSCRIPT_VERSION=$3
        export GOSCRIPT_VERSION
    fi
    if [ ! -x "$GOSCRIPT_SHARE_DIR/install.sh" ]; then
        printf 'Goscript installer is missing: %s/install.sh\n' "$GOSCRIPT_SHARE_DIR" >&2
        exit 1
    fi
    exec "$GOSCRIPT_SHARE_DIR/install.sh"
fi

exec "$GD_BIN" "$GOSCRIPT_SHARE_DIR/golem-cli.gjs" "$@"

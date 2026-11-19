#!/bin/sh
set -eu

PREFIX=${PREFIX:-/usr/local}
VERSION=${GOSCRIPT_VERSION:-latest}
WORK_DIR=$(mktemp -d "${TMPDIR:-/tmp}/goscript-install.XXXXXX")

cleanup() {
    rm -rf "$WORK_DIR"
}
trap cleanup EXIT HUP INT TERM

OS=$(uname -s)
MACHINE=$(uname -m)
TERMUX=0
case "$PREFIX" in
    /data/data/com.termux/files/usr|/data/user/0/com.termux/files/usr)
        TERMUX=1
        ;;
esac
if [ "$OS" = Linux ] && [ -n "${TERMUX_VERSION:-}" ]; then
    TERMUX=1
fi

if [ "$TERMUX" -eq 1 ]; then
    PLATFORM=
    ARCH=
else
    case "$OS:$MACHINE" in
        Linux:x86_64|Linux:amd64)
            PLATFORM=linux
            ARCH=x86_64
            ;;
        Linux:aarch64|Linux:arm64)
            PLATFORM=linux
            ARCH=arm64
            ;;
        Darwin:x86_64|Darwin:amd64)
            PLATFORM=macos
            ARCH=x86_64
            ;;
        Darwin:arm64|Darwin:aarch64)
            PLATFORM=macos
            ARCH=arm64
            ;;
        *)
            PLATFORM=
            ARCH=
            ;;
    esac
fi

if [ -z "$PLATFORM" ]; then
    if [ "$TERMUX" -eq 1 ]; then
        printf 'Termux/Android detected; building Goscript for Bionic from source.\n'
    else
        printf 'No prebuilt release for %s/%s; building from a temporary source checkout.\n' "$OS" "$MACHINE"
    fi
    install_build_tools() {
        if [ "$TERMUX" -eq 1 ]; then
            pkg update
            pkg install -y clang coreutils flex bison libffi zlib git make curl tar
        elif command -v apt-get >/dev/null 2>&1; then
            SUDO=
            if [ "$(id -u)" -ne 0 ]; then SUDO=sudo; fi
            $SUDO apt-get update
            $SUDO apt-get install -y build-essential flex bison libffi-dev zlib1g-dev git make curl tar
        elif command -v dnf >/dev/null 2>&1; then
            SUDO=
            if [ "$(id -u)" -ne 0 ]; then SUDO=sudo; fi
            $SUDO dnf install -y gcc make flex bison libffi-devel zlib-devel git curl tar
        elif command -v pacman >/dev/null 2>&1; then
            SUDO=
            if [ "$(id -u)" -ne 0 ]; then SUDO=sudo; fi
            $SUDO pacman -Sy --needed --noconfirm base-devel flex bison libffi zlib git curl tar
        elif command -v apk >/dev/null 2>&1; then
            SUDO=
            if [ "$(id -u)" -ne 0 ]; then SUDO=sudo; fi
            $SUDO apk add build-base flex bison libffi-dev zlib-dev git curl tar
        elif command -v brew >/dev/null 2>&1; then
            brew install gcc make flex bison libffi zlib git curl gnu-tar
        else
            printf 'No supported package manager found to install build tools.\n' >&2
            exit 1
        fi
    }
    install_build_tools
    command -v git >/dev/null 2>&1 || { printf 'git is required for the source build.\n' >&2; exit 1; }
    if [ "$VERSION" = latest ]; then
        git clone --depth 1 "https://github.com/gopu-inc/goscript.git" "$WORK_DIR/source"
    else
        git clone --depth 1 --branch "$VERSION" "https://github.com/gopu-inc/goscript.git" "$WORK_DIR/source"
    fi
    BUILD_CC=gcc
    if [ "$TERMUX" -eq 1 ]; then BUILD_CC=clang; fi
    make -C "$WORK_DIR/source" gd CC="$BUILD_CC"
    make -C "$WORK_DIR/source" install PREFIX="$PREFIX" CC="$BUILD_CC"
    printf 'Installed from source. Temporary checkout will now be removed.\n'
    exit 0
fi

ASSET="goscript-${PLATFORM}-${ARCH}.tar.gz"
if [ -n "${GOSCRIPT_RELEASE_URL:-}" ]; then
    RELEASE_URL=${GOSCRIPT_RELEASE_URL%/}
elif [ "$VERSION" = latest ]; then
    RELEASE_URL="https://github.com/gopu-inc/goscript/releases/latest/download"
else
    RELEASE_URL="https://github.com/gopu-inc/goscript/releases/download/${VERSION}"
fi

printf 'Downloading Goscript %s for %s/%s...\n' "$VERSION" "$PLATFORM" "$ARCH"
if ! curl -fsSL "$RELEASE_URL/$ASSET" -o "$WORK_DIR/$ASSET" 2>/dev/null; then
    sleep 2
    if ! curl -fsSL "$RELEASE_URL/$ASSET" -o "$WORK_DIR/$ASSET"; then
        printf 'Could not download %s from %s. Check the network and release assets.\n' "$ASSET" "$RELEASE_URL" >&2
        exit 1
    fi
fi
if ! curl -fsSL "$RELEASE_URL/$ASSET.sha256" -o "$WORK_DIR/$ASSET.sha256"; then
    printf 'Could not download the checksum for %s.\n' "$ASSET" >&2
    exit 1
fi

EXPECTED=$(awk 'NR == 1 { print $1 }' "$WORK_DIR/$ASSET.sha256")
if [ -z "$EXPECTED" ]; then
    printf 'Release checksum is empty.\n' >&2
    exit 1
fi
if command -v sha256sum >/dev/null 2>&1; then
    ACTUAL=$(sha256sum "$WORK_DIR/$ASSET" | awk '{ print $1 }')
elif command -v shasum >/dev/null 2>&1; then
    ACTUAL=$(shasum -a 256 "$WORK_DIR/$ASSET" | awk '{ print $1 }')
else
    printf 'sha256sum or shasum is required to verify the release.\n' >&2
    exit 1
fi
if [ "$ACTUAL" != "$EXPECTED" ]; then
    printf 'Release checksum mismatch.\n' >&2
    exit 1
fi

mkdir -p "$PREFIX"
tar -xzf "$WORK_DIR/$ASSET" -C "$PREFIX"
chmod 755 "$PREFIX/bin/gd" "$PREFIX/bin/golem"
printf 'Goscript and Golem installed under %s.\n' "$PREFIX"
printf 'Install the standard packages for a project with: golem install base\n'

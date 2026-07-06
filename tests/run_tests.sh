#!/usr/bin/env bash
# tests/run_tests.sh — Lanceur de la suite de tests Goscript
#
# Exécution : bash tests/run_tests.sh
# Depuis la racine du projet après `make`.

set -euo pipefail

# Couleurs ANSI
GRN="\033[0;32m"
RED="\033[0;31m"
YLW="\033[0;33m"
BLU="\033[0;34m"
RST="\033[0m"

GD="./gd"
TESTS_DIR="./tests"
PASS=0
FAIL=0
SKIP=0

if [ ! -x "$GD" ]; then
    echo -e "${RED}[ERREUR]${RST} Binaire '$GD' introuvable. Lancez 'make' d'abord."
    exit 1
fi

echo ""
echo -e "${BLU}╔══════════════════════════════════════════╗${RST}"
echo -e "${BLU}║   Suite de tests Goscript               ║${RST}"
echo -e "${BLU}╚══════════════════════════════════════════╝${RST}"
echo ""

run_test() {
    local name="$1"
    local file="$2"
    local timeout="${3:-10}"

    if [ ! -f "$file" ]; then
        echo -e "  ${YLW}SKIP${RST}  $name (fichier introuvable : $file)"
        ((SKIP++)) || true
        return
    fi

    echo -e "${BLU}▶ $name${RST}"

    local output
    local exit_code=0
    output=$(timeout "$timeout" "$GD" "$file" 2>&1) || exit_code=$?

    if [ $exit_code -eq 124 ]; then
        echo -e "  ${YLW}TIMEOUT${RST}  (>${timeout}s)"
        ((FAIL++)) || true
        return
    fi

    # Compter les FAIL dans la sortie
    local fails
    fails=$(echo "$output" | grep -c "FAIL" || true)
    local warns
    warns=$(echo "$output" | grep -c "WARN" || true)

    echo "$output" | while IFS= read -r line; do
        if echo "$line" | grep -q "FAIL"; then
            echo -e "    ${RED}$line${RST}"
        elif echo "$line" | grep -q "WARN"; then
            echo -e "    ${YLW}$line${RST}"
        elif echo "$line" | grep -q "OK"; then
            echo -e "    ${GRN}$line${RST}"
        else
            echo "    $line"
        fi
    done

    if [ "$fails" -eq 0 ]; then
        echo -e "  ${GRN}✓ RÉUSSI${RST}  ($warns avertissements)"
        ((PASS++)) || true
    else
        echo -e "  ${RED}✗ ÉCHOUÉ${RST}  ($fails erreur(s))"
        ((FAIL++)) || true
    fi
    echo ""
}

# ──────────────────────────────────────────────
# Compilation préalable
# ──────────────────────────────────────────────
echo -e "${BLU}► Compilation...${RST}"
if make -s 2>&1; then
    echo -e "  ${GRN}✓ Compilation OK${RST}"
else
    echo -e "  ${RED}✗ Compilation ÉCHOUÉE${RST}"
    exit 1
fi
echo ""

# ──────────────────────────────────────────────
# Lancement des tests
# ──────────────────────────────────────────────
run_test "Librairie standard"        "$TESTS_DIR/test_std.gjs"    15
run_test "Système d'imports"         "$TESTS_DIR/test_import.gjs" 15
run_test "FFI (fonctions C natives)" "$TESTS_DIR/test_ffi.gjs"    15
run_test "TCP Socket"                "$TESTS_DIR/test_socket.gjs" 20
run_test "SQLite"                    "$TESTS_DIR/test_db.gjs"     15
run_test "WebSocket"                 "$TESTS_DIR/test_websocket.gjs" 10

# ──────────────────────────────────────────────
# Résumé
# ──────────────────────────────────────────────
echo -e "${BLU}╔══════════════════════════════════════════╗${RST}"
echo -e "${BLU}║   Résumé                                 ║${RST}"
echo -e "${BLU}╚══════════════════════════════════════════╝${RST}"
echo -e "  ${GRN}Réussis  : $PASS${RST}"
echo -e "  ${RED}Échoués  : $FAIL${RST}"
echo -e "  ${YLW}Ignorés  : $SKIP${RST}"
echo ""

if [ "$FAIL" -eq 0 ]; then
    echo -e "${GRN}✓ Tous les tests ont réussi !${RST}"
    exit 0
else
    echo -e "${RED}✗ $FAIL test(s) en échec.${RST}"
    exit 1
fi

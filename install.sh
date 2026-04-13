#!/bin/bash
# install.sh - Install genv for Goscript

set -e

GREEN='\033[0;32m'
CYAN='\033[0;36m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${CYAN}Installing genv - Goscript Virtual Environment Manager${NC}\n"

# Déterminer le répertoire d'installation
INSTALL_DIR="${GENV_INSTALL_DIR:-$HOME/.local/bin}"
mkdir -p "$INSTALL_DIR"

# Copier le script principal
cp genv "$INSTALL_DIR/genv"
chmod +x "$INSTALL_DIR/genv"

echo -e "${GREEN}✓ genv installed to: $INSTALL_DIR/genv${NC}"

# Vérifier si le répertoire est dans PATH
if [[ ":$PATH:" != *":$INSTALL_DIR:"* ]]; then
    echo -e "${YELLOW}Warning: $INSTALL_DIR is not in your PATH${NC}"
    echo -e "  Add this to your ~/.bashrc or ~/.zshrc:"
    echo -e "  ${CYAN}export PATH=\"$INSTALL_DIR:\$PATH\"${NC}"
fi

# Créer les répertoires de données
mkdir -p "$HOME/.genv/envs"
mkdir -p "$HOME/.genv/bin"
mkdir -p "$HOME/.genv/cache"
mkdir -p "$HOME/.genv/tmp"

echo -e "${GREEN}✓ Data directories created${NC}"

# Ajouter l'alias pour activation rapide (optionnel)
if [[ -f "$HOME/.bashrc" ]]; then
    if ! grep -q "alias genv-activate" "$HOME/.bashrc"; then
        echo "" >> "$HOME/.bashrc"
        echo "# genv aliases" >> "$HOME/.bashrc"
        echo "alias ga='source \$(genv which 2>/dev/null)/bin/activate 2>/dev/null || genv activate'" >> "$HOME/.bashrc"
        echo "alias gd='genv deactivate'" >> "$HOME/.bashrc"
        echo "alias gl='genv list'" >> "$HOME/.bashrc"
        echo -e "${GREEN}✓ Aliases added to ~/.bashrc${NC}"
    fi
fi

echo ""
echo -e "${CYAN}Installation complete!${NC}"
echo ""
echo -e "${GREEN}Quick start:${NC}"
echo -e "  genv create myproject     # Create environment"
echo -e "  genv activate myproject   # Activate environment"
echo -e "  genv list                 # List environments"
echo -e "  genv help                 # Show all commands"
echo ""

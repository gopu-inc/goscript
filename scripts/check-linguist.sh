#!/bin/bash
# Script pour vérifier la configuration GitHub Linguist

echo "=== GitHub Linguist Configuration Check ==="
echo ""

# Vérifier les fichiers
echo "1. Checking files..."
ls -la grammars/goscript.json
ls -la .github/linguist.yml
ls -la language-configuration.json
echo ""

# Vérifier les extensions Goscript
echo "2. Checking Goscript files..."
find . -name "*.gjs" | head -5
echo ""

# Vérifier le contenu du .gitattributes
echo "3. .gitattributes content:"
cat .gitattributes | grep -E "(linguist|gjs)"
echo ""

# Vérifier la grammaire
echo "4. Grammar file validation:"
if command -v jq &> /dev/null; then
    jq . grammars/goscript.json > /dev/null 2>&1 && echo "✓ Grammar JSON is valid" || echo "✗ Grammar JSON is invalid"
else
    echo "jq not installed, skipping JSON validation"
fi
echo ""

# Compter les fichiers Goscript
echo "5. Goscript files count:"
find . -name "*.gjs" | wc -l
echo ""

echo "=== Configuration Complete ==="
echo "Push to GitHub and wait a few minutes for the language to be detected."

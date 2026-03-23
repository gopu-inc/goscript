#!/bin/bash
# Script pour initialiser un projet Goscript avec Git

PROJECT_NAME=$1
if [ -z "$PROJECT_NAME" ]; then
    echo "Usage: $0 <project-name>"
    exit 1
fi

# Créer le projet
mkdir -p "$PROJECT_NAME"
cd "$PROJECT_NAME" || exit 1

# Initialiser Git
git init

# Créer .gitattributes
cat > .gitattributes << 'GITATTR'
*.gjs linguist-language=Goscript linguist-detectable=true linguist-color=#7c3aed
*.c linguist-vendored
*.h linguist-vendored
*.sh linguist-vendored
Makefile linguist-vendored
GITATTR

# Créer .gitignore
cat > .gitignore << 'GITIGNORE'
*.o
*.exe
*.out
.DS_Store
.vscode/
*.swp
GITIGNORE

# Créer un exemple
cat > main.gjs << 'MAINEOF'
fn main() {
    println("Hello, Goscript!")
    ret 0
}
MAINEOF

# Créer README
cat > README.md << 'README'
# $PROJECT_NAME

Goscript project.
README

# Premier commit
git add .
git commit -m "Initial commit"

echo "✅ Project created: $PROJECT_NAME"
cd ..

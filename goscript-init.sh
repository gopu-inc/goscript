#!/bin/bash
# Script pour initialiser un projet Goscript avec Git

PROJECT_NAME=$1
if [ -z "$PROJECT_NAME" ]; then
    echo "Usage: $0 <project-name>"
    exit 1
fi

# Créer le projet
mkdir -p $PROJECT_NAME
cd $PROJECT_NAME

# Initialiser Git
git init

# Créer .gitattributes
cat > .gitattributes << 'GITATTR'
# Goscript language
*.gjs linguist-language=Goscript
*.gjs linguist-vendored=false
*.gjs linguist-detectable=true
*.gjs diff=goscript
*.gjs merge=goscript
GITATTR

# Créer .gitignore
cat > .gitignore << 'GITIGNORE'
# Goscript
*.exe
*.out
*.o
*.a
*.so
*.dylib

# IDE
.vscode/
.idea/
*.swp
*.swo

# OS
.DS_Store
Thumbs.db

# Logs
*.log
GITIGNORE

# Créer un exemple
cat > main.gjs << 'EOF'
fn main() {
    println("Hello, Goscript!")
    ret 0
}

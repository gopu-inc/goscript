# 1. Créer les dossiers Vim s'ils n'existent pas
mkdir -p ~/.vim/colors,ftdetect,indent,snippets,syntax
# 2. Copier tous les fichiers
cp vim/colors/goscript.vim ~/.vim/colors/
cp vim/ftdetect/goscript.vim ~/.vim/ftdetect/
cp vim/indent/goscript.vim ~/.vim/indent/
cp vim/snippets/goscript.snippets ~/.vim/snippets/
cp vim/syntax/goscript.vim ~/.vim/syntax/

# 3. Vérifier que les fichiers sont bien copiés
ls -la ~/.vim/colors/
ls -la ~/.vim/ftdetect/
ls -la ~/.vim/indent/
ls -la ~/.vim/snippets/
ls -la ~/.vim/syntax/

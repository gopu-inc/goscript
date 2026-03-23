" Goscript file type detection
" Maintainer: GOPU inc team
" Version: 2.0
" Last Change: 2026

" Détection par extension de fichier
au BufRead,BufNewFile *.gjs    setfiletype goscript
au BufRead,BufNewFile *.gos    setfiletype goscript
au BufRead,BufNewFile *.gscript setfiletype goscript

" Détection par nom de fichier
au BufRead,BufNewFile Goscriptfile setfiletype goscript
au BufRead,BufNewFile goscript.conf setfiletype goscript

" Détection par contenu (premier ligne)
au BufRead,BufNewFile * if getline(1) =~ '^#!.*goscript' | setfiletype goscript | endif

" Configuration spécifique au type de fichier
au FileType goscript call s:SetupGoscript()

function! s:SetupGoscript()
    " Options de base
    setlocal tabstop=4
    setlocal shiftwidth=4
    setlocal softtabstop=4
    setlocal expandtab
    setlocal autoindent
    setlocal smartindent
    
    " Commentaire
    setlocal commentstring=//\ %s
    
    " Formatage
    setlocal formatoptions+=croql
    
    " Folding
    setlocal foldmethod=syntax
    setlocal foldlevel=99
    
    " Complétion
    if exists('&omnifunc')
        setlocal omnifunc=syntaxcomplete#Complete
    endif
    
    " Mappages locaux
    nnoremap <buffer> <F5> :w<CR>:!./gd %<CR>
    nnoremap <buffer> <F6> :w<CR>:!./gd -d %<CR>
    
    " Commandes locales
    command! -buffer Run :!./gd %
    command! -buffer Debug :!./gd -d %
    command! -buffer Ast :!./gd -d %
    
    " Status line
    setlocal statusline=%<%f\ %h%m%r%{&ft==#'goscript'?'[Goscript]':''}%=%-14.(%l,%c%V%)\ %P
endfunction

" Détection des fichiers sans extension
au BufRead,BufNewFile * if getline(1) =~ '^#!.*goscript' | setfiletype goscript | endif

" Auto-formatage à la sauvegarde (optionnel)
" au BufWritePre *.gjs :%s/\s\+$//e

" Définition des motifs de pliage
setlocal foldtext=GoscriptFoldText()

function! GoscriptFoldText()
    let line = getline(v:foldstart)
    let lines = v:foldend - v:foldstart + 1
    let name = substitute(line, '^\s*', '', '')
    let name = substitute(name, '{.*', '', '')
    return '+ ' . name . ' (' . lines . ' lines)'
endfunction
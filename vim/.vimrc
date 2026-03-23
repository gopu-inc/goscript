" Configuration Vim pour Goscript
set nocompatible
filetype plugin indent on
syntax on

" Couleurs
set t_Co=256
colorscheme goscript

" Numéros de ligne
set number
set relativenumber

" Indentation
set tabstop=4
set shiftwidth=4
set softtabstop=4
set expandtab
set autoindent
set smartindent

" Recherche
set hlsearch
set incsearch
set ignorecase
set smartcase

" Interface
set cursorline
set showmatch
set matchtime=2
set wildmenu
set ruler
set laststatus=2

" Folding
set foldmethod=syntax
set foldlevel=99

" Mappages utiles
nnoremap <F5> :w<CR>:!./gd %<CR>
nnoremap <F6> :w<CR>:!./gd -d %<CR>

" Commande pour exécuter le fichier courant
command! -buffer GsRun !./gd %
command! -buffer GsDebug !./gd -d %

" Commande pour formater
command! -buffer GsFormat :%s/\t/    /g

" Fonctions personnalisées
function! GsStatus()
  echo "Goscript mode active"
endfunction

autocmd FileType goscript call GsStatus()
marttab

" ============================================
" Recherche
" ============================================
set hlsearch
set incsearch
set ignorecase
set smartcase
set wrapscan

" ============================================
" Folding
" ============================================
set foldmethod=syntax
set foldlevel=99
set foldenable

" ============================================
" Historique et sauvegarde
" ============================================
set history=1000
set undolevels=1000
set backup
set backupdir=~/.vim/backup
set directory=~/.vim/tmp
set undodir=~/.vim/undo

" Créer les dossiers s'ils n'existent pas
silent! call mkdir(expand("~/.vim/backup"), "p")
silent! call mkdir(expand("~/.vim/tmp"), "p")
silent! call mkdir(expand("~/.vim/undo"), "p")

" ============================================
" Encodage
" ============================================
set encoding=utf-8
set fileencoding=utf-8
set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936

" ============================================
" Mappages globaux
" ============================================
" Leader
let mapleader = ","

" Navigation entre buffers
nnoremap <leader>n :bn<CR>
nnoremap <leader>p :bp<CR>
nnoremap <leader>d :bd<CR>

" Sauvegarde rapide
nnoremap <leader>w :w<CR>
nnoremap <leader>q :q<CR>
nnoremap <leader>x :x<CR>

" Recherche
nnoremap <leader>/ :nohlsearch<CR>
nnoremap <leader><space> :nohlsearch<CR>

" Folding
nnoremap <space> za
vnoremap <space> za

" ============================================
" Fonctions spécifiques Goscript
" ============================================

" Fonction pour exécuter le fichier courant
function! RunGoscript()
    let l:file = expand("%")
    if l:file =~ '\.gjs$'
        execute "w"
        execute "!./gd " . l:file
    else
        echo "Not a Goscript file"
    endif
endfunction

" Fonction pour déboguer
function! DebugGoscript()
    let l:file = expand("%")
    if l:file =~ '\.gjs$'
        execute "w"
        execute "!./gd -d " . l:file
    else
        echo "Not a Goscript file"
    endif
endfunction

" Fonction pour afficher l'AST
function! ShowAST()
    let l:file = expand("%")
    if l:file =~ '\.gjs$'
        execute "w"
        execute "!./gd -d " . l:file . " | less"
    else
        echo "Not a Goscript file"
    endif
endfunction

" Mappages pour Goscript
autocmd FileType goscript nnoremap <buffer> <F5> :call RunGoscript()<CR>
autocmd FileType goscript nnoremap <buffer> <F6> :call DebugGoscript()<CR>
autocmd FileType goscript nnoremap <buffer> <F7> :call ShowAST()<CR>

" Commandes Goscript
command! GsRun call RunGoscript()
command! GsDebug call DebugGoscript()
command! GsAst call ShowAST()

" ============================================
" Templates automatiques
" ============================================

" Template pour nouveau fichier Goscript
function! NewGoscriptFile()
    let l:filename = expand("%")
    if l:filename =~ '\.gjs$' && line("$") == 1 && getline(1) == ""
        call setline(1, "fn main() {")
        call setline(2, "    lt name = \"Goscript\"")
        call setline(3, "    ")
        call setline(4, "    ret 0")
        call setline(5, "}")
        call cur

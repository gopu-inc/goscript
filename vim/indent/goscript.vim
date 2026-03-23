" Vim indent file for Goscript
" Language: Goscript
" Maintainer: GOPU inc team
" Version: 2.0
" Last Change: 2026
" License: MIT

" Only load this indent file when no other was loaded
if exists("b:did_indent")
  finish
endif
let b:did_indent = 1

" Set indentation options
setlocal indentexpr=GetGoscriptIndent(v:lnum)
setlocal indentkeys+=0=},0=),0=],0=else,0=catch,0=finally,0=end,=end,=},=)

" Only define the function once
if exists("*GetGoscriptIndent")
  finish
endif

" ============================================
" Fonction principale d'indentation
" ============================================

function! GetGoscriptIndent(lnum)
  " Get previous non-empty line
  let prevlnum = prevnonblank(a:lnum - 1)
  if prevlnum == 0
    return 0
  endif

  " Get current line and previous line content
  let curline = getline(a:lnum)
  let prevline = getline(prevlnum)

  " Get base indentation from previous line
  let ind = indent(prevlnum)

  " ============================================
  " Augmenter l'indentation
  " ============================================

  " Blocs d'ouverture ( { )
  if prevline =~ '{\s*$'
    let ind += &sw
  endif

  " Parenthèses d'ouverture ( )
  if prevline =~ '(\s*$'
    let ind += &sw
  endif

  " Crochets d'ouverture [ ]
  if prevline =~ '\[\s*$'
    let ind += &sw
  endif

  " Déclarations de structures
  if prevline =~ '\<struct\s\+\w\+\s*{'
    let ind += &sw
  endif

  " Déclarations d'énumérations
  if prevline =~ '\<enm\s\+\w\+\s*{'
    let ind += &sw
  endif

  " Déclarations d'implémentations
  if prevline =~ '\<impl\s\+\w\+\s*{'
    let ind += &sw
  endif

  " Déclarations de fonctions
  if prevline =~ '\<fn\s\+\w\+\s*('
    let ind += &sw
  endif

  " Déclarations de modules
  if prevline =~ '\<packet\s\+\w\+\s*{'
    let ind += &sw
  endif

  " Conditions (if)
  if prevline =~ '\<if\s\+.*\s*$' && prevline !~ ';'
    let ind += &sw
  endif

  " Boucles (for, while)
  if prevline =~ '\<for\s\+.*\s*$' && prevline !~ ';'
    let ind += &sw
  endif
  if prevline =~ '\<while\s\+.*\s*$'
    let ind += &sw
  endif
  if prevline =~ '\<loop\s*$'
    let ind += &sw
  endif

  " Match statement
  if prevline =~ '\<match\s\+.*\s*$'
    let ind += &sw
  endif

  " Case statements
  if prevline =~ '=>\s*$'
    let ind += &sw
  endif

  " Début de bloc unsafe
  if prevline =~ '\<unsafe\s*{'
    let ind += &sw
  endif

  " Saut non-local
  if prevline =~ '\<nnl\s\+\w\+\s*{'
    let ind += &sw
  endif

  " Continuation de ligne avec opérateur
  if prevline =~ '[-+*/%&|^=<>!]\s*$'
    let ind += &sw / 2
  endif

  " Dictionnaires et tableaux multi-lignes
  if prevline =~ '{\s*$'
    let ind += &sw
  endif
  if prevline =~ '\[\s*$'
    let ind += &sw
  endif

  " ============================================
  " Diminuer l'indentation
  " ============================================

  " Fermeture d'accolade
  if curline =~ '^\s*}\s*'
    let ind -= &sw
  endif

  " Fermeture de parenthèse
  if curline =~ '^\s*)\s*'
    let ind -= &sw
  endif

  " Fermeture de crochet
  if curline =~ '^\s*]\s*'
    let ind -= &sw
  endif

  " Else statement
  if curline =~ '^\s*else\>'
    let ind -= &sw
  endif

  " Else if statement
  if curline =~ '^\s*}\s*else\s*if\>'
    let ind -= &sw
  endif

  " Match case
  if curline =~ '^\s*=>'
    let ind -= &sw / 2
  endif

  " ============================================
  " Cas spéciaux
  ============================================

  " Commentaires (maintenir indentation)
  if curline =~ '^\s*//'
    " Keep current indentation
    let ind = indent(prevlnum)
  endif

  " Multi-line comments
  if prevline =~ '/\*' && prevline !~ '\*/'
    let ind += &sw / 2
  endif
  if curline =~ '\*/'
    let ind -= &sw / 2
  endif

  " Retour à la ligne après une virgule
  if prevline =~ ',$' && prevline !~ ',\s*$'
    let ind += &sw / 2
  endif

  " ============================================
  " Correction des valeurs d'indentation
  ============================================

  " Éviter l'indentation négative
  if ind < 0
    let ind = 0
  endif

  return ind
endfunction

" ============================================
" Fonction d'indentation spécifique pour certains cas
" ============================================

function! GoscriptIndent()
  let lnum = line('.')
  let curind = indent(lnum)
  let expected = GetGoscriptIndent(lnum)
  
  if curind != expected
    call setline(lnum, substitute(getline(lnum), '^\s*', repeat(' ', expected), ''))
  endif
endfunction

" ============================================
" Commandes d'indentation
" ============================================

command! -buffer GsIndent :call GoscriptIndent()

" ============================================
" Auto-formatage à la sauvegarde
" ============================================

" Décommenter pour activer l'auto-formatage
" autocmd BufWritePre *.gjs call GsFormatFile()

function! GsFormatFile()
  let save_cursor = getpos('.')
  %s/\t/    /g
  %s/\s\+$//e
  call setpos('.', save_cursor)
  echo "File formatted"
endfunction

" ============================================
" Fonction pour formater la sélection
" ============================================

function! GsFormatSelection() range
  let save_cursor = getpos('.')
  execute a:firstline . ',' . a:lastline . 's/\t/    /g'
  execute a:firstline . ',' . a:lastline . 's/\s\+$//e'
  call setpos('.', save_cursor)
  echo "Selection formatted"
endfunction

" Commande pour formater la sélection
command! -range GsFormat <line1>,<line2>call GsFormatSelection()

" ============================================
" Fonction pour corriger l'indentation du fichier
" ============================================

function! GsFixIndent()
  let save_cursor = getpos('.')
  let lnum = 1
  while lnum <= line('$')
    call setline(lnum, substitute(getline(lnum), '^\s*', repeat(' ', GetGoscriptIndent(lnum)), ''))
    let lnum = lnum + 1
  endwhile
  call setpos('.', save_cursor)
  echo "Indentation fixed"
endfunction

command! GsFixIndent :call GsFixIndent()

" ============================================
" Informations de fin
" ============================================

let b:did_indent = 1
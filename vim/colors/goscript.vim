" Goscript Color Scheme
" A modern, vibrant color scheme for Goscript language
" Maintainer: GOPU inc team
" Version: 2.0
" Last Change: 2026

set background=dark
hi clear

if exists("syntax_on")
  syntax reset
endif

let g:colors_name = "goscript"

" ============================================
" Interface Vim (UI)
" ============================================

" Fond et texte de base
hi Normal          guifg=#e6e6e6 guibg=#1a1b26 ctermfg=254 ctermbg=235
hi NonText         guifg=#3b4261 guibg=#1a1b26 ctermfg=60 ctermbg=235
hi EndOfBuffer     guifg=#3b4261 guibg=#1a1b26 ctermfg=60 ctermbg=235

" Numéros de ligne
hi LineNr          guifg=#4a4f6e guibg=#1a1b26 ctermfg=60 ctermbg=235
hi CursorLineNr    guifg=#c0caf5 gui=bold ctermfg=189 cterm=bold
hi CursorLine      guibg=#24283b ctermbg=236

" Sélection et recherche
hi Visual          guibg=#2a2f4e ctermbg=238
hi Search          guifg=#1a1b26 guibg=#e5c07b ctermfg=235 ctermbg=180
hi IncSearch       guifg=#1a1b26 guibg=#e5c07b gui=bold ctermfg=235 ctermbg=180 cterm=bold
hi MatchParen      guifg=#e5c07b guibg=#2a2f4e gui=bold ctermfg=180 ctermbg=238 cterm=bold

" Status line
hi StatusLine      guifg=#c0caf5 guibg=#24283b ctermfg=189 ctermbg=236
hi StatusLineNC    guifg=#4a4f6e guibg=#24283b ctermfg=60 ctermbg=236
hi VertSplit       guifg=#24283b guibg=#24283b ctermfg=236 ctermbg=236

" Folding
hi Folded          guifg=#4a4f6e guibg=#1a1b26 ctermfg=60 ctermbg=235
hi FoldColumn      guifg=#4a4f6e guibg=#1a1b26 ctermfg=60 ctermbg=235

" Menu et popup
hi Pmenu           guifg=#c0caf5 guibg=#24283b ctermfg=189 ctermbg=236
hi PmenuSel        guifg=#1a1b26 guibg=#9ece6a ctermfg=235 ctermbg=149
hi PmenuThumb      guibg=#3b4261 ctermbg=60

" Messages
hi ErrorMsg        guifg=#f7768e guibg=#1a1b26 ctermfg=210 ctermbg=235
hi WarningMsg      guifg=#e5c07b ctermfg=180
hi ModeMsg         guifg=#9ece6a gui=bold ctermfg=149 cterm=bold
hi MoreMsg         guifg=#9ece6a ctermfg=149

" Diff
hi DiffAdd         guifg=#9ece6a guibg=#2a2f4e ctermfg=149 ctermbg=238
hi DiffChange      guifg=#e5c07b guibg=#2a2f4e ctermfg=180 ctermbg=238
hi DiffDelete      guifg=#f7768e guibg=#2a2f4e ctermfg=210 ctermbg=238
hi DiffText        guifg=#7aa2f7 guibg=#2a2f4e gui=bold ctermfg=75 ctermbg=238 cterm=bold

" ============================================
" Mots-clés et déclarations
" ============================================

" Mots-clés principaux (fn, struct, enum, impl, etc.)
hi goscriptDeclare    guifg=#bb9af7 gui=bold ctermfg=141 cterm=bold

" Variables (lt, cn, muts, const)
hi goscriptVariable   guifg=#7aa2f7 gui=bold ctermfg=75 cterm=bold

" Contrôle de flux (if, else, match)
hi goscriptConditional guifg=#e5c07b gui=bold ctermfg=180 cterm=bold

" Boucles (for, while, loop, in)
hi goscriptRepeat     guifg=#e5c07b ctermfg=180

" Sauts (break, continue, return, ret, jmp)
hi goscriptJump       guifg=#f7768e ctermfg=210

" Modules (import, export, from, as)
hi goscriptModule     guifg=#9ece6a ctermfg=149

" Visibilité et sécurité (pub, unsafe, only, sandbox)
hi goscriptScope      guifg=#9ece6a ctermfg=149

" ============================================
" Types
" ============================================

" Types numériques (int, i32, u64, etc.)
hi goscriptNumberType guifg=#4ec9b0 ctermfg=43

" Types flottants (float, f32, f64)
hi goscriptFloatType  guifg=#4ec9b0 ctermfg=43

" Types texte (string, str, char)
hi goscriptStringType guifg=#ce9178 ctermfg=173

" Types booléens (bool, boolean)
hi goscriptBoolType   guifg=#569cd6 ctermfg=68

" Types spéciaux (void, nil, any)
hi goscriptSpecialType guifg=#6a9955 ctermfg=71

" Types composites (dict, map, array, list)
hi goscriptCompositeType guifg=#9cdcfe ctermfg=117

" ============================================
" Valeurs littérales
" ============================================

" Booléens (true, false)
hi goscriptBoolean    guifg=#569cd6 gui=bold ctermfg=68 cterm=bold

" Null (nil, null, none)
hi goscriptNull       guifg=#ce9178 ctermfg=173

" Underscore (_)
hi goscriptUnderscore guifg=#858585 ctermfg=244

" ============================================
" Noms (identifiants)
" ============================================

" Noms de structures
hi goscriptStructName guifg=#c586c0 gui=bold ctermfg=176 cterm=bold
hi goscriptStructDef  guifg=#c586c0 gui=bold ctermfg=176 cterm=bold

" Noms d'enums
hi goscriptEnumName   guifg=#c586c0 gui=bold ctermfg=176 cterm=bold
hi goscriptEnumDef    guifg=#c586c0 gui=bold ctermfg=176 cterm=bold

" Noms d'implémentations
hi goscriptImplName   guifg=#c586c0 gui=bold ctermfg=176 cterm=bold
hi goscriptImplDef    guifg=#c586c0 gui=bold ctermfg=176 cterm=bold

" Noms de variables
hi goscriptVarName    guifg=#9cdcfe ctermfg=117
hi goscriptVariableName guifg=#9cdcfe ctermfg=117

" Constantes (MAJUSCULES)
hi goscriptConstName  guifg=#d7ba7d ctermfg=180

" ============================================
" Fonctions et méthodes
" ============================================

" Définitions de fonctions
hi goscriptFunctionDef guifg=#dcdcaa gui=bold ctermfg=187 cterm=bold

" Définitions de méthodes
hi goscriptMethodDef  guifg=#dcdcaa ctermfg=187

" Appels de fonctions
hi goscriptFunctionCall guifg=#d7ba7d ctermfg=180

" Lambdas
hi goscriptLambda     guifg=#c586c0 ctermfg=176

" ============================================
" Structures et champs
" ============================================

" Création de structures (new)
hi goscriptNewStruct  guifg=#c586c0 ctermfg=176

" Champs de structure
hi goscriptStructField guifg=#9cdcfe ctermfg=117

" Clés de dictionnaire
hi goscriptDictKey    guifg=#ce9178 ctermfg=173

" ============================================
" Opérateurs
" ============================================

" Opérateurs de comparaison (==, !=, <, >, <=, >=)
hi goscriptCompareOp  guifg=#ff8c00 gui=bold ctermfg=208 cterm=bold

" Opérateurs arithmétiques (+, -, *, /, %)
hi goscriptArithOp    guifg=#ff8c00 ctermfg=208

" Opérateurs logiques (&&, ||, !)
hi goscriptLogicOp    guifg=#ff8c00 ctermfg=208

" Opérateurs binaires (&, |, ^, <<, >>)
hi goscriptBitOp      guifg=#ff8c00 ctermfg=208

" Opérateurs spéciaux (=>, ->, ::, ., ?, ??)
hi goscriptSpecialOp  guifg=#ff8c00 gui=bold ctermfg=208 cterm=bold

" ============================================
" Commentaires
" ============================================

" Commentaires ligne
hi goscriptCommentLine guifg=#6a9955 ctermfg=71

" Commentaires documentation (///)
hi goscriptDocComment guifg=#6a9955 ctermfg=71

" Commentaires bloc (/* */)
hi goscriptCommentBlock guifg=#6a9955 ctermfg=71

" TODO et FIXME
hi goscriptTodo       guifg=#ff6b6b gui=bold ctermfg=203 cterm=bold

" Notes (NOTE, INFO, etc.)
hi goscriptNote       guifg=#e5c07b ctermfg=180

" ============================================
" Chaînes de caractères
" ============================================

" Chaînes normales
hi goscriptString     guifg=#ce9178 ctermfg=173

" Chaînes brutes (backticks)
hi goscriptRawString  guifg=#ce9178 ctermfg=173

" Caractères d'échappement (\n, \t, etc.)
hi goscriptEscape     guifg=#dcdcaa gui=bold ctermfg=187 cterm=bold

" ============================================
" Nombres
" ============================================

" Nombres décimaux
hi goscriptDecimal    guifg=#b5cea8 ctermfg=151

" Nombres hexadécimaux (0x...)
hi goscriptHex        guifg=#b5cea8 ctermfg=151

" Nombres binaires (0b...)
hi goscriptBinary     guifg=#b5cea8 ctermfg=151

" Nombres octaux (0o...)
hi goscriptOctal      guifg=#b5cea8 ctermfg=151

" Nombres flottants
hi goscriptFloat      guifg=#b5cea8 ctermfg=151

" ============================================
" Délimiteurs
" ============================================

" Parenthèses ()
hi goscriptParen      guifg=#858585 ctermfg=244

" Accolades {}
hi goscriptBrace      guifg=#858585 ctermfg=244

" Crochets []
hi goscriptBracket    guifg=#858585 ctermfg=244

" Chevrons <>
hi goscriptAngle      guifg=#858585 ctermfg=244

" ============================================
" Liens pour la compatibilité
" ============================================

" Liens vers les groupes standard pour fallback
hi link goscriptKeyword goscriptDeclare
hi link goscriptStatement goscriptJump

" ============================================
" Informations de fin
" ============================================

let g:colors_name = "goscript"

" Fin du fichier de couleurs

" Vim syntax file for Goscript
" Language: Goscript
" Maintainer: GOPU inc team
" Last Change: 2026
" Use extension: .gjs

" Quit if syntax already loaded
if exists("b:current_syntax")
  finish
endif

" ============================================
" Mots-clés par catégorie
" ============================================

" Déclarations de fonctions et structures
syn keyword goscriptDeclare fn struct enum impl packet module
syn keyword goscriptDeclare nextgroup=goscriptStructName skipwhite

" Variables et mutabilité
syn keyword goscriptVariable lt cn muts const
syn keyword goscriptVariable nextgroup=goscriptVarName skipwhite

" Contrôle de flux
syn keyword goscriptConditional if else match
syn keyword goscriptConditional nextgroup=goscriptCondition skipwhite

" Boucles
syn keyword goscriptRepeat for while loop in
syn keyword goscriptRepeat nextgroup=goscriptLoopVar skipwhite

" Sauts
syn keyword goscriptJump break continue return ret jmp nnl
syn keyword goscriptJump nextgroup=goscriptJumpTarget skipwhite

" Module système
syn keyword goscriptModule import export from as
syn keyword goscriptModule nextgroup=goscriptModulePath skipwhite

" Visibilité et sécurité
syn keyword goscriptScope pub private protected
syn keyword goscriptSecurity only sandbox timeout unsafe

" ============================================
" Types (avec couleurs distinctes)
" ============================================

" Types numériques
syn keyword goscriptNumberType int i8 i16 i32 i64 u8 u16 u32 u64
syn keyword goscriptFloatType float f32 f64 double

" Types texte
syn keyword goscriptStringType string str char

" Types logiques
syn keyword goscriptBoolType bool boolean

" Types spéciaux
syn keyword goscriptSpecialType void nil any unknown

" Types composites
syn keyword goscriptCompositeType dict map array list vector tuple

" ============================================
" Valeurs littérales
" ============================================

syn keyword goscriptBoolean true false
syn keyword goscriptNull nil null none
syn keyword goscriptUnderscore _

" ============================================
" Noms (structures, variables, etc)
" ============================================

" Noms de structures (après struct)
syn match goscriptStructName "\<\w\+\>" contained
syn match goscriptStructDef "^\s*struct\s\+\zs\w\+\ze"

" Noms d'enums
syn match goscriptEnumName "\<\w\+\>" contained
syn match goscriptEnumDef "^\s*enm\s\+\zs\w\+\ze"

" Noms d'implémentations
syn match goscriptImplName "\<\w\+\>" contained
syn match goscriptImplDef "^\s*impl\s\+\zs\w\+\ze"

" Noms de variables
syn match goscriptVarName "\<\w\+\>" contained
syn match goscriptVariableName "\<[a-z_][a-zA-Z0-9_]*\>"

" Noms de constantes (uppercase)
syn match goscriptConstName "\<[A-Z][A-Z0-9_]*\>"

" ============================================
" Fonctions et méthodes
" ============================================

" Définitions de fonctions
syn match goscriptFunctionDef "^\s*fn\s\+\zs\w\+\ze\s*("
syn match goscriptMethodDef "^\s*impl\s\+\w\+\s\+\zs\w\+\ze\s*("

" Appels de fonctions
syn match goscriptFunctionCall "\<\w\+\ze\s*("

" Lambdas
syn keyword goscriptLambda lambda

" ============================================
" Structures et initialisation
" ============================================

" Création de structures avec new
syn match goscriptNewStruct "new\s\+\zs\w\+\ze\s*{"

" Champs de structure
syn match goscriptStructField "\w\+\ze\s*:\s*\w\+"

" Clés de dictionnaire
syn match goscriptDictKey "\w\+\ze\s*:"

" ============================================
" Opérateurs (avec catégories distinctes)
" ============================================

" Opérateurs de comparaison
syn match goscriptCompareOp "=="
syn match goscriptCompareOp "!="
syn match goscriptCompareOp "<="
syn match goscriptCompareOp ">="
syn match goscriptCompareOp "<"
syn match goscriptCompareOp ">"

" Opérateurs arithmétiques
syn match goscriptArithOp "[+\-*/%]"
syn match goscriptArithOp "+="
syn match goscriptArithOp "-="
syn match goscriptArithOp "*="
syn match goscriptArithOp "/="
syn match goscriptArithOp "%="

" Opérateurs logiques
syn match goscriptLogicOp "&&"
syn match goscriptLogicOp "||"
syn match goscriptLogicOp "!"

" Opérateurs binaires
syn match goscriptBitOp "&"
syn match goscriptBitOp "|"
syn match goscriptBitOp "^"
syn match goscriptBitOp "<<"
syn match goscriptBitOp ">>"
syn match goscriptBitOp "~"

" Opérateurs spéciaux
syn match goscriptSpecialOp "=>"
syn match goscriptSpecialOp "->"
syn match goscriptSpecialOp "|>"
syn match goscriptSpecialOp "::"
syn match goscriptSpecialOp "\.\."
syn match goscriptSpecialOp "\.\..="
syn match goscriptSpecialOp "?"
syn match goscriptSpecialOp "??"
syn match goscriptSpecialOp "="

" ============================================
" Commentaires (avec support TODO)
" ============================================

" Commentaires ligne unique
syn region goscriptCommentLine start="//" end="$" contains=goscriptTodo,goscriptNote
syn region goscriptDocComment start="///" end="$" contains=goscriptTodo

" Commentaires bloc
syn region goscriptCommentBlock start="/\*" end="\*/" contains=goscriptTodo,goscriptNote

" Mots spéciaux dans les commentaires
syn keyword goscriptTodo contained TODO FIXME XXX HACK BUG
syn keyword goscriptNote contained NOTE INFO OPTIMIZE WARNING

" ============================================
" Chaînes de caractères
" ============================================

" Chaînes simples avec échappement
syn region goscriptString start='"' end='"' skip='\\"' contains=goscriptEscape

" Chaînes multilignes (backticks)
syn region goscriptRawString start='`' end='`'

" Caractères d'échappement
syn match goscriptEscape contained "\\[nrt\\\"'0]"
syn match goscriptEscape contained "\\x[0-9a-fA-F]\{2}"
syn match goscriptEscape contained "\\u[0-9a-fA-F]\{4}"

" ============================================
" Nombres (tous formats)
" ============================================

" Entiers décimaux
syn match goscriptDecimal "\<[0-9]\+\>"

" Entiers hexadécimaux
syn match goscriptHex "\<0x[0-9a-fA-F]\+\>"

" Entiers binaires
syn match goscriptBinary "\<0b[01]\+\>"

" Entiers octaux
syn match goscriptOctal "\<0o[0-7]\+\>"

" Flottants
syn match goscriptFloat "\<[0-9]\+\.[0-9]*\>"
syn match goscriptFloat "\<[0-9]*\.[0-9]\+\>"
syn match goscriptFloat "\<[0-9]\+[eE][+-]\?[0-9]\+\>"
syn match goscriptFloat "\<[0-9]\+\.[0-9]\+[eE][+-]\?[0-9]\+\>"

" ============================================
" Délimiteurs et parenthèses
" ============================================

syn match goscriptParen "("
syn match goscriptParen ")"
syn match goscriptBrace "{"
syn match goscriptBrace "}"
syn match goscriptBracket "\["
syn match goscriptBracket "\]"
syn match goscriptAngle "<"
syn match goscriptAngle ">"

" ============================================
" Liens avec les couleurs (thème moderne)
" ============================================

" Mots-clés par catégorie
hi def link goscriptDeclare Keyword
hi def link goscriptVariable Identifier
hi def link goscriptConditional Conditional
hi def link goscriptRepeat Repeat
hi def link goscriptJump Special
hi def link goscriptModule Include
hi def link goscriptScope PreProc
hi def link goscriptSecurity PreProc

" Types
hi def link goscriptNumberType Type
hi def link goscriptFloatType Type
hi def link goscriptStringType Type
hi def link goscriptBoolType Type
hi def link goscriptSpecialType Type
hi def link goscriptCompositeType Structure

" Valeurs
hi def link goscriptBoolean Boolean
hi def link goscriptNull Constant
hi def link goscriptUnderscore Special

" Noms
hi def link goscriptStructName Structure
hi def link goscriptStructDef Structure
hi def link goscriptEnumName Structure
hi def link goscriptEnumDef Structure
hi def link goscriptImplName Structure
hi def link goscriptImplDef Structure
hi def link goscriptVarName Identifier
hi def link goscriptVariableName Identifier
hi def link goscriptConstName Constant

" Fonctions
hi def link goscriptFunctionDef Function
hi def link goscriptMethodDef Function
hi def link goscriptFunctionCall Function
hi def link goscriptLambda Function

" Structures et champs
hi def link goscriptNewStruct Structure
hi def link goscriptStructField Identifier
hi def link goscriptDictKey String

" Opérateurs
hi def link goscriptCompareOp Operator
hi def link goscriptArithOp Operator
hi def link goscriptLogicOp Operator
hi def link goscriptBitOp Operator
hi def link goscriptSpecialOp Operator

" Commentaires
hi def link goscriptCommentLine Comment
hi def link goscriptDocComment Comment
hi def link goscriptCommentBlock Comment
hi def link goscriptTodo Todo
hi def link goscriptNote SpecialComment

" Chaînes
hi def link goscriptString String
hi def link goscriptRawString String
hi def link goscriptEscape SpecialChar

" Nombres
hi def link goscriptDecimal Number
hi def link goscriptHex Number
hi def link goscriptBinary Number
hi def link goscriptOctal Number
hi def link goscriptFloat Float

" Délimiteurs
hi def link goscriptParen Delimiter
hi def link goscriptBrace Delimiter
hi def link goscriptBracket Delimiter
hi def link goscriptAngle Delimiter

let b:current_syntax = "goscript"

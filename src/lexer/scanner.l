%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

extern int yylineno;
extern char* yytext;

void yyerror(const char* msg);
%}

%option noyywrap
%option yylineno

%%

 /* Mots-clés */
"async"                 { return TOKEN_ASYNC; }
"await"                 { return TOKEN_AWAIT; }
"spawn"                 { return TOKEN_SPAWN; }
"fn"                    { return TOKEN_FN; }
"lt"                    { return TOKEN_LET; }
"cn"                    { return TOKEN_CONST; }
"ret"                   { return TOKEN_RETURN; }
"if"                    { return TOKEN_IF; }
"else"                  { return TOKEN_ELSE; }
"for"                   { return TOKEN_FOR; }
"while"                 { return TOKEN_WHILE; }
"loop"                  { return TOKEN_LOOP; }
"break"                 { return TOKEN_BREAK; }
"continue"              { return TOKEN_CONTINUE; }
"lambda"                { return TOKEN_LAMBDA; }
"nnl"                   { return TOKEN_NNL; }
"jmp"                   { return TOKEN_JMP; }
"import"                { return TOKEN_IMPORT; }
"export"                { return TOKEN_EXPORT; }
"packet"                { return TOKEN_PACKET; }
"struct"                { return TOKEN_STRUCT; }
"enm"                   { return TOKEN_ENUM; }
"impl"                  { return TOKEN_IMPL; }
"match"                 { return TOKEN_MATCH; }
"type"                  { return TOKEN_TYPE; }
"true"                  { return TOKEN_TRUE; }
"false"                 { return TOKEN_FALSE; }
"nil"                   { return TOKEN_NIL; }
"as"                    { return TOKEN_AS; }
"in"                    { return TOKEN_IN; }
"from"                  { return TOKEN_FROM; }
"pub"                   { return TOKEN_PUB; }
"new"                   { return TOKEN_NEW; }
"module"                { return TOKEN_MODULE; }
"only"                  { return TOKEN_ONLY; }
"sandbox"               { return TOKEN_SANDBOX; }
"security"              { return TOKEN_SECURITY; }
"extends"               { return TOKEN_EXTENDS; }
"dict"                  { return TOKEN_DICT; }
"map"                   { return TOKEN_MAP; }
"timeout"               { return TOKEN_TIMEOUT; }
"muts"                  { return TOKEN_MUTS; }
"unsafe"                { return TOKEN_UNSAFE; }
/* Mots-clés pour try/catch */
"try"                   { return TOKEN_TRY; }
"catch"                 { return TOKEN_CATCH; }
"finally"               { return TOKEN_FINALLY; }
"throw"                 { return TOKEN_THROW; }
"except"                { return TOKEN_EXCEPT; }
"raise"                 { return TOKEN_RAISE; }

"_"                     { return TOKEN_UNDERSCORE; }

 /* Types primitifs (mots-clés spéciaux) */
"int"                   { yylval.string = strdup(yytext); return TOKEN_IDENTIFIER; }
"float"                 { yylval.string = strdup(yytext); return TOKEN_IDENTIFIER; }
"string"                { yylval.string = strdup(yytext); return TOKEN_IDENTIFIER; }
"bool"                  { yylval.string = strdup(yytext); return TOKEN_IDENTIFIER; }
"void"                  { yylval.string = strdup(yytext); return TOKEN_IDENTIFIER; }


"Union"                 { return TOKEN_UNION; }
"Optional"              { return TOKEN_OPTIONAL_TYPE; }
"Any"                   { return TOKEN_ANY; }
 /* Identifiants */
[a-zA-Z_][a-zA-Z0-9_]*  { 
    yylval.string = strdup(yytext); 
    return TOKEN_IDENTIFIER; 
}

 /* Nombres */
[0-9]+                  {
    yylval.number = atoi(yytext);
    return TOKEN_NUMBER;
}

[0-9]+\.[0-9]+          {
    yylval.float_val = atof(yytext);
    return TOKEN_FLOAT;
}

0x[0-9a-fA-F]+          {
    yylval.number = strtol(yytext, NULL, 16);
    return TOKEN_NUMBER;
}

0[0-7]+                 {
    yylval.number = strtol(yytext, NULL, 8);
    return TOKEN_NUMBER;
}

0b[01]+                 {
    yylval.number = strtol(yytext + 2, NULL, 2);
    return TOKEN_NUMBER;
}

 /* f-strings avec guillemets doubles */
f\"(\\.|[^"\\])*\"     {
    int len = strlen(yytext);
    char* raw = malloc(len - 2);
    int i, j = 0;
    for (i = 2; i < len - 1; i++) {
        if (yytext[i] == '\\' && i+1 < len-1) {
            i++;
            switch (yytext[i]) {
                case 'n': raw[j++] = '\n'; break;
                case 't': raw[j++] = '\t'; break;
                case 'r': raw[j++] = '\r'; break;
                case '\\': raw[j++] = '\\'; break;
                case '"': raw[j++] = '"'; break;
                case '\'': raw[j++] = '\''; break;
                case '{': raw[j++] = '{'; break;
                case '}': raw[j++] = '}'; break;
                case 'a': raw[j++] = '\a'; break;
                case 'b': raw[j++] = '\b'; break;
                case 'f': raw[j++] = '\f'; break;
                case 'v': raw[j++] = '\v'; break;
                case '0': raw[j++] = '\0'; break;
                default: raw[j++] = yytext[i]; break;
            }
        } else {
            raw[j++] = yytext[i];
        }
    }
    raw[j] = '\0';
    yylval.string = raw;
    return TOKEN_F_STRING;
}

 /* f-strings avec apostrophes simples */
f\'(\\.|[^'\\])*\'     {
    int len = strlen(yytext);
    char* raw = malloc(len - 2);
    int i, j = 0;
    for (i = 2; i < len - 1; i++) {
        if (yytext[i] == '\\' && i+1 < len-1) {
            i++;
            switch (yytext[i]) {
                case 'n': raw[j++] = '\n'; break;
                case 't': raw[j++] = '\t'; break;
                case 'r': raw[j++] = '\r'; break;
                case '\\': raw[j++] = '\\'; break;
                case '\'': raw[j++] = '\''; break;
                case '"': raw[j++] = '"'; break;
                case '{': raw[j++] = '{'; break;
                case '}': raw[j++] = '}'; break;
                case 'a': raw[j++] = '\a'; break;
                case 'b': raw[j++] = '\b'; break;
                case 'f': raw[j++] = '\f'; break;
                case 'v': raw[j++] = '\v'; break;
                case '0': raw[j++] = '\0'; break;
                default: raw[j++] = yytext[i]; break;
            }
        } else {
            raw[j++] = yytext[i];
        }
    }
    raw[j] = '\0';
    yylval.string = raw;
    return TOKEN_F_STRING;
}

 /* Chaînes avec guillemets doubles */
\"(\\.|[^"\\])*\"       {
    int len = strlen(yytext);
    char* str = malloc(len - 1);
    int i, j = 0;
    for (i = 1; i < len - 1; i++) {
        if (yytext[i] == '\\' && i+1 < len-1) {
            i++;
            switch (yytext[i]) {
                case 'n': str[j++] = '\n'; break;
                case 't': str[j++] = '\t'; break;
                case 'r': str[j++] = '\r'; break;
                case '\\': str[j++] = '\\'; break;
                case '"': str[j++] = '"'; break;
                case '\'': str[j++] = '\''; break;
                case 'a': str[j++] = '\a'; break;
                case 'b': str[j++] = '\b'; break;
                case 'f': str[j++] = '\f'; break;
                case 'v': str[j++] = '\v'; break;
                case '0': str[j++] = '\0'; break;
                default: str[j++] = yytext[i]; break;
            }
        } else {
            str[j++] = yytext[i];
        }
    }
    str[j] = '\0';
    yylval.string = str;
    return TOKEN_STRING;
}

 /* Chaînes avec apostrophes simples */
\'(\\.|[^'\\])*\'       {
    int len = strlen(yytext);
    char* str = malloc(len - 1);
    int i, j = 0;
    for (i = 1; i < len - 1; i++) {
        if (yytext[i] == '\\' && i+1 < len-1) {
            i++;
            switch (yytext[i]) {
                case 'n': str[j++] = '\n'; break;
                case 't': str[j++] = '\t'; break;
                case 'r': str[j++] = '\r'; break;
                case '\\': str[j++] = '\\'; break;
                case '\'': str[j++] = '\''; break;
                case '"': str[j++] = '"'; break;
                case 'a': str[j++] = '\a'; break;
                case 'b': str[j++] = '\b'; break;
                case 'f': str[j++] = '\f'; break;
                case 'v': str[j++] = '\v'; break;
                case '0': str[j++] = '\0'; break;
                default: str[j++] = yytext[i]; break;
            }
        } else {
            str[j++] = yytext[i];
        }
    }
    str[j] = '\0';
    yylval.string = str;
    return TOKEN_STRING;
}

 /* Chaînes multi-lignes (guillemets triples) */
\"\"\"([^\"\\]|\\.)*\"\"\"     {
    int len = strlen(yytext);
    char* str = malloc(len - 5);
    int i, j = 0;
    for (i = 3; i < len - 3; i++) {
        if (yytext[i] == '\\' && i+1 < len-3) {
            i++;
            switch (yytext[i]) {
                case 'n': str[j++] = '\n'; break;
                case 't': str[j++] = '\t'; break;
                case 'r': str[j++] = '\r'; break;
                case '\\': str[j++] = '\\'; break;
                case '"': str[j++] = '"'; break;
                case '\'': str[j++] = '\''; break;
                default: str[j++] = yytext[i]; break;
            }
        } else {
            str[j++] = yytext[i];
        }
    }
    str[j] = '\0';
    yylval.string = str;
    return TOKEN_STRING;
}

 /* Chaînes multi-lignes (apostrophes triples) */
\'\'\'([^'\\]|\\.)*\'\'\'     {
    int len = strlen(yytext);
    char* str = malloc(len - 5);
    int i, j = 0;
    for (i = 3; i < len - 3; i++) {
        if (yytext[i] == '\\' && i+1 < len-3) {
            i++;
            switch (yytext[i]) {
                case 'n': str[j++] = '\n'; break;
                case 't': str[j++] = '\t'; break;
                case 'r': str[j++] = '\r'; break;
                case '\\': str[j++] = '\\'; break;
                case '\'': str[j++] = '\''; break;
                case '"': str[j++] = '"'; break;
                default: str[j++] = yytext[i]; break;
            }
        } else {
            str[j++] = yytext[i];
        }
    }
    str[j] = '\0';
    yylval.string = str;
    return TOKEN_STRING;
}

 /* Opérateurs */
"+"                     { return TOKEN_PLUS; }
"-"                     { return TOKEN_MINUS; }
"*"                     { return TOKEN_MULTIPLY; }
"/"                     { return TOKEN_DIVIDE; }
"%"                     { return TOKEN_MODULO; }
"="                     { return TOKEN_ASSIGN; }
"+="                    { return TOKEN_PLUS_ASSIGN; }
"-="                    { return TOKEN_MINUS_ASSIGN; }
"*="                    { return TOKEN_MULTIPLY_ASSIGN; }
"/="                    { return TOKEN_DIVIDE_ASSIGN; }
"%="                    { return TOKEN_MODULO_ASSIGN; }
"=="                    { return TOKEN_EQ; }
"!="                    { return TOKEN_NEQ; }
"<"                     { return TOKEN_LT; }
"<="                    { return TOKEN_LTE; }
">"                     { return TOKEN_GT; }
">="                    { return TOKEN_GTE; }
"&&"                    { return TOKEN_AND; }
"||"                    { return TOKEN_OR; }
"!"                     { return TOKEN_NOT; }
"&"                     { return TOKEN_AMP; }
"|"                     { return TOKEN_PIPE; }
"^"                     { return TOKEN_XOR; }
"<<"                    { return TOKEN_LSHIFT; }
">>"                    { return TOKEN_RSHIFT; }
"::"                    { return TOKEN_DOUBLE_COLON; }
"."                     { return TOKEN_DOT; }
":"                     { return TOKEN_COLON; }
";"                     { return TOKEN_SEMICOLON; }
","                     { return TOKEN_COMMA; }
"->"                    { return TOKEN_ARROW; }
"=>"                    { return TOKEN_FAT_ARROW; }
"|>"                    { return TOKEN_PIPE_FORWARD; }
"?"                     { return TOKEN_OPTIONAL; }
"??"                    { return TOKEN_COALESCE; }
".."                    { return TOKEN_RANGE; }
"..="                   { return TOKEN_RANGE_INC; }

 /* Délimiteurs */
"("                     { return TOKEN_LPAREN; }
")"                     { return TOKEN_RPAREN; }
"{"                     { return TOKEN_LBRACE; }
"}"                     { return TOKEN_RBRACE; }
"["                     { return TOKEN_LBRACKET; }
"]"                     { return TOKEN_RBRACKET; }

 /* Commentaires */
"//".*                  { /* Ignorer */ }
"/*"([^*]|\*+[^*/])*\*+"/" { /* Ignorer */ }

 /* Espaces - inclut \r pour Windows */
[ \t\r\n]+              { /* Ignorer */ }

 /* Caractère invalide */
.                       { 
    fprintf(stderr, "Error at line %d: Invalid character '%c' (ASCII %d)\n", 
            yylineno, yytext[0], yytext[0]);
    yyerror("Invalid character"); 
}

%%

/* Fonction pour nettoyer la mémoire si nécessaire */
void cleanup_scanner(void) {
    /* Rien à faire pour l'instant */
}

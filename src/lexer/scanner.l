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
%option nodefault

%x COMMENT
%x STRING

%%

 /* Mots-clés */
"fn"                    { return TOKEN_FN; }
"lt"                    { return TOKEN_LET; }
"cn"                    { return TOKEN_CONST; }
"ret"                   { return TOKEN_RETURN; }
"if"                    { return TOKEN_IF; }
"else"                  { return TOKEN_ELSE; }
"elseif"                { return TOKEN_ELSEIF; }
"for"                   { return TOKEN_FOR; }
"while"                 { return TOKEN_WHILE; }
"loop"                  { return TOKEN_LOOP; }
"break"                 { return TOKEN_BREAK; }
"continue"              { return TOKEN_CONTINUE; }
"match"                 { return TOKEN_MATCH; }
"struct"                { return TOKEN_STRUCT; }
"enm"                   { return TOKEN_ENUM; }
"impl"                  { return TOKEN_IMPL; }
"import"                { return TOKEN_IMPORT; }
"packet"                { return TOKEN_PACKET; }
"export"                { return TOKEN_EXPORT; }
"type"                  { return TOKEN_TYPE; }
"true"                  { return TOKEN_TRUE; }
"false"                 { return TOKEN_FALSE; }
"nil"                   { return TOKEN_NIL; }
"as"                    { return TOKEN_AS; }
"in"                    { return TOKEN_IN; }
"from"                  { return TOKEN_FROM; }

 /* Identifiants */
[a-zA-Z_][a-zA-Z0-9_]*  { 
    yylval.string = strdup(yytext); 
    return TOKEN_IDENTIFIER; 
}

 /* Nombres décimaux */
[0-9]+                  {
    yylval.number = atoi(yytext);
    return TOKEN_NUMBER;
}

[0-9]+\.[0-9]+          {
    yylval.float_val = atof(yytext);
    return TOKEN_FLOAT;
}

 /* Nombres hexadécimaux */
0x[0-9a-fA-F]+          {
    yylval.number = strtol(yytext, NULL, 16);
    return TOKEN_NUMBER;
}

 /* Nombres binaires */
0b[01]+                 {
    yylval.number = strtol(yytext+2, NULL, 2);
    return TOKEN_NUMBER;
}

 /* Nombres octaux */
0[0-7]+                 {
    yylval.number = strtol(yytext, NULL, 8);
    return TOKEN_NUMBER;
}

 /* Chaînes de caractères */
\"                      {
    BEGIN(STRING);
    yylval.string = malloc(1024);
    yylval.string[0] = '\0';
}

<STRING>{
    \"                      {
        BEGIN(INITIAL);
        return TOKEN_STRING;
    }
    \n                      {
        yyerror("Unterminated string");
        BEGIN(INITIAL);
    }
    \\n                     { strcat(yylval.string, "\n"); }
    \\t                     { strcat(yylval.string, "\t"); }
    \\r                     { strcat(yylval.string, "\r"); }
    \\\"                    { strcat(yylval.string, "\""); }
    \\\'                    { strcat(yylval.string, "'"); }
    \\\\                    { strcat(yylval.string, "\\"); }
    [^\\\n\"]+              { strcat(yylval.string, yytext); }
    .                       { strcat(yylval.string, yytext); }
}

 /* Opérateurs arithmétiques */
"+"                     { return TOKEN_PLUS; }
"-"                     { return TOKEN_MINUS; }
"*"                     { return TOKEN_MULTIPLY; }
"/"                     { return TOKEN_DIVIDE; }
"%"                     { return TOKEN_MODULO; }

 /* Opérateurs d'assignation */
"="                     { return TOKEN_ASSIGN; }
"+="                    { return TOKEN_PLUS_ASSIGN; }
"-="                    { return TOKEN_MINUS_ASSIGN; }
"*="                    { return TOKEN_MULTIPLY_ASSIGN; }
"/="                    { return TOKEN_DIVIDE_ASSIGN; }
"%="                    { return TOKEN_MODULO_ASSIGN; }

 /* Opérateurs de comparaison */
"=="                    { return TOKEN_EQ; }
"!="                    { return TOKEN_NEQ; }
"<"                     { return TOKEN_LT; }
"<="                    { return TOKEN_LTE; }
">"                     { return TOKEN_GT; }
">="                    { return TOKEN_GTE; }

 /* Opérateurs logiques */
"&&"                    { return TOKEN_AND; }
"||"                    { return TOKEN_OR; }
"!"                     { return TOKEN_NOT; }

 /* Opérateurs bit à bit */
"&"                     { return TOKEN_AMP; }
"|"                     { return TOKEN_PIPE; }
"^"                     { return TOKEN_XOR; }
"~"                     { return TOKEN_TILDE; }
"<<"                    { return TOKEN_LSHIFT; }
">>"                    { return TOKEN_RSHIFT; }

 /* Opérateurs d'incrémentation/décrémentation */
"++"                    { return TOKEN_INC; }
"--"                    { return TOKEN_DEC; }

 /* Opérateurs spéciaux */
"->"                    { return TOKEN_ARROW; }
"=>"                    { return TOKEN_FAT_ARROW; }
".."                    { return TOKEN_RANGE; }
"..="                   { return TOKEN_RANGE_INC; }
"??"                    { return TOKEN_COALESCE; }
"?"                     { return TOKEN_OPTIONAL; }
":"                     { return TOKEN_COLON; }
";"                     { return TOKEN_SEMICOLON; }
","                     { return TOKEN_COMMA; }
"."                     { return TOKEN_DOT; }
"::"                    { return TOKEN_DOUBLE_COLON; }
"|>"                    { return TOKEN_PIPE_FORWARD; }
"@"                     { return TOKEN_AT; }

 /* Délimiteurs */
"("                     { return TOKEN_LPAREN; }
")"                     { return TOKEN_RPAREN; }
"{"                     { return TOKEN_LBRACE; }
"}"                     { return TOKEN_RBRACE; }
"["                     { return TOKEN_LBRACKET; }
"]"                     { return TOKEN_RBRACKET; }

 /* Commentaires */
"//".*                  { /* Ignore line comment */ }
"/*"                    { BEGIN(COMMENT); }

<COMMENT>{
    "*/"                    { BEGIN(INITIAL); }
    .                       { /* Ignore */ }
    \n                      { /* Ignore */ }
}

 /* Espaces blancs */
[ \t\r\n]+              { /* Ignore */ }

 /* Caractères invalides */
.                       { 
    char msg[256];
    snprintf(msg, sizeof(msg), "Invalid character '%c' (ASCII %d)", yytext[0], yytext[0]);
    yyerror(msg);
}

%%

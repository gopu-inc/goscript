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
"import"                { return TOKEN_IMPORT; }
"packet"                { return TOKEN_PACKET; }
"true"                  { return TOKEN_TRUE; }
"false"                 { return TOKEN_FALSE; }
"nil"                   { return TOKEN_NIL; }

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

 /* Chaînes */
\"[^\"]*\"              {
    yytext[strlen(yytext)-1] = '\0';
    yylval.string = strdup(yytext+1);
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
":"                     { return TOKEN_COLON; }
";"                     { return TOKEN_SEMICOLON; }
","                     { return TOKEN_COMMA; }
"."                     { return TOKEN_DOT; }

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

 /* Espaces */
[ \t\r\n]+              { /* Ignorer */ }

.                       { yyerror("Invalid character"); }

%%

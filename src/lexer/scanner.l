%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
#include "ast.h"

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
"elseif"                { return TOKEN_ELSEIF; }
"then"                  { return TOKEN_THEN; }
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
"go"                    { return TOKEN_GO; }
"chan"                  { return TOKEN_CHAN; }
"select"                { return TOKEN_SELECT; }
"try"                   { return TOKEN_TRY; }
"catch"                 { return TOKEN_CATCH; }
"finally"               { return TOKEN_FINALLY; }
"nil"                   { return TOKEN_NIL; }
"true"                  { return TOKEN_TRUE; }
"false"                 { return TOKEN_FALSE; }
"where"                 { return TOKEN_WHERE; }
"as"                    { return TOKEN_AS; }

/* Identifiants et littéraux */
[a-zA-Z_][a-zA-Z0-9_]*  { 
    yylval.string = strdup(yytext); 
    return TOKEN_IDENTIFIER; 
}

[0-9]+                  {
    yylval.number = atoi(yytext);
    return TOKEN_NUMBER;
}

[0-9]+\.[0-9]+          {
    yylval.float_val = atof(yytext);
    return TOKEN_FLOAT;
}

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
"->"                    { return TOKEN_ARROW; }
"=>"                    { return TOKEN_FAT_ARROW; }
".."                    { return TOKEN_RANGE; }
"..="                   { return TOKEN_RANGE_INC; }
"??"                    { return TOKEN_COALESCE; }
"?"                     { return TOKEN_OPTIONAL; }
"!"                     { return TOKEN_BANG; }
":"                     { return TOKEN_COLON; }
";"                     { return TOKEN_SEMICOLON; }
","                     { return TOKEN_COMMA; }
"."                     { return TOKEN_DOT; }
"::"                    { return TOKEN_DOUBLE_COLON; }
"|>"                    { return TOKEN_PIPE_FORWARD; }

/* Délimiteurs */
"("                     { return TOKEN_LPAREN; }
")"                     { return TOKEN_RPAREN; }
"{"                     { return TOKEN_LBRACE; }
"}"                     { return TOKEN_RBRACE; }
"["                     { return TOKEN_LBRACKET; }
"]"                     { return TOKEN_RBRACKET; }

/* Commentaires */
"//".*                  { /* Ignorer ligne */ }
"/*"([^*]|\*+[^*/])*\*+"/" { /* Ignorer bloc */ }

/* Espaces blancs */
[ \t\r\n]+              { /* Ignorer */ }

.                       { yyerror("Caractère invalide"); }

%%

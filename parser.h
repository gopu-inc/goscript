/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_FN = 258,                /* TOKEN_FN  */
    TOKEN_LET = 259,               /* TOKEN_LET  */
    TOKEN_CONST = 260,             /* TOKEN_CONST  */
    TOKEN_RETURN = 261,            /* TOKEN_RETURN  */
    TOKEN_IF = 262,                /* TOKEN_IF  */
    TOKEN_ELSE = 263,              /* TOKEN_ELSE  */
    TOKEN_NEW = 264,               /* TOKEN_NEW  */
    TOKEN_FOR = 265,               /* TOKEN_FOR  */
    TOKEN_WHILE = 266,             /* TOKEN_WHILE  */
    TOKEN_LOOP = 267,              /* TOKEN_LOOP  */
    TOKEN_BREAK = 268,             /* TOKEN_BREAK  */
    TOKEN_CONTINUE = 269,          /* TOKEN_CONTINUE  */
    TOKEN_IMPORT = 270,            /* TOKEN_IMPORT  */
    TOKEN_EXPORT = 271,            /* TOKEN_EXPORT  */
    TOKEN_PACKET = 272,            /* TOKEN_PACKET  */
    TOKEN_STRUCT = 273,            /* TOKEN_STRUCT  */
    TOKEN_ENUM = 274,              /* TOKEN_ENUM  */
    TOKEN_IMPL = 275,              /* TOKEN_IMPL  */
    TOKEN_MATCH = 276,             /* TOKEN_MATCH  */
    TOKEN_TYPE = 277,              /* TOKEN_TYPE  */
    TOKEN_TRUE = 278,              /* TOKEN_TRUE  */
    TOKEN_FALSE = 279,             /* TOKEN_FALSE  */
    TOKEN_NIL = 280,               /* TOKEN_NIL  */
    TOKEN_AS = 281,                /* TOKEN_AS  */
    TOKEN_IN = 282,                /* TOKEN_IN  */
    TOKEN_FROM = 283,              /* TOKEN_FROM  */
    TOKEN_PUB = 284,               /* TOKEN_PUB  */
    TOKEN_UNDERSCORE = 285,        /* TOKEN_UNDERSCORE  */
    TOKEN_PLUS = 286,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 287,             /* TOKEN_MINUS  */
    TOKEN_MULTIPLY = 288,          /* TOKEN_MULTIPLY  */
    TOKEN_DIVIDE = 289,            /* TOKEN_DIVIDE  */
    TOKEN_MODULO = 290,            /* TOKEN_MODULO  */
    TOKEN_ASSIGN = 291,            /* TOKEN_ASSIGN  */
    TOKEN_PLUS_ASSIGN = 292,       /* TOKEN_PLUS_ASSIGN  */
    TOKEN_MINUS_ASSIGN = 293,      /* TOKEN_MINUS_ASSIGN  */
    TOKEN_MULTIPLY_ASSIGN = 294,   /* TOKEN_MULTIPLY_ASSIGN  */
    TOKEN_DIVIDE_ASSIGN = 295,     /* TOKEN_DIVIDE_ASSIGN  */
    TOKEN_MODULO_ASSIGN = 296,     /* TOKEN_MODULO_ASSIGN  */
    TOKEN_EQ = 297,                /* TOKEN_EQ  */
    TOKEN_NEQ = 298,               /* TOKEN_NEQ  */
    TOKEN_LT = 299,                /* TOKEN_LT  */
    TOKEN_LTE = 300,               /* TOKEN_LTE  */
    TOKEN_GT = 301,                /* TOKEN_GT  */
    TOKEN_GTE = 302,               /* TOKEN_GTE  */
    TOKEN_AND = 303,               /* TOKEN_AND  */
    TOKEN_OR = 304,                /* TOKEN_OR  */
    TOKEN_NOT = 305,               /* TOKEN_NOT  */
    TOKEN_AMP = 306,               /* TOKEN_AMP  */
    TOKEN_PIPE = 307,              /* TOKEN_PIPE  */
    TOKEN_XOR = 308,               /* TOKEN_XOR  */
    TOKEN_LSHIFT = 309,            /* TOKEN_LSHIFT  */
    TOKEN_RSHIFT = 310,            /* TOKEN_RSHIFT  */
    TOKEN_DOUBLE_COLON = 311,      /* TOKEN_DOUBLE_COLON  */
    TOKEN_DOT = 312,               /* TOKEN_DOT  */
    TOKEN_COLON = 313,             /* TOKEN_COLON  */
    TOKEN_SEMICOLON = 314,         /* TOKEN_SEMICOLON  */
    TOKEN_COMMA = 315,             /* TOKEN_COMMA  */
    TOKEN_ARROW = 316,             /* TOKEN_ARROW  */
    TOKEN_FAT_ARROW = 317,         /* TOKEN_FAT_ARROW  */
    TOKEN_PIPE_FORWARD = 318,      /* TOKEN_PIPE_FORWARD  */
    TOKEN_OPTIONAL = 319,          /* TOKEN_OPTIONAL  */
    TOKEN_COALESCE = 320,          /* TOKEN_COALESCE  */
    TOKEN_RANGE = 321,             /* TOKEN_RANGE  */
    TOKEN_RANGE_INC = 322,         /* TOKEN_RANGE_INC  */
    TOKEN_LPAREN = 323,            /* TOKEN_LPAREN  */
    TOKEN_RPAREN = 324,            /* TOKEN_RPAREN  */
    TOKEN_LBRACE = 325,            /* TOKEN_LBRACE  */
    TOKEN_RBRACE = 326,            /* TOKEN_RBRACE  */
    TOKEN_LBRACKET = 327,          /* TOKEN_LBRACKET  */
    TOKEN_RBRACKET = 328,          /* TOKEN_RBRACKET  */
    TOKEN_IDENTIFIER = 329,        /* TOKEN_IDENTIFIER  */
    TOKEN_NUMBER = 330,            /* TOKEN_NUMBER  */
    TOKEN_FLOAT = 331,             /* TOKEN_FLOAT  */
    TOKEN_STRING = 332             /* TOKEN_STRING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "src/parser/parser.y"

    int number;
    double float_val;
    char* string;
    struct ASTNode* node;
    struct ASTNodeList* node_list;

#line 149 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

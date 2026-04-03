/* A Bison parser, made by GNU Bison 3.8.2.  */

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
    TOKEN_DICT = 258,              /* TOKEN_DICT  */
    TOKEN_MAP = 259,               /* TOKEN_MAP  */
    TOKEN_FN = 260,                /* TOKEN_FN  */
    TOKEN_LET = 261,               /* TOKEN_LET  */
    TOKEN_CONST = 262,             /* TOKEN_CONST  */
    TOKEN_RETURN = 263,            /* TOKEN_RETURN  */
    TOKEN_IF = 264,                /* TOKEN_IF  */
    TOKEN_ELSE = 265,              /* TOKEN_ELSE  */
    TOKEN_FOR = 266,               /* TOKEN_FOR  */
    TOKEN_WHILE = 267,             /* TOKEN_WHILE  */
    TOKEN_LOOP = 268,              /* TOKEN_LOOP  */
    TOKEN_BREAK = 269,             /* TOKEN_BREAK  */
    TOKEN_CONTINUE = 270,          /* TOKEN_CONTINUE  */
    TOKEN_IMPORT = 271,            /* TOKEN_IMPORT  */
    TOKEN_EXPORT = 272,            /* TOKEN_EXPORT  */
    TOKEN_PACKET = 273,            /* TOKEN_PACKET  */
    TOKEN_STRUCT = 274,            /* TOKEN_STRUCT  */
    TOKEN_ENUM = 275,              /* TOKEN_ENUM  */
    TOKEN_IMPL = 276,              /* TOKEN_IMPL  */
    TOKEN_MATCH = 277,             /* TOKEN_MATCH  */
    TOKEN_TYPE = 278,              /* TOKEN_TYPE  */
    TOKEN_TRUE = 279,              /* TOKEN_TRUE  */
    TOKEN_FALSE = 280,             /* TOKEN_FALSE  */
    TOKEN_NIL = 281,               /* TOKEN_NIL  */
    TOKEN_AS = 282,                /* TOKEN_AS  */
    TOKEN_IN = 283,                /* TOKEN_IN  */
    TOKEN_FROM = 284,              /* TOKEN_FROM  */
    TOKEN_PUB = 285,               /* TOKEN_PUB  */
    TOKEN_NEW = 286,               /* TOKEN_NEW  */
    TOKEN_UNSAFE = 287,            /* TOKEN_UNSAFE  */
    TOKEN_NNL = 288,               /* TOKEN_NNL  */
    TOKEN_JMP = 289,               /* TOKEN_JMP  */
    TOKEN_MODULE = 290,            /* TOKEN_MODULE  */
    TOKEN_ONLY = 291,              /* TOKEN_ONLY  */
    TOKEN_TIMEOUT = 292,           /* TOKEN_TIMEOUT  */
    TOKEN_SANDBOX = 293,           /* TOKEN_SANDBOX  */
    TOKEN_ALLOW_FFI = 294,         /* TOKEN_ALLOW_FFI  */
    TOKEN_LAMBDA = 295,            /* TOKEN_LAMBDA  */
    TOKEN_EXTENDS = 296,           /* TOKEN_EXTENDS  */
    TOKEN_UNDERSCORE = 297,        /* TOKEN_UNDERSCORE  */
    TOKEN_PLUS = 298,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 299,             /* TOKEN_MINUS  */
    TOKEN_MULTIPLY = 300,          /* TOKEN_MULTIPLY  */
    TOKEN_DIVIDE = 301,            /* TOKEN_DIVIDE  */
    TOKEN_MODULO = 302,            /* TOKEN_MODULO  */
    TOKEN_ASSIGN = 303,            /* TOKEN_ASSIGN  */
    TOKEN_PLUS_ASSIGN = 304,       /* TOKEN_PLUS_ASSIGN  */
    TOKEN_MINUS_ASSIGN = 305,      /* TOKEN_MINUS_ASSIGN  */
    TOKEN_MULTIPLY_ASSIGN = 306,   /* TOKEN_MULTIPLY_ASSIGN  */
    TOKEN_DIVIDE_ASSIGN = 307,     /* TOKEN_DIVIDE_ASSIGN  */
    TOKEN_MODULO_ASSIGN = 308,     /* TOKEN_MODULO_ASSIGN  */
    TOKEN_EQ = 309,                /* TOKEN_EQ  */
    TOKEN_NEQ = 310,               /* TOKEN_NEQ  */
    TOKEN_LT = 311,                /* TOKEN_LT  */
    TOKEN_LTE = 312,               /* TOKEN_LTE  */
    TOKEN_GT = 313,                /* TOKEN_GT  */
    TOKEN_GTE = 314,               /* TOKEN_GTE  */
    TOKEN_AND = 315,               /* TOKEN_AND  */
    TOKEN_OR = 316,                /* TOKEN_OR  */
    TOKEN_NOT = 317,               /* TOKEN_NOT  */
    TOKEN_AMP = 318,               /* TOKEN_AMP  */
    TOKEN_PIPE = 319,              /* TOKEN_PIPE  */
    TOKEN_XOR = 320,               /* TOKEN_XOR  */
    TOKEN_LSHIFT = 321,            /* TOKEN_LSHIFT  */
    TOKEN_RSHIFT = 322,            /* TOKEN_RSHIFT  */
    TOKEN_DOUBLE_COLON = 323,      /* TOKEN_DOUBLE_COLON  */
    TOKEN_DOT = 324,               /* TOKEN_DOT  */
    TOKEN_SECURITY = 325,          /* TOKEN_SECURITY  */
    TOKEN_COLON = 326,             /* TOKEN_COLON  */
    TOKEN_SEMICOLON = 327,         /* TOKEN_SEMICOLON  */
    TOKEN_COMMA = 328,             /* TOKEN_COMMA  */
    TOKEN_ARROW = 329,             /* TOKEN_ARROW  */
    TOKEN_FAT_ARROW = 330,         /* TOKEN_FAT_ARROW  */
    TOKEN_PIPE_FORWARD = 331,      /* TOKEN_PIPE_FORWARD  */
    TOKEN_OPTIONAL = 332,          /* TOKEN_OPTIONAL  */
    TOKEN_COALESCE = 333,          /* TOKEN_COALESCE  */
    TOKEN_RANGE = 334,             /* TOKEN_RANGE  */
    TOKEN_RANGE_INC = 335,         /* TOKEN_RANGE_INC  */
    TOKEN_MUTS = 336,              /* TOKEN_MUTS  */
    TOKEN_LPAREN = 337,            /* TOKEN_LPAREN  */
    TOKEN_RPAREN = 338,            /* TOKEN_RPAREN  */
    TOKEN_LBRACE = 339,            /* TOKEN_LBRACE  */
    TOKEN_RBRACE = 340,            /* TOKEN_RBRACE  */
    TOKEN_LBRACKET = 341,          /* TOKEN_LBRACKET  */
    TOKEN_RBRACKET = 342,          /* TOKEN_RBRACKET  */
    TOKEN_IDENTIFIER = 343,        /* TOKEN_IDENTIFIER  */
    TOKEN_NUMBER = 344,            /* TOKEN_NUMBER  */
    TOKEN_FLOAT = 345,             /* TOKEN_FLOAT  */
    TOKEN_STRING = 346             /* TOKEN_STRING  */
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

#line 163 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */

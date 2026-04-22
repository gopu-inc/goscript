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
    TOKEN_ASYNC = 295,             /* TOKEN_ASYNC  */
    TOKEN_AWAIT = 296,             /* TOKEN_AWAIT  */
    TOKEN_SPAWN = 297,             /* TOKEN_SPAWN  */
    TOKEN_LAMBDA = 298,            /* TOKEN_LAMBDA  */
    TOKEN_EXTENDS = 299,           /* TOKEN_EXTENDS  */
    TOKEN_UNDERSCORE = 300,        /* TOKEN_UNDERSCORE  */
    TOKEN_SWITCH = 301,            /* TOKEN_SWITCH  */
    TOKEN_USE = 302,               /* TOKEN_USE  */
    TOKEN_PLUS = 303,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 304,             /* TOKEN_MINUS  */
    TOKEN_MULTIPLY = 305,          /* TOKEN_MULTIPLY  */
    TOKEN_DIVIDE = 306,            /* TOKEN_DIVIDE  */
    TOKEN_MODULO = 307,            /* TOKEN_MODULO  */
    TOKEN_ASSIGN = 308,            /* TOKEN_ASSIGN  */
    TOKEN_PLUS_ASSIGN = 309,       /* TOKEN_PLUS_ASSIGN  */
    TOKEN_MINUS_ASSIGN = 310,      /* TOKEN_MINUS_ASSIGN  */
    TOKEN_MULTIPLY_ASSIGN = 311,   /* TOKEN_MULTIPLY_ASSIGN  */
    TOKEN_DIVIDE_ASSIGN = 312,     /* TOKEN_DIVIDE_ASSIGN  */
    TOKEN_MODULO_ASSIGN = 313,     /* TOKEN_MODULO_ASSIGN  */
    TOKEN_EQ = 314,                /* TOKEN_EQ  */
    TOKEN_NEQ = 315,               /* TOKEN_NEQ  */
    TOKEN_LT = 316,                /* TOKEN_LT  */
    TOKEN_LTE = 317,               /* TOKEN_LTE  */
    TOKEN_GT = 318,                /* TOKEN_GT  */
    TOKEN_GTE = 319,               /* TOKEN_GTE  */
    TOKEN_AND = 320,               /* TOKEN_AND  */
    TOKEN_OR = 321,                /* TOKEN_OR  */
    TOKEN_NOT = 322,               /* TOKEN_NOT  */
    TOKEN_AMP = 323,               /* TOKEN_AMP  */
    TOKEN_PIPE = 324,              /* TOKEN_PIPE  */
    TOKEN_XOR = 325,               /* TOKEN_XOR  */
    TOKEN_LSHIFT = 326,            /* TOKEN_LSHIFT  */
    TOKEN_RSHIFT = 327,            /* TOKEN_RSHIFT  */
    TOKEN_DOUBLE_COLON = 328,      /* TOKEN_DOUBLE_COLON  */
    TOKEN_DOT = 329,               /* TOKEN_DOT  */
    TOKEN_SECURITY = 330,          /* TOKEN_SECURITY  */
    TOKEN_COLON = 331,             /* TOKEN_COLON  */
    TOKEN_SEMICOLON = 332,         /* TOKEN_SEMICOLON  */
    TOKEN_COMMA = 333,             /* TOKEN_COMMA  */
    TOKEN_ARROW = 334,             /* TOKEN_ARROW  */
    TOKEN_FAT_ARROW = 335,         /* TOKEN_FAT_ARROW  */
    TOKEN_PIPE_FORWARD = 336,      /* TOKEN_PIPE_FORWARD  */
    TOKEN_OPTIONAL = 337,          /* TOKEN_OPTIONAL  */
    TOKEN_COALESCE = 338,          /* TOKEN_COALESCE  */
    TOKEN_RANGE = 339,             /* TOKEN_RANGE  */
    TOKEN_RANGE_INC = 340,         /* TOKEN_RANGE_INC  */
    TOKEN_MUTS = 341,              /* TOKEN_MUTS  */
    TOKEN_SYSF = 342,              /* TOKEN_SYSF  */
    TOKEN_SH = 343,                /* TOKEN_SH  */
    TOKEN_LPAREN = 344,            /* TOKEN_LPAREN  */
    TOKEN_RPAREN = 345,            /* TOKEN_RPAREN  */
    TOKEN_LBRACE = 346,            /* TOKEN_LBRACE  */
    TOKEN_RBRACE = 347,            /* TOKEN_RBRACE  */
    TOKEN_LBRACKET = 348,          /* TOKEN_LBRACKET  */
    TOKEN_RBRACKET = 349,          /* TOKEN_RBRACKET  */
    TOKEN_TRY = 350,               /* TOKEN_TRY  */
    TOKEN_CATCH = 351,             /* TOKEN_CATCH  */
    TOKEN_FINALLY = 352,           /* TOKEN_FINALLY  */
    TOKEN_THROW = 353,             /* TOKEN_THROW  */
    TOKEN_EXCEPT = 354,            /* TOKEN_EXCEPT  */
    TOKEN_RAISE = 355,             /* TOKEN_RAISE  */
    TOKEN_IDENTIFIER = 356,        /* TOKEN_IDENTIFIER  */
    TOKEN_NUMBER = 357,            /* TOKEN_NUMBER  */
    TOKEN_FLOAT = 358,             /* TOKEN_FLOAT  */
    TOKEN_STRING = 359,            /* TOKEN_STRING  */
    TOKEN_F_STRING = 360           /* TOKEN_F_STRING  */
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

#line 177 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

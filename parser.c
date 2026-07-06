/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylineno;
extern char* yytext;

void yyerror(const char* msg);
int yylex(void);
ASTNode* parse_f_string(char* template);
ASTNode* program_root;

#line 86 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_DICT = 3,                 /* TOKEN_DICT  */
  YYSYMBOL_TOKEN_MAP = 4,                  /* TOKEN_MAP  */
  YYSYMBOL_TOKEN_FN = 5,                   /* TOKEN_FN  */
  YYSYMBOL_TOKEN_LET = 6,                  /* TOKEN_LET  */
  YYSYMBOL_TOKEN_CONST = 7,                /* TOKEN_CONST  */
  YYSYMBOL_TOKEN_RETURN = 8,               /* TOKEN_RETURN  */
  YYSYMBOL_TOKEN_IF = 9,                   /* TOKEN_IF  */
  YYSYMBOL_TOKEN_ELSE = 10,                /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_FOR = 11,                 /* TOKEN_FOR  */
  YYSYMBOL_TOKEN_WHILE = 12,               /* TOKEN_WHILE  */
  YYSYMBOL_TOKEN_LOOP = 13,                /* TOKEN_LOOP  */
  YYSYMBOL_TOKEN_BREAK = 14,               /* TOKEN_BREAK  */
  YYSYMBOL_TOKEN_CONTINUE = 15,            /* TOKEN_CONTINUE  */
  YYSYMBOL_TOKEN_IMPORT = 16,              /* TOKEN_IMPORT  */
  YYSYMBOL_TOKEN_EXPORT = 17,              /* TOKEN_EXPORT  */
  YYSYMBOL_TOKEN_PACKET = 18,              /* TOKEN_PACKET  */
  YYSYMBOL_TOKEN_STRUCT = 19,              /* TOKEN_STRUCT  */
  YYSYMBOL_TOKEN_ENUM = 20,                /* TOKEN_ENUM  */
  YYSYMBOL_TOKEN_IMPL = 21,                /* TOKEN_IMPL  */
  YYSYMBOL_TOKEN_MATCH = 22,               /* TOKEN_MATCH  */
  YYSYMBOL_TOKEN_TYPE = 23,                /* TOKEN_TYPE  */
  YYSYMBOL_TOKEN_TRUE = 24,                /* TOKEN_TRUE  */
  YYSYMBOL_TOKEN_FALSE = 25,               /* TOKEN_FALSE  */
  YYSYMBOL_TOKEN_NIL = 26,                 /* TOKEN_NIL  */
  YYSYMBOL_TOKEN_AS = 27,                  /* TOKEN_AS  */
  YYSYMBOL_TOKEN_IN = 28,                  /* TOKEN_IN  */
  YYSYMBOL_TOKEN_FROM = 29,                /* TOKEN_FROM  */
  YYSYMBOL_TOKEN_PUB = 30,                 /* TOKEN_PUB  */
  YYSYMBOL_TOKEN_NEW = 31,                 /* TOKEN_NEW  */
  YYSYMBOL_TOKEN_UNSAFE = 32,              /* TOKEN_UNSAFE  */
  YYSYMBOL_TOKEN_NNL = 33,                 /* TOKEN_NNL  */
  YYSYMBOL_TOKEN_JMP = 34,                 /* TOKEN_JMP  */
  YYSYMBOL_TOKEN_MODULE = 35,              /* TOKEN_MODULE  */
  YYSYMBOL_TOKEN_ONLY = 36,                /* TOKEN_ONLY  */
  YYSYMBOL_TOKEN_TIMEOUT = 37,             /* TOKEN_TIMEOUT  */
  YYSYMBOL_TOKEN_SANDBOX = 38,             /* TOKEN_SANDBOX  */
  YYSYMBOL_TOKEN_ALLOW_FFI = 39,           /* TOKEN_ALLOW_FFI  */
  YYSYMBOL_TOKEN_ASYNC = 40,               /* TOKEN_ASYNC  */
  YYSYMBOL_TOKEN_AWAIT = 41,               /* TOKEN_AWAIT  */
  YYSYMBOL_TOKEN_SPAWN = 42,               /* TOKEN_SPAWN  */
  YYSYMBOL_TOKEN_LAMBDA = 43,              /* TOKEN_LAMBDA  */
  YYSYMBOL_TOKEN_EXTENDS = 44,             /* TOKEN_EXTENDS  */
  YYSYMBOL_TOKEN_UNDERSCORE = 45,          /* TOKEN_UNDERSCORE  */
  YYSYMBOL_TOKEN_SWITCH = 46,              /* TOKEN_SWITCH  */
  YYSYMBOL_TOKEN_USE = 47,                 /* TOKEN_USE  */
  YYSYMBOL_TOKEN_AT = 48,                  /* TOKEN_AT  */
  YYSYMBOL_TOKEN_PLUS = 49,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 50,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MULTIPLY = 51,            /* TOKEN_MULTIPLY  */
  YYSYMBOL_TOKEN_DIVIDE = 52,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 53,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_ASSIGN = 54,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 55,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 56,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 57,     /* TOKEN_MULTIPLY_ASSIGN  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 58,       /* TOKEN_DIVIDE_ASSIGN  */
  YYSYMBOL_TOKEN_MODULO_ASSIGN = 59,       /* TOKEN_MODULO_ASSIGN  */
  YYSYMBOL_TOKEN_EQ = 60,                  /* TOKEN_EQ  */
  YYSYMBOL_TOKEN_NEQ = 61,                 /* TOKEN_NEQ  */
  YYSYMBOL_TOKEN_LT = 62,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LTE = 63,                 /* TOKEN_LTE  */
  YYSYMBOL_TOKEN_GT = 64,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GTE = 65,                 /* TOKEN_GTE  */
  YYSYMBOL_TOKEN_AND = 66,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 67,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_NOT = 68,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_AMP = 69,                 /* TOKEN_AMP  */
  YYSYMBOL_TOKEN_PIPE = 70,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_XOR = 71,                 /* TOKEN_XOR  */
  YYSYMBOL_TOKEN_LSHIFT = 72,              /* TOKEN_LSHIFT  */
  YYSYMBOL_TOKEN_RSHIFT = 73,              /* TOKEN_RSHIFT  */
  YYSYMBOL_TOKEN_DOUBLE_COLON = 74,        /* TOKEN_DOUBLE_COLON  */
  YYSYMBOL_TOKEN_DOT = 75,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_SECURITY = 76,            /* TOKEN_SECURITY  */
  YYSYMBOL_TOKEN_COLON = 77,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_SEMICOLON = 78,           /* TOKEN_SEMICOLON  */
  YYSYMBOL_TOKEN_COMMA = 79,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_ARROW = 80,               /* TOKEN_ARROW  */
  YYSYMBOL_TOKEN_FAT_ARROW = 81,           /* TOKEN_FAT_ARROW  */
  YYSYMBOL_TOKEN_PIPE_FORWARD = 82,        /* TOKEN_PIPE_FORWARD  */
  YYSYMBOL_TOKEN_OPTIONAL = 83,            /* TOKEN_OPTIONAL  */
  YYSYMBOL_TOKEN_COALESCE = 84,            /* TOKEN_COALESCE  */
  YYSYMBOL_TOKEN_RANGE = 85,               /* TOKEN_RANGE  */
  YYSYMBOL_TOKEN_RANGE_INC = 86,           /* TOKEN_RANGE_INC  */
  YYSYMBOL_TOKEN_MUTS = 87,                /* TOKEN_MUTS  */
  YYSYMBOL_TOKEN_SYSF = 88,                /* TOKEN_SYSF  */
  YYSYMBOL_TOKEN_SH = 89,                  /* TOKEN_SH  */
  YYSYMBOL_TOKEN_LPAREN = 90,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 91,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_LBRACE = 92,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 93,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_LBRACKET = 94,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 95,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_TRY = 96,                 /* TOKEN_TRY  */
  YYSYMBOL_TOKEN_CATCH = 97,               /* TOKEN_CATCH  */
  YYSYMBOL_TOKEN_FINALLY = 98,             /* TOKEN_FINALLY  */
  YYSYMBOL_TOKEN_THROW = 99,               /* TOKEN_THROW  */
  YYSYMBOL_TOKEN_EXCEPT = 100,             /* TOKEN_EXCEPT  */
  YYSYMBOL_TOKEN_RAISE = 101,              /* TOKEN_RAISE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 102,         /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_NUMBER = 103,             /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_FLOAT = 104,              /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_STRING = 105,             /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_F_STRING = 106,           /* TOKEN_F_STRING  */
  YYSYMBOL_YYACCEPT = 107,                 /* $accept  */
  YYSYMBOL_switch_statement = 108,         /* switch_statement  */
  YYSYMBOL_ternary_expr = 109,             /* ternary_expr  */
  YYSYMBOL_program = 110,                  /* program  */
  YYSYMBOL_statement_list = 111,           /* statement_list  */
  YYSYMBOL_unsafe_stmt = 112,              /* unsafe_stmt  */
  YYSYMBOL_continue_statement = 113,       /* continue_statement  */
  YYSYMBOL_statement = 114,                /* statement  */
  YYSYMBOL_sysf_expr = 115,                /* sysf_expr  */
  YYSYMBOL_use_statement = 116,            /* use_statement  */
  YYSYMBOL_use_path = 117,                 /* use_path  */
  YYSYMBOL_sh_expr = 118,                  /* sh_expr  */
  YYSYMBOL_nnl_statement = 119,            /* nnl_statement  */
  YYSYMBOL_try_statement = 120,            /* try_statement  */
  YYSYMBOL_catch_block = 121,              /* catch_block  */
  YYSYMBOL_finally_block = 122,            /* finally_block  */
  YYSYMBOL_throw_statement = 123,          /* throw_statement  */
  YYSYMBOL_jmp_statement = 124,            /* jmp_statement  */
  YYSYMBOL_import_statement = 125,         /* import_statement  */
  YYSYMBOL_import_path_tail = 126,         /* import_path_tail  */
  YYSYMBOL_import_path = 127,              /* import_path  */
  YYSYMBOL_import_constraints = 128,       /* import_constraints  */
  YYSYMBOL_import_options = 129,           /* import_options  */
  YYSYMBOL_name_list = 130,                /* name_list  */
  YYSYMBOL_export_statement = 131,         /* export_statement  */
  YYSYMBOL_export_list = 132,              /* export_list  */
  YYSYMBOL_export_item = 133,              /* export_item  */
  YYSYMBOL_import_impl_list = 134,         /* import_impl_list  */
  YYSYMBOL_import_impl_item = 135,         /* import_impl_item  */
  YYSYMBOL_packet_decl = 136,              /* packet_decl  */
  YYSYMBOL_decorator_list = 137,           /* decorator_list  */
  YYSYMBOL_decorator = 138,                /* decorator  */
  YYSYMBOL_function_decl = 139,            /* function_decl  */
  YYSYMBOL_param_list = 140,               /* param_list  */
  YYSYMBOL_param = 141,                    /* param  */
  YYSYMBOL_type = 142,                     /* type  */
  YYSYMBOL_dict_expr = 143,                /* dict_expr  */
  YYSYMBOL_dict_entries = 144,             /* dict_entries  */
  YYSYMBOL_dict_entry_list = 145,          /* dict_entry_list  */
  YYSYMBOL_bracket_access = 146,           /* bracket_access  */
  YYSYMBOL_return_type = 147,              /* return_type  */
  YYSYMBOL_let_decl = 148,                 /* let_decl  */
  YYSYMBOL_const_decl = 149,               /* const_decl  */
  YYSYMBOL_if_statement = 150,             /* if_statement  */
  YYSYMBOL_break_statement = 151,          /* break_statement  */
  YYSYMBOL_for_statement = 152,            /* for_statement  */
  YYSYMBOL_while_statement = 153,          /* while_statement  */
  YYSYMBOL_loop_statement = 154,           /* loop_statement  */
  YYSYMBOL_match_statement = 155,          /* match_statement  */
  YYSYMBOL_match_cases = 156,              /* match_cases  */
  YYSYMBOL_match_case = 157,               /* match_case  */
  YYSYMBOL_pattern = 158,                  /* pattern  */
  YYSYMBOL_array_patterns = 159,           /* array_patterns  */
  YYSYMBOL_struct_decl = 160,              /* struct_decl  */
  YYSYMBOL_struct_fields = 161,            /* struct_fields  */
  YYSYMBOL_struct_field = 162,             /* struct_field  */
  YYSYMBOL_enum_decl = 163,                /* enum_decl  */
  YYSYMBOL_enum_variants = 164,            /* enum_variants  */
  YYSYMBOL_module_decl = 165,              /* module_decl  */
  YYSYMBOL_impl_decl = 166,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 167,       /* function_decl_list  */
  YYSYMBOL_return_statement = 168,         /* return_statement  */
  YYSYMBOL_expression = 169,               /* expression  */
  YYSYMBOL_binary_expr = 170,              /* binary_expr  */
  YYSYMBOL_unary_expr = 171,               /* unary_expr  */
  YYSYMBOL_lambda_expr = 172,              /* lambda_expr  */
  YYSYMBOL_primary_expr = 173,             /* primary_expr  */
  YYSYMBOL_f_string = 174,                 /* f_string  */
  YYSYMBOL_member_access = 175,            /* member_access  */
  YYSYMBOL_call_expr = 176,                /* call_expr  */
  YYSYMBOL_argument_list = 177,            /* argument_list  */
  YYSYMBOL_array_expr = 178,               /* array_expr  */
  YYSYMBOL_await_expr = 179,               /* await_expr  */
  YYSYMBOL_spawn_expr = 180,               /* spawn_expr  */
  YYSYMBOL_array_items = 181,              /* array_items  */
  YYSYMBOL_struct_expr = 182,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 183,       /* struct_init_fields  */
  YYSYMBOL_block = 184                     /* block  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  159
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4294

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  78
/* YYNRULES -- Number of rules.  */
#define YYNRULES  231
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  534

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   361


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   126,   126,   131,   138,   144,   148,   154,   159,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   196,   199,   206,   210,   214,
     222,   225,   234,   237,   243,   249,   252,   258,   261,   267,
     273,   276,   281,   284,   293,   297,   301,   305,   309,   315,
     324,   327,   336,   339,   345,   354,   360,   363,   369,   373,
     380,   384,   392,   396,   403,   409,   417,   421,   429,   437,
     447,   451,   459,   463,   467,   474,   483,   486,   489,   495,
     502,   509,   513,   520,   523,   527,   536,   538,   540,   542,
     548,   551,   554,   562,   563,   564,   568,   571,   577,   582,
     592,   608,   611,   614,   621,   624,   627,   633,   636,   641,
     644,   653,   656,   659,   667,   672,   678,   681,   694,   709,
     724,   730,   737,   743,   747,   754,   757,   763,   764,   765,
     766,   767,   768,   772,   773,   774,   779,   782,   788,   791,
     795,   799,   806,   812,   818,   821,   825,   832,   839,   845,
     848,   852,   859,   862,   868,   869,   870,   871,   872,   880,
     883,   886,   889,   892,   895,   898,   901,   904,   907,   910,
     913,   916,   919,   922,   925,   928,   931,   934,   940,   943,
     950,   953,   962,   965,   968,   971,   974,   977,   980,   983,
     986,   987,   988,   989,   990,   991,   992,   993,   994,   995,
     996,   997,  1001,  1007,  1010,  1016,  1019,  1025,  1028,  1032,
    1039,  1054,  1057,  1064,  1076,  1079,  1083,  1090,  1096,  1099,
    1103,  1110
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_DICT",
  "TOKEN_MAP", "TOKEN_FN", "TOKEN_LET", "TOKEN_CONST", "TOKEN_RETURN",
  "TOKEN_IF", "TOKEN_ELSE", "TOKEN_FOR", "TOKEN_WHILE", "TOKEN_LOOP",
  "TOKEN_BREAK", "TOKEN_CONTINUE", "TOKEN_IMPORT", "TOKEN_EXPORT",
  "TOKEN_PACKET", "TOKEN_STRUCT", "TOKEN_ENUM", "TOKEN_IMPL",
  "TOKEN_MATCH", "TOKEN_TYPE", "TOKEN_TRUE", "TOKEN_FALSE", "TOKEN_NIL",
  "TOKEN_AS", "TOKEN_IN", "TOKEN_FROM", "TOKEN_PUB", "TOKEN_NEW",
  "TOKEN_UNSAFE", "TOKEN_NNL", "TOKEN_JMP", "TOKEN_MODULE", "TOKEN_ONLY",
  "TOKEN_TIMEOUT", "TOKEN_SANDBOX", "TOKEN_ALLOW_FFI", "TOKEN_ASYNC",
  "TOKEN_AWAIT", "TOKEN_SPAWN", "TOKEN_LAMBDA", "TOKEN_EXTENDS",
  "TOKEN_UNDERSCORE", "TOKEN_SWITCH", "TOKEN_USE", "TOKEN_AT",
  "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_MULTIPLY", "TOKEN_DIVIDE",
  "TOKEN_MODULO", "TOKEN_ASSIGN", "TOKEN_PLUS_ASSIGN",
  "TOKEN_MINUS_ASSIGN", "TOKEN_MULTIPLY_ASSIGN", "TOKEN_DIVIDE_ASSIGN",
  "TOKEN_MODULO_ASSIGN", "TOKEN_EQ", "TOKEN_NEQ", "TOKEN_LT", "TOKEN_LTE",
  "TOKEN_GT", "TOKEN_GTE", "TOKEN_AND", "TOKEN_OR", "TOKEN_NOT",
  "TOKEN_AMP", "TOKEN_PIPE", "TOKEN_XOR", "TOKEN_LSHIFT", "TOKEN_RSHIFT",
  "TOKEN_DOUBLE_COLON", "TOKEN_DOT", "TOKEN_SECURITY", "TOKEN_COLON",
  "TOKEN_SEMICOLON", "TOKEN_COMMA", "TOKEN_ARROW", "TOKEN_FAT_ARROW",
  "TOKEN_PIPE_FORWARD", "TOKEN_OPTIONAL", "TOKEN_COALESCE", "TOKEN_RANGE",
  "TOKEN_RANGE_INC", "TOKEN_MUTS", "TOKEN_SYSF", "TOKEN_SH",
  "TOKEN_LPAREN", "TOKEN_RPAREN", "TOKEN_LBRACE", "TOKEN_RBRACE",
  "TOKEN_LBRACKET", "TOKEN_RBRACKET", "TOKEN_TRY", "TOKEN_CATCH",
  "TOKEN_FINALLY", "TOKEN_THROW", "TOKEN_EXCEPT", "TOKEN_RAISE",
  "TOKEN_IDENTIFIER", "TOKEN_NUMBER", "TOKEN_FLOAT", "TOKEN_STRING",
  "TOKEN_F_STRING", "$accept", "switch_statement", "ternary_expr",
  "program", "statement_list", "unsafe_stmt", "continue_statement",
  "statement", "sysf_expr", "use_statement", "use_path", "sh_expr",
  "nnl_statement", "try_statement", "catch_block", "finally_block",
  "throw_statement", "jmp_statement", "import_statement",
  "import_path_tail", "import_path", "import_constraints",
  "import_options", "name_list", "export_statement", "export_list",
  "export_item", "import_impl_list", "import_impl_item", "packet_decl",
  "decorator_list", "decorator", "function_decl", "param_list", "param",
  "type", "dict_expr", "dict_entries", "dict_entry_list", "bracket_access",
  "return_type", "let_decl", "const_decl", "if_statement",
  "break_statement", "for_statement", "while_statement", "loop_statement",
  "match_statement", "match_cases", "match_case", "pattern",
  "array_patterns", "struct_decl", "struct_fields", "struct_field",
  "enum_decl", "enum_variants", "module_decl", "impl_decl",
  "function_decl_list", "return_statement", "expression", "binary_expr",
  "unary_expr", "lambda_expr", "primary_expr", "f_string", "member_access",
  "call_expr", "argument_list", "array_expr", "await_expr", "spawn_expr",
  "array_items", "struct_expr", "struct_init_fields", "block", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-404)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    3207,    27,    56,    -2,     2,    82,   203,   203,  3248,   203,
      63,  -404,  -404,   -47,   -19,   113,   120,   124,   131,   203,
    -404,  -404,  -404,    44,   135,   158,   152,   154,   177,    73,
    3414,  3497,    54,   203,   183,   185,   203,   203,   187,  3331,
    3360,   203,   203,   203,   194,   203,   203,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,   146,  3207,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,    18,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  4211,  -404,  -404,
    -404,    53,  -404,  -404,  -404,  -404,  -404,  -404,  -404,   203,
     203,   200,   -10,   223,  4211,  3501,    15,  3599,  3643,  3207,
     192,   192,  -404,    35,   -16,    -3,  -404,   204,   -24,   206,
     208,  3687,   199,   201,   210,   297,   218,  3207,   221,   203,
    -404,   212,  3207,    53,    53,   234,     8,   106,  -404,  3731,
    -404,   -15,     1,   166,    74,    20,   203,  4211,   203,  4211,
    3907,   244,   260,  4036,  4211,     3,  3207,  4211,  4211,  -404,
    -404,   238,   336,  -404,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   240,   203,   242,   247,   203,   203,   257,
     259,   234,   203,   180,   203,  3207,   203,   203,  3207,  3207,
     503,    35,    35,   251,   253,    65,  -404,   256,  -404,    52,
    -404,  3207,   258,   264,   267,    41,    19,   271,   308,   316,
     269,   270,   607,  3207,  4211,   283,   711,  4036,   110,   203,
     180,   234,  3207,    19,   272,   103,   273,   203,   203,   180,
    3950,  3993,  -404,  -404,   203,   203,   203,  -404,   815,   286,
     275,   166,   166,    74,    74,    74,  4211,  4211,  4211,  4211,
    4211,  4211,   511,   511,   160,   160,   160,   160,   505,   378,
     288,  4071,   289,  -404,  4211,   123,   268,  -404,  -404,   125,
    4211,   285,   298,   328,  4211,   919,  3555,  4106,  1023,  1127,
    -404,  -404,   291,   282,   310,    58,    59,  -404,  -404,    -3,
    -404,  1231,   296,   312,   -32,  -404,  -404,    60,    16,  -404,
      12,   290,  -404,    19,  -404,  -404,  -404,     9,  -404,   309,
     234,   203,   203,   303,   317,   100,  -404,  1335,   234,  -404,
     306,  4211,   341,  -404,  1439,    13,  -404,   299,  -404,   318,
     129,  4211,   353,  -404,  -404,  4141,  4211,  4211,   176,   234,
     320,   203,   203,   203,   203,  -404,  -404,   195,   180,  -404,
     203,   402,   203,   203,  3207,   203,  -404,  -404,    65,  -404,
    -404,   321,   380,  -404,   397,  -404,  -404,  -404,   264,   180,
     264,  -404,  -404,   319,  -404,  -404,  -404,  -404,  -404,    46,
    -404,  -404,  3443,   145,  4211,  4211,   234,   203,   322,  -404,
    -404,   151,  3207,   203,  -404,  -404,  -404,   101,   203,  -404,
     203,   203,   329,   330,   324,   168,   234,   169,  4211,   172,
    4211,   180,  3497,   175,  -404,  4211,    17,  3775,  3819,  1543,
    4176,   104,   299,   344,  -404,   -14,  -404,  -404,  -404,    19,
    -404,  3207,  4211,  -404,   195,   173,  4211,   348,   195,  1647,
    4211,   331,  -404,   178,  4211,  4211,   332,   334,   340,  -404,
     195,   179,  -404,  -404,  -404,    53,   203,  3207,  3207,  -404,
    3207,  3207,  -404,   203,  -404,    55,  -404,  -404,  1751,   345,
     195,   203,   354,  -404,  -404,  -404,   356,   357,  3207,   358,
     195,  4211,  1855,  1959,  2063,  2167,  3863,  -404,  -404,  3207,
     359,  4211,  3207,   360,   362,  2271,  3207,   364,  -404,  -404,
    -404,  -404,  3207,  2375,  3207,  2479,  3207,  3207,  -404,  2583,
    3207,  2687,  -404,  2791,  -404,  2895,  2999,  -404,  3103,  -404,
    -404,  -404,  -404,  -404
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,   163,     0,     0,     0,
       0,   124,     8,     0,     0,     0,     0,     0,     0,     0,
     195,   196,   197,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   106,   224,     0,     0,     0,   198,   192,   193,
     194,   212,    21,   166,     0,     4,    29,    11,     5,   208,
      18,   209,    12,    15,    16,    13,     9,    10,    17,     0,
      80,    19,   202,   201,    24,    26,    27,    25,    28,    30,
      31,    32,    20,    22,    14,    23,    33,    34,   164,   165,
     206,   167,   211,   205,   200,   203,   207,   210,   204,   106,
     106,     0,     0,     0,   162,     0,   198,     0,     0,     0,
       0,     0,    60,    62,    54,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
     157,     0,   106,   221,   223,    93,    96,     0,    94,     0,
      40,    37,    82,   189,   188,     0,     0,    36,     0,    43,
       0,     0,   107,     0,   225,     0,     0,    50,    51,     1,
       6,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   217,     0,     0,
       0,    93,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    63,    64,     0,     0,     0,    56,     0,    74,     0,
      72,     0,     0,   148,   154,   159,     0,     0,     0,     0,
       0,   228,     0,     0,    53,     0,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   217,     0,     0,
       0,     0,   199,   105,     0,     0,     0,   220,     0,     0,
       0,   169,   170,   171,   172,   173,   182,   183,   184,   185,
     186,   187,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     0,   214,   213,   218,     0,     0,   103,   104,     0,
     114,     0,   100,     0,   119,     0,     0,     0,     0,     0,
     131,    61,    55,     0,     0,     0,     0,    76,    75,     0,
      71,     0,     0,     0,     0,   149,   155,     0,     0,   160,
       0,     0,   140,   143,   139,   137,   138,     0,   133,     0,
      93,     0,     0,     0,     0,     0,     7,     0,    93,   222,
       0,    98,    97,    95,     0,     0,    39,     0,    41,    84,
       0,   117,     0,    35,    42,     0,   108,   226,     0,    93,
       0,   217,     0,   217,     0,   215,   110,   111,     0,   101,
       0,   121,     0,     0,     0,     0,   126,   130,     0,    57,
      78,     0,     0,    65,     0,    58,    73,    79,   148,     0,
       0,   146,   151,     0,   153,   158,   161,   142,   144,     0,
     132,   134,     0,     0,   116,   120,    93,     0,     0,   227,
      44,     0,     0,     0,   190,     2,    68,     0,   217,    83,
       0,     0,     0,     0,    45,     0,    93,     0,     3,     0,
     219,     0,     0,     0,   102,   115,     0,     0,     0,     0,
       0,     0,     0,    67,    77,     0,   152,   150,   156,     0,
     141,   106,   135,   136,   111,     0,   229,     0,   111,     0,
      99,     0,    38,     0,   118,   109,     0,     0,     0,    46,
     111,     0,   168,   216,   112,   113,     0,     0,     0,   123,
       0,     0,   127,     0,    59,     0,   147,   145,     0,     0,
     111,     0,     0,   191,    69,    85,     0,     0,     0,     0,
     111,    90,     0,     0,     0,     0,     0,    66,   231,     0,
       0,   230,     0,     0,     0,     0,     0,     0,    86,   122,
     128,   129,     0,     0,     0,     0,     0,     0,    49,     0,
       0,     0,    87,     0,    88,     0,     0,    91,     0,   125,
      89,    47,    48,    92
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -404,  -404,  -404,  -404,  -103,  -404,  -404,   -23,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,   170,
    -404,   153,    77,    25,  -404,  -404,   159,    91,    88,  -404,
    -404,   394,  -193,  -128,   233,  -225,  -404,   184,  -404,  -404,
    -403,  -404,  -404,    39,  -404,  -404,  -404,  -404,  -404,   235,
    -245,  -303,  -404,  -404,    95,  -300,  -404,  -404,  -404,  -404,
    -404,  -404,    -6,  -404,  -404,  -404,   -22,  -404,  -404,  -404,
    -221,  -404,  -404,  -404,  -404,  -404,  -404,  -404
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     141,    61,    62,    63,   414,   459,    64,    65,    66,   113,
     114,   206,   295,   407,    67,   209,   210,   296,   297,    68,
      69,    70,    71,   137,   138,   283,    72,   151,   152,    73,
     423,    74,    75,    76,    77,    78,    79,    80,    81,   317,
     318,   319,   389,    82,   304,   305,    83,   307,    84,    85,
     310,    86,    87,    88,    89,    90,    91,    92,    93,    94,
     275,    95,    96,    97,   155,    98,   325,   443
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     104,   105,   107,   108,   382,   332,   200,   228,   133,   134,
     388,   204,   234,   121,   342,   311,   340,     3,   207,   311,
     212,   122,   309,   161,   222,   311,     7,   139,   110,   226,
     143,   144,   160,   147,   149,   150,   153,   154,   111,   157,
     158,   479,   308,   196,   192,   482,     3,   380,   162,   122,
     123,   124,    29,   248,   312,   112,   125,   489,   312,   235,
      35,   381,   229,   279,   312,   380,    35,   193,   213,   197,
     303,   308,   391,   115,   238,   236,   205,   500,   131,   476,
     437,    29,   246,   116,   125,   230,   293,   507,   303,    35,
     391,   237,   285,   153,   153,   288,   289,   239,   247,   208,
     101,   294,   390,   313,   102,   385,   405,   313,   301,   468,
     203,   314,   315,   313,   316,   314,   315,   386,   316,    99,
     327,   314,   315,   224,   316,   439,   227,   185,   186,   334,
     417,   299,   419,   424,   451,   382,   477,   372,   374,   383,
     240,   440,   241,   187,   135,   300,   159,   188,   100,   183,
     497,   373,   375,   384,   436,   109,   136,   184,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   160,   271,   398,
     451,   274,   276,   374,   103,   231,   280,   453,   284,   231,
     286,   287,   393,   399,   452,   337,   464,   474,   232,   160,
     401,   330,   354,   160,   231,   338,     1,     2,   354,   164,
     165,   166,   167,   168,   355,   117,   357,   166,   167,   168,
     409,   415,   118,   331,   231,   160,   119,    20,    21,    22,
     231,   274,   341,   120,    24,   183,   444,   126,   345,   346,
     347,   183,   448,   184,    30,    31,    32,   231,   354,   184,
     127,   354,   231,    36,   128,   466,   129,   354,   231,   460,
     462,   429,   160,   463,   480,   160,   160,   467,   445,   485,
     490,    37,   421,   412,   281,   422,   413,   194,   160,   130,
     201,   202,   282,   189,   190,   140,   156,   142,   461,   145,
     191,    39,    40,    41,   112,    42,   211,    43,   214,   449,
     215,   217,   220,   218,   160,    47,    48,    49,    50,    51,
     221,   160,   219,   223,   225,   394,   395,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   136,   243,   478,   244,
     249,   250,   270,   183,   272,   274,   418,   274,   420,   273,
     277,   184,   278,   291,   425,   292,   427,   428,   298,   430,
     302,   320,   321,   356,   492,   493,   303,   494,   495,   306,
     322,   323,   324,   328,   336,   339,   349,   350,   351,   353,
     358,   359,   360,   368,   370,   505,   442,   371,   378,   379,
     392,   446,   387,   396,   397,   403,   513,   450,   402,   515,
     465,   406,   274,   519,   454,   455,   160,   410,   408,   521,
     416,   523,   426,   525,   526,   432,   294,   528,   293,   456,
     457,   438,   458,   372,   447,   481,   160,   164,   165,   166,
     167,   168,   488,   484,   486,   227,   487,   499,   175,   176,
     177,   178,   179,   180,   181,   369,   502,   503,   504,   433,
     506,   514,   516,   183,   517,   160,   520,   475,   376,   431,
     491,   184,   434,   163,   333,   469,     0,   496,   335,   160,
     160,   160,   160,   435,     0,   501,     0,     0,     0,     0,
       0,     0,   160,     0,     0,     0,     0,     0,     0,     0,
     160,     0,   160,     0,     0,     0,   160,     0,   160,     0,
     160,     0,   160,   160,     0,   160,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,    35,     0,    36,   164,   165,   166,   167,   168,     0,
     164,   165,   166,   167,   168,   175,   176,   177,   178,   179,
     180,    37,     0,   177,   178,   179,   180,     0,     0,     0,
     183,     0,     0,     0,     0,     0,   183,     0,   184,     0,
      38,    39,    40,    41,   184,    42,   290,    43,     0,    44,
       0,     0,    45,     0,    46,    47,    48,    49,    50,    51,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,    35,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,     0,    42,
     326,    43,     0,    44,     0,     0,    45,     0,    46,    47,
      48,    49,    50,    51,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,    35,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,     0,    42,   329,    43,     0,    44,     0,     0,
      45,     0,    46,    47,    48,    49,    50,    51,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,    35,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,     0,    42,   348,    43,
       0,    44,     0,     0,    45,     0,    46,    47,    48,    49,
      50,    51,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,    35,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
       0,    42,   361,    43,     0,    44,     0,     0,    45,     0,
      46,    47,    48,    49,    50,    51,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,    35,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,     0,    42,   366,    43,     0,    44,
       0,     0,    45,     0,    46,    47,    48,    49,    50,    51,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,    35,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,     0,    42,
     367,    43,     0,    44,     0,     0,    45,     0,    46,    47,
      48,    49,    50,    51,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,    35,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,     0,    42,   377,    43,     0,    44,     0,     0,
      45,     0,    46,    47,    48,    49,    50,    51,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,    35,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,     0,    42,   400,    43,
       0,    44,     0,     0,    45,     0,    46,    47,    48,    49,
      50,    51,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,    35,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
       0,    42,   404,    43,     0,    44,     0,     0,    45,     0,
      46,    47,    48,    49,    50,    51,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,    35,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,     0,    42,   472,    43,     0,    44,
       0,     0,    45,     0,    46,    47,    48,    49,    50,    51,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,    35,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,     0,    42,
     483,    43,     0,    44,     0,     0,    45,     0,    46,    47,
      48,    49,    50,    51,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,    35,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,     0,    42,   498,    43,     0,    44,     0,     0,
      45,     0,    46,    47,    48,    49,    50,    51,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,    35,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,     0,    42,   508,    43,
       0,    44,     0,     0,    45,     0,    46,    47,    48,    49,
      50,    51,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,    35,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
       0,    42,   509,    43,     0,    44,     0,     0,    45,     0,
      46,    47,    48,    49,    50,    51,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,    35,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,     0,    42,   510,    43,     0,    44,
       0,     0,    45,     0,    46,    47,    48,    49,    50,    51,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,    35,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,     0,    42,
     511,    43,     0,    44,     0,     0,    45,     0,    46,    47,
      48,    49,    50,    51,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,    35,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,     0,    42,   518,    43,     0,    44,     0,     0,
      45,     0,    46,    47,    48,    49,    50,    51,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,    35,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,     0,    42,   522,    43,
       0,    44,     0,     0,    45,     0,    46,    47,    48,    49,
      50,    51,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,    35,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
       0,    42,   524,    43,     0,    44,     0,     0,    45,     0,
      46,    47,    48,    49,    50,    51,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,    35,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,     0,    42,   527,    43,     0,    44,
       0,     0,    45,     0,    46,    47,    48,    49,    50,    51,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,    35,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,    40,    41,     0,    42,
     529,    43,     0,    44,     0,     0,    45,     0,    46,    47,
      48,    49,    50,    51,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,    35,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,     0,    42,   530,    43,     0,    44,     0,     0,
      45,     0,    46,    47,    48,    49,    50,    51,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,    35,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,     0,    42,   531,    43,
       0,    44,     0,     0,    45,     0,    46,    47,    48,    49,
      50,    51,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,    35,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
       0,    42,   532,    43,     0,    44,     0,     0,    45,     0,
      46,    47,    48,    49,    50,    51,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,    35,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,     0,    42,   533,    43,     0,    44,
       0,     0,    45,     0,    46,    47,    48,    49,    50,    51,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     1,     2,    33,    34,    35,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,    21,    22,    37,     0,     0,     0,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,     0,     0,    38,    39,    40,    41,    36,    42,
       0,    43,     0,    44,     0,     0,    45,     0,    46,    47,
      48,    49,    50,    51,     0,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     2,    39,    40,    41,     0,
      42,     0,    43,     0,     0,     0,     0,     0,     0,     0,
     106,    48,    49,    50,    51,    20,    21,    22,     0,     0,
       0,     0,    24,     1,     2,     0,     0,     0,     0,     0,
       0,     0,    30,    31,    32,     0,     0,     0,     0,     0,
       0,    36,     0,     0,    20,    21,    22,     0,     0,     0,
       0,    24,     0,     0,     0,     0,     0,     0,     0,    37,
       0,    30,    31,    32,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     1,     2,    39,
      40,   146,     0,    42,     0,    43,     0,     0,    37,     0,
       0,     0,     0,    47,    48,    49,    50,    51,    20,    21,
      22,     0,     0,     0,     0,    24,     1,     2,    39,    40,
     148,     0,    42,     0,    43,    30,    31,    32,     0,     0,
       0,     0,    47,    48,    49,    50,    51,    20,    21,    22,
       0,     0,     0,     0,    24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    31,    32,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       1,     2,    39,    40,    41,     0,   132,     0,    43,     0,
       0,    37,     0,     0,     0,     0,    47,    48,    49,    50,
      51,    20,    21,    22,     0,     0,     0,     0,    24,     0,
       0,    39,    40,    41,     0,   441,     0,    43,    30,    31,
      32,     0,     0,     0,     0,    47,    48,    49,    50,    51,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,     0,     0,     0,     0,     0,   183,     0,     0,     0,
       0,     0,     0,     0,   184,    39,    40,    41,     0,    42,
       0,    43,     0,   195,     0,     0,     0,     0,     0,    47,
      48,    49,    50,    51,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,     0,     0,     0,     0,     0,     0,     0,
     183,     0,     0,     0,     0,     0,     0,     0,   184,     0,
     362,   363,     0,     0,     0,     0,     0,   364,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,     0,     0,     0,
       0,     0,     0,     0,   183,     0,     0,     0,     0,     0,
       0,     0,   184,     0,     0,     0,     0,     0,     0,     0,
       0,   198,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,     0,     0,     0,     0,     0,     0,     0,   183,     0,
       0,     0,     0,     0,     0,     0,   184,     0,     0,     0,
       0,     0,     0,     0,     0,   199,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,     0,     0,     0,     0,     0,
       0,     0,   183,     0,     0,     0,     0,     0,     0,     0,
     184,     0,     0,     0,     0,     0,     0,     0,     0,   216,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,     0,     0,     0,     0,     0,   183,     0,     0,     0,
       0,     0,     0,     0,   184,     0,     0,     0,     0,     0,
       0,     0,     0,   233,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,     0,     0,     0,     0,     0,     0,     0,
     183,     0,     0,     0,     0,     0,     0,     0,   184,     0,
       0,     0,     0,     0,     0,     0,     0,   470,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,     0,     0,     0,
       0,     0,     0,     0,   183,     0,     0,     0,     0,     0,
       0,     0,   184,     0,     0,     0,     0,     0,     0,     0,
       0,   471,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,     0,     0,     0,     0,     0,     0,     0,   183,     0,
       0,     0,     0,     0,     0,     0,   184,     0,     0,     0,
       0,     0,     0,     0,     0,   512,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,     0,     0,     0,     0,     0,
       0,     0,   183,     0,     0,     0,     0,     0,     0,     0,
     184,     0,     0,     0,     0,     0,     0,     0,   242,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,     0,     0,
       0,     0,     0,     0,     0,   183,     0,     0,     0,     0,
       0,     0,     0,   184,     0,     0,     0,     0,     0,     0,
       0,   343,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,     0,     0,     0,     0,     0,     0,     0,   183,     0,
       0,     0,     0,     0,     0,     0,   184,     0,     0,     0,
       0,     0,     0,     0,   344,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,     0,     0,     0,     0,     0,     0,
       0,   183,     0,     0,     0,     0,     0,   245,     0,   184,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,     0,     0,     0,     0,     0,   183,     0,   352,     0,
       0,     0,     0,     0,   184,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,     0,     0,     0,     0,     0,     0,
       0,   183,     0,     0,   365,     0,     0,     0,     0,   184,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,     0,     0,     0,     0,     0,   183,     0,     0,     0,
       0,     0,   411,     0,   184,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,     0,     0,     0,     0,     0,     0,
       0,   183,     0,     0,   473,     0,     0,     0,     0,   184,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,     0,
       0,     0,     0,     0,     0,     0,   183,     0,     0,     0,
       0,     0,     0,     0,   184
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,   304,   230,   109,   135,    30,    31,
     313,    27,    27,    19,   239,     6,   237,     5,    21,     6,
      44,     5,   215,     5,   127,     6,     9,    33,    75,   132,
      36,    37,    55,    39,    40,    41,    42,    43,    85,    45,
      46,   444,    30,    28,    54,   448,     5,    79,    30,     5,
       6,     7,    40,   156,    45,   102,    40,   460,    45,    74,
      48,    93,    54,   191,    45,    79,    48,    77,    92,    54,
     102,    30,   317,    92,    54,    74,    92,   480,     5,    93,
     380,    40,    79,   102,    40,    77,    21,   490,   102,    48,
     335,    90,   195,    99,   100,   198,   199,    77,    95,   102,
     102,    36,    93,    94,   102,    93,    93,    94,   211,    92,
      75,   102,   103,    94,   105,   102,   103,   310,   105,    92,
     223,   102,   103,   129,   105,    79,   132,    74,    75,   232,
     351,    79,   353,   358,    79,   435,   439,    79,    79,    79,
     146,    95,   148,    90,    90,    93,     0,    94,    92,    75,
      95,    93,    93,    93,   379,    92,   102,    83,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   200,   184,    79,
      79,   187,   188,    79,   102,    79,   192,   408,   194,    79,
     196,   197,   320,    93,    93,    92,   421,    93,    92,   222,
     328,    91,    79,   226,    79,   102,     3,     4,    79,    49,
      50,    51,    52,    53,    91,   102,    91,    51,    52,    53,
      91,   349,   102,   229,    79,   248,   102,    24,    25,    26,
      79,   237,   238,   102,    31,    75,    91,   102,   244,   245,
     246,    75,    91,    83,    41,    42,    43,    79,    79,    83,
      92,    79,    79,    50,   102,    80,   102,    79,    79,    91,
      91,   364,   285,    91,    91,   288,   289,    92,   396,    91,
      91,    68,    77,    97,    94,    80,   100,    54,   301,   102,
     110,   111,   102,    99,   100,   102,    92,   102,   416,   102,
      90,    88,    89,    90,   102,    92,    92,    94,    92,   402,
      92,   102,     5,   102,   327,   102,   103,   104,   105,   106,
      92,   334,   102,    92,   102,   321,   322,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,   102,    93,   441,    79,
     102,     5,   102,    75,   102,   351,   352,   353,   354,   102,
      93,    83,    93,   102,   360,   102,   362,   363,   102,   365,
     102,    90,    54,    95,   467,   468,   102,   470,   471,   102,
      54,   102,   102,    90,   102,   102,    90,   102,    90,    90,
      95,    83,    54,    92,   102,   488,   392,    77,    92,    77,
      81,   397,   102,    90,    77,    54,   499,   403,    92,   502,
     422,   102,   408,   506,   410,   411,   429,    54,    90,   512,
      90,   514,    10,   516,   517,    94,    36,   520,    21,    90,
      90,   102,    98,    79,   102,    77,   449,    49,    50,    51,
      52,    53,    92,   102,   102,   441,   102,    92,    60,    61,
      62,    63,    64,    65,    66,   292,    92,    91,    91,   372,
      92,    92,    92,    75,    92,   478,    92,   432,   299,   368,
     466,    83,   374,    69,   231,   426,    -1,   473,   233,   492,
     493,   494,   495,   378,    -1,   481,    -1,    -1,    -1,    -1,
      -1,    -1,   505,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     513,    -1,   515,    -1,    -1,    -1,   519,    -1,   521,    -1,
     523,    -1,   525,   526,    -1,   528,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    48,    -1,    50,    49,    50,    51,    52,    53,    -1,
      49,    50,    51,    52,    53,    60,    61,    62,    63,    64,
      65,    68,    -1,    62,    63,    64,    65,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    75,    -1,    83,    -1,
      87,    88,    89,    90,    83,    92,    93,    94,    -1,    96,
      -1,    -1,    99,    -1,   101,   102,   103,   104,   105,   106,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    88,    89,    90,    -1,    92,
      93,    94,    -1,    96,    -1,    -1,    99,    -1,   101,   102,
     103,   104,   105,   106,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    48,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,
      89,    90,    -1,    92,    93,    94,    -1,    96,    -1,    -1,
      99,    -1,   101,   102,   103,   104,   105,   106,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    47,    48,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    88,    89,    90,    -1,    92,    93,    94,
      -1,    96,    -1,    -1,    99,    -1,   101,   102,   103,   104,
     105,   106,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    47,    48,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,
      -1,    92,    93,    94,    -1,    96,    -1,    -1,    99,    -1,
     101,   102,   103,   104,   105,   106,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    -1,    92,    93,    94,    -1,    96,
      -1,    -1,    99,    -1,   101,   102,   103,   104,   105,   106,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    88,    89,    90,    -1,    92,
      93,    94,    -1,    96,    -1,    -1,    99,    -1,   101,   102,
     103,   104,   105,   106,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    48,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,
      89,    90,    -1,    92,    93,    94,    -1,    96,    -1,    -1,
      99,    -1,   101,   102,   103,   104,   105,   106,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    47,    48,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    88,    89,    90,    -1,    92,    93,    94,
      -1,    96,    -1,    -1,    99,    -1,   101,   102,   103,   104,
     105,   106,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    47,    48,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,
      -1,    92,    93,    94,    -1,    96,    -1,    -1,    99,    -1,
     101,   102,   103,   104,   105,   106,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    -1,    92,    93,    94,    -1,    96,
      -1,    -1,    99,    -1,   101,   102,   103,   104,   105,   106,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    88,    89,    90,    -1,    92,
      93,    94,    -1,    96,    -1,    -1,    99,    -1,   101,   102,
     103,   104,   105,   106,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    48,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,
      89,    90,    -1,    92,    93,    94,    -1,    96,    -1,    -1,
      99,    -1,   101,   102,   103,   104,   105,   106,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    47,    48,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    88,    89,    90,    -1,    92,    93,    94,
      -1,    96,    -1,    -1,    99,    -1,   101,   102,   103,   104,
     105,   106,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    47,    48,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,
      -1,    92,    93,    94,    -1,    96,    -1,    -1,    99,    -1,
     101,   102,   103,   104,   105,   106,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    -1,    92,    93,    94,    -1,    96,
      -1,    -1,    99,    -1,   101,   102,   103,   104,   105,   106,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    88,    89,    90,    -1,    92,
      93,    94,    -1,    96,    -1,    -1,    99,    -1,   101,   102,
     103,   104,   105,   106,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    48,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,
      89,    90,    -1,    92,    93,    94,    -1,    96,    -1,    -1,
      99,    -1,   101,   102,   103,   104,   105,   106,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    47,    48,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    88,    89,    90,    -1,    92,    93,    94,
      -1,    96,    -1,    -1,    99,    -1,   101,   102,   103,   104,
     105,   106,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    47,    48,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,
      -1,    92,    93,    94,    -1,    96,    -1,    -1,    99,    -1,
     101,   102,   103,   104,   105,   106,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    -1,    92,    93,    94,    -1,    96,
      -1,    -1,    99,    -1,   101,   102,   103,   104,   105,   106,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    88,    89,    90,    -1,    92,
      93,    94,    -1,    96,    -1,    -1,    99,    -1,   101,   102,
     103,   104,   105,   106,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    48,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,
      89,    90,    -1,    92,    93,    94,    -1,    96,    -1,    -1,
      99,    -1,   101,   102,   103,   104,   105,   106,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    47,    48,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,    88,    89,    90,    -1,    92,    93,    94,
      -1,    96,    -1,    -1,    99,    -1,   101,   102,   103,   104,
     105,   106,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    47,    48,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,
      -1,    92,    93,    94,    -1,    96,    -1,    -1,    99,    -1,
     101,   102,   103,   104,   105,   106,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    -1,    92,    93,    94,    -1,    96,
      -1,    -1,    99,    -1,   101,   102,   103,   104,   105,   106,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,     3,     4,    46,    47,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    68,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    -1,    -1,    87,    88,    89,    90,    50,    92,
      -1,    94,    -1,    96,    -1,    -1,    99,    -1,   101,   102,
     103,   104,   105,   106,    -1,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,    88,    89,    90,    -1,
      92,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,    24,    25,    26,    -1,    -1,
      -1,    -1,    31,     3,     4,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    88,
      89,    90,    -1,    92,    -1,    94,    -1,    -1,    68,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,    24,    25,
      26,    -1,    -1,    -1,    -1,    31,     3,     4,    88,    89,
      90,    -1,    92,    -1,    94,    41,    42,    43,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,    24,    25,    26,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,    88,    89,    90,    -1,    92,    -1,    94,    -1,
      -1,    68,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,    24,    25,    26,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    88,    89,    90,    -1,    92,    -1,    94,    41,    42,
      43,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    88,    89,    90,    -1,    92,
      -1,    94,    -1,    92,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,   106,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,
      85,    86,    -1,    -1,    -1,    -1,    -1,    92,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    92,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    92,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    -1,    81,    -1,    83,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    83,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    -1,    83,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    83,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    -1,    78,    -1,    -1,    -1,    -1,    83,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    40,
      41,    42,    43,    46,    47,    48,    50,    68,    87,    88,
      89,    90,    92,    94,    96,    99,   101,   102,   103,   104,
     105,   106,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   118,   119,   120,   123,   124,   125,   131,   136,   137,
     138,   139,   143,   146,   148,   149,   150,   151,   152,   153,
     154,   155,   160,   163,   165,   166,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   178,   179,   180,   182,    92,
      92,   102,   102,   102,   169,   169,   102,   169,   169,    92,
      75,    85,   102,   126,   127,    92,   102,   102,   102,   102,
     102,   169,     5,     6,     7,    40,   102,    92,   102,   102,
     102,     5,    92,   173,   173,    90,   102,   140,   141,   169,
     102,   117,   102,   169,   169,   102,    90,   169,    90,   169,
     169,   144,   145,   169,   169,   181,    92,   169,   169,     0,
     114,     5,    30,   138,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    75,    83,    74,    75,    90,    94,   144,
     144,    90,    54,    77,    54,    92,    28,    54,    92,    92,
     111,   126,   126,    75,    27,    92,   128,    21,   102,   132,
     133,    92,    44,    92,    92,    92,    92,   102,   102,   102,
       5,    92,   111,    92,   169,   102,   111,   169,   140,    54,
      77,    79,    92,    92,    27,    74,    74,    90,    54,    77,
     169,   169,    91,    93,    79,    81,    79,    95,   111,   102,
       5,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     102,   169,   102,   102,   169,   177,   169,    93,    93,   140,
     169,    94,   102,   142,   169,   111,   169,   169,   111,   111,
      93,   102,   102,    21,    36,   129,   134,   135,   102,    79,
      93,   111,   102,   102,   161,   162,   102,   164,    30,   139,
     167,     6,    45,    94,   102,   103,   105,   156,   157,   158,
      90,    54,    54,   102,   102,   183,    93,   111,    90,    93,
      91,   169,   142,   141,   111,   156,   102,    92,   102,   102,
     177,   169,   142,    91,    91,   169,   169,   169,    93,    90,
     102,    90,    77,    90,    79,    91,    95,    91,    95,    83,
      54,    93,    85,    86,    92,    78,    93,    93,    92,   128,
     102,    77,    79,    93,    79,    93,   133,    93,    92,    77,
      79,    93,   162,    79,    93,    93,   139,   102,   158,   159,
      93,   157,    81,   140,   169,   169,    90,    77,    79,    93,
      93,   140,    92,    54,    93,    93,   102,   130,    90,    91,
      54,    81,    97,   100,   121,   140,    90,   177,   169,   177,
     169,    77,    80,   147,   142,   169,    10,   169,   169,   111,
     169,   134,    94,   129,   135,   161,   142,   162,   102,    79,
      95,    92,   169,   184,    91,   140,   169,   102,    91,   111,
     169,    79,    93,   177,   169,   169,    90,    90,    98,   122,
      91,   140,    91,    91,   142,   173,    80,    92,    92,   150,
      92,    92,    93,    78,    93,   130,    93,   158,   111,   147,
      91,    77,   147,    93,   102,    91,   102,   102,    92,   147,
      91,   169,   111,   111,   111,   111,   169,    95,    93,    92,
     147,   169,    92,    91,    91,   111,    92,   147,    93,    93,
      93,    93,    92,   111,    92,   111,    92,    92,    93,   111,
      92,   111,    93,   111,    93,   111,   111,    93,   111,    93,
      93,    93,    93,    93
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   109,   110,   111,   111,   112,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   115,   115,   116,   116,   116,
     117,   117,   118,   118,   119,   120,   120,   121,   121,   122,
     123,   123,   124,   124,   125,   125,   125,   125,   125,   125,
     126,   126,   127,   127,   127,   128,   129,   129,   130,   130,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   136,
     137,   137,   138,   138,   138,   138,   139,   139,   139,   139,
     139,   139,   139,   140,   140,   140,   141,   141,   141,   141,
     142,   142,   142,   143,   143,   143,   144,   144,   145,   145,
     146,   147,   147,   147,   148,   148,   148,   148,   148,   149,
     149,   150,   150,   150,   151,   152,   152,   152,   152,   152,
     153,   154,   155,   156,   156,   157,   157,   158,   158,   158,
     158,   158,   158,   159,   159,   159,   160,   160,   161,   161,
     161,   161,   162,   163,   164,   164,   164,   165,   166,   167,
     167,   167,   168,   168,   169,   169,   169,   169,   169,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   171,   171,
     172,   172,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   174,   175,   175,   176,   176,   177,   177,   177,
     178,   179,   179,   180,   181,   181,   181,   182,   183,   183,
     183,   184
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     5,     1,     1,     2,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     2,     2,     6,     4,
       1,     3,     4,     2,     5,     5,     6,     7,     7,     4,
       2,     2,     2,     3,     2,     4,     3,     5,     5,     7,
       1,     3,     1,     2,     2,     3,     5,     3,     1,     3,
       2,     4,     1,     3,     1,     2,     1,     3,     2,     5,
       1,     2,     2,     5,     4,     7,     9,    10,    10,    11,
       8,    10,    11,     0,     1,     3,     1,     3,     3,     5,
       1,     2,     3,     4,     4,     3,     0,     1,     3,     5,
       4,     0,     2,     2,     4,     6,     5,     4,     6,     4,
       5,     5,     9,     7,     1,    11,     5,     7,     9,     9,
       5,     4,     5,     1,     2,     3,     3,     1,     1,     1,
       1,     3,     2,     0,     1,     3,     5,     7,     0,     1,
       3,     2,     3,     5,     0,     1,     3,     2,     5,     0,
       1,     2,     2,     1,     1,     1,     1,     1,     6,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       5,     7,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     4,     6,     0,     1,     3,
       3,     2,     4,     2,     0,     1,     3,     5,     0,     3,
       5,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* switch_statement: TOKEN_SWITCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 126 "src/parser/parser.y"
                                                                  {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2398 "parser.c"
    break;

  case 3: /* ternary_expr: expression TOKEN_OPTIONAL expression TOKEN_COLON expression  */
#line 131 "src/parser/parser.y"
                                                                {
        // condition ? true_expr : false_expr
        (yyval.node) = create_ternary_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2407 "parser.c"
    break;

  case 4: /* program: statement_list  */
#line 138 "src/parser/parser.y"
                   {
        program_root = create_program_node((yyvsp[0].node_list));
    }
#line 2415 "parser.c"
    break;

  case 5: /* statement_list: statement  */
#line 144 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2424 "parser.c"
    break;

  case 6: /* statement_list: statement_list statement  */
#line 148 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2433 "parser.c"
    break;

  case 7: /* unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 154 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_unsafe_node((yyvsp[-1].node_list));
    }
#line 2441 "parser.c"
    break;

  case 8: /* continue_statement: TOKEN_CONTINUE  */
#line 159 "src/parser/parser.y"
                   {
        (yyval.node) = create_continue_node();
    }
#line 2449 "parser.c"
    break;

  case 34: /* statement: expression  */
#line 191 "src/parser/parser.y"
                 {
        (yyval.node) = create_expr_statement((yyvsp[0].node));
    }
#line 2457 "parser.c"
    break;

  case 35: /* sysf_expr: TOKEN_SYSF TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 196 "src/parser/parser.y"
                                                    {
        (yyval.node) = create_sysf_node((yyvsp[-1].node));
    }
#line 2465 "parser.c"
    break;

  case 36: /* sysf_expr: TOKEN_SYSF expression  */
#line 199 "src/parser/parser.y"
                            {
        (yyval.node) = create_sysf_node((yyvsp[0].node));
    }
#line 2473 "parser.c"
    break;

  case 37: /* use_statement: TOKEN_USE use_path  */
#line 206 "src/parser/parser.y"
                       {
        (yyval.node) = create_use_node((yyvsp[0].string), NULL);
    }
#line 2481 "parser.c"
    break;

  case 38: /* use_statement: TOKEN_USE use_path TOKEN_DOUBLE_COLON TOKEN_LBRACE name_list TOKEN_RBRACE  */
#line 210 "src/parser/parser.y"
                                                                                {
        (yyval.node) = create_use_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2489 "parser.c"
    break;

  case 39: /* use_statement: TOKEN_USE use_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 214 "src/parser/parser.y"
                                                   {
        (yyval.node) = create_use_node((yyvsp[-2].string), NULL);
        // Stocker l'alias dans le nœud
        (yyval.node)->use_stmt.alias = strdup((yyvsp[0].string));
    }
#line 2499 "parser.c"
    break;

  case 40: /* use_path: TOKEN_IDENTIFIER  */
#line 222 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2507 "parser.c"
    break;

  case 41: /* use_path: use_path TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 225 "src/parser/parser.y"
                                                   {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 3);
        sprintf(path, "%s::%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2518 "parser.c"
    break;

  case 42: /* sh_expr: TOKEN_SH TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 234 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_sh_node((yyvsp[-1].node));
    }
#line 2526 "parser.c"
    break;

  case 43: /* sh_expr: TOKEN_SH expression  */
#line 237 "src/parser/parser.y"
                          {
        (yyval.node) = create_sh_node((yyvsp[0].node));
    }
#line 2534 "parser.c"
    break;

  case 44: /* nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 243 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_nnl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2542 "parser.c"
    break;

  case 45: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block  */
#line 249 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_try_node((yyvsp[-2].node_list), (yyvsp[0].node), NULL);
    }
#line 2550 "parser.c"
    break;

  case 46: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block  */
#line 252 "src/parser/parser.y"
                                                                                   {
        (yyval.node) = create_try_node((yyvsp[-3].node_list), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2558 "parser.c"
    break;

  case 47: /* catch_block: TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 258 "src/parser/parser.y"
                                                                                                    {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2566 "parser.c"
    break;

  case 48: /* catch_block: TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 261 "src/parser/parser.y"
                                                                                                       {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2574 "parser.c"
    break;

  case 49: /* finally_block: TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 267 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_finally_node((yyvsp[-1].node_list));
    }
#line 2582 "parser.c"
    break;

  case 50: /* throw_statement: TOKEN_THROW expression  */
#line 273 "src/parser/parser.y"
                           {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2590 "parser.c"
    break;

  case 51: /* throw_statement: TOKEN_RAISE expression  */
#line 276 "src/parser/parser.y"
                             {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2598 "parser.c"
    break;

  case 52: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER  */
#line 281 "src/parser/parser.y"
                               {
        (yyval.node) = create_jmp_node((yyvsp[0].string), NULL);
    }
#line 2606 "parser.c"
    break;

  case 53: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression  */
#line 284 "src/parser/parser.y"
                                            {
        (yyval.node) = create_jmp_node((yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2614 "parser.c"
    break;

  case 54: /* import_statement: TOKEN_IMPORT import_path  */
#line 293 "src/parser/parser.y"
                             {
        (yyval.node) = create_import_node((yyvsp[0].string), NULL, NULL);
    }
#line 2622 "parser.c"
    break;

  case 55: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 297 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_import_node((yyvsp[-2].string), (yyvsp[0].string), NULL);
    }
#line 2630 "parser.c"
    break;

  case 56: /* import_statement: TOKEN_IMPORT import_path import_constraints  */
#line 301 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_import_node((yyvsp[-1].string), NULL, (yyvsp[0].node));
    }
#line 2638 "parser.c"
    break;

  case 57: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER import_constraints  */
#line 305 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_import_node((yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2646 "parser.c"
    break;

  case 58: /* import_statement: TOKEN_IMPORT import_path TOKEN_LBRACE import_impl_list TOKEN_RBRACE  */
#line 309 "src/parser/parser.y"
                                                                          {
        ASTNode* node = create_import_node((yyvsp[-3].string), NULL, NULL);
        node->import.impl_list = (yyvsp[-1].node_list);
        (yyval.node) = node;
    }
#line 2656 "parser.c"
    break;

  case 59: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER TOKEN_LBRACE import_impl_list TOKEN_RBRACE  */
#line 315 "src/parser/parser.y"
                                                                                                    {
        ASTNode* node = create_import_node((yyvsp[-5].string), (yyvsp[-3].string), NULL);
        node->import.impl_list = (yyvsp[-1].node_list);
        (yyval.node) = node;
    }
#line 2666 "parser.c"
    break;

  case 60: /* import_path_tail: TOKEN_IDENTIFIER  */
#line 324 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2674 "parser.c"
    break;

  case 61: /* import_path_tail: import_path_tail TOKEN_DOT TOKEN_IDENTIFIER  */
#line 327 "src/parser/parser.y"
                                                  {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 2);
        sprintf(path, "%s.%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2685 "parser.c"
    break;

  case 62: /* import_path: import_path_tail  */
#line 336 "src/parser/parser.y"
                     { 
        (yyval.string) = (yyvsp[0].string); 
    }
#line 2693 "parser.c"
    break;

  case 63: /* import_path: TOKEN_DOT import_path_tail  */
#line 339 "src/parser/parser.y"
                                 { // Import relatif: .fichier
        char* path = malloc(strlen((yyvsp[0].string)) + 2);
        sprintf(path, ".%s", (yyvsp[0].string));
        free((yyvsp[0].string));
        (yyval.string) = path;
    }
#line 2704 "parser.c"
    break;

  case 64: /* import_path: TOKEN_RANGE import_path_tail  */
#line 345 "src/parser/parser.y"
                                   { // Import relatif: ..fichier (utilise TOKEN_RANGE ".." du lexer)
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "..%s", (yyvsp[0].string));
        free((yyvsp[0].string));
        (yyval.string) = path;
    }
#line 2715 "parser.c"
    break;

  case 65: /* import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE  */
#line 354 "src/parser/parser.y"
                                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2723 "parser.c"
    break;

  case 66: /* import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET  */
#line 360 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_constraints_node("only", (yyvsp[-1].node_list));
    }
#line 2731 "parser.c"
    break;

  case 67: /* import_options: import_options TOKEN_COMMA import_options  */
#line 363 "src/parser/parser.y"
                                                {
        (yyval.node) = merge_constraints((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2739 "parser.c"
    break;

  case 68: /* name_list: TOKEN_IDENTIFIER  */
#line 369 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2748 "parser.c"
    break;

  case 69: /* name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 373 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2757 "parser.c"
    break;

  case 70: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
#line 380 "src/parser/parser.y"
                                  {
        (yyval.node) = create_export_node((yyvsp[0].string));
    }
#line 2765 "parser.c"
    break;

  case 71: /* export_statement: TOKEN_EXPORT TOKEN_LBRACE export_list TOKEN_RBRACE  */
#line 384 "src/parser/parser.y"
                                                         {
        ASTNode* node = create_export_node(NULL);
        node->export.export_list = (yyvsp[-1].node_list);
        (yyval.node) = node;
    }
#line 2775 "parser.c"
    break;

  case 72: /* export_list: export_item  */
#line 392 "src/parser/parser.y"
                {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2784 "parser.c"
    break;

  case 73: /* export_list: export_list TOKEN_COMMA export_item  */
#line 396 "src/parser/parser.y"
                                          {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2793 "parser.c"
    break;

  case 74: /* export_item: TOKEN_IDENTIFIER  */
#line 403 "src/parser/parser.y"
                     {
        ASTNode* node = create_identifier_node((yyvsp[0].string));
        node->is_impl = 0;
        (yyval.node) = node;
    }
#line 2803 "parser.c"
    break;

  case 75: /* export_item: TOKEN_IMPL TOKEN_IDENTIFIER  */
#line 409 "src/parser/parser.y"
                                  {
        ASTNode* node = create_identifier_node((yyvsp[0].string));
        node->is_impl = 1;
        (yyval.node) = node;
    }
#line 2813 "parser.c"
    break;

  case 76: /* import_impl_list: import_impl_item  */
#line 417 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2822 "parser.c"
    break;

  case 77: /* import_impl_list: import_impl_list TOKEN_COMMA import_impl_item  */
#line 421 "src/parser/parser.y"
                                                    {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2831 "parser.c"
    break;

  case 78: /* import_impl_item: TOKEN_IMPL TOKEN_IDENTIFIER  */
#line 429 "src/parser/parser.y"
                                {
        ASTNode* node = create_identifier_node((yyvsp[0].string));
        node->is_impl = 1;
        (yyval.node) = node;
    }
#line 2841 "parser.c"
    break;

  case 79: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 437 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_packet_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2849 "parser.c"
    break;

  case 80: /* decorator_list: decorator  */
#line 447 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2858 "parser.c"
    break;

  case 81: /* decorator_list: decorator_list decorator  */
#line 451 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2867 "parser.c"
    break;

  case 82: /* decorator: TOKEN_AT TOKEN_IDENTIFIER  */
#line 459 "src/parser/parser.y"
                              {
        (yyval.node) = create_decorator_node((yyvsp[0].string), NULL, NULL);
    }
#line 2875 "parser.c"
    break;

  case 83: /* decorator: TOKEN_AT TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 463 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_decorator_node((yyvsp[-3].string), NULL, (yyvsp[-1].node_list));
    }
#line 2883 "parser.c"
    break;

  case 84: /* decorator: TOKEN_AT TOKEN_IDENTIFIER TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 467 "src/parser/parser.y"
                                                                    {
        char* full = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 3);
        sprintf(full, "%s::%s", (yyvsp[-2].string), (yyvsp[0].string));
        (yyval.node) = create_decorator_node(full, NULL, NULL);
        free(full);
    }
#line 2894 "parser.c"
    break;

  case 85: /* decorator: TOKEN_AT TOKEN_IDENTIFIER TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 474 "src/parser/parser.y"
                                                                                                            {
        char* full = malloc(strlen((yyvsp[-5].string)) + strlen((yyvsp[-3].string)) + 3);
        sprintf(full, "%s::%s", (yyvsp[-5].string), (yyvsp[-3].string));
        (yyval.node) = create_decorator_node(full, NULL, (yyvsp[-1].node_list));
        free(full);
    }
#line 2905 "parser.c"
    break;

  case 86: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 483 "src/parser/parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2913 "parser.c"
    break;

  case 87: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 486 "src/parser/parser.y"
                                                                                                                                    {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2921 "parser.c"
    break;

  case 88: /* function_decl: TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 489 "src/parser/parser.y"
                                                                                                                                      {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        (yyval.node) = node;
    }
#line 2932 "parser.c"
    break;

  case 89: /* function_decl: TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 495 "src/parser/parser.y"
                                                                                                                                                {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        (yyval.node) = node;
    }
#line 2944 "parser.c"
    break;

  case 90: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression  */
#line 502 "src/parser/parser.y"
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node((yyvsp[0].node));
        add_to_node_list(body, return_stmt);
        (yyval.node) = create_function_node((yyvsp[-6].string), (yyvsp[-4].node_list), (yyvsp[-2].node), body);
    }
#line 2955 "parser.c"
    break;

  case 91: /* function_decl: decorator_list TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 509 "src/parser/parser.y"
                                                                                                                                         {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        (yyval.node)->function.decorators = (yyvsp[-9].node_list);
    }
#line 2964 "parser.c"
    break;

  case 92: /* function_decl: decorator_list TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 513 "src/parser/parser.y"
                                                                                                                                                   {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        (yyval.node)->function.decorators = (yyvsp[-10].node_list);
    }
#line 2973 "parser.c"
    break;

  case 93: /* param_list: %empty  */
#line 520 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2981 "parser.c"
    break;

  case 94: /* param_list: param  */
#line 523 "src/parser/parser.y"
            {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2990 "parser.c"
    break;

  case 95: /* param_list: param_list TOKEN_COMMA param  */
#line 527 "src/parser/parser.y"
                                   {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2999 "parser.c"
    break;

  case 96: /* param: TOKEN_IDENTIFIER  */
#line 537 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[0].string), NULL, NULL); }
#line 3005 "parser.c"
    break;

  case 97: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 539 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[-2].string), (yyvsp[0].node), NULL); }
#line 3011 "parser.c"
    break;

  case 98: /* param: TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 541 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[-2].string), NULL, (yyvsp[0].node)); }
#line 3017 "parser.c"
    break;

  case 99: /* param: TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 543 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3023 "parser.c"
    break;

  case 100: /* type: TOKEN_IDENTIFIER  */
#line 548 "src/parser/parser.y"
                     {
        (yyval.node) = create_type_node((yyvsp[0].string));
    }
#line 3031 "parser.c"
    break;

  case 101: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
#line 551 "src/parser/parser.y"
                                      {
        (yyval.node) = create_optional_type_node((yyvsp[-1].string));
    }
#line 3039 "parser.c"
    break;

  case 102: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 554 "src/parser/parser.y"
                                         {
        (yyval.node) = create_array_type_node((yyvsp[0].node));
    }
#line 3047 "parser.c"
    break;

  case 103: /* dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 562 "src/parser/parser.y"
                                                      { (yyval.node) = create_dict_node((yyvsp[-1].node_list)); }
#line 3053 "parser.c"
    break;

  case 104: /* dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 563 "src/parser/parser.y"
                                                       { (yyval.node) = create_dict_node((yyvsp[-1].node_list)); }
#line 3059 "parser.c"
    break;

  case 105: /* dict_expr: TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 564 "src/parser/parser.y"
                                             { (yyval.node) = create_dict_node((yyvsp[-1].node_list)); }
#line 3065 "parser.c"
    break;

  case 106: /* dict_entries: %empty  */
#line 568 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3073 "parser.c"
    break;

  case 107: /* dict_entries: dict_entry_list  */
#line 571 "src/parser/parser.y"
                      {
        (yyval.node_list) = (yyvsp[0].node_list);
    }
#line 3081 "parser.c"
    break;

  case 108: /* dict_entry_list: expression TOKEN_FAT_ARROW expression  */
#line 577 "src/parser/parser.y"
                                          {
        (yyval.node_list) = create_node_list();
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyval.node_list), pair);
    }
#line 3091 "parser.c"
    break;

  case 109: /* dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression  */
#line 582 "src/parser/parser.y"
                                                                        {
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyvsp[-4].node_list), pair);
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 3101 "parser.c"
    break;

  case 110: /* bracket_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 592 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 3109 "parser.c"
    break;

  case 111: /* return_type: %empty  */
#line 608 "src/parser/parser.y"
                {
        (yyval.node) = NULL;
    }
#line 3117 "parser.c"
    break;

  case 112: /* return_type: TOKEN_COLON type  */
#line 611 "src/parser/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3125 "parser.c"
    break;

  case 113: /* return_type: TOKEN_ARROW primary_expr  */
#line 614 "src/parser/parser.y"
                               {
        // Pour les retours directs: -> expr
        (yyval.node) = create_return_direct_node((yyvsp[0].node));
    }
#line 3134 "parser.c"
    break;

  case 114: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 621 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 3142 "parser.c"
    break;

  case 115: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 624 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_let_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3150 "parser.c"
    break;

  case 116: /* let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 627 "src/parser/parser.y"
                                                                   {
        ASTNode* node = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 3160 "parser.c"
    break;

  case 117: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 633 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_muts_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 3168 "parser.c"
    break;

  case 118: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 636 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_muts_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3176 "parser.c"
    break;

  case 119: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 641 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 3184 "parser.c"
    break;

  case 120: /* const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 644 "src/parser/parser.y"
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 3195 "parser.c"
    break;

  case 121: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 653 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-1].node_list), NULL);
    }
#line 3203 "parser.c"
    break;

  case 122: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 656 "src/parser/parser.y"
                                                                                                                       {
        (yyval.node) = create_if_node((yyvsp[-7].node), (yyvsp[-5].node_list), (yyvsp[-1].node_list));
    }
#line 3211 "parser.c"
    break;

  case 123: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE if_statement  */
#line 659 "src/parser/parser.y"
                                                                                           {
        // else if -> le else contient un autre if
        ASTNodeList* else_branch = create_node_list();
        add_to_node_list(else_branch, (yyvsp[0].node));
        (yyval.node) = create_if_node((yyvsp[-5].node), (yyvsp[-3].node_list), else_branch);
    }
#line 3222 "parser.c"
    break;

  case 124: /* break_statement: TOKEN_BREAK  */
#line 667 "src/parser/parser.y"
                {
        (yyval.node) = create_break_node();
    }
#line 3230 "parser.c"
    break;

  case 125: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 672 "src/parser/parser.y"
                                                                                                                                                      {
        ASTNode* init = create_let_node((yyvsp[-9].string), NULL, (yyvsp[-7].node));
        ASTNode* cond = (yyvsp[-5].node);
        ASTNode* inc = create_expr_statement((yyvsp[-3].node));
        (yyval.node) = create_for_node(init, cond, inc, (yyvsp[-1].node_list));
    }
#line 3241 "parser.c"
    break;

  case 126: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 678 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3249 "parser.c"
    break;

  case 127: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 681 "src/parser/parser.y"
                                                                                              {
        // for x in array { ... }
        ASTNode* array_expr = (yyvsp[-3].node);
        ASTNodeList* body = (yyvsp[-1].node_list);
        
        // Créer un nœud spécial pour for-in
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_FOR_IN;
        node->for_in.var = strdup((yyvsp[-5].string));
        node->for_in.collection = array_expr;
        node->for_in.body = body;
        (yyval.node) = node;
    }
#line 3267 "parser.c"
    break;

  case 128: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 694 "src/parser/parser.y"
                                                                                                                     {
        // for i in 0..10 { ... }
        ASTNode* start = (yyvsp[-5].node);
        ASTNode* end = (yyvsp[-3].node);
        ASTNodeList* body = (yyvsp[-1].node_list);
        
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_FOR_RANGE;
        node->for_range.var = strdup((yyvsp[-7].string));
        node->for_range.start = start;
        node->for_range.end = end;
        node->for_range.body = body;
        node->for_range.inclusive = 0;
        (yyval.node) = node;
    }
#line 3287 "parser.c"
    break;

  case 129: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE_INC expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 709 "src/parser/parser.y"
                                                                                                                         {
        // for i in 0..=10 { ... } (inclusif)
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_FOR_RANGE;
        node->for_range.var = strdup((yyvsp[-7].string));
        node->for_range.start = (yyvsp[-5].node);
        node->for_range.end = (yyvsp[-3].node);
        node->for_range.body = (yyvsp[-1].node_list);
        node->for_range.inclusive = 1;
        (yyval.node) = node;
    }
#line 3303 "parser.c"
    break;

  case 130: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 724 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3311 "parser.c"
    break;

  case 131: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 730 "src/parser/parser.y"
                                                        {
        (yyval.node) = create_loop_node((yyvsp[-1].node_list));
    }
#line 3319 "parser.c"
    break;

  case 132: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 737 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3327 "parser.c"
    break;

  case 133: /* match_cases: match_case  */
#line 743 "src/parser/parser.y"
               {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3336 "parser.c"
    break;

  case 134: /* match_cases: match_cases match_case  */
#line 747 "src/parser/parser.y"
                             {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3345 "parser.c"
    break;

  case 135: /* match_case: pattern TOKEN_FAT_ARROW expression  */
#line 754 "src/parser/parser.y"
                                       {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3353 "parser.c"
    break;

  case 136: /* match_case: pattern TOKEN_FAT_ARROW block  */
#line 757 "src/parser/parser.y"
                                    {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (ASTNode*)(yyvsp[0].node));
    }
#line 3361 "parser.c"
    break;

  case 137: /* pattern: TOKEN_NUMBER  */
#line 763 "src/parser/parser.y"
                 { (yyval.node) = create_pattern_number((yyvsp[0].number)); }
#line 3367 "parser.c"
    break;

  case 138: /* pattern: TOKEN_STRING  */
#line 764 "src/parser/parser.y"
                   { (yyval.node) = create_pattern_string((yyvsp[0].string)); }
#line 3373 "parser.c"
    break;

  case 139: /* pattern: TOKEN_IDENTIFIER  */
#line 765 "src/parser/parser.y"
                       { (yyval.node) = create_pattern_ident((yyvsp[0].string)); }
#line 3379 "parser.c"
    break;

  case 140: /* pattern: TOKEN_UNDERSCORE  */
#line 766 "src/parser/parser.y"
                       { (yyval.node) = create_pattern_wildcard(); }
#line 3385 "parser.c"
    break;

  case 141: /* pattern: TOKEN_LBRACKET array_patterns TOKEN_RBRACKET  */
#line 767 "src/parser/parser.y"
                                                   { (yyval.node) = create_pattern_array((yyvsp[-1].node_list)); }
#line 3391 "parser.c"
    break;

  case 142: /* pattern: TOKEN_LET TOKEN_IDENTIFIER  */
#line 768 "src/parser/parser.y"
                                 { (yyval.node) = create_pattern_binding((yyvsp[0].string)); }
#line 3397 "parser.c"
    break;

  case 143: /* array_patterns: %empty  */
#line 772 "src/parser/parser.y"
                { (yyval.node_list) = NULL; }
#line 3403 "parser.c"
    break;

  case 144: /* array_patterns: pattern  */
#line 773 "src/parser/parser.y"
              { (yyval.node_list) = create_node_list(); add_to_node_list((yyval.node_list), (yyvsp[0].node)); }
#line 3409 "parser.c"
    break;

  case 145: /* array_patterns: array_patterns TOKEN_COMMA pattern  */
#line 774 "src/parser/parser.y"
                                         { add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node)); (yyval.node_list) = (yyvsp[-2].node_list); }
#line 3415 "parser.c"
    break;

  case 146: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 779 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_struct_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3423 "parser.c"
    break;

  case 147: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 782 "src/parser/parser.y"
                                                                                                           {
        (yyval.node) = create_struct_extend_node((yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3431 "parser.c"
    break;

  case 148: /* struct_fields: %empty  */
#line 788 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3439 "parser.c"
    break;

  case 149: /* struct_fields: struct_field  */
#line 791 "src/parser/parser.y"
                   {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3448 "parser.c"
    break;

  case 150: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
#line 795 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3457 "parser.c"
    break;

  case 151: /* struct_fields: struct_fields struct_field  */
#line 799 "src/parser/parser.y"
                                 {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3466 "parser.c"
    break;

  case 152: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 806 "src/parser/parser.y"
                                      {
        (yyval.node) = create_field_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 3474 "parser.c"
    break;

  case 153: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
#line 812 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_enum_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3482 "parser.c"
    break;

  case 154: /* enum_variants: %empty  */
#line 818 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3490 "parser.c"
    break;

  case 155: /* enum_variants: TOKEN_IDENTIFIER  */
#line 821 "src/parser/parser.y"
                       {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 3499 "parser.c"
    break;

  case 156: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 825 "src/parser/parser.y"
                                                 {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3508 "parser.c"
    break;

  case 157: /* module_decl: TOKEN_MODULE TOKEN_IDENTIFIER  */
#line 832 "src/parser/parser.y"
                                  {
        // Créer un nœud nil pour éviter l'erreur
        (yyval.node) = create_expr_statement(create_nil_node());
    }
#line 3517 "parser.c"
    break;

  case 158: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
#line 839 "src/parser/parser.y"
                                                                             {
        (yyval.node) = create_impl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3525 "parser.c"
    break;

  case 159: /* function_decl_list: %empty  */
#line 845 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3533 "parser.c"
    break;

  case 160: /* function_decl_list: function_decl  */
#line 848 "src/parser/parser.y"
                    {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3542 "parser.c"
    break;

  case 161: /* function_decl_list: function_decl_list function_decl  */
#line 852 "src/parser/parser.y"
                                       {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3551 "parser.c"
    break;

  case 162: /* return_statement: TOKEN_RETURN expression  */
#line 859 "src/parser/parser.y"
                            {
        (yyval.node) = create_return_node((yyvsp[0].node));
    }
#line 3559 "parser.c"
    break;

  case 163: /* return_statement: TOKEN_RETURN  */
#line 862 "src/parser/parser.y"
                   {
        (yyval.node) = create_return_node(NULL);
    }
#line 3567 "parser.c"
    break;

  case 168: /* expression: expression TOKEN_DOT TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 872 "src/parser/parser.y"
                                                                                    {
        // 'expression' est l'objet ($1), 'TOKEN_IDENTIFIER' est la méthode ($3)
        // 'argument_list' est la liste des arguments ($5)
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3577 "parser.c"
    break;

  case 169: /* binary_expr: expression TOKEN_PLUS expression  */
#line 880 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_ADD, (yyvsp[0].node));
    }
#line 3585 "parser.c"
    break;

  case 170: /* binary_expr: expression TOKEN_MINUS expression  */
#line 883 "src/parser/parser.y"
                                        {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_SUB, (yyvsp[0].node));
    }
#line 3593 "parser.c"
    break;

  case 171: /* binary_expr: expression TOKEN_MULTIPLY expression  */
#line 886 "src/parser/parser.y"
                                           {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
    }
#line 3601 "parser.c"
    break;

  case 172: /* binary_expr: expression TOKEN_DIVIDE expression  */
#line 889 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
    }
#line 3609 "parser.c"
    break;

  case 173: /* binary_expr: expression TOKEN_MODULO expression  */
#line 892 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
    }
#line 3617 "parser.c"
    break;

  case 174: /* binary_expr: expression TOKEN_EQ expression  */
#line 895 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_EQ, (yyvsp[0].node));
    }
#line 3625 "parser.c"
    break;

  case 175: /* binary_expr: expression TOKEN_NEQ expression  */
#line 898 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_NEQ, (yyvsp[0].node));
    }
#line 3633 "parser.c"
    break;

  case 176: /* binary_expr: expression TOKEN_LT expression  */
#line 901 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
    }
#line 3641 "parser.c"
    break;

  case 177: /* binary_expr: expression TOKEN_LTE expression  */
#line 904 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LTE, (yyvsp[0].node));
    }
#line 3649 "parser.c"
    break;

  case 178: /* binary_expr: expression TOKEN_GT expression  */
#line 907 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
    }
#line 3657 "parser.c"
    break;

  case 179: /* binary_expr: expression TOKEN_GTE expression  */
#line 910 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GTE, (yyvsp[0].node));
    }
#line 3665 "parser.c"
    break;

  case 180: /* binary_expr: expression TOKEN_AND expression  */
#line 913 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_AND, (yyvsp[0].node));
    }
#line 3673 "parser.c"
    break;

  case 181: /* binary_expr: expression TOKEN_OR expression  */
#line 916 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_OR, (yyvsp[0].node));
    }
#line 3681 "parser.c"
    break;

  case 182: /* binary_expr: expression TOKEN_ASSIGN expression  */
#line 919 "src/parser/parser.y"
                                         {
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3689 "parser.c"
    break;

  case 183: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
#line 922 "src/parser/parser.y"
                                              {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_ADD_ASSIGN, (yyvsp[0].node));
    }
#line 3697 "parser.c"
    break;

  case 184: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
#line 925 "src/parser/parser.y"
                                               {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_SUB_ASSIGN, (yyvsp[0].node));
    }
#line 3705 "parser.c"
    break;

  case 185: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
#line 928 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MUL_ASSIGN, (yyvsp[0].node));
    }
#line 3713 "parser.c"
    break;

  case 186: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
#line 931 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_DIV_ASSIGN, (yyvsp[0].node));
    }
#line 3721 "parser.c"
    break;

  case 187: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
#line 934 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MOD_ASSIGN, (yyvsp[0].node));
    }
#line 3729 "parser.c"
    break;

  case 188: /* unary_expr: TOKEN_NOT expression  */
#line 940 "src/parser/parser.y"
                         {
        (yyval.node) = create_unary_op(OP_NOT, (yyvsp[0].node));
    }
#line 3737 "parser.c"
    break;

  case 189: /* unary_expr: TOKEN_MINUS expression  */
#line 943 "src/parser/parser.y"
                             {
        (yyval.node) = create_unary_op(OP_NEG, (yyvsp[0].node));
    }
#line 3745 "parser.c"
    break;

  case 190: /* lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 950 "src/parser/parser.y"
                                                                     {
        (yyval.node) = create_lambda_node((yyvsp[-3].node_list), (yyvsp[-1].node_list));
    }
#line 3753 "parser.c"
    break;

  case 191: /* lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 953 "src/parser/parser.y"
                                                                                                 {
        (yyval.node) = create_lambda_node((yyvsp[-4].node_list), (yyvsp[-1].node_list));
    }
#line 3761 "parser.c"
    break;

  case 192: /* primary_expr: TOKEN_NUMBER  */
#line 962 "src/parser/parser.y"
                 {
        (yyval.node) = create_number_node((yyvsp[0].number));
    }
#line 3769 "parser.c"
    break;

  case 193: /* primary_expr: TOKEN_FLOAT  */
#line 965 "src/parser/parser.y"
                  {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 3777 "parser.c"
    break;

  case 194: /* primary_expr: TOKEN_STRING  */
#line 968 "src/parser/parser.y"
                   {
        (yyval.node) = create_string_node((yyvsp[0].string));
    }
#line 3785 "parser.c"
    break;

  case 195: /* primary_expr: TOKEN_TRUE  */
#line 971 "src/parser/parser.y"
                 {
        (yyval.node) = create_bool_node(1);
    }
#line 3793 "parser.c"
    break;

  case 196: /* primary_expr: TOKEN_FALSE  */
#line 974 "src/parser/parser.y"
                  {
        (yyval.node) = create_bool_node(0);
    }
#line 3801 "parser.c"
    break;

  case 197: /* primary_expr: TOKEN_NIL  */
#line 977 "src/parser/parser.y"
                {
        (yyval.node) = create_nil_node();
    }
#line 3809 "parser.c"
    break;

  case 198: /* primary_expr: TOKEN_IDENTIFIER  */
#line 980 "src/parser/parser.y"
                       {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 3817 "parser.c"
    break;

  case 199: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 983 "src/parser/parser.y"
                                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3825 "parser.c"
    break;

  case 212: /* f_string: TOKEN_F_STRING  */
#line 1001 "src/parser/parser.y"
                   {
        (yyval.node) = parse_f_string((yyvsp[0].string));
    }
#line 3833 "parser.c"
    break;

  case 213: /* member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER  */
#line 1007 "src/parser/parser.y"
                                            {
        (yyval.node) = create_member_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3841 "parser.c"
    break;

  case 214: /* member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 1010 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_static_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3849 "parser.c"
    break;

  case 215: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 1016 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_call_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3857 "parser.c"
    break;

  case 216: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 1019 "src/parser/parser.y"
                                                                                               {
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3865 "parser.c"
    break;

  case 217: /* argument_list: %empty  */
#line 1025 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3873 "parser.c"
    break;

  case 218: /* argument_list: expression  */
#line 1028 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_arg_list();
        add_arg((yyval.node_list), (yyvsp[0].node));
    }
#line 3882 "parser.c"
    break;

  case 219: /* argument_list: argument_list TOKEN_COMMA expression  */
#line 1032 "src/parser/parser.y"
                                           {
        add_arg((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3891 "parser.c"
    break;

  case 220: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
#line 1039 "src/parser/parser.y"
                                              {
        (yyval.node) = create_array_node((yyvsp[-1].node_list));
    }
#line 3899 "parser.c"
    break;

  case 221: /* await_expr: TOKEN_AWAIT primary_expr  */
#line 1054 "src/parser/parser.y"
                             {
        (yyval.node) = create_await_node((yyvsp[0].node));
    }
#line 3907 "parser.c"
    break;

  case 222: /* await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 1057 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_await_block_node((yyvsp[-1].node_list));
    }
#line 3915 "parser.c"
    break;

  case 223: /* spawn_expr: TOKEN_SPAWN primary_expr  */
#line 1064 "src/parser/parser.y"
                             {
        (yyval.node) = create_spawn_node((yyvsp[0].node));
    }
#line 3923 "parser.c"
    break;

  case 224: /* array_items: %empty  */
#line 1076 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3931 "parser.c"
    break;

  case 225: /* array_items: expression  */
#line 1079 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3940 "parser.c"
    break;

  case 226: /* array_items: array_items TOKEN_COMMA expression  */
#line 1083 "src/parser/parser.y"
                                         {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3949 "parser.c"
    break;

  case 227: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
#line 1090 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_struct_init_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3957 "parser.c"
    break;

  case 228: /* struct_init_fields: %empty  */
#line 1096 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3965 "parser.c"
    break;

  case 229: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 1099 "src/parser/parser.y"
                                              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
    }
#line 3974 "parser.c"
    break;

  case 230: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 1103 "src/parser/parser.y"
                                                                             {
        add_to_node_list((yyvsp[-4].node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 3983 "parser.c"
    break;

  case 231: /* block: TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 1110 "src/parser/parser.y"
                                             {
        (yyval.node) = (ASTNode*)(yyvsp[-1].node_list);
    }
#line 3991 "parser.c"
    break;


#line 3995 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1115 "src/parser/parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

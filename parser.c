/* A Bison parser, made by GNU Bison 3.7.6.  */

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
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

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
  YYSYMBOL_TOKEN_PLUS = 48,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 49,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MULTIPLY = 50,            /* TOKEN_MULTIPLY  */
  YYSYMBOL_TOKEN_DIVIDE = 51,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 52,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_ASSIGN = 53,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 54,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 55,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 56,     /* TOKEN_MULTIPLY_ASSIGN  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 57,       /* TOKEN_DIVIDE_ASSIGN  */
  YYSYMBOL_TOKEN_MODULO_ASSIGN = 58,       /* TOKEN_MODULO_ASSIGN  */
  YYSYMBOL_TOKEN_EQ = 59,                  /* TOKEN_EQ  */
  YYSYMBOL_TOKEN_NEQ = 60,                 /* TOKEN_NEQ  */
  YYSYMBOL_TOKEN_LT = 61,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LTE = 62,                 /* TOKEN_LTE  */
  YYSYMBOL_TOKEN_GT = 63,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GTE = 64,                 /* TOKEN_GTE  */
  YYSYMBOL_TOKEN_AND = 65,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 66,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_NOT = 67,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_AMP = 68,                 /* TOKEN_AMP  */
  YYSYMBOL_TOKEN_PIPE = 69,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_XOR = 70,                 /* TOKEN_XOR  */
  YYSYMBOL_TOKEN_LSHIFT = 71,              /* TOKEN_LSHIFT  */
  YYSYMBOL_TOKEN_RSHIFT = 72,              /* TOKEN_RSHIFT  */
  YYSYMBOL_TOKEN_DOUBLE_COLON = 73,        /* TOKEN_DOUBLE_COLON  */
  YYSYMBOL_TOKEN_DOT = 74,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_SECURITY = 75,            /* TOKEN_SECURITY  */
  YYSYMBOL_TOKEN_COLON = 76,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_SEMICOLON = 77,           /* TOKEN_SEMICOLON  */
  YYSYMBOL_TOKEN_COMMA = 78,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_ARROW = 79,               /* TOKEN_ARROW  */
  YYSYMBOL_TOKEN_FAT_ARROW = 80,           /* TOKEN_FAT_ARROW  */
  YYSYMBOL_TOKEN_PIPE_FORWARD = 81,        /* TOKEN_PIPE_FORWARD  */
  YYSYMBOL_TOKEN_OPTIONAL = 82,            /* TOKEN_OPTIONAL  */
  YYSYMBOL_TOKEN_COALESCE = 83,            /* TOKEN_COALESCE  */
  YYSYMBOL_TOKEN_RANGE = 84,               /* TOKEN_RANGE  */
  YYSYMBOL_TOKEN_RANGE_INC = 85,           /* TOKEN_RANGE_INC  */
  YYSYMBOL_TOKEN_MUTS = 86,                /* TOKEN_MUTS  */
  YYSYMBOL_TOKEN_SYSF = 87,                /* TOKEN_SYSF  */
  YYSYMBOL_TOKEN_SH = 88,                  /* TOKEN_SH  */
  YYSYMBOL_TOKEN_LPAREN = 89,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 90,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_LBRACE = 91,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 92,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_LBRACKET = 93,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 94,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_TRY = 95,                 /* TOKEN_TRY  */
  YYSYMBOL_TOKEN_CATCH = 96,               /* TOKEN_CATCH  */
  YYSYMBOL_TOKEN_FINALLY = 97,             /* TOKEN_FINALLY  */
  YYSYMBOL_TOKEN_THROW = 98,               /* TOKEN_THROW  */
  YYSYMBOL_TOKEN_EXCEPT = 99,              /* TOKEN_EXCEPT  */
  YYSYMBOL_TOKEN_RAISE = 100,              /* TOKEN_RAISE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 101,         /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_NUMBER = 102,             /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_FLOAT = 103,              /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_STRING = 104,             /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_F_STRING = 105,           /* TOKEN_F_STRING  */
  YYSYMBOL_YYACCEPT = 106,                 /* $accept  */
  YYSYMBOL_switch_statement = 107,         /* switch_statement  */
  YYSYMBOL_program = 108,                  /* program  */
  YYSYMBOL_statement_list = 109,           /* statement_list  */
  YYSYMBOL_unsafe_stmt = 110,              /* unsafe_stmt  */
  YYSYMBOL_continue_statement = 111,       /* continue_statement  */
  YYSYMBOL_statement = 112,                /* statement  */
  YYSYMBOL_sysf_expr = 113,                /* sysf_expr  */
  YYSYMBOL_use_statement = 114,            /* use_statement  */
  YYSYMBOL_use_path = 115,                 /* use_path  */
  YYSYMBOL_sh_expr = 116,                  /* sh_expr  */
  YYSYMBOL_nnl_statement = 117,            /* nnl_statement  */
  YYSYMBOL_try_statement = 118,            /* try_statement  */
  YYSYMBOL_catch_block = 119,              /* catch_block  */
  YYSYMBOL_finally_block = 120,            /* finally_block  */
  YYSYMBOL_throw_statement = 121,          /* throw_statement  */
  YYSYMBOL_jmp_statement = 122,            /* jmp_statement  */
  YYSYMBOL_import_statement = 123,         /* import_statement  */
  YYSYMBOL_import_path_tail = 124,         /* import_path_tail  */
  YYSYMBOL_import_path = 125,              /* import_path  */
  YYSYMBOL_import_constraints = 126,       /* import_constraints  */
  YYSYMBOL_import_options = 127,           /* import_options  */
  YYSYMBOL_name_list = 128,                /* name_list  */
  YYSYMBOL_export_statement = 129,         /* export_statement  */
  YYSYMBOL_packet_decl = 130,              /* packet_decl  */
  YYSYMBOL_function_decl = 131,            /* function_decl  */
  YYSYMBOL_param_list = 132,               /* param_list  */
  YYSYMBOL_param = 133,                    /* param  */
  YYSYMBOL_type = 134,                     /* type  */
  YYSYMBOL_dict_expr = 135,                /* dict_expr  */
  YYSYMBOL_dict_entries = 136,             /* dict_entries  */
  YYSYMBOL_dict_entry_list = 137,          /* dict_entry_list  */
  YYSYMBOL_dict_access = 138,              /* dict_access  */
  YYSYMBOL_return_type = 139,              /* return_type  */
  YYSYMBOL_let_decl = 140,                 /* let_decl  */
  YYSYMBOL_const_decl = 141,               /* const_decl  */
  YYSYMBOL_if_statement = 142,             /* if_statement  */
  YYSYMBOL_break_statement = 143,          /* break_statement  */
  YYSYMBOL_for_statement = 144,            /* for_statement  */
  YYSYMBOL_while_statement = 145,          /* while_statement  */
  YYSYMBOL_loop_statement = 146,           /* loop_statement  */
  YYSYMBOL_match_statement = 147,          /* match_statement  */
  YYSYMBOL_match_cases = 148,              /* match_cases  */
  YYSYMBOL_match_case = 149,               /* match_case  */
  YYSYMBOL_pattern = 150,                  /* pattern  */
  YYSYMBOL_array_patterns = 151,           /* array_patterns  */
  YYSYMBOL_struct_decl = 152,              /* struct_decl  */
  YYSYMBOL_struct_fields = 153,            /* struct_fields  */
  YYSYMBOL_struct_field = 154,             /* struct_field  */
  YYSYMBOL_enum_decl = 155,                /* enum_decl  */
  YYSYMBOL_enum_variants = 156,            /* enum_variants  */
  YYSYMBOL_module_decl = 157,              /* module_decl  */
  YYSYMBOL_impl_decl = 158,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 159,       /* function_decl_list  */
  YYSYMBOL_return_statement = 160,         /* return_statement  */
  YYSYMBOL_expression = 161,               /* expression  */
  YYSYMBOL_binary_expr = 162,              /* binary_expr  */
  YYSYMBOL_unary_expr = 163,               /* unary_expr  */
  YYSYMBOL_lambda_expr = 164,              /* lambda_expr  */
  YYSYMBOL_array_access = 165,             /* array_access  */
  YYSYMBOL_primary_expr = 166,             /* primary_expr  */
  YYSYMBOL_f_string = 167,                 /* f_string  */
  YYSYMBOL_member_access = 168,            /* member_access  */
  YYSYMBOL_call_expr = 169,                /* call_expr  */
  YYSYMBOL_argument_list = 170,            /* argument_list  */
  YYSYMBOL_array_expr = 171,               /* array_expr  */
  YYSYMBOL_await_expr = 172,               /* await_expr  */
  YYSYMBOL_spawn_expr = 173,               /* spawn_expr  */
  YYSYMBOL_array_items = 174,              /* array_items  */
  YYSYMBOL_struct_expr = 175,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 176,       /* struct_init_fields  */
  YYSYMBOL_block = 177                     /* block  */
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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  150
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3893

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  210
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  471

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   360


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
     105
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   120,   120,   132,   138,   142,   148,   153,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   190,   193,   200,   204,   208,   216,
     219,   228,   231,   237,   243,   246,   252,   255,   261,   267,
     270,   275,   278,   287,   291,   295,   299,   306,   309,   318,
     321,   327,   336,   342,   345,   351,   355,   362,   368,   374,
     377,   380,   386,   393,   402,   405,   409,   416,   419,   425,
     428,   431,   439,   442,   448,   451,   457,   462,   471,   490,
     493,   496,   503,   506,   509,   515,   518,   523,   526,   535,
     538,   541,   549,   554,   560,   563,   576,   591,   606,   612,
     619,   625,   629,   636,   639,   645,   646,   647,   648,   649,
     650,   654,   655,   656,   661,   664,   670,   673,   677,   681,
     688,   694,   700,   703,   707,   714,   721,   727,   730,   734,
     741,   744,   750,   751,   752,   753,   761,   764,   767,   770,
     773,   776,   779,   782,   785,   788,   791,   794,   797,   800,
     803,   806,   809,   812,   815,   821,   824,   831,   834,   841,
     847,   850,   853,   856,   859,   862,   865,   868,   871,   872,
     873,   874,   875,   876,   877,   878,   879,   880,   881,   882,
     883,   887,   893,   896,   902,   905,   911,   914,   918,   925,
     940,   943,   950,   962,   965,   969,   976,   982,   985,   989,
     996
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
  "TOKEN_UNDERSCORE", "TOKEN_SWITCH", "TOKEN_USE", "TOKEN_PLUS",
  "TOKEN_MINUS", "TOKEN_MULTIPLY", "TOKEN_DIVIDE", "TOKEN_MODULO",
  "TOKEN_ASSIGN", "TOKEN_PLUS_ASSIGN", "TOKEN_MINUS_ASSIGN",
  "TOKEN_MULTIPLY_ASSIGN", "TOKEN_DIVIDE_ASSIGN", "TOKEN_MODULO_ASSIGN",
  "TOKEN_EQ", "TOKEN_NEQ", "TOKEN_LT", "TOKEN_LTE", "TOKEN_GT",
  "TOKEN_GTE", "TOKEN_AND", "TOKEN_OR", "TOKEN_NOT", "TOKEN_AMP",
  "TOKEN_PIPE", "TOKEN_XOR", "TOKEN_LSHIFT", "TOKEN_RSHIFT",
  "TOKEN_DOUBLE_COLON", "TOKEN_DOT", "TOKEN_SECURITY", "TOKEN_COLON",
  "TOKEN_SEMICOLON", "TOKEN_COMMA", "TOKEN_ARROW", "TOKEN_FAT_ARROW",
  "TOKEN_PIPE_FORWARD", "TOKEN_OPTIONAL", "TOKEN_COALESCE", "TOKEN_RANGE",
  "TOKEN_RANGE_INC", "TOKEN_MUTS", "TOKEN_SYSF", "TOKEN_SH",
  "TOKEN_LPAREN", "TOKEN_RPAREN", "TOKEN_LBRACE", "TOKEN_RBRACE",
  "TOKEN_LBRACKET", "TOKEN_RBRACKET", "TOKEN_TRY", "TOKEN_CATCH",
  "TOKEN_FINALLY", "TOKEN_THROW", "TOKEN_EXCEPT", "TOKEN_RAISE",
  "TOKEN_IDENTIFIER", "TOKEN_NUMBER", "TOKEN_FLOAT", "TOKEN_STRING",
  "TOKEN_F_STRING", "$accept", "switch_statement", "program",
  "statement_list", "unsafe_stmt", "continue_statement", "statement",
  "sysf_expr", "use_statement", "use_path", "sh_expr", "nnl_statement",
  "try_statement", "catch_block", "finally_block", "throw_statement",
  "jmp_statement", "import_statement", "import_path_tail", "import_path",
  "import_constraints", "import_options", "name_list", "export_statement",
  "packet_decl", "function_decl", "param_list", "param", "type",
  "dict_expr", "dict_entries", "dict_entry_list", "dict_access",
  "return_type", "let_decl", "const_decl", "if_statement",
  "break_statement", "for_statement", "while_statement", "loop_statement",
  "match_statement", "match_cases", "match_case", "pattern",
  "array_patterns", "struct_decl", "struct_fields", "struct_field",
  "enum_decl", "enum_variants", "module_decl", "impl_decl",
  "function_decl_list", "return_statement", "expression", "binary_expr",
  "unary_expr", "lambda_expr", "array_access", "primary_expr", "f_string",
  "member_access", "call_expr", "argument_list", "array_expr",
  "await_expr", "spawn_expr", "array_items", "struct_expr",
  "struct_init_fields", "block", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360
};
#endif

#define YYPACT_NINF (-354)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2929,   -71,   -40,   -35,    25,    32,   323,   323,  2995,   323,
      53,  -354,  -354,    -4,    64,    82,    84,   100,   111,   323,
    -354,  -354,  -354,    18,   115,   145,   129,   142,   155,    79,
    2962,  3110,   -20,   323,   161,   323,   323,   165,  3044,  3077,
     323,   323,   199,   323,   323,  -354,  -354,  -354,  -354,  -354,
    -354,   246,  2929,  -354,  -354,  -354,  -354,  -354,  -354,  -354,
    -354,  -354,  -354,  -354,  -354,  -354,  -354,  -354,  -354,  -354,
    -354,  -354,  -354,  -354,  -354,  -354,  -354,  -354,  -354,  -354,
    -354,  -354,  3819,  -354,  -354,  -354,  -354,    99,  -354,  -354,
    -354,  -354,  -354,  -354,  -354,   323,   323,   206,   -17,   243,
    3819,  3212,     3,  3256,  3300,  2929,   197,   197,  -354,   230,
     -15,  -354,   214,   -26,   217,   221,  3344,   215,   222,   227,
     302,   229,  2929,   238,   323,  -354,   231,  2929,    99,    99,
     233,   254,    54,  -354,  3388,  -354,    -5,    -2,   257,   -12,
     323,  3819,   323,  3819,  3564,  3819,     4,  2929,  3819,  3819,
    -354,  -354,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   234,   235,   236,   323,   323,   247,   260,  3693,   248,
     233,   323,   134,   323,  2929,   323,   323,  2929,  2929,   457,
     230,   230,   240,   242,   308,  -354,  2929,   249,   255,   258,
      14,    85,   271,   309,   310,   266,   268,   560,  2929,  3819,
     281,   663,   103,   134,   233,  2929,    85,   270,    15,   323,
     134,  3607,  3650,  -354,   323,  -354,   766,    -2,    -2,   257,
     257,   257,  3819,  3819,  3819,  3819,  3819,  3819,   335,   335,
     251,   251,   251,   251,   190,   146,   284,   285,  -354,  3819,
     113,   219,  -354,   323,   323,  -354,   139,  3819,   283,   293,
     325,  3819,   869,  3168,  3759,   972,  1075,  -354,  -354,   288,
     304,   -21,  1178,   290,   306,    10,  -354,  -354,    16,    23,
    -354,    12,   287,  -354,    85,  -354,  -354,  -354,     8,  -354,
     311,   233,   323,   323,   300,   316,    92,  -354,  1281,   233,
    -354,   312,  -354,  -354,  1384,   122,  -354,   292,  -354,  3819,
     342,  -354,  -354,  3819,   164,   323,   323,   323,  -354,  -354,
    3726,  3819,   123,   134,  -354,   323,   390,   323,   323,  2929,
     323,  -354,  -354,  -354,   313,   308,  -354,  -354,   255,   134,
     255,  -354,  -354,   301,  -354,  -354,  -354,  -354,  -354,    27,
    -354,  -354,    36,   143,  3819,  3819,   233,   323,   303,  -354,
    -354,   144,  2929,  -354,  -354,  -354,    98,   323,   318,   324,
     317,   147,   154,  3819,   323,   134,  3110,   166,  -354,  3819,
       2,  3432,  3476,  1487,  3789,   292,   327,    21,  -354,  -354,
    -354,    85,  -354,  2929,  3819,  -354,   123,   216,  3819,   341,
     123,  1590,   319,  -354,  3819,   320,   322,   328,  -354,  -354,
    -354,  3819,  -354,    99,   323,  2929,  2929,  -354,  2929,  2929,
    -354,   323,    37,  -354,  -354,  1693,   343,   123,   323,   344,
    -354,  -354,   346,   347,  2929,  3819,  1796,  1899,  2002,  2105,
    3520,  -354,  -354,  2929,   348,  3819,  2929,   349,   350,  2208,
    -354,  -354,  -354,  -354,  2929,  2311,  2929,  2414,  2929,  2929,
    -354,  2517,  -354,  2620,  -354,  2723,  2826,  -354,  -354,  -354,
    -354
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,   141,     0,     0,     0,
       0,   102,     7,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    74,     0,     0,     0,     0,     0,     0,     0,
       0,   203,     0,     0,     0,   176,   170,   171,   172,   191,
      20,     0,     3,    28,    10,     4,   187,    17,   188,    11,
      14,    15,    12,     8,     9,    16,    18,   180,   179,    23,
      25,    26,    24,    27,    29,    30,    31,    19,    21,    13,
      22,    32,    33,   142,   143,   184,   185,   144,   190,   183,
     178,   181,   186,   189,   182,    84,    84,     0,     0,     0,
     140,     0,   176,     0,     0,     0,     0,     0,    57,    59,
      53,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,   135,     0,     0,   200,   202,
      74,    77,     0,    75,     0,    39,    36,   166,   165,     0,
       0,    35,     0,    42,     0,   204,     0,     0,    49,    50,
       1,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   196,     0,     0,    85,     0,     0,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,    61,     0,     0,     0,    55,     0,     0,   126,   132,
     137,     0,     0,     0,     0,     0,   207,     0,     0,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   177,     0,   199,     0,   146,   147,   148,
     149,   150,   159,   160,   161,   162,   163,   164,   151,   152,
     153,   154,   155,   156,   157,   158,     0,   193,   192,   197,
       0,     0,    82,     0,     0,    83,     0,    92,     0,    79,
       0,    97,     0,     0,     0,     0,     0,   109,    58,    54,
       0,     0,     0,     0,     0,     0,   127,   133,     0,     0,
     138,     0,     0,   118,   121,   117,   115,   116,     0,   111,
       0,    74,     0,     0,     0,     0,     0,     6,     0,    74,
     201,     0,    78,    76,     0,     0,    38,     0,    40,    95,
       0,    34,    41,   205,     0,   196,   196,     0,   194,    88,
       0,    86,    89,     0,    80,     0,    99,     0,     0,     0,
       0,   104,   108,    56,     0,     0,    62,    68,   126,     0,
       0,   124,   129,     0,   131,   136,   139,   120,   122,     0,
     110,   112,     0,     0,    94,    98,    74,     0,     0,   206,
      43,     0,     0,   167,     2,    65,     0,     0,     0,     0,
      44,     0,     0,   198,     0,     0,     0,     0,    81,    93,
       0,     0,     0,     0,     0,     0,    64,     0,   130,   128,
     134,     0,   119,     0,   113,   114,    89,     0,   208,     0,
      89,     0,     0,    37,    96,     0,     0,     0,    45,   145,
     195,    87,    90,    91,     0,     0,     0,   101,     0,     0,
     105,     0,     0,   125,   123,     0,     0,    89,     0,     0,
     168,    66,     0,     0,     0,    73,     0,     0,     0,     0,
       0,    63,   210,     0,     0,   209,     0,     0,     0,     0,
      69,   100,   106,   107,     0,     0,     0,     0,     0,     0,
      48,     0,    70,     0,    71,     0,     0,   103,    72,    46,
      47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -354,  -354,  -354,  -101,  -354,  -354,    -7,  -354,  -354,  -354,
    -354,  -354,  -354,  -354,  -354,  -354,  -354,  -354,   182,  -354,
     132,   108,    48,  -354,  -354,  -185,  -125,   224,  -204,  -354,
     351,  -354,  -354,  -353,  -354,  -354,    65,  -354,  -354,  -354,
    -354,  -354,   228,  -213,  -274,  -354,  -354,   114,  -267,  -354,
    -354,  -354,  -354,  -354,  -354,    -6,  -354,  -354,  -354,  -354,
     -24,  -354,  -354,  -354,  -173,  -354,  -354,  -354,  -354,  -354,
    -354,  -354
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    50,    51,    52,    53,    54,    55,    56,    57,   136,
      58,    59,    60,   370,   408,    61,    62,    63,   109,   110,
     195,   271,   366,    64,    65,    66,   132,   133,   260,    67,
     176,   177,    68,   377,    69,    70,    71,    72,    73,    74,
      75,    76,   288,   289,   290,   349,    77,   275,   276,    78,
     278,    79,    80,   281,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,   250,    91,    92,    93,   146,    94,
     296,   395
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     100,   101,   103,   104,   189,   212,   128,   129,   342,   302,
     348,     7,   193,   116,   282,   280,   310,     3,   197,     3,
      95,   207,   217,   117,   118,   119,   211,   134,   117,   137,
     138,   185,   141,   143,   144,   145,   181,   148,   149,     1,
       2,   219,   279,   426,   279,   151,   226,   429,   154,   155,
     156,    96,    29,   283,    29,   256,   186,   335,   120,   182,
      20,    21,    22,   120,   220,   198,    97,    24,   218,   130,
     106,   336,   171,   389,   444,   351,   194,    30,    31,    32,
     107,   131,   224,   262,   126,    35,   265,   266,   340,   178,
     178,   282,   351,   416,   343,   272,   346,   108,   225,   340,
     350,   284,   341,    36,   345,   391,   307,   298,   344,   285,
     286,   274,   287,   423,   304,   402,   308,   424,   209,   378,
     342,   392,   274,    38,    39,    40,    98,   393,   282,    41,
     283,   441,   214,    99,   221,   388,   222,    45,    46,    47,
      48,    49,   371,   372,   105,   215,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   111,   353,   283,   249,   251,
     358,   412,   172,   173,   361,   257,   402,   261,   284,   263,
     264,   214,   151,   112,   359,   113,   285,   286,   174,   287,
     403,   317,   175,   301,   152,   153,   154,   155,   156,   375,
     151,   114,   376,   318,   151,   163,   164,   165,   166,   167,
     168,   169,   115,   309,   364,   284,   121,   214,   313,   151,
     171,   214,   214,   285,   286,   317,   287,   258,   383,   322,
     123,   397,   317,   396,   400,   259,   122,   409,   152,   153,
     154,   155,   156,   124,   410,   414,   150,   320,   321,   163,
     164,   165,   166,   167,   168,   151,   125,   415,   151,   151,
     368,   401,   135,   369,   171,   151,   139,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   354,   355,   190,   191,
     147,   151,   425,   171,   214,   180,   183,   151,   108,   152,
     153,   154,   155,   156,   192,   196,   427,   205,   199,   249,
     249,   373,   200,   319,   436,   437,   202,   438,   439,   379,
     206,   381,   382,   203,   384,   171,     1,     2,   204,   208,
     213,   171,   210,   449,   131,   246,   247,   248,   253,   252,
     255,   268,   455,   269,   270,   457,   394,    20,    21,    22,
     273,   398,   413,   461,    24,   463,   274,   465,   466,   277,
     291,   404,   292,   293,    30,    31,    32,   294,   411,   295,
     299,   306,    35,   315,   316,   324,   151,   323,   325,   194,
     334,   338,   339,   152,   153,   154,   155,   156,   347,   356,
      36,   352,   357,   365,   151,   367,   165,   166,   167,   168,
     380,   333,   390,   362,   399,   335,   385,   405,   435,   171,
      38,    39,    40,   406,   407,   440,    41,   428,   151,   434,
     431,   432,   445,   433,    45,    46,    47,    48,    49,   151,
     151,   151,   151,   422,   443,   446,   447,   448,   303,   456,
     458,   459,   151,   386,   305,   417,     0,   179,   151,     0,
     151,     0,   387,     0,   151,     0,   151,     0,   151,   151,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,     0,     0,   267,
      41,     0,    42,     0,     0,    43,     0,    44,    45,    46,
      47,    48,    49,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,    33,    34,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    38,    39,    40,
       0,     0,   297,    41,     0,    42,     0,     0,    43,     0,
      44,    45,    46,    47,    48,    49,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,     0,     0,   300,    41,     0,    42,     0,
       0,    43,     0,    44,    45,    46,    47,    48,    49,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,    33,    34,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,     0,     0,   314,    41,
       0,    42,     0,     0,    43,     0,    44,    45,    46,    47,
      48,    49,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,     0,
       0,   326,    41,     0,    42,     0,     0,    43,     0,    44,
      45,    46,    47,    48,    49,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,    33,    34,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,     0,     0,   331,    41,     0,    42,     0,     0,
      43,     0,    44,    45,    46,    47,    48,    49,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    40,     0,     0,   332,    41,     0,
      42,     0,     0,    43,     0,    44,    45,    46,    47,    48,
      49,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,    33,    34,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    38,    39,    40,     0,     0,
     337,    41,     0,    42,     0,     0,    43,     0,    44,    45,
      46,    47,    48,    49,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,     0,     0,   360,    41,     0,    42,     0,     0,    43,
       0,    44,    45,    46,    47,    48,    49,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
      33,    34,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,     0,   363,    41,     0,    42,
       0,     0,    43,     0,    44,    45,    46,    47,    48,    49,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,     0,     0,   420,
      41,     0,    42,     0,     0,    43,     0,    44,    45,    46,
      47,    48,    49,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,    33,    34,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    38,    39,    40,
       0,     0,   430,    41,     0,    42,     0,     0,    43,     0,
      44,    45,    46,    47,    48,    49,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,     0,     0,   442,    41,     0,    42,     0,
       0,    43,     0,    44,    45,    46,    47,    48,    49,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,    33,    34,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,     0,     0,   450,    41,
       0,    42,     0,     0,    43,     0,    44,    45,    46,    47,
      48,    49,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,     0,
       0,   451,    41,     0,    42,     0,     0,    43,     0,    44,
      45,    46,    47,    48,    49,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,    33,    34,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,     0,     0,   452,    41,     0,    42,     0,     0,
      43,     0,    44,    45,    46,    47,    48,    49,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    40,     0,     0,   453,    41,     0,
      42,     0,     0,    43,     0,    44,    45,    46,    47,    48,
      49,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,    33,    34,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    38,    39,    40,     0,     0,
     460,    41,     0,    42,     0,     0,    43,     0,    44,    45,
      46,    47,    48,    49,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,     0,     0,   462,    41,     0,    42,     0,     0,    43,
       0,    44,    45,    46,    47,    48,    49,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
      33,    34,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,     0,   464,    41,     0,    42,
       0,     0,    43,     0,    44,    45,    46,    47,    48,    49,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,     0,     0,   467,
      41,     0,    42,     0,     0,    43,     0,    44,    45,    46,
      47,    48,    49,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,    33,    34,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    38,    39,    40,
       0,     0,   468,    41,     0,    42,     0,     0,    43,     0,
      44,    45,    46,    47,    48,    49,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,     0,     0,   469,    41,     0,    42,     0,
       0,    43,     0,    44,    45,    46,    47,    48,    49,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,    33,    34,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,     0,     0,   470,    41,
       0,    42,     0,     0,    43,     0,    44,    45,    46,    47,
      48,    49,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     1,     2,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,     0,    35,     0,
       0,     0,     0,     0,     0,     0,    20,    21,    22,     0,
       0,     0,     0,    24,     0,     0,    36,     0,     1,     2,
       0,     0,     0,    30,    31,    32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,    20,
      21,    22,    41,     0,    42,     0,    24,    43,     0,    44,
      45,    46,    47,    48,    49,     0,    30,    31,    32,     0,
       0,     0,     0,     0,    35,     0,     0,     1,     2,    38,
      39,    40,     0,   127,     0,    41,     0,     0,     0,     0,
       0,     0,    36,    45,    46,    47,    48,    49,    20,    21,
      22,     0,     0,     0,     0,    24,     0,     0,     0,     0,
       1,     2,    38,    39,    40,    30,    31,    32,    41,     0,
       0,     0,     0,    35,     0,     0,   102,    46,    47,    48,
      49,    20,    21,    22,     0,     0,     0,     0,    24,     0,
       0,    36,     0,     1,     2,     0,     0,     0,    30,    31,
      32,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,    38,    39,   140,    20,    21,    22,    41,     0,     0,
       0,    24,     0,     0,    36,    45,    46,    47,    48,    49,
       0,    30,    31,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    39,   142,     0,     0,     0,
      41,     0,     0,     0,     0,     0,     0,     0,    45,    46,
      47,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    38,    39,    40,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
       0,    45,    46,    47,    48,    49,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,     0,     0,     0,     0,     0,
       0,     0,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   327,   328,     0,     0,     0,     0,     0,   329,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,     0,
       0,     0,     0,     0,     0,     0,   171,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   184,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,     0,     0,     0,     0,     0,     0,     0,
     171,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   187,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,     0,     0,     0,
       0,     0,     0,     0,   171,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   188,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,     0,     0,     0,     0,     0,     0,     0,   171,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,     0,     0,     0,     0,     0,
       0,     0,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   216,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,     0,
       0,     0,     0,     0,     0,     0,   171,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   418,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,     0,     0,     0,     0,     0,     0,     0,
     171,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   419,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,     0,     0,     0,
       0,     0,     0,     0,   171,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   454,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,     0,     0,     0,     0,     0,     0,     0,   171,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   223,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,     0,     0,     0,     0,     0,     0,
       0,   171,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   311,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,     0,     0,     0,
       0,     0,     0,     0,   171,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     312,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,     0,     0,     0,     0,     0,     0,   171,     0,     0,
       0,     0,     0,   254,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,     0,     0,     0,     0,     0,     0,     0,
     171,     0,     0,     0,     0,     0,   374,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     0,     0,     0,     0,
       0,     0,     0,   171,     0,     0,   330,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     0,     0,     0,     0,
       0,     0,     0,   171,     0,     0,   421,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     0,     0,     0,     0,
       0,     0,     0,   171
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,   105,   130,    30,    31,   275,   213,
     284,     9,    27,    19,     6,   200,   220,     5,    44,     5,
      91,   122,    27,     5,     6,     7,   127,    33,     5,    35,
      36,    28,    38,    39,    40,    41,    53,    43,    44,     3,
       4,    53,    30,   396,    30,    52,   147,   400,    50,    51,
      52,    91,    40,    45,    40,   180,    53,    78,    40,    76,
      24,    25,    26,    40,    76,    91,   101,    31,    73,    89,
      74,    92,    74,   340,   427,   288,    91,    41,    42,    43,
      84,   101,    78,   184,     5,    49,   187,   188,    78,    95,
      96,     6,   305,    91,    78,   196,   281,   101,    94,    78,
      92,    93,    92,    67,    92,    78,    91,   208,    92,   101,
     102,   101,   104,    92,   215,    78,   101,   391,   124,   323,
     387,    94,   101,    87,    88,    89,   101,    91,     6,    93,
      45,    94,    78,   101,   140,   339,   142,   101,   102,   103,
     104,   105,   315,   316,    91,    91,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   101,   291,    45,   174,   175,
      78,   375,    73,    74,   299,   181,    78,   183,    93,   185,
     186,    78,   189,   101,    92,   101,   101,   102,    89,   104,
      92,    78,    93,    90,    48,    49,    50,    51,    52,    76,
     207,   101,    79,    90,   211,    59,    60,    61,    62,    63,
      64,    65,   101,   219,    92,    93,   101,    78,   224,   226,
      74,    78,    78,   101,   102,    78,   104,    93,   329,    90,
     101,   356,    78,    90,    90,   101,    91,    90,    48,    49,
      50,    51,    52,   101,    90,    79,     0,   253,   254,    59,
      60,    61,    62,    63,    64,   262,   101,    91,   265,   266,
      96,   362,   101,    99,    74,   272,   101,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,   292,   293,   106,   107,
      91,   298,   393,    74,    78,    89,    53,   304,   101,    48,
      49,    50,    51,    52,    74,    91,    90,     5,    91,   315,
     316,   317,    91,    94,   415,   416,   101,   418,   419,   325,
      91,   327,   328,   101,   330,    74,     3,     4,   101,    91,
      76,    74,   101,   434,   101,   101,   101,   101,    78,    92,
      92,   101,   443,   101,    36,   446,   352,    24,    25,    26,
     101,   357,   376,   454,    31,   456,   101,   458,   459,   101,
      89,   367,    53,    53,    41,    42,    43,   101,   374,   101,
      89,   101,    49,    89,    89,    82,   383,    94,    53,    91,
      76,    91,    76,    48,    49,    50,    51,    52,   101,    89,
      67,    80,    76,   101,   401,    53,    61,    62,    63,    64,
      10,   269,   101,    91,   101,    78,    93,    89,   414,    74,
      87,    88,    89,    89,    97,   421,    93,    76,   425,    91,
     101,   101,   428,   101,   101,   102,   103,   104,   105,   436,
     437,   438,   439,   385,    91,    91,    90,    90,   214,    91,
      91,    91,   449,   335,   216,   380,    -1,    96,   455,    -1,
     457,    -1,   338,    -1,   461,    -1,   463,    -1,   465,   466,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,
      93,    -1,    95,    -1,    -1,    98,    -1,   100,   101,   102,
     103,   104,   105,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    -1,    -1,    46,    47,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      -1,    -1,    92,    93,    -1,    95,    -1,    -1,    98,    -1,
     100,   101,   102,   103,   104,   105,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    -1,    -1,    92,    93,    -1,    95,    -1,
      -1,    98,    -1,   100,   101,   102,   103,   104,   105,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,    93,
      -1,    95,    -1,    -1,    98,    -1,   100,   101,   102,   103,
     104,   105,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,    -1,
      -1,    92,    93,    -1,    95,    -1,    -1,    98,    -1,   100,
     101,   102,   103,   104,   105,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    -1,    92,    93,    -1,    95,    -1,    -1,
      98,    -1,   100,   101,   102,   103,   104,   105,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    -1,    -1,    92,    93,    -1,
      95,    -1,    -1,    98,    -1,   100,   101,   102,   103,   104,
     105,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    87,    88,    89,    -1,    -1,
      92,    93,    -1,    95,    -1,    -1,    98,    -1,   100,   101,
     102,   103,   104,   105,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    -1,    -1,    92,    93,    -1,    95,    -1,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    -1,    -1,    92,    93,    -1,    95,
      -1,    -1,    98,    -1,   100,   101,   102,   103,   104,   105,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,
      93,    -1,    95,    -1,    -1,    98,    -1,   100,   101,   102,
     103,   104,   105,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    -1,    -1,    46,    47,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      -1,    -1,    92,    93,    -1,    95,    -1,    -1,    98,    -1,
     100,   101,   102,   103,   104,   105,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    -1,    -1,    92,    93,    -1,    95,    -1,
      -1,    98,    -1,   100,   101,   102,   103,   104,   105,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,    93,
      -1,    95,    -1,    -1,    98,    -1,   100,   101,   102,   103,
     104,   105,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,    -1,
      -1,    92,    93,    -1,    95,    -1,    -1,    98,    -1,   100,
     101,   102,   103,   104,   105,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    -1,    92,    93,    -1,    95,    -1,    -1,
      98,    -1,   100,   101,   102,   103,   104,   105,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    -1,    -1,    92,    93,    -1,
      95,    -1,    -1,    98,    -1,   100,   101,   102,   103,   104,
     105,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    87,    88,    89,    -1,    -1,
      92,    93,    -1,    95,    -1,    -1,    98,    -1,   100,   101,
     102,   103,   104,   105,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    -1,    -1,    92,    93,    -1,    95,    -1,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    -1,    -1,    92,    93,    -1,    95,
      -1,    -1,    98,    -1,   100,   101,   102,   103,   104,   105,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,
      93,    -1,    95,    -1,    -1,    98,    -1,   100,   101,   102,
     103,   104,   105,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    -1,    -1,    46,    47,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      -1,    -1,    92,    93,    -1,    95,    -1,    -1,    98,    -1,
     100,   101,   102,   103,   104,   105,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    -1,    -1,    92,    93,    -1,    95,    -1,
      -1,    98,    -1,   100,   101,   102,   103,   104,   105,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    -1,    -1,    92,    93,
      -1,    95,    -1,    -1,    98,    -1,   100,   101,   102,   103,
     104,   105,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,     3,     4,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    67,    -1,     3,     4,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,    24,
      25,    26,    93,    -1,    95,    -1,    31,    98,    -1,   100,
     101,   102,   103,   104,   105,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,     3,     4,    87,
      88,    89,    -1,    91,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    67,   101,   102,   103,   104,   105,    24,    25,
      26,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
       3,     4,    87,    88,    89,    41,    42,    43,    93,    -1,
      -1,    -1,    -1,    49,    -1,    -1,   101,   102,   103,   104,
     105,    24,    25,    26,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    67,    -1,     3,     4,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    87,    88,    89,    24,    25,    26,    93,    -1,    -1,
      -1,    31,    -1,    -1,    67,   101,   102,   103,   104,   105,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    88,    89,    -1,    -1,    -1,
      93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,
      -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,   105,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    -1,    -1,    80,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    80,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    -1,    77,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    -1,    77,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    40,
      41,    42,    43,    46,    47,    49,    67,    86,    87,    88,
      89,    93,    95,    98,   100,   101,   102,   103,   104,   105,
     107,   108,   109,   110,   111,   112,   113,   114,   116,   117,
     118,   121,   122,   123,   129,   130,   131,   135,   138,   140,
     141,   142,   143,   144,   145,   146,   147,   152,   155,   157,
     158,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   171,   172,   173,   175,    91,    91,   101,   101,   101,
     161,   161,   101,   161,   161,    91,    74,    84,   101,   124,
     125,   101,   101,   101,   101,   101,   161,     5,     6,     7,
      40,   101,    91,   101,   101,   101,     5,    91,   166,   166,
      89,   101,   132,   133,   161,   101,   115,   161,   161,   101,
      89,   161,    89,   161,   161,   161,   174,    91,   161,   161,
       0,   112,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    74,    73,    74,    89,    93,   136,   137,   161,   136,
      89,    53,    76,    53,    91,    28,    53,    91,    91,   109,
     124,   124,    74,    27,    91,   126,    91,    44,    91,    91,
      91,    91,   101,   101,   101,     5,    91,   109,    91,   161,
     101,   109,   132,    76,    78,    91,    91,    27,    73,    53,
      76,   161,   161,    90,    78,    94,   109,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   101,   101,   101,   161,
     170,   161,    92,    78,    80,    92,   132,   161,    93,   101,
     134,   161,   109,   161,   161,   109,   109,    92,   101,   101,
      36,   127,   109,   101,   101,   153,   154,   101,   156,    30,
     131,   159,     6,    45,    93,   101,   102,   104,   148,   149,
     150,    89,    53,    53,   101,   101,   176,    92,   109,    89,
      92,    90,   134,   133,   109,   148,   101,    91,   101,   161,
     134,    90,    90,   161,    92,    89,    89,    78,    90,    94,
     161,   161,    90,    94,    82,    53,    92,    84,    85,    91,
      77,    92,    92,   126,    76,    78,    92,    92,    91,    76,
      78,    92,   154,    78,    92,    92,   131,   101,   150,   151,
      92,   149,    80,   132,   161,   161,    89,    76,    78,    92,
      92,   132,    91,    92,    92,   101,   128,    53,    96,    99,
     119,   170,   170,   161,    80,    76,    79,   139,   134,   161,
      10,   161,   161,   109,   161,    93,   127,   153,   134,   154,
     101,    78,    94,    91,   161,   177,    90,   132,   161,   101,
      90,   109,    78,    92,   161,    89,    89,    97,   120,    90,
      90,   161,   134,   166,    79,    91,    91,   142,    91,    91,
      92,    77,   128,    92,   150,   109,   139,    90,    76,   139,
      92,   101,   101,   101,    91,   161,   109,   109,   109,   109,
     161,    94,    92,    91,   139,   161,    91,    90,    90,   109,
      92,    92,    92,    92,    91,   109,    91,   109,    91,    91,
      92,   109,    92,   109,    92,   109,   109,    92,    92,    92,
      92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   106,   107,   108,   109,   109,   110,   111,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   113,   113,   114,   114,   114,   115,
     115,   116,   116,   117,   118,   118,   119,   119,   120,   121,
     121,   122,   122,   123,   123,   123,   123,   124,   124,   125,
     125,   125,   126,   127,   127,   128,   128,   129,   130,   131,
     131,   131,   131,   131,   132,   132,   132,   133,   133,   134,
     134,   134,   135,   135,   136,   136,   137,   137,   138,   139,
     139,   139,   140,   140,   140,   140,   140,   141,   141,   142,
     142,   142,   143,   144,   144,   144,   144,   144,   145,   146,
     147,   148,   148,   149,   149,   150,   150,   150,   150,   150,
     150,   151,   151,   151,   152,   152,   153,   153,   153,   153,
     154,   155,   156,   156,   156,   157,   158,   159,   159,   159,
     160,   160,   161,   161,   161,   161,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   163,   163,   164,   164,   165,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   167,   168,   168,   169,   169,   170,   170,   170,   171,
     172,   172,   173,   174,   174,   174,   175,   176,   176,   176,
     177
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     1,     1,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     2,     2,     6,     4,     1,
       3,     4,     2,     5,     5,     6,     7,     7,     4,     2,
       2,     2,     3,     2,     4,     3,     5,     1,     3,     1,
       2,     2,     3,     5,     3,     1,     3,     2,     5,     9,
      10,    10,    11,     8,     0,     1,     3,     1,     3,     1,
       2,     3,     4,     4,     0,     1,     3,     5,     4,     0,
       2,     2,     4,     6,     5,     4,     6,     4,     5,     5,
       9,     7,     1,    11,     5,     7,     9,     9,     5,     4,
       5,     1,     2,     3,     3,     1,     1,     1,     1,     3,
       2,     0,     1,     3,     5,     7,     0,     1,     3,     2,
       3,     5,     0,     1,     3,     2,     5,     0,     1,     2,
       2,     1,     1,     1,     1,     6,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     5,     7,     4,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     4,     6,     0,     1,     3,     3,
       2,     4,     2,     0,     1,     3,     5,     0,     3,     5,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
#line 120 "src/parser/parser.y"
                                                                  {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2303 "parser.c"
    break;

  case 3: /* program: statement_list  */
#line 132 "src/parser/parser.y"
                   {
        program_root = create_program_node((yyvsp[0].node_list));
    }
#line 2311 "parser.c"
    break;

  case 4: /* statement_list: statement  */
#line 138 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2320 "parser.c"
    break;

  case 5: /* statement_list: statement_list statement  */
#line 142 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2329 "parser.c"
    break;

  case 6: /* unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 148 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_unsafe_node((yyvsp[-1].node_list));
    }
#line 2337 "parser.c"
    break;

  case 7: /* continue_statement: TOKEN_CONTINUE  */
#line 153 "src/parser/parser.y"
                   {
        (yyval.node) = create_continue_node();
    }
#line 2345 "parser.c"
    break;

  case 33: /* statement: expression  */
#line 185 "src/parser/parser.y"
                 {
        (yyval.node) = create_expr_statement((yyvsp[0].node));
    }
#line 2353 "parser.c"
    break;

  case 34: /* sysf_expr: TOKEN_SYSF TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 190 "src/parser/parser.y"
                                                    {
        (yyval.node) = create_sysf_node((yyvsp[-1].node));
    }
#line 2361 "parser.c"
    break;

  case 35: /* sysf_expr: TOKEN_SYSF expression  */
#line 193 "src/parser/parser.y"
                            {
        (yyval.node) = create_sysf_node((yyvsp[0].node));
    }
#line 2369 "parser.c"
    break;

  case 36: /* use_statement: TOKEN_USE use_path  */
#line 200 "src/parser/parser.y"
                       {
        (yyval.node) = create_use_node((yyvsp[0].string), NULL);
    }
#line 2377 "parser.c"
    break;

  case 37: /* use_statement: TOKEN_USE use_path TOKEN_DOUBLE_COLON TOKEN_LBRACE name_list TOKEN_RBRACE  */
#line 204 "src/parser/parser.y"
                                                                                {
        (yyval.node) = create_use_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2385 "parser.c"
    break;

  case 38: /* use_statement: TOKEN_USE use_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 208 "src/parser/parser.y"
                                                   {
        (yyval.node) = create_use_node((yyvsp[-2].string), NULL);
        // Stocker l'alias dans le nœud
        (yyval.node)->use_stmt.alias = strdup((yyvsp[0].string));
    }
#line 2395 "parser.c"
    break;

  case 39: /* use_path: TOKEN_IDENTIFIER  */
#line 216 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2403 "parser.c"
    break;

  case 40: /* use_path: use_path TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 219 "src/parser/parser.y"
                                                   {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 3);
        sprintf(path, "%s::%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2414 "parser.c"
    break;

  case 41: /* sh_expr: TOKEN_SH TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 228 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_sh_node((yyvsp[-1].node));
    }
#line 2422 "parser.c"
    break;

  case 42: /* sh_expr: TOKEN_SH expression  */
#line 231 "src/parser/parser.y"
                          {
        (yyval.node) = create_sh_node((yyvsp[0].node));
    }
#line 2430 "parser.c"
    break;

  case 43: /* nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 237 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_nnl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2438 "parser.c"
    break;

  case 44: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block  */
#line 243 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_try_node((yyvsp[-2].node_list), (yyvsp[0].node), NULL);
    }
#line 2446 "parser.c"
    break;

  case 45: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block  */
#line 246 "src/parser/parser.y"
                                                                                   {
        (yyval.node) = create_try_node((yyvsp[-3].node_list), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2454 "parser.c"
    break;

  case 46: /* catch_block: TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 252 "src/parser/parser.y"
                                                                                                    {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2462 "parser.c"
    break;

  case 47: /* catch_block: TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 255 "src/parser/parser.y"
                                                                                                       {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2470 "parser.c"
    break;

  case 48: /* finally_block: TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 261 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_finally_node((yyvsp[-1].node_list));
    }
#line 2478 "parser.c"
    break;

  case 49: /* throw_statement: TOKEN_THROW expression  */
#line 267 "src/parser/parser.y"
                           {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2486 "parser.c"
    break;

  case 50: /* throw_statement: TOKEN_RAISE expression  */
#line 270 "src/parser/parser.y"
                             {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2494 "parser.c"
    break;

  case 51: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER  */
#line 275 "src/parser/parser.y"
                               {
        (yyval.node) = create_jmp_node((yyvsp[0].string), NULL);
    }
#line 2502 "parser.c"
    break;

  case 52: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression  */
#line 278 "src/parser/parser.y"
                                            {
        (yyval.node) = create_jmp_node((yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2510 "parser.c"
    break;

  case 53: /* import_statement: TOKEN_IMPORT import_path  */
#line 287 "src/parser/parser.y"
                             {
        (yyval.node) = create_import_node((yyvsp[0].string), NULL, NULL);
    }
#line 2518 "parser.c"
    break;

  case 54: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 291 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_import_node((yyvsp[-2].string), (yyvsp[0].string), NULL);
    }
#line 2526 "parser.c"
    break;

  case 55: /* import_statement: TOKEN_IMPORT import_path import_constraints  */
#line 295 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_import_node((yyvsp[-1].string), NULL, (yyvsp[0].node));
    }
#line 2534 "parser.c"
    break;

  case 56: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER import_constraints  */
#line 299 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_import_node((yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2542 "parser.c"
    break;

  case 57: /* import_path_tail: TOKEN_IDENTIFIER  */
#line 306 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2550 "parser.c"
    break;

  case 58: /* import_path_tail: import_path_tail TOKEN_DOT TOKEN_IDENTIFIER  */
#line 309 "src/parser/parser.y"
                                                  {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 2);
        sprintf(path, "%s.%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2561 "parser.c"
    break;

  case 59: /* import_path: import_path_tail  */
#line 318 "src/parser/parser.y"
                     { 
        (yyval.string) = (yyvsp[0].string); 
    }
#line 2569 "parser.c"
    break;

  case 60: /* import_path: TOKEN_DOT import_path_tail  */
#line 321 "src/parser/parser.y"
                                 { // Import relatif: .fichier
        char* path = malloc(strlen((yyvsp[0].string)) + 2);
        sprintf(path, ".%s", (yyvsp[0].string));
        free((yyvsp[0].string));
        (yyval.string) = path;
    }
#line 2580 "parser.c"
    break;

  case 61: /* import_path: TOKEN_RANGE import_path_tail  */
#line 327 "src/parser/parser.y"
                                   { // Import relatif: ..fichier (utilise TOKEN_RANGE ".." du lexer)
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "..%s", (yyvsp[0].string));
        free((yyvsp[0].string));
        (yyval.string) = path;
    }
#line 2591 "parser.c"
    break;

  case 62: /* import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE  */
#line 336 "src/parser/parser.y"
                                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2599 "parser.c"
    break;

  case 63: /* import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET  */
#line 342 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_constraints_node("only", (yyvsp[-1].node_list));
    }
#line 2607 "parser.c"
    break;

  case 64: /* import_options: import_options TOKEN_COMMA import_options  */
#line 345 "src/parser/parser.y"
                                                {
        (yyval.node) = merge_constraints((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2615 "parser.c"
    break;

  case 65: /* name_list: TOKEN_IDENTIFIER  */
#line 351 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2624 "parser.c"
    break;

  case 66: /* name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 355 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2633 "parser.c"
    break;

  case 67: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
#line 362 "src/parser/parser.y"
                                  {
        (yyval.node) = create_export_node((yyvsp[0].string));
    }
#line 2641 "parser.c"
    break;

  case 68: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 368 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_packet_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2649 "parser.c"
    break;

  case 69: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 374 "src/parser/parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2657 "parser.c"
    break;

  case 70: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 377 "src/parser/parser.y"
                                                                                                                                    {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2665 "parser.c"
    break;

  case 71: /* function_decl: TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 380 "src/parser/parser.y"
                                                                                                                                      {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        (yyval.node) = node;
    }
#line 2676 "parser.c"
    break;

  case 72: /* function_decl: TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 386 "src/parser/parser.y"
                                                                                                                                                {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        (yyval.node) = node;
    }
#line 2688 "parser.c"
    break;

  case 73: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression  */
#line 393 "src/parser/parser.y"
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node((yyvsp[0].node));
        add_to_node_list(body, return_stmt);
        (yyval.node) = create_function_node((yyvsp[-6].string), (yyvsp[-4].node_list), (yyvsp[-2].node), body);
    }
#line 2699 "parser.c"
    break;

  case 74: /* param_list: %empty  */
#line 402 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2707 "parser.c"
    break;

  case 75: /* param_list: param  */
#line 405 "src/parser/parser.y"
            {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2716 "parser.c"
    break;

  case 76: /* param_list: param_list TOKEN_COMMA param  */
#line 409 "src/parser/parser.y"
                                   {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2725 "parser.c"
    break;

  case 77: /* param: TOKEN_IDENTIFIER  */
#line 416 "src/parser/parser.y"
                     {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 2733 "parser.c"
    break;

  case 78: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 419 "src/parser/parser.y"
                                        {
        (yyval.node) = create_param_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2741 "parser.c"
    break;

  case 79: /* type: TOKEN_IDENTIFIER  */
#line 425 "src/parser/parser.y"
                     {
        (yyval.node) = create_type_node((yyvsp[0].string));
    }
#line 2749 "parser.c"
    break;

  case 80: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
#line 428 "src/parser/parser.y"
                                      {
        (yyval.node) = create_optional_type_node((yyvsp[-1].string));
    }
#line 2757 "parser.c"
    break;

  case 81: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 431 "src/parser/parser.y"
                                         {
        (yyval.node) = create_array_type_node((yyvsp[0].node));
    }
#line 2765 "parser.c"
    break;

  case 82: /* dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 439 "src/parser/parser.y"
                                                      {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2773 "parser.c"
    break;

  case 83: /* dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 442 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2781 "parser.c"
    break;

  case 84: /* dict_entries: %empty  */
#line 448 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2789 "parser.c"
    break;

  case 85: /* dict_entries: dict_entry_list  */
#line 451 "src/parser/parser.y"
                      {
        (yyval.node_list) = (yyvsp[0].node_list);
    }
#line 2797 "parser.c"
    break;

  case 86: /* dict_entry_list: expression TOKEN_FAT_ARROW expression  */
#line 457 "src/parser/parser.y"
                                          {
        (yyval.node_list) = create_node_list();
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyval.node_list), pair);
    }
#line 2807 "parser.c"
    break;

  case 87: /* dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression  */
#line 462 "src/parser/parser.y"
                                                                        {
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyvsp[-4].node_list), pair);
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 2817 "parser.c"
    break;

  case 88: /* dict_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 471 "src/parser/parser.y"
                                                          {
        // Détecter si c'est un accès dictionnaire ou tableau
        // Par défaut, c'est un accès tableau, mais on peut différencier par le type
        // Pour l'instant, on crée un nœud d'accès dictionnaire
        (yyval.node) = create_dict_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2828 "parser.c"
    break;

  case 89: /* return_type: %empty  */
#line 490 "src/parser/parser.y"
                {
        (yyval.node) = NULL;
    }
#line 2836 "parser.c"
    break;

  case 90: /* return_type: TOKEN_COLON type  */
#line 493 "src/parser/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2844 "parser.c"
    break;

  case 91: /* return_type: TOKEN_ARROW primary_expr  */
#line 496 "src/parser/parser.y"
                               {
        // Pour les retours directs: -> expr
        (yyval.node) = create_return_direct_node((yyvsp[0].node));
    }
#line 2853 "parser.c"
    break;

  case 92: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 503 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2861 "parser.c"
    break;

  case 93: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 506 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_let_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2869 "parser.c"
    break;

  case 94: /* let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 509 "src/parser/parser.y"
                                                                   {
        ASTNode* node = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2879 "parser.c"
    break;

  case 95: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 515 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_muts_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2887 "parser.c"
    break;

  case 96: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 518 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_muts_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2895 "parser.c"
    break;

  case 97: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 523 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2903 "parser.c"
    break;

  case 98: /* const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 526 "src/parser/parser.y"
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2914 "parser.c"
    break;

  case 99: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 535 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-1].node_list), NULL);
    }
#line 2922 "parser.c"
    break;

  case 100: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 538 "src/parser/parser.y"
                                                                                                                       {
        (yyval.node) = create_if_node((yyvsp[-7].node), (yyvsp[-5].node_list), (yyvsp[-1].node_list));
    }
#line 2930 "parser.c"
    break;

  case 101: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE if_statement  */
#line 541 "src/parser/parser.y"
                                                                                           {
        // else if -> le else contient un autre if
        ASTNodeList* else_branch = create_node_list();
        add_to_node_list(else_branch, (yyvsp[0].node));
        (yyval.node) = create_if_node((yyvsp[-5].node), (yyvsp[-3].node_list), else_branch);
    }
#line 2941 "parser.c"
    break;

  case 102: /* break_statement: TOKEN_BREAK  */
#line 549 "src/parser/parser.y"
                {
        (yyval.node) = create_break_node();
    }
#line 2949 "parser.c"
    break;

  case 103: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 554 "src/parser/parser.y"
                                                                                                                                                      {
        ASTNode* init = create_let_node((yyvsp[-9].string), NULL, (yyvsp[-7].node));
        ASTNode* cond = (yyvsp[-5].node);
        ASTNode* inc = create_expr_statement((yyvsp[-3].node));
        (yyval.node) = create_for_node(init, cond, inc, (yyvsp[-1].node_list));
    }
#line 2960 "parser.c"
    break;

  case 104: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 560 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2968 "parser.c"
    break;

  case 105: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 563 "src/parser/parser.y"
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
#line 2986 "parser.c"
    break;

  case 106: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 576 "src/parser/parser.y"
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
#line 3006 "parser.c"
    break;

  case 107: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE_INC expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 591 "src/parser/parser.y"
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
#line 3022 "parser.c"
    break;

  case 108: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 606 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3030 "parser.c"
    break;

  case 109: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 612 "src/parser/parser.y"
                                                        {
        (yyval.node) = create_loop_node((yyvsp[-1].node_list));
    }
#line 3038 "parser.c"
    break;

  case 110: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 619 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3046 "parser.c"
    break;

  case 111: /* match_cases: match_case  */
#line 625 "src/parser/parser.y"
               {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3055 "parser.c"
    break;

  case 112: /* match_cases: match_cases match_case  */
#line 629 "src/parser/parser.y"
                             {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3064 "parser.c"
    break;

  case 113: /* match_case: pattern TOKEN_FAT_ARROW expression  */
#line 636 "src/parser/parser.y"
                                       {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3072 "parser.c"
    break;

  case 114: /* match_case: pattern TOKEN_FAT_ARROW block  */
#line 639 "src/parser/parser.y"
                                    {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (ASTNode*)(yyvsp[0].node));
    }
#line 3080 "parser.c"
    break;

  case 115: /* pattern: TOKEN_NUMBER  */
#line 645 "src/parser/parser.y"
                 { (yyval.node) = create_pattern_number((yyvsp[0].number)); }
#line 3086 "parser.c"
    break;

  case 116: /* pattern: TOKEN_STRING  */
#line 646 "src/parser/parser.y"
                   { (yyval.node) = create_pattern_string((yyvsp[0].string)); }
#line 3092 "parser.c"
    break;

  case 117: /* pattern: TOKEN_IDENTIFIER  */
#line 647 "src/parser/parser.y"
                       { (yyval.node) = create_pattern_ident((yyvsp[0].string)); }
#line 3098 "parser.c"
    break;

  case 118: /* pattern: TOKEN_UNDERSCORE  */
#line 648 "src/parser/parser.y"
                       { (yyval.node) = create_pattern_wildcard(); }
#line 3104 "parser.c"
    break;

  case 119: /* pattern: TOKEN_LBRACKET array_patterns TOKEN_RBRACKET  */
#line 649 "src/parser/parser.y"
                                                   { (yyval.node) = create_pattern_array((yyvsp[-1].node_list)); }
#line 3110 "parser.c"
    break;

  case 120: /* pattern: TOKEN_LET TOKEN_IDENTIFIER  */
#line 650 "src/parser/parser.y"
                                 { (yyval.node) = create_pattern_binding((yyvsp[0].string)); }
#line 3116 "parser.c"
    break;

  case 121: /* array_patterns: %empty  */
#line 654 "src/parser/parser.y"
                { (yyval.node_list) = NULL; }
#line 3122 "parser.c"
    break;

  case 122: /* array_patterns: pattern  */
#line 655 "src/parser/parser.y"
              { (yyval.node_list) = create_node_list(); add_to_node_list((yyval.node_list), (yyvsp[0].node)); }
#line 3128 "parser.c"
    break;

  case 123: /* array_patterns: array_patterns TOKEN_COMMA pattern  */
#line 656 "src/parser/parser.y"
                                         { add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node)); (yyval.node_list) = (yyvsp[-2].node_list); }
#line 3134 "parser.c"
    break;

  case 124: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 661 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_struct_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3142 "parser.c"
    break;

  case 125: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 664 "src/parser/parser.y"
                                                                                                           {
        (yyval.node) = create_struct_extend_node((yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3150 "parser.c"
    break;

  case 126: /* struct_fields: %empty  */
#line 670 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3158 "parser.c"
    break;

  case 127: /* struct_fields: struct_field  */
#line 673 "src/parser/parser.y"
                   {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3167 "parser.c"
    break;

  case 128: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
#line 677 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3176 "parser.c"
    break;

  case 129: /* struct_fields: struct_fields struct_field  */
#line 681 "src/parser/parser.y"
                                 {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3185 "parser.c"
    break;

  case 130: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 688 "src/parser/parser.y"
                                      {
        (yyval.node) = create_field_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 3193 "parser.c"
    break;

  case 131: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
#line 694 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_enum_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3201 "parser.c"
    break;

  case 132: /* enum_variants: %empty  */
#line 700 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3209 "parser.c"
    break;

  case 133: /* enum_variants: TOKEN_IDENTIFIER  */
#line 703 "src/parser/parser.y"
                       {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 3218 "parser.c"
    break;

  case 134: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 707 "src/parser/parser.y"
                                                 {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3227 "parser.c"
    break;

  case 135: /* module_decl: TOKEN_MODULE TOKEN_IDENTIFIER  */
#line 714 "src/parser/parser.y"
                                  {
        // Créer un nœud nil pour éviter l'erreur
        (yyval.node) = create_expr_statement(create_nil_node());
    }
#line 3236 "parser.c"
    break;

  case 136: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
#line 721 "src/parser/parser.y"
                                                                             {
        (yyval.node) = create_impl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3244 "parser.c"
    break;

  case 137: /* function_decl_list: %empty  */
#line 727 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3252 "parser.c"
    break;

  case 138: /* function_decl_list: function_decl  */
#line 730 "src/parser/parser.y"
                    {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3261 "parser.c"
    break;

  case 139: /* function_decl_list: function_decl_list function_decl  */
#line 734 "src/parser/parser.y"
                                       {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3270 "parser.c"
    break;

  case 140: /* return_statement: TOKEN_RETURN expression  */
#line 741 "src/parser/parser.y"
                            {
        (yyval.node) = create_return_node((yyvsp[0].node));
    }
#line 3278 "parser.c"
    break;

  case 141: /* return_statement: TOKEN_RETURN  */
#line 744 "src/parser/parser.y"
                   {
        (yyval.node) = create_return_node(NULL);
    }
#line 3286 "parser.c"
    break;

  case 145: /* expression: expression TOKEN_DOT TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 753 "src/parser/parser.y"
                                                                                    {
        // 'expression' est l'objet ($1), 'TOKEN_IDENTIFIER' est la méthode ($3)
        // 'argument_list' est la liste des arguments ($5)
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3296 "parser.c"
    break;

  case 146: /* binary_expr: expression TOKEN_PLUS expression  */
#line 761 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_ADD, (yyvsp[0].node));
    }
#line 3304 "parser.c"
    break;

  case 147: /* binary_expr: expression TOKEN_MINUS expression  */
#line 764 "src/parser/parser.y"
                                        {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_SUB, (yyvsp[0].node));
    }
#line 3312 "parser.c"
    break;

  case 148: /* binary_expr: expression TOKEN_MULTIPLY expression  */
#line 767 "src/parser/parser.y"
                                           {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
    }
#line 3320 "parser.c"
    break;

  case 149: /* binary_expr: expression TOKEN_DIVIDE expression  */
#line 770 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
    }
#line 3328 "parser.c"
    break;

  case 150: /* binary_expr: expression TOKEN_MODULO expression  */
#line 773 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
    }
#line 3336 "parser.c"
    break;

  case 151: /* binary_expr: expression TOKEN_EQ expression  */
#line 776 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_EQ, (yyvsp[0].node));
    }
#line 3344 "parser.c"
    break;

  case 152: /* binary_expr: expression TOKEN_NEQ expression  */
#line 779 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_NEQ, (yyvsp[0].node));
    }
#line 3352 "parser.c"
    break;

  case 153: /* binary_expr: expression TOKEN_LT expression  */
#line 782 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
    }
#line 3360 "parser.c"
    break;

  case 154: /* binary_expr: expression TOKEN_LTE expression  */
#line 785 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LTE, (yyvsp[0].node));
    }
#line 3368 "parser.c"
    break;

  case 155: /* binary_expr: expression TOKEN_GT expression  */
#line 788 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
    }
#line 3376 "parser.c"
    break;

  case 156: /* binary_expr: expression TOKEN_GTE expression  */
#line 791 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GTE, (yyvsp[0].node));
    }
#line 3384 "parser.c"
    break;

  case 157: /* binary_expr: expression TOKEN_AND expression  */
#line 794 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_AND, (yyvsp[0].node));
    }
#line 3392 "parser.c"
    break;

  case 158: /* binary_expr: expression TOKEN_OR expression  */
#line 797 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_OR, (yyvsp[0].node));
    }
#line 3400 "parser.c"
    break;

  case 159: /* binary_expr: expression TOKEN_ASSIGN expression  */
#line 800 "src/parser/parser.y"
                                         {
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3408 "parser.c"
    break;

  case 160: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
#line 803 "src/parser/parser.y"
                                              {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_ADD_ASSIGN, (yyvsp[0].node));
    }
#line 3416 "parser.c"
    break;

  case 161: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
#line 806 "src/parser/parser.y"
                                               {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_SUB_ASSIGN, (yyvsp[0].node));
    }
#line 3424 "parser.c"
    break;

  case 162: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
#line 809 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MUL_ASSIGN, (yyvsp[0].node));
    }
#line 3432 "parser.c"
    break;

  case 163: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
#line 812 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_DIV_ASSIGN, (yyvsp[0].node));
    }
#line 3440 "parser.c"
    break;

  case 164: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
#line 815 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MOD_ASSIGN, (yyvsp[0].node));
    }
#line 3448 "parser.c"
    break;

  case 165: /* unary_expr: TOKEN_NOT expression  */
#line 821 "src/parser/parser.y"
                         {
        (yyval.node) = create_unary_op(OP_NOT, (yyvsp[0].node));
    }
#line 3456 "parser.c"
    break;

  case 166: /* unary_expr: TOKEN_MINUS expression  */
#line 824 "src/parser/parser.y"
                             {
        (yyval.node) = create_unary_op(OP_NEG, (yyvsp[0].node));
    }
#line 3464 "parser.c"
    break;

  case 167: /* lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 831 "src/parser/parser.y"
                                                                     {
        (yyval.node) = create_lambda_node((yyvsp[-3].node_list), (yyvsp[-1].node_list));
    }
#line 3472 "parser.c"
    break;

  case 168: /* lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 834 "src/parser/parser.y"
                                                                                                 {
        (yyval.node) = create_lambda_node((yyvsp[-4].node_list), (yyvsp[-1].node_list));
    }
#line 3480 "parser.c"
    break;

  case 169: /* array_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 841 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 3488 "parser.c"
    break;

  case 170: /* primary_expr: TOKEN_NUMBER  */
#line 847 "src/parser/parser.y"
                 {
        (yyval.node) = create_number_node((yyvsp[0].number));
    }
#line 3496 "parser.c"
    break;

  case 171: /* primary_expr: TOKEN_FLOAT  */
#line 850 "src/parser/parser.y"
                  {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 3504 "parser.c"
    break;

  case 172: /* primary_expr: TOKEN_STRING  */
#line 853 "src/parser/parser.y"
                   {
        (yyval.node) = create_string_node((yyvsp[0].string));
    }
#line 3512 "parser.c"
    break;

  case 173: /* primary_expr: TOKEN_TRUE  */
#line 856 "src/parser/parser.y"
                 {
        (yyval.node) = create_bool_node(1);
    }
#line 3520 "parser.c"
    break;

  case 174: /* primary_expr: TOKEN_FALSE  */
#line 859 "src/parser/parser.y"
                  {
        (yyval.node) = create_bool_node(0);
    }
#line 3528 "parser.c"
    break;

  case 175: /* primary_expr: TOKEN_NIL  */
#line 862 "src/parser/parser.y"
                {
        (yyval.node) = create_nil_node();
    }
#line 3536 "parser.c"
    break;

  case 176: /* primary_expr: TOKEN_IDENTIFIER  */
#line 865 "src/parser/parser.y"
                       {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 3544 "parser.c"
    break;

  case 177: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 868 "src/parser/parser.y"
                                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3552 "parser.c"
    break;

  case 191: /* f_string: TOKEN_F_STRING  */
#line 887 "src/parser/parser.y"
                   {
        (yyval.node) = parse_f_string((yyvsp[0].string));
    }
#line 3560 "parser.c"
    break;

  case 192: /* member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER  */
#line 893 "src/parser/parser.y"
                                            {
        (yyval.node) = create_member_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3568 "parser.c"
    break;

  case 193: /* member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 896 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_static_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3576 "parser.c"
    break;

  case 194: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 902 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_call_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3584 "parser.c"
    break;

  case 195: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 905 "src/parser/parser.y"
                                                                                               {
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3592 "parser.c"
    break;

  case 196: /* argument_list: %empty  */
#line 911 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3600 "parser.c"
    break;

  case 197: /* argument_list: expression  */
#line 914 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_arg_list();
        add_arg((yyval.node_list), (yyvsp[0].node));
    }
#line 3609 "parser.c"
    break;

  case 198: /* argument_list: argument_list TOKEN_COMMA expression  */
#line 918 "src/parser/parser.y"
                                           {
        add_arg((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3618 "parser.c"
    break;

  case 199: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
#line 925 "src/parser/parser.y"
                                              {
        (yyval.node) = create_array_node((yyvsp[-1].node_list));
    }
#line 3626 "parser.c"
    break;

  case 200: /* await_expr: TOKEN_AWAIT primary_expr  */
#line 940 "src/parser/parser.y"
                             {
        (yyval.node) = create_await_node((yyvsp[0].node));
    }
#line 3634 "parser.c"
    break;

  case 201: /* await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 943 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_await_block_node((yyvsp[-1].node_list));
    }
#line 3642 "parser.c"
    break;

  case 202: /* spawn_expr: TOKEN_SPAWN primary_expr  */
#line 950 "src/parser/parser.y"
                             {
        (yyval.node) = create_spawn_node((yyvsp[0].node));
    }
#line 3650 "parser.c"
    break;

  case 203: /* array_items: %empty  */
#line 962 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3658 "parser.c"
    break;

  case 204: /* array_items: expression  */
#line 965 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3667 "parser.c"
    break;

  case 205: /* array_items: array_items TOKEN_COMMA expression  */
#line 969 "src/parser/parser.y"
                                         {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3676 "parser.c"
    break;

  case 206: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
#line 976 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_struct_init_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3684 "parser.c"
    break;

  case 207: /* struct_init_fields: %empty  */
#line 982 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3692 "parser.c"
    break;

  case 208: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 985 "src/parser/parser.y"
                                              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
    }
#line 3701 "parser.c"
    break;

  case 209: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 989 "src/parser/parser.y"
                                                                             {
        add_to_node_list((yyvsp[-4].node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 3710 "parser.c"
    break;

  case 210: /* block: TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 996 "src/parser/parser.y"
                                             {
        (yyval.node) = (ASTNode*)(yyvsp[-1].node_list);
    }
#line 3718 "parser.c"
    break;


#line 3722 "parser.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 1001 "src/parser/parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

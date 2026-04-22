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
  YYSYMBOL_import_path = 124,              /* import_path  */
  YYSYMBOL_import_constraints = 125,       /* import_constraints  */
  YYSYMBOL_import_options = 126,           /* import_options  */
  YYSYMBOL_name_list = 127,                /* name_list  */
  YYSYMBOL_export_statement = 128,         /* export_statement  */
  YYSYMBOL_packet_decl = 129,              /* packet_decl  */
  YYSYMBOL_function_decl = 130,            /* function_decl  */
  YYSYMBOL_param_list = 131,               /* param_list  */
  YYSYMBOL_param = 132,                    /* param  */
  YYSYMBOL_type = 133,                     /* type  */
  YYSYMBOL_dict_expr = 134,                /* dict_expr  */
  YYSYMBOL_dict_entries = 135,             /* dict_entries  */
  YYSYMBOL_dict_entry_list = 136,          /* dict_entry_list  */
  YYSYMBOL_dict_access = 137,              /* dict_access  */
  YYSYMBOL_return_type = 138,              /* return_type  */
  YYSYMBOL_let_decl = 139,                 /* let_decl  */
  YYSYMBOL_const_decl = 140,               /* const_decl  */
  YYSYMBOL_if_statement = 141,             /* if_statement  */
  YYSYMBOL_break_statement = 142,          /* break_statement  */
  YYSYMBOL_for_statement = 143,            /* for_statement  */
  YYSYMBOL_while_statement = 144,          /* while_statement  */
  YYSYMBOL_loop_statement = 145,           /* loop_statement  */
  YYSYMBOL_match_statement = 146,          /* match_statement  */
  YYSYMBOL_match_cases = 147,              /* match_cases  */
  YYSYMBOL_match_case = 148,               /* match_case  */
  YYSYMBOL_pattern = 149,                  /* pattern  */
  YYSYMBOL_struct_decl = 150,              /* struct_decl  */
  YYSYMBOL_struct_fields = 151,            /* struct_fields  */
  YYSYMBOL_struct_field = 152,             /* struct_field  */
  YYSYMBOL_enum_decl = 153,                /* enum_decl  */
  YYSYMBOL_enum_variants = 154,            /* enum_variants  */
  YYSYMBOL_module_decl = 155,              /* module_decl  */
  YYSYMBOL_impl_decl = 156,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 157,       /* function_decl_list  */
  YYSYMBOL_return_statement = 158,         /* return_statement  */
  YYSYMBOL_expression = 159,               /* expression  */
  YYSYMBOL_binary_expr = 160,              /* binary_expr  */
  YYSYMBOL_unary_expr = 161,               /* unary_expr  */
  YYSYMBOL_lambda_expr = 162,              /* lambda_expr  */
  YYSYMBOL_array_access = 163,             /* array_access  */
  YYSYMBOL_primary_expr = 164,             /* primary_expr  */
  YYSYMBOL_f_string = 165,                 /* f_string  */
  YYSYMBOL_member_access = 166,            /* member_access  */
  YYSYMBOL_call_expr = 167,                /* call_expr  */
  YYSYMBOL_argument_list = 168,            /* argument_list  */
  YYSYMBOL_array_expr = 169,               /* array_expr  */
  YYSYMBOL_await_expr = 170,               /* await_expr  */
  YYSYMBOL_spawn_expr = 171,               /* spawn_expr  */
  YYSYMBOL_array_items = 172,              /* array_items  */
  YYSYMBOL_struct_expr = 173,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 174,       /* struct_init_fields  */
  YYSYMBOL_block = 175                     /* block  */
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
#define YYFINAL  147
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3738

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  201
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  453

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
       0,   117,   117,   129,   135,   139,   145,   150,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   187,   190,   197,   201,   205,   213,
     216,   225,   228,   234,   240,   243,   249,   252,   258,   264,
     267,   272,   275,   284,   288,   292,   296,   303,   306,   314,
     320,   323,   329,   333,   340,   346,   352,   355,   358,   364,
     371,   380,   383,   387,   394,   397,   403,   406,   409,   417,
     420,   426,   429,   435,   440,   449,   468,   471,   474,   481,
     484,   487,   493,   496,   501,   504,   513,   516,   519,   527,
     532,   538,   541,   554,   569,   584,   590,   597,   603,   607,
     614,   617,   622,   625,   628,   631,   637,   640,   646,   649,
     653,   657,   664,   670,   676,   679,   683,   690,   697,   703,
     706,   710,   717,   720,   726,   727,   728,   732,   735,   738,
     741,   744,   747,   750,   753,   756,   759,   762,   765,   768,
     771,   774,   777,   780,   783,   786,   792,   795,   802,   805,
     812,   818,   821,   824,   827,   830,   833,   836,   839,   842,
     843,   844,   845,   846,   847,   848,   849,   850,   851,   852,
     853,   854,   858,   864,   867,   873,   876,   882,   885,   889,
     896,   911,   914,   921,   933,   936,   940,   947,   953,   956,
     960,   967
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
  "jmp_statement", "import_statement", "import_path", "import_constraints",
  "import_options", "name_list", "export_statement", "packet_decl",
  "function_decl", "param_list", "param", "type", "dict_expr",
  "dict_entries", "dict_entry_list", "dict_access", "return_type",
  "let_decl", "const_decl", "if_statement", "break_statement",
  "for_statement", "while_statement", "loop_statement", "match_statement",
  "match_cases", "match_case", "pattern", "struct_decl", "struct_fields",
  "struct_field", "enum_decl", "enum_variants", "module_decl", "impl_decl",
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

#define YYPACT_NINF (-273)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2911,   -35,   -18,   -76,   -15,    -2,  2977,  2977,  3026,  2977,
       6,  -273,  -273,     9,    33,    68,    69,    87,    89,  2977,
    -273,  -273,  -273,    45,   110,    36,   114,   124,   137,    70,
      98,  2944,    78,  2977,   149,  2977,  2977,   168,  3059,  3092,
    2977,  2977,   128,  2977,  2977,  -273,  -273,  -273,  -273,  -273,
    -273,    95,  2911,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  3672,  -273,  -273,  -273,  -273,   131,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  2977,  2977,   148,   -32,   226,
    3672,  3213,    -4,  3232,  3276,  2911,  -273,   -20,  -273,   189,
     -30,   198,   199,  3295,   190,   191,   192,   289,   213,  2911,
     217,  2977,  -273,   194,  2911,   131,   131,   206,   234,   -11,
    -273,  3339,  -273,   -10,   204,  -273,    17,  2977,  3672,  2977,
    3672,  3465,  3672,     4,  2911,  3672,  3672,  -273,  -273,  2977,
    2977,  2977,  2977,  2977,  2977,  2977,  2977,  2977,  2977,  2977,
    2977,  2977,  2977,  2977,  2977,  2977,  2977,  2977,   212,   214,
    2977,  2977,   224,   239,  3546,   227,   206,  2977,   156,  2977,
    2911,  2977,  2977,  2911,  2911,   439,   220,   221,   282,  -273,
    2911,   222,   223,   225,    13,    91,   236,   274,   275,   229,
     230,   542,  2911,  3672,   245,   645,    90,   156,   206,  2911,
      91,   238,   -55,  2977,   156,  3484,  3527,  -273,  2977,  -273,
     748,   204,   204,  -273,  -273,  -273,  3672,  3672,  3672,  3672,
    3672,  3672,   235,   235,   216,   216,   216,   216,   183,   211,
     246,  -273,  3672,   118,  3150,  -273,  2977,  2977,  -273,   132,
    3672,   243,   259,   290,  3672,   851,  3169,  3612,   954,  1057,
    -273,   255,  -273,   271,   -66,  1160,   258,   276,    -1,  -273,
    -273,   -16,    26,  -273,    34,  -273,  -273,  -273,  -273,   -23,
    -273,   270,   206,  2977,  2977,   262,   277,    50,  -273,  1263,
     206,  -273,   264,  -273,  -273,  1366,    80,  -273,   256,  -273,
    3672,   303,  -273,  -273,  3672,    39,  2977,  2977,  -273,  -273,
    3579,  3672,   160,   156,  -273,  2977,   348,  2977,  2977,  2911,
    2977,  -273,  -273,  -273,   266,   282,  -273,  -273,   223,   156,
     223,  -273,  -273,   260,  -273,  -273,  -273,  -273,  -273,    16,
     136,  3672,  3672,   206,  2977,   263,  -273,  -273,   138,  2911,
    -273,  -273,  -273,    85,  2977,   278,   279,   268,   139,  3672,
    2977,   156,  2944,   130,  -273,  3672,     1,  3358,  3402,  1469,
    3642,   256,   285,   105,  -273,  -273,  -273,  2911,  3672,  -273,
     160,   140,  3672,   284,   160,  1572,   265,  -273,  3672,   269,
     272,   280,  -273,  -273,  3672,  -273,   131,  2977,  2911,  2911,
    -273,  2911,  2911,  -273,  2977,    38,  -273,  1675,   281,   160,
    2977,   283,  -273,  -273,   286,   287,  2911,  3672,  1778,  1881,
    1984,  2087,  3421,  -273,  -273,  2911,   288,  3672,  2911,   291,
     292,  2190,  -273,  -273,  -273,  -273,  2911,  2293,  2911,  2396,
    2911,  2911,  -273,  2499,  -273,  2602,  -273,  2705,  2808,  -273,
    -273,  -273,  -273
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
       0,    99,     7,     0,     0,     0,     0,     0,     0,     0,
     164,   165,   166,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,     0,     0,
       0,   194,     0,     0,     0,   167,   161,   162,   163,   182,
      20,     0,     3,    28,    10,     4,   178,    17,   179,    11,
      14,    15,    12,     8,     9,    16,    18,   171,   170,    23,
      25,    26,    24,    27,    29,    30,    31,    19,    21,    13,
      22,    32,    33,   134,   135,   175,   176,   136,   181,   174,
     169,   172,   177,   180,   173,    81,    81,     0,     0,     0,
     132,     0,   167,     0,     0,     0,    57,    53,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,   127,     0,     0,   191,   193,    71,    74,     0,
      72,     0,    39,    36,   157,   156,     0,     0,    35,     0,
      42,     0,   195,     0,     0,    49,    50,     1,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     187,     0,     0,    82,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
       0,     0,   118,   124,   129,     0,     0,     0,     0,     0,
     198,     0,     0,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   168,     0,   190,
       0,   137,   138,   139,   140,   141,   150,   151,   152,   153,
     154,   155,   142,   143,   144,   145,   146,   147,   148,   149,
     184,   183,   188,     0,     0,    79,     0,     0,    80,     0,
      89,     0,    76,     0,    94,     0,     0,     0,     0,     0,
     106,    54,    58,     0,     0,     0,     0,     0,     0,   119,
     125,     0,     0,   130,     0,   115,   114,   112,   113,     0,
     108,     0,    71,     0,     0,     0,     0,     0,     6,     0,
      71,   192,     0,    75,    73,     0,     0,    38,     0,    40,
      92,     0,    34,    41,   196,     0,   187,     0,   185,    85,
       0,    83,    86,     0,    77,     0,    96,     0,     0,     0,
       0,   101,   105,    56,     0,     0,    59,    65,   118,     0,
       0,   116,   121,     0,   123,   128,   131,   107,   109,     0,
       0,    91,    95,    71,     0,     0,   197,    43,     0,     0,
     158,     2,    62,     0,     0,     0,     0,    44,     0,   189,
       0,     0,     0,     0,    78,    90,     0,     0,     0,     0,
       0,     0,    61,     0,   122,   120,   126,     0,   110,   111,
      86,     0,   199,     0,    86,     0,     0,    37,    93,     0,
       0,     0,    45,   186,    84,    87,    88,     0,     0,     0,
      98,     0,     0,   102,     0,     0,   117,     0,     0,    86,
       0,     0,   159,    63,     0,     0,     0,    70,     0,     0,
       0,     0,     0,    60,   201,     0,     0,   200,     0,     0,
       0,     0,    66,    97,   103,   104,     0,     0,     0,     0,
       0,     0,    48,     0,    67,     0,    68,     0,     0,   100,
      69,    46,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -273,  -273,  -273,   -96,  -273,  -273,    -7,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,   108,
      55,    10,  -273,  -273,  -178,  -116,   167,  -199,  -273,   293,
    -273,  -273,  -272,  -273,  -273,    18,  -273,  -273,  -273,  -273,
    -273,   175,  -224,  -273,  -273,    58,  -262,  -273,  -273,  -273,
    -273,  -273,  -273,    -6,  -273,  -273,  -273,  -273,   -26,  -273,
    -273,  -273,    81,  -273,  -273,  -273,  -273,  -273,  -273,  -273
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    50,    51,    52,    53,    54,    55,    56,    57,   133,
      58,    59,    60,   357,   392,    61,    62,    63,   107,   189,
     264,   353,    64,    65,    66,   129,   130,   253,    67,   172,
     173,    68,   363,    69,    70,    71,    72,    73,    74,    75,
      76,   279,   280,   281,    77,   268,   269,    78,   271,    79,
      80,   274,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,   243,    91,    92,    93,   143,    94,   287,   379
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     100,   101,   103,   104,   125,   126,   332,   186,   293,   185,
       7,   206,   325,   113,   191,   301,   273,   211,     3,     1,
       2,   177,   275,   201,   181,    97,   326,   131,   205,   134,
     135,   114,   138,   140,   141,   142,   298,   145,   146,     3,
      20,    21,    22,   272,   178,   148,   299,    24,   220,   182,
     114,   115,   116,    29,   187,   338,    95,    30,    31,    32,
     249,   192,   333,   212,   272,    35,   117,   208,   375,   337,
     213,   188,   338,    96,    29,   123,   334,   330,   276,   277,
     209,   278,   218,    36,   255,   117,    98,   258,   259,   174,
     174,   331,   399,   214,   265,   147,   336,   105,   219,    99,
     267,     1,     2,    38,    39,    40,   289,   377,   408,    41,
     106,   332,   411,   295,   364,   203,   386,    45,    46,    47,
      48,    49,    20,    21,    22,   275,   335,   119,   345,    24,
     374,   215,   423,   216,   108,   355,   275,   426,   356,    30,
      31,    32,   346,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   395,   386,   242,   244,   340,   127,   208,   109,
     110,   250,   351,   254,   348,   256,   257,   387,   148,   128,
     292,   276,   277,   330,   278,    38,    39,    40,   111,   124,
     112,    41,   276,   277,   148,   278,   307,   406,   148,    45,
      46,    47,    48,    49,   168,   169,   267,   300,   308,   397,
     208,   118,   304,   148,   208,   120,   208,   307,   208,   144,
     170,   398,   312,   369,   171,   121,   380,   381,   384,   393,
     409,   149,   150,   151,   152,   153,   361,   176,   122,   362,
     310,   311,   160,   161,   162,   163,   164,   165,   148,   251,
     132,   148,   148,   385,   151,   152,   153,   252,   148,   149,
     150,   151,   152,   153,   149,   150,   151,   152,   153,   136,
     160,   161,   162,   163,   164,   165,   166,   341,   342,   179,
     190,   407,   148,   149,   150,   151,   152,   153,   148,   193,
     194,   196,   197,   198,   199,   204,   162,   163,   164,   165,
     242,   359,   418,   419,   200,   420,   421,   128,   202,   365,
     207,   367,   368,   240,   370,   241,   245,   246,   263,   248,
     431,   261,   262,   266,   267,   282,   270,   283,   284,   437,
     285,   286,   439,   378,   290,   306,   396,   313,   382,   297,
     443,   314,   445,   315,   447,   448,   188,   324,   388,   328,
     339,   343,   329,   344,   394,   349,   354,   352,   366,   371,
     410,   376,   148,   325,   383,   391,   413,   389,   390,   323,
     414,   416,   425,   415,   428,   294,   429,   430,   148,   438,
     372,   405,   440,   441,   400,   296,   373,   358,     0,   175,
       0,   417,     0,     0,     0,     0,     0,     0,   422,     0,
     148,     0,     0,     0,   427,     0,     0,     0,     0,     0,
       0,   148,   148,   148,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   148,     0,     0,     0,     0,     0,
     148,     0,   148,     0,     0,     0,   148,     0,   148,     0,
     148,   148,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,     0,
       0,   260,    41,     0,    42,     0,     0,    43,     0,    44,
      45,    46,    47,    48,    49,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,    33,    34,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,     0,     0,   288,    41,     0,    42,     0,     0,
      43,     0,    44,    45,    46,    47,    48,    49,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    40,     0,     0,   291,    41,     0,
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
     305,    41,     0,    42,     0,     0,    43,     0,    44,    45,
      46,    47,    48,    49,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,     0,     0,   316,    41,     0,    42,     0,     0,    43,
       0,    44,    45,    46,    47,    48,    49,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
      33,    34,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,     0,   321,    41,     0,    42,
       0,     0,    43,     0,    44,    45,    46,    47,    48,    49,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,     0,     0,   322,
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
       0,     0,   327,    41,     0,    42,     0,     0,    43,     0,
      44,    45,    46,    47,    48,    49,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,     0,     0,   347,    41,     0,    42,     0,
       0,    43,     0,    44,    45,    46,    47,    48,    49,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,    33,    34,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,     0,     0,   350,    41,
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
       0,   403,    41,     0,    42,     0,     0,    43,     0,    44,
      45,    46,    47,    48,    49,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,    33,    34,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,     0,     0,   412,    41,     0,    42,     0,     0,
      43,     0,    44,    45,    46,    47,    48,    49,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    40,     0,     0,   424,    41,     0,
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
     432,    41,     0,    42,     0,     0,    43,     0,    44,    45,
      46,    47,    48,    49,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,     0,     0,   433,    41,     0,    42,     0,     0,    43,
       0,    44,    45,    46,    47,    48,    49,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
      33,    34,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,     0,   434,    41,     0,    42,
       0,     0,    43,     0,    44,    45,    46,    47,    48,    49,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,     0,     0,   435,
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
       0,     0,   442,    41,     0,    42,     0,     0,    43,     0,
      44,    45,    46,    47,    48,    49,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,     0,     0,   444,    41,     0,    42,     0,
       0,    43,     0,    44,    45,    46,    47,    48,    49,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,    33,    34,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,     0,     0,   446,    41,
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
       0,   449,    41,     0,    42,     0,     0,    43,     0,    44,
      45,    46,    47,    48,    49,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,    33,    34,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,     0,     0,   450,    41,     0,    42,     0,     0,
      43,     0,    44,    45,    46,    47,    48,    49,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    40,     0,     0,   451,    41,     0,
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
     452,    41,     0,    42,     0,     0,    43,     0,    44,    45,
      46,    47,    48,    49,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     1,     2,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,     0,
      35,     0,     0,     0,     0,     0,     0,     0,    20,    21,
      22,     0,     0,     0,     0,    24,     0,     0,    36,     0,
       1,     2,     0,     0,     0,    30,    31,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,    20,    21,    22,    41,     0,    42,     0,    24,    43,
       0,    44,    45,    46,    47,    48,    49,     0,    30,    31,
      32,     0,     0,     0,     0,     0,    35,     0,     0,     1,
       2,    38,    39,    40,     0,     0,     0,    41,     0,     0,
       0,     0,     0,     0,    36,    45,    46,    47,    48,    49,
      20,    21,    22,     0,     0,     0,     0,    24,     0,     0,
       0,     0,     1,     2,    38,    39,    40,    30,    31,    32,
      41,     0,     0,     0,     0,    35,     0,     0,    45,    46,
      47,    48,    49,    20,    21,    22,     0,     0,     0,     0,
      24,     0,     0,    36,     0,     1,     2,     0,     0,     0,
      30,    31,    32,     0,     0,     0,     0,     0,    35,     0,
       0,     0,     0,    38,    39,    40,    20,    21,    22,    41,
       0,     0,     0,    24,     0,     0,    36,   102,    46,    47,
      48,    49,     0,    30,    31,    32,     0,     0,     0,     0,
       0,    35,     0,     0,     0,     0,    38,    39,   137,     0,
       0,     0,    41,     0,     0,     0,     0,     0,     0,    36,
      45,    46,    47,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
      39,   139,     0,     0,     0,    41,     0,     0,     0,     0,
       0,     0,     0,    45,    46,    47,    48,    49,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,     0,     0,     0,     0,
       0,     0,     0,     0,   309,     0,     0,     0,     0,     0,
       0,     0,     0,   317,   318,     0,     0,     0,     0,     0,
     319,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,     0,
       0,     0,     0,     0,   180,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   183,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,     0,     0,     0,     0,     0,   184,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   195,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,     0,     0,     0,     0,     0,
     210,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   401,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,     0,     0,
       0,     0,     0,   402,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   436,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,     0,     0,     0,     0,   217,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   302,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,     0,     0,     0,     0,   303,     0,     0,
       0,     0,     0,     0,     0,     0,   247,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   360,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   320,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   404,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,    30,    31,   268,    27,   207,   105,
       9,   127,    78,    19,    44,   214,   194,    27,     5,     3,
       4,    53,    45,   119,    28,   101,    92,    33,   124,    35,
      36,     5,    38,    39,    40,    41,    91,    43,    44,     5,
      24,    25,    26,    30,    76,    52,   101,    31,   144,    53,
       5,     6,     7,    40,    74,   279,    91,    41,    42,    43,
     176,    91,    78,    73,    30,    49,    40,    78,   330,    92,
      53,    91,   296,    91,    40,     5,    92,    78,   101,   102,
      91,   104,    78,    67,   180,    40,   101,   183,   184,    95,
      96,    92,    91,    76,   190,     0,   274,    91,    94,   101,
     101,     3,     4,    87,    88,    89,   202,    91,   380,    93,
     101,   373,   384,   209,   313,   121,    78,   101,   102,   103,
     104,   105,    24,    25,    26,    45,    92,    91,    78,    31,
     329,   137,    94,   139,   101,    96,    45,   409,    99,    41,
      42,    43,    92,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   361,    78,   170,   171,   282,    89,    78,   101,
     101,   177,    92,   179,   290,   181,   182,    92,   185,   101,
      90,   101,   102,    78,   104,    87,    88,    89,   101,    91,
     101,    93,   101,   102,   201,   104,    78,    92,   205,   101,
     102,   103,   104,   105,    73,    74,   101,   213,    90,    79,
      78,   101,   218,   220,    78,   101,    78,    78,    78,    91,
      89,    91,    90,   319,    93,   101,    90,   343,    90,    90,
      90,    48,    49,    50,    51,    52,    76,    89,   101,    79,
     246,   247,    59,    60,    61,    62,    63,    64,   255,    93,
     101,   258,   259,   349,    50,    51,    52,   101,   265,    48,
      49,    50,    51,    52,    48,    49,    50,    51,    52,   101,
      59,    60,    61,    62,    63,    64,    65,   283,   284,    53,
      91,   377,   289,    48,    49,    50,    51,    52,   295,    91,
      91,   101,   101,   101,     5,   101,    61,    62,    63,    64,
     306,   307,   398,   399,    91,   401,   402,   101,    91,   315,
      76,   317,   318,   101,   320,   101,    92,    78,    36,    92,
     416,   101,   101,   101,   101,    89,   101,    53,    53,   425,
     101,   101,   428,   339,    89,    89,   362,    94,   344,   101,
     436,    82,   438,    53,   440,   441,    91,    76,   354,    91,
      80,    89,    76,    76,   360,    91,    53,   101,    10,    93,
      76,   101,   369,    78,   101,    97,   101,    89,    89,   261,
     101,    91,    91,   101,    91,   208,    90,    90,   385,    91,
     325,   371,    91,    91,   366,   210,   328,   306,    -1,    96,
      -1,   397,    -1,    -1,    -1,    -1,    -1,    -1,   404,    -1,
     407,    -1,    -1,    -1,   410,    -1,    -1,    -1,    -1,    -1,
      -1,   418,   419,   420,   421,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   431,    -1,    -1,    -1,    -1,    -1,
     437,    -1,   439,    -1,    -1,    -1,   443,    -1,   445,    -1,
     447,   448,     3,     4,     5,     6,     7,     8,     9,    -1,
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
      -1,    30,    31,    32,    33,    34,    35,     3,     4,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    31,    -1,    -1,    67,    -1,
       3,     4,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    24,    25,    26,    93,    -1,    95,    -1,    31,    98,
      -1,   100,   101,   102,   103,   104,   105,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,     3,
       4,    87,    88,    89,    -1,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    67,   101,   102,   103,   104,   105,
      24,    25,    26,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,     3,     4,    87,    88,    89,    41,    42,    43,
      93,    -1,    -1,    -1,    -1,    49,    -1,    -1,   101,   102,
     103,   104,   105,    24,    25,    26,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    67,    -1,     3,     4,    -1,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    87,    88,    89,    24,    25,    26,    93,
      -1,    -1,    -1,    31,    -1,    -1,    67,   101,   102,   103,
     104,   105,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    87,    88,    89,    -1,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,    67,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      88,    89,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,   104,   105,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,
      91,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    91,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    91,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66
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
     118,   121,   122,   123,   128,   129,   130,   134,   137,   139,
     140,   141,   142,   143,   144,   145,   146,   150,   153,   155,
     156,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   169,   170,   171,   173,    91,    91,   101,   101,   101,
     159,   159,   101,   159,   159,    91,   101,   124,   101,   101,
     101,   101,   101,   159,     5,     6,     7,    40,   101,    91,
     101,   101,   101,     5,    91,   164,   164,    89,   101,   131,
     132,   159,   101,   115,   159,   159,   101,    89,   159,    89,
     159,   159,   159,   172,    91,   159,   159,     0,   112,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    73,    74,
      89,    93,   135,   136,   159,   135,    89,    53,    76,    53,
      91,    28,    53,    91,    91,   109,    27,    74,    91,   125,
      91,    44,    91,    91,    91,    91,   101,   101,   101,     5,
      91,   109,    91,   159,   101,   109,   131,    76,    78,    91,
      91,    27,    73,    53,    76,   159,   159,    90,    78,    94,
     109,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     101,   101,   159,   168,   159,    92,    78,    80,    92,   131,
     159,    93,   101,   133,   159,   109,   159,   159,   109,   109,
      92,   101,   101,    36,   126,   109,   101,   101,   151,   152,
     101,   154,    30,   130,   157,    45,   101,   102,   104,   147,
     148,   149,    89,    53,    53,   101,   101,   174,    92,   109,
      89,    92,    90,   133,   132,   109,   147,   101,    91,   101,
     159,   133,    90,    90,   159,    92,    89,    78,    90,    94,
     159,   159,    90,    94,    82,    53,    92,    84,    85,    91,
      77,    92,    92,   125,    76,    78,    92,    92,    91,    76,
      78,    92,   152,    78,    92,    92,   130,    92,   148,    80,
     131,   159,   159,    89,    76,    78,    92,    92,   131,    91,
      92,    92,   101,   127,    53,    96,    99,   119,   168,   159,
      80,    76,    79,   138,   133,   159,    10,   159,   159,   109,
     159,    93,   126,   151,   133,   152,   101,    91,   159,   175,
      90,   131,   159,   101,    90,   109,    78,    92,   159,    89,
      89,    97,   120,    90,   159,   133,   164,    79,    91,    91,
     141,    91,    91,    92,    77,   127,    92,   109,   138,    90,
      76,   138,    92,   101,   101,   101,    91,   159,   109,   109,
     109,   109,   159,    94,    92,    91,   138,   159,    91,    90,
      90,   109,    92,    92,    92,    92,    91,   109,    91,   109,
      91,    91,    92,   109,    92,   109,    92,   109,   109,    92,
      92,    92,    92
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
     126,   126,   127,   127,   128,   129,   130,   130,   130,   130,
     130,   131,   131,   131,   132,   132,   133,   133,   133,   134,
     134,   135,   135,   136,   136,   137,   138,   138,   138,   139,
     139,   139,   139,   139,   140,   140,   141,   141,   141,   142,
     143,   143,   143,   143,   143,   144,   145,   146,   147,   147,
     148,   148,   149,   149,   149,   149,   150,   150,   151,   151,
     151,   151,   152,   153,   154,   154,   154,   155,   156,   157,
     157,   157,   158,   158,   159,   159,   159,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   161,   161,   162,   162,
     163,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   165,   166,   166,   167,   167,   168,   168,   168,
     169,   170,   170,   171,   172,   172,   172,   173,   174,   174,
     174,   175
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     1,     1,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     2,     2,     6,     4,     1,
       3,     4,     2,     5,     5,     6,     7,     7,     4,     2,
       2,     2,     3,     2,     4,     3,     5,     1,     3,     3,
       5,     3,     1,     3,     2,     5,     9,    10,    10,    11,
       8,     0,     1,     3,     1,     3,     1,     2,     3,     4,
       4,     0,     1,     3,     5,     4,     0,     2,     2,     4,
       6,     5,     4,     6,     4,     5,     5,     9,     7,     1,
      11,     5,     7,     9,     9,     5,     4,     5,     1,     2,
       3,     3,     1,     1,     1,     1,     5,     7,     0,     1,
       3,     2,     3,     5,     0,     1,     3,     2,     5,     0,
       1,     2,     2,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     5,     7,
       4,     1,     1,     1,     1,     1,     1,     1,     3,     1,
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
#line 117 "src/parser/parser.y"
                                                                  {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2257 "parser.c"
    break;

  case 3: /* program: statement_list  */
#line 129 "src/parser/parser.y"
                   {
        program_root = create_program_node((yyvsp[0].node_list));
    }
#line 2265 "parser.c"
    break;

  case 4: /* statement_list: statement  */
#line 135 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2274 "parser.c"
    break;

  case 5: /* statement_list: statement_list statement  */
#line 139 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2283 "parser.c"
    break;

  case 6: /* unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 145 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_unsafe_node((yyvsp[-1].node_list));
    }
#line 2291 "parser.c"
    break;

  case 7: /* continue_statement: TOKEN_CONTINUE  */
#line 150 "src/parser/parser.y"
                   {
        (yyval.node) = create_continue_node();
    }
#line 2299 "parser.c"
    break;

  case 33: /* statement: expression  */
#line 182 "src/parser/parser.y"
                 {
        (yyval.node) = create_expr_statement((yyvsp[0].node));
    }
#line 2307 "parser.c"
    break;

  case 34: /* sysf_expr: TOKEN_SYSF TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 187 "src/parser/parser.y"
                                                    {
        (yyval.node) = create_sysf_node((yyvsp[-1].node));
    }
#line 2315 "parser.c"
    break;

  case 35: /* sysf_expr: TOKEN_SYSF expression  */
#line 190 "src/parser/parser.y"
                            {
        (yyval.node) = create_sysf_node((yyvsp[0].node));
    }
#line 2323 "parser.c"
    break;

  case 36: /* use_statement: TOKEN_USE use_path  */
#line 197 "src/parser/parser.y"
                       {
        (yyval.node) = create_use_node((yyvsp[0].string), NULL);
    }
#line 2331 "parser.c"
    break;

  case 37: /* use_statement: TOKEN_USE use_path TOKEN_DOUBLE_COLON TOKEN_LBRACE name_list TOKEN_RBRACE  */
#line 201 "src/parser/parser.y"
                                                                                {
        (yyval.node) = create_use_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2339 "parser.c"
    break;

  case 38: /* use_statement: TOKEN_USE use_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 205 "src/parser/parser.y"
                                                   {
        (yyval.node) = create_use_node((yyvsp[-2].string), NULL);
        // Stocker l'alias dans le nœud
        (yyval.node)->use_stmt.alias = strdup((yyvsp[0].string));
    }
#line 2349 "parser.c"
    break;

  case 39: /* use_path: TOKEN_IDENTIFIER  */
#line 213 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2357 "parser.c"
    break;

  case 40: /* use_path: use_path TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 216 "src/parser/parser.y"
                                                   {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 3);
        sprintf(path, "%s::%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2368 "parser.c"
    break;

  case 41: /* sh_expr: TOKEN_SH TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 225 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_sh_node((yyvsp[-1].node));
    }
#line 2376 "parser.c"
    break;

  case 42: /* sh_expr: TOKEN_SH expression  */
#line 228 "src/parser/parser.y"
                          {
        (yyval.node) = create_sh_node((yyvsp[0].node));
    }
#line 2384 "parser.c"
    break;

  case 43: /* nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 234 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_nnl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2392 "parser.c"
    break;

  case 44: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block  */
#line 240 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_try_node((yyvsp[-2].node_list), (yyvsp[0].node), NULL);
    }
#line 2400 "parser.c"
    break;

  case 45: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block  */
#line 243 "src/parser/parser.y"
                                                                                   {
        (yyval.node) = create_try_node((yyvsp[-3].node_list), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2408 "parser.c"
    break;

  case 46: /* catch_block: TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 249 "src/parser/parser.y"
                                                                                                    {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2416 "parser.c"
    break;

  case 47: /* catch_block: TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 252 "src/parser/parser.y"
                                                                                                       {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2424 "parser.c"
    break;

  case 48: /* finally_block: TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 258 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_finally_node((yyvsp[-1].node_list));
    }
#line 2432 "parser.c"
    break;

  case 49: /* throw_statement: TOKEN_THROW expression  */
#line 264 "src/parser/parser.y"
                           {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2440 "parser.c"
    break;

  case 50: /* throw_statement: TOKEN_RAISE expression  */
#line 267 "src/parser/parser.y"
                             {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2448 "parser.c"
    break;

  case 51: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER  */
#line 272 "src/parser/parser.y"
                               {
        (yyval.node) = create_jmp_node((yyvsp[0].string), NULL);
    }
#line 2456 "parser.c"
    break;

  case 52: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression  */
#line 275 "src/parser/parser.y"
                                            {
        (yyval.node) = create_jmp_node((yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2464 "parser.c"
    break;

  case 53: /* import_statement: TOKEN_IMPORT import_path  */
#line 284 "src/parser/parser.y"
                             {
        (yyval.node) = create_import_node((yyvsp[0].string), NULL, NULL);
    }
#line 2472 "parser.c"
    break;

  case 54: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 288 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_import_node((yyvsp[-2].string), (yyvsp[0].string), NULL);
    }
#line 2480 "parser.c"
    break;

  case 55: /* import_statement: TOKEN_IMPORT import_path import_constraints  */
#line 292 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_import_node((yyvsp[-1].string), NULL, (yyvsp[0].node));
    }
#line 2488 "parser.c"
    break;

  case 56: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER import_constraints  */
#line 296 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_import_node((yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2496 "parser.c"
    break;

  case 57: /* import_path: TOKEN_IDENTIFIER  */
#line 303 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2504 "parser.c"
    break;

  case 58: /* import_path: import_path TOKEN_DOT TOKEN_IDENTIFIER  */
#line 306 "src/parser/parser.y"
                                             {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 2);
        sprintf(path, "%s.%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2515 "parser.c"
    break;

  case 59: /* import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE  */
#line 314 "src/parser/parser.y"
                                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2523 "parser.c"
    break;

  case 60: /* import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET  */
#line 320 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_constraints_node("only", (yyvsp[-1].node_list));
    }
#line 2531 "parser.c"
    break;

  case 61: /* import_options: import_options TOKEN_COMMA import_options  */
#line 323 "src/parser/parser.y"
                                                {
        (yyval.node) = merge_constraints((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2539 "parser.c"
    break;

  case 62: /* name_list: TOKEN_IDENTIFIER  */
#line 329 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2548 "parser.c"
    break;

  case 63: /* name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 333 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2557 "parser.c"
    break;

  case 64: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
#line 340 "src/parser/parser.y"
                                  {
        (yyval.node) = create_export_node((yyvsp[0].string));
    }
#line 2565 "parser.c"
    break;

  case 65: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 346 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_packet_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2573 "parser.c"
    break;

  case 66: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 352 "src/parser/parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2581 "parser.c"
    break;

  case 67: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 355 "src/parser/parser.y"
                                                                                                                                    {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2589 "parser.c"
    break;

  case 68: /* function_decl: TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 358 "src/parser/parser.y"
                                                                                                                                      {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        (yyval.node) = node;
    }
#line 2600 "parser.c"
    break;

  case 69: /* function_decl: TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 364 "src/parser/parser.y"
                                                                                                                                                {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        (yyval.node) = node;
    }
#line 2612 "parser.c"
    break;

  case 70: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression  */
#line 371 "src/parser/parser.y"
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node((yyvsp[0].node));
        add_to_node_list(body, return_stmt);
        (yyval.node) = create_function_node((yyvsp[-6].string), (yyvsp[-4].node_list), (yyvsp[-2].node), body);
    }
#line 2623 "parser.c"
    break;

  case 71: /* param_list: %empty  */
#line 380 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2631 "parser.c"
    break;

  case 72: /* param_list: param  */
#line 383 "src/parser/parser.y"
            {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2640 "parser.c"
    break;

  case 73: /* param_list: param_list TOKEN_COMMA param  */
#line 387 "src/parser/parser.y"
                                   {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2649 "parser.c"
    break;

  case 74: /* param: TOKEN_IDENTIFIER  */
#line 394 "src/parser/parser.y"
                     {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 2657 "parser.c"
    break;

  case 75: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 397 "src/parser/parser.y"
                                        {
        (yyval.node) = create_param_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2665 "parser.c"
    break;

  case 76: /* type: TOKEN_IDENTIFIER  */
#line 403 "src/parser/parser.y"
                     {
        (yyval.node) = create_type_node((yyvsp[0].string));
    }
#line 2673 "parser.c"
    break;

  case 77: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
#line 406 "src/parser/parser.y"
                                      {
        (yyval.node) = create_optional_type_node((yyvsp[-1].string));
    }
#line 2681 "parser.c"
    break;

  case 78: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 409 "src/parser/parser.y"
                                         {
        (yyval.node) = create_array_type_node((yyvsp[0].node));
    }
#line 2689 "parser.c"
    break;

  case 79: /* dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 417 "src/parser/parser.y"
                                                      {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2697 "parser.c"
    break;

  case 80: /* dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 420 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2705 "parser.c"
    break;

  case 81: /* dict_entries: %empty  */
#line 426 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2713 "parser.c"
    break;

  case 82: /* dict_entries: dict_entry_list  */
#line 429 "src/parser/parser.y"
                      {
        (yyval.node_list) = (yyvsp[0].node_list);
    }
#line 2721 "parser.c"
    break;

  case 83: /* dict_entry_list: expression TOKEN_FAT_ARROW expression  */
#line 435 "src/parser/parser.y"
                                          {
        (yyval.node_list) = create_node_list();
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyval.node_list), pair);
    }
#line 2731 "parser.c"
    break;

  case 84: /* dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression  */
#line 440 "src/parser/parser.y"
                                                                        {
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyvsp[-4].node_list), pair);
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 2741 "parser.c"
    break;

  case 85: /* dict_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 449 "src/parser/parser.y"
                                                          {
        // Détecter si c'est un accès dictionnaire ou tableau
        // Par défaut, c'est un accès tableau, mais on peut différencier par le type
        // Pour l'instant, on crée un nœud d'accès dictionnaire
        (yyval.node) = create_dict_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2752 "parser.c"
    break;

  case 86: /* return_type: %empty  */
#line 468 "src/parser/parser.y"
                {
        (yyval.node) = NULL;
    }
#line 2760 "parser.c"
    break;

  case 87: /* return_type: TOKEN_COLON type  */
#line 471 "src/parser/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2768 "parser.c"
    break;

  case 88: /* return_type: TOKEN_ARROW primary_expr  */
#line 474 "src/parser/parser.y"
                               {
        // Pour les retours directs: -> expr
        (yyval.node) = create_return_direct_node((yyvsp[0].node));
    }
#line 2777 "parser.c"
    break;

  case 89: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 481 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2785 "parser.c"
    break;

  case 90: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 484 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_let_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2793 "parser.c"
    break;

  case 91: /* let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 487 "src/parser/parser.y"
                                                                   {
        ASTNode* node = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2803 "parser.c"
    break;

  case 92: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 493 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_muts_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2811 "parser.c"
    break;

  case 93: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 496 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_muts_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2819 "parser.c"
    break;

  case 94: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 501 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2827 "parser.c"
    break;

  case 95: /* const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 504 "src/parser/parser.y"
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2838 "parser.c"
    break;

  case 96: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 513 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-1].node_list), NULL);
    }
#line 2846 "parser.c"
    break;

  case 97: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 516 "src/parser/parser.y"
                                                                                                                       {
        (yyval.node) = create_if_node((yyvsp[-7].node), (yyvsp[-5].node_list), (yyvsp[-1].node_list));
    }
#line 2854 "parser.c"
    break;

  case 98: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE if_statement  */
#line 519 "src/parser/parser.y"
                                                                                           {
        // else if -> le else contient un autre if
        ASTNodeList* else_branch = create_node_list();
        add_to_node_list(else_branch, (yyvsp[0].node));
        (yyval.node) = create_if_node((yyvsp[-5].node), (yyvsp[-3].node_list), else_branch);
    }
#line 2865 "parser.c"
    break;

  case 99: /* break_statement: TOKEN_BREAK  */
#line 527 "src/parser/parser.y"
                {
        (yyval.node) = create_break_node();
    }
#line 2873 "parser.c"
    break;

  case 100: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 532 "src/parser/parser.y"
                                                                                                                                                      {
        ASTNode* init = create_let_node((yyvsp[-9].string), NULL, (yyvsp[-7].node));
        ASTNode* cond = (yyvsp[-5].node);
        ASTNode* inc = create_expr_statement((yyvsp[-3].node));
        (yyval.node) = create_for_node(init, cond, inc, (yyvsp[-1].node_list));
    }
#line 2884 "parser.c"
    break;

  case 101: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 538 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2892 "parser.c"
    break;

  case 102: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 541 "src/parser/parser.y"
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
#line 2910 "parser.c"
    break;

  case 103: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 554 "src/parser/parser.y"
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
#line 2930 "parser.c"
    break;

  case 104: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE_INC expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 569 "src/parser/parser.y"
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
#line 2946 "parser.c"
    break;

  case 105: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 584 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2954 "parser.c"
    break;

  case 106: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 590 "src/parser/parser.y"
                                                        {
        (yyval.node) = create_loop_node((yyvsp[-1].node_list));
    }
#line 2962 "parser.c"
    break;

  case 107: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 597 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2970 "parser.c"
    break;

  case 108: /* match_cases: match_case  */
#line 603 "src/parser/parser.y"
               {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2979 "parser.c"
    break;

  case 109: /* match_cases: match_cases match_case  */
#line 607 "src/parser/parser.y"
                             {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2988 "parser.c"
    break;

  case 110: /* match_case: pattern TOKEN_FAT_ARROW expression  */
#line 614 "src/parser/parser.y"
                                       {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2996 "parser.c"
    break;

  case 111: /* match_case: pattern TOKEN_FAT_ARROW block  */
#line 617 "src/parser/parser.y"
                                    {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (ASTNode*)(yyvsp[0].node));
    }
#line 3004 "parser.c"
    break;

  case 112: /* pattern: TOKEN_NUMBER  */
#line 622 "src/parser/parser.y"
                 {
        (yyval.node) = create_pattern_number((yyvsp[0].number));
    }
#line 3012 "parser.c"
    break;

  case 113: /* pattern: TOKEN_STRING  */
#line 625 "src/parser/parser.y"
                   {
        (yyval.node) = create_pattern_string((yyvsp[0].string));
    }
#line 3020 "parser.c"
    break;

  case 114: /* pattern: TOKEN_IDENTIFIER  */
#line 628 "src/parser/parser.y"
                       {
        (yyval.node) = create_pattern_ident((yyvsp[0].string));
    }
#line 3028 "parser.c"
    break;

  case 115: /* pattern: TOKEN_UNDERSCORE  */
#line 631 "src/parser/parser.y"
                       {
        (yyval.node) = create_pattern_wildcard();
    }
#line 3036 "parser.c"
    break;

  case 116: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 637 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_struct_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3044 "parser.c"
    break;

  case 117: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 640 "src/parser/parser.y"
                                                                                                           {
        (yyval.node) = create_struct_extend_node((yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3052 "parser.c"
    break;

  case 118: /* struct_fields: %empty  */
#line 646 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3060 "parser.c"
    break;

  case 119: /* struct_fields: struct_field  */
#line 649 "src/parser/parser.y"
                   {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3069 "parser.c"
    break;

  case 120: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
#line 653 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3078 "parser.c"
    break;

  case 121: /* struct_fields: struct_fields struct_field  */
#line 657 "src/parser/parser.y"
                                 {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3087 "parser.c"
    break;

  case 122: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 664 "src/parser/parser.y"
                                      {
        (yyval.node) = create_field_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 3095 "parser.c"
    break;

  case 123: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
#line 670 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_enum_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3103 "parser.c"
    break;

  case 124: /* enum_variants: %empty  */
#line 676 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3111 "parser.c"
    break;

  case 125: /* enum_variants: TOKEN_IDENTIFIER  */
#line 679 "src/parser/parser.y"
                       {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 3120 "parser.c"
    break;

  case 126: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 683 "src/parser/parser.y"
                                                 {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3129 "parser.c"
    break;

  case 127: /* module_decl: TOKEN_MODULE TOKEN_IDENTIFIER  */
#line 690 "src/parser/parser.y"
                                  {
        // Créer un nœud nil pour éviter l'erreur
        (yyval.node) = create_expr_statement(create_nil_node());
    }
#line 3138 "parser.c"
    break;

  case 128: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
#line 697 "src/parser/parser.y"
                                                                             {
        (yyval.node) = create_impl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3146 "parser.c"
    break;

  case 129: /* function_decl_list: %empty  */
#line 703 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3154 "parser.c"
    break;

  case 130: /* function_decl_list: function_decl  */
#line 706 "src/parser/parser.y"
                    {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3163 "parser.c"
    break;

  case 131: /* function_decl_list: function_decl_list function_decl  */
#line 710 "src/parser/parser.y"
                                       {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3172 "parser.c"
    break;

  case 132: /* return_statement: TOKEN_RETURN expression  */
#line 717 "src/parser/parser.y"
                            {
        (yyval.node) = create_return_node((yyvsp[0].node));
    }
#line 3180 "parser.c"
    break;

  case 133: /* return_statement: TOKEN_RETURN  */
#line 720 "src/parser/parser.y"
                   {
        (yyval.node) = create_return_node(NULL);
    }
#line 3188 "parser.c"
    break;

  case 137: /* binary_expr: expression TOKEN_PLUS expression  */
#line 732 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_ADD, (yyvsp[0].node));
    }
#line 3196 "parser.c"
    break;

  case 138: /* binary_expr: expression TOKEN_MINUS expression  */
#line 735 "src/parser/parser.y"
                                        {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_SUB, (yyvsp[0].node));
    }
#line 3204 "parser.c"
    break;

  case 139: /* binary_expr: expression TOKEN_MULTIPLY expression  */
#line 738 "src/parser/parser.y"
                                           {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
    }
#line 3212 "parser.c"
    break;

  case 140: /* binary_expr: expression TOKEN_DIVIDE expression  */
#line 741 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
    }
#line 3220 "parser.c"
    break;

  case 141: /* binary_expr: expression TOKEN_MODULO expression  */
#line 744 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
    }
#line 3228 "parser.c"
    break;

  case 142: /* binary_expr: expression TOKEN_EQ expression  */
#line 747 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_EQ, (yyvsp[0].node));
    }
#line 3236 "parser.c"
    break;

  case 143: /* binary_expr: expression TOKEN_NEQ expression  */
#line 750 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_NEQ, (yyvsp[0].node));
    }
#line 3244 "parser.c"
    break;

  case 144: /* binary_expr: expression TOKEN_LT expression  */
#line 753 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
    }
#line 3252 "parser.c"
    break;

  case 145: /* binary_expr: expression TOKEN_LTE expression  */
#line 756 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LTE, (yyvsp[0].node));
    }
#line 3260 "parser.c"
    break;

  case 146: /* binary_expr: expression TOKEN_GT expression  */
#line 759 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
    }
#line 3268 "parser.c"
    break;

  case 147: /* binary_expr: expression TOKEN_GTE expression  */
#line 762 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GTE, (yyvsp[0].node));
    }
#line 3276 "parser.c"
    break;

  case 148: /* binary_expr: expression TOKEN_AND expression  */
#line 765 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_AND, (yyvsp[0].node));
    }
#line 3284 "parser.c"
    break;

  case 149: /* binary_expr: expression TOKEN_OR expression  */
#line 768 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_OR, (yyvsp[0].node));
    }
#line 3292 "parser.c"
    break;

  case 150: /* binary_expr: expression TOKEN_ASSIGN expression  */
#line 771 "src/parser/parser.y"
                                         {
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3300 "parser.c"
    break;

  case 151: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
#line 774 "src/parser/parser.y"
                                              {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_ADD_ASSIGN, (yyvsp[0].node));
    }
#line 3308 "parser.c"
    break;

  case 152: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
#line 777 "src/parser/parser.y"
                                               {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_SUB_ASSIGN, (yyvsp[0].node));
    }
#line 3316 "parser.c"
    break;

  case 153: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
#line 780 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MUL_ASSIGN, (yyvsp[0].node));
    }
#line 3324 "parser.c"
    break;

  case 154: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
#line 783 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_DIV_ASSIGN, (yyvsp[0].node));
    }
#line 3332 "parser.c"
    break;

  case 155: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
#line 786 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MOD_ASSIGN, (yyvsp[0].node));
    }
#line 3340 "parser.c"
    break;

  case 156: /* unary_expr: TOKEN_NOT expression  */
#line 792 "src/parser/parser.y"
                         {
        (yyval.node) = create_unary_op(OP_NOT, (yyvsp[0].node));
    }
#line 3348 "parser.c"
    break;

  case 157: /* unary_expr: TOKEN_MINUS expression  */
#line 795 "src/parser/parser.y"
                             {
        (yyval.node) = create_unary_op(OP_NEG, (yyvsp[0].node));
    }
#line 3356 "parser.c"
    break;

  case 158: /* lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 802 "src/parser/parser.y"
                                                                     {
        (yyval.node) = create_lambda_node((yyvsp[-3].node_list), (yyvsp[-1].node_list));
    }
#line 3364 "parser.c"
    break;

  case 159: /* lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 805 "src/parser/parser.y"
                                                                                                 {
        (yyval.node) = create_lambda_node((yyvsp[-4].node_list), (yyvsp[-1].node_list));
    }
#line 3372 "parser.c"
    break;

  case 160: /* array_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 812 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 3380 "parser.c"
    break;

  case 161: /* primary_expr: TOKEN_NUMBER  */
#line 818 "src/parser/parser.y"
                 {
        (yyval.node) = create_number_node((yyvsp[0].number));
    }
#line 3388 "parser.c"
    break;

  case 162: /* primary_expr: TOKEN_FLOAT  */
#line 821 "src/parser/parser.y"
                  {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 3396 "parser.c"
    break;

  case 163: /* primary_expr: TOKEN_STRING  */
#line 824 "src/parser/parser.y"
                   {
        (yyval.node) = create_string_node((yyvsp[0].string));
    }
#line 3404 "parser.c"
    break;

  case 164: /* primary_expr: TOKEN_TRUE  */
#line 827 "src/parser/parser.y"
                 {
        (yyval.node) = create_bool_node(1);
    }
#line 3412 "parser.c"
    break;

  case 165: /* primary_expr: TOKEN_FALSE  */
#line 830 "src/parser/parser.y"
                  {
        (yyval.node) = create_bool_node(0);
    }
#line 3420 "parser.c"
    break;

  case 166: /* primary_expr: TOKEN_NIL  */
#line 833 "src/parser/parser.y"
                {
        (yyval.node) = create_nil_node();
    }
#line 3428 "parser.c"
    break;

  case 167: /* primary_expr: TOKEN_IDENTIFIER  */
#line 836 "src/parser/parser.y"
                       {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 3436 "parser.c"
    break;

  case 168: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 839 "src/parser/parser.y"
                                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3444 "parser.c"
    break;

  case 182: /* f_string: TOKEN_F_STRING  */
#line 858 "src/parser/parser.y"
                   {
        (yyval.node) = parse_f_string((yyvsp[0].string));
    }
#line 3452 "parser.c"
    break;

  case 183: /* member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER  */
#line 864 "src/parser/parser.y"
                                            {
        (yyval.node) = create_member_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3460 "parser.c"
    break;

  case 184: /* member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 867 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_static_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3468 "parser.c"
    break;

  case 185: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 873 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_call_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3476 "parser.c"
    break;

  case 186: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 876 "src/parser/parser.y"
                                                                                               {
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3484 "parser.c"
    break;

  case 187: /* argument_list: %empty  */
#line 882 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3492 "parser.c"
    break;

  case 188: /* argument_list: expression  */
#line 885 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_arg_list();
        add_arg((yyval.node_list), (yyvsp[0].node));
    }
#line 3501 "parser.c"
    break;

  case 189: /* argument_list: argument_list TOKEN_COMMA expression  */
#line 889 "src/parser/parser.y"
                                           {
        add_arg((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3510 "parser.c"
    break;

  case 190: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
#line 896 "src/parser/parser.y"
                                              {
        (yyval.node) = create_array_node((yyvsp[-1].node_list));
    }
#line 3518 "parser.c"
    break;

  case 191: /* await_expr: TOKEN_AWAIT primary_expr  */
#line 911 "src/parser/parser.y"
                             {
        (yyval.node) = create_await_node((yyvsp[0].node));
    }
#line 3526 "parser.c"
    break;

  case 192: /* await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 914 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_await_block_node((yyvsp[-1].node_list));
    }
#line 3534 "parser.c"
    break;

  case 193: /* spawn_expr: TOKEN_SPAWN primary_expr  */
#line 921 "src/parser/parser.y"
                             {
        (yyval.node) = create_spawn_node((yyvsp[0].node));
    }
#line 3542 "parser.c"
    break;

  case 194: /* array_items: %empty  */
#line 933 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3550 "parser.c"
    break;

  case 195: /* array_items: expression  */
#line 936 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3559 "parser.c"
    break;

  case 196: /* array_items: array_items TOKEN_COMMA expression  */
#line 940 "src/parser/parser.y"
                                         {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3568 "parser.c"
    break;

  case 197: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
#line 947 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_struct_init_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3576 "parser.c"
    break;

  case 198: /* struct_init_fields: %empty  */
#line 953 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3584 "parser.c"
    break;

  case 199: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 956 "src/parser/parser.y"
                                              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
    }
#line 3593 "parser.c"
    break;

  case 200: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 960 "src/parser/parser.y"
                                                                             {
        add_to_node_list((yyvsp[-4].node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 3602 "parser.c"
    break;

  case 201: /* block: TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 967 "src/parser/parser.y"
                                             {
        (yyval.node) = (ASTNode*)(yyvsp[-1].node_list);
    }
#line 3610 "parser.c"
    break;


#line 3614 "parser.c"

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

#line 972 "src/parser/parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

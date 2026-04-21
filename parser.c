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
  YYSYMBOL_TOKEN_PLUS = 47,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 48,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MULTIPLY = 49,            /* TOKEN_MULTIPLY  */
  YYSYMBOL_TOKEN_DIVIDE = 50,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 51,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_ASSIGN = 52,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 53,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 54,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 55,     /* TOKEN_MULTIPLY_ASSIGN  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 56,       /* TOKEN_DIVIDE_ASSIGN  */
  YYSYMBOL_TOKEN_MODULO_ASSIGN = 57,       /* TOKEN_MODULO_ASSIGN  */
  YYSYMBOL_TOKEN_EQ = 58,                  /* TOKEN_EQ  */
  YYSYMBOL_TOKEN_NEQ = 59,                 /* TOKEN_NEQ  */
  YYSYMBOL_TOKEN_LT = 60,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LTE = 61,                 /* TOKEN_LTE  */
  YYSYMBOL_TOKEN_GT = 62,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GTE = 63,                 /* TOKEN_GTE  */
  YYSYMBOL_TOKEN_AND = 64,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 65,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_NOT = 66,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_AMP = 67,                 /* TOKEN_AMP  */
  YYSYMBOL_TOKEN_PIPE = 68,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_XOR = 69,                 /* TOKEN_XOR  */
  YYSYMBOL_TOKEN_LSHIFT = 70,              /* TOKEN_LSHIFT  */
  YYSYMBOL_TOKEN_RSHIFT = 71,              /* TOKEN_RSHIFT  */
  YYSYMBOL_TOKEN_DOUBLE_COLON = 72,        /* TOKEN_DOUBLE_COLON  */
  YYSYMBOL_TOKEN_DOT = 73,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_SECURITY = 74,            /* TOKEN_SECURITY  */
  YYSYMBOL_TOKEN_COLON = 75,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_SEMICOLON = 76,           /* TOKEN_SEMICOLON  */
  YYSYMBOL_TOKEN_COMMA = 77,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_ARROW = 78,               /* TOKEN_ARROW  */
  YYSYMBOL_TOKEN_FAT_ARROW = 79,           /* TOKEN_FAT_ARROW  */
  YYSYMBOL_TOKEN_PIPE_FORWARD = 80,        /* TOKEN_PIPE_FORWARD  */
  YYSYMBOL_TOKEN_OPTIONAL = 81,            /* TOKEN_OPTIONAL  */
  YYSYMBOL_TOKEN_COALESCE = 82,            /* TOKEN_COALESCE  */
  YYSYMBOL_TOKEN_RANGE = 83,               /* TOKEN_RANGE  */
  YYSYMBOL_TOKEN_RANGE_INC = 84,           /* TOKEN_RANGE_INC  */
  YYSYMBOL_TOKEN_MUTS = 85,                /* TOKEN_MUTS  */
  YYSYMBOL_TOKEN_SYSF = 86,                /* TOKEN_SYSF  */
  YYSYMBOL_TOKEN_SH = 87,                  /* TOKEN_SH  */
  YYSYMBOL_TOKEN_LPAREN = 88,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 89,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_LBRACE = 90,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 91,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_LBRACKET = 92,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 93,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_TRY = 94,                 /* TOKEN_TRY  */
  YYSYMBOL_TOKEN_CATCH = 95,               /* TOKEN_CATCH  */
  YYSYMBOL_TOKEN_FINALLY = 96,             /* TOKEN_FINALLY  */
  YYSYMBOL_TOKEN_THROW = 97,               /* TOKEN_THROW  */
  YYSYMBOL_TOKEN_EXCEPT = 98,              /* TOKEN_EXCEPT  */
  YYSYMBOL_TOKEN_RAISE = 99,               /* TOKEN_RAISE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 100,         /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_NUMBER = 101,             /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_FLOAT = 102,              /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_STRING = 103,             /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_F_STRING = 104,           /* TOKEN_F_STRING  */
  YYSYMBOL_YYACCEPT = 105,                 /* $accept  */
  YYSYMBOL_switch_statement = 106,         /* switch_statement  */
  YYSYMBOL_program = 107,                  /* program  */
  YYSYMBOL_statement_list = 108,           /* statement_list  */
  YYSYMBOL_unsafe_stmt = 109,              /* unsafe_stmt  */
  YYSYMBOL_continue_statement = 110,       /* continue_statement  */
  YYSYMBOL_statement = 111,                /* statement  */
  YYSYMBOL_sysf_expr = 112,                /* sysf_expr  */
  YYSYMBOL_sh_expr = 113,                  /* sh_expr  */
  YYSYMBOL_nnl_statement = 114,            /* nnl_statement  */
  YYSYMBOL_try_statement = 115,            /* try_statement  */
  YYSYMBOL_catch_block = 116,              /* catch_block  */
  YYSYMBOL_finally_block = 117,            /* finally_block  */
  YYSYMBOL_throw_statement = 118,          /* throw_statement  */
  YYSYMBOL_jmp_statement = 119,            /* jmp_statement  */
  YYSYMBOL_import_statement = 120,         /* import_statement  */
  YYSYMBOL_import_constraints = 121,       /* import_constraints  */
  YYSYMBOL_import_options = 122,           /* import_options  */
  YYSYMBOL_name_list = 123,                /* name_list  */
  YYSYMBOL_export_statement = 124,         /* export_statement  */
  YYSYMBOL_packet_decl = 125,              /* packet_decl  */
  YYSYMBOL_function_decl = 126,            /* function_decl  */
  YYSYMBOL_param_list = 127,               /* param_list  */
  YYSYMBOL_param = 128,                    /* param  */
  YYSYMBOL_type = 129,                     /* type  */
  YYSYMBOL_dict_expr = 130,                /* dict_expr  */
  YYSYMBOL_dict_entries = 131,             /* dict_entries  */
  YYSYMBOL_dict_entry_list = 132,          /* dict_entry_list  */
  YYSYMBOL_dict_access = 133,              /* dict_access  */
  YYSYMBOL_return_type = 134,              /* return_type  */
  YYSYMBOL_let_decl = 135,                 /* let_decl  */
  YYSYMBOL_const_decl = 136,               /* const_decl  */
  YYSYMBOL_if_statement = 137,             /* if_statement  */
  YYSYMBOL_break_statement = 138,          /* break_statement  */
  YYSYMBOL_for_statement = 139,            /* for_statement  */
  YYSYMBOL_while_statement = 140,          /* while_statement  */
  YYSYMBOL_loop_statement = 141,           /* loop_statement  */
  YYSYMBOL_match_statement = 142,          /* match_statement  */
  YYSYMBOL_match_cases = 143,              /* match_cases  */
  YYSYMBOL_match_case = 144,               /* match_case  */
  YYSYMBOL_pattern = 145,                  /* pattern  */
  YYSYMBOL_struct_decl = 146,              /* struct_decl  */
  YYSYMBOL_struct_fields = 147,            /* struct_fields  */
  YYSYMBOL_struct_field = 148,             /* struct_field  */
  YYSYMBOL_enum_decl = 149,                /* enum_decl  */
  YYSYMBOL_enum_variants = 150,            /* enum_variants  */
  YYSYMBOL_module_decl = 151,              /* module_decl  */
  YYSYMBOL_impl_decl = 152,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 153,       /* function_decl_list  */
  YYSYMBOL_return_statement = 154,         /* return_statement  */
  YYSYMBOL_expression = 155,               /* expression  */
  YYSYMBOL_binary_expr = 156,              /* binary_expr  */
  YYSYMBOL_unary_expr = 157,               /* unary_expr  */
  YYSYMBOL_lambda_expr = 158,              /* lambda_expr  */
  YYSYMBOL_array_access = 159,             /* array_access  */
  YYSYMBOL_primary_expr = 160,             /* primary_expr  */
  YYSYMBOL_f_string = 161,                 /* f_string  */
  YYSYMBOL_member_access = 162,            /* member_access  */
  YYSYMBOL_call_expr = 163,                /* call_expr  */
  YYSYMBOL_argument_list = 164,            /* argument_list  */
  YYSYMBOL_array_expr = 165,               /* array_expr  */
  YYSYMBOL_await_expr = 166,               /* await_expr  */
  YYSYMBOL_spawn_expr = 167,               /* spawn_expr  */
  YYSYMBOL_array_items = 168,              /* array_items  */
  YYSYMBOL_struct_expr = 169,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 170,       /* struct_init_fields  */
  YYSYMBOL_block = 171                     /* block  */
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
#define YYFINAL  143
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4025

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  105
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  197
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  449

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   359


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
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   116,   116,   128,   134,   138,   144,   149,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   185,   188,   194,   197,   203,   209,   212,
     218,   221,   227,   233,   236,   241,   244,   250,   253,   259,
     265,   269,   275,   278,   284,   290,   293,   299,   303,   310,
     316,   322,   325,   328,   334,   341,   350,   353,   357,   364,
     367,   373,   376,   379,   387,   390,   396,   399,   405,   410,
     419,   438,   441,   444,   451,   454,   457,   463,   466,   471,
     474,   483,   486,   489,   497,   502,   508,   511,   524,   539,
     554,   560,   567,   573,   577,   584,   587,   592,   595,   598,
     601,   607,   610,   616,   619,   623,   627,   634,   640,   646,
     649,   653,   660,   667,   673,   676,   680,   687,   690,   696,
     697,   698,   702,   705,   708,   711,   714,   717,   720,   723,
     726,   729,   732,   735,   738,   741,   744,   747,   750,   753,
     756,   760,   767,   770,   777,   780,   787,   793,   796,   799,
     802,   805,   808,   811,   814,   817,   818,   819,   820,   821,
     822,   823,   824,   825,   826,   827,   828,   829,   833,   839,
     842,   848,   851,   857,   860,   864,   871,   886,   889,   896,
     908,   911,   915,   922,   928,   931,   935,   942
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
  "TOKEN_UNDERSCORE", "TOKEN_SWITCH", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_MULTIPLY", "TOKEN_DIVIDE", "TOKEN_MODULO", "TOKEN_ASSIGN",
  "TOKEN_PLUS_ASSIGN", "TOKEN_MINUS_ASSIGN", "TOKEN_MULTIPLY_ASSIGN",
  "TOKEN_DIVIDE_ASSIGN", "TOKEN_MODULO_ASSIGN", "TOKEN_EQ", "TOKEN_NEQ",
  "TOKEN_LT", "TOKEN_LTE", "TOKEN_GT", "TOKEN_GTE", "TOKEN_AND",
  "TOKEN_OR", "TOKEN_NOT", "TOKEN_AMP", "TOKEN_PIPE", "TOKEN_XOR",
  "TOKEN_LSHIFT", "TOKEN_RSHIFT", "TOKEN_DOUBLE_COLON", "TOKEN_DOT",
  "TOKEN_SECURITY", "TOKEN_COLON", "TOKEN_SEMICOLON", "TOKEN_COMMA",
  "TOKEN_ARROW", "TOKEN_FAT_ARROW", "TOKEN_PIPE_FORWARD", "TOKEN_OPTIONAL",
  "TOKEN_COALESCE", "TOKEN_RANGE", "TOKEN_RANGE_INC", "TOKEN_MUTS",
  "TOKEN_SYSF", "TOKEN_SH", "TOKEN_LPAREN", "TOKEN_RPAREN", "TOKEN_LBRACE",
  "TOKEN_RBRACE", "TOKEN_LBRACKET", "TOKEN_RBRACKET", "TOKEN_TRY",
  "TOKEN_CATCH", "TOKEN_FINALLY", "TOKEN_THROW", "TOKEN_EXCEPT",
  "TOKEN_RAISE", "TOKEN_IDENTIFIER", "TOKEN_NUMBER", "TOKEN_FLOAT",
  "TOKEN_STRING", "TOKEN_F_STRING", "$accept", "switch_statement",
  "program", "statement_list", "unsafe_stmt", "continue_statement",
  "statement", "sysf_expr", "sh_expr", "nnl_statement", "try_statement",
  "catch_block", "finally_block", "throw_statement", "jmp_statement",
  "import_statement", "import_constraints", "import_options", "name_list",
  "export_statement", "packet_decl", "function_decl", "param_list",
  "param", "type", "dict_expr", "dict_entries", "dict_entry_list",
  "dict_access", "return_type", "let_decl", "const_decl", "if_statement",
  "break_statement", "for_statement", "while_statement", "loop_statement",
  "match_statement", "match_cases", "match_case", "pattern", "struct_decl",
  "struct_fields", "struct_field", "enum_decl", "enum_variants",
  "module_decl", "impl_decl", "function_decl_list", "return_statement",
  "expression", "binary_expr", "unary_expr", "lambda_expr", "array_access",
  "primary_expr", "f_string", "member_access", "call_expr",
  "argument_list", "array_expr", "await_expr", "spawn_expr", "array_items",
  "struct_expr", "struct_init_fields", "block", YY_NULLPTR
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
     355,   356,   357,   358,   359
};
#endif

#define YYPACT_NINF (-286)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2967,   -51,   -41,    -8,    -3,    37,   398,   398,  3015,   398,
     -16,  -286,  -286,   -49,    38,    59,    64,    66,    67,   398,
    -286,  -286,  -286,    36,    69,     3,    94,    98,   112,   211,
      22,  3145,   100,   398,   398,   398,   120,  3080,  3109,   398,
     398,   128,   398,   398,  -286,  -286,  -286,  -286,  -286,  -286,
     219,  2967,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
    3911,  -286,  -286,  -286,  -286,    44,  -286,  -286,  -286,  -286,
    -286,  -286,  -286,   398,   398,   133,    19,   171,  3911,  3294,
      31,  3338,  3382,  2967,   -38,   -11,  -286,   147,   -32,   157,
     158,  3426,   159,   160,   162,   252,   173,  2967,   176,   398,
    -286,   167,  2967,    44,    44,   168,   194,     9,  -286,  3470,
     360,   188,    29,   398,  3911,   398,  3911,  3646,  3911,   -70,
    2967,  3911,  3911,  -286,  -286,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   398,   398,   398,   398,   398,
     398,   398,   398,   398,   398,   170,   172,   398,   398,   180,
     197,  3775,   184,   168,   398,     6,   398,  2967,   398,   398,
    2967,  2967,   519,   203,  -286,   181,   -43,   247,  -286,  2967,
     186,   187,   189,    15,   -28,   196,   238,   239,   193,   195,
     621,  2967,  3911,   206,   723,    26,     6,   168,  2967,   -28,
     398,     6,  3689,  3732,  -286,   398,  -286,   825,   360,   360,
     188,   188,   188,   199,   199,   199,   199,   199,   199,   129,
     129,   179,   179,   179,   179,   623,  3945,   641,   208,  -286,
    3911,   118,  3203,  -286,   398,   398,  -286,   119,   537,   210,
     218,   253,   537,   927,  3250,  3809,  1029,  1131,  -286,   204,
    -286,   212,  -286,   235,    30,  1233,   223,   240,   -39,  -286,
    -286,    43,    16,  -286,    10,  -286,  -286,  -286,  -286,   -34,
    -286,   237,   168,   398,   398,   226,   245,    83,  -286,  1335,
     168,  -286,   231,  -286,  -286,  1437,   -23,   537,   270,  -286,
    -286,  3911,    33,   398,   398,  -286,  -286,  3843,  3911,    55,
       6,  -286,   398,   313,   398,   398,  2967,   398,  -286,  -286,
    -286,  -286,   233,   247,  -286,  -286,   187,     6,   187,  -286,
    -286,   227,  -286,  -286,  -286,  -286,  -286,   276,   122,   537,
     537,   168,   398,   228,  -286,  -286,   125,  2967,  -286,  -286,
     398,   241,   242,   230,   126,  3911,   398,     6,  3145,   127,
    -286,   537,    -1,  3514,  3558,  1539,  3877,   234,   256,     5,
    -286,  -286,  -286,  2967,  3911,  -286,    55,   136,  3911,   260,
      55,  1641,   537,   243,   246,   248,  -286,  -286,  3911,  -286,
      44,   398,  2967,  2967,  -286,  2967,  2967,  -286,   398,  -286,
       7,  -286,  1743,   249,    55,   398,   250,  -286,   258,   259,
    2967,  3911,  1845,  1947,  2049,  2151,  3602,   251,  -286,  -286,
    2967,   255,  3911,  2967,   262,   263,  2253,  -286,  -286,  -286,
    -286,  2967,  -286,  2355,  2967,  2457,  2967,  2967,  -286,  2559,
    -286,  2661,  -286,  2763,  2865,  -286,  -286,  -286,  -286
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,   128,     0,     0,     0,
       0,    94,     7,     0,     0,     0,     0,     0,     0,     0,
     160,   161,   162,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,     0,     0,     0,     0,     0,
     190,     0,     0,     0,   163,   157,   158,   159,   178,    19,
       0,     3,    27,    10,     4,   174,   175,    11,    14,    15,
      12,     8,     9,    16,    17,   167,   166,    22,    24,    25,
      23,    26,    28,    29,    30,    18,    20,    13,    21,    31,
      32,   129,   130,   171,   172,   131,   177,   170,   165,   168,
     173,   176,   169,    76,    76,     0,     0,     0,   127,     0,
     163,     0,     0,     0,     0,    47,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
     122,     0,     0,   187,   189,    66,    69,     0,    67,     0,
     153,   152,     0,     0,    34,     0,    36,     0,   191,     0,
       0,    43,    44,     1,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   183,     0,     0,
      77,     0,     0,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,     0,     0,     0,    53,     0,
       0,   113,   119,   124,     0,     0,     0,     0,     0,   194,
       0,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,     0,   186,     0,   132,   133,
     134,   135,   136,   145,   146,   147,   148,   149,   150,   137,
     138,   139,   140,   141,   142,   143,   144,   151,   180,   179,
     184,     0,     0,    74,     0,     0,    75,     0,    84,     0,
      71,     0,    89,     0,     0,     0,     0,     0,   101,     0,
      52,     0,    50,     0,     0,     0,     0,     0,     0,   114,
     120,     0,     0,   125,     0,   110,   109,   107,   108,     0,
     103,     0,    66,     0,     0,     0,     0,     0,     6,     0,
      66,   188,     0,    70,    68,     0,     0,    87,     0,    33,
      35,   192,     0,   183,     0,   181,    80,     0,    78,    81,
       0,    72,     0,    91,     0,     0,     0,     0,    96,   100,
      49,    51,     0,     0,    54,    60,   113,     0,     0,   111,
     116,     0,   118,   123,   126,   102,   104,     0,     0,    86,
      90,    66,     0,     0,   193,    37,     0,     0,   154,     2,
       0,     0,     0,    38,     0,   185,     0,     0,     0,     0,
      73,    85,     0,     0,     0,     0,     0,     0,    56,     0,
     117,   115,   121,     0,   105,   106,    81,     0,   195,     0,
      81,     0,    88,     0,     0,     0,    39,   182,    79,    82,
      83,     0,     0,     0,    93,     0,     0,    97,     0,    57,
       0,   112,     0,     0,    81,     0,     0,   155,     0,     0,
       0,    65,     0,     0,     0,     0,     0,     0,    55,   197,
       0,     0,   196,     0,     0,     0,     0,    61,    92,    98,
      99,     0,    58,     0,     0,     0,     0,     0,    42,     0,
      62,     0,    63,     0,     0,    95,    64,    40,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -286,  -286,  -286,    84,  -286,  -286,    -7,  -286,  -286,  -286,
    -286,  -286,  -286,  -286,  -286,  -286,  -286,    14,  -286,  -286,
    -286,  -184,  -119,   134,  -192,  -286,   261,  -286,  -286,  -285,
    -286,  -286,   -13,  -286,  -286,  -286,  -286,  -286,   145,  -194,
    -286,  -286,    34,  -258,  -286,  -286,  -286,  -286,  -286,  -286,
      -6,  -286,  -286,  -286,  -286,   -26,  -286,  -286,  -286,    53,
    -286,  -286,  -286,  -286,  -286,  -286,  -286
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,   353,   386,    59,    60,    61,   188,   264,   400,    62,
      63,    64,   127,   128,   251,    65,   169,   170,    66,   359,
      67,    68,    69,    70,    71,    72,    73,    74,   279,   280,
     281,    75,   268,   269,    76,   271,    77,    78,   274,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,   241,
      89,    90,    91,   139,    92,   287,   375
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      98,    99,   101,   102,   123,   124,   205,   215,     7,   273,
     330,   275,   190,   111,   293,     3,   185,   275,   186,   298,
       3,   112,   275,   216,   104,     1,     2,   129,   130,   131,
     261,   134,   136,   137,   138,   183,   141,   142,   328,    93,
     272,   112,   113,   114,   144,   272,    20,    21,    22,    94,
      29,   105,   329,    24,   247,    29,   115,   335,   191,   178,
     262,   267,   184,    30,    31,    32,   276,   277,   349,   278,
     371,   174,   276,   277,   103,   278,   115,   276,   277,   187,
     278,   210,   328,   179,   417,   336,   207,   171,   171,   393,
     334,   403,    95,   117,   175,   406,   401,    96,   249,   208,
     418,   333,   336,   207,   211,   267,   250,   323,    37,    38,
      39,   330,   122,   202,    40,   292,   165,   166,   360,   421,
     331,   324,    44,    45,    46,    47,    48,   212,   351,   213,
     357,   352,   167,   358,   332,   370,   168,    97,   106,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   107,
     343,   240,   242,   338,   108,   389,   109,   110,   248,   116,
     252,   346,   254,   255,   344,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   182,   125,   158,
     159,   160,   161,   144,   118,   304,   207,   144,   119,   207,
     126,   200,   207,   304,   297,   391,   204,   305,   309,   301,
     144,   376,   120,   207,   380,   387,   121,   392,   140,   143,
     132,   173,   377,   176,   217,   404,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   189,   307,   308,
     150,   151,   152,   153,   154,   155,   144,   192,   193,   144,
     144,    -1,    -1,    -1,    -1,    -1,    -1,   198,   144,   195,
     196,   253,   197,   199,   256,   257,   201,   203,   126,   206,
     238,   243,   239,   265,   244,   246,   259,   339,   340,     1,
       2,   260,   144,   263,   282,   289,   266,   267,   144,   270,
     283,   284,   295,   285,   290,   286,   303,   240,   355,   311,
      20,    21,    22,   310,   320,   312,   361,    24,   363,   364,
     322,   366,   321,   326,   341,   327,   337,    30,    31,    32,
     342,   347,   350,   362,    34,   367,   385,   372,   379,   383,
     384,   374,   390,   323,   399,   405,   378,   368,   410,   420,
     423,   294,    35,   408,   382,   434,   409,   424,   425,   394,
     388,   432,   436,   437,   296,   172,   354,     0,   144,     0,
     369,     0,    37,    38,    39,     0,   373,     0,    40,     0,
       0,     0,     0,     0,   144,     0,    44,    45,    46,    47,
      48,     0,     0,     0,     0,   411,     0,     0,     0,     0,
       0,     0,   416,     0,     0,   144,     0,     0,     0,   422,
     365,     1,     2,     0,     0,   144,   144,   144,   144,   147,
     148,   149,   150,   151,   152,   153,   154,   155,     0,   144,
       0,     0,    20,    21,    22,     0,   144,     0,   144,    24,
       0,   381,   144,     0,   144,     0,   144,   144,     0,    30,
      31,    32,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   402,     0,     0,
       0,     0,     0,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   412,   413,     0,   414,
     415,     0,     0,     0,    37,    38,    39,     0,     0,     0,
      40,     0,     0,     0,   426,     0,     0,     0,    44,    45,
      46,    47,    48,     0,   433,     0,     0,   435,     0,     0,
       0,     0,     0,     0,     0,   439,     0,     0,   441,     0,
     443,   444,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,    35,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,     0,    36,    37,    38,    39,     0,     0,
     258,    40,     0,    41,     0,     0,    42,   164,    43,    44,
      45,    46,    47,    48,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,     0,    34,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,    35,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,    36,    37,    38,    39,
       0,     0,   288,    40,     0,    41,     0,     0,    42,     0,
      43,    44,    45,    46,    47,    48,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,    37,
      38,    39,     0,     0,   291,    40,     0,    41,     0,     0,
      42,     0,    43,    44,    45,    46,    47,    48,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    37,    38,    39,     0,     0,   302,    40,     0,    41,
       0,     0,    42,     0,    43,    44,    45,    46,    47,    48,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,    37,    38,    39,     0,     0,   313,    40,
       0,    41,     0,     0,    42,     0,    43,    44,    45,    46,
      47,    48,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,    39,     0,     0,
     318,    40,     0,    41,     0,     0,    42,     0,    43,    44,
      45,    46,    47,    48,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    37,    38,    39,
       0,     0,   319,    40,     0,    41,     0,     0,    42,     0,
      43,    44,    45,    46,    47,    48,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,    37,
      38,    39,     0,     0,   325,    40,     0,    41,     0,     0,
      42,     0,    43,    44,    45,    46,    47,    48,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    37,    38,    39,     0,     0,   345,    40,     0,    41,
       0,     0,    42,     0,    43,    44,    45,    46,    47,    48,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,    37,    38,    39,     0,     0,   348,    40,
       0,    41,     0,     0,    42,     0,    43,    44,    45,    46,
      47,    48,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,    39,     0,     0,
     397,    40,     0,    41,     0,     0,    42,     0,    43,    44,
      45,    46,    47,    48,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    37,    38,    39,
       0,     0,   407,    40,     0,    41,     0,     0,    42,     0,
      43,    44,    45,    46,    47,    48,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,    37,
      38,    39,     0,     0,   419,    40,     0,    41,     0,     0,
      42,     0,    43,    44,    45,    46,    47,    48,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    37,    38,    39,     0,     0,   427,    40,     0,    41,
       0,     0,    42,     0,    43,    44,    45,    46,    47,    48,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,    37,    38,    39,     0,     0,   428,    40,
       0,    41,     0,     0,    42,     0,    43,    44,    45,    46,
      47,    48,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,    39,     0,     0,
     429,    40,     0,    41,     0,     0,    42,     0,    43,    44,
      45,    46,    47,    48,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    37,    38,    39,
       0,     0,   430,    40,     0,    41,     0,     0,    42,     0,
      43,    44,    45,    46,    47,    48,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,    37,
      38,    39,     0,     0,   438,    40,     0,    41,     0,     0,
      42,     0,    43,    44,    45,    46,    47,    48,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    37,    38,    39,     0,     0,   440,    40,     0,    41,
       0,     0,    42,     0,    43,    44,    45,    46,    47,    48,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,    37,    38,    39,     0,     0,   442,    40,
       0,    41,     0,     0,    42,     0,    43,    44,    45,    46,
      47,    48,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,    39,     0,     0,
     445,    40,     0,    41,     0,     0,    42,     0,    43,    44,
      45,    46,    47,    48,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    37,    38,    39,
       0,     0,   446,    40,     0,    41,     0,     0,    42,     0,
      43,    44,    45,    46,    47,    48,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,    37,
      38,    39,     0,     0,   447,    40,     0,    41,     0,     0,
      42,     0,    43,    44,    45,    46,    47,    48,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    37,    38,    39,     0,     0,   448,    40,     0,    41,
       0,     0,    42,     0,    43,    44,    45,    46,    47,    48,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,     0,    34,     0,     0,     1,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,     0,     0,     0,     0,     0,    20,
      21,    22,     0,     0,     0,     0,    24,     0,     0,     0,
       0,     0,    36,    37,    38,    39,    30,    31,    32,    40,
       0,    41,     0,    34,    42,     0,    43,    44,    45,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,     1,     2,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    20,    21,    22,    40,     0,     0,
       0,    24,     1,     2,     0,   100,    45,    46,    47,    48,
       0,    30,    31,    32,     0,     0,     0,     0,    34,     0,
       0,     0,     0,    20,    21,    22,     0,     0,     0,     0,
      24,     0,     0,     0,     0,     0,    35,     0,     1,     2,
      30,    31,    32,     0,     0,     0,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    38,   133,    20,
      21,    22,    40,     0,     0,    35,    24,     0,     0,     0,
      44,    45,    46,    47,    48,     0,    30,    31,    32,     0,
       0,     0,     0,     0,     0,    37,    38,   135,     0,     0,
       0,    40,     0,     0,     0,     0,     0,     0,     0,    44,
      45,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,     0,     0,     0,    40,     0,     0,
       0,     0,     0,     0,     0,    44,    45,    46,    47,    48,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   164,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   306,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,   314,   315,     0,     0,     0,     0,     0,
     316,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   177,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   181,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   194,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     164,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     209,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   395,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   396,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   431,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   164,     0,     0,     0,
       0,     0,     0,     0,     0,   214,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   164,
       0,     0,     0,     0,     0,     0,     0,     0,   299,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,     0,     0,     0,     0,     0,     0,     0,
       0,   300,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   245,   164,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   317,     0,     0,     0,   164,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   356,   164,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   398,     0,     0,     0,   164,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   164,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   164
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,    30,    31,   125,    77,     9,   193,
     268,    45,    44,    19,   206,     5,    27,    45,    29,   211,
       5,     5,    45,    93,    73,     3,     4,    33,    34,    35,
      73,    37,    38,    39,    40,    73,    42,    43,    77,    90,
      30,     5,     6,     7,    51,    30,    24,    25,    26,    90,
      40,   100,    91,    31,   173,    40,    40,    91,    90,    28,
     103,   100,   100,    41,    42,    43,   100,   101,    91,   103,
     328,    52,   100,   101,    90,   103,    40,   100,   101,    90,
     103,    52,    77,    52,    77,   279,    77,    93,    94,    90,
     274,   376,   100,    90,    75,   380,    91,   100,    92,    90,
      93,    91,   296,    77,    75,   100,   100,    77,    86,    87,
      88,   369,    90,   119,    92,    89,    72,    73,   310,   404,
      77,    91,   100,   101,   102,   103,   104,   133,    95,   135,
      75,    98,    88,    78,    91,   327,    92,   100,   100,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   100,
      77,   167,   168,   282,   100,   357,   100,   100,   174,   100,
     176,   290,   178,   179,    91,   182,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,   103,    88,    60,
      61,    62,    63,   200,   100,    77,    77,   204,   100,    77,
     100,   117,    77,    77,   210,    78,   122,    89,    89,   215,
     217,    89,   100,    77,    89,    89,     5,    90,    90,     0,
     100,    88,   341,    52,   140,    89,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    90,   244,   245,
      52,    53,    54,    55,    56,    57,   253,    90,    90,   256,
     257,    52,    53,    54,    55,    56,    57,     5,   265,   100,
     100,   177,   100,    90,   180,   181,    90,   100,   100,    75,
     100,    91,   100,   189,    77,    91,    73,   283,   284,     3,
       4,   100,   289,    36,    88,   201,   100,   100,   295,   100,
      52,    52,   208,   100,    88,   100,    88,   303,   304,    81,
      24,    25,    26,    93,   100,    52,   312,    31,   314,   315,
      75,   317,   100,    90,    88,    75,    79,    41,    42,    43,
      75,    90,    52,    10,    48,    92,    96,   100,   100,    88,
      88,   337,   358,    77,   100,    75,   342,   323,    90,    90,
      90,   207,    66,   100,   350,    90,   100,    89,    89,   362,
     356,   100,    90,    90,   209,    94,   303,    -1,   365,    -1,
     326,    -1,    86,    87,    88,    -1,    90,    -1,    92,    -1,
      -1,    -1,    -1,    -1,   381,    -1,   100,   101,   102,   103,
     104,    -1,    -1,    -1,    -1,   391,    -1,    -1,    -1,    -1,
      -1,    -1,   398,    -1,    -1,   402,    -1,    -1,    -1,   405,
     316,     3,     4,    -1,    -1,   412,   413,   414,   415,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,   426,
      -1,    -1,    24,    25,    26,    -1,   433,    -1,   435,    31,
      -1,   347,   439,    -1,   441,    -1,   443,   444,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   392,   393,    -1,   395,
     396,    -1,    -1,    -1,    86,    87,    88,    -1,    -1,    -1,
      92,    -1,    -1,    -1,   410,    -1,    -1,    -1,   100,   101,
     102,   103,   104,    -1,   420,    -1,    -1,   423,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   431,    -1,    -1,   434,    -1,
     436,   437,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    66,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    -1,    85,    86,    87,    88,    -1,    -1,
      91,    92,    -1,    94,    -1,    -1,    97,    80,    99,   100,
     101,   102,   103,   104,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    -1,    48,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    66,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    85,    86,    87,    88,
      -1,    -1,    91,    92,    -1,    94,    -1,    -1,    97,    -1,
      99,   100,   101,   102,   103,   104,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      87,    88,    -1,    -1,    91,    92,    -1,    94,    -1,    -1,
      97,    -1,    99,   100,   101,   102,   103,   104,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    87,    88,    -1,    -1,    91,    92,    -1,    94,
      -1,    -1,    97,    -1,    99,   100,   101,   102,   103,   104,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    -1,    -1,    91,    92,
      -1,    94,    -1,    -1,    97,    -1,    99,   100,   101,   102,
     103,   104,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    87,    88,    -1,    -1,
      91,    92,    -1,    94,    -1,    -1,    97,    -1,    99,   100,
     101,   102,   103,   104,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,
      -1,    -1,    91,    92,    -1,    94,    -1,    -1,    97,    -1,
      99,   100,   101,   102,   103,   104,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      87,    88,    -1,    -1,    91,    92,    -1,    94,    -1,    -1,
      97,    -1,    99,   100,   101,   102,   103,   104,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    87,    88,    -1,    -1,    91,    92,    -1,    94,
      -1,    -1,    97,    -1,    99,   100,   101,   102,   103,   104,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    -1,    -1,    91,    92,
      -1,    94,    -1,    -1,    97,    -1,    99,   100,   101,   102,
     103,   104,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    87,    88,    -1,    -1,
      91,    92,    -1,    94,    -1,    -1,    97,    -1,    99,   100,
     101,   102,   103,   104,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,
      -1,    -1,    91,    92,    -1,    94,    -1,    -1,    97,    -1,
      99,   100,   101,   102,   103,   104,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      87,    88,    -1,    -1,    91,    92,    -1,    94,    -1,    -1,
      97,    -1,    99,   100,   101,   102,   103,   104,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    87,    88,    -1,    -1,    91,    92,    -1,    94,
      -1,    -1,    97,    -1,    99,   100,   101,   102,   103,   104,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    -1,    -1,    91,    92,
      -1,    94,    -1,    -1,    97,    -1,    99,   100,   101,   102,
     103,   104,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    87,    88,    -1,    -1,
      91,    92,    -1,    94,    -1,    -1,    97,    -1,    99,   100,
     101,   102,   103,   104,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,
      -1,    -1,    91,    92,    -1,    94,    -1,    -1,    97,    -1,
      99,   100,   101,   102,   103,   104,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      87,    88,    -1,    -1,    91,    92,    -1,    94,    -1,    -1,
      97,    -1,    99,   100,   101,   102,   103,   104,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    87,    88,    -1,    -1,    91,    92,    -1,    94,
      -1,    -1,    97,    -1,    99,   100,   101,   102,   103,   104,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    -1,    -1,    91,    92,
      -1,    94,    -1,    -1,    97,    -1,    99,   100,   101,   102,
     103,   104,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    87,    88,    -1,    -1,
      91,    92,    -1,    94,    -1,    -1,    97,    -1,    99,   100,
     101,   102,   103,   104,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,    88,
      -1,    -1,    91,    92,    -1,    94,    -1,    -1,    97,    -1,
      99,   100,   101,   102,   103,   104,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      87,    88,    -1,    -1,    91,    92,    -1,    94,    -1,    -1,
      97,    -1,    99,   100,   101,   102,   103,   104,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    87,    88,    -1,    -1,    91,    92,    -1,    94,
      -1,    -1,    97,    -1,    99,   100,   101,   102,   103,   104,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    -1,    48,    -1,    -1,     3,     4,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    85,    86,    87,    88,    41,    42,    43,    92,
      -1,    94,    -1,    48,    97,    -1,    99,   100,   101,   102,
     103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,     3,     4,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    24,    25,    26,    92,    -1,    -1,
      -1,    31,     3,     4,    -1,   100,   101,   102,   103,   104,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    66,    -1,     3,     4,
      41,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,    24,
      25,    26,    92,    -1,    -1,    66,    31,    -1,    -1,    -1,
     100,   101,   102,   103,   104,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,
     101,   102,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    -1,    -1,    -1,    92,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   100,   101,   102,   103,   104,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,
      90,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    80,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    80,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    80,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    40,
      41,    42,    43,    46,    48,    66,    85,    86,    87,    88,
      92,    94,    97,    99,   100,   101,   102,   103,   104,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   118,
     119,   120,   124,   125,   126,   130,   133,   135,   136,   137,
     138,   139,   140,   141,   142,   146,   149,   151,   152,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   165,
     166,   167,   169,    90,    90,   100,   100,   100,   155,   155,
     100,   155,   155,    90,    73,   100,   100,   100,   100,   100,
     100,   155,     5,     6,     7,    40,   100,    90,   100,   100,
     100,     5,    90,   160,   160,    88,   100,   127,   128,   155,
     155,   155,   100,    88,   155,    88,   155,   155,   155,   168,
      90,   155,   155,     0,   111,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    80,    72,    73,    88,    92,   131,
     132,   155,   131,    88,    52,    75,    52,    90,    28,    52,
      90,    90,   108,    73,   100,    27,    29,    90,   121,    90,
      44,    90,    90,    90,    90,   100,   100,   100,     5,    90,
     108,    90,   155,   100,   108,   127,    75,    77,    90,    90,
      52,    75,   155,   155,    89,    77,    93,   108,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   100,   100,
     155,   164,   155,    91,    77,    79,    91,   127,   155,    92,
     100,   129,   155,   108,   155,   155,   108,   108,    91,    73,
     100,    73,   103,    36,   122,   108,   100,   100,   147,   148,
     100,   150,    30,   126,   153,    45,   100,   101,   103,   143,
     144,   145,    88,    52,    52,   100,   100,   170,    91,   108,
      88,    91,    89,   129,   128,   108,   143,   155,   129,    89,
      89,   155,    91,    88,    77,    89,    93,   155,   155,    89,
      93,    81,    52,    91,    83,    84,    90,    76,    91,    91,
     100,   100,    75,    77,    91,    91,    90,    75,    77,    91,
     148,    77,    91,    91,   126,    91,   144,    79,   127,   155,
     155,    88,    75,    77,    91,    91,   127,    90,    91,    91,
      52,    95,    98,   116,   164,   155,    79,    75,    78,   134,
     129,   155,    10,   155,   155,   108,   155,    92,   122,   147,
     129,   148,   100,    90,   155,   171,    89,   127,   155,   100,
      89,   108,   155,    88,    88,    96,   117,    89,   155,   129,
     160,    78,    90,    90,   137,    90,    90,    91,    76,   100,
     123,    91,   108,   134,    89,    75,   134,    91,   100,   100,
      90,   155,   108,   108,   108,   108,   155,    77,    93,    91,
      90,   134,   155,    90,    89,    89,   108,    91,    91,    91,
      91,    90,   100,   108,    90,   108,    90,    90,    91,   108,
      91,   108,    91,   108,   108,    91,    91,    91,    91
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   105,   106,   107,   108,   108,   109,   110,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   112,   112,   113,   113,   114,   115,   115,
     116,   116,   117,   118,   118,   119,   119,   120,   120,   120,
     120,   120,   120,   120,   121,   122,   122,   123,   123,   124,
     125,   126,   126,   126,   126,   126,   127,   127,   127,   128,
     128,   129,   129,   129,   130,   130,   131,   131,   132,   132,
     133,   134,   134,   134,   135,   135,   135,   135,   135,   136,
     136,   137,   137,   137,   138,   139,   139,   139,   139,   139,
     140,   141,   142,   143,   143,   144,   144,   145,   145,   145,
     145,   146,   146,   147,   147,   147,   147,   148,   149,   150,
     150,   150,   151,   152,   153,   153,   153,   154,   154,   155,
     155,   155,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   157,   157,   158,   158,   159,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   161,   162,
     162,   163,   163,   164,   164,   164,   165,   166,   166,   167,
     168,   168,   168,   169,   170,   170,   170,   171
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     1,     1,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     2,     4,     2,     5,     5,     6,
       7,     7,     4,     2,     2,     2,     3,     2,     3,     5,
       4,     5,     4,     3,     3,     5,     3,     1,     3,     2,
       5,     9,    10,    10,    11,     8,     0,     1,     3,     1,
       3,     1,     2,     3,     4,     4,     0,     1,     3,     5,
       4,     0,     2,     2,     4,     6,     5,     4,     6,     4,
       5,     5,     9,     7,     1,    11,     5,     7,     9,     9,
       5,     4,     5,     1,     2,     3,     3,     1,     1,     1,
       1,     5,     7,     0,     1,     3,     2,     3,     5,     0,
       1,     3,     2,     5,     0,     1,     2,     2,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     5,     7,     4,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     4,     6,     0,     1,     3,     3,     2,     4,     2,
       0,     1,     3,     5,     0,     3,     5,     3
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
#line 116 "src/parser/parser.y"
                                                                  {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2302 "parser.c"
    break;

  case 3: /* program: statement_list  */
#line 128 "src/parser/parser.y"
                   {
        program_root = create_program_node((yyvsp[0].node_list));
    }
#line 2310 "parser.c"
    break;

  case 4: /* statement_list: statement  */
#line 134 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2319 "parser.c"
    break;

  case 5: /* statement_list: statement_list statement  */
#line 138 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2328 "parser.c"
    break;

  case 6: /* unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 144 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_unsafe_node((yyvsp[-1].node_list));
    }
#line 2336 "parser.c"
    break;

  case 7: /* continue_statement: TOKEN_CONTINUE  */
#line 149 "src/parser/parser.y"
                   {
        (yyval.node) = create_continue_node();
    }
#line 2344 "parser.c"
    break;

  case 32: /* statement: expression  */
#line 180 "src/parser/parser.y"
                 {
        (yyval.node) = create_expr_statement((yyvsp[0].node));
    }
#line 2352 "parser.c"
    break;

  case 33: /* sysf_expr: TOKEN_SYSF TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 185 "src/parser/parser.y"
                                                    {
        (yyval.node) = create_sysf_node((yyvsp[-1].node));
    }
#line 2360 "parser.c"
    break;

  case 34: /* sysf_expr: TOKEN_SYSF expression  */
#line 188 "src/parser/parser.y"
                            {
        (yyval.node) = create_sysf_node((yyvsp[0].node));
    }
#line 2368 "parser.c"
    break;

  case 35: /* sh_expr: TOKEN_SH TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 194 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_sh_node((yyvsp[-1].node));
    }
#line 2376 "parser.c"
    break;

  case 36: /* sh_expr: TOKEN_SH expression  */
#line 197 "src/parser/parser.y"
                          {
        (yyval.node) = create_sh_node((yyvsp[0].node));
    }
#line 2384 "parser.c"
    break;

  case 37: /* nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 203 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_nnl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2392 "parser.c"
    break;

  case 38: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block  */
#line 209 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_try_node((yyvsp[-2].node_list), (yyvsp[0].node), NULL);
    }
#line 2400 "parser.c"
    break;

  case 39: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block  */
#line 212 "src/parser/parser.y"
                                                                                   {
        (yyval.node) = create_try_node((yyvsp[-3].node_list), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2408 "parser.c"
    break;

  case 40: /* catch_block: TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 218 "src/parser/parser.y"
                                                                                                    {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2416 "parser.c"
    break;

  case 41: /* catch_block: TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 221 "src/parser/parser.y"
                                                                                                       {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2424 "parser.c"
    break;

  case 42: /* finally_block: TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 227 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_finally_node((yyvsp[-1].node_list));
    }
#line 2432 "parser.c"
    break;

  case 43: /* throw_statement: TOKEN_THROW expression  */
#line 233 "src/parser/parser.y"
                           {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2440 "parser.c"
    break;

  case 44: /* throw_statement: TOKEN_RAISE expression  */
#line 236 "src/parser/parser.y"
                             {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2448 "parser.c"
    break;

  case 45: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER  */
#line 241 "src/parser/parser.y"
                               {
        (yyval.node) = create_jmp_node((yyvsp[0].string), NULL);
    }
#line 2456 "parser.c"
    break;

  case 46: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression  */
#line 244 "src/parser/parser.y"
                                            {
        (yyval.node) = create_jmp_node((yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2464 "parser.c"
    break;

  case 47: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER  */
#line 250 "src/parser/parser.y"
                                  {
        (yyval.node) = create_import_node((yyvsp[0].string), NULL, NULL);
    }
#line 2472 "parser.c"
    break;

  case 48: /* import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_IDENTIFIER  */
#line 253 "src/parser/parser.y"
                                              {
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "./%s", (yyvsp[0].string));
        (yyval.node) = create_import_node(path, NULL, NULL);
        free(path);
    }
#line 2483 "parser.c"
    break;

  case 49: /* import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_DOT TOKEN_DOT TOKEN_IDENTIFIER  */
#line 259 "src/parser/parser.y"
                                                                  {
        char* path = malloc(strlen((yyvsp[0].string)) + 4);
        sprintf(path, "../%s", (yyvsp[0].string));
        (yyval.node) = create_import_node(path, NULL, NULL);
        free(path);
    }
#line 2494 "parser.c"
    break;

  case 50: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_STRING  */
#line 265 "src/parser/parser.y"
                                                            {
        (yyval.node) = create_import_node((yyvsp[0].string), (yyvsp[-2].string), NULL);
    }
#line 2502 "parser.c"
    break;

  case 51: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_DOT TOKEN_IDENTIFIER  */
#line 269 "src/parser/parser.y"
                                                                          {
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "./%s", (yyvsp[0].string));
        (yyval.node) = create_import_node(path, (yyvsp[-3].string), NULL);
        free(path);
    }
#line 2513 "parser.c"
    break;

  case 52: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_AS TOKEN_IDENTIFIER  */
#line 275 "src/parser/parser.y"
                                                              {
        (yyval.node) = create_import_node((yyvsp[-2].string), (yyvsp[0].string), NULL);
    }
#line 2521 "parser.c"
    break;

  case 53: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER import_constraints  */
#line 278 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_import_node((yyvsp[-1].string), NULL, (yyvsp[0].node));
    }
#line 2529 "parser.c"
    break;

  case 54: /* import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE  */
#line 284 "src/parser/parser.y"
                                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2537 "parser.c"
    break;

  case 55: /* import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET  */
#line 290 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_constraints_node("only", (yyvsp[-1].node_list));
    }
#line 2545 "parser.c"
    break;

  case 56: /* import_options: import_options TOKEN_COMMA import_options  */
#line 293 "src/parser/parser.y"
                                                {
        (yyval.node) = merge_constraints((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2553 "parser.c"
    break;

  case 57: /* name_list: TOKEN_IDENTIFIER  */
#line 299 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2562 "parser.c"
    break;

  case 58: /* name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 303 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2571 "parser.c"
    break;

  case 59: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
#line 310 "src/parser/parser.y"
                                  {
        (yyval.node) = create_export_node((yyvsp[0].string));
    }
#line 2579 "parser.c"
    break;

  case 60: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 316 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_packet_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2587 "parser.c"
    break;

  case 61: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 322 "src/parser/parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2595 "parser.c"
    break;

  case 62: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 325 "src/parser/parser.y"
                                                                                                                                    {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2603 "parser.c"
    break;

  case 63: /* function_decl: TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 328 "src/parser/parser.y"
                                                                                                                                      {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        (yyval.node) = node;
    }
#line 2614 "parser.c"
    break;

  case 64: /* function_decl: TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 334 "src/parser/parser.y"
                                                                                                                                                {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        (yyval.node) = node;
    }
#line 2626 "parser.c"
    break;

  case 65: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression  */
#line 341 "src/parser/parser.y"
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node((yyvsp[0].node));
        add_to_node_list(body, return_stmt);
        (yyval.node) = create_function_node((yyvsp[-6].string), (yyvsp[-4].node_list), (yyvsp[-2].node), body);
    }
#line 2637 "parser.c"
    break;

  case 66: /* param_list: %empty  */
#line 350 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2645 "parser.c"
    break;

  case 67: /* param_list: param  */
#line 353 "src/parser/parser.y"
            {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2654 "parser.c"
    break;

  case 68: /* param_list: param_list TOKEN_COMMA param  */
#line 357 "src/parser/parser.y"
                                   {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2663 "parser.c"
    break;

  case 69: /* param: TOKEN_IDENTIFIER  */
#line 364 "src/parser/parser.y"
                     {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 2671 "parser.c"
    break;

  case 70: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 367 "src/parser/parser.y"
                                        {
        (yyval.node) = create_param_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2679 "parser.c"
    break;

  case 71: /* type: TOKEN_IDENTIFIER  */
#line 373 "src/parser/parser.y"
                     {
        (yyval.node) = create_type_node((yyvsp[0].string));
    }
#line 2687 "parser.c"
    break;

  case 72: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
#line 376 "src/parser/parser.y"
                                      {
        (yyval.node) = create_optional_type_node((yyvsp[-1].string));
    }
#line 2695 "parser.c"
    break;

  case 73: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 379 "src/parser/parser.y"
                                         {
        (yyval.node) = create_array_type_node((yyvsp[0].node));
    }
#line 2703 "parser.c"
    break;

  case 74: /* dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 387 "src/parser/parser.y"
                                                      {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2711 "parser.c"
    break;

  case 75: /* dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 390 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2719 "parser.c"
    break;

  case 76: /* dict_entries: %empty  */
#line 396 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2727 "parser.c"
    break;

  case 77: /* dict_entries: dict_entry_list  */
#line 399 "src/parser/parser.y"
                      {
        (yyval.node_list) = (yyvsp[0].node_list);
    }
#line 2735 "parser.c"
    break;

  case 78: /* dict_entry_list: expression TOKEN_FAT_ARROW expression  */
#line 405 "src/parser/parser.y"
                                          {
        (yyval.node_list) = create_node_list();
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyval.node_list), pair);
    }
#line 2745 "parser.c"
    break;

  case 79: /* dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression  */
#line 410 "src/parser/parser.y"
                                                                        {
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyvsp[-4].node_list), pair);
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 2755 "parser.c"
    break;

  case 80: /* dict_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 419 "src/parser/parser.y"
                                                          {
        // Détecter si c'est un accès dictionnaire ou tableau
        // Par défaut, c'est un accès tableau, mais on peut différencier par le type
        // Pour l'instant, on crée un nœud d'accès dictionnaire
        (yyval.node) = create_dict_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2766 "parser.c"
    break;

  case 81: /* return_type: %empty  */
#line 438 "src/parser/parser.y"
                {
        (yyval.node) = NULL;
    }
#line 2774 "parser.c"
    break;

  case 82: /* return_type: TOKEN_COLON type  */
#line 441 "src/parser/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2782 "parser.c"
    break;

  case 83: /* return_type: TOKEN_ARROW primary_expr  */
#line 444 "src/parser/parser.y"
                               {
        // Pour les retours directs: -> expr
        (yyval.node) = create_return_direct_node((yyvsp[0].node));
    }
#line 2791 "parser.c"
    break;

  case 84: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 451 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2799 "parser.c"
    break;

  case 85: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 454 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_let_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2807 "parser.c"
    break;

  case 86: /* let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 457 "src/parser/parser.y"
                                                                   {
        ASTNode* node = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2817 "parser.c"
    break;

  case 87: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 463 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_muts_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2825 "parser.c"
    break;

  case 88: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 466 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_muts_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2833 "parser.c"
    break;

  case 89: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 471 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2841 "parser.c"
    break;

  case 90: /* const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 474 "src/parser/parser.y"
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2852 "parser.c"
    break;

  case 91: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 483 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-1].node_list), NULL);
    }
#line 2860 "parser.c"
    break;

  case 92: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 486 "src/parser/parser.y"
                                                                                                                       {
        (yyval.node) = create_if_node((yyvsp[-7].node), (yyvsp[-5].node_list), (yyvsp[-1].node_list));
    }
#line 2868 "parser.c"
    break;

  case 93: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE if_statement  */
#line 489 "src/parser/parser.y"
                                                                                           {
        // else if -> le else contient un autre if
        ASTNodeList* else_branch = create_node_list();
        add_to_node_list(else_branch, (yyvsp[0].node));
        (yyval.node) = create_if_node((yyvsp[-5].node), (yyvsp[-3].node_list), else_branch);
    }
#line 2879 "parser.c"
    break;

  case 94: /* break_statement: TOKEN_BREAK  */
#line 497 "src/parser/parser.y"
                {
        (yyval.node) = create_break_node();
    }
#line 2887 "parser.c"
    break;

  case 95: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 502 "src/parser/parser.y"
                                                                                                                                                      {
        ASTNode* init = create_let_node((yyvsp[-9].string), NULL, (yyvsp[-7].node));
        ASTNode* cond = (yyvsp[-5].node);
        ASTNode* inc = create_expr_statement((yyvsp[-3].node));
        (yyval.node) = create_for_node(init, cond, inc, (yyvsp[-1].node_list));
    }
#line 2898 "parser.c"
    break;

  case 96: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 508 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2906 "parser.c"
    break;

  case 97: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 511 "src/parser/parser.y"
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
#line 2924 "parser.c"
    break;

  case 98: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 524 "src/parser/parser.y"
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
#line 2944 "parser.c"
    break;

  case 99: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE_INC expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 539 "src/parser/parser.y"
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
#line 2960 "parser.c"
    break;

  case 100: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 554 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2968 "parser.c"
    break;

  case 101: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 560 "src/parser/parser.y"
                                                        {
        (yyval.node) = create_loop_node((yyvsp[-1].node_list));
    }
#line 2976 "parser.c"
    break;

  case 102: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 567 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2984 "parser.c"
    break;

  case 103: /* match_cases: match_case  */
#line 573 "src/parser/parser.y"
               {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2993 "parser.c"
    break;

  case 104: /* match_cases: match_cases match_case  */
#line 577 "src/parser/parser.y"
                             {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3002 "parser.c"
    break;

  case 105: /* match_case: pattern TOKEN_FAT_ARROW expression  */
#line 584 "src/parser/parser.y"
                                       {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3010 "parser.c"
    break;

  case 106: /* match_case: pattern TOKEN_FAT_ARROW block  */
#line 587 "src/parser/parser.y"
                                    {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (ASTNode*)(yyvsp[0].node));
    }
#line 3018 "parser.c"
    break;

  case 107: /* pattern: TOKEN_NUMBER  */
#line 592 "src/parser/parser.y"
                 {
        (yyval.node) = create_pattern_number((yyvsp[0].number));
    }
#line 3026 "parser.c"
    break;

  case 108: /* pattern: TOKEN_STRING  */
#line 595 "src/parser/parser.y"
                   {
        (yyval.node) = create_pattern_string((yyvsp[0].string));
    }
#line 3034 "parser.c"
    break;

  case 109: /* pattern: TOKEN_IDENTIFIER  */
#line 598 "src/parser/parser.y"
                       {
        (yyval.node) = create_pattern_ident((yyvsp[0].string));
    }
#line 3042 "parser.c"
    break;

  case 110: /* pattern: TOKEN_UNDERSCORE  */
#line 601 "src/parser/parser.y"
                       {
        (yyval.node) = create_pattern_wildcard();
    }
#line 3050 "parser.c"
    break;

  case 111: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 607 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_struct_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3058 "parser.c"
    break;

  case 112: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 610 "src/parser/parser.y"
                                                                                                           {
        (yyval.node) = create_struct_extend_node((yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3066 "parser.c"
    break;

  case 113: /* struct_fields: %empty  */
#line 616 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3074 "parser.c"
    break;

  case 114: /* struct_fields: struct_field  */
#line 619 "src/parser/parser.y"
                   {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3083 "parser.c"
    break;

  case 115: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
#line 623 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3092 "parser.c"
    break;

  case 116: /* struct_fields: struct_fields struct_field  */
#line 627 "src/parser/parser.y"
                                 {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3101 "parser.c"
    break;

  case 117: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 634 "src/parser/parser.y"
                                      {
        (yyval.node) = create_field_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 3109 "parser.c"
    break;

  case 118: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
#line 640 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_enum_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3117 "parser.c"
    break;

  case 119: /* enum_variants: %empty  */
#line 646 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3125 "parser.c"
    break;

  case 120: /* enum_variants: TOKEN_IDENTIFIER  */
#line 649 "src/parser/parser.y"
                       {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 3134 "parser.c"
    break;

  case 121: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 653 "src/parser/parser.y"
                                                 {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3143 "parser.c"
    break;

  case 122: /* module_decl: TOKEN_MODULE TOKEN_IDENTIFIER  */
#line 660 "src/parser/parser.y"
                                  {
        // Créer un nœud nil pour éviter l'erreur
        (yyval.node) = create_expr_statement(create_nil_node());
    }
#line 3152 "parser.c"
    break;

  case 123: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
#line 667 "src/parser/parser.y"
                                                                             {
        (yyval.node) = create_impl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3160 "parser.c"
    break;

  case 124: /* function_decl_list: %empty  */
#line 673 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3168 "parser.c"
    break;

  case 125: /* function_decl_list: function_decl  */
#line 676 "src/parser/parser.y"
                    {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3177 "parser.c"
    break;

  case 126: /* function_decl_list: function_decl_list function_decl  */
#line 680 "src/parser/parser.y"
                                       {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3186 "parser.c"
    break;

  case 127: /* return_statement: TOKEN_RETURN expression  */
#line 687 "src/parser/parser.y"
                            {
        (yyval.node) = create_return_node((yyvsp[0].node));
    }
#line 3194 "parser.c"
    break;

  case 128: /* return_statement: TOKEN_RETURN  */
#line 690 "src/parser/parser.y"
                   {
        (yyval.node) = create_return_node(NULL);
    }
#line 3202 "parser.c"
    break;

  case 132: /* binary_expr: expression TOKEN_PLUS expression  */
#line 702 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_ADD, (yyvsp[0].node));
    }
#line 3210 "parser.c"
    break;

  case 133: /* binary_expr: expression TOKEN_MINUS expression  */
#line 705 "src/parser/parser.y"
                                        {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_SUB, (yyvsp[0].node));
    }
#line 3218 "parser.c"
    break;

  case 134: /* binary_expr: expression TOKEN_MULTIPLY expression  */
#line 708 "src/parser/parser.y"
                                           {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
    }
#line 3226 "parser.c"
    break;

  case 135: /* binary_expr: expression TOKEN_DIVIDE expression  */
#line 711 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
    }
#line 3234 "parser.c"
    break;

  case 136: /* binary_expr: expression TOKEN_MODULO expression  */
#line 714 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
    }
#line 3242 "parser.c"
    break;

  case 137: /* binary_expr: expression TOKEN_EQ expression  */
#line 717 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_EQ, (yyvsp[0].node));
    }
#line 3250 "parser.c"
    break;

  case 138: /* binary_expr: expression TOKEN_NEQ expression  */
#line 720 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_NEQ, (yyvsp[0].node));
    }
#line 3258 "parser.c"
    break;

  case 139: /* binary_expr: expression TOKEN_LT expression  */
#line 723 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
    }
#line 3266 "parser.c"
    break;

  case 140: /* binary_expr: expression TOKEN_LTE expression  */
#line 726 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LTE, (yyvsp[0].node));
    }
#line 3274 "parser.c"
    break;

  case 141: /* binary_expr: expression TOKEN_GT expression  */
#line 729 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
    }
#line 3282 "parser.c"
    break;

  case 142: /* binary_expr: expression TOKEN_GTE expression  */
#line 732 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GTE, (yyvsp[0].node));
    }
#line 3290 "parser.c"
    break;

  case 143: /* binary_expr: expression TOKEN_AND expression  */
#line 735 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_AND, (yyvsp[0].node));
    }
#line 3298 "parser.c"
    break;

  case 144: /* binary_expr: expression TOKEN_OR expression  */
#line 738 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_OR, (yyvsp[0].node));
    }
#line 3306 "parser.c"
    break;

  case 145: /* binary_expr: expression TOKEN_ASSIGN expression  */
#line 741 "src/parser/parser.y"
                                         {
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3314 "parser.c"
    break;

  case 146: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
#line 744 "src/parser/parser.y"
                                              {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_ADD_ASSIGN, (yyvsp[0].node));
    }
#line 3322 "parser.c"
    break;

  case 147: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
#line 747 "src/parser/parser.y"
                                               {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_SUB_ASSIGN, (yyvsp[0].node));
    }
#line 3330 "parser.c"
    break;

  case 148: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
#line 750 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MUL_ASSIGN, (yyvsp[0].node));
    }
#line 3338 "parser.c"
    break;

  case 149: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
#line 753 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_DIV_ASSIGN, (yyvsp[0].node));
    }
#line 3346 "parser.c"
    break;

  case 150: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
#line 756 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MOD_ASSIGN, (yyvsp[0].node));
    }
#line 3354 "parser.c"
    break;

  case 151: /* binary_expr: expression TOKEN_PIPE_FORWARD expression  */
#line 760 "src/parser/parser.y"
                                               {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_PIPE, (yyvsp[0].node));
    }
#line 3362 "parser.c"
    break;

  case 152: /* unary_expr: TOKEN_NOT expression  */
#line 767 "src/parser/parser.y"
                         {
        (yyval.node) = create_unary_op(OP_NOT, (yyvsp[0].node));
    }
#line 3370 "parser.c"
    break;

  case 153: /* unary_expr: TOKEN_MINUS expression  */
#line 770 "src/parser/parser.y"
                             {
        (yyval.node) = create_unary_op(OP_NEG, (yyvsp[0].node));
    }
#line 3378 "parser.c"
    break;

  case 154: /* lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 777 "src/parser/parser.y"
                                                                     {
        (yyval.node) = create_lambda_node((yyvsp[-3].node_list), (yyvsp[-1].node_list));
    }
#line 3386 "parser.c"
    break;

  case 155: /* lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 780 "src/parser/parser.y"
                                                                                                 {
        (yyval.node) = create_lambda_node((yyvsp[-4].node_list), (yyvsp[-1].node_list));
    }
#line 3394 "parser.c"
    break;

  case 156: /* array_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 787 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 3402 "parser.c"
    break;

  case 157: /* primary_expr: TOKEN_NUMBER  */
#line 793 "src/parser/parser.y"
                 {
        (yyval.node) = create_number_node((yyvsp[0].number));
    }
#line 3410 "parser.c"
    break;

  case 158: /* primary_expr: TOKEN_FLOAT  */
#line 796 "src/parser/parser.y"
                  {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 3418 "parser.c"
    break;

  case 159: /* primary_expr: TOKEN_STRING  */
#line 799 "src/parser/parser.y"
                   {
        (yyval.node) = create_string_node((yyvsp[0].string));
    }
#line 3426 "parser.c"
    break;

  case 160: /* primary_expr: TOKEN_TRUE  */
#line 802 "src/parser/parser.y"
                 {
        (yyval.node) = create_bool_node(1);
    }
#line 3434 "parser.c"
    break;

  case 161: /* primary_expr: TOKEN_FALSE  */
#line 805 "src/parser/parser.y"
                  {
        (yyval.node) = create_bool_node(0);
    }
#line 3442 "parser.c"
    break;

  case 162: /* primary_expr: TOKEN_NIL  */
#line 808 "src/parser/parser.y"
                {
        (yyval.node) = create_nil_node();
    }
#line 3450 "parser.c"
    break;

  case 163: /* primary_expr: TOKEN_IDENTIFIER  */
#line 811 "src/parser/parser.y"
                       {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 3458 "parser.c"
    break;

  case 164: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 814 "src/parser/parser.y"
                                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3466 "parser.c"
    break;

  case 178: /* f_string: TOKEN_F_STRING  */
#line 833 "src/parser/parser.y"
                   {
        (yyval.node) = parse_f_string((yyvsp[0].string));
    }
#line 3474 "parser.c"
    break;

  case 179: /* member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER  */
#line 839 "src/parser/parser.y"
                                            {
        (yyval.node) = create_member_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3482 "parser.c"
    break;

  case 180: /* member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 842 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_static_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3490 "parser.c"
    break;

  case 181: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 848 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_call_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3498 "parser.c"
    break;

  case 182: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 851 "src/parser/parser.y"
                                                                                               {
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3506 "parser.c"
    break;

  case 183: /* argument_list: %empty  */
#line 857 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3514 "parser.c"
    break;

  case 184: /* argument_list: expression  */
#line 860 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_arg_list();
        add_arg((yyval.node_list), (yyvsp[0].node));
    }
#line 3523 "parser.c"
    break;

  case 185: /* argument_list: argument_list TOKEN_COMMA expression  */
#line 864 "src/parser/parser.y"
                                           {
        add_arg((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3532 "parser.c"
    break;

  case 186: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
#line 871 "src/parser/parser.y"
                                              {
        (yyval.node) = create_array_node((yyvsp[-1].node_list));
    }
#line 3540 "parser.c"
    break;

  case 187: /* await_expr: TOKEN_AWAIT primary_expr  */
#line 886 "src/parser/parser.y"
                             {
        (yyval.node) = create_await_node((yyvsp[0].node));
    }
#line 3548 "parser.c"
    break;

  case 188: /* await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 889 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_await_block_node((yyvsp[-1].node_list));
    }
#line 3556 "parser.c"
    break;

  case 189: /* spawn_expr: TOKEN_SPAWN primary_expr  */
#line 896 "src/parser/parser.y"
                             {
        (yyval.node) = create_spawn_node((yyvsp[0].node));
    }
#line 3564 "parser.c"
    break;

  case 190: /* array_items: %empty  */
#line 908 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3572 "parser.c"
    break;

  case 191: /* array_items: expression  */
#line 911 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3581 "parser.c"
    break;

  case 192: /* array_items: array_items TOKEN_COMMA expression  */
#line 915 "src/parser/parser.y"
                                         {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3590 "parser.c"
    break;

  case 193: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
#line 922 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_struct_init_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3598 "parser.c"
    break;

  case 194: /* struct_init_fields: %empty  */
#line 928 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3606 "parser.c"
    break;

  case 195: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 931 "src/parser/parser.y"
                                              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
    }
#line 3615 "parser.c"
    break;

  case 196: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 935 "src/parser/parser.y"
                                                                             {
        add_to_node_list((yyvsp[-4].node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 3624 "parser.c"
    break;

  case 197: /* block: TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 942 "src/parser/parser.y"
                                             {
        (yyval.node) = (ASTNode*)(yyvsp[-1].node_list);
    }
#line 3632 "parser.c"
    break;


#line 3636 "parser.c"

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

#line 947 "src/parser/parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

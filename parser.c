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
  YYSYMBOL_ternary_expr = 108,             /* ternary_expr  */
  YYSYMBOL_program = 109,                  /* program  */
  YYSYMBOL_statement_list = 110,           /* statement_list  */
  YYSYMBOL_unsafe_stmt = 111,              /* unsafe_stmt  */
  YYSYMBOL_continue_statement = 112,       /* continue_statement  */
  YYSYMBOL_statement = 113,                /* statement  */
  YYSYMBOL_sysf_expr = 114,                /* sysf_expr  */
  YYSYMBOL_use_statement = 115,            /* use_statement  */
  YYSYMBOL_use_path = 116,                 /* use_path  */
  YYSYMBOL_sh_expr = 117,                  /* sh_expr  */
  YYSYMBOL_nnl_statement = 118,            /* nnl_statement  */
  YYSYMBOL_try_statement = 119,            /* try_statement  */
  YYSYMBOL_catch_block = 120,              /* catch_block  */
  YYSYMBOL_finally_block = 121,            /* finally_block  */
  YYSYMBOL_throw_statement = 122,          /* throw_statement  */
  YYSYMBOL_jmp_statement = 123,            /* jmp_statement  */
  YYSYMBOL_import_statement = 124,         /* import_statement  */
  YYSYMBOL_import_path_tail = 125,         /* import_path_tail  */
  YYSYMBOL_import_path = 126,              /* import_path  */
  YYSYMBOL_import_constraints = 127,       /* import_constraints  */
  YYSYMBOL_import_options = 128,           /* import_options  */
  YYSYMBOL_name_list = 129,                /* name_list  */
  YYSYMBOL_export_statement = 130,         /* export_statement  */
  YYSYMBOL_export_list = 131,              /* export_list  */
  YYSYMBOL_export_item = 132,              /* export_item  */
  YYSYMBOL_import_impl_list = 133,         /* import_impl_list  */
  YYSYMBOL_import_impl_item = 134,         /* import_impl_item  */
  YYSYMBOL_packet_decl = 135,              /* packet_decl  */
  YYSYMBOL_function_decl = 136,            /* function_decl  */
  YYSYMBOL_param_list = 137,               /* param_list  */
  YYSYMBOL_param = 138,                    /* param  */
  YYSYMBOL_type = 139,                     /* type  */
  YYSYMBOL_dict_expr = 140,                /* dict_expr  */
  YYSYMBOL_dict_entries = 141,             /* dict_entries  */
  YYSYMBOL_dict_entry_list = 142,          /* dict_entry_list  */
  YYSYMBOL_bracket_access = 143,           /* bracket_access  */
  YYSYMBOL_return_type = 144,              /* return_type  */
  YYSYMBOL_let_decl = 145,                 /* let_decl  */
  YYSYMBOL_const_decl = 146,               /* const_decl  */
  YYSYMBOL_if_statement = 147,             /* if_statement  */
  YYSYMBOL_break_statement = 148,          /* break_statement  */
  YYSYMBOL_for_statement = 149,            /* for_statement  */
  YYSYMBOL_while_statement = 150,          /* while_statement  */
  YYSYMBOL_loop_statement = 151,           /* loop_statement  */
  YYSYMBOL_match_statement = 152,          /* match_statement  */
  YYSYMBOL_match_cases = 153,              /* match_cases  */
  YYSYMBOL_match_case = 154,               /* match_case  */
  YYSYMBOL_pattern = 155,                  /* pattern  */
  YYSYMBOL_array_patterns = 156,           /* array_patterns  */
  YYSYMBOL_struct_decl = 157,              /* struct_decl  */
  YYSYMBOL_struct_fields = 158,            /* struct_fields  */
  YYSYMBOL_struct_field = 159,             /* struct_field  */
  YYSYMBOL_enum_decl = 160,                /* enum_decl  */
  YYSYMBOL_enum_variants = 161,            /* enum_variants  */
  YYSYMBOL_module_decl = 162,              /* module_decl  */
  YYSYMBOL_impl_decl = 163,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 164,       /* function_decl_list  */
  YYSYMBOL_return_statement = 165,         /* return_statement  */
  YYSYMBOL_expression = 166,               /* expression  */
  YYSYMBOL_binary_expr = 167,              /* binary_expr  */
  YYSYMBOL_unary_expr = 168,               /* unary_expr  */
  YYSYMBOL_lambda_expr = 169,              /* lambda_expr  */
  YYSYMBOL_primary_expr = 170,             /* primary_expr  */
  YYSYMBOL_f_string = 171,                 /* f_string  */
  YYSYMBOL_member_access = 172,            /* member_access  */
  YYSYMBOL_call_expr = 173,                /* call_expr  */
  YYSYMBOL_argument_list = 174,            /* argument_list  */
  YYSYMBOL_array_expr = 175,               /* array_expr  */
  YYSYMBOL_await_expr = 176,               /* await_expr  */
  YYSYMBOL_spawn_expr = 177,               /* spawn_expr  */
  YYSYMBOL_array_items = 178,              /* array_items  */
  YYSYMBOL_struct_expr = 179,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 180,       /* struct_init_fields  */
  YYSYMBOL_block = 181                     /* block  */
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
#define YYFINAL  155
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4078

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  223
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  502

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
       0,   123,   123,   128,   135,   141,   145,   151,   156,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   193,   196,   203,   207,   211,
     219,   222,   231,   234,   240,   246,   249,   255,   258,   264,
     270,   273,   278,   281,   290,   294,   298,   302,   306,   312,
     321,   324,   333,   336,   342,   351,   357,   360,   366,   370,
     377,   381,   389,   393,   400,   406,   414,   418,   426,   434,
     440,   443,   446,   452,   459,   468,   471,   475,   484,   486,
     488,   490,   496,   499,   502,   510,   511,   512,   516,   519,
     525,   530,   540,   556,   559,   562,   569,   572,   575,   581,
     584,   589,   592,   601,   604,   607,   615,   620,   626,   629,
     642,   657,   672,   678,   685,   691,   695,   702,   705,   711,
     712,   713,   714,   715,   716,   720,   721,   722,   727,   730,
     736,   739,   743,   747,   754,   760,   766,   769,   773,   780,
     787,   793,   796,   800,   807,   810,   816,   817,   818,   819,
     820,   828,   831,   834,   837,   840,   843,   846,   849,   852,
     855,   858,   861,   864,   867,   870,   873,   876,   879,   882,
     888,   891,   898,   901,   910,   913,   916,   919,   922,   925,
     928,   931,   934,   935,   936,   937,   938,   939,   940,   941,
     942,   943,   944,   945,   949,   955,   958,   964,   967,   973,
     976,   980,   987,  1002,  1005,  1012,  1024,  1027,  1031,  1038,
    1044,  1047,  1051,  1058
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
  "TOKEN_F_STRING", "$accept", "switch_statement", "ternary_expr",
  "program", "statement_list", "unsafe_stmt", "continue_statement",
  "statement", "sysf_expr", "use_statement", "use_path", "sh_expr",
  "nnl_statement", "try_statement", "catch_block", "finally_block",
  "throw_statement", "jmp_statement", "import_statement",
  "import_path_tail", "import_path", "import_constraints",
  "import_options", "name_list", "export_statement", "export_list",
  "export_item", "import_impl_list", "import_impl_item", "packet_decl",
  "function_decl", "param_list", "param", "type", "dict_expr",
  "dict_entries", "dict_entry_list", "bracket_access", "return_type",
  "let_decl", "const_decl", "if_statement", "break_statement",
  "for_statement", "while_statement", "loop_statement", "match_statement",
  "match_cases", "match_case", "pattern", "array_patterns", "struct_decl",
  "struct_fields", "struct_field", "enum_decl", "enum_variants",
  "module_decl", "impl_decl", "function_decl_list", "return_statement",
  "expression", "binary_expr", "unary_expr", "lambda_expr", "primary_expr",
  "f_string", "member_access", "call_expr", "argument_list", "array_expr",
  "await_expr", "spawn_expr", "array_items", "struct_expr",
  "struct_init_fields", "block", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-386)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2980,   -49,   -44,   -22,    72,   102,   247,   247,   359,   247,
      33,  -386,  -386,   -29,    49,   138,   145,   146,   147,   247,
    -386,  -386,  -386,    17,   148,    79,   157,   158,   159,    83,
    3155,  3237,    42,   247,   161,   247,   247,   162,  3073,  3102,
     247,   247,   247,   137,   247,   247,  -386,  -386,  -386,  -386,
    -386,  -386,  -386,    94,  2980,  -386,  -386,  -386,  -386,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,
    -386,  -386,  -386,  -386,  3996,  -386,  -386,  -386,    48,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,   247,   247,   163,   -10,
     165,  3996,  3340,    -3,  3384,  3428,  2980,   166,   166,  -386,
      35,   -11,    -4,  -386,   177,   -24,   178,   179,  3472,   174,
     175,   180,   274,   189,  2980,   191,   247,  -386,   182,  2980,
      48,    48,   183,    -1,    34,  -386,  3516,  -386,    -9,    18,
     151,     6,   247,  3996,   247,  3996,  3692,   193,   208,  3821,
    3996,   -41,  2980,  3996,  3996,  -386,  -386,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   186,   247,   190,   194,
     247,   247,   200,   201,   183,   247,   134,   247,  2980,   247,
     247,  2980,  2980,   508,    35,    35,   196,   197,    53,  -386,
     198,  -386,    40,  -386,  2980,   199,   205,   206,    21,    13,
     212,   241,   249,   207,   210,   611,  2980,  3996,   220,   714,
    3821,     8,   247,   134,   183,  2980,    13,   211,   103,   247,
     134,  3735,  3778,  -386,  -386,   247,   247,   247,  -386,   817,
      18,    18,   151,   151,   151,  3996,  3996,  3996,  3996,  3996,
    3996,   192,   192,   139,   139,   139,   139,   510,  2990,   224,
    3856,   226,  -386,  3996,    56,  3249,  -386,  -386,    57,  3996,
     222,   235,   265,  3996,   920,  3296,  3891,  1023,  1126,  -386,
    -386,   228,   219,   245,    41,   100,  -386,  -386,    -4,  -386,
    1229,   231,   248,   -16,  -386,  -386,   104,    23,  -386,    16,
     225,  -386,    13,  -386,  -386,  -386,     3,  -386,   243,   183,
     247,   247,   236,   251,   117,  -386,  1332,   183,  -386,   237,
    3996,   276,  -386,  1435,     9,  -386,   242,  -386,  3996,   284,
    -386,  -386,  3926,  3996,  3996,   -15,   247,   247,   247,   247,
    -386,  -386,    66,   134,  -386,   247,   335,   247,   247,  2980,
     247,  -386,  -386,    53,  -386,  -386,   253,   311,  -386,   332,
    -386,  -386,  -386,   205,   134,   205,  -386,  -386,   254,  -386,
    -386,  -386,  -386,  -386,    -7,  -386,  -386,  3184,   120,  3996,
    3996,   183,   247,   255,  -386,  -386,   127,  2980,   247,  -386,
    -386,  -386,   122,   247,   247,   268,   269,   257,   129,  3996,
     142,  3996,   134,  3237,   -14,  -386,  3996,     2,  3560,  3604,
    1538,  3961,   123,   242,   281,  -386,    38,  -386,  -386,  -386,
      13,  -386,  2980,  3996,  -386,    66,   144,  3996,   285,    66,
    1641,  3996,   259,  -386,  3996,  3996,   263,   264,   275,  -386,
    -386,  -386,  -386,    48,   247,  2980,  2980,  -386,  2980,  2980,
    -386,   247,  -386,     5,  -386,  -386,  1744,   277,    66,   247,
     279,  -386,  -386,   282,   283,  2980,  3996,  1847,  1950,  2053,
    2156,  3648,  -386,  -386,  2980,   287,  3996,  2980,   288,   289,
    2259,  -386,  -386,  -386,  -386,  2980,  2362,  2980,  2465,  2980,
    2980,  -386,  2568,  -386,  2671,  -386,  2774,  2877,  -386,  -386,
    -386,  -386
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,   155,     0,     0,     0,
       0,   116,     8,     0,     0,     0,     0,     0,     0,     0,
     187,   188,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,     0,     0,     0,     0,     0,     0,     0,
       0,    98,   216,     0,     0,     0,   190,   184,   185,   186,
     204,    21,   158,     0,     4,    29,    11,     5,   200,    18,
     201,    12,    15,    16,    13,     9,    10,    17,    19,   194,
     193,    24,    26,    27,    25,    28,    30,    31,    32,    20,
      22,    14,    23,    33,    34,   156,   157,   198,   159,   203,
     197,   192,   195,   199,   202,   196,    98,    98,     0,     0,
       0,   154,     0,   190,     0,     0,     0,     0,     0,    60,
      62,    54,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,   149,     0,    98,
     213,   215,    85,    88,     0,    86,     0,    40,    37,   181,
     180,     0,     0,    36,     0,    43,     0,     0,    99,     0,
     217,     0,     0,    50,    51,     1,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     209,     0,     0,     0,    85,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,    64,     0,     0,     0,    56,
       0,    74,     0,    72,     0,     0,   140,   146,   151,     0,
       0,     0,     0,     0,   220,     0,     0,    53,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   191,    97,     0,     0,     0,   212,     0,
     161,   162,   163,   164,   165,   174,   175,   176,   177,   178,
     179,   166,   167,   168,   169,   170,   171,   172,   173,     0,
       0,   206,   205,   210,     0,     0,    95,    96,     0,   106,
       0,    92,     0,   111,     0,     0,     0,     0,     0,   123,
      61,    55,     0,     0,     0,     0,    76,    75,     0,    71,
       0,     0,     0,     0,   141,   147,     0,     0,   152,     0,
       0,   132,   135,   131,   129,   130,     0,   125,     0,    85,
       0,     0,     0,     0,     0,     7,     0,    85,   214,     0,
      90,    89,    87,     0,     0,    39,     0,    41,   109,     0,
      35,    42,     0,   100,   218,     0,   209,     0,   209,     0,
     207,   102,   103,     0,    93,     0,   113,     0,     0,     0,
       0,   118,   122,     0,    57,    78,     0,     0,    65,     0,
      58,    73,    79,   140,     0,     0,   138,   143,     0,   145,
     150,   153,   134,   136,     0,   124,   126,     0,     0,   108,
     112,    85,     0,     0,   219,    44,     0,     0,     0,   182,
       2,    68,     0,     0,     0,     0,     0,    45,     0,     3,
       0,   211,     0,     0,     0,    94,   107,     0,     0,     0,
       0,     0,     0,     0,    67,    77,     0,   144,   142,   148,
       0,   133,    98,   127,   128,   103,     0,   221,     0,   103,
       0,    91,     0,    38,   110,   101,     0,     0,     0,    46,
     160,   208,   104,   105,     0,     0,     0,   115,     0,     0,
     119,     0,    59,     0,   139,   137,     0,     0,   103,     0,
       0,   183,    69,     0,     0,     0,    84,     0,     0,     0,
       0,     0,    66,   223,     0,     0,   222,     0,     0,     0,
       0,    80,   114,   120,   121,     0,     0,     0,     0,     0,
       0,    49,     0,    81,     0,    82,     0,     0,   117,    83,
      47,    48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -386,  -386,  -386,  -386,    20,  -386,  -386,   -13,  -386,  -386,
    -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,  -386,    69,
    -386,    86,    24,   -39,  -386,  -386,    87,    36,    27,  -386,
    -196,  -124,   167,  -216,  -386,   141,  -386,  -386,  -385,  -386,
    -386,   -12,  -386,  -386,  -386,  -386,  -386,   168,  -275,  -292,
    -386,  -386,    29,  -287,  -386,  -386,  -386,  -386,  -386,  -386,
      -6,  -386,  -386,  -386,   -26,  -386,  -386,  -386,  -139,  -386,
    -386,  -386,  -386,  -386,  -386,  -386
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    51,    52,    53,    54,    55,    56,    57,    58,    59,
     138,    60,    61,    62,   397,   439,    63,    64,    65,   110,
     111,   199,   284,   392,    66,   202,   203,   285,   286,    67,
      68,   134,   135,   272,    69,   147,   148,    70,   404,    71,
      72,    73,    74,    75,    76,    77,    78,   306,   307,   308,
     374,    79,   293,   294,    80,   296,    81,    82,   299,    83,
      84,    85,    86,    87,    88,    89,    90,    91,   264,    92,
      93,    94,   151,    95,   314,   424
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     101,   102,   104,   105,   130,   131,   367,   321,   221,   300,
     373,     7,   298,   118,   329,   300,   197,   200,   227,   300,
     205,     3,   119,   120,   121,   189,     3,   136,   119,   139,
     140,   376,   143,   145,   146,   149,   150,   237,   153,   154,
     457,   156,    96,   185,   460,   107,   297,    97,   301,   376,
     190,   297,   222,   238,   301,   108,    29,   122,   301,   229,
     268,    29,   365,   122,   228,   444,   186,   206,   159,   160,
     161,   420,   109,   475,   282,   223,   366,   445,   418,    98,
     198,   395,   230,   432,   396,   292,   224,   421,   128,   283,
     149,   149,   176,   446,   155,   375,   302,   201,   319,   472,
     177,   390,   302,   371,   303,   304,   302,   305,   370,   196,
     303,   304,   224,   305,   303,   304,   365,   305,   288,   357,
     217,   178,   179,   220,   106,   225,   193,   405,   455,   367,
     454,   132,   289,   358,   339,   224,   231,   180,   232,   292,
     112,   181,   402,   133,   215,   403,   340,   342,   417,   219,
     113,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     124,   260,   239,    99,   263,   265,   194,   195,   359,   269,
     156,   273,   368,   275,   276,   378,   442,   157,   158,   159,
     160,   161,   360,   386,   326,   383,   369,   398,   224,   400,
     432,   359,   156,   100,   327,   224,   156,   339,   274,   384,
     425,   277,   278,   176,   433,   452,   320,   429,   187,   440,
     339,   177,   224,   328,   290,   176,   156,   270,   152,   332,
     333,   334,   441,   177,   458,   271,   316,   182,   183,   114,
     157,   158,   159,   160,   161,   323,   115,   116,   117,   123,
       1,     2,   184,   170,   171,   172,   173,   426,   125,   126,
     127,   156,   137,   141,   156,   156,   176,   109,   204,   207,
     208,    20,    21,    22,   177,   210,   211,   156,    24,   213,
     214,   212,   216,   218,   133,   234,   235,   259,    30,    31,
      32,   261,   266,   267,   310,   262,    35,   280,   281,   287,
     291,   309,   311,   156,   379,   380,   292,   295,   312,   317,
     156,   313,   325,   336,    36,   338,   343,   344,   345,   353,
     355,   356,   363,   377,   364,   381,   372,   382,   387,   388,
     263,   399,   263,   401,    38,    39,    40,   393,    41,   406,
      42,   408,   409,   391,   411,   407,   413,   283,    46,    47,
      48,    49,    50,   282,   438,   419,   428,   436,   437,   357,
     462,   459,     1,     2,   463,   464,   465,   354,   474,   410,
     477,   423,   478,   479,   453,   361,   427,   443,   487,   489,
     490,   414,   431,    20,    21,    22,   415,   434,   435,   412,
      24,   322,   416,     0,   324,   447,     0,   156,     0,     0,
      30,    31,    32,     0,     0,     0,     0,   430,    35,     0,
       0,     0,     0,     0,     0,     0,   220,   156,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   466,     0,
       0,     0,   456,   156,     0,   471,    38,    39,    40,     0,
      41,     0,    42,   476,   156,   156,   156,   156,     0,     0,
     103,    47,    48,    49,    50,   467,   468,   156,   469,   470,
       0,     0,     0,   156,     0,   156,     0,     0,     0,   156,
       0,   156,     0,   156,   156,   480,     0,     0,     0,     0,
       0,     0,     0,     0,   486,     0,     0,   488,     0,     0,
       0,     0,     0,     0,     0,   492,     0,   494,     0,   496,
     497,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,    33,    34,     0,    35,   157,   158,
     159,   160,   161,     0,     0,     0,     0,     0,     0,   168,
     169,   170,   171,   172,   173,    36,     0,     0,     0,     0,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,   177,     0,    37,    38,    39,    40,     0,    41,
     279,    42,     0,    43,     0,     0,    44,     0,    45,    46,
      47,    48,    49,    50,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,     0,    41,   315,    42,     0,    43,     0,     0,    44,
       0,    45,    46,    47,    48,    49,    50,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
      33,    34,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,    41,   318,    42,     0,    43,
       0,     0,    44,     0,    45,    46,    47,    48,    49,    50,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,     0,    41,   335,
      42,     0,    43,     0,     0,    44,     0,    45,    46,    47,
      48,    49,    50,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,    33,    34,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    38,    39,    40,
       0,    41,   346,    42,     0,    43,     0,     0,    44,     0,
      45,    46,    47,    48,    49,    50,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,     0,    41,   351,    42,     0,    43,     0,
       0,    44,     0,    45,    46,    47,    48,    49,    50,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,    33,    34,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,     0,    41,   352,    42,
       0,    43,     0,     0,    44,     0,    45,    46,    47,    48,
      49,    50,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,     0,
      41,   362,    42,     0,    43,     0,     0,    44,     0,    45,
      46,    47,    48,    49,    50,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,    33,    34,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,     0,    41,   385,    42,     0,    43,     0,     0,
      44,     0,    45,    46,    47,    48,    49,    50,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    40,     0,    41,   389,    42,     0,
      43,     0,     0,    44,     0,    45,    46,    47,    48,    49,
      50,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,    33,    34,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    38,    39,    40,     0,    41,
     450,    42,     0,    43,     0,     0,    44,     0,    45,    46,
      47,    48,    49,    50,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,     0,    41,   461,    42,     0,    43,     0,     0,    44,
       0,    45,    46,    47,    48,    49,    50,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
      33,    34,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,    41,   473,    42,     0,    43,
       0,     0,    44,     0,    45,    46,    47,    48,    49,    50,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,     0,    41,   481,
      42,     0,    43,     0,     0,    44,     0,    45,    46,    47,
      48,    49,    50,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,    33,    34,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    38,    39,    40,
       0,    41,   482,    42,     0,    43,     0,     0,    44,     0,
      45,    46,    47,    48,    49,    50,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,    33,
      34,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      38,    39,    40,     0,    41,   483,    42,     0,    43,     0,
       0,    44,     0,    45,    46,    47,    48,    49,    50,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,    33,    34,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    38,    39,    40,     0,    41,   484,    42,
       0,    43,     0,     0,    44,     0,    45,    46,    47,    48,
      49,    50,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,    33,    34,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    39,    40,     0,
      41,   491,    42,     0,    43,     0,     0,    44,     0,    45,
      46,    47,    48,    49,    50,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,    33,    34,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    38,
      39,    40,     0,    41,   493,    42,     0,    43,     0,     0,
      44,     0,    45,    46,    47,    48,    49,    50,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,    33,    34,     0,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    40,     0,    41,   495,    42,     0,
      43,     0,     0,    44,     0,    45,    46,    47,    48,    49,
      50,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,    33,    34,     0,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    38,    39,    40,     0,    41,
     498,    42,     0,    43,     0,     0,    44,     0,    45,    46,
      47,    48,    49,    50,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,    33,    34,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,    39,
      40,     0,    41,   499,    42,     0,    43,     0,     0,    44,
       0,    45,    46,    47,    48,    49,    50,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
      33,    34,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    38,    39,    40,     0,    41,   500,    42,     0,    43,
       0,     0,    44,     0,    45,    46,    47,    48,    49,    50,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,    33,    34,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    38,    39,    40,     0,    41,   501,
      42,     0,    43,     0,     0,    44,     0,    45,    46,    47,
      48,    49,    50,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,    33,    34,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,   157,   158,
     159,   160,   161,     0,     0,     0,     0,    36,     0,   168,
     169,   170,   171,   172,   173,   174,     0,     0,     0,     0,
       0,     0,     0,     0,   176,     0,    37,    38,    39,    40,
       0,    41,   177,    42,     0,    43,     1,     2,    44,     0,
      45,    46,    47,    48,    49,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,    22,
       0,     0,     0,     0,    24,     1,     2,     0,     0,     0,
       0,     0,     0,     0,    30,    31,    32,     0,     0,     0,
       0,     0,    35,     0,     0,     0,    20,    21,    22,     0,
       0,     0,     0,    24,     0,     0,     0,     0,     0,     0,
      36,     0,     0,    30,    31,    32,     0,     0,     0,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     1,     2,
      38,    39,   142,     0,    41,     0,    42,     0,     0,    36,
       0,     0,     0,     0,    46,    47,    48,    49,    50,    20,
      21,    22,     0,     0,     0,     0,    24,     1,     2,    38,
      39,   144,     0,    41,     0,    42,    30,    31,    32,     0,
       0,     0,     0,    46,    47,    48,    49,    50,    20,    21,
      22,     0,     0,     0,     0,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    31,    32,     0,     0,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       1,     2,    38,    39,    40,     0,   129,     0,    42,     0,
       0,    36,     0,     0,     0,     0,    46,    47,    48,    49,
      50,    20,    21,    22,     0,     0,     0,     0,    24,     0,
       0,    38,    39,    40,     0,   422,     0,    42,    30,    31,
      32,     0,     0,     0,     0,    46,    47,    48,    49,    50,
       0,     0,     0,     0,     0,     0,     0,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,     0,     0,     0,     0,
       0,     0,     0,   176,    38,    39,    40,     0,    41,     0,
      42,   177,     0,     0,     0,     0,     0,     0,    46,    47,
      48,    49,    50,   341,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,     0,     0,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,   177,     0,
     347,   348,     0,     0,     0,     0,     0,   349,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,     0,     0,     0,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,   177,     0,     0,     0,     0,     0,     0,     0,
       0,   188,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,     0,     0,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,     0,     0,     0,   177,     0,     0,     0,
       0,     0,     0,     0,     0,   191,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,     0,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,     0,     0,
     177,     0,     0,     0,     0,     0,     0,     0,     0,   192,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,     0,
       0,     0,     0,     0,     0,     0,   176,     0,     0,     0,
       0,     0,     0,     0,   177,     0,     0,     0,     0,     0,
       0,     0,     0,   209,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,     0,     0,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,   177,     0,
       0,     0,     0,     0,     0,     0,     0,   226,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,     0,     0,     0,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,   177,     0,     0,     0,     0,     0,     0,     0,
       0,   448,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,     0,     0,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,     0,     0,     0,   177,     0,     0,     0,
       0,     0,     0,     0,     0,   449,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,     0,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,     0,     0,
     177,     0,     0,     0,     0,     0,     0,     0,     0,   485,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,     0,
       0,     0,     0,     0,     0,     0,   176,     0,     0,     0,
       0,     0,     0,     0,   177,     0,     0,     0,     0,     0,
       0,     0,   233,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,     0,     0,     0,     0,     0,     0,     0,   176,
       0,     0,     0,     0,     0,     0,     0,   177,     0,     0,
       0,     0,     0,     0,     0,   330,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,     0,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,     0,     0,
     177,     0,     0,     0,     0,     0,     0,     0,   331,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     0,
       0,     0,     0,     0,     0,   176,     0,     0,     0,     0,
       0,   236,     0,   177,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,     0,     0,     0,     0,     0,     0,     0,
     176,     0,   337,     0,     0,     0,     0,     0,   177,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     0,
       0,     0,     0,     0,     0,   176,     0,     0,   350,     0,
       0,     0,     0,   177,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,     0,     0,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,   394,     0,   177,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,     0,     0,
       0,     0,     0,     0,     0,   176,     0,     0,   451,     0,
       0,     0,     0,   177,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,     0,     0,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,   177
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,    30,    31,   293,   223,   132,     6,
     302,     9,   208,    19,   230,     6,    27,    21,    27,     6,
      44,     5,     5,     6,     7,    28,     5,    33,     5,    35,
      36,   306,    38,    39,    40,    41,    42,    78,    44,    45,
     425,    54,    91,    53,   429,    74,    30,    91,    45,   324,
      53,    30,    53,    94,    45,    84,    40,    40,    45,    53,
     184,    40,    78,    40,    73,    79,    76,    91,    50,    51,
      52,    78,   101,   458,    21,    76,    92,    91,   365,   101,
      91,    96,    76,    78,    99,   101,    78,    94,     5,    36,
      96,    97,    74,    91,     0,    92,    93,   101,    90,    94,
      82,    92,    93,   299,   101,   102,    93,   104,    92,    74,
     101,   102,    78,   104,   101,   102,    78,   104,    78,    78,
     126,    73,    74,   129,    91,    91,   106,   343,   420,   416,
      92,    89,    92,    92,    78,    78,   142,    89,   144,   101,
      91,    93,    76,   101,   124,    79,    90,    90,   364,   129,
     101,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
      91,   177,   152,   101,   180,   181,   107,   108,    78,   185,
     193,   187,    78,   189,   190,   309,   402,    48,    49,    50,
      51,    52,    92,   317,    91,    78,    92,   336,    78,   338,
      78,    78,   215,   101,   101,    78,   219,    78,   188,    92,
      90,   191,   192,    74,    92,    92,   222,    90,    53,    90,
      78,    82,    78,   229,   204,    74,   239,    93,    91,   235,
     236,   237,    90,    82,    90,   101,   216,    96,    97,   101,
      48,    49,    50,    51,    52,   225,   101,   101,   101,   101,
       3,     4,    89,    61,    62,    63,    64,   381,   101,   101,
     101,   274,   101,   101,   277,   278,    74,   101,    91,    91,
      91,    24,    25,    26,    82,   101,   101,   290,    31,     5,
      91,   101,    91,   101,   101,    92,    78,   101,    41,    42,
      43,   101,    92,    92,    53,   101,    49,   101,   101,   101,
     101,    89,    53,   316,   310,   311,   101,   101,   101,    89,
     323,   101,   101,    89,    67,    89,    94,    82,    53,    91,
     101,    76,    91,    80,    76,    89,   101,    76,    91,    53,
     336,   337,   338,   339,    87,    88,    89,    53,    91,   345,
      93,   347,   348,   101,   350,    10,    93,    36,   101,   102,
     103,   104,   105,    21,    97,   101,   101,    89,    89,    78,
     101,    76,     3,     4,   101,   101,    91,   281,    91,   349,
      91,   377,    90,    90,   413,   288,   382,   403,    91,    91,
      91,   357,   388,    24,    25,    26,   359,   393,   394,   353,
      31,   224,   363,    -1,   226,   407,    -1,   410,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,   387,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   422,   430,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   444,    -1,
      -1,    -1,   422,   456,    -1,   451,    87,    88,    89,    -1,
      91,    -1,    93,   459,   467,   468,   469,   470,    -1,    -1,
     101,   102,   103,   104,   105,   445,   446,   480,   448,   449,
      -1,    -1,    -1,   486,    -1,   488,    -1,    -1,    -1,   492,
      -1,   494,    -1,   496,   497,   465,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   474,    -1,    -1,   477,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   485,    -1,   487,    -1,   489,
     490,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    46,    47,    -1,    49,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    86,    87,    88,    89,    -1,    91,
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
      89,    -1,    91,    92,    93,    -1,    95,    -1,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    -1,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    -1,   100,   101,   102,   103,   104,   105,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    -1,    91,    92,
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
      -1,    91,    92,    93,    -1,    95,    -1,    -1,    98,    -1,
     100,   101,   102,   103,   104,   105,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    -1,    91,    92,    93,    -1,    95,    -1,
      -1,    98,    -1,   100,   101,   102,   103,   104,   105,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    -1,    91,    92,    93,
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
      91,    92,    93,    -1,    95,    -1,    -1,    98,    -1,   100,
     101,   102,   103,   104,   105,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    91,    92,    93,    -1,    95,    -1,    -1,
      98,    -1,   100,   101,   102,   103,   104,   105,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    -1,    91,    92,    93,    -1,
      95,    -1,    -1,    98,    -1,   100,   101,   102,   103,   104,
     105,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    87,    88,    89,    -1,    91,
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
      89,    -1,    91,    92,    93,    -1,    95,    -1,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    -1,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    -1,   100,   101,   102,   103,   104,   105,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    -1,    91,    92,
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
      -1,    91,    92,    93,    -1,    95,    -1,    -1,    98,    -1,
     100,   101,   102,   103,   104,   105,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    -1,    91,    92,    93,    -1,    95,    -1,
      -1,    98,    -1,   100,   101,   102,   103,   104,   105,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    -1,    91,    92,    93,
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
      91,    92,    93,    -1,    95,    -1,    -1,    98,    -1,   100,
     101,   102,   103,   104,   105,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    91,    92,    93,    -1,    95,    -1,    -1,
      98,    -1,   100,   101,   102,   103,   104,   105,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    -1,    91,    92,    93,    -1,
      95,    -1,    -1,    98,    -1,   100,   101,   102,   103,   104,
     105,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    87,    88,    89,    -1,    91,
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
      89,    -1,    91,    92,    93,    -1,    95,    -1,    -1,    98,
      -1,   100,   101,   102,   103,   104,   105,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    -1,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    -1,   100,   101,   102,   103,   104,   105,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    -1,    91,    92,
      93,    -1,    95,    -1,    -1,    98,    -1,   100,   101,   102,
     103,   104,   105,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    -1,    -1,    46,    47,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    67,    -1,    59,
      60,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    86,    87,    88,    89,
      -1,    91,    82,    93,    -1,    95,     3,     4,    98,    -1,
     100,   101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,
      -1,    -1,    -1,    -1,    31,     3,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    24,    25,    26,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
      87,    88,    89,    -1,    91,    -1,    93,    -1,    -1,    67,
      -1,    -1,    -1,    -1,   101,   102,   103,   104,   105,    24,
      25,    26,    -1,    -1,    -1,    -1,    31,     3,     4,    87,
      88,    89,    -1,    91,    -1,    93,    41,    42,    43,    -1,
      -1,    -1,    -1,   101,   102,   103,   104,   105,    24,    25,
      26,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,    87,    88,    89,    -1,    91,    -1,    93,    -1,
      -1,    67,    -1,    -1,    -1,    -1,   101,   102,   103,   104,
     105,    24,    25,    26,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    87,    88,    89,    -1,    91,    -1,    93,    41,    42,
      43,    -1,    -1,    -1,    -1,   101,   102,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    87,    88,    89,    -1,    91,    -1,
      93,    82,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
     103,   104,   105,    94,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    82,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    76,    -1,    -1,    -1,    -1,    -1,    82,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    82,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    80,    -1,    82,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    82,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    40,
      41,    42,    43,    46,    47,    49,    67,    86,    87,    88,
      89,    91,    93,    95,    98,   100,   101,   102,   103,   104,
     105,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     117,   118,   119,   122,   123,   124,   130,   135,   136,   140,
     143,   145,   146,   147,   148,   149,   150,   151,   152,   157,
     160,   162,   163,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   175,   176,   177,   179,    91,    91,   101,   101,
     101,   166,   166,   101,   166,   166,    91,    74,    84,   101,
     125,   126,    91,   101,   101,   101,   101,   101,   166,     5,
       6,     7,    40,   101,    91,   101,   101,   101,     5,    91,
     170,   170,    89,   101,   137,   138,   166,   101,   116,   166,
     166,   101,    89,   166,    89,   166,   166,   141,   142,   166,
     166,   178,    91,   166,   166,     0,   113,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    74,    82,    73,    74,
      89,    93,   141,   141,    89,    53,    76,    53,    91,    28,
      53,    91,    91,   110,   125,   125,    74,    27,    91,   127,
      21,   101,   131,   132,    91,    44,    91,    91,    91,    91,
     101,   101,   101,     5,    91,   110,    91,   166,   101,   110,
     166,   137,    53,    76,    78,    91,    91,    27,    73,    53,
      76,   166,   166,    90,    92,    78,    80,    78,    94,   110,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   101,
     166,   101,   101,   166,   174,   166,    92,    92,   137,   166,
      93,   101,   139,   166,   110,   166,   166,   110,   110,    92,
     101,   101,    21,    36,   128,   133,   134,   101,    78,    92,
     110,   101,   101,   158,   159,   101,   161,    30,   136,   164,
       6,    45,    93,   101,   102,   104,   153,   154,   155,    89,
      53,    53,   101,   101,   180,    92,   110,    89,    92,    90,
     166,   139,   138,   110,   153,   101,    91,   101,   166,   139,
      90,    90,   166,   166,   166,    92,    89,    76,    89,    78,
      90,    94,    90,    94,    82,    53,    92,    84,    85,    91,
      77,    92,    92,    91,   127,   101,    76,    78,    92,    78,
      92,   132,    92,    91,    76,    78,    92,   159,    78,    92,
      92,   136,   101,   155,   156,    92,   154,    80,   137,   166,
     166,    89,    76,    78,    92,    92,   137,    91,    53,    92,
      92,   101,   129,    53,    80,    96,    99,   120,   174,   166,
     174,   166,    76,    79,   144,   139,   166,    10,   166,   166,
     110,   166,   133,    93,   128,   134,   158,   139,   159,   101,
      78,    94,    91,   166,   181,    90,   137,   166,   101,    90,
     110,   166,    78,    92,   166,   166,    89,    89,    97,   121,
      90,    90,   139,   170,    79,    91,    91,   147,    91,    91,
      92,    77,    92,   129,    92,   155,   110,   144,    90,    76,
     144,    92,   101,   101,   101,    91,   166,   110,   110,   110,
     110,   166,    94,    92,    91,   144,   166,    91,    90,    90,
     110,    92,    92,    92,    92,    91,   110,    91,   110,    91,
      91,    92,   110,    92,   110,    92,   110,   110,    92,    92,
      92,    92
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   106,   107,   108,   109,   110,   110,   111,   112,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   115,   115,   115,
     116,   116,   117,   117,   118,   119,   119,   120,   120,   121,
     122,   122,   123,   123,   124,   124,   124,   124,   124,   124,
     125,   125,   126,   126,   126,   127,   128,   128,   129,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   134,   135,
     136,   136,   136,   136,   136,   137,   137,   137,   138,   138,
     138,   138,   139,   139,   139,   140,   140,   140,   141,   141,
     142,   142,   143,   144,   144,   144,   145,   145,   145,   145,
     145,   146,   146,   147,   147,   147,   148,   149,   149,   149,
     149,   149,   150,   151,   152,   153,   153,   154,   154,   155,
     155,   155,   155,   155,   155,   156,   156,   156,   157,   157,
     158,   158,   158,   158,   159,   160,   161,   161,   161,   162,
     163,   164,   164,   164,   165,   165,   166,   166,   166,   166,
     166,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     168,   168,   169,   169,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   171,   172,   172,   173,   173,   174,
     174,   174,   175,   176,   176,   177,   178,   178,   178,   179,
     180,   180,   180,   181
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
       9,    10,    10,    11,     8,     0,     1,     3,     1,     3,
       3,     5,     1,     2,     3,     4,     4,     3,     0,     1,
       3,     5,     4,     0,     2,     2,     4,     6,     5,     4,
       6,     4,     5,     5,     9,     7,     1,    11,     5,     7,
       9,     9,     5,     4,     5,     1,     2,     3,     3,     1,
       1,     1,     1,     3,     2,     0,     1,     3,     5,     7,
       0,     1,     3,     2,     3,     5,     0,     1,     3,     2,
       5,     0,     1,     2,     2,     1,     1,     1,     1,     1,
       6,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     5,     7,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     4,     6,     0,
       1,     3,     3,     2,     4,     2,     0,     1,     3,     5,
       0,     3,     5,     3
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
#line 123 "src/parser/parser.y"
                                                                  {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2339 "parser.c"
    break;

  case 3: /* ternary_expr: expression TOKEN_OPTIONAL expression TOKEN_COLON expression  */
#line 128 "src/parser/parser.y"
                                                                {
        // condition ? true_expr : false_expr
        (yyval.node) = create_ternary_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2348 "parser.c"
    break;

  case 4: /* program: statement_list  */
#line 135 "src/parser/parser.y"
                   {
        program_root = create_program_node((yyvsp[0].node_list));
    }
#line 2356 "parser.c"
    break;

  case 5: /* statement_list: statement  */
#line 141 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2365 "parser.c"
    break;

  case 6: /* statement_list: statement_list statement  */
#line 145 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2374 "parser.c"
    break;

  case 7: /* unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 151 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_unsafe_node((yyvsp[-1].node_list));
    }
#line 2382 "parser.c"
    break;

  case 8: /* continue_statement: TOKEN_CONTINUE  */
#line 156 "src/parser/parser.y"
                   {
        (yyval.node) = create_continue_node();
    }
#line 2390 "parser.c"
    break;

  case 34: /* statement: expression  */
#line 188 "src/parser/parser.y"
                 {
        (yyval.node) = create_expr_statement((yyvsp[0].node));
    }
#line 2398 "parser.c"
    break;

  case 35: /* sysf_expr: TOKEN_SYSF TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 193 "src/parser/parser.y"
                                                    {
        (yyval.node) = create_sysf_node((yyvsp[-1].node));
    }
#line 2406 "parser.c"
    break;

  case 36: /* sysf_expr: TOKEN_SYSF expression  */
#line 196 "src/parser/parser.y"
                            {
        (yyval.node) = create_sysf_node((yyvsp[0].node));
    }
#line 2414 "parser.c"
    break;

  case 37: /* use_statement: TOKEN_USE use_path  */
#line 203 "src/parser/parser.y"
                       {
        (yyval.node) = create_use_node((yyvsp[0].string), NULL);
    }
#line 2422 "parser.c"
    break;

  case 38: /* use_statement: TOKEN_USE use_path TOKEN_DOUBLE_COLON TOKEN_LBRACE name_list TOKEN_RBRACE  */
#line 207 "src/parser/parser.y"
                                                                                {
        (yyval.node) = create_use_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2430 "parser.c"
    break;

  case 39: /* use_statement: TOKEN_USE use_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 211 "src/parser/parser.y"
                                                   {
        (yyval.node) = create_use_node((yyvsp[-2].string), NULL);
        // Stocker l'alias dans le nœud
        (yyval.node)->use_stmt.alias = strdup((yyvsp[0].string));
    }
#line 2440 "parser.c"
    break;

  case 40: /* use_path: TOKEN_IDENTIFIER  */
#line 219 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2448 "parser.c"
    break;

  case 41: /* use_path: use_path TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 222 "src/parser/parser.y"
                                                   {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 3);
        sprintf(path, "%s::%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2459 "parser.c"
    break;

  case 42: /* sh_expr: TOKEN_SH TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 231 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_sh_node((yyvsp[-1].node));
    }
#line 2467 "parser.c"
    break;

  case 43: /* sh_expr: TOKEN_SH expression  */
#line 234 "src/parser/parser.y"
                          {
        (yyval.node) = create_sh_node((yyvsp[0].node));
    }
#line 2475 "parser.c"
    break;

  case 44: /* nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 240 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_nnl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2483 "parser.c"
    break;

  case 45: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block  */
#line 246 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_try_node((yyvsp[-2].node_list), (yyvsp[0].node), NULL);
    }
#line 2491 "parser.c"
    break;

  case 46: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block  */
#line 249 "src/parser/parser.y"
                                                                                   {
        (yyval.node) = create_try_node((yyvsp[-3].node_list), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2499 "parser.c"
    break;

  case 47: /* catch_block: TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 255 "src/parser/parser.y"
                                                                                                    {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2507 "parser.c"
    break;

  case 48: /* catch_block: TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 258 "src/parser/parser.y"
                                                                                                       {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2515 "parser.c"
    break;

  case 49: /* finally_block: TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 264 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_finally_node((yyvsp[-1].node_list));
    }
#line 2523 "parser.c"
    break;

  case 50: /* throw_statement: TOKEN_THROW expression  */
#line 270 "src/parser/parser.y"
                           {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2531 "parser.c"
    break;

  case 51: /* throw_statement: TOKEN_RAISE expression  */
#line 273 "src/parser/parser.y"
                             {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2539 "parser.c"
    break;

  case 52: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER  */
#line 278 "src/parser/parser.y"
                               {
        (yyval.node) = create_jmp_node((yyvsp[0].string), NULL);
    }
#line 2547 "parser.c"
    break;

  case 53: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression  */
#line 281 "src/parser/parser.y"
                                            {
        (yyval.node) = create_jmp_node((yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2555 "parser.c"
    break;

  case 54: /* import_statement: TOKEN_IMPORT import_path  */
#line 290 "src/parser/parser.y"
                             {
        (yyval.node) = create_import_node((yyvsp[0].string), NULL, NULL);
    }
#line 2563 "parser.c"
    break;

  case 55: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 294 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_import_node((yyvsp[-2].string), (yyvsp[0].string), NULL);
    }
#line 2571 "parser.c"
    break;

  case 56: /* import_statement: TOKEN_IMPORT import_path import_constraints  */
#line 298 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_import_node((yyvsp[-1].string), NULL, (yyvsp[0].node));
    }
#line 2579 "parser.c"
    break;

  case 57: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER import_constraints  */
#line 302 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_import_node((yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2587 "parser.c"
    break;

  case 58: /* import_statement: TOKEN_IMPORT import_path TOKEN_LBRACE import_impl_list TOKEN_RBRACE  */
#line 306 "src/parser/parser.y"
                                                                          {
        ASTNode* node = create_import_node((yyvsp[-3].string), NULL, NULL);
        node->import.impl_list = (yyvsp[-1].node_list);
        (yyval.node) = node;
    }
#line 2597 "parser.c"
    break;

  case 59: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER TOKEN_LBRACE import_impl_list TOKEN_RBRACE  */
#line 312 "src/parser/parser.y"
                                                                                                    {
        ASTNode* node = create_import_node((yyvsp[-5].string), (yyvsp[-3].string), NULL);
        node->import.impl_list = (yyvsp[-1].node_list);
        (yyval.node) = node;
    }
#line 2607 "parser.c"
    break;

  case 60: /* import_path_tail: TOKEN_IDENTIFIER  */
#line 321 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2615 "parser.c"
    break;

  case 61: /* import_path_tail: import_path_tail TOKEN_DOT TOKEN_IDENTIFIER  */
#line 324 "src/parser/parser.y"
                                                  {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 2);
        sprintf(path, "%s.%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2626 "parser.c"
    break;

  case 62: /* import_path: import_path_tail  */
#line 333 "src/parser/parser.y"
                     { 
        (yyval.string) = (yyvsp[0].string); 
    }
#line 2634 "parser.c"
    break;

  case 63: /* import_path: TOKEN_DOT import_path_tail  */
#line 336 "src/parser/parser.y"
                                 { // Import relatif: .fichier
        char* path = malloc(strlen((yyvsp[0].string)) + 2);
        sprintf(path, ".%s", (yyvsp[0].string));
        free((yyvsp[0].string));
        (yyval.string) = path;
    }
#line 2645 "parser.c"
    break;

  case 64: /* import_path: TOKEN_RANGE import_path_tail  */
#line 342 "src/parser/parser.y"
                                   { // Import relatif: ..fichier (utilise TOKEN_RANGE ".." du lexer)
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "..%s", (yyvsp[0].string));
        free((yyvsp[0].string));
        (yyval.string) = path;
    }
#line 2656 "parser.c"
    break;

  case 65: /* import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE  */
#line 351 "src/parser/parser.y"
                                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2664 "parser.c"
    break;

  case 66: /* import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET  */
#line 357 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_constraints_node("only", (yyvsp[-1].node_list));
    }
#line 2672 "parser.c"
    break;

  case 67: /* import_options: import_options TOKEN_COMMA import_options  */
#line 360 "src/parser/parser.y"
                                                {
        (yyval.node) = merge_constraints((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2680 "parser.c"
    break;

  case 68: /* name_list: TOKEN_IDENTIFIER  */
#line 366 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2689 "parser.c"
    break;

  case 69: /* name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 370 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2698 "parser.c"
    break;

  case 70: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
#line 377 "src/parser/parser.y"
                                  {
        (yyval.node) = create_export_node((yyvsp[0].string));
    }
#line 2706 "parser.c"
    break;

  case 71: /* export_statement: TOKEN_EXPORT TOKEN_LBRACE export_list TOKEN_RBRACE  */
#line 381 "src/parser/parser.y"
                                                         {
        ASTNode* node = create_export_node(NULL);
        node->export.export_list = (yyvsp[-1].node_list);
        (yyval.node) = node;
    }
#line 2716 "parser.c"
    break;

  case 72: /* export_list: export_item  */
#line 389 "src/parser/parser.y"
                {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2725 "parser.c"
    break;

  case 73: /* export_list: export_list TOKEN_COMMA export_item  */
#line 393 "src/parser/parser.y"
                                          {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2734 "parser.c"
    break;

  case 74: /* export_item: TOKEN_IDENTIFIER  */
#line 400 "src/parser/parser.y"
                     {
        ASTNode* node = create_identifier_node((yyvsp[0].string));
        node->is_impl = 0;
        (yyval.node) = node;
    }
#line 2744 "parser.c"
    break;

  case 75: /* export_item: TOKEN_IMPL TOKEN_IDENTIFIER  */
#line 406 "src/parser/parser.y"
                                  {
        ASTNode* node = create_identifier_node((yyvsp[0].string));
        node->is_impl = 1;
        (yyval.node) = node;
    }
#line 2754 "parser.c"
    break;

  case 76: /* import_impl_list: import_impl_item  */
#line 414 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2763 "parser.c"
    break;

  case 77: /* import_impl_list: import_impl_list TOKEN_COMMA import_impl_item  */
#line 418 "src/parser/parser.y"
                                                    {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2772 "parser.c"
    break;

  case 78: /* import_impl_item: TOKEN_IMPL TOKEN_IDENTIFIER  */
#line 426 "src/parser/parser.y"
                                {
        ASTNode* node = create_identifier_node((yyvsp[0].string));
        node->is_impl = 1;
        (yyval.node) = node;
    }
#line 2782 "parser.c"
    break;

  case 79: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 434 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_packet_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2790 "parser.c"
    break;

  case 80: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 440 "src/parser/parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2798 "parser.c"
    break;

  case 81: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 443 "src/parser/parser.y"
                                                                                                                                    {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2806 "parser.c"
    break;

  case 82: /* function_decl: TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 446 "src/parser/parser.y"
                                                                                                                                      {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        (yyval.node) = node;
    }
#line 2817 "parser.c"
    break;

  case 83: /* function_decl: TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 452 "src/parser/parser.y"
                                                                                                                                                {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        (yyval.node) = node;
    }
#line 2829 "parser.c"
    break;

  case 84: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression  */
#line 459 "src/parser/parser.y"
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node((yyvsp[0].node));
        add_to_node_list(body, return_stmt);
        (yyval.node) = create_function_node((yyvsp[-6].string), (yyvsp[-4].node_list), (yyvsp[-2].node), body);
    }
#line 2840 "parser.c"
    break;

  case 85: /* param_list: %empty  */
#line 468 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2848 "parser.c"
    break;

  case 86: /* param_list: param  */
#line 471 "src/parser/parser.y"
            {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2857 "parser.c"
    break;

  case 87: /* param_list: param_list TOKEN_COMMA param  */
#line 475 "src/parser/parser.y"
                                   {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2866 "parser.c"
    break;

  case 88: /* param: TOKEN_IDENTIFIER  */
#line 485 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[0].string), NULL, NULL); }
#line 2872 "parser.c"
    break;

  case 89: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 487 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[-2].string), (yyvsp[0].node), NULL); }
#line 2878 "parser.c"
    break;

  case 90: /* param: TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 489 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[-2].string), NULL, (yyvsp[0].node)); }
#line 2884 "parser.c"
    break;

  case 91: /* param: TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 491 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2890 "parser.c"
    break;

  case 92: /* type: TOKEN_IDENTIFIER  */
#line 496 "src/parser/parser.y"
                     {
        (yyval.node) = create_type_node((yyvsp[0].string));
    }
#line 2898 "parser.c"
    break;

  case 93: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
#line 499 "src/parser/parser.y"
                                      {
        (yyval.node) = create_optional_type_node((yyvsp[-1].string));
    }
#line 2906 "parser.c"
    break;

  case 94: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 502 "src/parser/parser.y"
                                         {
        (yyval.node) = create_array_type_node((yyvsp[0].node));
    }
#line 2914 "parser.c"
    break;

  case 95: /* dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 510 "src/parser/parser.y"
                                                      { (yyval.node) = create_dict_node((yyvsp[-1].node_list)); }
#line 2920 "parser.c"
    break;

  case 96: /* dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 511 "src/parser/parser.y"
                                                       { (yyval.node) = create_dict_node((yyvsp[-1].node_list)); }
#line 2926 "parser.c"
    break;

  case 97: /* dict_expr: TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 512 "src/parser/parser.y"
                                             { (yyval.node) = create_dict_node((yyvsp[-1].node_list)); }
#line 2932 "parser.c"
    break;

  case 98: /* dict_entries: %empty  */
#line 516 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2940 "parser.c"
    break;

  case 99: /* dict_entries: dict_entry_list  */
#line 519 "src/parser/parser.y"
                      {
        (yyval.node_list) = (yyvsp[0].node_list);
    }
#line 2948 "parser.c"
    break;

  case 100: /* dict_entry_list: expression TOKEN_FAT_ARROW expression  */
#line 525 "src/parser/parser.y"
                                          {
        (yyval.node_list) = create_node_list();
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyval.node_list), pair);
    }
#line 2958 "parser.c"
    break;

  case 101: /* dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression  */
#line 530 "src/parser/parser.y"
                                                                        {
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyvsp[-4].node_list), pair);
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 2968 "parser.c"
    break;

  case 102: /* bracket_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 540 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2976 "parser.c"
    break;

  case 103: /* return_type: %empty  */
#line 556 "src/parser/parser.y"
                {
        (yyval.node) = NULL;
    }
#line 2984 "parser.c"
    break;

  case 104: /* return_type: TOKEN_COLON type  */
#line 559 "src/parser/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2992 "parser.c"
    break;

  case 105: /* return_type: TOKEN_ARROW primary_expr  */
#line 562 "src/parser/parser.y"
                               {
        // Pour les retours directs: -> expr
        (yyval.node) = create_return_direct_node((yyvsp[0].node));
    }
#line 3001 "parser.c"
    break;

  case 106: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 569 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 3009 "parser.c"
    break;

  case 107: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 572 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_let_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3017 "parser.c"
    break;

  case 108: /* let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 575 "src/parser/parser.y"
                                                                   {
        ASTNode* node = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 3027 "parser.c"
    break;

  case 109: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 581 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_muts_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 3035 "parser.c"
    break;

  case 110: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 584 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_muts_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3043 "parser.c"
    break;

  case 111: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 589 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 3051 "parser.c"
    break;

  case 112: /* const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 592 "src/parser/parser.y"
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 3062 "parser.c"
    break;

  case 113: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 601 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-1].node_list), NULL);
    }
#line 3070 "parser.c"
    break;

  case 114: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 604 "src/parser/parser.y"
                                                                                                                       {
        (yyval.node) = create_if_node((yyvsp[-7].node), (yyvsp[-5].node_list), (yyvsp[-1].node_list));
    }
#line 3078 "parser.c"
    break;

  case 115: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE if_statement  */
#line 607 "src/parser/parser.y"
                                                                                           {
        // else if -> le else contient un autre if
        ASTNodeList* else_branch = create_node_list();
        add_to_node_list(else_branch, (yyvsp[0].node));
        (yyval.node) = create_if_node((yyvsp[-5].node), (yyvsp[-3].node_list), else_branch);
    }
#line 3089 "parser.c"
    break;

  case 116: /* break_statement: TOKEN_BREAK  */
#line 615 "src/parser/parser.y"
                {
        (yyval.node) = create_break_node();
    }
#line 3097 "parser.c"
    break;

  case 117: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 620 "src/parser/parser.y"
                                                                                                                                                      {
        ASTNode* init = create_let_node((yyvsp[-9].string), NULL, (yyvsp[-7].node));
        ASTNode* cond = (yyvsp[-5].node);
        ASTNode* inc = create_expr_statement((yyvsp[-3].node));
        (yyval.node) = create_for_node(init, cond, inc, (yyvsp[-1].node_list));
    }
#line 3108 "parser.c"
    break;

  case 118: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 626 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3116 "parser.c"
    break;

  case 119: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 629 "src/parser/parser.y"
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
#line 3134 "parser.c"
    break;

  case 120: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 642 "src/parser/parser.y"
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
#line 3154 "parser.c"
    break;

  case 121: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE_INC expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 657 "src/parser/parser.y"
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
#line 3170 "parser.c"
    break;

  case 122: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 672 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3178 "parser.c"
    break;

  case 123: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 678 "src/parser/parser.y"
                                                        {
        (yyval.node) = create_loop_node((yyvsp[-1].node_list));
    }
#line 3186 "parser.c"
    break;

  case 124: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 685 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3194 "parser.c"
    break;

  case 125: /* match_cases: match_case  */
#line 691 "src/parser/parser.y"
               {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3203 "parser.c"
    break;

  case 126: /* match_cases: match_cases match_case  */
#line 695 "src/parser/parser.y"
                             {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3212 "parser.c"
    break;

  case 127: /* match_case: pattern TOKEN_FAT_ARROW expression  */
#line 702 "src/parser/parser.y"
                                       {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3220 "parser.c"
    break;

  case 128: /* match_case: pattern TOKEN_FAT_ARROW block  */
#line 705 "src/parser/parser.y"
                                    {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (ASTNode*)(yyvsp[0].node));
    }
#line 3228 "parser.c"
    break;

  case 129: /* pattern: TOKEN_NUMBER  */
#line 711 "src/parser/parser.y"
                 { (yyval.node) = create_pattern_number((yyvsp[0].number)); }
#line 3234 "parser.c"
    break;

  case 130: /* pattern: TOKEN_STRING  */
#line 712 "src/parser/parser.y"
                   { (yyval.node) = create_pattern_string((yyvsp[0].string)); }
#line 3240 "parser.c"
    break;

  case 131: /* pattern: TOKEN_IDENTIFIER  */
#line 713 "src/parser/parser.y"
                       { (yyval.node) = create_pattern_ident((yyvsp[0].string)); }
#line 3246 "parser.c"
    break;

  case 132: /* pattern: TOKEN_UNDERSCORE  */
#line 714 "src/parser/parser.y"
                       { (yyval.node) = create_pattern_wildcard(); }
#line 3252 "parser.c"
    break;

  case 133: /* pattern: TOKEN_LBRACKET array_patterns TOKEN_RBRACKET  */
#line 715 "src/parser/parser.y"
                                                   { (yyval.node) = create_pattern_array((yyvsp[-1].node_list)); }
#line 3258 "parser.c"
    break;

  case 134: /* pattern: TOKEN_LET TOKEN_IDENTIFIER  */
#line 716 "src/parser/parser.y"
                                 { (yyval.node) = create_pattern_binding((yyvsp[0].string)); }
#line 3264 "parser.c"
    break;

  case 135: /* array_patterns: %empty  */
#line 720 "src/parser/parser.y"
                { (yyval.node_list) = NULL; }
#line 3270 "parser.c"
    break;

  case 136: /* array_patterns: pattern  */
#line 721 "src/parser/parser.y"
              { (yyval.node_list) = create_node_list(); add_to_node_list((yyval.node_list), (yyvsp[0].node)); }
#line 3276 "parser.c"
    break;

  case 137: /* array_patterns: array_patterns TOKEN_COMMA pattern  */
#line 722 "src/parser/parser.y"
                                         { add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node)); (yyval.node_list) = (yyvsp[-2].node_list); }
#line 3282 "parser.c"
    break;

  case 138: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 727 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_struct_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3290 "parser.c"
    break;

  case 139: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 730 "src/parser/parser.y"
                                                                                                           {
        (yyval.node) = create_struct_extend_node((yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3298 "parser.c"
    break;

  case 140: /* struct_fields: %empty  */
#line 736 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3306 "parser.c"
    break;

  case 141: /* struct_fields: struct_field  */
#line 739 "src/parser/parser.y"
                   {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3315 "parser.c"
    break;

  case 142: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
#line 743 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3324 "parser.c"
    break;

  case 143: /* struct_fields: struct_fields struct_field  */
#line 747 "src/parser/parser.y"
                                 {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3333 "parser.c"
    break;

  case 144: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 754 "src/parser/parser.y"
                                      {
        (yyval.node) = create_field_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 3341 "parser.c"
    break;

  case 145: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
#line 760 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_enum_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3349 "parser.c"
    break;

  case 146: /* enum_variants: %empty  */
#line 766 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3357 "parser.c"
    break;

  case 147: /* enum_variants: TOKEN_IDENTIFIER  */
#line 769 "src/parser/parser.y"
                       {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 3366 "parser.c"
    break;

  case 148: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 773 "src/parser/parser.y"
                                                 {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3375 "parser.c"
    break;

  case 149: /* module_decl: TOKEN_MODULE TOKEN_IDENTIFIER  */
#line 780 "src/parser/parser.y"
                                  {
        // Créer un nœud nil pour éviter l'erreur
        (yyval.node) = create_expr_statement(create_nil_node());
    }
#line 3384 "parser.c"
    break;

  case 150: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
#line 787 "src/parser/parser.y"
                                                                             {
        (yyval.node) = create_impl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3392 "parser.c"
    break;

  case 151: /* function_decl_list: %empty  */
#line 793 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3400 "parser.c"
    break;

  case 152: /* function_decl_list: function_decl  */
#line 796 "src/parser/parser.y"
                    {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3409 "parser.c"
    break;

  case 153: /* function_decl_list: function_decl_list function_decl  */
#line 800 "src/parser/parser.y"
                                       {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3418 "parser.c"
    break;

  case 154: /* return_statement: TOKEN_RETURN expression  */
#line 807 "src/parser/parser.y"
                            {
        (yyval.node) = create_return_node((yyvsp[0].node));
    }
#line 3426 "parser.c"
    break;

  case 155: /* return_statement: TOKEN_RETURN  */
#line 810 "src/parser/parser.y"
                   {
        (yyval.node) = create_return_node(NULL);
    }
#line 3434 "parser.c"
    break;

  case 160: /* expression: expression TOKEN_DOT TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 820 "src/parser/parser.y"
                                                                                    {
        // 'expression' est l'objet ($1), 'TOKEN_IDENTIFIER' est la méthode ($3)
        // 'argument_list' est la liste des arguments ($5)
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3444 "parser.c"
    break;

  case 161: /* binary_expr: expression TOKEN_PLUS expression  */
#line 828 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_ADD, (yyvsp[0].node));
    }
#line 3452 "parser.c"
    break;

  case 162: /* binary_expr: expression TOKEN_MINUS expression  */
#line 831 "src/parser/parser.y"
                                        {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_SUB, (yyvsp[0].node));
    }
#line 3460 "parser.c"
    break;

  case 163: /* binary_expr: expression TOKEN_MULTIPLY expression  */
#line 834 "src/parser/parser.y"
                                           {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
    }
#line 3468 "parser.c"
    break;

  case 164: /* binary_expr: expression TOKEN_DIVIDE expression  */
#line 837 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
    }
#line 3476 "parser.c"
    break;

  case 165: /* binary_expr: expression TOKEN_MODULO expression  */
#line 840 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
    }
#line 3484 "parser.c"
    break;

  case 166: /* binary_expr: expression TOKEN_EQ expression  */
#line 843 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_EQ, (yyvsp[0].node));
    }
#line 3492 "parser.c"
    break;

  case 167: /* binary_expr: expression TOKEN_NEQ expression  */
#line 846 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_NEQ, (yyvsp[0].node));
    }
#line 3500 "parser.c"
    break;

  case 168: /* binary_expr: expression TOKEN_LT expression  */
#line 849 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
    }
#line 3508 "parser.c"
    break;

  case 169: /* binary_expr: expression TOKEN_LTE expression  */
#line 852 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LTE, (yyvsp[0].node));
    }
#line 3516 "parser.c"
    break;

  case 170: /* binary_expr: expression TOKEN_GT expression  */
#line 855 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
    }
#line 3524 "parser.c"
    break;

  case 171: /* binary_expr: expression TOKEN_GTE expression  */
#line 858 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GTE, (yyvsp[0].node));
    }
#line 3532 "parser.c"
    break;

  case 172: /* binary_expr: expression TOKEN_AND expression  */
#line 861 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_AND, (yyvsp[0].node));
    }
#line 3540 "parser.c"
    break;

  case 173: /* binary_expr: expression TOKEN_OR expression  */
#line 864 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_OR, (yyvsp[0].node));
    }
#line 3548 "parser.c"
    break;

  case 174: /* binary_expr: expression TOKEN_ASSIGN expression  */
#line 867 "src/parser/parser.y"
                                         {
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3556 "parser.c"
    break;

  case 175: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
#line 870 "src/parser/parser.y"
                                              {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_ADD_ASSIGN, (yyvsp[0].node));
    }
#line 3564 "parser.c"
    break;

  case 176: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
#line 873 "src/parser/parser.y"
                                               {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_SUB_ASSIGN, (yyvsp[0].node));
    }
#line 3572 "parser.c"
    break;

  case 177: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
#line 876 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MUL_ASSIGN, (yyvsp[0].node));
    }
#line 3580 "parser.c"
    break;

  case 178: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
#line 879 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_DIV_ASSIGN, (yyvsp[0].node));
    }
#line 3588 "parser.c"
    break;

  case 179: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
#line 882 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MOD_ASSIGN, (yyvsp[0].node));
    }
#line 3596 "parser.c"
    break;

  case 180: /* unary_expr: TOKEN_NOT expression  */
#line 888 "src/parser/parser.y"
                         {
        (yyval.node) = create_unary_op(OP_NOT, (yyvsp[0].node));
    }
#line 3604 "parser.c"
    break;

  case 181: /* unary_expr: TOKEN_MINUS expression  */
#line 891 "src/parser/parser.y"
                             {
        (yyval.node) = create_unary_op(OP_NEG, (yyvsp[0].node));
    }
#line 3612 "parser.c"
    break;

  case 182: /* lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 898 "src/parser/parser.y"
                                                                     {
        (yyval.node) = create_lambda_node((yyvsp[-3].node_list), (yyvsp[-1].node_list));
    }
#line 3620 "parser.c"
    break;

  case 183: /* lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 901 "src/parser/parser.y"
                                                                                                 {
        (yyval.node) = create_lambda_node((yyvsp[-4].node_list), (yyvsp[-1].node_list));
    }
#line 3628 "parser.c"
    break;

  case 184: /* primary_expr: TOKEN_NUMBER  */
#line 910 "src/parser/parser.y"
                 {
        (yyval.node) = create_number_node((yyvsp[0].number));
    }
#line 3636 "parser.c"
    break;

  case 185: /* primary_expr: TOKEN_FLOAT  */
#line 913 "src/parser/parser.y"
                  {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 3644 "parser.c"
    break;

  case 186: /* primary_expr: TOKEN_STRING  */
#line 916 "src/parser/parser.y"
                   {
        (yyval.node) = create_string_node((yyvsp[0].string));
    }
#line 3652 "parser.c"
    break;

  case 187: /* primary_expr: TOKEN_TRUE  */
#line 919 "src/parser/parser.y"
                 {
        (yyval.node) = create_bool_node(1);
    }
#line 3660 "parser.c"
    break;

  case 188: /* primary_expr: TOKEN_FALSE  */
#line 922 "src/parser/parser.y"
                  {
        (yyval.node) = create_bool_node(0);
    }
#line 3668 "parser.c"
    break;

  case 189: /* primary_expr: TOKEN_NIL  */
#line 925 "src/parser/parser.y"
                {
        (yyval.node) = create_nil_node();
    }
#line 3676 "parser.c"
    break;

  case 190: /* primary_expr: TOKEN_IDENTIFIER  */
#line 928 "src/parser/parser.y"
                       {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 3684 "parser.c"
    break;

  case 191: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 931 "src/parser/parser.y"
                                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3692 "parser.c"
    break;

  case 204: /* f_string: TOKEN_F_STRING  */
#line 949 "src/parser/parser.y"
                   {
        (yyval.node) = parse_f_string((yyvsp[0].string));
    }
#line 3700 "parser.c"
    break;

  case 205: /* member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER  */
#line 955 "src/parser/parser.y"
                                            {
        (yyval.node) = create_member_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3708 "parser.c"
    break;

  case 206: /* member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 958 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_static_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3716 "parser.c"
    break;

  case 207: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 964 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_call_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3724 "parser.c"
    break;

  case 208: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 967 "src/parser/parser.y"
                                                                                               {
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3732 "parser.c"
    break;

  case 209: /* argument_list: %empty  */
#line 973 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3740 "parser.c"
    break;

  case 210: /* argument_list: expression  */
#line 976 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_arg_list();
        add_arg((yyval.node_list), (yyvsp[0].node));
    }
#line 3749 "parser.c"
    break;

  case 211: /* argument_list: argument_list TOKEN_COMMA expression  */
#line 980 "src/parser/parser.y"
                                           {
        add_arg((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3758 "parser.c"
    break;

  case 212: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
#line 987 "src/parser/parser.y"
                                              {
        (yyval.node) = create_array_node((yyvsp[-1].node_list));
    }
#line 3766 "parser.c"
    break;

  case 213: /* await_expr: TOKEN_AWAIT primary_expr  */
#line 1002 "src/parser/parser.y"
                             {
        (yyval.node) = create_await_node((yyvsp[0].node));
    }
#line 3774 "parser.c"
    break;

  case 214: /* await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 1005 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_await_block_node((yyvsp[-1].node_list));
    }
#line 3782 "parser.c"
    break;

  case 215: /* spawn_expr: TOKEN_SPAWN primary_expr  */
#line 1012 "src/parser/parser.y"
                             {
        (yyval.node) = create_spawn_node((yyvsp[0].node));
    }
#line 3790 "parser.c"
    break;

  case 216: /* array_items: %empty  */
#line 1024 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3798 "parser.c"
    break;

  case 217: /* array_items: expression  */
#line 1027 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3807 "parser.c"
    break;

  case 218: /* array_items: array_items TOKEN_COMMA expression  */
#line 1031 "src/parser/parser.y"
                                         {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3816 "parser.c"
    break;

  case 219: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
#line 1038 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_struct_init_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3824 "parser.c"
    break;

  case 220: /* struct_init_fields: %empty  */
#line 1044 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3832 "parser.c"
    break;

  case 221: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 1047 "src/parser/parser.y"
                                              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
    }
#line 3841 "parser.c"
    break;

  case 222: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 1051 "src/parser/parser.y"
                                                                             {
        add_to_node_list((yyvsp[-4].node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 3850 "parser.c"
    break;

  case 223: /* block: TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 1058 "src/parser/parser.y"
                                             {
        (yyval.node) = (ASTNode*)(yyvsp[-1].node_list);
    }
#line 3858 "parser.c"
    break;


#line 3862 "parser.c"

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

#line 1063 "src/parser/parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

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
  YYSYMBOL_TOKEN_GOLEM = 35,               /* TOKEN_GOLEM  */
  YYSYMBOL_TOKEN_ONLY = 36,                /* TOKEN_ONLY  */
  YYSYMBOL_TOKEN_TIMEOUT = 37,             /* TOKEN_TIMEOUT  */
  YYSYMBOL_TOKEN_SANDBOX = 38,             /* TOKEN_SANDBOX  */
  YYSYMBOL_TOKEN_ALLOW_FFI = 39,           /* TOKEN_ALLOW_FFI  */
  YYSYMBOL_TOKEN_ASYNC = 40,               /* TOKEN_ASYNC  */
  YYSYMBOL_TOKEN_AWAIT = 41,               /* TOKEN_AWAIT  */
  YYSYMBOL_TOKEN_SPAWN = 42,               /* TOKEN_SPAWN  */
  YYSYMBOL_TOKEN_WITH = 43,                /* TOKEN_WITH  */
  YYSYMBOL_TOKEN_LAMBDA = 44,              /* TOKEN_LAMBDA  */
  YYSYMBOL_TOKEN_EXTENDS = 45,             /* TOKEN_EXTENDS  */
  YYSYMBOL_TOKEN_UNDERSCORE = 46,          /* TOKEN_UNDERSCORE  */
  YYSYMBOL_TOKEN_SWITCH = 47,              /* TOKEN_SWITCH  */
  YYSYMBOL_TOKEN_USE = 48,                 /* TOKEN_USE  */
  YYSYMBOL_TOKEN_AT = 49,                  /* TOKEN_AT  */
  YYSYMBOL_TOKEN_PLUS = 50,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 51,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MULTIPLY = 52,            /* TOKEN_MULTIPLY  */
  YYSYMBOL_TOKEN_DIVIDE = 53,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 54,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_ASSIGN = 55,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 56,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 57,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 58,     /* TOKEN_MULTIPLY_ASSIGN  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 59,       /* TOKEN_DIVIDE_ASSIGN  */
  YYSYMBOL_TOKEN_MODULO_ASSIGN = 60,       /* TOKEN_MODULO_ASSIGN  */
  YYSYMBOL_TOKEN_EQ = 61,                  /* TOKEN_EQ  */
  YYSYMBOL_TOKEN_NEQ = 62,                 /* TOKEN_NEQ  */
  YYSYMBOL_TOKEN_LT = 63,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LTE = 64,                 /* TOKEN_LTE  */
  YYSYMBOL_TOKEN_GT = 65,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GTE = 66,                 /* TOKEN_GTE  */
  YYSYMBOL_TOKEN_AND = 67,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 68,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_NOT = 69,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_AMP = 70,                 /* TOKEN_AMP  */
  YYSYMBOL_TOKEN_PIPE = 71,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_XOR = 72,                 /* TOKEN_XOR  */
  YYSYMBOL_TOKEN_LSHIFT = 73,              /* TOKEN_LSHIFT  */
  YYSYMBOL_TOKEN_RSHIFT = 74,              /* TOKEN_RSHIFT  */
  YYSYMBOL_TOKEN_DOUBLE_COLON = 75,        /* TOKEN_DOUBLE_COLON  */
  YYSYMBOL_TOKEN_DOT = 76,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_SECURITY = 77,            /* TOKEN_SECURITY  */
  YYSYMBOL_TOKEN_COLON = 78,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_SEMICOLON = 79,           /* TOKEN_SEMICOLON  */
  YYSYMBOL_TOKEN_COMMA = 80,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_ARROW = 81,               /* TOKEN_ARROW  */
  YYSYMBOL_TOKEN_FAT_ARROW = 82,           /* TOKEN_FAT_ARROW  */
  YYSYMBOL_TOKEN_PIPE_FORWARD = 83,        /* TOKEN_PIPE_FORWARD  */
  YYSYMBOL_TOKEN_OPTIONAL = 84,            /* TOKEN_OPTIONAL  */
  YYSYMBOL_TOKEN_COALESCE = 85,            /* TOKEN_COALESCE  */
  YYSYMBOL_TOKEN_RANGE = 86,               /* TOKEN_RANGE  */
  YYSYMBOL_TOKEN_RANGE_INC = 87,           /* TOKEN_RANGE_INC  */
  YYSYMBOL_TOKEN_MUTS = 88,                /* TOKEN_MUTS  */
  YYSYMBOL_TOKEN_SYSF = 89,                /* TOKEN_SYSF  */
  YYSYMBOL_TOKEN_SH = 90,                  /* TOKEN_SH  */
  YYSYMBOL_TOKEN_LPAREN = 91,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 92,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_LBRACE = 93,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 94,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_LBRACKET = 95,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 96,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_TRY = 97,                 /* TOKEN_TRY  */
  YYSYMBOL_TOKEN_CATCH = 98,               /* TOKEN_CATCH  */
  YYSYMBOL_TOKEN_FINALLY = 99,             /* TOKEN_FINALLY  */
  YYSYMBOL_TOKEN_THROW = 100,              /* TOKEN_THROW  */
  YYSYMBOL_TOKEN_EXCEPT = 101,             /* TOKEN_EXCEPT  */
  YYSYMBOL_TOKEN_RAISE = 102,              /* TOKEN_RAISE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 103,         /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_NUMBER = 104,             /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_FLOAT = 105,              /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_STRING = 106,             /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_F_STRING = 107,           /* TOKEN_F_STRING  */
  YYSYMBOL_YYACCEPT = 108,                 /* $accept  */
  YYSYMBOL_switch_statement = 109,         /* switch_statement  */
  YYSYMBOL_ternary_expr = 110,             /* ternary_expr  */
  YYSYMBOL_program = 111,                  /* program  */
  YYSYMBOL_statement_list = 112,           /* statement_list  */
  YYSYMBOL_unsafe_stmt = 113,              /* unsafe_stmt  */
  YYSYMBOL_continue_statement = 114,       /* continue_statement  */
  YYSYMBOL_statement = 115,                /* statement  */
  YYSYMBOL_with_statement = 116,           /* with_statement  */
  YYSYMBOL_sysf_expr = 117,                /* sysf_expr  */
  YYSYMBOL_use_statement = 118,            /* use_statement  */
  YYSYMBOL_use_path = 119,                 /* use_path  */
  YYSYMBOL_sh_expr = 120,                  /* sh_expr  */
  YYSYMBOL_nnl_statement = 121,            /* nnl_statement  */
  YYSYMBOL_try_statement = 122,            /* try_statement  */
  YYSYMBOL_catch_block = 123,              /* catch_block  */
  YYSYMBOL_finally_block = 124,            /* finally_block  */
  YYSYMBOL_throw_statement = 125,          /* throw_statement  */
  YYSYMBOL_jmp_statement = 126,            /* jmp_statement  */
  YYSYMBOL_import_statement = 127,         /* import_statement  */
  YYSYMBOL_import_path_tail = 128,         /* import_path_tail  */
  YYSYMBOL_import_path = 129,              /* import_path  */
  YYSYMBOL_import_constraints = 130,       /* import_constraints  */
  YYSYMBOL_import_options = 131,           /* import_options  */
  YYSYMBOL_name_list = 132,                /* name_list  */
  YYSYMBOL_export_statement = 133,         /* export_statement  */
  YYSYMBOL_export_list = 134,              /* export_list  */
  YYSYMBOL_export_item = 135,              /* export_item  */
  YYSYMBOL_import_impl_list = 136,         /* import_impl_list  */
  YYSYMBOL_import_impl_item = 137,         /* import_impl_item  */
  YYSYMBOL_packet_decl = 138,              /* packet_decl  */
  YYSYMBOL_decorator_list = 139,           /* decorator_list  */
  YYSYMBOL_decorator = 140,                /* decorator  */
  YYSYMBOL_function_decl = 141,            /* function_decl  */
  YYSYMBOL_param_list = 142,               /* param_list  */
  YYSYMBOL_param = 143,                    /* param  */
  YYSYMBOL_type = 144,                     /* type  */
  YYSYMBOL_dict_expr = 145,                /* dict_expr  */
  YYSYMBOL_dict_entries = 146,             /* dict_entries  */
  YYSYMBOL_dict_entry_list = 147,          /* dict_entry_list  */
  YYSYMBOL_bracket_access = 148,           /* bracket_access  */
  YYSYMBOL_return_type = 149,              /* return_type  */
  YYSYMBOL_let_decl = 150,                 /* let_decl  */
  YYSYMBOL_const_decl = 151,               /* const_decl  */
  YYSYMBOL_if_statement = 152,             /* if_statement  */
  YYSYMBOL_break_statement = 153,          /* break_statement  */
  YYSYMBOL_for_statement = 154,            /* for_statement  */
  YYSYMBOL_while_statement = 155,          /* while_statement  */
  YYSYMBOL_loop_statement = 156,           /* loop_statement  */
  YYSYMBOL_match_statement = 157,          /* match_statement  */
  YYSYMBOL_match_cases = 158,              /* match_cases  */
  YYSYMBOL_match_case = 159,               /* match_case  */
  YYSYMBOL_pattern = 160,                  /* pattern  */
  YYSYMBOL_array_patterns = 161,           /* array_patterns  */
  YYSYMBOL_struct_decl = 162,              /* struct_decl  */
  YYSYMBOL_struct_fields = 163,            /* struct_fields  */
  YYSYMBOL_struct_field = 164,             /* struct_field  */
  YYSYMBOL_enum_decl = 165,                /* enum_decl  */
  YYSYMBOL_enum_variants = 166,            /* enum_variants  */
  YYSYMBOL_golem_decl = 167,               /* golem_decl  */
  YYSYMBOL_impl_decl = 168,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 169,       /* function_decl_list  */
  YYSYMBOL_return_statement = 170,         /* return_statement  */
  YYSYMBOL_expression = 171,               /* expression  */
  YYSYMBOL_binary_expr = 172,              /* binary_expr  */
  YYSYMBOL_unary_expr = 173,               /* unary_expr  */
  YYSYMBOL_lambda_expr = 174,              /* lambda_expr  */
  YYSYMBOL_primary_expr = 175,             /* primary_expr  */
  YYSYMBOL_f_string = 176,                 /* f_string  */
  YYSYMBOL_member_access = 177,            /* member_access  */
  YYSYMBOL_call_expr = 178,                /* call_expr  */
  YYSYMBOL_argument_list = 179,            /* argument_list  */
  YYSYMBOL_array_expr = 180,               /* array_expr  */
  YYSYMBOL_await_expr = 181,               /* await_expr  */
  YYSYMBOL_spawn_expr = 182,               /* spawn_expr  */
  YYSYMBOL_array_items = 183,              /* array_items  */
  YYSYMBOL_struct_expr = 184,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 185,       /* struct_init_fields  */
  YYSYMBOL_block = 186                     /* block  */
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
#define YYFINAL  162
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4462

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  108
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  79
/* YYNRULES -- Number of rules.  */
#define YYNRULES  233
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  541

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   362


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
     105,   106,   107
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   128,   128,   133,   140,   146,   150,   156,   161,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   199,   204,   207,   214,
     218,   222,   230,   233,   242,   245,   251,   257,   260,   266,
     269,   275,   281,   284,   289,   292,   301,   305,   309,   313,
     317,   323,   332,   335,   344,   347,   353,   362,   368,   371,
     377,   381,   388,   392,   400,   404,   411,   417,   425,   429,
     437,   445,   455,   459,   467,   471,   475,   482,   491,   494,
     497,   503,   510,   517,   521,   528,   531,   535,   544,   546,
     548,   550,   556,   559,   562,   570,   571,   572,   576,   579,
     585,   590,   600,   616,   619,   622,   629,   632,   635,   641,
     644,   649,   652,   661,   664,   667,   675,   680,   686,   689,
     702,   717,   732,   738,   745,   751,   755,   762,   765,   771,
     772,   773,   774,   775,   776,   780,   781,   782,   787,   790,
     796,   799,   803,   807,   814,   820,   826,   829,   833,   840,
     846,   852,   855,   859,   866,   869,   875,   876,   877,   878,
     879,   887,   890,   893,   896,   899,   902,   905,   908,   911,
     914,   917,   920,   923,   926,   929,   932,   935,   938,   941,
     947,   950,   957,   960,   969,   972,   975,   978,   981,   984,
     987,   990,   993,   994,   995,   996,   997,   998,   999,  1000,
    1001,  1002,  1003,  1004,  1008,  1014,  1017,  1023,  1026,  1032,
    1035,  1039,  1046,  1061,  1064,  1071,  1083,  1086,  1090,  1097,
    1103,  1106,  1110,  1117
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
  "TOKEN_UNSAFE", "TOKEN_NNL", "TOKEN_JMP", "TOKEN_GOLEM", "TOKEN_ONLY",
  "TOKEN_TIMEOUT", "TOKEN_SANDBOX", "TOKEN_ALLOW_FFI", "TOKEN_ASYNC",
  "TOKEN_AWAIT", "TOKEN_SPAWN", "TOKEN_WITH", "TOKEN_LAMBDA",
  "TOKEN_EXTENDS", "TOKEN_UNDERSCORE", "TOKEN_SWITCH", "TOKEN_USE",
  "TOKEN_AT", "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_MULTIPLY",
  "TOKEN_DIVIDE", "TOKEN_MODULO", "TOKEN_ASSIGN", "TOKEN_PLUS_ASSIGN",
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
  "statement", "with_statement", "sysf_expr", "use_statement", "use_path",
  "sh_expr", "nnl_statement", "try_statement", "catch_block",
  "finally_block", "throw_statement", "jmp_statement", "import_statement",
  "import_path_tail", "import_path", "import_constraints",
  "import_options", "name_list", "export_statement", "export_list",
  "export_item", "import_impl_list", "import_impl_item", "packet_decl",
  "decorator_list", "decorator", "function_decl", "param_list", "param",
  "type", "dict_expr", "dict_entries", "dict_entry_list", "bracket_access",
  "return_type", "let_decl", "const_decl", "if_statement",
  "break_statement", "for_statement", "while_statement", "loop_statement",
  "match_statement", "match_cases", "match_case", "pattern",
  "array_patterns", "struct_decl", "struct_fields", "struct_field",
  "enum_decl", "enum_variants", "golem_decl", "impl_decl",
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

#define YYPACT_NINF (-406)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    3330,   -68,   -42,    -2,    16,    80,   237,   237,   332,   237,
      66,  -406,  -406,   -29,   104,    87,    89,    98,   114,   237,
    -406,  -406,  -406,    81,   120,   131,   147,   151,   152,   226,
     428,  3509,   237,   -48,   237,   162,   164,   237,   237,   171,
    3425,  3454,   237,   237,   237,   178,   237,   237,  -406,  -406,
    -406,  -406,  -406,  -406,  -406,   275,  3330,  -406,  -406,  -406,
    -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,
    -406,    24,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,
    -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  4378,
    -406,  -406,  -406,    47,  -406,  -406,  -406,  -406,  -406,  -406,
    -406,   237,   237,   189,    13,   235,  4378,  3722,    11,  3766,
    3810,  3330,   188,   188,  -406,   216,   -15,   -10,  -406,   209,
     -24,   210,   211,  3854,   202,   204,   207,   307,   220,  3330,
     221,   237,  -406,   212,  3330,    47,    47,  3596,   215,    22,
      67,  -406,  3898,  -406,    -5,    55,    27,   -12,    34,   237,
    4378,   237,  4378,  4074,   227,   242,  4203,  4378,    52,  3330,
    4378,  4378,  -406,  -406,   222,   318,  -406,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   228,   237,   230,   231,
     237,   237,   243,   244,   215,   237,   154,   237,  3330,   237,
     237,  3330,  3330,   600,   216,   216,   236,   245,   103,  -406,
     246,  -406,    -4,  -406,  3330,   251,   252,   257,    18,    14,
     238,   269,   290,   262,   268,   705,  3330,  4378,   255,   810,
    4203,   272,   -17,   237,   154,   215,  3330,    14,   282,   129,
     283,   237,   237,   154,  4117,  4160,  -406,  -406,   237,   237,
     237,  -406,   915,   256,   284,    27,    27,   -12,   -12,   -12,
    4378,  4378,  4378,  4378,  4378,  4378,   475,   475,   161,   161,
     161,   161,   316,   233,   281,  4238,   297,  -406,  4378,   108,
    3631,  -406,  -406,   118,  4378,   293,   306,   338,  4378,  1020,
    3678,  4273,  1125,  1230,  -406,  -406,   301,   292,   319,     3,
      57,  -406,  -406,   -10,  -406,  1335,   305,   321,   -50,  -406,
    -406,    61,    19,  -406,    12,   302,  -406,    14,  -406,  -406,
    -406,     4,  -406,   322,   215,   237,   237,   315,   329,    64,
    -406,  1440,   215,  -406,   331,   320,  4378,   359,  -406,  1545,
      10,  -406,   312,  -406,   325,   128,  4378,   362,  -406,  -406,
    4308,  4378,  4378,    56,   215,   327,   237,   237,   237,   237,
    -406,  -406,   175,   154,  -406,   237,   409,   237,   237,  3330,
     237,  -406,  -406,   103,  -406,  -406,   333,   384,  -406,   403,
    -406,  -406,  -406,   252,   154,   252,  -406,  -406,   323,  -406,
    -406,  -406,  -406,  -406,    53,  -406,  -406,  3538,   136,  4378,
    4378,   215,   237,   326,  -406,  -406,   138,  3330,  3330,   237,
    -406,  -406,  -406,   102,   237,  -406,   237,   237,   339,   343,
     341,   141,   215,   146,  4378,   159,  4378,   154,  3509,   165,
    -406,  4378,     9,  3942,  3986,  1650,  4343,   125,   312,   363,
    -406,    -9,  -406,  -406,  -406,    14,  -406,  3330,  4378,  -406,
     175,   167,  4378,   364,   175,  -406,  1755,  4378,   342,  -406,
     168,  4378,  4378,   344,   345,   353,  -406,   175,   172,  -406,
    -406,  -406,    47,   237,  3330,  3330,  -406,  3330,  3330,  -406,
     237,  -406,    54,  -406,  -406,  1860,   356,   175,   237,   357,
    -406,  -406,  -406,   365,   366,  3330,   358,   175,  4378,  1965,
    2070,  2175,  2280,  4030,  -406,  -406,  3330,   367,  4378,  3330,
     368,   370,  2385,  3330,   371,  -406,  -406,  -406,  -406,  3330,
    2490,  3330,  2595,  3330,  3330,  -406,  2700,  3330,  2805,  -406,
    2910,  -406,  3015,  3120,  -406,  3225,  -406,  -406,  -406,  -406,
    -406
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,   165,     0,     0,     0,
       0,   126,     8,     0,     0,     0,     0,     0,     0,     0,
     197,   198,   199,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,   226,     0,     0,     0,   200,   194,
     195,   196,   214,    21,   168,     0,     4,    29,    11,     5,
      33,   210,    18,   211,    12,    15,    16,    13,     9,    10,
      17,     0,    82,    19,   204,   203,    24,    26,    27,    25,
      28,    30,    31,    32,    20,    22,    14,    23,    34,    35,
     166,   167,   208,   169,   213,   207,   202,   205,   209,   212,
     206,   108,   108,     0,     0,     0,   164,     0,   200,     0,
       0,     0,     0,     0,    62,    64,    56,     0,    72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,   159,     0,   108,   223,   225,     0,    95,    98,
       0,    96,     0,    42,    39,    84,   191,   190,     0,     0,
      38,     0,    45,     0,     0,   109,     0,   227,     0,     0,
      52,    53,     1,     6,     0,     0,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     219,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,    66,     0,     0,     0,    58,
       0,    76,     0,    74,     0,     0,   150,   156,   161,     0,
       0,     0,     0,     0,   230,     0,     0,    55,     0,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   219,     0,     0,     0,     0,   201,   107,     0,     0,
       0,   222,     0,     0,     0,   171,   172,   173,   174,   175,
     184,   185,   186,   187,   188,   189,   176,   177,   178,   179,
     180,   181,   182,   183,     0,     0,   216,   215,   220,     0,
       0,   105,   106,     0,   116,     0,   102,     0,   121,     0,
       0,     0,     0,     0,   133,    63,    57,     0,     0,     0,
       0,    78,    77,     0,    73,     0,     0,     0,     0,   151,
     157,     0,     0,   162,     0,     0,   142,   145,   141,   139,
     140,     0,   135,     0,    95,     0,     0,     0,     0,     0,
       7,     0,    95,   224,     0,     0,   100,    99,    97,     0,
       0,    41,     0,    43,    86,     0,   119,     0,    37,    44,
       0,   110,   228,     0,    95,     0,   219,     0,   219,     0,
     217,   112,   113,     0,   103,     0,   123,     0,     0,     0,
       0,   128,   132,     0,    59,    80,     0,     0,    67,     0,
      60,    75,    81,   150,     0,     0,   148,   153,     0,   155,
     160,   163,   144,   146,     0,   134,   136,     0,     0,   118,
     122,    95,     0,     0,   229,    46,     0,     0,     0,     0,
     192,     2,    70,     0,   219,    85,     0,     0,     0,     0,
      47,     0,    95,     0,     3,     0,   221,     0,     0,     0,
     104,   117,     0,     0,     0,     0,     0,     0,     0,    69,
      79,     0,   154,   152,   158,     0,   143,   108,   137,   138,
     113,     0,   231,     0,   113,    36,     0,   101,     0,    40,
       0,   120,   111,     0,     0,     0,    48,   113,     0,   170,
     218,   114,   115,     0,     0,     0,   125,     0,     0,   129,
       0,    61,     0,   149,   147,     0,     0,   113,     0,     0,
     193,    71,    87,     0,     0,     0,     0,   113,    92,     0,
       0,     0,     0,     0,    68,   233,     0,     0,   232,     0,
       0,     0,     0,     0,     0,    88,   124,   130,   131,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,    89,
       0,    90,     0,     0,    93,     0,   127,    91,    49,    50,
      94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -406,  -406,  -406,  -406,    75,  -406,  -406,   -23,  -406,  -406,
    -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,
      40,  -406,   160,    78,    28,  -406,  -406,   170,    92,    96,
    -406,  -406,   397,  -199,  -129,   249,  -228,  -406,    25,  -406,
    -406,  -405,  -406,  -406,    39,  -406,  -406,  -406,  -406,  -406,
     248,  -294,  -309,  -406,  -406,    97,  -301,  -406,  -406,  -406,
    -406,  -406,  -406,    -6,  -406,  -406,  -406,   -26,  -406,  -406,
    -406,  -227,  -406,  -406,  -406,  -406,  -406,  -406,  -406
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,   144,    63,    64,    65,   420,   466,    66,    67,    68,
     115,   116,   209,   299,   413,    69,   212,   213,   300,   301,
      70,    71,    72,    73,   140,   141,   287,    74,   154,   155,
      75,   429,    76,    77,    78,    79,    80,    81,    82,    83,
     321,   322,   323,   394,    84,   308,   309,    85,   311,    86,
      87,   314,    88,    89,    90,    91,    92,    93,    94,    95,
      96,   279,    97,    98,    99,   158,   100,   329,   449
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     106,   107,   109,   110,   135,   136,   337,   387,   393,   232,
     315,   210,   207,   123,   345,   347,   315,     3,     7,   313,
     315,   215,   238,     3,   124,   101,   137,   396,   142,   164,
     385,   146,   147,   163,   150,   152,   153,   156,   157,   199,
     160,   161,   312,   138,   386,   486,   396,   112,   312,   489,
     316,   102,    29,   307,   165,   139,   316,   113,    29,   127,
     316,    36,   496,   235,   186,   283,   200,    36,   195,   216,
     239,   385,   187,    36,   114,   335,   303,   233,   208,   169,
     170,   171,   507,   377,   443,   483,   124,   125,   126,   242,
     304,   196,   514,   211,   307,   156,   156,   378,   395,   317,
     234,   103,   475,   186,   411,   317,   390,   318,   319,   317,
     320,   187,   243,   318,   319,   391,   320,   318,   319,   104,
     320,   127,   188,   189,   297,   227,   192,   193,   230,   423,
     240,   425,   250,   445,   458,   430,   484,   379,   190,   298,
     387,   388,   191,   244,   403,   245,   241,   235,   251,   446,
     504,   380,   204,   205,   418,   389,   442,   419,   404,   111,
     236,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     163,   275,   458,   105,   278,   280,   203,   460,   359,   284,
     119,   288,   120,   290,   291,   398,   459,   117,   235,   471,
     360,   121,   163,   406,   225,   379,   163,   118,   359,   229,
     362,   167,   168,   169,   170,   171,   235,   122,   235,   481,
     415,   235,   342,   128,   129,   421,   359,   336,   450,   163,
     454,   133,   343,   467,   252,   278,   346,   186,   469,   359,
       1,     2,   350,   351,   352,   187,   473,   235,   359,   285,
     130,   470,   235,   427,   131,   132,   428,   286,   474,   487,
     492,    20,    21,    22,   497,   143,   163,   145,    24,   163,
     163,   159,   451,   289,   148,   162,   292,   293,    30,    31,
     194,    33,   163,   167,   168,   169,   170,   171,    37,   305,
     197,   114,   206,   468,   178,   179,   180,   181,   182,   183,
     184,   331,   214,   217,   218,   220,    38,   221,   163,   186,
     222,   339,   223,   224,   226,   228,   163,   187,   139,   399,
     400,   247,   248,   254,   325,   253,    40,    41,    42,   324,
      43,   274,    44,   276,   277,     1,     2,   281,   282,   295,
      48,    49,    50,    51,    52,   326,   332,   354,   296,   302,
     278,   424,   278,   426,   306,   307,    20,    21,    22,   431,
     310,   433,   434,    24,   436,   327,   167,   168,   169,   170,
     171,   328,   356,    30,    31,   334,    33,   178,   179,   180,
     181,   182,   183,    37,   455,   341,   344,   355,   358,   363,
     364,   448,   186,   365,   373,   375,   452,   376,   383,   384,
     187,    38,   472,   457,   397,   392,   401,   402,   278,   407,
     461,   462,   163,   408,   409,   412,   414,   416,   422,   432,
     298,    40,    41,    42,   297,    43,   444,    44,   438,   453,
     463,     1,     2,   163,   464,   108,    49,    50,    51,    52,
     465,   230,   488,   377,   435,   491,   495,   493,   494,   506,
     509,   513,    20,    21,    22,   439,   374,   510,   511,    24,
     521,   523,   163,   524,   527,   437,   482,   498,   166,    30,
      31,   476,    33,   381,   503,   440,   163,   163,   163,   163,
     441,     0,   508,   456,   338,   340,     0,     0,     0,   163,
       0,     0,     0,     0,     0,     0,     0,   163,     0,   163,
       0,     0,     0,   163,     0,   163,     0,   163,     0,   163,
     163,     0,   163,     0,     0,     0,     0,    40,    41,    42,
       0,   134,   485,    44,     0,   167,   168,   169,   170,   171,
       0,    48,    49,    50,    51,    52,     0,     0,   180,   181,
     182,   183,     0,     0,     0,     0,     0,     0,     0,   499,
     500,   186,   501,   502,     0,     0,     0,     0,     0,   187,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     512,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   520,     0,     0,   522,     0,     0,     0,   526,     0,
       0,     0,     0,     0,   528,     0,   530,     0,   532,   533,
       0,     0,   535,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   294,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   330,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   333,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   353,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   366,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   371,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   372,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   382,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   405,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   410,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   479,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   490,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   505,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   515,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   516,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   517,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   518,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   525,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   529,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   531,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   534,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   536,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   537,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   538,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,   539,    44,     0,    45,     0,     0,
      46,     0,    47,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    41,    42,     0,    43,   540,
      44,     0,    45,     0,     0,    46,     0,    47,    48,    49,
      50,    51,    52,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,    43,     0,    44,     0,    45,     1,     2,
      46,     0,    47,    48,    49,    50,    51,    52,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,     0,     0,     0,     0,    24,     1,     2,     0,
       0,     0,     0,     0,     0,     0,    30,    31,     0,    33,
       0,     0,     0,     0,     0,     0,    37,     0,    20,    21,
      22,     0,     0,     0,     0,    24,     0,     0,     0,     0,
       0,     0,     0,     0,    38,    30,    31,     0,    33,     0,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,     1,     2,    40,    41,   149,     0,    43,     0,
      44,     0,     0,    38,     0,     0,     0,     0,    48,    49,
      50,    51,    52,    20,    21,    22,     0,     0,     0,     0,
      24,     1,     2,    40,    41,   151,     0,    43,     0,    44,
      30,    31,     0,    33,     0,     0,     0,    48,    49,    50,
      51,    52,    20,    21,    22,     0,     0,     0,     0,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,     0,    33,     0,     0,     0,     0,     0,     0,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    40,    41,
      42,     0,    43,     0,    44,     0,     0,    38,     0,     0,
       0,     0,    48,    49,    50,    51,    52,     0,     0,     0,
       0,     0,     0,   231,     0,     0,     0,    40,    41,    42,
       0,   447,     0,    44,     0,     0,     0,     0,     0,     0,
       0,    48,    49,    50,    51,    52,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,     0,     0,     0,     0,     0,
       0,     0,   186,     0,     0,     0,     0,     0,     0,     0,
     187,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       0,     0,     0,     0,     0,     0,     0,   186,     0,     0,
       0,     0,     0,     0,     0,   187,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   361,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,     0,     0,     0,
       0,     0,     0,     0,   186,     0,     0,     0,     0,     0,
       0,     0,   187,     0,   367,   368,     0,     0,     0,     0,
       0,   369,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,     0,     0,     0,     0,     0,     0,     0,   186,     0,
       0,     0,     0,     0,     0,     0,   187,     0,     0,     0,
       0,     0,     0,     0,     0,   198,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,     0,     0,     0,     0,     0,
       0,     0,   186,     0,     0,     0,     0,     0,     0,     0,
     187,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,     0,
       0,     0,     0,     0,     0,     0,   186,     0,     0,     0,
       0,     0,     0,     0,   187,     0,     0,     0,     0,     0,
       0,     0,     0,   202,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,     0,     0,     0,     0,     0,     0,     0,
     186,     0,     0,     0,     0,     0,     0,     0,   187,     0,
       0,     0,     0,     0,     0,     0,     0,   219,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,     0,     0,     0,
       0,     0,     0,     0,   186,     0,     0,     0,     0,     0,
       0,     0,   187,     0,     0,     0,     0,     0,     0,     0,
       0,   237,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,     0,     0,     0,     0,     0,     0,     0,   186,     0,
       0,     0,     0,     0,     0,     0,   187,     0,     0,     0,
       0,     0,     0,     0,     0,   477,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,     0,     0,     0,     0,     0,
       0,     0,   186,     0,     0,     0,     0,     0,     0,     0,
     187,     0,     0,     0,     0,     0,     0,     0,     0,   478,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,     0,
       0,     0,     0,     0,     0,     0,   186,     0,     0,     0,
       0,     0,     0,     0,   187,     0,     0,     0,     0,     0,
       0,     0,     0,   519,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,     0,     0,     0,     0,     0,     0,     0,
     186,     0,     0,     0,     0,     0,     0,     0,   187,     0,
       0,     0,     0,     0,     0,     0,   246,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,     0,     0,     0,     0,
       0,     0,     0,   186,     0,     0,     0,     0,     0,     0,
       0,   187,     0,     0,     0,     0,     0,     0,     0,   348,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,     0,
       0,     0,     0,     0,     0,     0,   186,     0,     0,     0,
       0,     0,     0,     0,   187,     0,     0,     0,     0,     0,
       0,     0,   349,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,     0,     0,     0,     0,     0,     0,     0,   186,
       0,     0,     0,     0,     0,   249,     0,   187,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,     0,     0,     0,
       0,     0,     0,     0,   186,     0,   357,     0,     0,     0,
       0,     0,   187,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,     0,     0,     0,     0,     0,     0,     0,   186,
       0,     0,   370,     0,     0,     0,     0,   187,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,     0,     0,     0,
       0,     0,     0,     0,   186,     0,     0,     0,     0,     0,
     417,     0,   187,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,     0,     0,     0,     0,     0,     0,     0,   186,
       0,     0,   480,     0,     0,     0,     0,   187,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,     0,     0,     0,
       0,     0,     0,     0,   186,     0,     0,     0,     0,     0,
       0,     0,   187
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,    30,    31,   234,   308,   317,   138,
       6,    21,    27,    19,   241,   243,     6,     5,     9,   218,
       6,    45,    27,     5,     5,    93,    32,   321,    34,     5,
      80,    37,    38,    56,    40,    41,    42,    43,    44,    28,
      46,    47,    30,    91,    94,   450,   340,    76,    30,   454,
      46,    93,    40,   103,    30,   103,    46,    86,    40,    40,
      46,    49,   467,    80,    76,   194,    55,    49,    55,    93,
      75,    80,    84,    49,   103,    92,    80,    55,    93,    52,
      53,    54,   487,    80,   385,    94,     5,     6,     7,    55,
      94,    78,   497,   103,   103,   101,   102,    94,    94,    95,
      78,   103,    93,    76,    94,    95,    94,   103,   104,    95,
     106,    84,    78,   103,   104,   314,   106,   103,   104,   103,
     106,    40,    75,    76,    21,   131,   101,   102,   134,   356,
      75,   358,    80,    80,    80,   363,   445,    80,    91,    36,
     441,    80,    95,   149,    80,   151,    91,    80,    96,    96,
      96,    94,   112,   113,    98,    94,   384,   101,    94,    93,
      93,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     203,   187,    80,   103,   190,   191,   111,   414,    80,   195,
     103,   197,   103,   199,   200,   324,    94,    93,    80,   427,
      92,   103,   225,   332,   129,    80,   229,   103,    80,   134,
      92,    50,    51,    52,    53,    54,    80,   103,    80,    94,
      92,    80,    93,   103,    93,   354,    80,   233,    92,   252,
      92,     5,   103,    92,   159,   241,   242,    76,    92,    80,
       3,     4,   248,   249,   250,    84,    81,    80,    80,    95,
     103,    92,    80,    78,   103,   103,    81,   103,    93,    92,
      92,    24,    25,    26,    92,   103,   289,   103,    31,   292,
     293,    93,   401,   198,   103,     0,   201,   202,    41,    42,
      91,    44,   305,    50,    51,    52,    53,    54,    51,   214,
      55,   103,    76,   422,    61,    62,    63,    64,    65,    66,
      67,   226,    93,    93,    93,   103,    69,   103,   331,    76,
     103,   236,     5,    93,    93,   103,   339,    84,   103,   325,
     326,    94,    80,     5,    55,   103,    89,    90,    91,    91,
      93,   103,    95,   103,   103,     3,     4,    94,    94,   103,
     103,   104,   105,   106,   107,    55,    91,    91,   103,   103,
     356,   357,   358,   359,   103,   103,    24,    25,    26,   365,
     103,   367,   368,    31,   370,   103,    50,    51,    52,    53,
      54,   103,    91,    41,    42,   103,    44,    61,    62,    63,
      64,    65,    66,    51,   407,   103,   103,   103,    91,    96,
      84,   397,    76,    55,    93,   103,   402,    78,    93,    78,
      84,    69,   428,   409,    82,   103,    91,    78,   414,    78,
     416,   417,   435,    93,    55,   103,    91,    55,    91,    10,
      36,    89,    90,    91,    21,    93,   103,    95,    95,   103,
      91,     3,     4,   456,    91,   103,   104,   105,   106,   107,
      99,   447,    78,    80,   369,   103,    93,   103,   103,    93,
      93,    93,    24,    25,    26,   377,   296,    92,    92,    31,
      93,    93,   485,    93,    93,   373,   438,   473,    71,    41,
      42,   432,    44,   303,   480,   379,   499,   500,   501,   502,
     383,    -1,   488,   408,   235,   237,    -1,    -1,    -1,   512,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   520,    -1,   522,
      -1,    -1,    -1,   526,    -1,   528,    -1,   530,    -1,   532,
     533,    -1,   535,    -1,    -1,    -1,    -1,    89,    90,    91,
      -1,    93,   447,    95,    -1,    50,    51,    52,    53,    54,
      -1,   103,   104,   105,   106,   107,    -1,    -1,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   474,
     475,    76,   477,   478,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     495,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   506,    -1,    -1,   509,    -1,    -1,    -1,   513,    -1,
      -1,    -1,    -1,    -1,   519,    -1,   521,    -1,   523,   524,
      -1,    -1,   527,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    97,    -1,    -1,
     100,    -1,   102,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    97,    -1,    -1,   100,    -1,   102,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    -1,    93,    -1,    95,    -1,    97,     3,     4,
     100,    -1,   102,   103,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    26,    -1,    -1,    -1,    -1,    31,     3,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    24,    25,
      26,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    41,    42,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,    89,    90,    91,    -1,    93,    -1,
      95,    -1,    -1,    69,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,   107,    24,    25,    26,    -1,    -1,    -1,    -1,
      31,     3,     4,    89,    90,    91,    -1,    93,    -1,    95,
      41,    42,    -1,    44,    -1,    -1,    -1,   103,   104,   105,
     106,   107,    24,    25,    26,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    -1,    93,    -1,    95,    -1,    -1,    69,    -1,    -1,
      -1,    -1,   103,   104,   105,   106,   107,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    -1,    89,    90,    91,
      -1,    93,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    86,    87,    -1,    -1,    -1,    -1,
      -1,    93,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    92,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    92,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    84,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    84,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    84,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    84,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    84,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    40,
      41,    42,    43,    44,    47,    48,    49,    51,    69,    88,
      89,    90,    91,    93,    95,    97,   100,   102,   103,   104,
     105,   106,   107,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   120,   121,   122,   125,   126,   127,   133,
     138,   139,   140,   141,   145,   148,   150,   151,   152,   153,
     154,   155,   156,   157,   162,   165,   167,   168,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   180,   181,   182,
     184,    93,    93,   103,   103,   103,   171,   171,   103,   171,
     171,    93,    76,    86,   103,   128,   129,    93,   103,   103,
     103,   103,   103,   171,     5,     6,     7,    40,   103,    93,
     103,   103,   103,     5,    93,   175,   175,   171,    91,   103,
     142,   143,   171,   103,   119,   103,   171,   171,   103,    91,
     171,    91,   171,   171,   146,   147,   171,   171,   183,    93,
     171,   171,     0,   115,     5,    30,   140,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    76,    84,    75,    76,
      91,    95,   146,   146,    91,    55,    78,    55,    93,    28,
      55,    93,    93,   112,   128,   128,    76,    27,    93,   130,
      21,   103,   134,   135,    93,    45,    93,    93,    93,    93,
     103,   103,   103,     5,    93,   112,    93,   171,   103,   112,
     171,    27,   142,    55,    78,    80,    93,    93,    27,    75,
      75,    91,    55,    78,   171,   171,    92,    94,    80,    82,
      80,    96,   112,   103,     5,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   103,   171,   103,   103,   171,   179,
     171,    94,    94,   142,   171,    95,   103,   144,   171,   112,
     171,   171,   112,   112,    94,   103,   103,    21,    36,   131,
     136,   137,   103,    80,    94,   112,   103,   103,   163,   164,
     103,   166,    30,   141,   169,     6,    46,    95,   103,   104,
     106,   158,   159,   160,    91,    55,    55,   103,   103,   185,
      94,   112,    91,    94,   103,    92,   171,   144,   143,   112,
     158,   103,    93,   103,   103,   179,   171,   144,    92,    92,
     171,   171,   171,    94,    91,   103,    91,    78,    91,    80,
      92,    96,    92,    96,    84,    55,    94,    86,    87,    93,
      79,    94,    94,    93,   130,   103,    78,    80,    94,    80,
      94,   135,    94,    93,    78,    80,    94,   164,    80,    94,
      94,   141,   103,   160,   161,    94,   159,    82,   142,   171,
     171,    91,    78,    80,    94,    94,   142,    78,    93,    55,
      94,    94,   103,   132,    91,    92,    55,    82,    98,   101,
     123,   142,    91,   179,   171,   179,   171,    78,    81,   149,
     144,   171,    10,   171,   171,   112,   171,   136,    95,   131,
     137,   163,   144,   164,   103,    80,    96,    93,   171,   186,
      92,   142,   171,   103,    92,   115,   112,   171,    80,    94,
     179,   171,   171,    91,    91,    99,   124,    92,   142,    92,
      92,   144,   175,    81,    93,    93,   152,    93,    93,    94,
      79,    94,   132,    94,   160,   112,   149,    92,    78,   149,
      94,   103,    92,   103,   103,    93,   149,    92,   171,   112,
     112,   112,   112,   171,    96,    94,    93,   149,   171,    93,
      92,    92,   112,    93,   149,    94,    94,    94,    94,    93,
     112,    93,   112,    93,    93,    94,   112,    93,   112,    94,
     112,    94,   112,   112,    94,   112,    94,    94,    94,    94,
      94
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   108,   109,   110,   111,   112,   112,   113,   114,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   116,   117,   117,   118,
     118,   118,   119,   119,   120,   120,   121,   122,   122,   123,
     123,   124,   125,   125,   126,   126,   127,   127,   127,   127,
     127,   127,   128,   128,   129,   129,   129,   130,   131,   131,
     132,   132,   133,   133,   134,   134,   135,   135,   136,   136,
     137,   138,   139,   139,   140,   140,   140,   140,   141,   141,
     141,   141,   141,   141,   141,   142,   142,   142,   143,   143,
     143,   143,   144,   144,   144,   145,   145,   145,   146,   146,
     147,   147,   148,   149,   149,   149,   150,   150,   150,   150,
     150,   151,   151,   152,   152,   152,   153,   154,   154,   154,
     154,   154,   155,   156,   157,   158,   158,   159,   159,   160,
     160,   160,   160,   160,   160,   161,   161,   161,   162,   162,
     163,   163,   163,   163,   164,   165,   166,   166,   166,   167,
     168,   169,   169,   169,   170,   170,   171,   171,   171,   171,
     171,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     173,   173,   174,   174,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   176,   177,   177,   178,   178,   179,
     179,   179,   180,   181,   181,   182,   183,   183,   183,   184,
     185,   185,   185,   186
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     5,     1,     1,     2,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     6,     4,     2,     2,
       6,     4,     1,     3,     4,     2,     5,     5,     6,     7,
       7,     4,     2,     2,     2,     3,     2,     4,     3,     5,
       5,     7,     1,     3,     1,     2,     2,     3,     5,     3,
       1,     3,     2,     4,     1,     3,     1,     2,     1,     3,
       2,     5,     1,     2,     2,     5,     4,     7,     9,    10,
      10,    11,     8,    10,    11,     0,     1,     3,     1,     3,
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
#line 128 "src/parser/parser.y"
                                                                  {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2437 "parser.c"
    break;

  case 3: /* ternary_expr: expression TOKEN_OPTIONAL expression TOKEN_COLON expression  */
#line 133 "src/parser/parser.y"
                                                                {
        // condition ? true_expr : false_expr
        (yyval.node) = create_ternary_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2446 "parser.c"
    break;

  case 4: /* program: statement_list  */
#line 140 "src/parser/parser.y"
                   {
        program_root = create_program_node((yyvsp[0].node_list));
    }
#line 2454 "parser.c"
    break;

  case 5: /* statement_list: statement  */
#line 146 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2463 "parser.c"
    break;

  case 6: /* statement_list: statement_list statement  */
#line 150 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2472 "parser.c"
    break;

  case 7: /* unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 156 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_unsafe_node((yyvsp[-1].node_list));
    }
#line 2480 "parser.c"
    break;

  case 8: /* continue_statement: TOKEN_CONTINUE  */
#line 161 "src/parser/parser.y"
                   {
        (yyval.node) = create_continue_node();
    }
#line 2488 "parser.c"
    break;

  case 35: /* statement: expression  */
#line 194 "src/parser/parser.y"
                 {
        (yyval.node) = create_expr_statement((yyvsp[0].node));
    }
#line 2496 "parser.c"
    break;

  case 36: /* with_statement: TOKEN_WITH expression TOKEN_AS TOKEN_IDENTIFIER TOKEN_COLON statement  */
#line 199 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_with_node((yyvsp[-4].node), (yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2504 "parser.c"
    break;

  case 37: /* sysf_expr: TOKEN_SYSF TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 204 "src/parser/parser.y"
                                                    {
        (yyval.node) = create_sysf_node((yyvsp[-1].node));
    }
#line 2512 "parser.c"
    break;

  case 38: /* sysf_expr: TOKEN_SYSF expression  */
#line 207 "src/parser/parser.y"
                            {
        (yyval.node) = create_sysf_node((yyvsp[0].node));
    }
#line 2520 "parser.c"
    break;

  case 39: /* use_statement: TOKEN_USE use_path  */
#line 214 "src/parser/parser.y"
                       {
        (yyval.node) = create_use_node((yyvsp[0].string), NULL);
    }
#line 2528 "parser.c"
    break;

  case 40: /* use_statement: TOKEN_USE use_path TOKEN_DOUBLE_COLON TOKEN_LBRACE name_list TOKEN_RBRACE  */
#line 218 "src/parser/parser.y"
                                                                                {
        (yyval.node) = create_use_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2536 "parser.c"
    break;

  case 41: /* use_statement: TOKEN_USE use_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 222 "src/parser/parser.y"
                                                   {
        (yyval.node) = create_use_node((yyvsp[-2].string), NULL);
        // Stocker l'alias dans le nœud
        (yyval.node)->use_stmt.alias = strdup((yyvsp[0].string));
    }
#line 2546 "parser.c"
    break;

  case 42: /* use_path: TOKEN_IDENTIFIER  */
#line 230 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2554 "parser.c"
    break;

  case 43: /* use_path: use_path TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 233 "src/parser/parser.y"
                                                   {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 3);
        sprintf(path, "%s::%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2565 "parser.c"
    break;

  case 44: /* sh_expr: TOKEN_SH TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 242 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_sh_node((yyvsp[-1].node));
    }
#line 2573 "parser.c"
    break;

  case 45: /* sh_expr: TOKEN_SH expression  */
#line 245 "src/parser/parser.y"
                          {
        (yyval.node) = create_sh_node((yyvsp[0].node));
    }
#line 2581 "parser.c"
    break;

  case 46: /* nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 251 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_nnl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2589 "parser.c"
    break;

  case 47: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block  */
#line 257 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_try_node((yyvsp[-2].node_list), (yyvsp[0].node), NULL);
    }
#line 2597 "parser.c"
    break;

  case 48: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block  */
#line 260 "src/parser/parser.y"
                                                                                   {
        (yyval.node) = create_try_node((yyvsp[-3].node_list), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2605 "parser.c"
    break;

  case 49: /* catch_block: TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 266 "src/parser/parser.y"
                                                                                                    {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2613 "parser.c"
    break;

  case 50: /* catch_block: TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 269 "src/parser/parser.y"
                                                                                                       {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2621 "parser.c"
    break;

  case 51: /* finally_block: TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 275 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_finally_node((yyvsp[-1].node_list));
    }
#line 2629 "parser.c"
    break;

  case 52: /* throw_statement: TOKEN_THROW expression  */
#line 281 "src/parser/parser.y"
                           {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2637 "parser.c"
    break;

  case 53: /* throw_statement: TOKEN_RAISE expression  */
#line 284 "src/parser/parser.y"
                             {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2645 "parser.c"
    break;

  case 54: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER  */
#line 289 "src/parser/parser.y"
                               {
        (yyval.node) = create_jmp_node((yyvsp[0].string), NULL);
    }
#line 2653 "parser.c"
    break;

  case 55: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression  */
#line 292 "src/parser/parser.y"
                                            {
        (yyval.node) = create_jmp_node((yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2661 "parser.c"
    break;

  case 56: /* import_statement: TOKEN_IMPORT import_path  */
#line 301 "src/parser/parser.y"
                             {
        (yyval.node) = create_import_node((yyvsp[0].string), NULL, NULL);
    }
#line 2669 "parser.c"
    break;

  case 57: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER  */
#line 305 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_import_node((yyvsp[-2].string), (yyvsp[0].string), NULL);
    }
#line 2677 "parser.c"
    break;

  case 58: /* import_statement: TOKEN_IMPORT import_path import_constraints  */
#line 309 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_import_node((yyvsp[-1].string), NULL, (yyvsp[0].node));
    }
#line 2685 "parser.c"
    break;

  case 59: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER import_constraints  */
#line 313 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_import_node((yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2693 "parser.c"
    break;

  case 60: /* import_statement: TOKEN_IMPORT import_path TOKEN_LBRACE import_impl_list TOKEN_RBRACE  */
#line 317 "src/parser/parser.y"
                                                                          {
        ASTNode* node = create_import_node((yyvsp[-3].string), NULL, NULL);
        node->import.impl_list = (yyvsp[-1].node_list);
        (yyval.node) = node;
    }
#line 2703 "parser.c"
    break;

  case 61: /* import_statement: TOKEN_IMPORT import_path TOKEN_AS TOKEN_IDENTIFIER TOKEN_LBRACE import_impl_list TOKEN_RBRACE  */
#line 323 "src/parser/parser.y"
                                                                                                    {
        ASTNode* node = create_import_node((yyvsp[-5].string), (yyvsp[-3].string), NULL);
        node->import.impl_list = (yyvsp[-1].node_list);
        (yyval.node) = node;
    }
#line 2713 "parser.c"
    break;

  case 62: /* import_path_tail: TOKEN_IDENTIFIER  */
#line 332 "src/parser/parser.y"
                     {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 2721 "parser.c"
    break;

  case 63: /* import_path_tail: import_path_tail TOKEN_DOT TOKEN_IDENTIFIER  */
#line 335 "src/parser/parser.y"
                                                  {
        char* path = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 2);
        sprintf(path, "%s.%s", (yyvsp[-2].string), (yyvsp[0].string));
        free((yyvsp[-2].string));
        (yyval.string) = path;
    }
#line 2732 "parser.c"
    break;

  case 64: /* import_path: import_path_tail  */
#line 344 "src/parser/parser.y"
                     { 
        (yyval.string) = (yyvsp[0].string); 
    }
#line 2740 "parser.c"
    break;

  case 65: /* import_path: TOKEN_DOT import_path_tail  */
#line 347 "src/parser/parser.y"
                                 { // Import relatif: .fichier
        char* path = malloc(strlen((yyvsp[0].string)) + 2);
        sprintf(path, ".%s", (yyvsp[0].string));
        free((yyvsp[0].string));
        (yyval.string) = path;
    }
#line 2751 "parser.c"
    break;

  case 66: /* import_path: TOKEN_RANGE import_path_tail  */
#line 353 "src/parser/parser.y"
                                   { // Import relatif: ..fichier (utilise TOKEN_RANGE ".." du lexer)
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "..%s", (yyvsp[0].string));
        free((yyvsp[0].string));
        (yyval.string) = path;
    }
#line 2762 "parser.c"
    break;

  case 67: /* import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE  */
#line 362 "src/parser/parser.y"
                                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2770 "parser.c"
    break;

  case 68: /* import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET  */
#line 368 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_constraints_node("only", (yyvsp[-1].node_list));
    }
#line 2778 "parser.c"
    break;

  case 69: /* import_options: import_options TOKEN_COMMA import_options  */
#line 371 "src/parser/parser.y"
                                                {
        (yyval.node) = merge_constraints((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2786 "parser.c"
    break;

  case 70: /* name_list: TOKEN_IDENTIFIER  */
#line 377 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2795 "parser.c"
    break;

  case 71: /* name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 381 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2804 "parser.c"
    break;

  case 72: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
#line 388 "src/parser/parser.y"
                                  {
        (yyval.node) = create_export_node((yyvsp[0].string));
    }
#line 2812 "parser.c"
    break;

  case 73: /* export_statement: TOKEN_EXPORT TOKEN_LBRACE export_list TOKEN_RBRACE  */
#line 392 "src/parser/parser.y"
                                                         {
        ASTNode* node = create_export_node(NULL);
        node->export.export_list = (yyvsp[-1].node_list);
        (yyval.node) = node;
    }
#line 2822 "parser.c"
    break;

  case 74: /* export_list: export_item  */
#line 400 "src/parser/parser.y"
                {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2831 "parser.c"
    break;

  case 75: /* export_list: export_list TOKEN_COMMA export_item  */
#line 404 "src/parser/parser.y"
                                          {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2840 "parser.c"
    break;

  case 76: /* export_item: TOKEN_IDENTIFIER  */
#line 411 "src/parser/parser.y"
                     {
        ASTNode* node = create_identifier_node((yyvsp[0].string));
        node->is_impl = 0;
        (yyval.node) = node;
    }
#line 2850 "parser.c"
    break;

  case 77: /* export_item: TOKEN_IMPL TOKEN_IDENTIFIER  */
#line 417 "src/parser/parser.y"
                                  {
        ASTNode* node = create_identifier_node((yyvsp[0].string));
        node->is_impl = 1;
        (yyval.node) = node;
    }
#line 2860 "parser.c"
    break;

  case 78: /* import_impl_list: import_impl_item  */
#line 425 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2869 "parser.c"
    break;

  case 79: /* import_impl_list: import_impl_list TOKEN_COMMA import_impl_item  */
#line 429 "src/parser/parser.y"
                                                    {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2878 "parser.c"
    break;

  case 80: /* import_impl_item: TOKEN_IMPL TOKEN_IDENTIFIER  */
#line 437 "src/parser/parser.y"
                                {
        ASTNode* node = create_identifier_node((yyvsp[0].string));
        node->is_impl = 1;
        (yyval.node) = node;
    }
#line 2888 "parser.c"
    break;

  case 81: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 445 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_packet_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2896 "parser.c"
    break;

  case 82: /* decorator_list: decorator  */
#line 455 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2905 "parser.c"
    break;

  case 83: /* decorator_list: decorator_list decorator  */
#line 459 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2914 "parser.c"
    break;

  case 84: /* decorator: TOKEN_AT TOKEN_IDENTIFIER  */
#line 467 "src/parser/parser.y"
                              {
        (yyval.node) = create_decorator_node((yyvsp[0].string), NULL, NULL);
    }
#line 2922 "parser.c"
    break;

  case 85: /* decorator: TOKEN_AT TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 471 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_decorator_node((yyvsp[-3].string), NULL, (yyvsp[-1].node_list));
    }
#line 2930 "parser.c"
    break;

  case 86: /* decorator: TOKEN_AT TOKEN_IDENTIFIER TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 475 "src/parser/parser.y"
                                                                    {
        char* full = malloc(strlen((yyvsp[-2].string)) + strlen((yyvsp[0].string)) + 3);
        sprintf(full, "%s::%s", (yyvsp[-2].string), (yyvsp[0].string));
        (yyval.node) = create_decorator_node(full, NULL, NULL);
        free(full);
    }
#line 2941 "parser.c"
    break;

  case 87: /* decorator: TOKEN_AT TOKEN_IDENTIFIER TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 482 "src/parser/parser.y"
                                                                                                            {
        char* full = malloc(strlen((yyvsp[-5].string)) + strlen((yyvsp[-3].string)) + 3);
        sprintf(full, "%s::%s", (yyvsp[-5].string), (yyvsp[-3].string));
        (yyval.node) = create_decorator_node(full, NULL, (yyvsp[-1].node_list));
        free(full);
    }
#line 2952 "parser.c"
    break;

  case 88: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 491 "src/parser/parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2960 "parser.c"
    break;

  case 89: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 494 "src/parser/parser.y"
                                                                                                                                    {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2968 "parser.c"
    break;

  case 90: /* function_decl: TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 497 "src/parser/parser.y"
                                                                                                                                      {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        (yyval.node) = node;
    }
#line 2979 "parser.c"
    break;

  case 91: /* function_decl: TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 503 "src/parser/parser.y"
                                                                                                                                                {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        (yyval.node) = node;
    }
#line 2991 "parser.c"
    break;

  case 92: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression  */
#line 510 "src/parser/parser.y"
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node((yyvsp[0].node));
        add_to_node_list(body, return_stmt);
        (yyval.node) = create_function_node((yyvsp[-6].string), (yyvsp[-4].node_list), (yyvsp[-2].node), body);
    }
#line 3002 "parser.c"
    break;

  case 93: /* function_decl: decorator_list TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 517 "src/parser/parser.y"
                                                                                                                                         {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        (yyval.node)->function.decorators = (yyvsp[-9].node_list);
    }
#line 3011 "parser.c"
    break;

  case 94: /* function_decl: decorator_list TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 521 "src/parser/parser.y"
                                                                                                                                                   {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        (yyval.node)->function.decorators = (yyvsp[-10].node_list);
    }
#line 3020 "parser.c"
    break;

  case 95: /* param_list: %empty  */
#line 528 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3028 "parser.c"
    break;

  case 96: /* param_list: param  */
#line 531 "src/parser/parser.y"
            {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3037 "parser.c"
    break;

  case 97: /* param_list: param_list TOKEN_COMMA param  */
#line 535 "src/parser/parser.y"
                                   {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3046 "parser.c"
    break;

  case 98: /* param: TOKEN_IDENTIFIER  */
#line 545 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[0].string), NULL, NULL); }
#line 3052 "parser.c"
    break;

  case 99: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 547 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[-2].string), (yyvsp[0].node), NULL); }
#line 3058 "parser.c"
    break;

  case 100: /* param: TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 549 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[-2].string), NULL, (yyvsp[0].node)); }
#line 3064 "parser.c"
    break;

  case 101: /* param: TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 551 "src/parser/parser.y"
    { (yyval.node) = create_param_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3070 "parser.c"
    break;

  case 102: /* type: TOKEN_IDENTIFIER  */
#line 556 "src/parser/parser.y"
                     {
        (yyval.node) = create_type_node((yyvsp[0].string));
    }
#line 3078 "parser.c"
    break;

  case 103: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
#line 559 "src/parser/parser.y"
                                      {
        (yyval.node) = create_optional_type_node((yyvsp[-1].string));
    }
#line 3086 "parser.c"
    break;

  case 104: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 562 "src/parser/parser.y"
                                         {
        (yyval.node) = create_array_type_node((yyvsp[0].node));
    }
#line 3094 "parser.c"
    break;

  case 105: /* dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 570 "src/parser/parser.y"
                                                      { (yyval.node) = create_dict_node((yyvsp[-1].node_list)); }
#line 3100 "parser.c"
    break;

  case 106: /* dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 571 "src/parser/parser.y"
                                                       { (yyval.node) = create_dict_node((yyvsp[-1].node_list)); }
#line 3106 "parser.c"
    break;

  case 107: /* dict_expr: TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 572 "src/parser/parser.y"
                                             { (yyval.node) = create_dict_node((yyvsp[-1].node_list)); }
#line 3112 "parser.c"
    break;

  case 108: /* dict_entries: %empty  */
#line 576 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3120 "parser.c"
    break;

  case 109: /* dict_entries: dict_entry_list  */
#line 579 "src/parser/parser.y"
                      {
        (yyval.node_list) = (yyvsp[0].node_list);
    }
#line 3128 "parser.c"
    break;

  case 110: /* dict_entry_list: expression TOKEN_FAT_ARROW expression  */
#line 585 "src/parser/parser.y"
                                          {
        (yyval.node_list) = create_node_list();
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyval.node_list), pair);
    }
#line 3138 "parser.c"
    break;

  case 111: /* dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression  */
#line 590 "src/parser/parser.y"
                                                                        {
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyvsp[-4].node_list), pair);
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 3148 "parser.c"
    break;

  case 112: /* bracket_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 600 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 3156 "parser.c"
    break;

  case 113: /* return_type: %empty  */
#line 616 "src/parser/parser.y"
                {
        (yyval.node) = NULL;
    }
#line 3164 "parser.c"
    break;

  case 114: /* return_type: TOKEN_COLON type  */
#line 619 "src/parser/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3172 "parser.c"
    break;

  case 115: /* return_type: TOKEN_ARROW primary_expr  */
#line 622 "src/parser/parser.y"
                               {
        // Pour les retours directs: -> expr
        (yyval.node) = create_return_direct_node((yyvsp[0].node));
    }
#line 3181 "parser.c"
    break;

  case 116: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 629 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 3189 "parser.c"
    break;

  case 117: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 632 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_let_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3197 "parser.c"
    break;

  case 118: /* let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 635 "src/parser/parser.y"
                                                                   {
        ASTNode* node = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 3207 "parser.c"
    break;

  case 119: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 641 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_muts_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 3215 "parser.c"
    break;

  case 120: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 644 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_muts_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3223 "parser.c"
    break;

  case 121: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 649 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 3231 "parser.c"
    break;

  case 122: /* const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 652 "src/parser/parser.y"
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 3242 "parser.c"
    break;

  case 123: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 661 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-1].node_list), NULL);
    }
#line 3250 "parser.c"
    break;

  case 124: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 664 "src/parser/parser.y"
                                                                                                                       {
        (yyval.node) = create_if_node((yyvsp[-7].node), (yyvsp[-5].node_list), (yyvsp[-1].node_list));
    }
#line 3258 "parser.c"
    break;

  case 125: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE if_statement  */
#line 667 "src/parser/parser.y"
                                                                                           {
        // else if -> le else contient un autre if
        ASTNodeList* else_branch = create_node_list();
        add_to_node_list(else_branch, (yyvsp[0].node));
        (yyval.node) = create_if_node((yyvsp[-5].node), (yyvsp[-3].node_list), else_branch);
    }
#line 3269 "parser.c"
    break;

  case 126: /* break_statement: TOKEN_BREAK  */
#line 675 "src/parser/parser.y"
                {
        (yyval.node) = create_break_node();
    }
#line 3277 "parser.c"
    break;

  case 127: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 680 "src/parser/parser.y"
                                                                                                                                                      {
        ASTNode* init = create_let_node((yyvsp[-9].string), NULL, (yyvsp[-7].node));
        ASTNode* cond = (yyvsp[-5].node);
        ASTNode* inc = create_expr_statement((yyvsp[-3].node));
        (yyval.node) = create_for_node(init, cond, inc, (yyvsp[-1].node_list));
    }
#line 3288 "parser.c"
    break;

  case 128: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 686 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3296 "parser.c"
    break;

  case 129: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 689 "src/parser/parser.y"
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
#line 3314 "parser.c"
    break;

  case 130: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 702 "src/parser/parser.y"
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
#line 3334 "parser.c"
    break;

  case 131: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE_INC expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 717 "src/parser/parser.y"
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
#line 3350 "parser.c"
    break;

  case 132: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 732 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3358 "parser.c"
    break;

  case 133: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 738 "src/parser/parser.y"
                                                        {
        (yyval.node) = create_loop_node((yyvsp[-1].node_list));
    }
#line 3366 "parser.c"
    break;

  case 134: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 745 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3374 "parser.c"
    break;

  case 135: /* match_cases: match_case  */
#line 751 "src/parser/parser.y"
               {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3383 "parser.c"
    break;

  case 136: /* match_cases: match_cases match_case  */
#line 755 "src/parser/parser.y"
                             {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3392 "parser.c"
    break;

  case 137: /* match_case: pattern TOKEN_FAT_ARROW expression  */
#line 762 "src/parser/parser.y"
                                       {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3400 "parser.c"
    break;

  case 138: /* match_case: pattern TOKEN_FAT_ARROW block  */
#line 765 "src/parser/parser.y"
                                    {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (ASTNode*)(yyvsp[0].node));
    }
#line 3408 "parser.c"
    break;

  case 139: /* pattern: TOKEN_NUMBER  */
#line 771 "src/parser/parser.y"
                 { (yyval.node) = create_pattern_number((yyvsp[0].number)); }
#line 3414 "parser.c"
    break;

  case 140: /* pattern: TOKEN_STRING  */
#line 772 "src/parser/parser.y"
                   { (yyval.node) = create_pattern_string((yyvsp[0].string)); }
#line 3420 "parser.c"
    break;

  case 141: /* pattern: TOKEN_IDENTIFIER  */
#line 773 "src/parser/parser.y"
                       { (yyval.node) = create_pattern_ident((yyvsp[0].string)); }
#line 3426 "parser.c"
    break;

  case 142: /* pattern: TOKEN_UNDERSCORE  */
#line 774 "src/parser/parser.y"
                       { (yyval.node) = create_pattern_wildcard(); }
#line 3432 "parser.c"
    break;

  case 143: /* pattern: TOKEN_LBRACKET array_patterns TOKEN_RBRACKET  */
#line 775 "src/parser/parser.y"
                                                   { (yyval.node) = create_pattern_array((yyvsp[-1].node_list)); }
#line 3438 "parser.c"
    break;

  case 144: /* pattern: TOKEN_LET TOKEN_IDENTIFIER  */
#line 776 "src/parser/parser.y"
                                 { (yyval.node) = create_pattern_binding((yyvsp[0].string)); }
#line 3444 "parser.c"
    break;

  case 145: /* array_patterns: %empty  */
#line 780 "src/parser/parser.y"
                { (yyval.node_list) = NULL; }
#line 3450 "parser.c"
    break;

  case 146: /* array_patterns: pattern  */
#line 781 "src/parser/parser.y"
              { (yyval.node_list) = create_node_list(); add_to_node_list((yyval.node_list), (yyvsp[0].node)); }
#line 3456 "parser.c"
    break;

  case 147: /* array_patterns: array_patterns TOKEN_COMMA pattern  */
#line 782 "src/parser/parser.y"
                                         { add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node)); (yyval.node_list) = (yyvsp[-2].node_list); }
#line 3462 "parser.c"
    break;

  case 148: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 787 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_struct_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3470 "parser.c"
    break;

  case 149: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 790 "src/parser/parser.y"
                                                                                                           {
        (yyval.node) = create_struct_extend_node((yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3478 "parser.c"
    break;

  case 150: /* struct_fields: %empty  */
#line 796 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3486 "parser.c"
    break;

  case 151: /* struct_fields: struct_field  */
#line 799 "src/parser/parser.y"
                   {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3495 "parser.c"
    break;

  case 152: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
#line 803 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3504 "parser.c"
    break;

  case 153: /* struct_fields: struct_fields struct_field  */
#line 807 "src/parser/parser.y"
                                 {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3513 "parser.c"
    break;

  case 154: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 814 "src/parser/parser.y"
                                      {
        (yyval.node) = create_field_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 3521 "parser.c"
    break;

  case 155: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
#line 820 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_enum_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3529 "parser.c"
    break;

  case 156: /* enum_variants: %empty  */
#line 826 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3537 "parser.c"
    break;

  case 157: /* enum_variants: TOKEN_IDENTIFIER  */
#line 829 "src/parser/parser.y"
                       {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 3546 "parser.c"
    break;

  case 158: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 833 "src/parser/parser.y"
                                                 {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3555 "parser.c"
    break;

  case 159: /* golem_decl: TOKEN_GOLEM TOKEN_IDENTIFIER  */
#line 840 "src/parser/parser.y"
                                 {
        (yyval.node) = create_module_node((yyvsp[0].string));
    }
#line 3563 "parser.c"
    break;

  case 160: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
#line 846 "src/parser/parser.y"
                                                                             {
        (yyval.node) = create_impl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3571 "parser.c"
    break;

  case 161: /* function_decl_list: %empty  */
#line 852 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3579 "parser.c"
    break;

  case 162: /* function_decl_list: function_decl  */
#line 855 "src/parser/parser.y"
                    {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3588 "parser.c"
    break;

  case 163: /* function_decl_list: function_decl_list function_decl  */
#line 859 "src/parser/parser.y"
                                       {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 3597 "parser.c"
    break;

  case 164: /* return_statement: TOKEN_RETURN expression  */
#line 866 "src/parser/parser.y"
                            {
        (yyval.node) = create_return_node((yyvsp[0].node));
    }
#line 3605 "parser.c"
    break;

  case 165: /* return_statement: TOKEN_RETURN  */
#line 869 "src/parser/parser.y"
                   {
        (yyval.node) = create_return_node(NULL);
    }
#line 3613 "parser.c"
    break;

  case 170: /* expression: expression TOKEN_DOT TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 879 "src/parser/parser.y"
                                                                                    {
        // 'expression' est l'objet ($1), 'TOKEN_IDENTIFIER' est la méthode ($3)
        // 'argument_list' est la liste des arguments ($5)
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3623 "parser.c"
    break;

  case 171: /* binary_expr: expression TOKEN_PLUS expression  */
#line 887 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_ADD, (yyvsp[0].node));
    }
#line 3631 "parser.c"
    break;

  case 172: /* binary_expr: expression TOKEN_MINUS expression  */
#line 890 "src/parser/parser.y"
                                        {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_SUB, (yyvsp[0].node));
    }
#line 3639 "parser.c"
    break;

  case 173: /* binary_expr: expression TOKEN_MULTIPLY expression  */
#line 893 "src/parser/parser.y"
                                           {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
    }
#line 3647 "parser.c"
    break;

  case 174: /* binary_expr: expression TOKEN_DIVIDE expression  */
#line 896 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
    }
#line 3655 "parser.c"
    break;

  case 175: /* binary_expr: expression TOKEN_MODULO expression  */
#line 899 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
    }
#line 3663 "parser.c"
    break;

  case 176: /* binary_expr: expression TOKEN_EQ expression  */
#line 902 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_EQ, (yyvsp[0].node));
    }
#line 3671 "parser.c"
    break;

  case 177: /* binary_expr: expression TOKEN_NEQ expression  */
#line 905 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_NEQ, (yyvsp[0].node));
    }
#line 3679 "parser.c"
    break;

  case 178: /* binary_expr: expression TOKEN_LT expression  */
#line 908 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
    }
#line 3687 "parser.c"
    break;

  case 179: /* binary_expr: expression TOKEN_LTE expression  */
#line 911 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LTE, (yyvsp[0].node));
    }
#line 3695 "parser.c"
    break;

  case 180: /* binary_expr: expression TOKEN_GT expression  */
#line 914 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
    }
#line 3703 "parser.c"
    break;

  case 181: /* binary_expr: expression TOKEN_GTE expression  */
#line 917 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GTE, (yyvsp[0].node));
    }
#line 3711 "parser.c"
    break;

  case 182: /* binary_expr: expression TOKEN_AND expression  */
#line 920 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_AND, (yyvsp[0].node));
    }
#line 3719 "parser.c"
    break;

  case 183: /* binary_expr: expression TOKEN_OR expression  */
#line 923 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_OR, (yyvsp[0].node));
    }
#line 3727 "parser.c"
    break;

  case 184: /* binary_expr: expression TOKEN_ASSIGN expression  */
#line 926 "src/parser/parser.y"
                                         {
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 3735 "parser.c"
    break;

  case 185: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
#line 929 "src/parser/parser.y"
                                              {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_ADD_ASSIGN, (yyvsp[0].node));
    }
#line 3743 "parser.c"
    break;

  case 186: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
#line 932 "src/parser/parser.y"
                                               {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_SUB_ASSIGN, (yyvsp[0].node));
    }
#line 3751 "parser.c"
    break;

  case 187: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
#line 935 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MUL_ASSIGN, (yyvsp[0].node));
    }
#line 3759 "parser.c"
    break;

  case 188: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
#line 938 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_DIV_ASSIGN, (yyvsp[0].node));
    }
#line 3767 "parser.c"
    break;

  case 189: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
#line 941 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MOD_ASSIGN, (yyvsp[0].node));
    }
#line 3775 "parser.c"
    break;

  case 190: /* unary_expr: TOKEN_NOT expression  */
#line 947 "src/parser/parser.y"
                         {
        (yyval.node) = create_unary_op(OP_NOT, (yyvsp[0].node));
    }
#line 3783 "parser.c"
    break;

  case 191: /* unary_expr: TOKEN_MINUS expression  */
#line 950 "src/parser/parser.y"
                             {
        (yyval.node) = create_unary_op(OP_NEG, (yyvsp[0].node));
    }
#line 3791 "parser.c"
    break;

  case 192: /* lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 957 "src/parser/parser.y"
                                                                     {
        (yyval.node) = create_lambda_node((yyvsp[-3].node_list), (yyvsp[-1].node_list));
    }
#line 3799 "parser.c"
    break;

  case 193: /* lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 960 "src/parser/parser.y"
                                                                                                 {
        (yyval.node) = create_lambda_node((yyvsp[-4].node_list), (yyvsp[-1].node_list));
    }
#line 3807 "parser.c"
    break;

  case 194: /* primary_expr: TOKEN_NUMBER  */
#line 969 "src/parser/parser.y"
                 {
        (yyval.node) = create_number_node((yyvsp[0].number));
    }
#line 3815 "parser.c"
    break;

  case 195: /* primary_expr: TOKEN_FLOAT  */
#line 972 "src/parser/parser.y"
                  {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 3823 "parser.c"
    break;

  case 196: /* primary_expr: TOKEN_STRING  */
#line 975 "src/parser/parser.y"
                   {
        (yyval.node) = create_string_node((yyvsp[0].string));
    }
#line 3831 "parser.c"
    break;

  case 197: /* primary_expr: TOKEN_TRUE  */
#line 978 "src/parser/parser.y"
                 {
        (yyval.node) = create_bool_node(1);
    }
#line 3839 "parser.c"
    break;

  case 198: /* primary_expr: TOKEN_FALSE  */
#line 981 "src/parser/parser.y"
                  {
        (yyval.node) = create_bool_node(0);
    }
#line 3847 "parser.c"
    break;

  case 199: /* primary_expr: TOKEN_NIL  */
#line 984 "src/parser/parser.y"
                {
        (yyval.node) = create_nil_node();
    }
#line 3855 "parser.c"
    break;

  case 200: /* primary_expr: TOKEN_IDENTIFIER  */
#line 987 "src/parser/parser.y"
                       {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 3863 "parser.c"
    break;

  case 201: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 990 "src/parser/parser.y"
                                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3871 "parser.c"
    break;

  case 214: /* f_string: TOKEN_F_STRING  */
#line 1008 "src/parser/parser.y"
                   {
        (yyval.node) = parse_f_string((yyvsp[0].string));
    }
#line 3879 "parser.c"
    break;

  case 215: /* member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER  */
#line 1014 "src/parser/parser.y"
                                            {
        (yyval.node) = create_member_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3887 "parser.c"
    break;

  case 216: /* member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 1017 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_static_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3895 "parser.c"
    break;

  case 217: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 1023 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_call_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3903 "parser.c"
    break;

  case 218: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 1026 "src/parser/parser.y"
                                                                                               {
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3911 "parser.c"
    break;

  case 219: /* argument_list: %empty  */
#line 1032 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3919 "parser.c"
    break;

  case 220: /* argument_list: expression  */
#line 1035 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_arg_list();
        add_arg((yyval.node_list), (yyvsp[0].node));
    }
#line 3928 "parser.c"
    break;

  case 221: /* argument_list: argument_list TOKEN_COMMA expression  */
#line 1039 "src/parser/parser.y"
                                           {
        add_arg((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3937 "parser.c"
    break;

  case 222: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
#line 1046 "src/parser/parser.y"
                                              {
        (yyval.node) = create_array_node((yyvsp[-1].node_list));
    }
#line 3945 "parser.c"
    break;

  case 223: /* await_expr: TOKEN_AWAIT primary_expr  */
#line 1061 "src/parser/parser.y"
                             {
        (yyval.node) = create_await_node((yyvsp[0].node));
    }
#line 3953 "parser.c"
    break;

  case 224: /* await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 1064 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_await_block_node((yyvsp[-1].node_list));
    }
#line 3961 "parser.c"
    break;

  case 225: /* spawn_expr: TOKEN_SPAWN primary_expr  */
#line 1071 "src/parser/parser.y"
                             {
        (yyval.node) = create_spawn_node((yyvsp[0].node));
    }
#line 3969 "parser.c"
    break;

  case 226: /* array_items: %empty  */
#line 1083 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3977 "parser.c"
    break;

  case 227: /* array_items: expression  */
#line 1086 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3986 "parser.c"
    break;

  case 228: /* array_items: array_items TOKEN_COMMA expression  */
#line 1090 "src/parser/parser.y"
                                         {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3995 "parser.c"
    break;

  case 229: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
#line 1097 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_struct_init_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 4003 "parser.c"
    break;

  case 230: /* struct_init_fields: %empty  */
#line 1103 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 4011 "parser.c"
    break;

  case 231: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 1106 "src/parser/parser.y"
                                              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
    }
#line 4020 "parser.c"
    break;

  case 232: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 1110 "src/parser/parser.y"
                                                                             {
        add_to_node_list((yyvsp[-4].node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 4029 "parser.c"
    break;

  case 233: /* block: TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 1117 "src/parser/parser.y"
                                             {
        (yyval.node) = (ASTNode*)(yyvsp[-1].node_list);
    }
#line 4037 "parser.c"
    break;


#line 4041 "parser.c"

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

#line 1122 "src/parser/parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

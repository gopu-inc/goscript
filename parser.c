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
  YYSYMBOL_TOKEN_PLUS = 46,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 47,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MULTIPLY = 48,            /* TOKEN_MULTIPLY  */
  YYSYMBOL_TOKEN_DIVIDE = 49,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 50,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_ASSIGN = 51,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 52,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 53,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 54,     /* TOKEN_MULTIPLY_ASSIGN  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 55,       /* TOKEN_DIVIDE_ASSIGN  */
  YYSYMBOL_TOKEN_MODULO_ASSIGN = 56,       /* TOKEN_MODULO_ASSIGN  */
  YYSYMBOL_TOKEN_EQ = 57,                  /* TOKEN_EQ  */
  YYSYMBOL_TOKEN_NEQ = 58,                 /* TOKEN_NEQ  */
  YYSYMBOL_TOKEN_LT = 59,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LTE = 60,                 /* TOKEN_LTE  */
  YYSYMBOL_TOKEN_GT = 61,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GTE = 62,                 /* TOKEN_GTE  */
  YYSYMBOL_TOKEN_AND = 63,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 64,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_NOT = 65,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_AMP = 66,                 /* TOKEN_AMP  */
  YYSYMBOL_TOKEN_PIPE = 67,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_XOR = 68,                 /* TOKEN_XOR  */
  YYSYMBOL_TOKEN_LSHIFT = 69,              /* TOKEN_LSHIFT  */
  YYSYMBOL_TOKEN_RSHIFT = 70,              /* TOKEN_RSHIFT  */
  YYSYMBOL_TOKEN_DOUBLE_COLON = 71,        /* TOKEN_DOUBLE_COLON  */
  YYSYMBOL_TOKEN_DOT = 72,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_SECURITY = 73,            /* TOKEN_SECURITY  */
  YYSYMBOL_TOKEN_COLON = 74,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_SEMICOLON = 75,           /* TOKEN_SEMICOLON  */
  YYSYMBOL_TOKEN_COMMA = 76,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_ARROW = 77,               /* TOKEN_ARROW  */
  YYSYMBOL_TOKEN_FAT_ARROW = 78,           /* TOKEN_FAT_ARROW  */
  YYSYMBOL_TOKEN_PIPE_FORWARD = 79,        /* TOKEN_PIPE_FORWARD  */
  YYSYMBOL_TOKEN_OPTIONAL = 80,            /* TOKEN_OPTIONAL  */
  YYSYMBOL_TOKEN_COALESCE = 81,            /* TOKEN_COALESCE  */
  YYSYMBOL_TOKEN_RANGE = 82,               /* TOKEN_RANGE  */
  YYSYMBOL_TOKEN_RANGE_INC = 83,           /* TOKEN_RANGE_INC  */
  YYSYMBOL_TOKEN_MUTS = 84,                /* TOKEN_MUTS  */
  YYSYMBOL_TOKEN_LPAREN = 85,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 86,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_LBRACE = 87,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 88,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_LBRACKET = 89,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 90,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_TRY = 91,                 /* TOKEN_TRY  */
  YYSYMBOL_TOKEN_CATCH = 92,               /* TOKEN_CATCH  */
  YYSYMBOL_TOKEN_FINALLY = 93,             /* TOKEN_FINALLY  */
  YYSYMBOL_TOKEN_THROW = 94,               /* TOKEN_THROW  */
  YYSYMBOL_TOKEN_EXCEPT = 95,              /* TOKEN_EXCEPT  */
  YYSYMBOL_TOKEN_RAISE = 96,               /* TOKEN_RAISE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 97,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_NUMBER = 98,              /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_FLOAT = 99,               /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_STRING = 100,             /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_F_STRING = 101,           /* TOKEN_F_STRING  */
  YYSYMBOL_YYACCEPT = 102,                 /* $accept  */
  YYSYMBOL_program = 103,                  /* program  */
  YYSYMBOL_statement_list = 104,           /* statement_list  */
  YYSYMBOL_unsafe_stmt = 105,              /* unsafe_stmt  */
  YYSYMBOL_continue_statement = 106,       /* continue_statement  */
  YYSYMBOL_statement = 107,                /* statement  */
  YYSYMBOL_nnl_statement = 108,            /* nnl_statement  */
  YYSYMBOL_try_statement = 109,            /* try_statement  */
  YYSYMBOL_catch_block = 110,              /* catch_block  */
  YYSYMBOL_finally_block = 111,            /* finally_block  */
  YYSYMBOL_throw_statement = 112,          /* throw_statement  */
  YYSYMBOL_jmp_statement = 113,            /* jmp_statement  */
  YYSYMBOL_import_statement = 114,         /* import_statement  */
  YYSYMBOL_import_constraints = 115,       /* import_constraints  */
  YYSYMBOL_import_options = 116,           /* import_options  */
  YYSYMBOL_name_list = 117,                /* name_list  */
  YYSYMBOL_export_statement = 118,         /* export_statement  */
  YYSYMBOL_packet_decl = 119,              /* packet_decl  */
  YYSYMBOL_function_decl = 120,            /* function_decl  */
  YYSYMBOL_param_list = 121,               /* param_list  */
  YYSYMBOL_param = 122,                    /* param  */
  YYSYMBOL_type = 123,                     /* type  */
  YYSYMBOL_dict_expr = 124,                /* dict_expr  */
  YYSYMBOL_dict_entries = 125,             /* dict_entries  */
  YYSYMBOL_dict_entry_list = 126,          /* dict_entry_list  */
  YYSYMBOL_dict_access = 127,              /* dict_access  */
  YYSYMBOL_return_type = 128,              /* return_type  */
  YYSYMBOL_let_decl = 129,                 /* let_decl  */
  YYSYMBOL_const_decl = 130,               /* const_decl  */
  YYSYMBOL_if_statement = 131,             /* if_statement  */
  YYSYMBOL_break_statement = 132,          /* break_statement  */
  YYSYMBOL_for_statement = 133,            /* for_statement  */
  YYSYMBOL_while_statement = 134,          /* while_statement  */
  YYSYMBOL_loop_statement = 135,           /* loop_statement  */
  YYSYMBOL_match_statement = 136,          /* match_statement  */
  YYSYMBOL_match_cases = 137,              /* match_cases  */
  YYSYMBOL_match_case = 138,               /* match_case  */
  YYSYMBOL_pattern = 139,                  /* pattern  */
  YYSYMBOL_struct_decl = 140,              /* struct_decl  */
  YYSYMBOL_struct_fields = 141,            /* struct_fields  */
  YYSYMBOL_struct_field = 142,             /* struct_field  */
  YYSYMBOL_enum_decl = 143,                /* enum_decl  */
  YYSYMBOL_enum_variants = 144,            /* enum_variants  */
  YYSYMBOL_module_decl = 145,              /* module_decl  */
  YYSYMBOL_impl_decl = 146,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 147,       /* function_decl_list  */
  YYSYMBOL_return_statement = 148,         /* return_statement  */
  YYSYMBOL_expression = 149,               /* expression  */
  YYSYMBOL_binary_expr = 150,              /* binary_expr  */
  YYSYMBOL_unary_expr = 151,               /* unary_expr  */
  YYSYMBOL_lambda_expr = 152,              /* lambda_expr  */
  YYSYMBOL_array_access = 153,             /* array_access  */
  YYSYMBOL_primary_expr = 154,             /* primary_expr  */
  YYSYMBOL_f_string = 155,                 /* f_string  */
  YYSYMBOL_member_access = 156,            /* member_access  */
  YYSYMBOL_call_expr = 157,                /* call_expr  */
  YYSYMBOL_argument_list = 158,            /* argument_list  */
  YYSYMBOL_array_expr = 159,               /* array_expr  */
  YYSYMBOL_await_expr = 160,               /* await_expr  */
  YYSYMBOL_spawn_expr = 161,               /* spawn_expr  */
  YYSYMBOL_array_items = 162,              /* array_items  */
  YYSYMBOL_struct_expr = 163,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 164        /* struct_init_fields  */
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
#define YYFINAL  132
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2939

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  183
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  414

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   356


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
      95,    96,    97,    98,    99,   100,   101
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   109,   109,   115,   119,   125,   130,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   165,   171,   174,   180,   183,   189,   195,   198,   203,
     206,   212,   215,   221,   227,   231,   237,   240,   246,   252,
     255,   261,   265,   272,   278,   284,   287,   290,   296,   303,
     312,   315,   319,   326,   329,   335,   338,   341,   349,   352,
     358,   361,   367,   372,   381,   400,   403,   406,   413,   416,
     419,   425,   428,   433,   436,   445,   448,   453,   458,   464,
     467,   483,   489,   496,   502,   506,   513,   519,   522,   525,
     528,   534,   537,   543,   546,   550,   554,   561,   567,   573,
     576,   580,   587,   594,   600,   603,   607,   614,   617,   623,
     624,   625,   629,   632,   635,   638,   641,   644,   647,   650,
     653,   656,   659,   662,   665,   668,   671,   674,   677,   680,
     683,   689,   692,   699,   702,   709,   715,   718,   721,   724,
     727,   730,   733,   736,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,   753,   759,   762,   768,   771,
     777,   780,   784,   791,   806,   809,   816,   828,   831,   835,
     842,   848,   851,   855
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
  "TOKEN_UNDERSCORE", "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_MULTIPLY",
  "TOKEN_DIVIDE", "TOKEN_MODULO", "TOKEN_ASSIGN", "TOKEN_PLUS_ASSIGN",
  "TOKEN_MINUS_ASSIGN", "TOKEN_MULTIPLY_ASSIGN", "TOKEN_DIVIDE_ASSIGN",
  "TOKEN_MODULO_ASSIGN", "TOKEN_EQ", "TOKEN_NEQ", "TOKEN_LT", "TOKEN_LTE",
  "TOKEN_GT", "TOKEN_GTE", "TOKEN_AND", "TOKEN_OR", "TOKEN_NOT",
  "TOKEN_AMP", "TOKEN_PIPE", "TOKEN_XOR", "TOKEN_LSHIFT", "TOKEN_RSHIFT",
  "TOKEN_DOUBLE_COLON", "TOKEN_DOT", "TOKEN_SECURITY", "TOKEN_COLON",
  "TOKEN_SEMICOLON", "TOKEN_COMMA", "TOKEN_ARROW", "TOKEN_FAT_ARROW",
  "TOKEN_PIPE_FORWARD", "TOKEN_OPTIONAL", "TOKEN_COALESCE", "TOKEN_RANGE",
  "TOKEN_RANGE_INC", "TOKEN_MUTS", "TOKEN_LPAREN", "TOKEN_RPAREN",
  "TOKEN_LBRACE", "TOKEN_RBRACE", "TOKEN_LBRACKET", "TOKEN_RBRACKET",
  "TOKEN_TRY", "TOKEN_CATCH", "TOKEN_FINALLY", "TOKEN_THROW",
  "TOKEN_EXCEPT", "TOKEN_RAISE", "TOKEN_IDENTIFIER", "TOKEN_NUMBER",
  "TOKEN_FLOAT", "TOKEN_STRING", "TOKEN_F_STRING", "$accept", "program",
  "statement_list", "unsafe_stmt", "continue_statement", "statement",
  "nnl_statement", "try_statement", "catch_block", "finally_block",
  "throw_statement", "jmp_statement", "import_statement",
  "import_constraints", "import_options", "name_list", "export_statement",
  "packet_decl", "function_decl", "param_list", "param", "type",
  "dict_expr", "dict_entries", "dict_entry_list", "dict_access",
  "return_type", "let_decl", "const_decl", "if_statement",
  "break_statement", "for_statement", "while_statement", "loop_statement",
  "match_statement", "match_cases", "match_case", "pattern", "struct_decl",
  "struct_fields", "struct_field", "enum_decl", "enum_variants",
  "module_decl", "impl_decl", "function_decl_list", "return_statement",
  "expression", "binary_expr", "unary_expr", "lambda_expr", "array_access",
  "primary_expr", "f_string", "member_access", "call_expr",
  "argument_list", "array_expr", "await_expr", "spawn_expr", "array_items",
  "struct_expr", "struct_init_fields", YY_NULLPTR
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
     355,   356
};
#endif

#define YYPACT_NINF (-288)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2474,   -67,   -66,   -61,   -48,   -44,    13,    13,   183,    13,
       3,  -288,  -288,   -46,     2,     8,    23,    28,    78,    13,
    -288,  -288,  -288,    36,    80,    81,    84,    85,    88,   171,
    2499,  2552,    -1,    13,    13,    91,    13,    13,   102,    13,
      13,  -288,  -288,  -288,  -288,  -288,   190,  2474,  -288,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,  2875,  -288,  -288,  -288,  -288,    82,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,    13,    13,   107,
      14,   142,  2875,   290,    38,  2555,  2608,  2474,   -40,   -15,
    -288,   108,   -35,   116,   117,  2627,   109,   113,   114,   207,
     126,  2474,   129,    13,  -288,   120,  2474,    82,    82,   123,
     147,   -47,  -288,   422,   146,    17,  2730,  2875,   -26,  2474,
    2875,  2875,  -288,  -288,    13,    13,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,    13,
      13,    13,    13,   131,   132,    13,    13,   143,   157,  2749,
     155,   123,    13,    -3,    13,  2474,    13,    13,  2474,  2474,
     395,   162,  -288,   148,   -53,   210,  -288,  2474,   150,   152,
     153,    18,   -23,   167,   202,   203,   158,   161,   494,  2474,
    2875,   174,   593,    -7,    -3,   123,  2474,    13,    -3,  -288,
      13,  -288,   692,   422,   422,   146,   146,   146,   186,   186,
     186,   186,   186,   186,   694,   694,   496,   496,   496,   496,
     595,   613,   175,  -288,  2875,    40,   245,  -288,    13,    13,
    -288,    71,   512,   176,   184,   214,   512,   791,  2669,  2815,
     890,   989,  -288,   170,  -288,   172,  -288,   196,    21,  1088,
     187,   197,     4,  -288,  -288,    30,    19,  -288,     5,  -288,
    -288,  -288,  -288,   -27,  -288,   195,   123,    13,    13,   191,
     201,    39,  -288,  1187,   123,  -288,   198,  -288,  -288,  1286,
     512,   226,  2875,    29,    13,    13,  -288,  -288,  2782,  2875,
      45,    -3,  -288,    13,   276,  2474,    13,  -288,  -288,  -288,
    -288,   199,   210,  -288,  -288,   152,    -3,   152,  -288,  -288,
     192,  -288,  -288,  -288,  -288,  -288,    13,    79,   512,   512,
     123,    13,   215,  -288,  -288,    86,  2474,  -288,    13,   228,
     229,   223,    87,  2875,    13,    -3,  2552,    92,  -288,   512,
     230,  1385,  2845,   221,   244,     7,  -288,  -288,  -288,  2875,
      45,    98,  2875,   247,    45,  1484,   512,   227,   232,   236,
    -288,  -288,  2875,  -288,    82,    13,  2474,  2474,  -288,    13,
    -288,    27,  -288,   238,    45,    13,   239,  -288,   241,   246,
    2474,  2875,  1583,  1682,  2688,   233,  -288,  2474,   268,  2875,
    2474,   269,   270,  1781,  -288,  -288,  2474,  -288,  1880,  2474,
    1979,  2474,  2474,  -288,  2078,  -288,  2177,  -288,  2276,  2375,
    -288,  -288,  -288,  -288
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,   118,     0,     0,     0,
       0,    87,     6,     0,     0,     0,     0,     0,     0,     0,
     149,   150,   151,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,     0,     0,     0,   177,     0,     0,
       0,   152,   146,   147,   148,   165,     0,     2,    25,     9,
       3,    10,    13,    14,    11,     7,     8,    15,    16,   156,
     155,    20,    22,    23,    21,    24,    26,    27,    28,    17,
      18,    12,    19,    29,    30,   119,   120,   160,   161,   121,
     164,   159,   154,   157,   162,   163,   158,    70,    70,     0,
       0,     0,   117,     0,   152,     0,     0,     0,     0,    41,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    39,   112,     0,     0,   174,   176,    60,
      63,     0,    61,   142,   141,     0,     0,   178,     0,     0,
      37,    38,     1,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   170,     0,     0,    71,     0,
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,     0,     0,     0,    47,     0,     0,   103,
     109,   114,     0,     0,     0,     0,     0,   181,     0,     0,
      40,     0,     0,     0,     0,     0,     0,     0,     0,   153,
       0,   173,     0,   122,   123,   124,   125,   126,   135,   136,
     137,   138,   139,   140,   127,   128,   129,   130,   131,   132,
     133,   134,   167,   166,   171,     0,     0,    68,     0,     0,
      69,     0,    78,     0,    65,     0,    83,     0,     0,     0,
       0,     0,    92,     0,    46,     0,    44,     0,     0,     0,
       0,     0,     0,   104,   110,     0,     0,   115,     0,   100,
      99,    97,    98,     0,    94,     0,    60,     0,     0,     0,
       0,     0,     5,     0,    60,   175,     0,    64,    62,     0,
      81,     0,   179,     0,   170,     0,   168,    74,     0,    72,
      75,     0,    66,     0,    85,     0,     0,    89,    91,    43,
      45,     0,     0,    48,    54,   103,     0,     0,   101,   106,
       0,   108,   113,   116,    93,    95,     0,     0,    80,    84,
      60,     0,     0,   180,    31,     0,     0,   143,     0,     0,
       0,    32,     0,   172,     0,     0,     0,     0,    67,    79,
       0,     0,     0,     0,    50,     0,   107,   105,   111,    96,
      75,     0,   182,     0,    75,     0,    82,     0,     0,     0,
      33,   169,    73,    76,    77,     0,     0,     0,    90,     0,
      51,     0,   102,     0,    75,     0,     0,   144,     0,     0,
       0,    59,     0,     0,     0,     0,    49,     0,     0,   183,
       0,     0,     0,     0,    55,    86,     0,    52,     0,     0,
       0,     0,     0,    36,     0,    56,     0,    57,     0,     0,
      88,    58,    34,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -288,  -288,    67,  -288,  -288,   -22,  -288,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,    32,  -288,  -288,  -288,  -173,  -115,
     136,  -183,  -288,   277,  -288,  -288,  -287,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,    95,  -288,  -288,    59,
    -245,  -288,  -288,  -288,  -288,  -288,  -288,    -6,  -288,  -288,
    -288,  -288,   -25,  -288,  -288,  -288,    83,  -288,  -288,  -288,
    -288,  -288,  -288
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    46,    47,    48,    49,    50,    51,    52,   331,   360,
      53,    54,    55,   176,   248,   371,    56,    57,    58,   121,
     122,   235,    59,   157,   158,    60,   337,    61,    62,    63,
      64,    65,    66,    67,    68,   263,   264,   265,    69,   252,
     253,    70,   255,    71,    72,   258,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,   225,    83,    84,    85,
     128,    86,   271
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      92,    93,    95,    96,   193,   117,   118,   309,   257,   178,
       3,   277,   173,   105,   174,   281,     1,     2,   259,   245,
      87,    88,   259,     3,   106,   133,    98,   123,   124,   195,
     126,   127,   171,   130,   131,   256,    89,    20,    21,    22,
     196,   106,   107,   108,    24,    29,   231,   246,   256,    90,
     200,    99,   179,    91,    30,    31,    32,   172,    29,   109,
      33,   314,   347,   373,   201,   162,   166,   376,   197,   195,
     260,   261,   175,   262,   260,   261,   109,   262,    34,   276,
     307,   159,   159,   307,   119,   313,   233,   388,   163,   167,
      97,   198,   308,   312,   234,   372,   120,   302,    36,   100,
     309,   251,    37,   385,   251,   101,   310,   190,   338,   303,
      41,    42,    43,    44,    45,   322,   285,   386,   311,   335,
     102,   329,   336,   346,   330,   103,   286,   323,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   195,   133,   224,
     226,   317,   363,   153,   154,   195,   232,   290,   236,   325,
     238,   239,   195,   285,   170,   350,   133,   155,   111,   365,
     133,   156,   354,   361,   195,   104,   115,   110,   188,   366,
     133,   112,   113,   192,   374,   114,     1,     2,   125,   129,
     132,   280,   161,   164,   282,   177,   202,   139,   140,   141,
     142,   143,   144,   180,   181,   351,   183,    20,    21,    22,
     184,   185,   186,   187,    24,   133,   189,   191,   133,   133,
     120,   194,   288,   289,    30,    31,    32,   133,   222,   223,
      33,   227,   237,   228,   243,   240,   241,    -1,    -1,    -1,
      -1,    -1,    -1,   230,   249,   244,   247,   250,    34,   251,
     254,   133,   266,   267,   268,   269,   273,   133,   270,   274,
     284,   318,   319,   279,   292,   293,   291,   299,    36,   300,
     301,   306,    37,   316,   305,   321,   320,   328,   224,   333,
      94,    42,    43,    44,    45,   326,   340,   339,   343,   348,
     342,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     349,   364,   353,   357,   358,   352,   359,   367,   370,   133,
     302,   375,   356,   380,   378,   387,   390,   391,   362,   379,
     397,   278,   392,   133,   344,   287,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   399,   401,   402,   315,   381,
     133,   133,   341,   384,   345,   160,     0,   332,     0,   389,
       0,   133,     0,     0,     0,     0,   133,   165,   133,     0,
       0,     0,   133,     0,   133,     0,   133,   133,     0,     0,
       0,     0,     0,   355,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,   382,   383,    29,    30,    31,    32,     0,
       0,     0,    33,     0,     0,     0,     0,   393,     0,     0,
       0,     0,     0,     0,   398,     0,     0,   400,     0,     0,
      34,     0,     0,   404,     0,     0,   406,     0,   408,   409,
     136,   137,   138,   139,   140,   141,   142,   143,   144,    35,
      36,     0,     0,   242,    37,     0,    38,     0,     0,    39,
       0,    40,    41,    42,    43,    44,    45,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
       0,    33,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     0,     0,     0,     0,     0,   134,    34,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,     0,    35,    36,
       0,     0,   272,    37,     0,    38,     0,     0,    39,     0,
      40,    41,    42,    43,    44,    45,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,     0,
      33,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,    34,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,    35,    36,     0,
       0,   275,    37,     0,    38,     0,     0,    39,     0,    40,
      41,    42,    43,    44,    45,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,     0,    33,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,     0,     0,   147,   148,   149,   150,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,     0,     0,
     283,    37,     0,    38,     0,     0,    39,     0,    40,    41,
      42,    43,    44,    45,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    36,     0,     0,   294,
      37,     0,    38,     0,     0,    39,     0,    40,    41,    42,
      43,    44,    45,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,     0,     0,   297,    37,
       0,    38,     0,     0,    39,     0,    40,    41,    42,    43,
      44,    45,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,    36,     0,     0,   298,    37,     0,
      38,     0,     0,    39,     0,    40,    41,    42,    43,    44,
      45,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,     0,     0,   304,    37,     0,    38,
       0,     0,    39,     0,    40,    41,    42,    43,    44,    45,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    36,     0,     0,   324,    37,     0,    38,     0,
       0,    39,     0,    40,    41,    42,    43,    44,    45,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,     0,     0,   327,    37,     0,    38,     0,     0,
      39,     0,    40,    41,    42,    43,    44,    45,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,     0,     0,   368,    37,     0,    38,     0,     0,    39,
       0,    40,    41,    42,    43,    44,    45,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,    36,
       0,     0,   377,    37,     0,    38,     0,     0,    39,     0,
      40,    41,    42,    43,    44,    45,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    36,     0,
       0,   394,    37,     0,    38,     0,     0,    39,     0,    40,
      41,    42,    43,    44,    45,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,     0,     0,
     395,    37,     0,    38,     0,     0,    39,     0,    40,    41,
      42,    43,    44,    45,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    36,     0,     0,   403,
      37,     0,    38,     0,     0,    39,     0,    40,    41,    42,
      43,    44,    45,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,     0,     0,   405,    37,
       0,    38,     0,     0,    39,     0,    40,    41,    42,    43,
      44,    45,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,    36,     0,     0,   407,    37,     0,
      38,     0,     0,    39,     0,    40,    41,    42,    43,    44,
      45,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,     0,     0,   410,    37,     0,    38,
       0,     0,    39,     0,    40,    41,    42,    43,    44,    45,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    36,     0,     0,   411,    37,     0,    38,     0,
       0,    39,     0,    40,    41,    42,    43,    44,    45,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,     0,     0,   412,    37,     0,    38,     0,     0,
      39,     0,    40,    41,    42,    43,    44,    45,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,     0,     0,   413,    37,     0,    38,     0,     0,    39,
       0,    40,    41,    42,    43,    44,    45,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     1,     2,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
       0,    33,     0,    20,    21,    22,     0,     0,     0,     0,
      24,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      30,    31,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     0,    35,    36,
       0,     0,     0,    37,     0,    38,     0,     0,    39,     0,
      40,    41,    42,    43,    44,    45,    20,    21,    22,     0,
       0,     0,     0,    24,    36,     0,   116,     0,    37,     0,
       0,     0,     0,    30,    31,    32,    41,    42,    43,    44,
      45,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,    37,   168,     0,     0,     0,     0,     0,     0,    41,
      42,    43,    44,    45,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,     0,     0,     0,   169,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,     0,     0,     0,   295,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   396,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,     0,     0,   199,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   229,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     334,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     296,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     369,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,   119,    30,    31,   252,   181,    44,
       5,   194,    27,    19,    29,   198,     3,     4,    45,    72,
      87,    87,    45,     5,     5,    47,    72,    33,    34,    76,
      36,    37,    72,    39,    40,    30,    97,    24,    25,    26,
      87,     5,     6,     7,    31,    40,   161,   100,    30,    97,
      76,    97,    87,    97,    41,    42,    43,    97,    40,    40,
      47,    88,   307,   350,    90,    51,    28,   354,    51,    76,
      97,    98,    87,   100,    97,    98,    40,   100,    65,    86,
      76,    87,    88,    76,    85,   258,    89,   374,    74,    51,
      87,    74,    88,    88,    97,    88,    97,    76,    85,    97,
     345,    97,    89,    76,    97,    97,    76,   113,   291,    88,
      97,    98,    99,   100,   101,    76,    76,    90,    88,    74,
      97,    92,    77,   306,    95,    97,    86,    88,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,    76,   170,   155,
     156,   266,   335,    71,    72,    76,   162,    86,   164,   274,
     166,   167,    76,    76,    97,    86,   188,    85,    87,    77,
     192,    89,    86,    86,    76,    97,     5,    97,   111,    87,
     202,    97,    97,   116,    86,    97,     3,     4,    97,    87,
       0,   197,    85,    51,   200,    87,   129,    51,    52,    53,
      54,    55,    56,    87,    87,   320,    97,    24,    25,    26,
      97,    97,     5,    87,    31,   237,    87,    97,   240,   241,
      97,    74,   228,   229,    41,    42,    43,   249,    97,    97,
      47,    88,   165,    76,    72,   168,   169,    51,    52,    53,
      54,    55,    56,    88,   177,    97,    36,    97,    65,    97,
      97,   273,    85,    51,    51,    97,   189,   279,    97,    85,
      85,   267,   268,   196,    80,    51,    90,    97,    85,    97,
      74,    74,    89,    78,    87,    74,    85,    51,   284,   285,
      97,    98,    99,   100,   101,    87,    10,   293,    89,    97,
     296,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
     316,   336,    97,    85,    85,   321,    93,    87,    97,   341,
      76,    74,   328,    87,    97,    87,    87,    86,   334,    97,
      97,   195,    86,   355,   302,    90,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    87,    87,    87,   263,   365,
     382,   383,   295,   369,   305,    88,    -1,   284,    -1,   375,
      -1,   393,    -1,    -1,    -1,    -1,   398,    87,   400,    -1,
      -1,    -1,   404,    -1,   406,    -1,   408,   409,    -1,    -1,
      -1,    -1,    -1,   326,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,   366,   367,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,   380,    -1,    -1,
      -1,    -1,    -1,    -1,   387,    -1,    -1,   390,    -1,    -1,
      65,    -1,    -1,   396,    -1,    -1,   399,    -1,   401,   402,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    84,
      85,    -1,    -1,    88,    89,    -1,    91,    -1,    -1,    94,
      -1,    96,    97,    98,    99,   100,   101,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    46,    65,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    84,    85,
      -1,    -1,    88,    89,    -1,    91,    -1,    -1,    94,    -1,
      96,    97,    98,    99,   100,   101,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    65,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    84,    85,    -1,
      -1,    88,    89,    -1,    91,    -1,    -1,    94,    -1,    96,
      97,    98,    99,   100,   101,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    47,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    59,    60,    61,    62,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      88,    89,    -1,    91,    -1,    -1,    94,    -1,    96,    97,
      98,    99,   100,   101,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    88,
      89,    -1,    91,    -1,    -1,    94,    -1,    96,    97,    98,
      99,   100,   101,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    88,    89,
      -1,    91,    -1,    -1,    94,    -1,    96,    97,    98,    99,
     100,   101,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    88,    89,    -1,
      91,    -1,    -1,    94,    -1,    96,    97,    98,    99,   100,
     101,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    88,    89,    -1,    91,
      -1,    -1,    94,    -1,    96,    97,    98,    99,   100,   101,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    88,    89,    -1,    91,    -1,
      -1,    94,    -1,    96,    97,    98,    99,   100,   101,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    88,    89,    -1,    91,    -1,    -1,
      94,    -1,    96,    97,    98,    99,   100,   101,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    88,    89,    -1,    91,    -1,    -1,    94,
      -1,    96,    97,    98,    99,   100,   101,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    88,    89,    -1,    91,    -1,    -1,    94,    -1,
      96,    97,    98,    99,   100,   101,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    88,    89,    -1,    91,    -1,    -1,    94,    -1,    96,
      97,    98,    99,   100,   101,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      88,    89,    -1,    91,    -1,    -1,    94,    -1,    96,    97,
      98,    99,   100,   101,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    88,
      89,    -1,    91,    -1,    -1,    94,    -1,    96,    97,    98,
      99,   100,   101,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    88,    89,
      -1,    91,    -1,    -1,    94,    -1,    96,    97,    98,    99,
     100,   101,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    88,    89,    -1,
      91,    -1,    -1,    94,    -1,    96,    97,    98,    99,   100,
     101,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    88,    89,    -1,    91,
      -1,    -1,    94,    -1,    96,    97,    98,    99,   100,   101,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    88,    89,    -1,    91,    -1,
      -1,    94,    -1,    96,    97,    98,    99,   100,   101,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    88,    89,    -1,    91,    -1,    -1,
      94,    -1,    96,    97,    98,    99,   100,   101,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    88,    89,    -1,    91,    -1,    -1,    94,
      -1,    96,    97,    98,    99,   100,   101,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,     3,     4,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    84,    85,
      -1,    -1,    -1,    89,    -1,    91,    -1,    -1,    94,    -1,
      96,    97,    98,    99,   100,   101,    24,    25,    26,    -1,
      -1,    -1,    -1,    31,    85,    -1,    87,    -1,    89,    -1,
      -1,    -1,    -1,    41,    42,    43,    97,    98,    99,   100,
     101,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    89,    87,    -1,    -1,    -1,    -1,    -1,    -1,    97,
      98,    99,   100,   101,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    40,
      41,    42,    43,    47,    65,    84,    85,    89,    91,    94,
      96,    97,    98,    99,   100,   101,   103,   104,   105,   106,
     107,   108,   109,   112,   113,   114,   118,   119,   120,   124,
     127,   129,   130,   131,   132,   133,   134,   135,   136,   140,
     143,   145,   146,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   159,   160,   161,   163,    87,    87,    97,
      97,    97,   149,   149,    97,   149,   149,    87,    72,    97,
      97,    97,    97,    97,    97,   149,     5,     6,     7,    40,
      97,    87,    97,    97,    97,     5,    87,   154,   154,    85,
      97,   121,   122,   149,   149,    97,   149,   149,   162,    87,
     149,   149,     0,   107,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    71,    72,    85,    89,   125,   126,   149,
     125,    85,    51,    74,    51,    87,    28,    51,    87,    87,
     104,    72,    97,    27,    29,    87,   115,    87,    44,    87,
      87,    87,    87,    97,    97,    97,     5,    87,   104,    87,
     149,    97,   104,   121,    74,    76,    87,    51,    74,    86,
      76,    90,   104,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,    97,    97,   149,   158,   149,    88,    76,    78,
      88,   121,   149,    89,    97,   123,   149,   104,   149,   149,
     104,   104,    88,    72,    97,    72,   100,    36,   116,   104,
      97,    97,   141,   142,    97,   144,    30,   120,   147,    45,
      97,    98,   100,   137,   138,   139,    85,    51,    51,    97,
      97,   164,    88,   104,    85,    88,    86,   123,   122,   104,
     149,   123,   149,    88,    85,    76,    86,    90,   149,   149,
      86,    90,    80,    51,    88,    87,    75,    88,    88,    97,
      97,    74,    76,    88,    88,    87,    74,    76,    88,   142,
      76,    88,    88,   120,    88,   138,    78,   121,   149,   149,
      85,    74,    76,    88,    88,   121,    87,    88,    51,    92,
      95,   110,   158,   149,    78,    74,    77,   128,   123,   149,
      10,   104,   149,    89,   116,   141,   123,   142,    97,   149,
      86,   121,   149,    97,    86,   104,   149,    85,    85,    93,
     111,    86,   149,   123,   154,    77,    87,    87,    88,    75,
      97,   117,    88,   128,    86,    74,   128,    88,    97,    97,
      87,   149,   104,   104,   149,    76,    90,    87,   128,   149,
      87,    86,    86,   104,    88,    88,    87,    97,   104,    87,
     104,    87,    87,    88,   104,    88,   104,    88,   104,   104,
      88,    88,    88,    88
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   103,   104,   104,   105,   106,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   108,   109,   109,   110,   110,   111,   112,   112,   113,
     113,   114,   114,   114,   114,   114,   114,   114,   115,   116,
     116,   117,   117,   118,   119,   120,   120,   120,   120,   120,
     121,   121,   121,   122,   122,   123,   123,   123,   124,   124,
     125,   125,   126,   126,   127,   128,   128,   128,   129,   129,
     129,   129,   129,   130,   130,   131,   131,   132,   133,   133,
     133,   134,   135,   136,   137,   137,   138,   139,   139,   139,
     139,   140,   140,   141,   141,   141,   141,   142,   143,   144,
     144,   144,   145,   146,   147,   147,   147,   148,   148,   149,
     149,   149,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   151,   151,   152,   152,   153,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   155,   156,   156,   157,   157,
     158,   158,   158,   159,   160,   160,   161,   162,   162,   162,
     163,   164,   164,   164
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     6,     7,     7,     4,     2,     2,     2,
       3,     2,     3,     5,     4,     5,     4,     3,     3,     5,
       3,     1,     3,     2,     5,     9,    10,    10,    11,     8,
       0,     1,     3,     1,     3,     1,     2,     3,     4,     4,
       0,     1,     3,     5,     4,     0,     2,     2,     4,     6,
       5,     4,     6,     4,     5,     5,     9,     1,    11,     5,
       7,     5,     4,     5,     1,     2,     3,     1,     1,     1,
       1,     5,     7,     0,     1,     3,     2,     3,     5,     0,
       1,     3,     2,     5,     0,     1,     2,     2,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     5,     7,     4,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     4,     6,
       0,     1,     3,     3,     2,     4,     2,     0,     1,     3,
       5,     0,     3,     5
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
  case 2: /* program: statement_list  */
#line 109 "src/parser/parser.y"
                   {
        program_root = create_program_node((yyvsp[0].node_list));
    }
#line 2064 "parser.c"
    break;

  case 3: /* statement_list: statement  */
#line 115 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2073 "parser.c"
    break;

  case 4: /* statement_list: statement_list statement  */
#line 119 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2082 "parser.c"
    break;

  case 5: /* unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 125 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_unsafe_node((yyvsp[-1].node_list));
    }
#line 2090 "parser.c"
    break;

  case 6: /* continue_statement: TOKEN_CONTINUE  */
#line 130 "src/parser/parser.y"
                   {
        (yyval.node) = create_continue_node();
    }
#line 2098 "parser.c"
    break;

  case 30: /* statement: expression  */
#line 160 "src/parser/parser.y"
                 {
        (yyval.node) = create_expr_statement((yyvsp[0].node));
    }
#line 2106 "parser.c"
    break;

  case 31: /* nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 165 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_nnl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2114 "parser.c"
    break;

  case 32: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block  */
#line 171 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_try_node((yyvsp[-2].node_list), (yyvsp[0].node), NULL);
    }
#line 2122 "parser.c"
    break;

  case 33: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block  */
#line 174 "src/parser/parser.y"
                                                                                   {
        (yyval.node) = create_try_node((yyvsp[-3].node_list), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2130 "parser.c"
    break;

  case 34: /* catch_block: TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 180 "src/parser/parser.y"
                                                                                                    {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2138 "parser.c"
    break;

  case 35: /* catch_block: TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 183 "src/parser/parser.y"
                                                                                                       {
        (yyval.node) = create_catch_node((yyvsp[-4].string), (yyvsp[-1].node_list));
    }
#line 2146 "parser.c"
    break;

  case 36: /* finally_block: TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 189 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_finally_node((yyvsp[-1].node_list));
    }
#line 2154 "parser.c"
    break;

  case 37: /* throw_statement: TOKEN_THROW expression  */
#line 195 "src/parser/parser.y"
                           {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2162 "parser.c"
    break;

  case 38: /* throw_statement: TOKEN_RAISE expression  */
#line 198 "src/parser/parser.y"
                             {
        (yyval.node) = create_throw_node((yyvsp[0].node));
    }
#line 2170 "parser.c"
    break;

  case 39: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER  */
#line 203 "src/parser/parser.y"
                               {
        (yyval.node) = create_jmp_node((yyvsp[0].string), NULL);
    }
#line 2178 "parser.c"
    break;

  case 40: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression  */
#line 206 "src/parser/parser.y"
                                            {
        (yyval.node) = create_jmp_node((yyvsp[-1].string), (yyvsp[0].node));
    }
#line 2186 "parser.c"
    break;

  case 41: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER  */
#line 212 "src/parser/parser.y"
                                  {
        (yyval.node) = create_import_node((yyvsp[0].string), NULL, NULL);
    }
#line 2194 "parser.c"
    break;

  case 42: /* import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_IDENTIFIER  */
#line 215 "src/parser/parser.y"
                                              {
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "./%s", (yyvsp[0].string));
        (yyval.node) = create_import_node(path, NULL, NULL);
        free(path);
    }
#line 2205 "parser.c"
    break;

  case 43: /* import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_DOT TOKEN_DOT TOKEN_IDENTIFIER  */
#line 221 "src/parser/parser.y"
                                                                  {
        char* path = malloc(strlen((yyvsp[0].string)) + 4);
        sprintf(path, "../%s", (yyvsp[0].string));
        (yyval.node) = create_import_node(path, NULL, NULL);
        free(path);
    }
#line 2216 "parser.c"
    break;

  case 44: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_STRING  */
#line 227 "src/parser/parser.y"
                                                            {
        (yyval.node) = create_import_node((yyvsp[0].string), (yyvsp[-2].string), NULL);
    }
#line 2224 "parser.c"
    break;

  case 45: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_DOT TOKEN_IDENTIFIER  */
#line 231 "src/parser/parser.y"
                                                                          {
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "./%s", (yyvsp[0].string));
        (yyval.node) = create_import_node(path, (yyvsp[-3].string), NULL);
        free(path);
    }
#line 2235 "parser.c"
    break;

  case 46: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_AS TOKEN_IDENTIFIER  */
#line 237 "src/parser/parser.y"
                                                              {
        (yyval.node) = create_import_node((yyvsp[-2].string), (yyvsp[0].string), NULL);
    }
#line 2243 "parser.c"
    break;

  case 47: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER import_constraints  */
#line 240 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_import_node((yyvsp[-1].string), NULL, (yyvsp[0].node));
    }
#line 2251 "parser.c"
    break;

  case 48: /* import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE  */
#line 246 "src/parser/parser.y"
                                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2259 "parser.c"
    break;

  case 49: /* import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET  */
#line 252 "src/parser/parser.y"
                                                                   {
        (yyval.node) = create_constraints_node("only", (yyvsp[-1].node_list));
    }
#line 2267 "parser.c"
    break;

  case 50: /* import_options: import_options TOKEN_COMMA import_options  */
#line 255 "src/parser/parser.y"
                                                {
        (yyval.node) = merge_constraints((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2275 "parser.c"
    break;

  case 51: /* name_list: TOKEN_IDENTIFIER  */
#line 261 "src/parser/parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2284 "parser.c"
    break;

  case 52: /* name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 265 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2293 "parser.c"
    break;

  case 53: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
#line 272 "src/parser/parser.y"
                                  {
        (yyval.node) = create_export_node((yyvsp[0].string));
    }
#line 2301 "parser.c"
    break;

  case 54: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 278 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_packet_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2309 "parser.c"
    break;

  case 55: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 284 "src/parser/parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2317 "parser.c"
    break;

  case 56: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 287 "src/parser/parser.y"
                                                                                                                                    {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2325 "parser.c"
    break;

  case 57: /* function_decl: TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 290 "src/parser/parser.y"
                                                                                                                                      {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        (yyval.node) = node;
    }
#line 2336 "parser.c"
    break;

  case 58: /* function_decl: TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 296 "src/parser/parser.y"
                                                                                                                                                {
        ASTNode* node = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        (yyval.node) = node;
    }
#line 2348 "parser.c"
    break;

  case 59: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression  */
#line 303 "src/parser/parser.y"
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node((yyvsp[0].node));
        add_to_node_list(body, return_stmt);
        (yyval.node) = create_function_node((yyvsp[-6].string), (yyvsp[-4].node_list), (yyvsp[-2].node), body);
    }
#line 2359 "parser.c"
    break;

  case 60: /* param_list: %empty  */
#line 312 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2367 "parser.c"
    break;

  case 61: /* param_list: param  */
#line 315 "src/parser/parser.y"
            {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2376 "parser.c"
    break;

  case 62: /* param_list: param_list TOKEN_COMMA param  */
#line 319 "src/parser/parser.y"
                                   {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2385 "parser.c"
    break;

  case 63: /* param: TOKEN_IDENTIFIER  */
#line 326 "src/parser/parser.y"
                     {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 2393 "parser.c"
    break;

  case 64: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 329 "src/parser/parser.y"
                                        {
        (yyval.node) = create_param_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2401 "parser.c"
    break;

  case 65: /* type: TOKEN_IDENTIFIER  */
#line 335 "src/parser/parser.y"
                     {
        (yyval.node) = create_type_node((yyvsp[0].string));
    }
#line 2409 "parser.c"
    break;

  case 66: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
#line 338 "src/parser/parser.y"
                                      {
        (yyval.node) = create_optional_type_node((yyvsp[-1].string));
    }
#line 2417 "parser.c"
    break;

  case 67: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 341 "src/parser/parser.y"
                                         {
        (yyval.node) = create_array_type_node((yyvsp[0].node));
    }
#line 2425 "parser.c"
    break;

  case 68: /* dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 349 "src/parser/parser.y"
                                                      {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2433 "parser.c"
    break;

  case 69: /* dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 352 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2441 "parser.c"
    break;

  case 70: /* dict_entries: %empty  */
#line 358 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2449 "parser.c"
    break;

  case 71: /* dict_entries: dict_entry_list  */
#line 361 "src/parser/parser.y"
                      {
        (yyval.node_list) = (yyvsp[0].node_list);
    }
#line 2457 "parser.c"
    break;

  case 72: /* dict_entry_list: expression TOKEN_FAT_ARROW expression  */
#line 367 "src/parser/parser.y"
                                          {
        (yyval.node_list) = create_node_list();
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyval.node_list), pair);
    }
#line 2467 "parser.c"
    break;

  case 73: /* dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression  */
#line 372 "src/parser/parser.y"
                                                                        {
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyvsp[-4].node_list), pair);
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 2477 "parser.c"
    break;

  case 74: /* dict_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 381 "src/parser/parser.y"
                                                          {
        // Détecter si c'est un accès dictionnaire ou tableau
        // Par défaut, c'est un accès tableau, mais on peut différencier par le type
        // Pour l'instant, on crée un nœud d'accès dictionnaire
        (yyval.node) = create_dict_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2488 "parser.c"
    break;

  case 75: /* return_type: %empty  */
#line 400 "src/parser/parser.y"
                {
        (yyval.node) = NULL;
    }
#line 2496 "parser.c"
    break;

  case 76: /* return_type: TOKEN_COLON type  */
#line 403 "src/parser/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2504 "parser.c"
    break;

  case 77: /* return_type: TOKEN_ARROW primary_expr  */
#line 406 "src/parser/parser.y"
                               {
        // Pour les retours directs: -> expr
        (yyval.node) = create_return_direct_node((yyvsp[0].node));
    }
#line 2513 "parser.c"
    break;

  case 78: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 413 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2521 "parser.c"
    break;

  case 79: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 416 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_let_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2529 "parser.c"
    break;

  case 80: /* let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 419 "src/parser/parser.y"
                                                                   {
        ASTNode* node = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2539 "parser.c"
    break;

  case 81: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 425 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_muts_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2547 "parser.c"
    break;

  case 82: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 428 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_muts_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2555 "parser.c"
    break;

  case 83: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 433 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2563 "parser.c"
    break;

  case 84: /* const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 436 "src/parser/parser.y"
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2574 "parser.c"
    break;

  case 85: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 445 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-1].node_list), NULL);
    }
#line 2582 "parser.c"
    break;

  case 86: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 448 "src/parser/parser.y"
                                                                                                                       {
        (yyval.node) = create_if_node((yyvsp[-7].node), (yyvsp[-5].node_list), (yyvsp[-1].node_list));
    }
#line 2590 "parser.c"
    break;

  case 87: /* break_statement: TOKEN_BREAK  */
#line 453 "src/parser/parser.y"
                {
        (yyval.node) = create_break_node();
    }
#line 2598 "parser.c"
    break;

  case 88: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 458 "src/parser/parser.y"
                                                                                                                                                      {
        ASTNode* init = create_let_node((yyvsp[-9].string), NULL, (yyvsp[-7].node));
        ASTNode* cond = (yyvsp[-5].node);
        ASTNode* inc = create_expr_statement((yyvsp[-3].node));
        (yyval.node) = create_for_node(init, cond, inc, (yyvsp[-1].node_list));
    }
#line 2609 "parser.c"
    break;

  case 89: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 464 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2617 "parser.c"
    break;

  case 90: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 467 "src/parser/parser.y"
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
#line 2635 "parser.c"
    break;

  case 91: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 483 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2643 "parser.c"
    break;

  case 92: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 489 "src/parser/parser.y"
                                                        {
        (yyval.node) = create_loop_node((yyvsp[-1].node_list));
    }
#line 2651 "parser.c"
    break;

  case 93: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 496 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2659 "parser.c"
    break;

  case 94: /* match_cases: match_case  */
#line 502 "src/parser/parser.y"
               {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2668 "parser.c"
    break;

  case 95: /* match_cases: match_cases match_case  */
#line 506 "src/parser/parser.y"
                             {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2677 "parser.c"
    break;

  case 96: /* match_case: pattern TOKEN_FAT_ARROW expression  */
#line 513 "src/parser/parser.y"
                                       {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2685 "parser.c"
    break;

  case 97: /* pattern: TOKEN_NUMBER  */
#line 519 "src/parser/parser.y"
                 {
        (yyval.node) = create_pattern_number((yyvsp[0].number));
    }
#line 2693 "parser.c"
    break;

  case 98: /* pattern: TOKEN_STRING  */
#line 522 "src/parser/parser.y"
                   {
        (yyval.node) = create_pattern_string((yyvsp[0].string));
    }
#line 2701 "parser.c"
    break;

  case 99: /* pattern: TOKEN_IDENTIFIER  */
#line 525 "src/parser/parser.y"
                       {
        (yyval.node) = create_pattern_ident((yyvsp[0].string));
    }
#line 2709 "parser.c"
    break;

  case 100: /* pattern: TOKEN_UNDERSCORE  */
#line 528 "src/parser/parser.y"
                       {
        (yyval.node) = create_pattern_wildcard();
    }
#line 2717 "parser.c"
    break;

  case 101: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 534 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_struct_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2725 "parser.c"
    break;

  case 102: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 537 "src/parser/parser.y"
                                                                                                           {
        (yyval.node) = create_struct_extend_node((yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2733 "parser.c"
    break;

  case 103: /* struct_fields: %empty  */
#line 543 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2741 "parser.c"
    break;

  case 104: /* struct_fields: struct_field  */
#line 546 "src/parser/parser.y"
                   {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2750 "parser.c"
    break;

  case 105: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
#line 550 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2759 "parser.c"
    break;

  case 106: /* struct_fields: struct_fields struct_field  */
#line 554 "src/parser/parser.y"
                                 {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2768 "parser.c"
    break;

  case 107: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 561 "src/parser/parser.y"
                                      {
        (yyval.node) = create_field_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2776 "parser.c"
    break;

  case 108: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
#line 567 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_enum_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2784 "parser.c"
    break;

  case 109: /* enum_variants: %empty  */
#line 573 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2792 "parser.c"
    break;

  case 110: /* enum_variants: TOKEN_IDENTIFIER  */
#line 576 "src/parser/parser.y"
                       {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2801 "parser.c"
    break;

  case 111: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 580 "src/parser/parser.y"
                                                 {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2810 "parser.c"
    break;

  case 112: /* module_decl: TOKEN_MODULE TOKEN_IDENTIFIER  */
#line 587 "src/parser/parser.y"
                                  {
        // Créer un nœud nil pour éviter l'erreur
        (yyval.node) = create_expr_statement(create_nil_node());
    }
#line 2819 "parser.c"
    break;

  case 113: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
#line 594 "src/parser/parser.y"
                                                                             {
        (yyval.node) = create_impl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2827 "parser.c"
    break;

  case 114: /* function_decl_list: %empty  */
#line 600 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2835 "parser.c"
    break;

  case 115: /* function_decl_list: function_decl  */
#line 603 "src/parser/parser.y"
                    {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2844 "parser.c"
    break;

  case 116: /* function_decl_list: function_decl_list function_decl  */
#line 607 "src/parser/parser.y"
                                       {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2853 "parser.c"
    break;

  case 117: /* return_statement: TOKEN_RETURN expression  */
#line 614 "src/parser/parser.y"
                            {
        (yyval.node) = create_return_node((yyvsp[0].node));
    }
#line 2861 "parser.c"
    break;

  case 118: /* return_statement: TOKEN_RETURN  */
#line 617 "src/parser/parser.y"
                   {
        (yyval.node) = create_return_node(NULL);
    }
#line 2869 "parser.c"
    break;

  case 122: /* binary_expr: expression TOKEN_PLUS expression  */
#line 629 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_ADD, (yyvsp[0].node));
    }
#line 2877 "parser.c"
    break;

  case 123: /* binary_expr: expression TOKEN_MINUS expression  */
#line 632 "src/parser/parser.y"
                                        {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_SUB, (yyvsp[0].node));
    }
#line 2885 "parser.c"
    break;

  case 124: /* binary_expr: expression TOKEN_MULTIPLY expression  */
#line 635 "src/parser/parser.y"
                                           {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
    }
#line 2893 "parser.c"
    break;

  case 125: /* binary_expr: expression TOKEN_DIVIDE expression  */
#line 638 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
    }
#line 2901 "parser.c"
    break;

  case 126: /* binary_expr: expression TOKEN_MODULO expression  */
#line 641 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
    }
#line 2909 "parser.c"
    break;

  case 127: /* binary_expr: expression TOKEN_EQ expression  */
#line 644 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_EQ, (yyvsp[0].node));
    }
#line 2917 "parser.c"
    break;

  case 128: /* binary_expr: expression TOKEN_NEQ expression  */
#line 647 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_NEQ, (yyvsp[0].node));
    }
#line 2925 "parser.c"
    break;

  case 129: /* binary_expr: expression TOKEN_LT expression  */
#line 650 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
    }
#line 2933 "parser.c"
    break;

  case 130: /* binary_expr: expression TOKEN_LTE expression  */
#line 653 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LTE, (yyvsp[0].node));
    }
#line 2941 "parser.c"
    break;

  case 131: /* binary_expr: expression TOKEN_GT expression  */
#line 656 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
    }
#line 2949 "parser.c"
    break;

  case 132: /* binary_expr: expression TOKEN_GTE expression  */
#line 659 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GTE, (yyvsp[0].node));
    }
#line 2957 "parser.c"
    break;

  case 133: /* binary_expr: expression TOKEN_AND expression  */
#line 662 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_AND, (yyvsp[0].node));
    }
#line 2965 "parser.c"
    break;

  case 134: /* binary_expr: expression TOKEN_OR expression  */
#line 665 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_OR, (yyvsp[0].node));
    }
#line 2973 "parser.c"
    break;

  case 135: /* binary_expr: expression TOKEN_ASSIGN expression  */
#line 668 "src/parser/parser.y"
                                         {
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2981 "parser.c"
    break;

  case 136: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
#line 671 "src/parser/parser.y"
                                              {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_ADD_ASSIGN, (yyvsp[0].node));
    }
#line 2989 "parser.c"
    break;

  case 137: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
#line 674 "src/parser/parser.y"
                                               {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_SUB_ASSIGN, (yyvsp[0].node));
    }
#line 2997 "parser.c"
    break;

  case 138: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
#line 677 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MUL_ASSIGN, (yyvsp[0].node));
    }
#line 3005 "parser.c"
    break;

  case 139: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
#line 680 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_DIV_ASSIGN, (yyvsp[0].node));
    }
#line 3013 "parser.c"
    break;

  case 140: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
#line 683 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MOD_ASSIGN, (yyvsp[0].node));
    }
#line 3021 "parser.c"
    break;

  case 141: /* unary_expr: TOKEN_NOT expression  */
#line 689 "src/parser/parser.y"
                         {
        (yyval.node) = create_unary_op(OP_NOT, (yyvsp[0].node));
    }
#line 3029 "parser.c"
    break;

  case 142: /* unary_expr: TOKEN_MINUS expression  */
#line 692 "src/parser/parser.y"
                             {
        (yyval.node) = create_unary_op(OP_NEG, (yyvsp[0].node));
    }
#line 3037 "parser.c"
    break;

  case 143: /* lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 699 "src/parser/parser.y"
                                                                     {
        (yyval.node) = create_lambda_node((yyvsp[-3].node_list), (yyvsp[-1].node_list));
    }
#line 3045 "parser.c"
    break;

  case 144: /* lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 702 "src/parser/parser.y"
                                                                                                 {
        (yyval.node) = create_lambda_node((yyvsp[-4].node_list), (yyvsp[-1].node_list));
    }
#line 3053 "parser.c"
    break;

  case 145: /* array_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 709 "src/parser/parser.y"
                                                          {
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 3061 "parser.c"
    break;

  case 146: /* primary_expr: TOKEN_NUMBER  */
#line 715 "src/parser/parser.y"
                 {
        (yyval.node) = create_number_node((yyvsp[0].number));
    }
#line 3069 "parser.c"
    break;

  case 147: /* primary_expr: TOKEN_FLOAT  */
#line 718 "src/parser/parser.y"
                  {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 3077 "parser.c"
    break;

  case 148: /* primary_expr: TOKEN_STRING  */
#line 721 "src/parser/parser.y"
                   {
        (yyval.node) = create_string_node((yyvsp[0].string));
    }
#line 3085 "parser.c"
    break;

  case 149: /* primary_expr: TOKEN_TRUE  */
#line 724 "src/parser/parser.y"
                 {
        (yyval.node) = create_bool_node(1);
    }
#line 3093 "parser.c"
    break;

  case 150: /* primary_expr: TOKEN_FALSE  */
#line 727 "src/parser/parser.y"
                  {
        (yyval.node) = create_bool_node(0);
    }
#line 3101 "parser.c"
    break;

  case 151: /* primary_expr: TOKEN_NIL  */
#line 730 "src/parser/parser.y"
                {
        (yyval.node) = create_nil_node();
    }
#line 3109 "parser.c"
    break;

  case 152: /* primary_expr: TOKEN_IDENTIFIER  */
#line 733 "src/parser/parser.y"
                       {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 3117 "parser.c"
    break;

  case 153: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 736 "src/parser/parser.y"
                                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3125 "parser.c"
    break;

  case 165: /* f_string: TOKEN_F_STRING  */
#line 753 "src/parser/parser.y"
                   {
        (yyval.node) = parse_f_string((yyvsp[0].string));
    }
#line 3133 "parser.c"
    break;

  case 166: /* member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER  */
#line 759 "src/parser/parser.y"
                                            {
        (yyval.node) = create_member_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3141 "parser.c"
    break;

  case 167: /* member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 762 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_static_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 3149 "parser.c"
    break;

  case 168: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 768 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_call_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 3157 "parser.c"
    break;

  case 169: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 771 "src/parser/parser.y"
                                                                                               {
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3165 "parser.c"
    break;

  case 170: /* argument_list: %empty  */
#line 777 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3173 "parser.c"
    break;

  case 171: /* argument_list: expression  */
#line 780 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_arg_list();
        add_arg((yyval.node_list), (yyvsp[0].node));
    }
#line 3182 "parser.c"
    break;

  case 172: /* argument_list: argument_list TOKEN_COMMA expression  */
#line 784 "src/parser/parser.y"
                                           {
        add_arg((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3191 "parser.c"
    break;

  case 173: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
#line 791 "src/parser/parser.y"
                                              {
        (yyval.node) = create_array_node((yyvsp[-1].node_list));
    }
#line 3199 "parser.c"
    break;

  case 174: /* await_expr: TOKEN_AWAIT primary_expr  */
#line 806 "src/parser/parser.y"
                             {
        (yyval.node) = create_await_node((yyvsp[0].node));
    }
#line 3207 "parser.c"
    break;

  case 175: /* await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 809 "src/parser/parser.y"
                                                           {
        (yyval.node) = create_await_block_node((yyvsp[-1].node_list));
    }
#line 3215 "parser.c"
    break;

  case 176: /* spawn_expr: TOKEN_SPAWN primary_expr  */
#line 816 "src/parser/parser.y"
                             {
        (yyval.node) = create_spawn_node((yyvsp[0].node));
    }
#line 3223 "parser.c"
    break;

  case 177: /* array_items: %empty  */
#line 828 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3231 "parser.c"
    break;

  case 178: /* array_items: expression  */
#line 831 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 3240 "parser.c"
    break;

  case 179: /* array_items: array_items TOKEN_COMMA expression  */
#line 835 "src/parser/parser.y"
                                         {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 3249 "parser.c"
    break;

  case 180: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
#line 842 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_struct_init_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 3257 "parser.c"
    break;

  case 181: /* struct_init_fields: %empty  */
#line 848 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3265 "parser.c"
    break;

  case 182: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 851 "src/parser/parser.y"
                                              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
    }
#line 3274 "parser.c"
    break;

  case 183: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 855 "src/parser/parser.y"
                                                                             {
        add_to_node_list((yyvsp[-4].node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 3283 "parser.c"
    break;


#line 3287 "parser.c"

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

#line 867 "src/parser/parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

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
  YYSYMBOL_TOKEN_FN = 3,                   /* TOKEN_FN  */
  YYSYMBOL_TOKEN_LET = 4,                  /* TOKEN_LET  */
  YYSYMBOL_TOKEN_CONST = 5,                /* TOKEN_CONST  */
  YYSYMBOL_TOKEN_RETURN = 6,               /* TOKEN_RETURN  */
  YYSYMBOL_TOKEN_IF = 7,                   /* TOKEN_IF  */
  YYSYMBOL_TOKEN_ELSE = 8,                 /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_NEW = 9,                  /* TOKEN_NEW  */
  YYSYMBOL_TOKEN_FOR = 10,                 /* TOKEN_FOR  */
  YYSYMBOL_TOKEN_WHILE = 11,               /* TOKEN_WHILE  */
  YYSYMBOL_TOKEN_LOOP = 12,                /* TOKEN_LOOP  */
  YYSYMBOL_TOKEN_BREAK = 13,               /* TOKEN_BREAK  */
  YYSYMBOL_TOKEN_CONTINUE = 14,            /* TOKEN_CONTINUE  */
  YYSYMBOL_TOKEN_IMPORT = 15,              /* TOKEN_IMPORT  */
  YYSYMBOL_TOKEN_EXPORT = 16,              /* TOKEN_EXPORT  */
  YYSYMBOL_TOKEN_PACKET = 17,              /* TOKEN_PACKET  */
  YYSYMBOL_TOKEN_STRUCT = 18,              /* TOKEN_STRUCT  */
  YYSYMBOL_TOKEN_ENUM = 19,                /* TOKEN_ENUM  */
  YYSYMBOL_TOKEN_IMPL = 20,                /* TOKEN_IMPL  */
  YYSYMBOL_TOKEN_MATCH = 21,               /* TOKEN_MATCH  */
  YYSYMBOL_TOKEN_TYPE = 22,                /* TOKEN_TYPE  */
  YYSYMBOL_TOKEN_TRUE = 23,                /* TOKEN_TRUE  */
  YYSYMBOL_TOKEN_FALSE = 24,               /* TOKEN_FALSE  */
  YYSYMBOL_TOKEN_NIL = 25,                 /* TOKEN_NIL  */
  YYSYMBOL_TOKEN_AS = 26,                  /* TOKEN_AS  */
  YYSYMBOL_TOKEN_IN = 27,                  /* TOKEN_IN  */
  YYSYMBOL_TOKEN_FROM = 28,                /* TOKEN_FROM  */
  YYSYMBOL_TOKEN_PUB = 29,                 /* TOKEN_PUB  */
  YYSYMBOL_TOKEN_UNDERSCORE = 30,          /* TOKEN_UNDERSCORE  */
  YYSYMBOL_TOKEN_PLUS = 31,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 32,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MULTIPLY = 33,            /* TOKEN_MULTIPLY  */
  YYSYMBOL_TOKEN_DIVIDE = 34,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 35,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_ASSIGN = 36,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 37,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 38,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 39,     /* TOKEN_MULTIPLY_ASSIGN  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 40,       /* TOKEN_DIVIDE_ASSIGN  */
  YYSYMBOL_TOKEN_MODULO_ASSIGN = 41,       /* TOKEN_MODULO_ASSIGN  */
  YYSYMBOL_TOKEN_EQ = 42,                  /* TOKEN_EQ  */
  YYSYMBOL_TOKEN_NEQ = 43,                 /* TOKEN_NEQ  */
  YYSYMBOL_TOKEN_LT = 44,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LTE = 45,                 /* TOKEN_LTE  */
  YYSYMBOL_TOKEN_GT = 46,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GTE = 47,                 /* TOKEN_GTE  */
  YYSYMBOL_TOKEN_AND = 48,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 49,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_NOT = 50,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_AMP = 51,                 /* TOKEN_AMP  */
  YYSYMBOL_TOKEN_PIPE = 52,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_XOR = 53,                 /* TOKEN_XOR  */
  YYSYMBOL_TOKEN_LSHIFT = 54,              /* TOKEN_LSHIFT  */
  YYSYMBOL_TOKEN_RSHIFT = 55,              /* TOKEN_RSHIFT  */
  YYSYMBOL_TOKEN_DOUBLE_COLON = 56,        /* TOKEN_DOUBLE_COLON  */
  YYSYMBOL_TOKEN_DOT = 57,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_COLON = 58,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_SEMICOLON = 59,           /* TOKEN_SEMICOLON  */
  YYSYMBOL_TOKEN_COMMA = 60,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_ARROW = 61,               /* TOKEN_ARROW  */
  YYSYMBOL_TOKEN_FAT_ARROW = 62,           /* TOKEN_FAT_ARROW  */
  YYSYMBOL_TOKEN_PIPE_FORWARD = 63,        /* TOKEN_PIPE_FORWARD  */
  YYSYMBOL_TOKEN_OPTIONAL = 64,            /* TOKEN_OPTIONAL  */
  YYSYMBOL_TOKEN_COALESCE = 65,            /* TOKEN_COALESCE  */
  YYSYMBOL_TOKEN_RANGE = 66,               /* TOKEN_RANGE  */
  YYSYMBOL_TOKEN_RANGE_INC = 67,           /* TOKEN_RANGE_INC  */
  YYSYMBOL_TOKEN_LPAREN = 68,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 69,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_LBRACE = 70,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 71,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_LBRACKET = 72,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 73,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_IDENTIFIER = 74,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_NUMBER = 75,              /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_FLOAT = 76,               /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_STRING = 77,              /* TOKEN_STRING  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_program = 79,                   /* program  */
  YYSYMBOL_statement_list = 80,            /* statement_list  */
  YYSYMBOL_statement = 81,                 /* statement  */
  YYSYMBOL_import_statement = 82,          /* import_statement  */
  YYSYMBOL_export_statement = 83,          /* export_statement  */
  YYSYMBOL_packet_decl = 84,               /* packet_decl  */
  YYSYMBOL_function_decl = 85,             /* function_decl  */
  YYSYMBOL_param_list = 86,                /* param_list  */
  YYSYMBOL_param = 87,                     /* param  */
  YYSYMBOL_type = 88,                      /* type  */
  YYSYMBOL_return_type = 89,               /* return_type  */
  YYSYMBOL_let_decl = 90,                  /* let_decl  */
  YYSYMBOL_const_decl = 91,                /* const_decl  */
  YYSYMBOL_if_statement = 92,              /* if_statement  */
  YYSYMBOL_for_statement = 93,             /* for_statement  */
  YYSYMBOL_while_statement = 94,           /* while_statement  */
  YYSYMBOL_loop_statement = 95,            /* loop_statement  */
  YYSYMBOL_match_statement = 96,           /* match_statement  */
  YYSYMBOL_match_cases = 97,               /* match_cases  */
  YYSYMBOL_match_case = 98,                /* match_case  */
  YYSYMBOL_pattern = 99,                   /* pattern  */
  YYSYMBOL_struct_decl = 100,              /* struct_decl  */
  YYSYMBOL_struct_fields = 101,            /* struct_fields  */
  YYSYMBOL_struct_field = 102,             /* struct_field  */
  YYSYMBOL_enum_decl = 103,                /* enum_decl  */
  YYSYMBOL_enum_variants = 104,            /* enum_variants  */
  YYSYMBOL_impl_decl = 105,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 106,       /* function_decl_list  */
  YYSYMBOL_return_statement = 107,         /* return_statement  */
  YYSYMBOL_expression = 108,               /* expression  */
  YYSYMBOL_binary_expr = 109,              /* binary_expr  */
  YYSYMBOL_unary_expr = 110,               /* unary_expr  */
  YYSYMBOL_primary_expr = 111,             /* primary_expr  */
  YYSYMBOL_call_expr = 112,                /* call_expr  */
  YYSYMBOL_argument_list = 113,            /* argument_list  */
  YYSYMBOL_array_expr = 114,               /* array_expr  */
  YYSYMBOL_array_items = 115,              /* array_items  */
  YYSYMBOL_struct_expr = 116,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 117        /* struct_init_fields  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   980

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  237

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   332


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
      75,    76,    77
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    75,    75,    81,    85,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   113,   116,   122,   128,   134,   137,   143,   146,   150,
     157,   160,   166,   169,   172,   178,   181,   187,   190,   196,
     202,   205,   211,   214,   220,   226,   232,   238,   242,   249,
     255,   258,   261,   264,   270,   276,   279,   283,   290,   296,
     302,   305,   309,   316,   322,   325,   329,   336,   339,   345,
     346,   347,   351,   354,   357,   360,   363,   366,   369,   372,
     375,   378,   381,   384,   387,   390,   393,   396,   399,   402,
     405,   411,   414,   420,   423,   426,   429,   432,   435,   438,
     441,   444,   445,   446,   450,   453,   459,   462,   466,   473,
     479,   482,   486,   493,   499,   502,   506
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
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_FN",
  "TOKEN_LET", "TOKEN_CONST", "TOKEN_RETURN", "TOKEN_IF", "TOKEN_ELSE",
  "TOKEN_NEW", "TOKEN_FOR", "TOKEN_WHILE", "TOKEN_LOOP", "TOKEN_BREAK",
  "TOKEN_CONTINUE", "TOKEN_IMPORT", "TOKEN_EXPORT", "TOKEN_PACKET",
  "TOKEN_STRUCT", "TOKEN_ENUM", "TOKEN_IMPL", "TOKEN_MATCH", "TOKEN_TYPE",
  "TOKEN_TRUE", "TOKEN_FALSE", "TOKEN_NIL", "TOKEN_AS", "TOKEN_IN",
  "TOKEN_FROM", "TOKEN_PUB", "TOKEN_UNDERSCORE", "TOKEN_PLUS",
  "TOKEN_MINUS", "TOKEN_MULTIPLY", "TOKEN_DIVIDE", "TOKEN_MODULO",
  "TOKEN_ASSIGN", "TOKEN_PLUS_ASSIGN", "TOKEN_MINUS_ASSIGN",
  "TOKEN_MULTIPLY_ASSIGN", "TOKEN_DIVIDE_ASSIGN", "TOKEN_MODULO_ASSIGN",
  "TOKEN_EQ", "TOKEN_NEQ", "TOKEN_LT", "TOKEN_LTE", "TOKEN_GT",
  "TOKEN_GTE", "TOKEN_AND", "TOKEN_OR", "TOKEN_NOT", "TOKEN_AMP",
  "TOKEN_PIPE", "TOKEN_XOR", "TOKEN_LSHIFT", "TOKEN_RSHIFT",
  "TOKEN_DOUBLE_COLON", "TOKEN_DOT", "TOKEN_COLON", "TOKEN_SEMICOLON",
  "TOKEN_COMMA", "TOKEN_ARROW", "TOKEN_FAT_ARROW", "TOKEN_PIPE_FORWARD",
  "TOKEN_OPTIONAL", "TOKEN_COALESCE", "TOKEN_RANGE", "TOKEN_RANGE_INC",
  "TOKEN_LPAREN", "TOKEN_RPAREN", "TOKEN_LBRACE", "TOKEN_RBRACE",
  "TOKEN_LBRACKET", "TOKEN_RBRACKET", "TOKEN_IDENTIFIER", "TOKEN_NUMBER",
  "TOKEN_FLOAT", "TOKEN_STRING", "$accept", "program", "statement_list",
  "statement", "import_statement", "export_statement", "packet_decl",
  "function_decl", "param_list", "param", "type", "return_type",
  "let_decl", "const_decl", "if_statement", "for_statement",
  "while_statement", "loop_statement", "match_statement", "match_cases",
  "match_case", "pattern", "struct_decl", "struct_fields", "struct_field",
  "enum_decl", "enum_variants", "impl_decl", "function_decl_list",
  "return_statement", "expression", "binary_expr", "unary_expr",
  "primary_expr", "call_expr", "argument_list", "array_expr",
  "array_items", "struct_expr", "struct_init_fields", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332
};
#endif

#define YYPACT_NINF (-169)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     672,   -46,   -36,   -29,   128,   128,   -21,   635,   128,   -10,
     -12,   -11,    -8,    -7,    -6,    -5,   128,  -169,  -169,  -169,
      46,   128,   128,   128,   128,  -169,  -169,  -169,  -169,    64,
     672,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,   931,  -169,  -169,
     -41,  -169,  -169,  -169,    -3,   -22,    34,   931,   719,     1,
      45,   738,   778,   672,    66,  -169,     4,    26,    28,    31,
     797,    29,   931,   931,   856,   931,   -51,  -169,  -169,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,    30,   128,
      32,   128,   -13,   128,   672,    33,   128,   672,   672,   115,
      35,   672,    36,    37,     5,   -19,    40,  -169,   128,  -169,
     931,   931,   931,   931,   931,   931,   931,   931,   931,   931,
     931,   931,   931,   931,   931,   931,   931,   931,   931,    41,
     931,   -44,    47,   -37,  -169,   931,    42,    49,    80,   931,
     224,    59,   -34,   895,   261,   336,  -169,  -169,   373,    65,
     -31,  -169,  -169,   -30,  -169,     2,  -169,  -169,  -169,  -169,
     -23,  -169,    67,    32,   931,   128,   128,  -169,   -13,    32,
      70,   -13,  -169,   128,   134,   128,    69,  -169,   128,  -169,
    -169,  -169,   -13,    36,  -169,    74,  -169,  -169,  -169,  -169,
    -169,   128,   -27,   -25,   931,  -169,  -169,   -13,    84,  -169,
     931,    85,   931,    92,   837,  -169,  -169,  -169,   931,    70,
    -169,  -169,   672,   672,   128,   672,    86,   448,   485,   931,
     560,   672,  -169,  -169,  -169,   597,  -169
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,    68,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    96,    97,    98,
       0,     0,     0,     0,   110,    99,    93,    94,    95,     0,
       2,     3,     5,     6,     7,     8,    12,    13,    14,    15,
      16,    17,    18,     9,    10,    11,    19,    20,    69,    70,
      71,   101,   102,   103,     0,     0,     0,    67,     0,     0,
      99,     0,     0,     0,    21,    23,     0,     0,     0,     0,
       0,     0,    92,    91,     0,   111,     0,     1,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
      27,     0,     0,     0,     0,   114,     0,     0,     0,     0,
       0,     0,    55,    60,    64,     0,     0,   100,     0,   109,
      72,    73,    74,    75,    76,    85,    86,    87,    88,    89,
      90,    77,    78,    79,    80,    81,    82,    83,    84,     0,
     107,     0,    30,     0,    28,    37,     0,    32,     0,    39,
       0,     0,     0,     0,     0,     0,    45,    22,     0,     0,
       0,    56,    61,     0,    65,     0,    53,    52,    50,    51,
       0,    47,     0,    27,   112,   106,     0,   104,     0,     0,
      35,     0,    33,     0,    40,     0,     0,   113,     0,    42,
      44,    24,     0,     0,    54,     0,    59,    63,    66,    46,
      48,     0,     0,     0,   108,    31,    29,     0,     0,    34,
      38,     0,   115,     0,     0,    58,    57,    62,    49,    35,
     105,    36,     0,     0,     0,     0,     0,     0,     0,   116,
       0,     0,    25,    41,    43,     0,    26
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -169,  -169,   -61,    -9,  -169,  -169,  -169,  -108,   -16,   -20,
    -168,   -56,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
      -2,  -169,  -169,  -169,   -35,  -169,  -169,  -169,  -169,  -169,
      -4,  -169,  -169,  -169,  -169,    -1,  -169,  -169,  -169,  -169
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    29,    30,    31,    32,    33,    34,    35,   143,   144,
     148,   208,    36,    37,    38,    39,    40,    41,    42,   170,
     171,   172,    43,   160,   161,    44,   163,    45,   165,    46,
      47,    48,    49,    50,    51,   141,    52,    76,    53,   152
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,    58,   109,    61,    62,     1,   164,   166,     1,   118,
     205,   166,    70,   209,   101,    98,   176,    72,    73,    74,
      75,    78,   119,   179,   215,   177,   186,    99,    54,   193,
     195,    20,   180,   179,    20,   176,   102,   187,    55,   221,
     194,   196,   219,   150,   220,    56,   154,   155,   199,    71,
     158,   167,   168,    59,   169,   167,   168,   198,   169,   146,
      63,   147,    64,    65,    77,   100,    66,    67,    68,    69,
     103,   105,   106,   197,   111,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   110,   140,   112,   145,   113,   149,
      78,   114,   153,   116,   139,   178,   142,   151,   173,   175,
     159,   162,   157,   182,   174,   181,   183,   185,     1,     2,
       3,     4,     5,   192,     6,     7,     8,     9,   207,   201,
      10,    11,    12,    13,    14,    15,    16,     6,    17,    18,
      19,    78,   211,   213,    20,    78,    78,    21,   217,    78,
     224,    17,    18,    19,   222,   223,   231,   202,   216,   206,
      21,   227,   228,   226,   230,    22,     0,     0,   200,     0,
     235,   140,   204,     0,   203,     0,     0,     0,    22,   210,
       0,   212,     0,    23,   214,     0,   156,    24,     0,    25,
      26,    27,    28,     0,     0,     0,    23,   218,     0,     0,
      24,     0,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    78,    78,
     229,    78,     0,     0,     0,     0,    78,     1,     2,     3,
       4,     5,     0,     6,     7,     8,     9,     0,     0,    10,
      11,    12,    13,    14,    15,    16,     0,    17,    18,    19,
       0,     0,     0,    20,     0,     0,    21,     0,     0,     0,
       0,     0,     0,     0,     1,     2,     3,     4,     5,     0,
       6,     7,     8,     9,    22,     0,    10,    11,    12,    13,
      14,    15,    16,     0,    17,    18,    19,     0,     0,     0,
      20,     0,    23,    21,     0,   184,    24,     0,    25,    26,
      27,    28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    23,
       0,     0,   189,    24,     0,    25,    26,    27,    28,     1,
       2,     3,     4,     5,     0,     6,     7,     8,     9,     0,
       0,    10,    11,    12,    13,    14,    15,    16,     0,    17,
      18,    19,     0,     0,     0,    20,     0,     0,    21,     0,
       0,     0,     0,     0,     0,     0,     1,     2,     3,     4,
       5,     0,     6,     7,     8,     9,    22,     0,    10,    11,
      12,    13,    14,    15,    16,     0,    17,    18,    19,     0,
       0,     0,    20,     0,    23,    21,     0,   190,    24,     0,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,     0,     0,   191,    24,     0,    25,    26,    27,
      28,     1,     2,     3,     4,     5,     0,     6,     7,     8,
       9,     0,     0,    10,    11,    12,    13,    14,    15,    16,
       0,    17,    18,    19,     0,     0,     0,    20,     0,     0,
      21,     0,     0,     0,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     0,     6,     7,     8,     9,    22,     0,
      10,    11,    12,    13,    14,    15,    16,     0,    17,    18,
      19,     0,     0,     0,    20,     0,    23,    21,     0,   232,
      24,     0,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,     0,     0,   233,    24,     0,    25,
      26,    27,    28,     1,     2,     3,     4,     5,     0,     6,
       7,     8,     9,     0,     0,    10,    11,    12,    13,    14,
      15,    16,     0,    17,    18,    19,     0,     0,     0,    20,
       0,     0,    21,     0,     0,     0,     0,     0,     0,     0,
       1,     2,     3,     4,     5,     0,     6,     7,     8,     9,
      22,     0,    10,    11,    12,    13,    14,    15,    16,     0,
      17,    18,    19,     0,     0,     0,    20,     0,    23,    21,
       0,   234,    24,     0,    25,    26,    27,    28,     0,     0,
       0,     0,     0,     0,     6,     0,     0,    22,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    18,
      19,     0,     0,     0,     0,    23,     0,    21,   236,    24,
       0,    25,    26,    27,    28,     1,     2,     3,     4,     5,
       0,     6,     7,     8,     9,    22,     0,    10,    11,    12,
      13,    14,    15,    16,     0,    17,    18,    19,     0,     0,
       0,    20,     0,    23,    21,     0,     0,    24,     0,    60,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,     0,     0,     0,    24,     0,    25,    26,    27,    28,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,     0,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,     0,   108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,     0,   225,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   117,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   188,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97
};

static const yytype_int16 yycheck[] =
{
       4,     5,    63,     7,     8,     3,   114,    30,     3,    60,
     178,    30,    16,   181,    36,    56,    60,    21,    22,    23,
      24,    30,    73,    60,   192,    69,    60,    68,    74,    60,
      60,    29,    69,    60,    29,    60,    58,    71,    74,   207,
      71,    71,    69,   104,    69,    74,   107,   108,    71,     3,
     111,    74,    75,    74,    77,    74,    75,   165,    77,    72,
      70,    74,    74,    74,     0,    68,    74,    74,    74,    74,
      36,    70,    27,    71,    70,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    28,    99,    70,   101,    70,   103,
     109,    70,   106,    74,    74,    58,    74,    74,    68,    68,
      74,    74,    77,    64,   118,    73,    36,    58,     3,     4,
       5,     6,     7,    58,     9,    10,    11,    12,    58,    62,
      15,    16,    17,    18,    19,    20,    21,     9,    23,    24,
      25,   150,     8,    74,    29,   154,   155,    32,    74,   158,
      58,    23,    24,    25,    70,    70,    70,   173,   193,   179,
      32,   222,   223,   219,   225,    50,    -1,    -1,   170,    -1,
     231,   175,   176,    -1,   175,    -1,    -1,    -1,    50,   183,
      -1,   185,    -1,    68,   188,    -1,    71,    72,    -1,    74,
      75,    76,    77,    -1,    -1,    -1,    68,   201,    -1,    -1,
      72,    -1,    74,    75,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,
     224,   230,    -1,    -1,    -1,    -1,   235,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    25,
      -1,    -1,    -1,    29,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    50,    -1,    15,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    25,    -1,    -1,    -1,
      29,    -1,    68,    32,    -1,    71,    72,    -1,    74,    75,
      76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    71,    72,    -1,    74,    75,    76,    77,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    -1,    23,
      24,    25,    -1,    -1,    -1,    29,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    50,    -1,    15,    16,
      17,    18,    19,    20,    21,    -1,    23,    24,    25,    -1,
      -1,    -1,    29,    -1,    68,    32,    -1,    71,    72,    -1,
      74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    72,    -1,    74,    75,    76,
      77,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      -1,    23,    24,    25,    -1,    -1,    -1,    29,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    50,    -1,
      15,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      25,    -1,    -1,    -1,    29,    -1,    68,    32,    -1,    71,
      72,    -1,    74,    75,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    71,    72,    -1,    74,
      75,    76,    77,     3,     4,     5,     6,     7,    -1,     9,
      10,    11,    12,    -1,    -1,    15,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    25,    -1,    -1,    -1,    29,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      50,    -1,    15,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    25,    -1,    -1,    -1,    29,    -1,    68,    32,
      -1,    71,    72,    -1,    74,    75,    76,    77,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,
      25,    -1,    -1,    -1,    -1,    68,    -1,    32,    71,    72,
      -1,    74,    75,    76,    77,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    50,    -1,    15,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    25,    -1,    -1,
      -1,    29,    -1,    68,    32,    -1,    -1,    72,    -1,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    -1,    72,    -1,    74,    75,    76,    77,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      15,    16,    17,    18,    19,    20,    21,    23,    24,    25,
      29,    32,    50,    68,    72,    74,    75,    76,    77,    79,
      80,    81,    82,    83,    84,    85,    90,    91,    92,    93,
      94,    95,    96,   100,   103,   105,   107,   108,   109,   110,
     111,   112,   114,   116,    74,    74,    74,   108,   108,    74,
      74,   108,   108,    70,    74,    74,    74,    74,    74,    74,
     108,     3,   108,   108,   108,   108,   115,     0,    81,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    56,    68,
      68,    36,    58,    36,    70,    70,    27,    70,    70,    80,
      28,    70,    70,    70,    70,    70,    74,    69,    60,    73,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,    74,
     108,   113,    74,    86,    87,   108,    72,    74,    88,   108,
      80,    74,   117,   108,    80,    80,    71,    77,    80,    74,
     101,   102,    74,   104,    85,   106,    30,    74,    75,    77,
      97,    98,    99,    68,   108,    68,    60,    69,    58,    60,
      69,    73,    64,    36,    71,    58,    60,    71,    66,    71,
      71,    71,    58,    60,    71,    60,    71,    71,    85,    71,
      98,    62,    86,   113,   108,    88,    87,    58,    89,    88,
     108,     8,   108,    74,   108,    88,   102,    74,   108,    69,
      69,    88,    70,    70,    58,    70,    89,    80,    80,   108,
      80,    70,    71,    71,    71,    80,    71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    78,    79,    80,    80,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    82,    82,    83,    84,    85,    85,    86,    86,    86,
      87,    87,    88,    88,    88,    89,    89,    90,    90,    91,
      92,    92,    93,    93,    94,    95,    96,    97,    97,    98,
      99,    99,    99,    99,   100,   101,   101,   101,   102,   103,
     104,   104,   104,   105,   106,   106,   106,   107,   107,   108,
     108,   108,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   110,   110,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   112,   112,   113,   113,   113,   114,
     115,   115,   115,   116,   117,   117,   117
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     4,     2,     5,     9,    10,     0,     1,     3,
       1,     3,     1,     2,     3,     0,     2,     4,     6,     4,
       5,     9,     5,     9,     5,     4,     5,     1,     2,     3,
       1,     1,     1,     1,     5,     0,     1,     3,     3,     5,
       0,     1,     3,     5,     0,     1,     2,     2,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     4,     6,     0,     1,     3,     3,
       0,     1,     3,     5,     0,     3,     5
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
#line 75 "src/parser/parser.y"
                   {
        program_root = create_program_node((yyvsp[0].node_list));
    }
#line 1530 "parser.c"
    break;

  case 3: /* statement_list: statement  */
#line 81 "src/parser/parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 1539 "parser.c"
    break;

  case 4: /* statement_list: statement_list statement  */
#line 85 "src/parser/parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 1548 "parser.c"
    break;

  case 20: /* statement: expression  */
#line 107 "src/parser/parser.y"
                 {
        (yyval.node) = create_expr_statement((yyvsp[0].node));
    }
#line 1556 "parser.c"
    break;

  case 21: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER  */
#line 113 "src/parser/parser.y"
                                  {
        (yyval.node) = create_import_node((yyvsp[0].string), NULL);
    }
#line 1564 "parser.c"
    break;

  case 22: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_STRING  */
#line 116 "src/parser/parser.y"
                                                            {
        (yyval.node) = create_import_node((yyvsp[0].string), (yyvsp[-2].string));
    }
#line 1572 "parser.c"
    break;

  case 23: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
#line 122 "src/parser/parser.y"
                                  {
        (yyval.node) = create_export_node((yyvsp[0].string));
    }
#line 1580 "parser.c"
    break;

  case 24: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 128 "src/parser/parser.y"
                                                                           {
        (yyval.node) = create_packet_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 1588 "parser.c"
    break;

  case 25: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 134 "src/parser/parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 1596 "parser.c"
    break;

  case 26: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 137 "src/parser/parser.y"
                                                                                                                                    {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 1604 "parser.c"
    break;

  case 27: /* param_list: %empty  */
#line 143 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 1612 "parser.c"
    break;

  case 28: /* param_list: param  */
#line 146 "src/parser/parser.y"
            {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 1621 "parser.c"
    break;

  case 29: /* param_list: param_list TOKEN_COMMA param  */
#line 150 "src/parser/parser.y"
                                   {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 1630 "parser.c"
    break;

  case 30: /* param: TOKEN_IDENTIFIER  */
#line 157 "src/parser/parser.y"
                     {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 1638 "parser.c"
    break;

  case 31: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 160 "src/parser/parser.y"
                                        {
        (yyval.node) = create_param_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 1646 "parser.c"
    break;

  case 32: /* type: TOKEN_IDENTIFIER  */
#line 166 "src/parser/parser.y"
                     {
        (yyval.node) = create_type_node((yyvsp[0].string));
    }
#line 1654 "parser.c"
    break;

  case 33: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
#line 169 "src/parser/parser.y"
                                      {
        (yyval.node) = create_optional_type_node((yyvsp[-1].string));
    }
#line 1662 "parser.c"
    break;

  case 34: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 172 "src/parser/parser.y"
                                         {
        (yyval.node) = create_array_type_node((yyvsp[0].node));
    }
#line 1670 "parser.c"
    break;

  case 35: /* return_type: %empty  */
#line 178 "src/parser/parser.y"
                {
        (yyval.node) = NULL;
    }
#line 1678 "parser.c"
    break;

  case 36: /* return_type: TOKEN_COLON type  */
#line 181 "src/parser/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1686 "parser.c"
    break;

  case 37: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 187 "src/parser/parser.y"
                                                       {
        (yyval.node) = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 1694 "parser.c"
    break;

  case 38: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 190 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_let_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1702 "parser.c"
    break;

  case 39: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 196 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 1710 "parser.c"
    break;

  case 40: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 202 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-1].node_list), NULL);
    }
#line 1718 "parser.c"
    break;

  case 41: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 205 "src/parser/parser.y"
                                                                                                                       {
        (yyval.node) = create_if_node((yyvsp[-7].node), (yyvsp[-5].node_list), (yyvsp[-1].node_list));
    }
#line 1726 "parser.c"
    break;

  case 42: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 211 "src/parser/parser.y"
                                                                  {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 1734 "parser.c"
    break;

  case 43: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_RANGE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 214 "src/parser/parser.y"
                                                                                                                     {
        (yyval.node) = create_for_range_node((yyvsp[-7].string), (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 1742 "parser.c"
    break;

  case 44: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 220 "src/parser/parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 1750 "parser.c"
    break;

  case 45: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 226 "src/parser/parser.y"
                                                        {
        (yyval.node) = create_loop_node((yyvsp[-1].node_list));
    }
#line 1758 "parser.c"
    break;

  case 46: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 232 "src/parser/parser.y"
                                                                 {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 1766 "parser.c"
    break;

  case 47: /* match_cases: match_case  */
#line 238 "src/parser/parser.y"
               {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 1775 "parser.c"
    break;

  case 48: /* match_cases: match_cases match_case  */
#line 242 "src/parser/parser.y"
                             {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 1784 "parser.c"
    break;

  case 49: /* match_case: pattern TOKEN_FAT_ARROW expression  */
#line 249 "src/parser/parser.y"
                                       {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1792 "parser.c"
    break;

  case 50: /* pattern: TOKEN_NUMBER  */
#line 255 "src/parser/parser.y"
                 {
        (yyval.node) = create_pattern_number((yyvsp[0].number));
    }
#line 1800 "parser.c"
    break;

  case 51: /* pattern: TOKEN_STRING  */
#line 258 "src/parser/parser.y"
                   {
        (yyval.node) = create_pattern_string((yyvsp[0].string));
    }
#line 1808 "parser.c"
    break;

  case 52: /* pattern: TOKEN_IDENTIFIER  */
#line 261 "src/parser/parser.y"
                       {
        (yyval.node) = create_pattern_ident((yyvsp[0].string));
    }
#line 1816 "parser.c"
    break;

  case 53: /* pattern: TOKEN_UNDERSCORE  */
#line 264 "src/parser/parser.y"
                       {
        (yyval.node) = create_pattern_wildcard();
    }
#line 1824 "parser.c"
    break;

  case 54: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 270 "src/parser/parser.y"
                                                                          {
        (yyval.node) = create_struct_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 1832 "parser.c"
    break;

  case 55: /* struct_fields: %empty  */
#line 276 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 1840 "parser.c"
    break;

  case 56: /* struct_fields: struct_field  */
#line 279 "src/parser/parser.y"
                   {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 1849 "parser.c"
    break;

  case 57: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
#line 283 "src/parser/parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 1858 "parser.c"
    break;

  case 58: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 290 "src/parser/parser.y"
                                      {
        (yyval.node) = create_field_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 1866 "parser.c"
    break;

  case 59: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
#line 296 "src/parser/parser.y"
                                                                        {
        (yyval.node) = create_enum_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 1874 "parser.c"
    break;

  case 60: /* enum_variants: %empty  */
#line 302 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 1882 "parser.c"
    break;

  case 61: /* enum_variants: TOKEN_IDENTIFIER  */
#line 305 "src/parser/parser.y"
                       {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 1891 "parser.c"
    break;

  case 62: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 309 "src/parser/parser.y"
                                                 {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 1900 "parser.c"
    break;

  case 63: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
#line 316 "src/parser/parser.y"
                                                                             {
        (yyval.node) = create_impl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 1908 "parser.c"
    break;

  case 64: /* function_decl_list: %empty  */
#line 322 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 1916 "parser.c"
    break;

  case 65: /* function_decl_list: function_decl  */
#line 325 "src/parser/parser.y"
                    {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 1925 "parser.c"
    break;

  case 66: /* function_decl_list: function_decl_list function_decl  */
#line 329 "src/parser/parser.y"
                                       {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 1934 "parser.c"
    break;

  case 67: /* return_statement: TOKEN_RETURN expression  */
#line 336 "src/parser/parser.y"
                            {
        (yyval.node) = create_return_node((yyvsp[0].node));
    }
#line 1942 "parser.c"
    break;

  case 68: /* return_statement: TOKEN_RETURN  */
#line 339 "src/parser/parser.y"
                   {
        (yyval.node) = create_return_node(NULL);
    }
#line 1950 "parser.c"
    break;

  case 72: /* binary_expr: expression TOKEN_PLUS expression  */
#line 351 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_ADD, (yyvsp[0].node));
    }
#line 1958 "parser.c"
    break;

  case 73: /* binary_expr: expression TOKEN_MINUS expression  */
#line 354 "src/parser/parser.y"
                                        {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_SUB, (yyvsp[0].node));
    }
#line 1966 "parser.c"
    break;

  case 74: /* binary_expr: expression TOKEN_MULTIPLY expression  */
#line 357 "src/parser/parser.y"
                                           {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
    }
#line 1974 "parser.c"
    break;

  case 75: /* binary_expr: expression TOKEN_DIVIDE expression  */
#line 360 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
    }
#line 1982 "parser.c"
    break;

  case 76: /* binary_expr: expression TOKEN_MODULO expression  */
#line 363 "src/parser/parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
    }
#line 1990 "parser.c"
    break;

  case 77: /* binary_expr: expression TOKEN_EQ expression  */
#line 366 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_EQ, (yyvsp[0].node));
    }
#line 1998 "parser.c"
    break;

  case 78: /* binary_expr: expression TOKEN_NEQ expression  */
#line 369 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_NEQ, (yyvsp[0].node));
    }
#line 2006 "parser.c"
    break;

  case 79: /* binary_expr: expression TOKEN_LT expression  */
#line 372 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
    }
#line 2014 "parser.c"
    break;

  case 80: /* binary_expr: expression TOKEN_LTE expression  */
#line 375 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LTE, (yyvsp[0].node));
    }
#line 2022 "parser.c"
    break;

  case 81: /* binary_expr: expression TOKEN_GT expression  */
#line 378 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
    }
#line 2030 "parser.c"
    break;

  case 82: /* binary_expr: expression TOKEN_GTE expression  */
#line 381 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GTE, (yyvsp[0].node));
    }
#line 2038 "parser.c"
    break;

  case 83: /* binary_expr: expression TOKEN_AND expression  */
#line 384 "src/parser/parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_AND, (yyvsp[0].node));
    }
#line 2046 "parser.c"
    break;

  case 84: /* binary_expr: expression TOKEN_OR expression  */
#line 387 "src/parser/parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_OR, (yyvsp[0].node));
    }
#line 2054 "parser.c"
    break;

  case 85: /* binary_expr: expression TOKEN_ASSIGN expression  */
#line 390 "src/parser/parser.y"
                                         {
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2062 "parser.c"
    break;

  case 86: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
#line 393 "src/parser/parser.y"
                                              {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_ADD_ASSIGN, (yyvsp[0].node));
    }
#line 2070 "parser.c"
    break;

  case 87: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
#line 396 "src/parser/parser.y"
                                               {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_SUB_ASSIGN, (yyvsp[0].node));
    }
#line 2078 "parser.c"
    break;

  case 88: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
#line 399 "src/parser/parser.y"
                                                  {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MUL_ASSIGN, (yyvsp[0].node));
    }
#line 2086 "parser.c"
    break;

  case 89: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
#line 402 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_DIV_ASSIGN, (yyvsp[0].node));
    }
#line 2094 "parser.c"
    break;

  case 90: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
#line 405 "src/parser/parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MOD_ASSIGN, (yyvsp[0].node));
    }
#line 2102 "parser.c"
    break;

  case 91: /* unary_expr: TOKEN_NOT expression  */
#line 411 "src/parser/parser.y"
                         {
        (yyval.node) = create_unary_op(OP_NOT, (yyvsp[0].node));
    }
#line 2110 "parser.c"
    break;

  case 92: /* unary_expr: TOKEN_MINUS expression  */
#line 414 "src/parser/parser.y"
                             {
        (yyval.node) = create_unary_op(OP_NEG, (yyvsp[0].node));
    }
#line 2118 "parser.c"
    break;

  case 93: /* primary_expr: TOKEN_NUMBER  */
#line 420 "src/parser/parser.y"
                 {
        (yyval.node) = create_number_node((yyvsp[0].number));
    }
#line 2126 "parser.c"
    break;

  case 94: /* primary_expr: TOKEN_FLOAT  */
#line 423 "src/parser/parser.y"
                  {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 2134 "parser.c"
    break;

  case 95: /* primary_expr: TOKEN_STRING  */
#line 426 "src/parser/parser.y"
                   {
        (yyval.node) = create_string_node((yyvsp[0].string));
    }
#line 2142 "parser.c"
    break;

  case 96: /* primary_expr: TOKEN_TRUE  */
#line 429 "src/parser/parser.y"
                 {
        (yyval.node) = create_bool_node(1);
    }
#line 2150 "parser.c"
    break;

  case 97: /* primary_expr: TOKEN_FALSE  */
#line 432 "src/parser/parser.y"
                  {
        (yyval.node) = create_bool_node(0);
    }
#line 2158 "parser.c"
    break;

  case 98: /* primary_expr: TOKEN_NIL  */
#line 435 "src/parser/parser.y"
                {
        (yyval.node) = create_nil_node();
    }
#line 2166 "parser.c"
    break;

  case 99: /* primary_expr: TOKEN_IDENTIFIER  */
#line 438 "src/parser/parser.y"
                       {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 2174 "parser.c"
    break;

  case 100: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 441 "src/parser/parser.y"
                                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2182 "parser.c"
    break;

  case 104: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 450 "src/parser/parser.y"
                                                         {
        (yyval.node) = create_call_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2190 "parser.c"
    break;

  case 105: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 453 "src/parser/parser.y"
                                                                                               {
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2198 "parser.c"
    break;

  case 106: /* argument_list: %empty  */
#line 459 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2206 "parser.c"
    break;

  case 107: /* argument_list: expression  */
#line 462 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_arg_list();
        add_arg((yyval.node_list), (yyvsp[0].node));
    }
#line 2215 "parser.c"
    break;

  case 108: /* argument_list: argument_list TOKEN_COMMA expression  */
#line 466 "src/parser/parser.y"
                                           {
        add_arg((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2224 "parser.c"
    break;

  case 109: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
#line 473 "src/parser/parser.y"
                                              {
        (yyval.node) = create_array_node((yyvsp[-1].node_list));
    }
#line 2232 "parser.c"
    break;

  case 110: /* array_items: %empty  */
#line 479 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2240 "parser.c"
    break;

  case 111: /* array_items: expression  */
#line 482 "src/parser/parser.y"
                 {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2249 "parser.c"
    break;

  case 112: /* array_items: array_items TOKEN_COMMA expression  */
#line 486 "src/parser/parser.y"
                                         {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2258 "parser.c"
    break;

  case 113: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
#line 493 "src/parser/parser.y"
                                                                            {
        (yyval.node) = create_struct_init_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2266 "parser.c"
    break;

  case 114: /* struct_init_fields: %empty  */
#line 499 "src/parser/parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2274 "parser.c"
    break;

  case 115: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 502 "src/parser/parser.y"
                                              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
    }
#line 2283 "parser.c"
    break;

  case 116: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 506 "src/parser/parser.y"
                                                                             {
        add_to_node_list((yyvsp[-4].node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 2292 "parser.c"
    break;


#line 2296 "parser.c"

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

#line 518 "src/parser/parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

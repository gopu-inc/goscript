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
  YYSYMBOL_TOKEN_LAMBDA = 40,              /* TOKEN_LAMBDA  */
  YYSYMBOL_TOKEN_EXTENDS = 41,             /* TOKEN_EXTENDS  */
  YYSYMBOL_TOKEN_UNDERSCORE = 42,          /* TOKEN_UNDERSCORE  */
  YYSYMBOL_TOKEN_PLUS = 43,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 44,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MULTIPLY = 45,            /* TOKEN_MULTIPLY  */
  YYSYMBOL_TOKEN_DIVIDE = 46,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 47,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_ASSIGN = 48,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_PLUS_ASSIGN = 49,         /* TOKEN_PLUS_ASSIGN  */
  YYSYMBOL_TOKEN_MINUS_ASSIGN = 50,        /* TOKEN_MINUS_ASSIGN  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 51,     /* TOKEN_MULTIPLY_ASSIGN  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 52,       /* TOKEN_DIVIDE_ASSIGN  */
  YYSYMBOL_TOKEN_MODULO_ASSIGN = 53,       /* TOKEN_MODULO_ASSIGN  */
  YYSYMBOL_TOKEN_EQ = 54,                  /* TOKEN_EQ  */
  YYSYMBOL_TOKEN_NEQ = 55,                 /* TOKEN_NEQ  */
  YYSYMBOL_TOKEN_LT = 56,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LTE = 57,                 /* TOKEN_LTE  */
  YYSYMBOL_TOKEN_GT = 58,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GTE = 59,                 /* TOKEN_GTE  */
  YYSYMBOL_TOKEN_AND = 60,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_OR = 61,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_NOT = 62,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_AMP = 63,                 /* TOKEN_AMP  */
  YYSYMBOL_TOKEN_PIPE = 64,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_XOR = 65,                 /* TOKEN_XOR  */
  YYSYMBOL_TOKEN_LSHIFT = 66,              /* TOKEN_LSHIFT  */
  YYSYMBOL_TOKEN_RSHIFT = 67,              /* TOKEN_RSHIFT  */
  YYSYMBOL_TOKEN_DOUBLE_COLON = 68,        /* TOKEN_DOUBLE_COLON  */
  YYSYMBOL_TOKEN_DOT = 69,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_SECURITY = 70,            /* TOKEN_SECURITY  */
  YYSYMBOL_TOKEN_COLON = 71,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_SEMICOLON = 72,           /* TOKEN_SEMICOLON  */
  YYSYMBOL_TOKEN_COMMA = 73,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_ARROW = 74,               /* TOKEN_ARROW  */
  YYSYMBOL_TOKEN_FAT_ARROW = 75,           /* TOKEN_FAT_ARROW  */
  YYSYMBOL_TOKEN_PIPE_FORWARD = 76,        /* TOKEN_PIPE_FORWARD  */
  YYSYMBOL_TOKEN_OPTIONAL = 77,            /* TOKEN_OPTIONAL  */
  YYSYMBOL_TOKEN_COALESCE = 78,            /* TOKEN_COALESCE  */
  YYSYMBOL_TOKEN_RANGE = 79,               /* TOKEN_RANGE  */
  YYSYMBOL_TOKEN_RANGE_INC = 80,           /* TOKEN_RANGE_INC  */
  YYSYMBOL_TOKEN_MUTS = 81,                /* TOKEN_MUTS  */
  YYSYMBOL_TOKEN_LPAREN = 82,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 83,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_LBRACE = 84,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 85,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_LBRACKET = 86,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 87,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_IDENTIFIER = 88,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_NUMBER = 89,              /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_FLOAT = 90,               /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_STRING = 91,              /* TOKEN_STRING  */
  YYSYMBOL_YYACCEPT = 92,                  /* $accept  */
  YYSYMBOL_program = 93,                   /* program  */
  YYSYMBOL_statement_list = 94,            /* statement_list  */
  YYSYMBOL_unsafe_stmt = 95,               /* unsafe_stmt  */
  YYSYMBOL_continue_statement = 96,        /* continue_statement  */
  YYSYMBOL_statement = 97,                 /* statement  */
  YYSYMBOL_nnl_statement = 98,             /* nnl_statement  */
  YYSYMBOL_jmp_statement = 99,             /* jmp_statement  */
  YYSYMBOL_import_statement = 100,         /* import_statement  */
  YYSYMBOL_import_constraints = 101,       /* import_constraints  */
  YYSYMBOL_import_options = 102,           /* import_options  */
  YYSYMBOL_name_list = 103,                /* name_list  */
  YYSYMBOL_export_statement = 104,         /* export_statement  */
  YYSYMBOL_packet_decl = 105,              /* packet_decl  */
  YYSYMBOL_function_decl = 106,            /* function_decl  */
  YYSYMBOL_param_list = 107,               /* param_list  */
  YYSYMBOL_param = 108,                    /* param  */
  YYSYMBOL_type = 109,                     /* type  */
  YYSYMBOL_dict_expr = 110,                /* dict_expr  */
  YYSYMBOL_dict_entries = 111,             /* dict_entries  */
  YYSYMBOL_dict_entry_list = 112,          /* dict_entry_list  */
  YYSYMBOL_dict_access = 113,              /* dict_access  */
  YYSYMBOL_return_type = 114,              /* return_type  */
  YYSYMBOL_let_decl = 115,                 /* let_decl  */
  YYSYMBOL_const_decl = 116,               /* const_decl  */
  YYSYMBOL_if_statement = 117,             /* if_statement  */
  YYSYMBOL_break_statement = 118,          /* break_statement  */
  YYSYMBOL_for_statement = 119,            /* for_statement  */
  YYSYMBOL_while_statement = 120,          /* while_statement  */
  YYSYMBOL_loop_statement = 121,           /* loop_statement  */
  YYSYMBOL_match_statement = 122,          /* match_statement  */
  YYSYMBOL_match_cases = 123,              /* match_cases  */
  YYSYMBOL_match_case = 124,               /* match_case  */
  YYSYMBOL_pattern = 125,                  /* pattern  */
  YYSYMBOL_struct_decl = 126,              /* struct_decl  */
  YYSYMBOL_struct_fields = 127,            /* struct_fields  */
  YYSYMBOL_struct_field = 128,             /* struct_field  */
  YYSYMBOL_enum_decl = 129,                /* enum_decl  */
  YYSYMBOL_enum_variants = 130,            /* enum_variants  */
  YYSYMBOL_module_decl = 131,              /* module_decl  */
  YYSYMBOL_impl_decl = 132,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 133,       /* function_decl_list  */
  YYSYMBOL_return_statement = 134,         /* return_statement  */
  YYSYMBOL_expression = 135,               /* expression  */
  YYSYMBOL_binary_expr = 136,              /* binary_expr  */
  YYSYMBOL_unary_expr = 137,               /* unary_expr  */
  YYSYMBOL_lambda_expr = 138,              /* lambda_expr  */
  YYSYMBOL_array_access = 139,             /* array_access  */
  YYSYMBOL_primary_expr = 140,             /* primary_expr  */
  YYSYMBOL_member_access = 141,            /* member_access  */
  YYSYMBOL_call_expr = 142,                /* call_expr  */
  YYSYMBOL_argument_list = 143,            /* argument_list  */
  YYSYMBOL_array_expr = 144,               /* array_expr  */
  YYSYMBOL_array_items = 145,              /* array_items  */
  YYSYMBOL_struct_expr = 146,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 147        /* struct_init_fields  */
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
#define YYFINAL  112
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2099

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  353

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   346


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
      85,    86,    87,    88,    89,    90,    91
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   101,   101,   107,   111,   117,   122,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   155,
     161,   164,   170,   173,   179,   185,   189,   195,   198,   204,
     210,   213,   219,   223,   230,   236,   242,   245,   249,   258,
     261,   265,   272,   275,   281,   284,   287,   295,   298,   304,
     307,   313,   318,   327,   346,   349,   352,   359,   362,   365,
     371,   374,   379,   382,   391,   394,   399,   404,   410,   413,
     429,   435,   442,   448,   452,   459,   465,   468,   471,   474,
     480,   483,   489,   492,   496,   500,   507,   513,   519,   522,
     526,   533,   540,   546,   549,   553,   560,   563,   569,   570,
     571,   575,   578,   581,   584,   587,   590,   593,   596,   599,
     602,   605,   608,   611,   614,   617,   620,   623,   626,   629,
     635,   638,   645,   648,   655,   661,   664,   667,   670,   673,
     676,   679,   682,   685,   686,   687,   688,   689,   690,   691,
     692,   696,   699,   705,   708,   714,   717,   721,   728,   734,
     737,   741,   748,   754,   757,   761
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
  "TOKEN_TIMEOUT", "TOKEN_SANDBOX", "TOKEN_ALLOW_FFI", "TOKEN_LAMBDA",
  "TOKEN_EXTENDS", "TOKEN_UNDERSCORE", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_MULTIPLY", "TOKEN_DIVIDE", "TOKEN_MODULO", "TOKEN_ASSIGN",
  "TOKEN_PLUS_ASSIGN", "TOKEN_MINUS_ASSIGN", "TOKEN_MULTIPLY_ASSIGN",
  "TOKEN_DIVIDE_ASSIGN", "TOKEN_MODULO_ASSIGN", "TOKEN_EQ", "TOKEN_NEQ",
  "TOKEN_LT", "TOKEN_LTE", "TOKEN_GT", "TOKEN_GTE", "TOKEN_AND",
  "TOKEN_OR", "TOKEN_NOT", "TOKEN_AMP", "TOKEN_PIPE", "TOKEN_XOR",
  "TOKEN_LSHIFT", "TOKEN_RSHIFT", "TOKEN_DOUBLE_COLON", "TOKEN_DOT",
  "TOKEN_SECURITY", "TOKEN_COLON", "TOKEN_SEMICOLON", "TOKEN_COMMA",
  "TOKEN_ARROW", "TOKEN_FAT_ARROW", "TOKEN_PIPE_FORWARD", "TOKEN_OPTIONAL",
  "TOKEN_COALESCE", "TOKEN_RANGE", "TOKEN_RANGE_INC", "TOKEN_MUTS",
  "TOKEN_LPAREN", "TOKEN_RPAREN", "TOKEN_LBRACE", "TOKEN_RBRACE",
  "TOKEN_LBRACKET", "TOKEN_RBRACKET", "TOKEN_IDENTIFIER", "TOKEN_NUMBER",
  "TOKEN_FLOAT", "TOKEN_STRING", "$accept", "program", "statement_list",
  "unsafe_stmt", "continue_statement", "statement", "nnl_statement",
  "jmp_statement", "import_statement", "import_constraints",
  "import_options", "name_list", "export_statement", "packet_decl",
  "function_decl", "param_list", "param", "type", "dict_expr",
  "dict_entries", "dict_entry_list", "dict_access", "return_type",
  "let_decl", "const_decl", "if_statement", "break_statement",
  "for_statement", "while_statement", "loop_statement", "match_statement",
  "match_cases", "match_case", "pattern", "struct_decl", "struct_fields",
  "struct_field", "enum_decl", "enum_variants", "module_decl", "impl_decl",
  "function_decl_list", "return_statement", "expression", "binary_expr",
  "unary_expr", "lambda_expr", "array_access", "primary_expr",
  "member_access", "call_expr", "argument_list", "array_expr",
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346
};
#endif

#define YYPACT_NINF (-225)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1595,   -61,   -36,   -10,    -9,    11,   179,   179,  1620,   179,
      19,  -225,  -225,   -49,    16,    18,    43,    44,    45,   179,
    -225,  -225,  -225,    91,    46,    21,    47,    49,    51,    13,
     179,   179,    54,   179,   179,  -225,  -225,  -225,  -225,   107,
    1595,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  2038,  -225,  -225,  -225,  -225,
     -39,  -225,  -225,  -225,  -225,   179,   179,    64,   -30,    99,
    2038,  1688,   -14,  1730,  1749,  1595,   -43,   -19,  -225,    66,
     -32,    67,    76,  1791,    60,    74,    75,    80,  1595,    81,
     179,  -225,    78,    98,   -51,  -225,   227,   106,   -29,  1871,
    2038,   -52,  -225,  -225,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,    82,    85,   179,   179,    89,   102,  1912,
      93,    78,   179,   -12,   179,  1595,   179,   179,  1595,  1595,
     349,   110,  -225,    88,   -53,   144,  -225,  1595,   103,   104,
     108,     7,   -27,   113,   133,   149,   112,   438,  1595,  2038,
     -24,   -12,    78,  1595,   179,   -12,  -225,   179,  -225,   227,
     227,   106,   106,   106,   136,   136,   136,   136,   136,   136,
     529,   529,   290,   290,   290,   290,   440,   458,   119,  -225,
    2038,     8,  1669,  -225,   179,   179,  -225,     9,   367,   120,
     129,   160,   367,   527,  1810,  1978,   616,   705,  -225,   121,
    -225,   123,  -225,   141,    -1,   794,   130,   142,   -22,  -225,
    -225,     0,   210,  -225,     1,  -225,  -225,  -225,  -225,   -31,
    -225,   143,    78,   179,   179,   145,     2,  -225,   883,   137,
    -225,  -225,   972,   367,   169,  2038,   179,   179,  -225,  -225,
    1945,  2038,   -21,   -12,  -225,   179,   212,  1595,   179,  -225,
    -225,  -225,  -225,   134,   144,  -225,  -225,   104,   -12,   104,
    -225,  -225,   140,  -225,  -225,  -225,  -225,  -225,   179,    10,
     367,   367,   179,   146,  -225,  -225,  1595,  -225,   179,    17,
    2038,   179,   -12,   223,    -7,  -225,   367,   147,  1061,  2008,
     148,   151,   -17,  -225,  -225,  -225,  2038,   -21,  2038,   159,
    1150,   367,  -225,  2038,  -225,   -39,   179,  1595,  1595,  -225,
     179,  -225,   -41,  -225,   155,   179,  -225,  2038,  1239,  1328,
    1852,   152,  -225,  1595,  2038,  -225,  -225,  1595,  -225,  1417,
    1506,  -225,  -225
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,   107,     0,     0,     0,
       0,    76,     6,     0,     0,     0,     0,     0,     0,     0,
     138,   139,   140,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,     0,   159,   141,   135,   136,   137,     0,
       2,    23,     9,     3,    10,    11,     7,     8,    13,    14,
     145,   144,    18,    20,    21,    19,    22,    24,    25,    26,
      15,    16,    12,    17,    27,    28,   108,   109,   149,   150,
     110,   148,   143,   146,   147,    59,    59,     0,     0,     0,
     106,     0,   141,     0,     0,     0,     0,    32,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      30,   101,    49,    52,     0,    50,   131,   130,     0,     0,
     160,     0,     1,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   155,     0,     0,    60,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,    38,     0,     0,    92,
      98,   103,     0,     0,     0,     0,   163,     0,     0,    31,
       0,     0,     0,     0,     0,     0,   142,     0,   158,   111,
     112,   113,   114,   115,   124,   125,   126,   127,   128,   129,
     116,   117,   118,   119,   120,   121,   122,   123,   152,   151,
     156,     0,     0,    57,     0,     0,    58,     0,    67,     0,
      54,     0,    72,     0,     0,     0,     0,     0,    81,     0,
      37,     0,    35,     0,     0,     0,     0,     0,     0,    93,
      99,     0,     0,   104,     0,    89,    88,    86,    87,     0,
      83,     0,    49,     0,     0,     0,     0,     5,     0,     0,
      53,    51,     0,    70,     0,   161,   155,     0,   153,    63,
       0,    61,    64,     0,    55,     0,    74,     0,     0,    78,
      80,    34,    36,     0,     0,    39,    45,    92,     0,     0,
      90,    95,     0,    97,   102,   105,    82,    84,     0,     0,
      69,    73,     0,     0,   162,    29,     0,   132,     0,     0,
     157,     0,     0,     0,     0,    56,    68,     0,     0,     0,
       0,    41,     0,    96,    94,   100,    85,    64,   164,     0,
       0,    71,   154,    62,    65,    66,     0,     0,     0,    79,
       0,    42,     0,    91,     0,     0,   133,    48,     0,     0,
       0,     0,    40,     0,   165,    46,    75,     0,    43,     0,
       0,    47,    77
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,  -225,     4,  -225,  -225,   -23,  -225,  -225,  -225,  -225,
     -42,  -225,  -225,  -225,  -154,   -97,    61,  -135,  -225,   166,
    -225,  -225,   -82,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,     5,  -225,  -225,   -34,  -224,  -225,  -225,  -225,
    -225,  -225,  -225,    -6,  -225,  -225,  -225,  -225,   -58,  -225,
    -225,    -4,  -225,  -225,  -225,  -225
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    39,    40,    41,    42,    43,    44,    45,    46,   156,
     224,   332,    47,    48,    49,   104,   105,   211,    50,   137,
     138,    51,   304,    52,    53,    54,    55,    56,    57,    58,
      59,   239,   240,   241,    60,   228,   229,    61,   231,    62,
      63,   234,    64,    65,    66,    67,    68,    69,    70,    71,
      72,   201,    73,   111,    74,   246
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,    81,    83,    84,   281,   170,     3,   233,   153,   158,
     154,   235,     3,    93,   146,   235,   221,   113,   142,   174,
      86,   177,   172,    75,   106,   107,   151,   109,   110,   133,
     134,   232,   341,   173,   147,   178,   250,   232,   222,    87,
     254,   143,   175,   135,   207,   152,   342,   136,    76,   172,
     302,   279,   159,   303,   286,   314,   279,   236,   237,   249,
     238,   236,   237,   280,   238,   155,   227,   326,   333,   139,
     139,   227,   274,   282,   209,   293,   210,   327,    77,    78,
     285,   257,   172,   172,   275,   283,   284,   294,   281,   150,
     257,   258,   262,   317,   169,   102,    94,    95,    96,    79,
     322,   103,   167,    85,    88,    98,    89,   112,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   113,   305,   200,
     202,    90,    91,    92,    97,    99,   208,   100,   212,   101,
     214,   215,   108,   313,   113,   289,   141,   144,   163,   213,
     157,   160,   216,   217,   119,   120,   121,   122,   123,   124,
     161,   225,   164,   165,   166,   168,   103,   324,   253,   171,
     198,   255,   248,   199,   203,   204,   220,   252,   206,   219,
     223,   243,     1,     2,    -1,    -1,    -1,    -1,    -1,    -1,
     113,   226,   227,   113,   113,   242,   230,   244,   260,   261,
     245,   256,   113,    20,    21,    22,   264,   263,   265,   271,
      24,   272,   273,   278,   277,    94,   292,   298,   288,    29,
     310,   296,   307,    30,   274,   113,     1,     2,   315,   113,
     335,   328,   311,   251,   319,   334,   331,   290,   291,   343,
     348,    31,   140,   312,   287,   325,     0,    20,    21,    22,
     200,   300,   299,     0,    24,     0,     0,     0,     0,   306,
       0,    33,   309,    29,     0,    34,     0,    35,    36,    37,
      38,   308,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     0,   316,     0,     0,   113,   318,     0,     0,     0,
       0,     0,   321,     0,     0,   323,     0,   113,     0,     0,
     320,     0,     0,     0,     0,    33,     0,     0,     0,    34,
       0,    35,    36,    37,    38,   113,   113,     0,     0,     0,
     337,     0,     0,     0,   340,     0,   113,   113,     0,   344,
       0,   338,   339,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,     0,     0,     0,   349,     0,     0,
       0,   350,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
       0,     0,     0,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,    31,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,     0,
      32,    33,     0,     0,   218,    34,     0,    35,    36,    37,
      38,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,     0,
       0,     0,    30,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
      31,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,    32,
      33,     0,     0,   247,    34,     0,    35,    36,    37,    38,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,     0,     0,
       0,    30,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,     0,     0,   127,   128,   129,   130,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,    33,
       0,     0,   266,    34,     0,    35,    36,    37,    38,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,     0,     0,     0,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,    33,     0,
       0,   269,    34,     0,    35,    36,    37,    38,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    32,    33,     0,     0,
     270,    34,     0,    35,    36,    37,    38,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,     0,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,    33,     0,     0,   276,
      34,     0,    35,    36,    37,    38,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,     0,     0,     0,    30,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,    33,     0,     0,   295,    34,
       0,    35,    36,    37,    38,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,     0,     0,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    33,     0,     0,   297,    34,     0,
      35,    36,    37,    38,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,     0,     0,     0,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    32,    33,     0,     0,   329,    34,     0,    35,
      36,    37,    38,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    32,    33,     0,     0,   336,    34,     0,    35,    36,
      37,    38,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
       0,     0,     0,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      32,    33,     0,     0,   345,    34,     0,    35,    36,    37,
      38,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,     0,
       0,     0,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      33,     0,     0,   346,    34,     0,    35,    36,    37,    38,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,     0,     0,
       0,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,    33,
       0,     0,   351,    34,     0,    35,    36,    37,    38,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,     0,     0,     0,
      30,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,    33,     0,
       0,   352,    34,     0,    35,    36,    37,    38,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     1,     2,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,     0,     0,     0,    30,
       0,     0,     0,     0,    20,    21,    22,     0,     0,     0,
       0,    24,     0,     0,     0,     0,     0,    31,     0,     0,
      29,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    32,    33,     0,     0,
       0,    34,    31,    35,    36,    37,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,    34,     0,    82,    36,
      37,    38,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,     0,     0,   259,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   145,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,     0,     0,     0,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,     0,     0,     0,   162,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   267,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,     0,     0,     0,   347,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   205,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     301,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     268,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     330,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,   228,   102,     5,   161,    27,    41,
      29,    42,     5,    19,    28,    42,    69,    40,    48,    48,
      69,    73,    73,    84,    30,    31,    69,    33,    34,    68,
      69,    30,    73,    84,    48,    87,   171,    30,    91,    88,
     175,    71,    71,    82,   141,    88,    87,    86,    84,    73,
      71,    73,    84,    74,    85,   279,    73,    88,    89,    83,
      91,    88,    89,    85,    91,    84,    88,    74,    85,    75,
      76,    88,    73,    73,    86,    73,    88,    84,    88,    88,
     234,    73,    73,    73,    85,    85,    85,    85,   312,    85,
      73,    83,    83,    83,   100,    82,     5,     6,     7,    88,
      83,    88,    98,    84,    88,    84,    88,     0,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   150,   263,   135,
     136,    88,    88,    88,    88,    88,   142,    88,   144,    88,
     146,   147,    88,   278,   167,   242,    82,    48,    88,   145,
      84,    84,   148,   149,    48,    49,    50,    51,    52,    53,
      84,   157,    88,    88,    84,    84,    88,   302,   174,    71,
      88,   177,   168,    88,    85,    73,    88,   173,    85,    69,
      36,    48,     3,     4,    48,    49,    50,    51,    52,    53,
     213,    88,    88,   216,   217,    82,    88,    48,   204,   205,
      88,    82,   225,    24,    25,    26,    77,    87,    48,    88,
      31,    88,    71,    71,    84,     5,    71,    48,    75,    40,
      86,    84,    10,    44,    73,   248,     3,     4,    88,   252,
      71,    84,   274,   172,    88,   317,    88,   243,   244,    84,
      88,    62,    76,   277,   239,   303,    -1,    24,    25,    26,
     256,   257,   256,    -1,    31,    -1,    -1,    -1,    -1,   265,
      -1,    82,   268,    40,    -1,    86,    -1,    88,    89,    90,
      91,   267,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    -1,   288,    -1,    -1,   308,   292,    -1,    -1,    -1,
      -1,    -1,   298,    -1,    -1,   301,    -1,   320,    -1,    -1,
     296,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,
      -1,    88,    89,    90,    91,   338,   339,    -1,    -1,    -1,
     326,    -1,    -1,    -1,   330,    -1,   349,   350,    -1,   335,
      -1,   327,   328,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,   343,    -1,    -1,
      -1,   347,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    62,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      81,    82,    -1,    -1,    85,    86,    -1,    88,    89,    90,
      91,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      62,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    81,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    90,    91,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    44,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    -1,    -1,    56,    57,    58,    59,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    90,    91,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    90,    91,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      85,    86,    -1,    88,    89,    90,    91,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    85,
      86,    -1,    88,    89,    90,    91,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    85,    86,
      -1,    88,    89,    90,    91,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    85,    86,    -1,
      88,    89,    90,    91,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    85,    86,    -1,    88,
      89,    90,    91,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    85,    86,    -1,    88,    89,
      90,    91,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    85,    86,    -1,    88,    89,    90,
      91,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    85,    86,    -1,    88,    89,    90,    91,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    85,    86,    -1,    88,    89,    90,    91,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    85,    86,    -1,    88,    89,    90,    91,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,     3,     4,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,
      40,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      -1,    86,    62,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    86,    -1,    88,    89,
      90,    91,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    40,
      44,    62,    81,    82,    86,    88,    89,    90,    91,    93,
      94,    95,    96,    97,    98,    99,   100,   104,   105,   106,
     110,   113,   115,   116,   117,   118,   119,   120,   121,   122,
     126,   129,   131,   132,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   144,   146,    84,    84,    88,    88,    88,
     135,   135,    88,   135,   135,    84,    69,    88,    88,    88,
      88,    88,    88,   135,     5,     6,     7,    88,    84,    88,
      88,    88,    82,    88,   107,   108,   135,   135,    88,   135,
     135,   145,     0,    97,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    68,    69,    82,    86,   111,   112,   135,
     111,    82,    48,    71,    48,    84,    28,    48,    84,    84,
      94,    69,    88,    27,    29,    84,   101,    84,    41,    84,
      84,    84,    84,    88,    88,    88,    84,    94,    84,   135,
     107,    71,    73,    84,    48,    71,    83,    73,    87,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,    88,    88,
     135,   143,   135,    85,    73,    75,    85,   107,   135,    86,
      88,   109,   135,    94,   135,   135,    94,    94,    85,    69,
      88,    69,    91,    36,   102,    94,    88,    88,   127,   128,
      88,   130,    30,   106,   133,    42,    88,    89,    91,   123,
     124,   125,    82,    48,    48,    88,   147,    85,    94,    83,
     109,   108,    94,   135,   109,   135,    82,    73,    83,    87,
     135,   135,    83,    87,    77,    48,    85,    84,    72,    85,
      85,    88,    88,    71,    73,    85,    85,    84,    71,    73,
      85,   128,    73,    85,    85,   106,    85,   124,    75,   107,
     135,   135,    71,    73,    85,    85,    84,    85,    48,   143,
     135,    75,    71,    74,   114,   109,   135,    10,    94,   135,
      86,   102,   127,   109,   128,    88,   135,    83,   135,    88,
      94,   135,    83,   135,   109,   140,    74,    84,    84,    85,
      72,    88,   103,    85,   114,    71,    85,   135,    94,    94,
     135,    73,    87,    84,   135,    85,    85,    84,    88,    94,
      94,    85,    85
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    94,    94,    95,    96,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    98,
      99,    99,   100,   100,   100,   100,   100,   100,   100,   101,
     102,   102,   103,   103,   104,   105,   106,   106,   106,   107,
     107,   107,   108,   108,   109,   109,   109,   110,   110,   111,
     111,   112,   112,   113,   114,   114,   114,   115,   115,   115,
     115,   115,   116,   116,   117,   117,   118,   119,   119,   119,
     120,   121,   122,   123,   123,   124,   125,   125,   125,   125,
     126,   126,   127,   127,   127,   127,   128,   129,   130,   130,
     130,   131,   132,   133,   133,   133,   134,   134,   135,   135,
     135,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     137,   137,   138,   138,   139,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   141,   141,   142,   142,   143,   143,   143,   144,   145,
     145,   145,   146,   147,   147,   147
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       2,     3,     2,     3,     5,     4,     5,     4,     3,     3,
       5,     3,     1,     3,     2,     5,     9,    10,     8,     0,
       1,     3,     1,     3,     1,     2,     3,     4,     4,     0,
       1,     3,     5,     4,     0,     2,     2,     4,     6,     5,
       4,     6,     4,     5,     5,     9,     1,    11,     5,     7,
       5,     4,     5,     1,     2,     3,     1,     1,     1,     1,
       5,     7,     0,     1,     3,     2,     3,     5,     0,     1,
       3,     2,     5,     0,     1,     2,     2,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
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
#line 1 "parser.y"

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
  YYSYMBOL_TOKEN_IDENTIFIER = 91,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_NUMBER = 92,              /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_FLOAT = 93,               /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_STRING = 94,              /* TOKEN_STRING  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_await_expr = 96,                /* await_expr  */
  YYSYMBOL_spawn_expr = 97,                /* spawn_expr  */
  YYSYMBOL_program = 98,                   /* program  */
  YYSYMBOL_statement_list = 99,            /* statement_list  */
  YYSYMBOL_unsafe_stmt = 100,              /* unsafe_stmt  */
  YYSYMBOL_continue_statement = 101,       /* continue_statement  */
  YYSYMBOL_statement = 102,                /* statement  */
  YYSYMBOL_nnl_statement = 103,            /* nnl_statement  */
  YYSYMBOL_jmp_statement = 104,            /* jmp_statement  */
  YYSYMBOL_import_statement = 105,         /* import_statement  */
  YYSYMBOL_import_constraints = 106,       /* import_constraints  */
  YYSYMBOL_import_options = 107,           /* import_options  */
  YYSYMBOL_name_list = 108,                /* name_list  */
  YYSYMBOL_export_statement = 109,         /* export_statement  */
  YYSYMBOL_packet_decl = 110,              /* packet_decl  */
  YYSYMBOL_function_decl = 111,            /* function_decl  */
  YYSYMBOL_param_list = 112,               /* param_list  */
  YYSYMBOL_param = 113,                    /* param  */
  YYSYMBOL_type = 114,                     /* type  */
  YYSYMBOL_dict_expr = 115,                /* dict_expr  */
  YYSYMBOL_dict_entries = 116,             /* dict_entries  */
  YYSYMBOL_dict_entry_list = 117,          /* dict_entry_list  */
  YYSYMBOL_dict_access = 118,              /* dict_access  */
  YYSYMBOL_return_type = 119,              /* return_type  */
  YYSYMBOL_let_decl = 120,                 /* let_decl  */
  YYSYMBOL_const_decl = 121,               /* const_decl  */
  YYSYMBOL_if_statement = 122,             /* if_statement  */
  YYSYMBOL_break_statement = 123,          /* break_statement  */
  YYSYMBOL_for_statement = 124,            /* for_statement  */
  YYSYMBOL_while_statement = 125,          /* while_statement  */
  YYSYMBOL_loop_statement = 126,           /* loop_statement  */
  YYSYMBOL_match_statement = 127,          /* match_statement  */
  YYSYMBOL_match_cases = 128,              /* match_cases  */
  YYSYMBOL_match_case = 129,               /* match_case  */
  YYSYMBOL_pattern = 130,                  /* pattern  */
  YYSYMBOL_struct_decl = 131,              /* struct_decl  */
  YYSYMBOL_struct_fields = 132,            /* struct_fields  */
  YYSYMBOL_struct_field = 133,             /* struct_field  */
  YYSYMBOL_enum_decl = 134,                /* enum_decl  */
  YYSYMBOL_enum_variants = 135,            /* enum_variants  */
  YYSYMBOL_module_decl = 136,              /* module_decl  */
  YYSYMBOL_impl_decl = 137,                /* impl_decl  */
  YYSYMBOL_function_decl_list = 138,       /* function_decl_list  */
  YYSYMBOL_return_statement = 139,         /* return_statement  */
  YYSYMBOL_expression = 140,               /* expression  */
  YYSYMBOL_binary_expr = 141,              /* binary_expr  */
  YYSYMBOL_unary_expr = 142,               /* unary_expr  */
  YYSYMBOL_lambda_expr = 143,              /* lambda_expr  */
  YYSYMBOL_array_access = 144,             /* array_access  */
  YYSYMBOL_primary_expr = 145,             /* primary_expr  */
  YYSYMBOL_member_access = 146,            /* member_access  */
  YYSYMBOL_call_expr = 147,                /* call_expr  */
  YYSYMBOL_argument_list = 148,            /* argument_list  */
  YYSYMBOL_array_expr = 149,               /* array_expr  */
  YYSYMBOL_array_items = 150,              /* array_items  */
  YYSYMBOL_struct_expr = 151,              /* struct_expr  */
  YYSYMBOL_struct_init_fields = 152        /* struct_init_fields  */
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
#define YYFINAL  119
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2263

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  362

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   349


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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   103,   112,   115,   122,   127,   133,   137,   143,   148,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   181,   187,   190,   196,   199,   205,   211,   215,
     221,   224,   230,   236,   239,   245,   249,   256,   262,   268,
     271,   275,   284,   287,   291,   298,   301,   307,   310,   313,
     321,   324,   330,   333,   339,   344,   353,   372,   375,   378,
     385,   388,   391,   397,   400,   405,   408,   417,   420,   425,
     430,   436,   439,   455,   461,   468,   474,   478,   485,   491,
     494,   497,   500,   506,   509,   515,   518,   522,   526,   533,
     539,   545,   548,   552,   559,   566,   572,   575,   579,   586,
     589,   595,   596,   597,   601,   604,   607,   610,   613,   616,
     619,   622,   625,   628,   631,   634,   637,   640,   643,   646,
     649,   652,   655,   661,   664,   671,   674,   681,   687,   690,
     693,   696,   699,   702,   705,   708,   711,   712,   713,   714,
     715,   716,   717,   718,   719,   720,   724,   727,   733,   736,
     742,   745,   749,   756,   762,   765,   769,   776,   782,   785,
     789
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
  "TOKEN_IDENTIFIER", "TOKEN_NUMBER", "TOKEN_FLOAT", "TOKEN_STRING",
  "$accept", "await_expr", "spawn_expr", "program", "statement_list",
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
     345,   346,   347,   348,   349
};
#endif

#define YYPACT_NINF (-230)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1716,   -63,   -54,   -51,   -38,   -20,  1741,  1741,  1771,  1741,
      -9,  -230,  -230,   -47,    18,    44,    49,    51,    53,  1741,
    -230,  -230,  -230,   106,    55,    63,    61,    62,    83,  1816,
    1842,    17,  1741,  1741,    84,  1741,  1741,  -230,  -230,  -230,
    -230,  -230,  -230,    82,  1716,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  2199,
    -230,  -230,  -230,  -230,   -33,  -230,  -230,  -230,  -230,  1741,
    1741,    92,   -31,   146,  2199,   165,    -5,  1891,  1910,  1716,
     -40,   -15,  -230,   113,   -27,   116,   117,  1952,   118,   139,
     140,   121,  1716,   145,  1741,  -230,  1716,   -33,   -33,   144,
     162,    -7,  -230,   224,   188,   -29,  2032,  2199,   -42,  -230,
    -230,  1741,  1741,  1741,  1741,  1741,  1741,  1741,  1741,  1741,
    1741,  1741,  1741,  1741,  1741,  1741,  1741,  1741,  1741,  1741,
     156,   157,  1741,  1741,   149,   173,  2073,   163,   144,  1741,
      50,  1741,  1716,  1741,  1741,  1716,  1716,   336,   178,  -230,
     170,   -44,   226,  -230,  1716,   172,   176,   179,    11,   -26,
     184,   213,   231,   192,   428,  1716,  2199,   520,     3,    50,
     144,  1716,  1741,    50,  -230,  1741,  -230,   224,   224,   188,
     188,   188,   202,   202,   202,   202,   202,   202,   338,   338,
     430,   430,   430,   430,   261,   356,   199,  -230,  2199,    10,
     109,  -230,  1741,  1741,  -230,    14,   132,   196,   208,   238,
     132,   612,  1971,  2139,   704,   796,  -230,   201,  -230,   205,
    -230,   216,   -39,   888,   206,   223,   -34,  -230,  -230,    -1,
     293,  -230,     6,  -230,  -230,  -230,  -230,   -30,  -230,   221,
     144,  1741,  1741,   228,     0,  -230,   980,  -230,   218,  -230,
    -230,  1072,   132,   249,  2199,  1741,  1741,  -230,  -230,  2106,
    2199,    29,    50,  -230,  1741,   316,  1716,  1741,  -230,  -230,
    -230,  -230,   214,   226,  -230,  -230,   176,    50,   176,  -230,
    -230,   236,  -230,  -230,  -230,  -230,  -230,  1741,    15,   132,
     132,  1741,   237,  -230,  -230,  1716,  -230,  1741,    19,  2199,
    1741,    50,  1842,    20,  -230,   132,   243,  1164,  2169,   240,
     256,   -21,  -230,  -230,  -230,  2199,    29,  2199,   260,  1256,
     132,  -230,  2199,  -230,   -33,  1741,  1716,  1716,  -230,  1741,
    -230,   -13,  -230,   250,  1741,  -230,  2199,  1348,  1440,  2013,
     255,  -230,  1716,  2199,  -230,  -230,  1716,  -230,  1532,  1624,
    -230,  -230
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,   110,     0,     0,     0,
       0,    79,     9,     0,     0,     0,     0,     0,     0,     0,
     141,   142,   143,     0,     0,     0,     0,     0,     0,     0,
       0,    52,     0,     0,     0,     0,   164,   144,   138,   139,
     140,   154,   155,     0,     5,    26,    12,     6,    13,    14,
      10,    11,    16,    17,   148,   147,    21,    23,    24,    22,
      25,    27,    28,    29,    18,    19,    15,    20,    30,    31,
     111,   112,   152,   153,   113,   151,   146,   149,   150,    62,
      62,     0,     0,     0,   109,     0,   144,     0,     0,     0,
       0,    35,    47,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,   104,     0,     2,     4,    52,
      55,     0,    53,   134,   133,     0,     0,   165,     0,     1,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   160,     0,     0,    63,     0,     0,    52,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,    41,     0,     0,    95,   101,   106,     0,
       0,     0,     0,   168,     0,     0,    34,     0,     0,     0,
       0,     0,     0,     0,   145,     0,   163,   114,   115,   116,
     117,   118,   127,   128,   129,   130,   131,   132,   119,   120,
     121,   122,   123,   124,   125,   126,   157,   156,   161,     0,
       0,    60,     0,     0,    61,     0,    70,     0,    57,     0,
      75,     0,     0,     0,     0,     0,    84,     0,    40,     0,
      38,     0,     0,     0,     0,     0,     0,    96,   102,     0,
       0,   107,     0,    92,    91,    89,    90,     0,    86,     0,
      52,     0,     0,     0,     0,     8,     0,     3,     0,    56,
      54,     0,    73,     0,   166,   160,     0,   158,    66,     0,
      64,    67,     0,    58,     0,    77,     0,     0,    81,    83,
      37,    39,     0,     0,    42,    48,    95,     0,     0,    93,
      98,     0,   100,   105,   108,    85,    87,     0,     0,    72,
      76,     0,     0,   167,    32,     0,   135,     0,     0,   162,
       0,     0,     0,     0,    59,    71,     0,     0,     0,     0,
      44,     0,    99,    97,   103,    88,    67,   169,     0,     0,
      74,   159,    65,    68,    69,     0,     0,     0,    82,     0,
      45,     0,    94,     0,     0,   136,    51,     0,     0,     0,
       0,    43,     0,   170,    49,    78,     0,    46,     0,     0,
      50,    80
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -230,  -230,  -230,  -230,   -71,  -230,  -230,   -23,  -230,  -230,
    -230,  -230,    76,  -230,  -230,  -230,  -159,  -101,   183,  -173,
    -230,   284,  -230,  -230,    39,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,   125,  -230,  -230,    87,  -229,  -230,
    -230,  -230,  -230,  -230,  -230,    -6,  -230,  -230,  -230,  -230,
     -25,  -230,  -230,   110,  -230,  -230,  -230,  -230
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,   163,   232,   341,    51,    52,    53,   111,   112,   219,
      54,   144,   145,    55,   313,    56,    57,    58,    59,    60,
      61,    62,    63,   247,   248,   249,    64,   236,   237,    65,
     239,    66,    67,   242,    68,    69,    70,    71,    72,    73,
      74,    75,    76,   209,    77,   118,    78,   254
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    85,    87,    88,   107,   108,   259,   290,   178,   241,
     263,     3,   160,    97,   161,   243,     3,   165,   157,   243,
     149,   120,   182,   153,    79,    90,   113,   114,   229,   116,
     117,   174,   158,    80,   185,   177,   240,   283,   140,   141,
      81,   240,   288,   150,    91,   183,   154,   215,   186,   284,
     230,   159,   142,    82,   289,   288,   143,   235,   295,   323,
     166,   244,   245,   350,   246,   244,   245,   342,   246,   180,
     235,    83,   162,   146,   146,   291,   302,   351,    89,   180,
     181,   221,   119,   294,   224,   225,   266,   292,   303,   258,
     180,   180,   290,   233,   293,   266,   267,   335,   176,   314,
     271,   326,   109,   311,   256,   331,   312,   336,   110,    92,
     261,    98,    99,   100,   322,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   120,    93,   208,   210,   333,   217,
      94,   218,    95,   216,    96,   220,   101,   222,   223,   298,
     102,   120,   103,   104,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   105,   115,   262,   148,   121,   264,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   151,   120,   268,
     164,   120,   120,   167,   168,   317,   269,   270,   173,   170,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     171,   172,   175,   120,   329,   110,   179,   211,   120,   126,
     127,   128,   129,   130,   131,   299,   300,   206,   207,   212,
     227,   214,   152,    -1,    -1,    -1,    -1,    -1,    -1,   208,
     309,   228,   231,   234,   251,   347,   348,   235,   315,   250,
     238,   318,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   358,   252,   253,   265,   359,   272,   334,   273,   274,
     282,   325,   280,   286,   120,   327,   281,   287,    98,   297,
     307,   330,   301,   319,   332,   305,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   120,   120,   316,   324,   328,   346,
     337,   340,   283,   349,   344,   120,   120,   352,   353,     1,
       2,     3,     4,     5,     6,     7,   357,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,   320,
      20,    21,    22,   260,   147,   343,    23,    24,    25,    26,
      27,    28,   296,   321,     0,   308,     0,    29,    30,    31,
       0,     0,     0,    32,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,     0,     0,   134,   135,   136,
     137,    33,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
      34,    35,     0,     0,   226,    36,     0,    37,    38,    39,
      40,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,    29,
      30,    31,     0,     0,     0,    32,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,     0,     0,   255,    36,     0,    37,
      38,    39,    40,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,    29,    30,    31,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,     0,     0,   257,    36,
       0,    37,    38,    39,    40,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,    29,    30,    31,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,     0,     0,
     275,    36,     0,    37,    38,    39,    40,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,     0,    29,    30,    31,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
       0,     0,   278,    36,     0,    37,    38,    39,    40,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,    29,    30,    31,
       0,     0,     0,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,     0,     0,   279,    36,     0,    37,    38,    39,
      40,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,    29,
      30,    31,     0,     0,     0,    32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,     0,     0,   285,    36,     0,    37,
      38,    39,    40,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,    29,    30,    31,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,     0,     0,   304,    36,
       0,    37,    38,    39,    40,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,    29,    30,    31,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,     0,     0,
     306,    36,     0,    37,    38,    39,    40,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,     0,    29,    30,    31,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
       0,     0,   338,    36,     0,    37,    38,    39,    40,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,    29,    30,    31,
       0,     0,     0,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    35,     0,     0,   345,    36,     0,    37,    38,    39,
      40,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,    29,
      30,    31,     0,     0,     0,    32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,     0,     0,   354,    36,     0,    37,
      38,    39,    40,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,    29,    30,    31,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    35,     0,     0,   355,    36,
       0,    37,    38,    39,    40,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,    29,    30,    31,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,     0,     0,
     360,    36,     0,    37,    38,    39,    40,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,     0,    29,    30,    31,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
       0,     0,   361,    36,     0,    37,    38,    39,    40,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     1,     2,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,    29,    30,    31,
       0,     0,     0,    32,     0,    20,    21,    22,     0,     0,
       0,     0,    24,     0,     1,     2,     0,     0,     0,     0,
       0,    33,    29,    30,    31,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,    20,    21,    22,     0,     0,
      34,    35,    24,     0,     0,    36,    33,    37,    38,    39,
      40,     0,    29,    30,    31,     0,     0,     0,    32,     1,
       2,     0,     0,     0,     0,     0,    35,     0,     0,     0,
      36,     0,    37,    38,    39,    40,    33,     0,     0,     0,
      20,    21,    22,     0,     0,     1,     2,    24,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    29,    30,    31,
      36,     0,    86,    38,    39,    40,    20,    21,    22,     0,
       0,     0,     0,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,   106,     0,    36,     0,    37,    38,    39,
      40,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,     0,     0,
       0,    36,     0,    37,    38,    39,    40,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,     0,     0,     0,   155,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   156,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,     0,     0,     0,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   276,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,     0,     0,     0,
     356,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   184,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   213,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   310,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   277,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   339,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,    29,    30,   179,   236,   109,   168,
     183,     5,    27,    19,    29,    45,     5,    44,    89,    45,
      51,    44,    51,    28,    87,    72,    32,    33,    72,    35,
      36,   102,    72,    87,    76,   106,    30,    76,    71,    72,
      91,    30,    76,    74,    91,    74,    51,   148,    90,    88,
      94,    91,    85,    91,    88,    76,    89,    91,    88,   288,
      87,    91,    92,    76,    94,    91,    92,    88,    94,    76,
      91,    91,    87,    79,    80,    76,    76,    90,    87,    76,
      87,   152,     0,   242,   155,   156,    76,    88,    88,    86,
      76,    76,   321,   164,    88,    76,    86,    77,   104,   272,
      86,    86,    85,    74,   175,    86,    77,    87,    91,    91,
     181,     5,     6,     7,   287,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   157,    91,   142,   143,   311,    89,
      91,    91,    91,   149,    91,   151,    91,   153,   154,   250,
      87,   174,    91,    91,   177,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    91,    91,   182,    85,    46,   185,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    51,   221,    90,
      87,   224,   225,    87,    87,   276,   212,   213,    87,    91,
     233,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      91,    91,    87,   256,   305,    91,    74,    88,   261,    51,
      52,    53,    54,    55,    56,   251,   252,    91,    91,    76,
      72,    88,    87,    51,    52,    53,    54,    55,    56,   265,
     266,    91,    36,    91,    51,   336,   337,    91,   274,    85,
      91,   277,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   352,    51,    91,    85,   356,    90,   312,    80,    51,
      74,   297,    91,    87,   317,   301,    91,    74,     5,    78,
      51,   307,    74,    89,   310,    87,   329,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,   347,   348,    10,    91,    91,   335,
      87,    91,    76,   339,    74,   358,   359,    87,   344,     3,
       4,     5,     6,     7,     8,     9,    91,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,   283,
      24,    25,    26,   180,    80,   326,    30,    31,    32,    33,
      34,    35,   247,   286,    -1,   265,    -1,    41,    42,    43,
      -1,    -1,    -1,    47,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    59,    60,    61,
      62,    65,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      84,    85,    -1,    -1,    88,    89,    -1,    91,    92,    93,
      94,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    -1,    -1,    -1,    47,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    88,    89,    -1,    91,
      92,    93,    94,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    88,    89,
      -1,    91,    92,    93,    94,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      88,    89,    -1,    91,    92,    93,    94,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    88,    89,    -1,    91,    92,    93,    94,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    88,    89,    -1,    91,    92,    93,
      94,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    88,    89,    -1,    91,
      92,    93,    94,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    88,    89,
      -1,    91,    92,    93,    94,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      88,    89,    -1,    91,    92,    93,    94,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    88,    89,    -1,    91,    92,    93,    94,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    88,    89,    -1,    91,    92,    93,
      94,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    88,    89,    -1,    91,
      92,    93,    94,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    88,    89,
      -1,    91,    92,    93,    94,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      88,    89,    -1,    91,    92,    93,    94,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    88,    89,    -1,    91,    92,    93,    94,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,     3,     4,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    -1,    -1,    47,    -1,    24,    25,    26,    -1,    -1,
      -1,    -1,    31,    -1,     3,     4,    -1,    -1,    -1,    -1,
      -1,    65,    41,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    -1,    -1,
      84,    85,    31,    -1,    -1,    89,    65,    91,    92,    93,
      94,    -1,    41,    42,    43,    -1,    -1,    -1,    47,     3,
       4,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,    -1,
      89,    -1,    91,    92,    93,    94,    65,    -1,    -1,    -1,
      24,    25,    26,    -1,    -1,     3,     4,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    41,    42,    43,
      89,    -1,    91,    92,    93,    94,    24,    25,    26,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    -1,    87,    -1,    89,    -1,    91,    92,    93,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    89,    -1,    91,    92,    93,    94,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    87,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    41,
      42,    43,    47,    65,    84,    85,    89,    91,    92,    93,
      94,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   109,   110,   111,   115,   118,   120,   121,   122,   123,
     124,   125,   126,   127,   131,   134,   136,   137,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   149,   151,    87,
      87,    91,    91,    91,   140,   140,    91,   140,   140,    87,
      72,    91,    91,    91,    91,    91,    91,   140,     5,     6,
       7,    91,    87,    91,    91,    91,    87,   145,   145,    85,
      91,   112,   113,   140,   140,    91,   140,   140,   150,     0,
     102,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      71,    72,    85,    89,   116,   117,   140,   116,    85,    51,
      74,    51,    87,    28,    51,    87,    87,    99,    72,    91,
      27,    29,    87,   106,    87,    44,    87,    87,    87,    87,
      91,    91,    91,    87,    99,    87,   140,    99,   112,    74,
      76,    87,    51,    74,    86,    76,    90,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,    91,    91,   140,   148,
     140,    88,    76,    78,    88,   112,   140,    89,    91,   114,
     140,    99,   140,   140,    99,    99,    88,    72,    91,    72,
      94,    36,   107,    99,    91,    91,   132,   133,    91,   135,
      30,   111,   138,    45,    91,    92,    94,   128,   129,   130,
      85,    51,    51,    91,   152,    88,    99,    88,    86,   114,
     113,    99,   140,   114,   140,    85,    76,    86,    90,   140,
     140,    86,    90,    80,    51,    88,    87,    75,    88,    88,
      91,    91,    74,    76,    88,    88,    87,    74,    76,    88,
     133,    76,    88,    88,   111,    88,   129,    78,   112,   140,
     140,    74,    76,    88,    88,    87,    88,    51,   148,   140,
      78,    74,    77,   119,   114,   140,    10,    99,   140,    89,
     107,   132,   114,   133,    91,   140,    86,   140,    91,    99,
     140,    86,   140,   114,   145,    77,    87,    87,    88,    75,
      91,   108,    88,   119,    74,    88,   140,    99,    99,   140,
      76,    90,    87,   140,    88,    88,    87,    91,    99,    99,
      88,    88
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    97,    98,    99,    99,   100,   101,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   104,   104,   105,   105,   105,   105,   105,
     105,   105,   106,   107,   107,   108,   108,   109,   110,   111,
     111,   111,   112,   112,   112,   113,   113,   114,   114,   114,
     115,   115,   116,   116,   117,   117,   118,   119,   119,   119,
     120,   120,   120,   120,   120,   121,   121,   122,   122,   123,
     124,   124,   124,   125,   126,   127,   128,   128,   129,   130,
     130,   130,   130,   131,   131,   132,   132,   132,   132,   133,
     134,   135,   135,   135,   136,   137,   138,   138,   138,   139,
     139,   140,   140,   140,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   142,   142,   143,   143,   144,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   146,   146,   147,   147,
     148,   148,   148,   149,   150,   150,   150,   151,   152,   152,
     152
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     2,     1,     1,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     2,     3,     2,     3,     5,     4,     5,
       4,     3,     3,     5,     3,     1,     3,     2,     5,     9,
      10,     8,     0,     1,     3,     1,     3,     1,     2,     3,
       4,     4,     0,     1,     3,     5,     4,     0,     2,     2,
       4,     6,     5,     4,     6,     4,     5,     5,     9,     1,
      11,     5,     7,     5,     4,     5,     1,     2,     3,     1,
       1,     1,     1,     5,     7,     0,     1,     3,     2,     3,
       5,     0,     1,     3,     2,     5,     0,     1,     2,     2,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     5,     7,     4,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     4,     6,
       0,     1,     3,     3,     0,     1,     3,     5,     0,     3,
       5
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
  case 2: /* await_expr: TOKEN_AWAIT primary_expr  */
#line 112 "parser.y"
                             {
        (yyval.node) = create_await_node((yyvsp[0].node));
    }
#line 1893 "parser.c"
    break;

  case 3: /* await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 115 "parser.y"
                                                           {
        (yyval.node) = create_await_block_node((yyvsp[-1].node_list));
    }
#line 1901 "parser.c"
    break;

  case 4: /* spawn_expr: TOKEN_SPAWN primary_expr  */
#line 122 "parser.y"
                             {
        (yyval.node) = create_spawn_node((yyvsp[0].node));
    }
#line 1909 "parser.c"
    break;

  case 5: /* program: statement_list  */
#line 127 "parser.y"
                   {
        program_root = create_program_node((yyvsp[0].node_list));
    }
#line 1917 "parser.c"
    break;

  case 6: /* statement_list: statement  */
#line 133 "parser.y"
              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 1926 "parser.c"
    break;

  case 7: /* statement_list: statement_list statement  */
#line 137 "parser.y"
                               {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 1935 "parser.c"
    break;

  case 8: /* unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 143 "parser.y"
                                                          {
        (yyval.node) = create_unsafe_node((yyvsp[-1].node_list));
    }
#line 1943 "parser.c"
    break;

  case 9: /* continue_statement: TOKEN_CONTINUE  */
#line 148 "parser.y"
                   {
        (yyval.node) = create_continue_node();
    }
#line 1951 "parser.c"
    break;

  case 31: /* statement: expression  */
#line 176 "parser.y"
                 {
        (yyval.node) = create_expr_statement((yyvsp[0].node));
    }
#line 1959 "parser.c"
    break;

  case 32: /* nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 181 "parser.y"
                                                                        {
        (yyval.node) = create_nnl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 1967 "parser.c"
    break;

  case 33: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER  */
#line 187 "parser.y"
                               {
        (yyval.node) = create_jmp_node((yyvsp[0].string), NULL);
    }
#line 1975 "parser.c"
    break;

  case 34: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression  */
#line 190 "parser.y"
                                            {
        (yyval.node) = create_jmp_node((yyvsp[-1].string), (yyvsp[0].node));
    }
#line 1983 "parser.c"
    break;

  case 35: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER  */
#line 196 "parser.y"
                                  {
        (yyval.node) = create_import_node((yyvsp[0].string), NULL, NULL);
    }
#line 1991 "parser.c"
    break;

  case 36: /* import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_IDENTIFIER  */
#line 199 "parser.y"
                                              {
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "./%s", (yyvsp[0].string));
        (yyval.node) = create_import_node(path, NULL, NULL);
        free(path);
    }
#line 2002 "parser.c"
    break;

  case 37: /* import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_DOT TOKEN_DOT TOKEN_IDENTIFIER  */
#line 205 "parser.y"
                                                                  {
        char* path = malloc(strlen((yyvsp[0].string)) + 4);
        sprintf(path, "../%s", (yyvsp[0].string));
        (yyval.node) = create_import_node(path, NULL, NULL);
        free(path);
    }
#line 2013 "parser.c"
    break;

  case 38: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_STRING  */
#line 211 "parser.y"
                                                            {
        (yyval.node) = create_import_node((yyvsp[0].string), (yyvsp[-2].string), NULL);
    }
#line 2021 "parser.c"
    break;

  case 39: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_DOT TOKEN_IDENTIFIER  */
#line 215 "parser.y"
                                                                          {
        char* path = malloc(strlen((yyvsp[0].string)) + 3);
        sprintf(path, "./%s", (yyvsp[0].string));
        (yyval.node) = create_import_node(path, (yyvsp[-3].string), NULL);
        free(path);
    }
#line 2032 "parser.c"
    break;

  case 40: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_AS TOKEN_IDENTIFIER  */
#line 221 "parser.y"
                                                              {
        (yyval.node) = create_import_node((yyvsp[-2].string), (yyvsp[0].string), NULL);
    }
#line 2040 "parser.c"
    break;

  case 41: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER import_constraints  */
#line 224 "parser.y"
                                                       {
        (yyval.node) = create_import_node((yyvsp[-1].string), NULL, (yyvsp[0].node));
    }
#line 2048 "parser.c"
    break;

  case 42: /* import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE  */
#line 230 "parser.y"
                                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2056 "parser.c"
    break;

  case 43: /* import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET  */
#line 236 "parser.y"
                                                                   {
        (yyval.node) = create_constraints_node("only", (yyvsp[-1].node_list));
    }
#line 2064 "parser.c"
    break;

  case 44: /* import_options: import_options TOKEN_COMMA import_options  */
#line 239 "parser.y"
                                                {
        (yyval.node) = merge_constraints((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2072 "parser.c"
    break;

  case 45: /* name_list: TOKEN_IDENTIFIER  */
#line 245 "parser.y"
                     {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2081 "parser.c"
    break;

  case 46: /* name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 249 "parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2090 "parser.c"
    break;

  case 47: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
#line 256 "parser.y"
                                  {
        (yyval.node) = create_export_node((yyvsp[0].string));
    }
#line 2098 "parser.c"
    break;

  case 48: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 262 "parser.y"
                                                                           {
        (yyval.node) = create_packet_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2106 "parser.c"
    break;

  case 49: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 268 "parser.y"
                                                                                                                        {
        (yyval.node) = create_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2114 "parser.c"
    break;

  case 50: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 271 "parser.y"
                                                                                                                                    {
        (yyval.node) = create_public_function_node((yyvsp[-7].string), (yyvsp[-5].node_list), (yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2122 "parser.c"
    break;

  case 51: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression  */
#line 275 "parser.y"
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node((yyvsp[0].node));
        add_to_node_list(body, return_stmt);
        (yyval.node) = create_function_node((yyvsp[-6].string), (yyvsp[-4].node_list), (yyvsp[-2].node), body);
    }
#line 2133 "parser.c"
    break;

  case 52: /* param_list: %empty  */
#line 284 "parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2141 "parser.c"
    break;

  case 53: /* param_list: param  */
#line 287 "parser.y"
            {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2150 "parser.c"
    break;

  case 54: /* param_list: param_list TOKEN_COMMA param  */
#line 291 "parser.y"
                                   {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2159 "parser.c"
    break;

  case 55: /* param: TOKEN_IDENTIFIER  */
#line 298 "parser.y"
                     {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 2167 "parser.c"
    break;

  case 56: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 301 "parser.y"
                                        {
        (yyval.node) = create_param_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2175 "parser.c"
    break;

  case 57: /* type: TOKEN_IDENTIFIER  */
#line 307 "parser.y"
                     {
        (yyval.node) = create_type_node((yyvsp[0].string));
    }
#line 2183 "parser.c"
    break;

  case 58: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
#line 310 "parser.y"
                                      {
        (yyval.node) = create_optional_type_node((yyvsp[-1].string));
    }
#line 2191 "parser.c"
    break;

  case 59: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 313 "parser.y"
                                         {
        (yyval.node) = create_array_type_node((yyvsp[0].node));
    }
#line 2199 "parser.c"
    break;

  case 60: /* dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 321 "parser.y"
                                                      {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2207 "parser.c"
    break;

  case 61: /* dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
#line 324 "parser.y"
                                                       {
        (yyval.node) = create_dict_node((yyvsp[-1].node_list));
    }
#line 2215 "parser.c"
    break;

  case 62: /* dict_entries: %empty  */
#line 330 "parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2223 "parser.c"
    break;

  case 63: /* dict_entries: dict_entry_list  */
#line 333 "parser.y"
                      {
        (yyval.node_list) = (yyvsp[0].node_list);
    }
#line 2231 "parser.c"
    break;

  case 64: /* dict_entry_list: expression TOKEN_FAT_ARROW expression  */
#line 339 "parser.y"
                                          {
        (yyval.node_list) = create_node_list();
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyval.node_list), pair);
    }
#line 2241 "parser.c"
    break;

  case 65: /* dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression  */
#line 344 "parser.y"
                                                                        {
        ASTNode* pair = create_binary_op((yyvsp[-2].node), OP_ASSIGN, (yyvsp[0].node));
        add_to_node_list((yyvsp[-4].node_list), pair);
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 2251 "parser.c"
    break;

  case 66: /* dict_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 353 "parser.y"
                                                          {
        // Détecter si c'est un accès dictionnaire ou tableau
        // Par défaut, c'est un accès tableau, mais on peut différencier par le type
        // Pour l'instant, on crée un nœud d'accès dictionnaire
        (yyval.node) = create_dict_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2262 "parser.c"
    break;

  case 67: /* return_type: %empty  */
#line 372 "parser.y"
                {
        (yyval.node) = NULL;
    }
#line 2270 "parser.c"
    break;

  case 68: /* return_type: TOKEN_COLON type  */
#line 375 "parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2278 "parser.c"
    break;

  case 69: /* return_type: TOKEN_ARROW primary_expr  */
#line 378 "parser.y"
                               {
        // Pour les retours directs: -> expr
        (yyval.node) = create_return_direct_node((yyvsp[0].node));
    }
#line 2287 "parser.c"
    break;

  case 70: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 385 "parser.y"
                                                       {
        (yyval.node) = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2295 "parser.c"
    break;

  case 71: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 388 "parser.y"
                                                                          {
        (yyval.node) = create_let_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2303 "parser.c"
    break;

  case 72: /* let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 391 "parser.y"
                                                                   {
        ASTNode* node = create_let_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2313 "parser.c"
    break;

  case 73: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 397 "parser.y"
                                                          {
        (yyval.node) = create_muts_node((yyvsp[-2].string), NULL, (yyvsp[0].node));
    }
#line 2321 "parser.c"
    break;

  case 74: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
#line 400 "parser.y"
                                                                           {
        (yyval.node) = create_muts_node((yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2329 "parser.c"
    break;

  case 75: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 405 "parser.y"
                                                         {
        (yyval.node) = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2337 "parser.c"
    break;

  case 76: /* const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
#line 408 "parser.y"
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node((yyvsp[-2].string), (yyvsp[0].node));
        node->var_decl.is_public = 1;
        (yyval.node) = node;
    }
#line 2348 "parser.c"
    break;

  case 77: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 417 "parser.y"
                                                                 {
        (yyval.node) = create_if_node((yyvsp[-3].node), (yyvsp[-1].node_list), NULL);
    }
#line 2356 "parser.c"
    break;

  case 78: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 420 "parser.y"
                                                                                                                       {
        (yyval.node) = create_if_node((yyvsp[-7].node), (yyvsp[-5].node_list), (yyvsp[-1].node_list));
    }
#line 2364 "parser.c"
    break;

  case 79: /* break_statement: TOKEN_BREAK  */
#line 425 "parser.y"
                {
        (yyval.node) = create_break_node();
    }
#line 2372 "parser.c"
    break;

  case 80: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 430 "parser.y"
                                                                                                                                                      {
        ASTNode* init = create_let_node((yyvsp[-9].string), NULL, (yyvsp[-7].node));
        ASTNode* cond = (yyvsp[-5].node);
        ASTNode* inc = create_expr_statement((yyvsp[-3].node));
        (yyval.node) = create_for_node(init, cond, inc, (yyvsp[-1].node_list));
    }
#line 2383 "parser.c"
    break;

  case 81: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 436 "parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2391 "parser.c"
    break;

  case 82: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 439 "parser.y"
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
#line 2409 "parser.c"
    break;

  case 83: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 455 "parser.y"
                                                                    {
        (yyval.node) = create_while_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2417 "parser.c"
    break;

  case 84: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 461 "parser.y"
                                                        {
        (yyval.node) = create_loop_node((yyvsp[-1].node_list));
    }
#line 2425 "parser.c"
    break;

  case 85: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
#line 468 "parser.y"
                                                                 {
        (yyval.node) = create_match_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2433 "parser.c"
    break;

  case 86: /* match_cases: match_case  */
#line 474 "parser.y"
               {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2442 "parser.c"
    break;

  case 87: /* match_cases: match_cases match_case  */
#line 478 "parser.y"
                             {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2451 "parser.c"
    break;

  case 88: /* match_case: pattern TOKEN_FAT_ARROW expression  */
#line 485 "parser.y"
                                       {
        (yyval.node) = create_match_case_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2459 "parser.c"
    break;

  case 89: /* pattern: TOKEN_NUMBER  */
#line 491 "parser.y"
                 {
        (yyval.node) = create_pattern_number((yyvsp[0].number));
    }
#line 2467 "parser.c"
    break;

  case 90: /* pattern: TOKEN_STRING  */
#line 494 "parser.y"
                   {
        (yyval.node) = create_pattern_string((yyvsp[0].string));
    }
#line 2475 "parser.c"
    break;

  case 91: /* pattern: TOKEN_IDENTIFIER  */
#line 497 "parser.y"
                       {
        (yyval.node) = create_pattern_ident((yyvsp[0].string));
    }
#line 2483 "parser.c"
    break;

  case 92: /* pattern: TOKEN_UNDERSCORE  */
#line 500 "parser.y"
                       {
        (yyval.node) = create_pattern_wildcard();
    }
#line 2491 "parser.c"
    break;

  case 93: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 506 "parser.y"
                                                                          {
        (yyval.node) = create_struct_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2499 "parser.c"
    break;

  case 94: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
#line 509 "parser.y"
                                                                                                           {
        (yyval.node) = create_struct_extend_node((yyvsp[-5].string), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2507 "parser.c"
    break;

  case 95: /* struct_fields: %empty  */
#line 515 "parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2515 "parser.c"
    break;

  case 96: /* struct_fields: struct_field  */
#line 518 "parser.y"
                   {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2524 "parser.c"
    break;

  case 97: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
#line 522 "parser.y"
                                             {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2533 "parser.c"
    break;

  case 98: /* struct_fields: struct_fields struct_field  */
#line 526 "parser.y"
                                 {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2542 "parser.c"
    break;

  case 99: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 533 "parser.y"
                                      {
        (yyval.node) = create_field_node((yyvsp[-2].string), (yyvsp[0].node));
    }
#line 2550 "parser.c"
    break;

  case 100: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
#line 539 "parser.y"
                                                                        {
        (yyval.node) = create_enum_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2558 "parser.c"
    break;

  case 101: /* enum_variants: %empty  */
#line 545 "parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2566 "parser.c"
    break;

  case 102: /* enum_variants: TOKEN_IDENTIFIER  */
#line 548 "parser.y"
                       {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_identifier_node((yyvsp[0].string)));
    }
#line 2575 "parser.c"
    break;

  case 103: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 552 "parser.y"
                                                 {
        add_to_node_list((yyvsp[-2].node_list), create_identifier_node((yyvsp[0].string)));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2584 "parser.c"
    break;

  case 104: /* module_decl: TOKEN_MODULE TOKEN_IDENTIFIER  */
#line 559 "parser.y"
                                  {
        // Créer un nœud nil pour éviter l'erreur
        (yyval.node) = create_expr_statement(create_nil_node());
    }
#line 2593 "parser.c"
    break;

  case 105: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
#line 566 "parser.y"
                                                                             {
        (yyval.node) = create_impl_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2601 "parser.c"
    break;

  case 106: /* function_decl_list: %empty  */
#line 572 "parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2609 "parser.c"
    break;

  case 107: /* function_decl_list: function_decl  */
#line 575 "parser.y"
                    {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2618 "parser.c"
    break;

  case 108: /* function_decl_list: function_decl_list function_decl  */
#line 579 "parser.y"
                                       {
        add_to_node_list((yyvsp[-1].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-1].node_list);
    }
#line 2627 "parser.c"
    break;

  case 109: /* return_statement: TOKEN_RETURN expression  */
#line 586 "parser.y"
                            {
        (yyval.node) = create_return_node((yyvsp[0].node));
    }
#line 2635 "parser.c"
    break;

  case 110: /* return_statement: TOKEN_RETURN  */
#line 589 "parser.y"
                   {
        (yyval.node) = create_return_node(NULL);
    }
#line 2643 "parser.c"
    break;

  case 114: /* binary_expr: expression TOKEN_PLUS expression  */
#line 601 "parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_ADD, (yyvsp[0].node));
    }
#line 2651 "parser.c"
    break;

  case 115: /* binary_expr: expression TOKEN_MINUS expression  */
#line 604 "parser.y"
                                        {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_SUB, (yyvsp[0].node));
    }
#line 2659 "parser.c"
    break;

  case 116: /* binary_expr: expression TOKEN_MULTIPLY expression  */
#line 607 "parser.y"
                                           {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MUL, (yyvsp[0].node));
    }
#line 2667 "parser.c"
    break;

  case 117: /* binary_expr: expression TOKEN_DIVIDE expression  */
#line 610 "parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_DIV, (yyvsp[0].node));
    }
#line 2675 "parser.c"
    break;

  case 118: /* binary_expr: expression TOKEN_MODULO expression  */
#line 613 "parser.y"
                                         {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_MOD, (yyvsp[0].node));
    }
#line 2683 "parser.c"
    break;

  case 119: /* binary_expr: expression TOKEN_EQ expression  */
#line 616 "parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_EQ, (yyvsp[0].node));
    }
#line 2691 "parser.c"
    break;

  case 120: /* binary_expr: expression TOKEN_NEQ expression  */
#line 619 "parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_NEQ, (yyvsp[0].node));
    }
#line 2699 "parser.c"
    break;

  case 121: /* binary_expr: expression TOKEN_LT expression  */
#line 622 "parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LT, (yyvsp[0].node));
    }
#line 2707 "parser.c"
    break;

  case 122: /* binary_expr: expression TOKEN_LTE expression  */
#line 625 "parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_LTE, (yyvsp[0].node));
    }
#line 2715 "parser.c"
    break;

  case 123: /* binary_expr: expression TOKEN_GT expression  */
#line 628 "parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GT, (yyvsp[0].node));
    }
#line 2723 "parser.c"
    break;

  case 124: /* binary_expr: expression TOKEN_GTE expression  */
#line 631 "parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_GTE, (yyvsp[0].node));
    }
#line 2731 "parser.c"
    break;

  case 125: /* binary_expr: expression TOKEN_AND expression  */
#line 634 "parser.y"
                                      {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_AND, (yyvsp[0].node));
    }
#line 2739 "parser.c"
    break;

  case 126: /* binary_expr: expression TOKEN_OR expression  */
#line 637 "parser.y"
                                     {
        (yyval.node) = create_binary_op((yyvsp[-2].node), OP_OR, (yyvsp[0].node));
    }
#line 2747 "parser.c"
    break;

  case 127: /* binary_expr: expression TOKEN_ASSIGN expression  */
#line 640 "parser.y"
                                         {
        (yyval.node) = create_assign_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2755 "parser.c"
    break;

  case 128: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
#line 643 "parser.y"
                                              {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_ADD_ASSIGN, (yyvsp[0].node));
    }
#line 2763 "parser.c"
    break;

  case 129: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
#line 646 "parser.y"
                                               {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_SUB_ASSIGN, (yyvsp[0].node));
    }
#line 2771 "parser.c"
    break;

  case 130: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
#line 649 "parser.y"
                                                  {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MUL_ASSIGN, (yyvsp[0].node));
    }
#line 2779 "parser.c"
    break;

  case 131: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
#line 652 "parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_DIV_ASSIGN, (yyvsp[0].node));
    }
#line 2787 "parser.c"
    break;

  case 132: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
#line 655 "parser.y"
                                                {
        (yyval.node) = create_assign_op_node((yyvsp[-2].node), OP_MOD_ASSIGN, (yyvsp[0].node));
    }
#line 2795 "parser.c"
    break;

  case 133: /* unary_expr: TOKEN_NOT expression  */
#line 661 "parser.y"
                         {
        (yyval.node) = create_unary_op(OP_NOT, (yyvsp[0].node));
    }
#line 2803 "parser.c"
    break;

  case 134: /* unary_expr: TOKEN_MINUS expression  */
#line 664 "parser.y"
                             {
        (yyval.node) = create_unary_op(OP_NEG, (yyvsp[0].node));
    }
#line 2811 "parser.c"
    break;

  case 135: /* lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 671 "parser.y"
                                                                     {
        (yyval.node) = create_lambda_node((yyvsp[-3].node_list), (yyvsp[-1].node_list));
    }
#line 2819 "parser.c"
    break;

  case 136: /* lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
#line 674 "parser.y"
                                                                                                 {
        (yyval.node) = create_lambda_node((yyvsp[-4].node_list), (yyvsp[-1].node_list));
    }
#line 2827 "parser.c"
    break;

  case 137: /* array_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
#line 681 "parser.y"
                                                          {
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2835 "parser.c"
    break;

  case 138: /* primary_expr: TOKEN_NUMBER  */
#line 687 "parser.y"
                 {
        (yyval.node) = create_number_node((yyvsp[0].number));
    }
#line 2843 "parser.c"
    break;

  case 139: /* primary_expr: TOKEN_FLOAT  */
#line 690 "parser.y"
                  {
        (yyval.node) = create_float_node((yyvsp[0].float_val));
    }
#line 2851 "parser.c"
    break;

  case 140: /* primary_expr: TOKEN_STRING  */
#line 693 "parser.y"
                   {
        (yyval.node) = create_string_node((yyvsp[0].string));
    }
#line 2859 "parser.c"
    break;

  case 141: /* primary_expr: TOKEN_TRUE  */
#line 696 "parser.y"
                 {
        (yyval.node) = create_bool_node(1);
    }
#line 2867 "parser.c"
    break;

  case 142: /* primary_expr: TOKEN_FALSE  */
#line 699 "parser.y"
                  {
        (yyval.node) = create_bool_node(0);
    }
#line 2875 "parser.c"
    break;

  case 143: /* primary_expr: TOKEN_NIL  */
#line 702 "parser.y"
                {
        (yyval.node) = create_nil_node();
    }
#line 2883 "parser.c"
    break;

  case 144: /* primary_expr: TOKEN_IDENTIFIER  */
#line 705 "parser.y"
                       {
        (yyval.node) = create_identifier_node((yyvsp[0].string));
    }
#line 2891 "parser.c"
    break;

  case 145: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
#line 708 "parser.y"
                                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2899 "parser.c"
    break;

  case 156: /* member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER  */
#line 724 "parser.y"
                                            {
        (yyval.node) = create_member_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 2907 "parser.c"
    break;

  case 157: /* member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
#line 727 "parser.y"
                                                       {
        (yyval.node) = create_static_access((yyvsp[-2].node), (yyvsp[0].string));
    }
#line 2915 "parser.c"
    break;

  case 158: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 733 "parser.y"
                                                         {
        (yyval.node) = create_call_node((yyvsp[-3].node), (yyvsp[-1].node_list));
    }
#line 2923 "parser.c"
    break;

  case 159: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
#line 736 "parser.y"
                                                                                               {
        (yyval.node) = create_method_call_node((yyvsp[-5].node), (yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2931 "parser.c"
    break;

  case 160: /* argument_list: %empty  */
#line 742 "parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2939 "parser.c"
    break;

  case 161: /* argument_list: expression  */
#line 745 "parser.y"
                 {
        (yyval.node_list) = create_arg_list();
        add_arg((yyval.node_list), (yyvsp[0].node));
    }
#line 2948 "parser.c"
    break;

  case 162: /* argument_list: argument_list TOKEN_COMMA expression  */
#line 749 "parser.y"
                                           {
        add_arg((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2957 "parser.c"
    break;

  case 163: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
#line 756 "parser.y"
                                              {
        (yyval.node) = create_array_node((yyvsp[-1].node_list));
    }
#line 2965 "parser.c"
    break;

  case 164: /* array_items: %empty  */
#line 762 "parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 2973 "parser.c"
    break;

  case 165: /* array_items: expression  */
#line 765 "parser.y"
                 {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), (yyvsp[0].node));
    }
#line 2982 "parser.c"
    break;

  case 166: /* array_items: array_items TOKEN_COMMA expression  */
#line 769 "parser.y"
                                         {
        add_to_node_list((yyvsp[-2].node_list), (yyvsp[0].node));
        (yyval.node_list) = (yyvsp[-2].node_list);
    }
#line 2991 "parser.c"
    break;

  case 167: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
#line 776 "parser.y"
                                                                            {
        (yyval.node) = create_struct_init_node((yyvsp[-3].string), (yyvsp[-1].node_list));
    }
#line 2999 "parser.c"
    break;

  case 168: /* struct_init_fields: %empty  */
#line 782 "parser.y"
                {
        (yyval.node_list) = NULL;
    }
#line 3007 "parser.c"
    break;

  case 169: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 785 "parser.y"
                                              {
        (yyval.node_list) = create_node_list();
        add_to_node_list((yyval.node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
    }
#line 3016 "parser.c"
    break;

  case 170: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
#line 789 "parser.y"
                                                                             {
        add_to_node_list((yyvsp[-4].node_list), create_field_init_node((yyvsp[-2].string), (yyvsp[0].node)));
        (yyval.node_list) = (yyvsp[-4].node_list);
    }
#line 3025 "parser.c"
    break;


#line 3029 "parser.c"

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

#line 801 "parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 1 "parser.y"

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

#line 56 "parser.tab.cc"




# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

namespace yy {
#line 187 "parser.tab.cc"




  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// Symbol semantic values.
    union semantic_type
    {
#line 16 "parser.y"

    int number;
    double float_val;
    char* string;
    struct ASTNode* node;
    struct ASTNodeList* node_list;

#line 208 "parser.tab.cc"

    };
#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    TOKEN_DICT = 258,              // TOKEN_DICT
    TOKEN_MAP = 259,               // TOKEN_MAP
    TOKEN_FN = 260,                // TOKEN_FN
    TOKEN_LET = 261,               // TOKEN_LET
    TOKEN_CONST = 262,             // TOKEN_CONST
    TOKEN_RETURN = 263,            // TOKEN_RETURN
    TOKEN_IF = 264,                // TOKEN_IF
    TOKEN_ELSE = 265,              // TOKEN_ELSE
    TOKEN_FOR = 266,               // TOKEN_FOR
    TOKEN_WHILE = 267,             // TOKEN_WHILE
    TOKEN_LOOP = 268,              // TOKEN_LOOP
    TOKEN_BREAK = 269,             // TOKEN_BREAK
    TOKEN_CONTINUE = 270,          // TOKEN_CONTINUE
    TOKEN_IMPORT = 271,            // TOKEN_IMPORT
    TOKEN_EXPORT = 272,            // TOKEN_EXPORT
    TOKEN_PACKET = 273,            // TOKEN_PACKET
    TOKEN_STRUCT = 274,            // TOKEN_STRUCT
    TOKEN_ENUM = 275,              // TOKEN_ENUM
    TOKEN_IMPL = 276,              // TOKEN_IMPL
    TOKEN_MATCH = 277,             // TOKEN_MATCH
    TOKEN_TYPE = 278,              // TOKEN_TYPE
    TOKEN_TRUE = 279,              // TOKEN_TRUE
    TOKEN_FALSE = 280,             // TOKEN_FALSE
    TOKEN_NIL = 281,               // TOKEN_NIL
    TOKEN_AS = 282,                // TOKEN_AS
    TOKEN_IN = 283,                // TOKEN_IN
    TOKEN_FROM = 284,              // TOKEN_FROM
    TOKEN_PUB = 285,               // TOKEN_PUB
    TOKEN_NEW = 286,               // TOKEN_NEW
    TOKEN_UNSAFE = 287,            // TOKEN_UNSAFE
    TOKEN_NNL = 288,               // TOKEN_NNL
    TOKEN_JMP = 289,               // TOKEN_JMP
    TOKEN_MODULE = 290,            // TOKEN_MODULE
    TOKEN_ONLY = 291,              // TOKEN_ONLY
    TOKEN_TIMEOUT = 292,           // TOKEN_TIMEOUT
    TOKEN_SANDBOX = 293,           // TOKEN_SANDBOX
    TOKEN_ALLOW_FFI = 294,         // TOKEN_ALLOW_FFI
    TOKEN_ASYNC = 295,             // TOKEN_ASYNC
    TOKEN_AWAIT = 296,             // TOKEN_AWAIT
    TOKEN_SPAWN = 297,             // TOKEN_SPAWN
    TOKEN_LAMBDA = 298,            // TOKEN_LAMBDA
    TOKEN_EXTENDS = 299,           // TOKEN_EXTENDS
    TOKEN_UNDERSCORE = 300,        // TOKEN_UNDERSCORE
    TOKEN_PLUS = 301,              // TOKEN_PLUS
    TOKEN_MINUS = 302,             // TOKEN_MINUS
    TOKEN_MULTIPLY = 303,          // TOKEN_MULTIPLY
    TOKEN_DIVIDE = 304,            // TOKEN_DIVIDE
    TOKEN_MODULO = 305,            // TOKEN_MODULO
    TOKEN_ASSIGN = 306,            // TOKEN_ASSIGN
    TOKEN_PLUS_ASSIGN = 307,       // TOKEN_PLUS_ASSIGN
    TOKEN_MINUS_ASSIGN = 308,      // TOKEN_MINUS_ASSIGN
    TOKEN_MULTIPLY_ASSIGN = 309,   // TOKEN_MULTIPLY_ASSIGN
    TOKEN_DIVIDE_ASSIGN = 310,     // TOKEN_DIVIDE_ASSIGN
    TOKEN_MODULO_ASSIGN = 311,     // TOKEN_MODULO_ASSIGN
    TOKEN_EQ = 312,                // TOKEN_EQ
    TOKEN_NEQ = 313,               // TOKEN_NEQ
    TOKEN_LT = 314,                // TOKEN_LT
    TOKEN_LTE = 315,               // TOKEN_LTE
    TOKEN_GT = 316,                // TOKEN_GT
    TOKEN_GTE = 317,               // TOKEN_GTE
    TOKEN_AND = 318,               // TOKEN_AND
    TOKEN_OR = 319,                // TOKEN_OR
    TOKEN_NOT = 320,               // TOKEN_NOT
    TOKEN_AMP = 321,               // TOKEN_AMP
    TOKEN_PIPE = 322,              // TOKEN_PIPE
    TOKEN_XOR = 323,               // TOKEN_XOR
    TOKEN_LSHIFT = 324,            // TOKEN_LSHIFT
    TOKEN_RSHIFT = 325,            // TOKEN_RSHIFT
    TOKEN_DOUBLE_COLON = 326,      // TOKEN_DOUBLE_COLON
    TOKEN_DOT = 327,               // TOKEN_DOT
    TOKEN_SECURITY = 328,          // TOKEN_SECURITY
    TOKEN_COLON = 329,             // TOKEN_COLON
    TOKEN_SEMICOLON = 330,         // TOKEN_SEMICOLON
    TOKEN_COMMA = 331,             // TOKEN_COMMA
    TOKEN_ARROW = 332,             // TOKEN_ARROW
    TOKEN_FAT_ARROW = 333,         // TOKEN_FAT_ARROW
    TOKEN_PIPE_FORWARD = 334,      // TOKEN_PIPE_FORWARD
    TOKEN_OPTIONAL = 335,          // TOKEN_OPTIONAL
    TOKEN_COALESCE = 336,          // TOKEN_COALESCE
    TOKEN_RANGE = 337,             // TOKEN_RANGE
    TOKEN_RANGE_INC = 338,         // TOKEN_RANGE_INC
    TOKEN_MUTS = 339,              // TOKEN_MUTS
    TOKEN_SYSF = 340,              // TOKEN_SYSF
    TOKEN_SH = 341,                // TOKEN_SH
    TOKEN_LPAREN = 342,            // TOKEN_LPAREN
    TOKEN_RPAREN = 343,            // TOKEN_RPAREN
    TOKEN_LBRACE = 344,            // TOKEN_LBRACE
    TOKEN_RBRACE = 345,            // TOKEN_RBRACE
    TOKEN_LBRACKET = 346,          // TOKEN_LBRACKET
    TOKEN_RBRACKET = 347,          // TOKEN_RBRACKET
    TOKEN_TRY = 348,               // TOKEN_TRY
    TOKEN_CATCH = 349,             // TOKEN_CATCH
    TOKEN_FINALLY = 350,           // TOKEN_FINALLY
    TOKEN_THROW = 351,             // TOKEN_THROW
    TOKEN_EXCEPT = 352,            // TOKEN_EXCEPT
    TOKEN_RAISE = 353,             // TOKEN_RAISE
    TOKEN_IDENTIFIER = 354,        // TOKEN_IDENTIFIER
    TOKEN_NUMBER = 355,            // TOKEN_NUMBER
    TOKEN_FLOAT = 356,             // TOKEN_FLOAT
    TOKEN_STRING = 357,            // TOKEN_STRING
    TOKEN_F_STRING = 358           // TOKEN_F_STRING
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 104, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_TOKEN_DICT = 3,                        // TOKEN_DICT
        S_TOKEN_MAP = 4,                         // TOKEN_MAP
        S_TOKEN_FN = 5,                          // TOKEN_FN
        S_TOKEN_LET = 6,                         // TOKEN_LET
        S_TOKEN_CONST = 7,                       // TOKEN_CONST
        S_TOKEN_RETURN = 8,                      // TOKEN_RETURN
        S_TOKEN_IF = 9,                          // TOKEN_IF
        S_TOKEN_ELSE = 10,                       // TOKEN_ELSE
        S_TOKEN_FOR = 11,                        // TOKEN_FOR
        S_TOKEN_WHILE = 12,                      // TOKEN_WHILE
        S_TOKEN_LOOP = 13,                       // TOKEN_LOOP
        S_TOKEN_BREAK = 14,                      // TOKEN_BREAK
        S_TOKEN_CONTINUE = 15,                   // TOKEN_CONTINUE
        S_TOKEN_IMPORT = 16,                     // TOKEN_IMPORT
        S_TOKEN_EXPORT = 17,                     // TOKEN_EXPORT
        S_TOKEN_PACKET = 18,                     // TOKEN_PACKET
        S_TOKEN_STRUCT = 19,                     // TOKEN_STRUCT
        S_TOKEN_ENUM = 20,                       // TOKEN_ENUM
        S_TOKEN_IMPL = 21,                       // TOKEN_IMPL
        S_TOKEN_MATCH = 22,                      // TOKEN_MATCH
        S_TOKEN_TYPE = 23,                       // TOKEN_TYPE
        S_TOKEN_TRUE = 24,                       // TOKEN_TRUE
        S_TOKEN_FALSE = 25,                      // TOKEN_FALSE
        S_TOKEN_NIL = 26,                        // TOKEN_NIL
        S_TOKEN_AS = 27,                         // TOKEN_AS
        S_TOKEN_IN = 28,                         // TOKEN_IN
        S_TOKEN_FROM = 29,                       // TOKEN_FROM
        S_TOKEN_PUB = 30,                        // TOKEN_PUB
        S_TOKEN_NEW = 31,                        // TOKEN_NEW
        S_TOKEN_UNSAFE = 32,                     // TOKEN_UNSAFE
        S_TOKEN_NNL = 33,                        // TOKEN_NNL
        S_TOKEN_JMP = 34,                        // TOKEN_JMP
        S_TOKEN_MODULE = 35,                     // TOKEN_MODULE
        S_TOKEN_ONLY = 36,                       // TOKEN_ONLY
        S_TOKEN_TIMEOUT = 37,                    // TOKEN_TIMEOUT
        S_TOKEN_SANDBOX = 38,                    // TOKEN_SANDBOX
        S_TOKEN_ALLOW_FFI = 39,                  // TOKEN_ALLOW_FFI
        S_TOKEN_ASYNC = 40,                      // TOKEN_ASYNC
        S_TOKEN_AWAIT = 41,                      // TOKEN_AWAIT
        S_TOKEN_SPAWN = 42,                      // TOKEN_SPAWN
        S_TOKEN_LAMBDA = 43,                     // TOKEN_LAMBDA
        S_TOKEN_EXTENDS = 44,                    // TOKEN_EXTENDS
        S_TOKEN_UNDERSCORE = 45,                 // TOKEN_UNDERSCORE
        S_TOKEN_PLUS = 46,                       // TOKEN_PLUS
        S_TOKEN_MINUS = 47,                      // TOKEN_MINUS
        S_TOKEN_MULTIPLY = 48,                   // TOKEN_MULTIPLY
        S_TOKEN_DIVIDE = 49,                     // TOKEN_DIVIDE
        S_TOKEN_MODULO = 50,                     // TOKEN_MODULO
        S_TOKEN_ASSIGN = 51,                     // TOKEN_ASSIGN
        S_TOKEN_PLUS_ASSIGN = 52,                // TOKEN_PLUS_ASSIGN
        S_TOKEN_MINUS_ASSIGN = 53,               // TOKEN_MINUS_ASSIGN
        S_TOKEN_MULTIPLY_ASSIGN = 54,            // TOKEN_MULTIPLY_ASSIGN
        S_TOKEN_DIVIDE_ASSIGN = 55,              // TOKEN_DIVIDE_ASSIGN
        S_TOKEN_MODULO_ASSIGN = 56,              // TOKEN_MODULO_ASSIGN
        S_TOKEN_EQ = 57,                         // TOKEN_EQ
        S_TOKEN_NEQ = 58,                        // TOKEN_NEQ
        S_TOKEN_LT = 59,                         // TOKEN_LT
        S_TOKEN_LTE = 60,                        // TOKEN_LTE
        S_TOKEN_GT = 61,                         // TOKEN_GT
        S_TOKEN_GTE = 62,                        // TOKEN_GTE
        S_TOKEN_AND = 63,                        // TOKEN_AND
        S_TOKEN_OR = 64,                         // TOKEN_OR
        S_TOKEN_NOT = 65,                        // TOKEN_NOT
        S_TOKEN_AMP = 66,                        // TOKEN_AMP
        S_TOKEN_PIPE = 67,                       // TOKEN_PIPE
        S_TOKEN_XOR = 68,                        // TOKEN_XOR
        S_TOKEN_LSHIFT = 69,                     // TOKEN_LSHIFT
        S_TOKEN_RSHIFT = 70,                     // TOKEN_RSHIFT
        S_TOKEN_DOUBLE_COLON = 71,               // TOKEN_DOUBLE_COLON
        S_TOKEN_DOT = 72,                        // TOKEN_DOT
        S_TOKEN_SECURITY = 73,                   // TOKEN_SECURITY
        S_TOKEN_COLON = 74,                      // TOKEN_COLON
        S_TOKEN_SEMICOLON = 75,                  // TOKEN_SEMICOLON
        S_TOKEN_COMMA = 76,                      // TOKEN_COMMA
        S_TOKEN_ARROW = 77,                      // TOKEN_ARROW
        S_TOKEN_FAT_ARROW = 78,                  // TOKEN_FAT_ARROW
        S_TOKEN_PIPE_FORWARD = 79,               // TOKEN_PIPE_FORWARD
        S_TOKEN_OPTIONAL = 80,                   // TOKEN_OPTIONAL
        S_TOKEN_COALESCE = 81,                   // TOKEN_COALESCE
        S_TOKEN_RANGE = 82,                      // TOKEN_RANGE
        S_TOKEN_RANGE_INC = 83,                  // TOKEN_RANGE_INC
        S_TOKEN_MUTS = 84,                       // TOKEN_MUTS
        S_TOKEN_SYSF = 85,                       // TOKEN_SYSF
        S_TOKEN_SH = 86,                         // TOKEN_SH
        S_TOKEN_LPAREN = 87,                     // TOKEN_LPAREN
        S_TOKEN_RPAREN = 88,                     // TOKEN_RPAREN
        S_TOKEN_LBRACE = 89,                     // TOKEN_LBRACE
        S_TOKEN_RBRACE = 90,                     // TOKEN_RBRACE
        S_TOKEN_LBRACKET = 91,                   // TOKEN_LBRACKET
        S_TOKEN_RBRACKET = 92,                   // TOKEN_RBRACKET
        S_TOKEN_TRY = 93,                        // TOKEN_TRY
        S_TOKEN_CATCH = 94,                      // TOKEN_CATCH
        S_TOKEN_FINALLY = 95,                    // TOKEN_FINALLY
        S_TOKEN_THROW = 96,                      // TOKEN_THROW
        S_TOKEN_EXCEPT = 97,                     // TOKEN_EXCEPT
        S_TOKEN_RAISE = 98,                      // TOKEN_RAISE
        S_TOKEN_IDENTIFIER = 99,                 // TOKEN_IDENTIFIER
        S_TOKEN_NUMBER = 100,                    // TOKEN_NUMBER
        S_TOKEN_FLOAT = 101,                     // TOKEN_FLOAT
        S_TOKEN_STRING = 102,                    // TOKEN_STRING
        S_TOKEN_F_STRING = 103,                  // TOKEN_F_STRING
        S_YYACCEPT = 104,                        // $accept
        S_program = 105,                         // program
        S_statement_list = 106,                  // statement_list
        S_unsafe_stmt = 107,                     // unsafe_stmt
        S_continue_statement = 108,              // continue_statement
        S_statement = 109,                       // statement
        S_sysf_expr = 110,                       // sysf_expr
        S_sh_expr = 111,                         // sh_expr
        S_nnl_statement = 112,                   // nnl_statement
        S_try_statement = 113,                   // try_statement
        S_catch_block = 114,                     // catch_block
        S_finally_block = 115,                   // finally_block
        S_throw_statement = 116,                 // throw_statement
        S_jmp_statement = 117,                   // jmp_statement
        S_import_statement = 118,                // import_statement
        S_import_constraints = 119,              // import_constraints
        S_import_options = 120,                  // import_options
        S_name_list = 121,                       // name_list
        S_export_statement = 122,                // export_statement
        S_packet_decl = 123,                     // packet_decl
        S_function_decl = 124,                   // function_decl
        S_param_list = 125,                      // param_list
        S_param = 126,                           // param
        S_type = 127,                            // type
        S_dict_expr = 128,                       // dict_expr
        S_dict_entries = 129,                    // dict_entries
        S_dict_entry_list = 130,                 // dict_entry_list
        S_dict_access = 131,                     // dict_access
        S_return_type = 132,                     // return_type
        S_let_decl = 133,                        // let_decl
        S_const_decl = 134,                      // const_decl
        S_if_statement = 135,                    // if_statement
        S_break_statement = 136,                 // break_statement
        S_for_statement = 137,                   // for_statement
        S_while_statement = 138,                 // while_statement
        S_loop_statement = 139,                  // loop_statement
        S_match_statement = 140,                 // match_statement
        S_match_cases = 141,                     // match_cases
        S_match_case = 142,                      // match_case
        S_pattern = 143,                         // pattern
        S_struct_decl = 144,                     // struct_decl
        S_struct_fields = 145,                   // struct_fields
        S_struct_field = 146,                    // struct_field
        S_enum_decl = 147,                       // enum_decl
        S_enum_variants = 148,                   // enum_variants
        S_module_decl = 149,                     // module_decl
        S_impl_decl = 150,                       // impl_decl
        S_function_decl_list = 151,              // function_decl_list
        S_return_statement = 152,                // return_statement
        S_expression = 153,                      // expression
        S_binary_expr = 154,                     // binary_expr
        S_unary_expr = 155,                      // unary_expr
        S_lambda_expr = 156,                     // lambda_expr
        S_array_access = 157,                    // array_access
        S_primary_expr = 158,                    // primary_expr
        S_f_string = 159,                        // f_string
        S_member_access = 160,                   // member_access
        S_call_expr = 161,                       // call_expr
        S_argument_list = 162,                   // argument_list
        S_array_expr = 163,                      // array_expr
        S_await_expr = 164,                      // await_expr
        S_spawn_expr = 165,                      // spawn_expr
        S_array_items = 166,                     // array_items
        S_struct_expr = 167,                     // struct_expr
        S_struct_init_fields = 168               // struct_init_fields
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value (std::move (that.value))
      {}
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);
      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    YY_RVREF (semantic_type) v);

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {};

    /// Build a parser object.
    parser ();
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0




  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const unsigned char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 3268,     ///< Last index in yytable_.
      yynnts_ = 65,  ///< Number of nonterminal symbols.
      yyfinal_ = 140 ///< Termination state number.
    };



  };


} // yy
#line 1016 "parser.tab.cc"








#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 1095 "parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}

  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: statement_list
#line 112 "parser.y"
                   {
        program_root = create_program_node((yystack_[0].value.node_list));
    }
#line 1547 "parser.tab.cc"
    break;

  case 3: // statement_list: statement
#line 118 "parser.y"
              {
        (yylhs.value.node_list) = create_node_list();
        add_to_node_list((yylhs.value.node_list), (yystack_[0].value.node));
    }
#line 1556 "parser.tab.cc"
    break;

  case 4: // statement_list: statement_list statement
#line 122 "parser.y"
                               {
        add_to_node_list((yystack_[1].value.node_list), (yystack_[0].value.node));
        (yylhs.value.node_list) = (yystack_[1].value.node_list);
    }
#line 1565 "parser.tab.cc"
    break;

  case 5: // unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 128 "parser.y"
                                                          {
        (yylhs.value.node) = create_unsafe_node((yystack_[1].value.node_list));
    }
#line 1573 "parser.tab.cc"
    break;

  case 6: // continue_statement: TOKEN_CONTINUE
#line 133 "parser.y"
                   {
        (yylhs.value.node) = create_continue_node();
    }
#line 1581 "parser.tab.cc"
    break;

  case 7: // statement: import_statement
#line 140 "parser.y"
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1587 "parser.tab.cc"
    break;

  case 8: // statement: export_statement
#line 141 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1593 "parser.tab.cc"
    break;

  case 9: // statement: continue_statement
#line 142 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1599 "parser.tab.cc"
    break;

  case 10: // statement: nnl_statement
#line 143 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1605 "parser.tab.cc"
    break;

  case 11: // statement: jmp_statement
#line 144 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1611 "parser.tab.cc"
    break;

  case 12: // statement: module_decl
#line 145 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1617 "parser.tab.cc"
    break;

  case 13: // statement: try_statement
#line 146 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1623 "parser.tab.cc"
    break;

  case 14: // statement: throw_statement
#line 147 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1629 "parser.tab.cc"
    break;

  case 15: // statement: packet_decl
#line 148 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1635 "parser.tab.cc"
    break;

  case 16: // statement: function_decl
#line 149 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1641 "parser.tab.cc"
    break;

  case 17: // statement: struct_decl
#line 150 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1647 "parser.tab.cc"
    break;

  case 18: // statement: enum_decl
#line 151 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1653 "parser.tab.cc"
    break;

  case 19: // statement: impl_decl
#line 152 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1659 "parser.tab.cc"
    break;

  case 20: // statement: let_decl
#line 153 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1665 "parser.tab.cc"
    break;

  case 21: // statement: break_statement
#line 154 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1671 "parser.tab.cc"
    break;

  case 22: // statement: const_decl
#line 155 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1677 "parser.tab.cc"
    break;

  case 23: // statement: if_statement
#line 156 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1683 "parser.tab.cc"
    break;

  case 24: // statement: for_statement
#line 157 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1689 "parser.tab.cc"
    break;

  case 25: // statement: unsafe_stmt
#line 158 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1695 "parser.tab.cc"
    break;

  case 26: // statement: while_statement
#line 159 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1701 "parser.tab.cc"
    break;

  case 27: // statement: loop_statement
#line 160 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1707 "parser.tab.cc"
    break;

  case 28: // statement: match_statement
#line 161 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1713 "parser.tab.cc"
    break;

  case 29: // statement: return_statement
#line 162 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1719 "parser.tab.cc"
    break;

  case 30: // statement: expression
#line 163 "parser.y"
                 {
        (yylhs.value.node) = create_expr_statement((yystack_[0].value.node));
    }
#line 1727 "parser.tab.cc"
    break;

  case 31: // sysf_expr: TOKEN_SYSF TOKEN_LPAREN expression TOKEN_RPAREN
#line 168 "parser.y"
                                                    {
        (yylhs.value.node) = create_sysf_node((yystack_[1].value.node));
    }
#line 1735 "parser.tab.cc"
    break;

  case 32: // sysf_expr: TOKEN_SYSF expression
#line 171 "parser.y"
                            {
        (yylhs.value.node) = create_sysf_node((yystack_[0].value.node));
    }
#line 1743 "parser.tab.cc"
    break;

  case 33: // sh_expr: TOKEN_SH TOKEN_LPAREN expression TOKEN_RPAREN
#line 177 "parser.y"
                                                  {
        (yylhs.value.node) = create_sh_node((yystack_[1].value.node));
    }
#line 1751 "parser.tab.cc"
    break;

  case 34: // sh_expr: TOKEN_SH expression
#line 180 "parser.y"
                          {
        (yylhs.value.node) = create_sh_node((yystack_[0].value.node));
    }
#line 1759 "parser.tab.cc"
    break;

  case 35: // nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 186 "parser.y"
                                                                        {
        (yylhs.value.node) = create_nnl_node((yystack_[3].value.string), (yystack_[1].value.node_list));
    }
#line 1767 "parser.tab.cc"
    break;

  case 36: // try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block
#line 192 "parser.y"
                                                                   {
        (yylhs.value.node) = create_try_node((yystack_[2].value.node_list), (yystack_[0].value.node), NULL);
    }
#line 1775 "parser.tab.cc"
    break;

  case 37: // try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block
#line 195 "parser.y"
                                                                                   {
        (yylhs.value.node) = create_try_node((yystack_[3].value.node_list), (yystack_[1].value.node), (yystack_[0].value.node));
    }
#line 1783 "parser.tab.cc"
    break;

  case 38: // catch_block: TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 201 "parser.y"
                                                                                                    {
        (yylhs.value.node) = create_catch_node((yystack_[4].value.string), (yystack_[1].value.node_list));
    }
#line 1791 "parser.tab.cc"
    break;

  case 39: // catch_block: TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 204 "parser.y"
                                                                                                       {
        (yylhs.value.node) = create_catch_node((yystack_[4].value.string), (yystack_[1].value.node_list));
    }
#line 1799 "parser.tab.cc"
    break;

  case 40: // finally_block: TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 210 "parser.y"
                                                           {
        (yylhs.value.node) = create_finally_node((yystack_[1].value.node_list));
    }
#line 1807 "parser.tab.cc"
    break;

  case 41: // throw_statement: TOKEN_THROW expression
#line 216 "parser.y"
                           {
        (yylhs.value.node) = create_throw_node((yystack_[0].value.node));
    }
#line 1815 "parser.tab.cc"
    break;

  case 42: // throw_statement: TOKEN_RAISE expression
#line 219 "parser.y"
                             {
        (yylhs.value.node) = create_throw_node((yystack_[0].value.node));
    }
#line 1823 "parser.tab.cc"
    break;

  case 43: // jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER
#line 224 "parser.y"
                               {
        (yylhs.value.node) = create_jmp_node((yystack_[0].value.string), NULL);
    }
#line 1831 "parser.tab.cc"
    break;

  case 44: // jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression
#line 227 "parser.y"
                                            {
        (yylhs.value.node) = create_jmp_node((yystack_[1].value.string), (yystack_[0].value.node));
    }
#line 1839 "parser.tab.cc"
    break;

  case 45: // import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER
#line 233 "parser.y"
                                  {
        (yylhs.value.node) = create_import_node((yystack_[0].value.string), NULL, NULL);
    }
#line 1847 "parser.tab.cc"
    break;

  case 46: // import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_IDENTIFIER
#line 236 "parser.y"
                                              {
        char* path = malloc(strlen((yystack_[0].value.string)) + 3);
        sprintf(path, "./%s", (yystack_[0].value.string));
        (yylhs.value.node) = create_import_node(path, NULL, NULL);
        free(path);
    }
#line 1858 "parser.tab.cc"
    break;

  case 47: // import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_DOT TOKEN_DOT TOKEN_IDENTIFIER
#line 242 "parser.y"
                                                                  {
        char* path = malloc(strlen((yystack_[0].value.string)) + 4);
        sprintf(path, "../%s", (yystack_[0].value.string));
        (yylhs.value.node) = create_import_node(path, NULL, NULL);
        free(path);
    }
#line 1869 "parser.tab.cc"
    break;

  case 48: // import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_STRING
#line 248 "parser.y"
                                                            {
        (yylhs.value.node) = create_import_node((yystack_[0].value.string), (yystack_[2].value.string), NULL);
    }
#line 1877 "parser.tab.cc"
    break;

  case 49: // import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_DOT TOKEN_IDENTIFIER
#line 252 "parser.y"
                                                                          {
        char* path = malloc(strlen((yystack_[0].value.string)) + 3);
        sprintf(path, "./%s", (yystack_[0].value.string));
        (yylhs.value.node) = create_import_node(path, (yystack_[3].value.string), NULL);
        free(path);
    }
#line 1888 "parser.tab.cc"
    break;

  case 50: // import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_AS TOKEN_IDENTIFIER
#line 258 "parser.y"
                                                              {
        (yylhs.value.node) = create_import_node((yystack_[2].value.string), (yystack_[0].value.string), NULL);
    }
#line 1896 "parser.tab.cc"
    break;

  case 51: // import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER import_constraints
#line 261 "parser.y"
                                                       {
        (yylhs.value.node) = create_import_node((yystack_[1].value.string), NULL, (yystack_[0].value.node));
    }
#line 1904 "parser.tab.cc"
    break;

  case 52: // import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE
#line 267 "parser.y"
                                             {
        (yylhs.value.node) = (yystack_[1].value.node);
    }
#line 1912 "parser.tab.cc"
    break;

  case 53: // import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET
#line 273 "parser.y"
                                                                   {
        (yylhs.value.node) = create_constraints_node("only", (yystack_[1].value.node_list));
    }
#line 1920 "parser.tab.cc"
    break;

  case 54: // import_options: import_options TOKEN_COMMA import_options
#line 276 "parser.y"
                                                {
        (yylhs.value.node) = merge_constraints((yystack_[2].value.node), (yystack_[0].value.node));
    }
#line 1928 "parser.tab.cc"
    break;

  case 55: // name_list: TOKEN_IDENTIFIER
#line 282 "parser.y"
                     {
        (yylhs.value.node_list) = create_node_list();
        add_to_node_list((yylhs.value.node_list), create_identifier_node((yystack_[0].value.string)));
    }
#line 1937 "parser.tab.cc"
    break;

  case 56: // name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER
#line 286 "parser.y"
                                             {
        add_to_node_list((yystack_[2].value.node_list), create_identifier_node((yystack_[0].value.string)));
        (yylhs.value.node_list) = (yystack_[2].value.node_list);
    }
#line 1946 "parser.tab.cc"
    break;

  case 57: // export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER
#line 293 "parser.y"
                                  {
        (yylhs.value.node) = create_export_node((yystack_[0].value.string));
    }
#line 1954 "parser.tab.cc"
    break;

  case 58: // packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 299 "parser.y"
                                                                           {
        (yylhs.value.node) = create_packet_node((yystack_[3].value.string), (yystack_[1].value.node_list));
    }
#line 1962 "parser.tab.cc"
    break;

  case 59: // function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 305 "parser.y"
                                                                                                                        {
        (yylhs.value.node) = create_function_node((yystack_[7].value.string), (yystack_[5].value.node_list), (yystack_[3].value.node), (yystack_[1].value.node_list));
    }
#line 1970 "parser.tab.cc"
    break;

  case 60: // function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 308 "parser.y"
                                                                                                                                    {
        (yylhs.value.node) = create_public_function_node((yystack_[7].value.string), (yystack_[5].value.node_list), (yystack_[3].value.node), (yystack_[1].value.node_list));
    }
#line 1978 "parser.tab.cc"
    break;

  case 61: // function_decl: TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 311 "parser.y"
                                                                                                                                      {
        ASTNode* node = create_function_node((yystack_[7].value.string), (yystack_[5].value.node_list), (yystack_[3].value.node), (yystack_[1].value.node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        (yylhs.value.node) = node;
    }
#line 1989 "parser.tab.cc"
    break;

  case 62: // function_decl: TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 317 "parser.y"
                                                                                                                                                {
        ASTNode* node = create_function_node((yystack_[7].value.string), (yystack_[5].value.node_list), (yystack_[3].value.node), (yystack_[1].value.node_list));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        (yylhs.value.node) = node;
    }
#line 2001 "parser.tab.cc"
    break;

  case 63: // function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression
#line 324 "parser.y"
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node((yystack_[0].value.node));
        add_to_node_list(body, return_stmt);
        (yylhs.value.node) = create_function_node((yystack_[6].value.string), (yystack_[4].value.node_list), (yystack_[2].value.node), body);
    }
#line 2012 "parser.tab.cc"
    break;

  case 64: // param_list: %empty
#line 333 "parser.y"
                {
        (yylhs.value.node_list) = NULL;
    }
#line 2020 "parser.tab.cc"
    break;

  case 65: // param_list: param
#line 336 "parser.y"
            {
        (yylhs.value.node_list) = create_node_list();
        add_to_node_list((yylhs.value.node_list), (yystack_[0].value.node));
    }
#line 2029 "parser.tab.cc"
    break;

  case 66: // param_list: param_list TOKEN_COMMA param
#line 340 "parser.y"
                                   {
        add_to_node_list((yystack_[2].value.node_list), (yystack_[0].value.node));
        (yylhs.value.node_list) = (yystack_[2].value.node_list);
    }
#line 2038 "parser.tab.cc"
    break;

  case 67: // param: TOKEN_IDENTIFIER
#line 347 "parser.y"
                     {
        (yylhs.value.node) = create_identifier_node((yystack_[0].value.string));
    }
#line 2046 "parser.tab.cc"
    break;

  case 68: // param: TOKEN_IDENTIFIER TOKEN_COLON type
#line 350 "parser.y"
                                        {
        (yylhs.value.node) = create_param_node((yystack_[2].value.string), (yystack_[0].value.node));
    }
#line 2054 "parser.tab.cc"
    break;

  case 69: // type: TOKEN_IDENTIFIER
#line 356 "parser.y"
                     {
        (yylhs.value.node) = create_type_node((yystack_[0].value.string));
    }
#line 2062 "parser.tab.cc"
    break;

  case 70: // type: TOKEN_IDENTIFIER TOKEN_OPTIONAL
#line 359 "parser.y"
                                      {
        (yylhs.value.node) = create_optional_type_node((yystack_[1].value.string));
    }
#line 2070 "parser.tab.cc"
    break;

  case 71: // type: TOKEN_LBRACKET TOKEN_RBRACKET type
#line 362 "parser.y"
                                         {
        (yylhs.value.node) = create_array_type_node((yystack_[0].value.node));
    }
#line 2078 "parser.tab.cc"
    break;

  case 72: // dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE
#line 370 "parser.y"
                                                      {
        (yylhs.value.node) = create_dict_node((yystack_[1].value.node_list));
    }
#line 2086 "parser.tab.cc"
    break;

  case 73: // dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE
#line 373 "parser.y"
                                                       {
        (yylhs.value.node) = create_dict_node((yystack_[1].value.node_list));
    }
#line 2094 "parser.tab.cc"
    break;

  case 74: // dict_entries: %empty
#line 379 "parser.y"
                {
        (yylhs.value.node_list) = NULL;
    }
#line 2102 "parser.tab.cc"
    break;

  case 75: // dict_entries: dict_entry_list
#line 382 "parser.y"
                      {
        (yylhs.value.node_list) = (yystack_[0].value.node_list);
    }
#line 2110 "parser.tab.cc"
    break;

  case 76: // dict_entry_list: expression TOKEN_FAT_ARROW expression
#line 388 "parser.y"
                                          {
        (yylhs.value.node_list) = create_node_list();
        ASTNode* pair = create_binary_op((yystack_[2].value.node), OP_ASSIGN, (yystack_[0].value.node));
        add_to_node_list((yylhs.value.node_list), pair);
    }
#line 2120 "parser.tab.cc"
    break;

  case 77: // dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression
#line 393 "parser.y"
                                                                        {
        ASTNode* pair = create_binary_op((yystack_[2].value.node), OP_ASSIGN, (yystack_[0].value.node));
        add_to_node_list((yystack_[4].value.node_list), pair);
        (yylhs.value.node_list) = (yystack_[4].value.node_list);
    }
#line 2130 "parser.tab.cc"
    break;

  case 78: // dict_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET
#line 402 "parser.y"
                                                          {
        // Détecter si c'est un accès dictionnaire ou tableau
        // Par défaut, c'est un accès tableau, mais on peut différencier par le type
        // Pour l'instant, on crée un nœud d'accès dictionnaire
        (yylhs.value.node) = create_dict_access_node((yystack_[3].value.node), (yystack_[1].value.node));
    }
#line 2141 "parser.tab.cc"
    break;

  case 79: // return_type: %empty
#line 421 "parser.y"
                {
        (yylhs.value.node) = NULL;
    }
#line 2149 "parser.tab.cc"
    break;

  case 80: // return_type: TOKEN_COLON type
#line 424 "parser.y"
                       {
        (yylhs.value.node) = (yystack_[0].value.node);
    }
#line 2157 "parser.tab.cc"
    break;

  case 81: // return_type: TOKEN_ARROW primary_expr
#line 427 "parser.y"
                               {
        // Pour les retours directs: -> expr
        (yylhs.value.node) = create_return_direct_node((yystack_[0].value.node));
    }
#line 2166 "parser.tab.cc"
    break;

  case 82: // let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression
#line 434 "parser.y"
                                                       {
        (yylhs.value.node) = create_let_node((yystack_[2].value.string), NULL, (yystack_[0].value.node));
    }
#line 2174 "parser.tab.cc"
    break;

  case 83: // let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression
#line 437 "parser.y"
                                                                          {
        (yylhs.value.node) = create_let_node((yystack_[4].value.string), (yystack_[2].value.node), (yystack_[0].value.node));
    }
#line 2182 "parser.tab.cc"
    break;

  case 84: // let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression
#line 440 "parser.y"
                                                                   {
        ASTNode* node = create_let_node((yystack_[2].value.string), NULL, (yystack_[0].value.node));
        node->var_decl.is_public = 1;
        (yylhs.value.node) = node;
    }
#line 2192 "parser.tab.cc"
    break;

  case 85: // let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression
#line 446 "parser.y"
                                                          {
        (yylhs.value.node) = create_muts_node((yystack_[2].value.string), NULL, (yystack_[0].value.node));
    }
#line 2200 "parser.tab.cc"
    break;

  case 86: // let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression
#line 449 "parser.y"
                                                                           {
        (yylhs.value.node) = create_muts_node((yystack_[4].value.string), (yystack_[2].value.node), (yystack_[0].value.node));
    }
#line 2208 "parser.tab.cc"
    break;

  case 87: // const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression
#line 454 "parser.y"
                                                         {
        (yylhs.value.node) = create_const_node((yystack_[2].value.string), (yystack_[0].value.node));
    }
#line 2216 "parser.tab.cc"
    break;

  case 88: // const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression
#line 457 "parser.y"
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node((yystack_[2].value.string), (yystack_[0].value.node));
        node->var_decl.is_public = 1;
        (yylhs.value.node) = node;
    }
#line 2227 "parser.tab.cc"
    break;

  case 89: // if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 466 "parser.y"
                                                                 {
        (yylhs.value.node) = create_if_node((yystack_[3].value.node), (yystack_[1].value.node_list), NULL);
    }
#line 2235 "parser.tab.cc"
    break;

  case 90: // if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 469 "parser.y"
                                                                                                                       {
        (yylhs.value.node) = create_if_node((yystack_[7].value.node), (yystack_[5].value.node_list), (yystack_[1].value.node_list));
    }
#line 2243 "parser.tab.cc"
    break;

  case 91: // break_statement: TOKEN_BREAK
#line 474 "parser.y"
                {
        (yylhs.value.node) = create_break_node();
    }
#line 2251 "parser.tab.cc"
    break;

  case 92: // for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 479 "parser.y"
                                                                                                                                                      {
        ASTNode* init = create_let_node((yystack_[9].value.string), NULL, (yystack_[7].value.node));
        ASTNode* cond = (yystack_[5].value.node);
        ASTNode* inc = create_expr_statement((yystack_[3].value.node));
        (yylhs.value.node) = create_for_node(init, cond, inc, (yystack_[1].value.node_list));
    }
#line 2262 "parser.tab.cc"
    break;

  case 93: // for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 485 "parser.y"
                                                                    {
        (yylhs.value.node) = create_while_node((yystack_[3].value.node), (yystack_[1].value.node_list));
    }
#line 2270 "parser.tab.cc"
    break;

  case 94: // for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 488 "parser.y"
                                                                                              {
        // for x in array { ... }
        ASTNode* array_expr = (yystack_[3].value.node);
        ASTNodeList* body = (yystack_[1].value.node_list);
        
        // Créer un nœud spécial pour for-in
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_FOR_IN;
        node->for_in.var = strdup((yystack_[5].value.string));
        node->for_in.collection = array_expr;
        node->for_in.body = body;
        (yylhs.value.node) = node;
    }
#line 2288 "parser.tab.cc"
    break;

  case 95: // while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 504 "parser.y"
                                                                    {
        (yylhs.value.node) = create_while_node((yystack_[3].value.node), (yystack_[1].value.node_list));
    }
#line 2296 "parser.tab.cc"
    break;

  case 96: // loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 510 "parser.y"
                                                        {
        (yylhs.value.node) = create_loop_node((yystack_[1].value.node_list));
    }
#line 2304 "parser.tab.cc"
    break;

  case 97: // match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE
#line 517 "parser.y"
                                                                 {
        (yylhs.value.node) = create_match_node((yystack_[3].value.node), (yystack_[1].value.node_list));
    }
#line 2312 "parser.tab.cc"
    break;

  case 98: // match_cases: match_case
#line 523 "parser.y"
               {
        (yylhs.value.node_list) = create_node_list();
        add_to_node_list((yylhs.value.node_list), (yystack_[0].value.node));
    }
#line 2321 "parser.tab.cc"
    break;

  case 99: // match_cases: match_cases match_case
#line 527 "parser.y"
                             {
        add_to_node_list((yystack_[1].value.node_list), (yystack_[0].value.node));
        (yylhs.value.node_list) = (yystack_[1].value.node_list);
    }
#line 2330 "parser.tab.cc"
    break;

  case 100: // match_case: pattern TOKEN_FAT_ARROW expression
#line 534 "parser.y"
                                       {
        (yylhs.value.node) = create_match_case_node((yystack_[2].value.node), (yystack_[0].value.node));
    }
#line 2338 "parser.tab.cc"
    break;

  case 101: // pattern: TOKEN_NUMBER
#line 540 "parser.y"
                 {
        (yylhs.value.node) = create_pattern_number((yystack_[0].value.number));
    }
#line 2346 "parser.tab.cc"
    break;

  case 102: // pattern: TOKEN_STRING
#line 543 "parser.y"
                   {
        (yylhs.value.node) = create_pattern_string((yystack_[0].value.string));
    }
#line 2354 "parser.tab.cc"
    break;

  case 103: // pattern: TOKEN_IDENTIFIER
#line 546 "parser.y"
                       {
        (yylhs.value.node) = create_pattern_ident((yystack_[0].value.string));
    }
#line 2362 "parser.tab.cc"
    break;

  case 104: // pattern: TOKEN_UNDERSCORE
#line 549 "parser.y"
                       {
        (yylhs.value.node) = create_pattern_wildcard();
    }
#line 2370 "parser.tab.cc"
    break;

  case 105: // struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE
#line 555 "parser.y"
                                                                          {
        (yylhs.value.node) = create_struct_node((yystack_[3].value.string), (yystack_[1].value.node_list));
    }
#line 2378 "parser.tab.cc"
    break;

  case 106: // struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE
#line 558 "parser.y"
                                                                                                           {
        (yylhs.value.node) = create_struct_extend_node((yystack_[5].value.string), (yystack_[3].value.string), (yystack_[1].value.node_list));
    }
#line 2386 "parser.tab.cc"
    break;

  case 107: // struct_fields: %empty
#line 564 "parser.y"
                {
        (yylhs.value.node_list) = NULL;
    }
#line 2394 "parser.tab.cc"
    break;

  case 108: // struct_fields: struct_field
#line 567 "parser.y"
                   {
        (yylhs.value.node_list) = create_node_list();
        add_to_node_list((yylhs.value.node_list), (yystack_[0].value.node));
    }
#line 2403 "parser.tab.cc"
    break;

  case 109: // struct_fields: struct_fields TOKEN_COMMA struct_field
#line 571 "parser.y"
                                             {
        add_to_node_list((yystack_[2].value.node_list), (yystack_[0].value.node));
        (yylhs.value.node_list) = (yystack_[2].value.node_list);
    }
#line 2412 "parser.tab.cc"
    break;

  case 110: // struct_fields: struct_fields struct_field
#line 575 "parser.y"
                                 {
        add_to_node_list((yystack_[1].value.node_list), (yystack_[0].value.node));
        (yylhs.value.node_list) = (yystack_[1].value.node_list);
    }
#line 2421 "parser.tab.cc"
    break;

  case 111: // struct_field: TOKEN_IDENTIFIER TOKEN_COLON type
#line 582 "parser.y"
                                      {
        (yylhs.value.node) = create_field_node((yystack_[2].value.string), (yystack_[0].value.node));
    }
#line 2429 "parser.tab.cc"
    break;

  case 112: // enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE
#line 588 "parser.y"
                                                                        {
        (yylhs.value.node) = create_enum_node((yystack_[3].value.string), (yystack_[1].value.node_list));
    }
#line 2437 "parser.tab.cc"
    break;

  case 113: // enum_variants: %empty
#line 594 "parser.y"
                {
        (yylhs.value.node_list) = NULL;
    }
#line 2445 "parser.tab.cc"
    break;

  case 114: // enum_variants: TOKEN_IDENTIFIER
#line 597 "parser.y"
                       {
        (yylhs.value.node_list) = create_node_list();
        add_to_node_list((yylhs.value.node_list), create_identifier_node((yystack_[0].value.string)));
    }
#line 2454 "parser.tab.cc"
    break;

  case 115: // enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER
#line 601 "parser.y"
                                                 {
        add_to_node_list((yystack_[2].value.node_list), create_identifier_node((yystack_[0].value.string)));
        (yylhs.value.node_list) = (yystack_[2].value.node_list);
    }
#line 2463 "parser.tab.cc"
    break;

  case 116: // module_decl: TOKEN_MODULE TOKEN_IDENTIFIER
#line 608 "parser.y"
                                  {
        // Créer un nœud nil pour éviter l'erreur
        (yylhs.value.node) = create_expr_statement(create_nil_node());
    }
#line 2472 "parser.tab.cc"
    break;

  case 117: // impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE
#line 615 "parser.y"
                                                                             {
        (yylhs.value.node) = create_impl_node((yystack_[3].value.string), (yystack_[1].value.node_list));
    }
#line 2480 "parser.tab.cc"
    break;

  case 118: // function_decl_list: %empty
#line 621 "parser.y"
                {
        (yylhs.value.node_list) = NULL;
    }
#line 2488 "parser.tab.cc"
    break;

  case 119: // function_decl_list: function_decl
#line 624 "parser.y"
                    {
        (yylhs.value.node_list) = create_node_list();
        add_to_node_list((yylhs.value.node_list), (yystack_[0].value.node));
    }
#line 2497 "parser.tab.cc"
    break;

  case 120: // function_decl_list: function_decl_list function_decl
#line 628 "parser.y"
                                       {
        add_to_node_list((yystack_[1].value.node_list), (yystack_[0].value.node));
        (yylhs.value.node_list) = (yystack_[1].value.node_list);
    }
#line 2506 "parser.tab.cc"
    break;

  case 121: // return_statement: TOKEN_RETURN expression
#line 635 "parser.y"
                            {
        (yylhs.value.node) = create_return_node((yystack_[0].value.node));
    }
#line 2514 "parser.tab.cc"
    break;

  case 122: // return_statement: TOKEN_RETURN
#line 638 "parser.y"
                   {
        (yylhs.value.node) = create_return_node(NULL);
    }
#line 2522 "parser.tab.cc"
    break;

  case 123: // expression: binary_expr
#line 644 "parser.y"
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2528 "parser.tab.cc"
    break;

  case 124: // expression: unary_expr
#line 645 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2534 "parser.tab.cc"
    break;

  case 125: // expression: primary_expr
#line 646 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2540 "parser.tab.cc"
    break;

  case 126: // binary_expr: expression TOKEN_PLUS expression
#line 650 "parser.y"
                                     {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_ADD, (yystack_[0].value.node));
    }
#line 2548 "parser.tab.cc"
    break;

  case 127: // binary_expr: expression TOKEN_MINUS expression
#line 653 "parser.y"
                                        {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_SUB, (yystack_[0].value.node));
    }
#line 2556 "parser.tab.cc"
    break;

  case 128: // binary_expr: expression TOKEN_MULTIPLY expression
#line 656 "parser.y"
                                           {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_MUL, (yystack_[0].value.node));
    }
#line 2564 "parser.tab.cc"
    break;

  case 129: // binary_expr: expression TOKEN_DIVIDE expression
#line 659 "parser.y"
                                         {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_DIV, (yystack_[0].value.node));
    }
#line 2572 "parser.tab.cc"
    break;

  case 130: // binary_expr: expression TOKEN_MODULO expression
#line 662 "parser.y"
                                         {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_MOD, (yystack_[0].value.node));
    }
#line 2580 "parser.tab.cc"
    break;

  case 131: // binary_expr: expression TOKEN_EQ expression
#line 665 "parser.y"
                                     {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_EQ, (yystack_[0].value.node));
    }
#line 2588 "parser.tab.cc"
    break;

  case 132: // binary_expr: expression TOKEN_NEQ expression
#line 668 "parser.y"
                                      {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_NEQ, (yystack_[0].value.node));
    }
#line 2596 "parser.tab.cc"
    break;

  case 133: // binary_expr: expression TOKEN_LT expression
#line 671 "parser.y"
                                     {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_LT, (yystack_[0].value.node));
    }
#line 2604 "parser.tab.cc"
    break;

  case 134: // binary_expr: expression TOKEN_LTE expression
#line 674 "parser.y"
                                      {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_LTE, (yystack_[0].value.node));
    }
#line 2612 "parser.tab.cc"
    break;

  case 135: // binary_expr: expression TOKEN_GT expression
#line 677 "parser.y"
                                     {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_GT, (yystack_[0].value.node));
    }
#line 2620 "parser.tab.cc"
    break;

  case 136: // binary_expr: expression TOKEN_GTE expression
#line 680 "parser.y"
                                      {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_GTE, (yystack_[0].value.node));
    }
#line 2628 "parser.tab.cc"
    break;

  case 137: // binary_expr: expression TOKEN_AND expression
#line 683 "parser.y"
                                      {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_AND, (yystack_[0].value.node));
    }
#line 2636 "parser.tab.cc"
    break;

  case 138: // binary_expr: expression TOKEN_OR expression
#line 686 "parser.y"
                                     {
        (yylhs.value.node) = create_binary_op((yystack_[2].value.node), OP_OR, (yystack_[0].value.node));
    }
#line 2644 "parser.tab.cc"
    break;

  case 139: // binary_expr: expression TOKEN_ASSIGN expression
#line 689 "parser.y"
                                         {
        (yylhs.value.node) = create_assign_node((yystack_[2].value.node), (yystack_[0].value.node));
    }
#line 2652 "parser.tab.cc"
    break;

  case 140: // binary_expr: expression TOKEN_PLUS_ASSIGN expression
#line 692 "parser.y"
                                              {
        (yylhs.value.node) = create_assign_op_node((yystack_[2].value.node), OP_ADD_ASSIGN, (yystack_[0].value.node));
    }
#line 2660 "parser.tab.cc"
    break;

  case 141: // binary_expr: expression TOKEN_MINUS_ASSIGN expression
#line 695 "parser.y"
                                               {
        (yylhs.value.node) = create_assign_op_node((yystack_[2].value.node), OP_SUB_ASSIGN, (yystack_[0].value.node));
    }
#line 2668 "parser.tab.cc"
    break;

  case 142: // binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression
#line 698 "parser.y"
                                                  {
        (yylhs.value.node) = create_assign_op_node((yystack_[2].value.node), OP_MUL_ASSIGN, (yystack_[0].value.node));
    }
#line 2676 "parser.tab.cc"
    break;

  case 143: // binary_expr: expression TOKEN_DIVIDE_ASSIGN expression
#line 701 "parser.y"
                                                {
        (yylhs.value.node) = create_assign_op_node((yystack_[2].value.node), OP_DIV_ASSIGN, (yystack_[0].value.node));
    }
#line 2684 "parser.tab.cc"
    break;

  case 144: // binary_expr: expression TOKEN_MODULO_ASSIGN expression
#line 704 "parser.y"
                                                {
        (yylhs.value.node) = create_assign_op_node((yystack_[2].value.node), OP_MOD_ASSIGN, (yystack_[0].value.node));
    }
#line 2692 "parser.tab.cc"
    break;

  case 145: // unary_expr: TOKEN_NOT expression
#line 710 "parser.y"
                         {
        (yylhs.value.node) = create_unary_op(OP_NOT, (yystack_[0].value.node));
    }
#line 2700 "parser.tab.cc"
    break;

  case 146: // unary_expr: TOKEN_MINUS expression
#line 713 "parser.y"
                             {
        (yylhs.value.node) = create_unary_op(OP_NEG, (yystack_[0].value.node));
    }
#line 2708 "parser.tab.cc"
    break;

  case 147: // lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 720 "parser.y"
                                                                     {
        (yylhs.value.node) = create_lambda_node((yystack_[3].value.node_list), (yystack_[1].value.node_list));
    }
#line 2716 "parser.tab.cc"
    break;

  case 148: // lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 723 "parser.y"
                                                                                                 {
        (yylhs.value.node) = create_lambda_node((yystack_[4].value.node_list), (yystack_[1].value.node_list));
    }
#line 2724 "parser.tab.cc"
    break;

  case 149: // array_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET
#line 730 "parser.y"
                                                          {
        (yylhs.value.node) = create_array_access_node((yystack_[3].value.node), (yystack_[1].value.node));
    }
#line 2732 "parser.tab.cc"
    break;

  case 150: // primary_expr: TOKEN_NUMBER
#line 736 "parser.y"
                 {
        (yylhs.value.node) = create_number_node((yystack_[0].value.number));
    }
#line 2740 "parser.tab.cc"
    break;

  case 151: // primary_expr: TOKEN_FLOAT
#line 739 "parser.y"
                  {
        (yylhs.value.node) = create_float_node((yystack_[0].value.float_val));
    }
#line 2748 "parser.tab.cc"
    break;

  case 152: // primary_expr: TOKEN_STRING
#line 742 "parser.y"
                   {
        (yylhs.value.node) = create_string_node((yystack_[0].value.string));
    }
#line 2756 "parser.tab.cc"
    break;

  case 153: // primary_expr: TOKEN_TRUE
#line 745 "parser.y"
                 {
        (yylhs.value.node) = create_bool_node(1);
    }
#line 2764 "parser.tab.cc"
    break;

  case 154: // primary_expr: TOKEN_FALSE
#line 748 "parser.y"
                  {
        (yylhs.value.node) = create_bool_node(0);
    }
#line 2772 "parser.tab.cc"
    break;

  case 155: // primary_expr: TOKEN_NIL
#line 751 "parser.y"
                {
        (yylhs.value.node) = create_nil_node();
    }
#line 2780 "parser.tab.cc"
    break;

  case 156: // primary_expr: TOKEN_IDENTIFIER
#line 754 "parser.y"
                       {
        (yylhs.value.node) = create_identifier_node((yystack_[0].value.string));
    }
#line 2788 "parser.tab.cc"
    break;

  case 157: // primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN
#line 757 "parser.y"
                                           {
        (yylhs.value.node) = (yystack_[1].value.node);
    }
#line 2796 "parser.tab.cc"
    break;

  case 158: // primary_expr: call_expr
#line 760 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2802 "parser.tab.cc"
    break;

  case 159: // primary_expr: dict_access
#line 761 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2808 "parser.tab.cc"
    break;

  case 160: // primary_expr: dict_expr
#line 762 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2814 "parser.tab.cc"
    break;

  case 161: // primary_expr: array_expr
#line 763 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2820 "parser.tab.cc"
    break;

  case 162: // primary_expr: struct_expr
#line 764 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2826 "parser.tab.cc"
    break;

  case 163: // primary_expr: member_access
#line 765 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2832 "parser.tab.cc"
    break;

  case 164: // primary_expr: lambda_expr
#line 766 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2838 "parser.tab.cc"
    break;

  case 165: // primary_expr: array_access
#line 767 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2844 "parser.tab.cc"
    break;

  case 166: // primary_expr: await_expr
#line 768 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2850 "parser.tab.cc"
    break;

  case 167: // primary_expr: sysf_expr
#line 769 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2856 "parser.tab.cc"
    break;

  case 168: // primary_expr: sh_expr
#line 770 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2862 "parser.tab.cc"
    break;

  case 169: // primary_expr: spawn_expr
#line 771 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2868 "parser.tab.cc"
    break;

  case 170: // primary_expr: f_string
#line 772 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2874 "parser.tab.cc"
    break;

  case 171: // f_string: TOKEN_F_STRING
#line 776 "parser.y"
                   {
        (yylhs.value.node) = parse_f_string((yystack_[0].value.string));
    }
#line 2882 "parser.tab.cc"
    break;

  case 172: // member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER
#line 782 "parser.y"
                                            {
        (yylhs.value.node) = create_member_access((yystack_[2].value.node), (yystack_[0].value.string));
    }
#line 2890 "parser.tab.cc"
    break;

  case 173: // member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER
#line 785 "parser.y"
                                                       {
        (yylhs.value.node) = create_static_access((yystack_[2].value.node), (yystack_[0].value.string));
    }
#line 2898 "parser.tab.cc"
    break;

  case 174: // call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN
#line 791 "parser.y"
                                                         {
        (yylhs.value.node) = create_call_node((yystack_[3].value.node), (yystack_[1].value.node_list));
    }
#line 2906 "parser.tab.cc"
    break;

  case 175: // call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN
#line 794 "parser.y"
                                                                                               {
        (yylhs.value.node) = create_method_call_node((yystack_[5].value.node), (yystack_[3].value.string), (yystack_[1].value.node_list));
    }
#line 2914 "parser.tab.cc"
    break;

  case 176: // argument_list: %empty
#line 800 "parser.y"
                {
        (yylhs.value.node_list) = NULL;
    }
#line 2922 "parser.tab.cc"
    break;

  case 177: // argument_list: expression
#line 803 "parser.y"
                 {
        (yylhs.value.node_list) = create_arg_list();
        add_arg((yylhs.value.node_list), (yystack_[0].value.node));
    }
#line 2931 "parser.tab.cc"
    break;

  case 178: // argument_list: argument_list TOKEN_COMMA expression
#line 807 "parser.y"
                                           {
        add_arg((yystack_[2].value.node_list), (yystack_[0].value.node));
        (yylhs.value.node_list) = (yystack_[2].value.node_list);
    }
#line 2940 "parser.tab.cc"
    break;

  case 179: // array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET
#line 814 "parser.y"
                                              {
        (yylhs.value.node) = create_array_node((yystack_[1].value.node_list));
    }
#line 2948 "parser.tab.cc"
    break;

  case 180: // await_expr: TOKEN_AWAIT primary_expr
#line 829 "parser.y"
                             {
        (yylhs.value.node) = create_await_node((yystack_[0].value.node));
    }
#line 2956 "parser.tab.cc"
    break;

  case 181: // await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE
#line 832 "parser.y"
                                                           {
        (yylhs.value.node) = create_await_block_node((yystack_[1].value.node_list));
    }
#line 2964 "parser.tab.cc"
    break;

  case 182: // spawn_expr: TOKEN_SPAWN primary_expr
#line 839 "parser.y"
                             {
        (yylhs.value.node) = create_spawn_node((yystack_[0].value.node));
    }
#line 2972 "parser.tab.cc"
    break;

  case 183: // array_items: %empty
#line 851 "parser.y"
                {
        (yylhs.value.node_list) = NULL;
    }
#line 2980 "parser.tab.cc"
    break;

  case 184: // array_items: expression
#line 854 "parser.y"
                 {
        (yylhs.value.node_list) = create_node_list();
        add_to_node_list((yylhs.value.node_list), (yystack_[0].value.node));
    }
#line 2989 "parser.tab.cc"
    break;

  case 185: // array_items: array_items TOKEN_COMMA expression
#line 858 "parser.y"
                                         {
        add_to_node_list((yystack_[2].value.node_list), (yystack_[0].value.node));
        (yylhs.value.node_list) = (yystack_[2].value.node_list);
    }
#line 2998 "parser.tab.cc"
    break;

  case 186: // struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE
#line 865 "parser.y"
                                                                            {
        (yylhs.value.node) = create_struct_init_node((yystack_[3].value.string), (yystack_[1].value.node_list));
    }
#line 3006 "parser.tab.cc"
    break;

  case 187: // struct_init_fields: %empty
#line 871 "parser.y"
                {
        (yylhs.value.node_list) = NULL;
    }
#line 3014 "parser.tab.cc"
    break;

  case 188: // struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression
#line 874 "parser.y"
                                              {
        (yylhs.value.node_list) = create_node_list();
        add_to_node_list((yylhs.value.node_list), create_field_init_node((yystack_[2].value.string), (yystack_[0].value.node)));
    }
#line 3023 "parser.tab.cc"
    break;

  case 189: // struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression
#line 878 "parser.y"
                                                                             {
        add_to_node_list((yystack_[4].value.node_list), create_field_init_node((yystack_[2].value.string), (yystack_[0].value.node)));
        (yylhs.value.node_list) = (yystack_[4].value.node_list);
    }
#line 3032 "parser.tab.cc"
    break;


#line 3036 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const short parser::yypact_ninf_ = -300;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    2594,   -65,    36,    31,    60,    62,    14,    14,   263,    14,
      89,  -300,  -300,   -49,    80,    81,    91,    92,    93,    14,
    -300,  -300,  -300,    41,    95,   106,    97,    98,   101,    88,
    2724,  2750,     5,    14,    14,   102,  2619,  2699,    14,    14,
     113,    14,    14,  -300,  -300,  -300,  -300,  -300,   103,  2594,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,  3204,  -300,
    -300,  -300,  -300,    19,  -300,  -300,  -300,  -300,  -300,  -300,
    -300,    14,    14,   116,    -2,    83,  3204,  2808,    26,  2827,
    2871,  2594,   -46,   -19,  -300,   117,   -24,   118,   119,  2890,
     121,   136,   137,   234,   152,  2594,   153,    14,  -300,   146,
    2594,    19,    19,   148,   174,    -1,  -300,   341,   132,    44,
      14,  3204,    14,  3204,  2997,  3204,   -55,  2594,  3204,  3204,
    -300,  -300,    14,    14,    14,    14,    14,    14,    14,    14,
      14,    14,    14,    14,    14,    14,    14,    14,    14,    14,
      14,   150,   151,    14,    14,   161,   177,  3078,   164,   148,
      14,    29,    14,  2594,    14,    14,  2594,  2594,   473,   183,
    -300,   157,   -50,   221,  -300,  2594,   160,   162,   165,    11,
     -26,   173,   211,   212,   169,   170,   574,  2594,  3204,   186,
     675,    21,    29,   148,  2594,    14,    29,  3016,  3059,  -300,
      14,  -300,   776,   341,   341,   132,   132,   132,   175,   175,
     175,   175,   175,   175,   163,   163,   265,   265,   265,   265,
     576,   594,   187,  -300,  3204,    43,   369,  -300,    14,    14,
    -300,    45,   491,   178,   195,   226,   491,   877,  2934,  3144,
     978,  1079,  -300,   179,  -300,   180,  -300,   206,   -47,  1180,
     192,   209,   -10,  -300,  -300,     6,    20,  -300,     4,  -300,
    -300,  -300,  -300,   -31,  -300,   207,   148,    14,    14,   197,
     218,    32,  -300,  1281,   148,  -300,   204,  -300,  -300,  1382,
     491,   235,  -300,  -300,  3204,    35,    14,    14,  -300,  -300,
    3111,  3204,   100,    29,  -300,    14,   285,  2594,    14,  -300,
    -300,  -300,  -300,   205,   221,  -300,  -300,   162,    29,   162,
    -300,  -300,   198,  -300,  -300,  -300,  -300,  -300,    14,    47,
     491,   491,   148,    14,   199,  -300,  -300,    79,  2594,  -300,
      14,   213,   214,   208,    84,  3204,    14,    29,  2750,    86,
    -300,   491,   219,  1483,  3174,   210,   231,     8,  -300,  -300,
    -300,  3204,   100,    94,  3204,   250,   100,  1584,   491,   227,
     230,   236,  -300,  -300,  3204,  -300,    19,    14,  2594,  2594,
    -300,    14,  -300,   -14,  -300,   241,   100,    14,   242,  -300,
     244,   245,  2594,  3204,  1685,  1786,  2953,   237,  -300,  2594,
     246,  3204,  2594,   248,   249,  1887,  -300,  -300,  2594,  -300,
    1988,  2594,  2089,  2594,  2594,  -300,  2190,  -300,  2291,  -300,
    2392,  2493,  -300,  -300,  -300,  -300
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,   122,     0,     0,     0,
       0,    91,     6,     0,     0,     0,     0,     0,     0,     0,
     153,   154,   155,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,   183,
       0,     0,     0,   156,   150,   151,   152,   171,     0,     2,
      25,     9,     3,   167,   168,    10,    13,    14,    11,     7,
       8,    15,    16,   160,   159,    20,    22,    23,    21,    24,
      26,    27,    28,    17,    18,    12,    19,    29,    30,   123,
     124,   164,   165,   125,   170,   163,   158,   161,   166,   169,
     162,    74,    74,     0,     0,     0,   121,     0,   156,     0,
       0,     0,     0,    45,    57,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,   116,     0,
       0,   180,   182,    64,    67,     0,    65,   146,   145,     0,
       0,    32,     0,    34,     0,   184,     0,     0,    41,    42,
       1,     4,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,     0,     0,    75,     0,     0,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     0,     0,    51,     0,     0,   107,   113,   118,
       0,     0,     0,     0,     0,   187,     0,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
       0,   179,     0,   126,   127,   128,   129,   130,   139,   140,
     141,   142,   143,   144,   131,   132,   133,   134,   135,   136,
     137,   138,   173,   172,   177,     0,     0,    72,     0,     0,
      73,     0,    82,     0,    69,     0,    87,     0,     0,     0,
       0,     0,    96,     0,    50,     0,    48,     0,     0,     0,
       0,     0,     0,   108,   114,     0,     0,   119,     0,   104,
     103,   101,   102,     0,    98,     0,    64,     0,     0,     0,
       0,     0,     5,     0,    64,   181,     0,    68,    66,     0,
      85,     0,    31,    33,   185,     0,   176,     0,   174,    78,
       0,    76,    79,     0,    70,     0,    89,     0,     0,    93,
      95,    47,    49,     0,     0,    52,    58,   107,     0,     0,
     105,   110,     0,   112,   117,   120,    97,    99,     0,     0,
      84,    88,    64,     0,     0,   186,    35,     0,     0,   147,
       0,     0,     0,    36,     0,   178,     0,     0,     0,     0,
      71,    83,     0,     0,     0,     0,    54,     0,   111,   109,
     115,   100,    79,     0,   188,     0,    79,     0,    86,     0,
       0,     0,    37,   175,    77,    80,    81,     0,     0,     0,
      94,     0,    55,     0,   106,     0,    79,     0,     0,   148,
       0,     0,     0,    63,     0,     0,     0,     0,    53,     0,
       0,   189,     0,     0,     0,     0,    59,    90,     0,    56,
       0,     0,     0,     0,     0,    40,     0,    60,     0,    61,
       0,     0,    92,    62,    38,    39
  };

  const short
  parser::yypgoto_[] =
  {
    -300,  -300,    61,  -300,  -300,    -7,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,    25,  -300,  -300,  -300,
    -185,  -111,   138,  -191,  -300,   251,  -300,  -300,  -299,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,    69,  -300,
    -300,    27,  -255,  -300,  -300,  -300,  -300,  -300,  -300,    -6,
    -300,  -300,  -300,  -300,   -25,  -300,  -300,  -300,    49,  -300,
    -300,  -300,  -300,  -300,  -300
  };

  const short
  parser::yydefgoto_[] =
  {
       0,    48,    49,    50,    51,    52,    53,    54,    55,    56,
     343,   372,    57,    58,    59,   184,   258,   383,    60,    61,
      62,   125,   126,   245,    63,   165,   166,    64,   349,    65,
      66,    67,    68,    69,    70,    71,    72,   273,   274,   275,
      73,   262,   263,    74,   265,    75,    76,   268,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,   235,    87,
      88,    89,   136,    90,   281
  };

  const short
  parser::yytable_[] =
  {
      96,    97,    99,   100,   267,   121,   122,   321,   181,     3,
     182,   287,   201,   109,   269,   291,     3,     1,     2,   269,
     186,   210,   255,   102,    91,   110,   179,   127,   128,   314,
     131,   133,   134,   135,   266,   138,   139,   211,    20,    21,
      22,   266,   141,   315,    29,    24,   110,   111,   112,   170,
     103,    29,   256,   180,   174,    30,    31,    32,   241,   326,
     113,    33,   397,   385,   359,   187,   319,   388,   270,   271,
     183,   272,   171,   270,   271,   203,   272,   175,   398,    34,
     320,   113,   322,   325,   319,   167,   167,   400,   204,   261,
     161,   162,   123,   119,   324,   205,   323,   203,   384,    36,
      37,    38,   321,   140,   124,    39,   163,   261,   334,   286,
     164,   198,   350,    43,    44,    45,    46,    47,   206,   297,
     243,   203,   335,   203,   207,    92,   208,   358,   244,   341,
      93,   298,   342,   302,   172,   362,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   203,   375,   234,   236,    94,
     297,    95,   178,   377,   242,   329,   246,   366,   248,   249,
     203,   141,   373,   337,   347,   378,   196,   348,   101,   104,
     105,   200,   386,   147,   148,   149,   150,   151,   152,   141,
     106,   107,   108,   141,   114,   115,   116,   117,   212,   290,
     118,   129,   137,   169,   294,   141,   185,   188,   189,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     191,   363,   155,   156,   157,   158,    -1,    -1,    -1,    -1,
      -1,    -1,   300,   301,   247,   192,   193,   250,   251,   194,
     141,   195,   197,   141,   141,   199,   259,   124,   202,   232,
     233,   237,   141,   238,   240,   253,   254,   257,   283,   260,
     276,   261,   277,   278,   264,   289,     1,     2,   279,   280,
     303,   330,   331,   284,   296,   304,   141,   305,   311,   312,
     313,   317,   141,   318,   332,   328,   340,    20,    21,    22,
     234,   345,   333,   338,    24,   352,   355,   360,   365,   351,
     369,   370,   354,   371,    30,    31,    32,   314,   379,   382,
      33,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   361,   376,   387,   392,   390,   364,    34,   391,
     399,   402,   403,   404,   368,   411,   409,   413,   414,   356,
     374,   288,   327,   168,   357,   344,   141,     0,    36,    37,
      38,     0,     0,     0,    39,     0,     0,     0,     0,     0,
     141,     0,    98,    44,    45,    46,    47,     0,   353,     0,
       0,   393,     0,     0,     0,   396,     0,     0,     0,     0,
       0,   401,     0,     0,     0,     0,     0,   141,   141,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   141,   367,
       0,     0,     0,   141,     0,   141,     0,     0,     0,   141,
       0,   141,     0,   141,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,     0,     0,     0,     0,     0,   394,
     395,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   405,     0,     0,     0,     0,     0,     0,
     410,   299,     0,   412,     0,     0,     0,     0,     0,   416,
       0,     0,   418,     0,   420,   421,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   142,    34,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,     0,    35,    36,    37,
      38,     0,     0,   252,    39,     0,    40,     0,     0,    41,
       0,    42,    43,    44,    45,    46,    47,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
       0,    33,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,    34,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,    35,    36,
      37,    38,     0,     0,   282,    39,     0,    40,     0,     0,
      41,     0,    42,    43,    44,    45,    46,    47,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,    37,    38,     0,     0,   285,    39,     0,    40,     0,
       0,    41,     0,    42,    43,    44,    45,    46,    47,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,    38,     0,     0,   295,    39,     0,    40,
       0,     0,    41,     0,    42,    43,    44,    45,    46,    47,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    36,    37,    38,     0,     0,   306,    39,     0,
      40,     0,     0,    41,     0,    42,    43,    44,    45,    46,
      47,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,    37,    38,     0,     0,   309,    39,
       0,    40,     0,     0,    41,     0,    42,    43,    44,    45,
      46,    47,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,    36,    37,    38,     0,     0,   310,
      39,     0,    40,     0,     0,    41,     0,    42,    43,    44,
      45,    46,    47,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    37,    38,     0,     0,
     316,    39,     0,    40,     0,     0,    41,     0,    42,    43,
      44,    45,    46,    47,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    36,    37,    38,     0,
       0,   336,    39,     0,    40,     0,     0,    41,     0,    42,
      43,    44,    45,    46,    47,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,    37,    38,
       0,     0,   339,    39,     0,    40,     0,     0,    41,     0,
      42,    43,    44,    45,    46,    47,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    36,    37,
      38,     0,     0,   380,    39,     0,    40,     0,     0,    41,
       0,    42,    43,    44,    45,    46,    47,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     0,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,    36,
      37,    38,     0,     0,   389,    39,     0,    40,     0,     0,
      41,     0,    42,    43,    44,    45,    46,    47,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,    20,
      21,    22,     0,     0,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,    29,    30,    31,    32,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,    37,    38,     0,     0,   406,    39,     0,    40,     0,
       0,    41,     0,    42,    43,    44,    45,    46,    47,     1,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
      20,    21,    22,     0,     0,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,    29,    30,    31,    32,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,    38,     0,     0,   407,    39,     0,    40,
       0,     0,    41,     0,    42,    43,    44,    45,    46,    47,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,    20,    21,    22,     0,     0,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,    29,    30,    31,
      32,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    36,    37,    38,     0,     0,   415,    39,     0,
      40,     0,     0,    41,     0,    42,    43,    44,    45,    46,
      47,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,    20,    21,    22,     0,     0,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,    37,    38,     0,     0,   417,    39,
       0,    40,     0,     0,    41,     0,    42,    43,    44,    45,
      46,    47,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,    20,    21,    22,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,    29,
      30,    31,    32,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,    36,    37,    38,     0,     0,   419,
      39,     0,    40,     0,     0,    41,     0,    42,    43,    44,
      45,    46,    47,     1,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,    20,    21,    22,     0,     0,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
      29,    30,    31,    32,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    37,    38,     0,     0,
     422,    39,     0,    40,     0,     0,    41,     0,    42,    43,
      44,    45,    46,    47,     1,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     0,    20,    21,    22,     0,     0,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,    29,    30,    31,    32,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    36,    37,    38,     0,
       0,   423,    39,     0,    40,     0,     0,    41,     0,    42,
      43,    44,    45,    46,    47,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,    20,    21,    22,     0,
       0,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,    29,    30,    31,    32,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,    37,    38,
       0,     0,   424,    39,     0,    40,     0,     0,    41,     0,
      42,    43,    44,    45,    46,    47,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,     0,    20,    21,    22,
       0,     0,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,    29,    30,    31,    32,     0,     0,     0,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    36,    37,
      38,     0,     0,   425,    39,     0,    40,     0,     0,    41,
       0,    42,    43,    44,    45,    46,    47,     1,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     0,    20,    21,
      22,     0,     1,     2,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,    29,    30,    31,    32,     0,     0,
       0,    33,     0,    20,    21,    22,     0,     0,     0,     0,
      24,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      30,    31,    32,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,    36,
      37,    38,     0,     0,    34,    39,     0,    40,     0,     0,
      41,     0,    42,    43,    44,    45,    46,    47,     0,     0,
       0,     0,     1,     2,    36,    37,   130,     0,     0,     0,
      39,     0,     0,     0,     0,     0,     0,     0,    43,    44,
      45,    46,    47,    20,    21,    22,     0,     1,     2,     0,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      30,    31,    32,     0,     0,     0,    33,     0,    20,    21,
      22,     0,     0,     1,     2,    24,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    30,    31,    32,     0,     0,
       0,     0,     0,     0,    20,    21,    22,     0,     0,     0,
       0,    24,     0,     0,    36,    37,   132,     0,     0,     0,
      39,    30,    31,    32,     0,     0,     0,     0,    43,    44,
      45,    46,    47,     0,     0,     0,     0,     0,     0,    36,
      37,    38,     0,   120,     0,    39,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    38,     0,     0,
       0,    39,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,     0,     0,     0,     0,     0,   173,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,     0,     0,     0,     0,     0,
     177,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   190,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,     0,     0,
       0,     0,     0,   307,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   408,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,     0,     0,     0,     0,   209,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   292,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,     0,     0,     0,     0,   293,     0,     0,
       0,     0,     0,     0,     0,     0,   239,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   346,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   308,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   381,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160
  };

  const short
  parser::yycheck_[] =
  {
       6,     7,     8,     9,   189,    30,    31,   262,    27,     5,
      29,   202,   123,    19,    45,   206,     5,     3,     4,    45,
      44,    76,    72,    72,    89,     5,    72,    33,    34,    76,
      36,    37,    38,    39,    30,    41,    42,    92,    24,    25,
      26,    30,    49,    90,    40,    31,     5,     6,     7,    51,
      99,    40,   102,    99,    28,    41,    42,    43,   169,    90,
      40,    47,    76,   362,   319,    89,    76,   366,    99,   100,
      89,   102,    74,    99,   100,    76,   102,    51,    92,    65,
      90,    40,    76,   268,    76,    91,    92,   386,    89,    99,
      71,    72,    87,     5,    90,    51,    90,    76,    90,    85,
      86,    87,   357,     0,    99,    91,    87,    99,    76,    88,
      91,   117,   303,    99,   100,   101,   102,   103,    74,    76,
      91,    76,    90,    76,   130,    89,   132,   318,    99,    94,
      99,    88,    97,    88,    51,    88,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,    76,   347,   163,   164,    99,
      76,    99,   101,    77,   170,   276,   172,    88,   174,   175,
      76,   178,    88,   284,    74,    89,   115,    77,    89,    99,
      99,   120,    88,    51,    52,    53,    54,    55,    56,   196,
      99,    99,    99,   200,    99,    89,    99,    99,   137,   205,
      99,    99,    89,    87,   210,   212,    89,    89,    89,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      99,   332,    59,    60,    61,    62,    51,    52,    53,    54,
      55,    56,   238,   239,   173,    99,    99,   176,   177,     5,
     247,    89,    89,   250,   251,    99,   185,    99,    74,    99,
      99,    90,   259,    76,    90,    72,    99,    36,   197,    99,
      87,    99,    51,    51,    99,   204,     3,     4,    99,    99,
      92,   277,   278,    87,    87,    80,   283,    51,    99,    99,
      74,    89,   289,    74,    87,    78,    51,    24,    25,    26,
     296,   297,    74,    89,    31,    10,    91,    99,    99,   305,
      87,    87,   308,    95,    41,    42,    43,    76,    89,    99,
      47,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,   328,   348,    74,    89,    99,   333,    65,    99,
      89,    89,    88,    88,   340,    89,    99,    89,    89,   314,
     346,   203,   273,    92,   317,   296,   353,    -1,    85,    86,
      87,    -1,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,
     367,    -1,    99,   100,   101,   102,   103,    -1,   307,    -1,
      -1,   377,    -1,    -1,    -1,   381,    -1,    -1,    -1,    -1,
      -1,   387,    -1,    -1,    -1,    -1,    -1,   394,   395,    48,
      49,    50,    51,    52,    53,    54,    55,    56,   405,   338,
      -1,    -1,    -1,   410,    -1,   412,    -1,    -1,    -1,   416,
      -1,   418,    -1,   420,   421,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,   378,
     379,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   392,    -1,    -1,    -1,    -1,    -1,    -1,
     399,    92,    -1,   402,    -1,    -1,    -1,    -1,    -1,   408,
      -1,    -1,   411,    -1,   413,   414,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    65,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    84,    85,    86,
      87,    -1,    -1,    90,    91,    -1,    93,    -1,    -1,    96,
      -1,    98,    99,   100,   101,   102,   103,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    65,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    84,    85,
      86,    87,    -1,    -1,    90,    91,    -1,    93,    -1,    -1,
      96,    -1,    98,    99,   100,   101,   102,   103,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    86,    87,    -1,    -1,    90,    91,    -1,    93,    -1,
      -1,    96,    -1,    98,    99,   100,   101,   102,   103,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    -1,    -1,    90,    91,    -1,    93,
      -1,    -1,    96,    -1,    98,    99,   100,   101,   102,   103,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    86,    87,    -1,    -1,    90,    91,    -1,
      93,    -1,    -1,    96,    -1,    98,    99,   100,   101,   102,
     103,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    -1,    -1,    90,    91,
      -1,    93,    -1,    -1,    96,    -1,    98,    99,   100,   101,
     102,   103,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    86,    87,    -1,    -1,    90,
      91,    -1,    93,    -1,    -1,    96,    -1,    98,    99,   100,
     101,   102,   103,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    -1,    -1,
      90,    91,    -1,    93,    -1,    -1,    96,    -1,    98,    99,
     100,   101,   102,   103,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    90,    91,    -1,    93,    -1,    -1,    96,    -1,    98,
      99,   100,   101,   102,   103,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      -1,    -1,    90,    91,    -1,    93,    -1,    -1,    96,    -1,
      98,    99,   100,   101,   102,   103,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,
      87,    -1,    -1,    90,    91,    -1,    93,    -1,    -1,    96,
      -1,    98,    99,   100,   101,   102,   103,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    -1,    -1,    90,    91,    -1,    93,    -1,    -1,
      96,    -1,    98,    99,   100,   101,   102,   103,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    86,    87,    -1,    -1,    90,    91,    -1,    93,    -1,
      -1,    96,    -1,    98,    99,   100,   101,   102,   103,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    -1,    -1,    90,    91,    -1,    93,
      -1,    -1,    96,    -1,    98,    99,   100,   101,   102,   103,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    86,    87,    -1,    -1,    90,    91,    -1,
      93,    -1,    -1,    96,    -1,    98,    99,   100,   101,   102,
     103,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    -1,    -1,    90,    91,
      -1,    93,    -1,    -1,    96,    -1,    98,    99,   100,   101,
     102,   103,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    86,    87,    -1,    -1,    90,
      91,    -1,    93,    -1,    -1,    96,    -1,    98,    99,   100,
     101,   102,   103,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    -1,    -1,
      90,    91,    -1,    93,    -1,    -1,    96,    -1,    98,    99,
     100,   101,   102,   103,     3,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    90,    91,    -1,    93,    -1,    -1,    96,    -1,    98,
      99,   100,   101,   102,   103,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      -1,    -1,    90,    91,    -1,    93,    -1,    -1,    96,    -1,
      98,    99,   100,   101,   102,   103,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,
      87,    -1,    -1,    90,    91,    -1,    93,    -1,    -1,    96,
      -1,    98,    99,   100,   101,   102,   103,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    -1,     3,     4,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    24,    25,    26,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    -1,    -1,    65,    91,    -1,    93,    -1,    -1,
      96,    -1,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,     3,     4,    85,    86,    87,    -1,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,
     101,   102,   103,    24,    25,    26,    -1,     3,     4,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    47,    -1,    24,    25,
      26,    -1,    -1,     3,     4,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,
      91,    41,    42,    43,    -1,    -1,    -1,    -1,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    87,    -1,    89,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    87,    -1,    -1,
      -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,
     100,   101,   102,   103,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      24,    25,    26,    30,    31,    32,    33,    34,    35,    40,
      41,    42,    43,    47,    65,    84,    85,    86,    87,    91,
      93,    96,    98,    99,   100,   101,   102,   103,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   116,   117,   118,
     122,   123,   124,   128,   131,   133,   134,   135,   136,   137,
     138,   139,   140,   144,   147,   149,   150,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   163,   164,   165,
     167,    89,    89,    99,    99,    99,   153,   153,    99,   153,
     153,    89,    72,    99,    99,    99,    99,    99,    99,   153,
       5,     6,     7,    40,    99,    89,    99,    99,    99,     5,
      89,   158,   158,    87,    99,   125,   126,   153,   153,    99,
      87,   153,    87,   153,   153,   153,   166,    89,   153,   153,
       0,   109,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    71,    72,    87,    91,   129,   130,   153,   129,    87,
      51,    74,    51,    89,    28,    51,    89,    89,   106,    72,
      99,    27,    29,    89,   119,    89,    44,    89,    89,    89,
      89,    99,    99,    99,     5,    89,   106,    89,   153,    99,
     106,   125,    74,    76,    89,    51,    74,   153,   153,    88,
      76,    92,   106,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,    99,    99,   153,   162,   153,    90,    76,    78,
      90,   125,   153,    91,    99,   127,   153,   106,   153,   153,
     106,   106,    90,    72,    99,    72,   102,    36,   120,   106,
      99,    99,   145,   146,    99,   148,    30,   124,   151,    45,
      99,   100,   102,   141,   142,   143,    87,    51,    51,    99,
      99,   168,    90,   106,    87,    90,    88,   127,   126,   106,
     153,   127,    88,    88,   153,    90,    87,    76,    88,    92,
     153,   153,    88,    92,    80,    51,    90,    89,    75,    90,
      90,    99,    99,    74,    76,    90,    90,    89,    74,    76,
      90,   146,    76,    90,    90,   124,    90,   142,    78,   125,
     153,   153,    87,    74,    76,    90,    90,   125,    89,    90,
      51,    94,    97,   114,   162,   153,    78,    74,    77,   132,
     127,   153,    10,   106,   153,    91,   120,   145,   127,   146,
      99,   153,    88,   125,   153,    99,    88,   106,   153,    87,
      87,    95,   115,    88,   153,   127,   158,    77,    89,    89,
      90,    75,    99,   121,    90,   132,    88,    74,   132,    90,
      99,    99,    89,   153,   106,   106,   153,    76,    92,    89,
     132,   153,    89,    88,    88,   106,    90,    90,    89,    99,
     106,    89,   106,    89,    89,    90,   106,    90,   106,    90,
     106,   106,    90,    90,    90,    90
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   104,   105,   106,   106,   107,   108,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   110,   110,   111,   111,   112,   113,   113,   114,   114,
     115,   116,   116,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   119,   120,   120,   121,   121,   122,   123,   124,
     124,   124,   124,   124,   125,   125,   125,   126,   126,   127,
     127,   127,   128,   128,   129,   129,   130,   130,   131,   132,
     132,   132,   133,   133,   133,   133,   133,   134,   134,   135,
     135,   136,   137,   137,   137,   138,   139,   140,   141,   141,
     142,   143,   143,   143,   143,   144,   144,   145,   145,   145,
     145,   146,   147,   148,   148,   148,   149,   150,   151,   151,
     151,   152,   152,   153,   153,   153,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   155,   155,   156,   156,   157,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   159,   160,   160,   161,   161,   162,   162,   162,   163,
     164,   164,   165,   166,   166,   166,   167,   168,   168,   168
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     2,     4,     2,     5,     5,     6,     7,     7,
       4,     2,     2,     2,     3,     2,     3,     5,     4,     5,
       4,     3,     3,     5,     3,     1,     3,     2,     5,     9,
      10,    10,    11,     8,     0,     1,     3,     1,     3,     1,
       2,     3,     4,     4,     0,     1,     3,     5,     4,     0,
       2,     2,     4,     6,     5,     4,     6,     4,     5,     5,
       9,     1,    11,     5,     7,     5,     4,     5,     1,     2,
       3,     1,     1,     1,     1,     5,     7,     0,     1,     3,
       2,     3,     5,     0,     1,     3,     2,     5,     0,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     5,     7,     4,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     4,     6,     0,     1,     3,     3,
       2,     4,     2,     0,     1,     3,     5,     0,     3,     5
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
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
  "TOKEN_RANGE_INC", "TOKEN_MUTS", "TOKEN_SYSF", "TOKEN_SH",
  "TOKEN_LPAREN", "TOKEN_RPAREN", "TOKEN_LBRACE", "TOKEN_RBRACE",
  "TOKEN_LBRACKET", "TOKEN_RBRACKET", "TOKEN_TRY", "TOKEN_CATCH",
  "TOKEN_FINALLY", "TOKEN_THROW", "TOKEN_EXCEPT", "TOKEN_RAISE",
  "TOKEN_IDENTIFIER", "TOKEN_NUMBER", "TOKEN_FLOAT", "TOKEN_STRING",
  "TOKEN_F_STRING", "$accept", "program", "statement_list", "unsafe_stmt",
  "continue_statement", "statement", "sysf_expr", "sh_expr",
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
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   112,   112,   118,   122,   128,   133,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   168,   171,   177,   180,   186,   192,   195,   201,   204,
     210,   216,   219,   224,   227,   233,   236,   242,   248,   252,
     258,   261,   267,   273,   276,   282,   286,   293,   299,   305,
     308,   311,   317,   324,   333,   336,   340,   347,   350,   356,
     359,   362,   370,   373,   379,   382,   388,   393,   402,   421,
     424,   427,   434,   437,   440,   446,   449,   454,   457,   466,
     469,   474,   479,   485,   488,   504,   510,   517,   523,   527,
     534,   540,   543,   546,   549,   555,   558,   564,   567,   571,
     575,   582,   588,   594,   597,   601,   608,   615,   621,   624,
     628,   635,   638,   644,   645,   646,   650,   653,   656,   659,
     662,   665,   668,   671,   674,   677,   680,   683,   686,   689,
     692,   695,   698,   701,   704,   710,   713,   720,   723,   730,
     736,   739,   742,   745,   748,   751,   754,   757,   760,   761,
     762,   763,   764,   765,   766,   767,   768,   769,   770,   771,
     772,   776,   782,   785,   791,   794,   800,   803,   807,   814,
     829,   832,   839,   851,   854,   858,   865,   871,   874,   878
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
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
      95,    96,    97,    98,    99,   100,   101,   102,   103
    };
    // Last valid token kind.
    const int code_max = 358;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 4266 "parser.tab.cc"

#line 890 "parser.y"


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

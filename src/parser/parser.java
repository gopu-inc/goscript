/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Skeleton implementation for Bison LALR(1) parsers in Java

   Copyright (C) 2007-2015, 2018-2021 Free Software Foundation, Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */


/* First part of user prologue.  */
/* "parser.y":1  */

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

/* "parser.java":55  */


import java.text.MessageFormat;

/**
 * A Bison parser, automatically generated from <tt>parser.y</tt>.
 *
 * @author LALR (1) parser skeleton written by Paolo Bonzini.
 */
class YYParser
{
  /** Version number for the Bison executable that generated this parser.  */
  public static final String bisonVersion = "3.7.6";

  /** Name of the skeleton that generated this parser.  */
  public static final String bisonSkeleton = "lalr1.java";






  public enum SymbolKind
  {
    S_YYEOF(0),                    /* "end of file"  */
    S_YYerror(1),                  /* error  */
    S_YYUNDEF(2),                  /* "invalid token"  */
    S_TOKEN_DICT(3),               /* TOKEN_DICT  */
    S_TOKEN_MAP(4),                /* TOKEN_MAP  */
    S_TOKEN_FN(5),                 /* TOKEN_FN  */
    S_TOKEN_LET(6),                /* TOKEN_LET  */
    S_TOKEN_CONST(7),              /* TOKEN_CONST  */
    S_TOKEN_RETURN(8),             /* TOKEN_RETURN  */
    S_TOKEN_IF(9),                 /* TOKEN_IF  */
    S_TOKEN_ELSE(10),              /* TOKEN_ELSE  */
    S_TOKEN_FOR(11),               /* TOKEN_FOR  */
    S_TOKEN_WHILE(12),             /* TOKEN_WHILE  */
    S_TOKEN_LOOP(13),              /* TOKEN_LOOP  */
    S_TOKEN_BREAK(14),             /* TOKEN_BREAK  */
    S_TOKEN_CONTINUE(15),          /* TOKEN_CONTINUE  */
    S_TOKEN_IMPORT(16),            /* TOKEN_IMPORT  */
    S_TOKEN_EXPORT(17),            /* TOKEN_EXPORT  */
    S_TOKEN_PACKET(18),            /* TOKEN_PACKET  */
    S_TOKEN_STRUCT(19),            /* TOKEN_STRUCT  */
    S_TOKEN_ENUM(20),              /* TOKEN_ENUM  */
    S_TOKEN_IMPL(21),              /* TOKEN_IMPL  */
    S_TOKEN_MATCH(22),             /* TOKEN_MATCH  */
    S_TOKEN_TYPE(23),              /* TOKEN_TYPE  */
    S_TOKEN_TRUE(24),              /* TOKEN_TRUE  */
    S_TOKEN_FALSE(25),             /* TOKEN_FALSE  */
    S_TOKEN_NIL(26),               /* TOKEN_NIL  */
    S_TOKEN_AS(27),                /* TOKEN_AS  */
    S_TOKEN_IN(28),                /* TOKEN_IN  */
    S_TOKEN_FROM(29),              /* TOKEN_FROM  */
    S_TOKEN_PUB(30),               /* TOKEN_PUB  */
    S_TOKEN_NEW(31),               /* TOKEN_NEW  */
    S_TOKEN_UNSAFE(32),            /* TOKEN_UNSAFE  */
    S_TOKEN_NNL(33),               /* TOKEN_NNL  */
    S_TOKEN_JMP(34),               /* TOKEN_JMP  */
    S_TOKEN_MODULE(35),            /* TOKEN_MODULE  */
    S_TOKEN_ONLY(36),              /* TOKEN_ONLY  */
    S_TOKEN_TIMEOUT(37),           /* TOKEN_TIMEOUT  */
    S_TOKEN_SANDBOX(38),           /* TOKEN_SANDBOX  */
    S_TOKEN_ALLOW_FFI(39),         /* TOKEN_ALLOW_FFI  */
    S_TOKEN_ASYNC(40),             /* TOKEN_ASYNC  */
    S_TOKEN_AWAIT(41),             /* TOKEN_AWAIT  */
    S_TOKEN_SPAWN(42),             /* TOKEN_SPAWN  */
    S_TOKEN_LAMBDA(43),            /* TOKEN_LAMBDA  */
    S_TOKEN_EXTENDS(44),           /* TOKEN_EXTENDS  */
    S_TOKEN_UNDERSCORE(45),        /* TOKEN_UNDERSCORE  */
    S_TOKEN_PLUS(46),              /* TOKEN_PLUS  */
    S_TOKEN_MINUS(47),             /* TOKEN_MINUS  */
    S_TOKEN_MULTIPLY(48),          /* TOKEN_MULTIPLY  */
    S_TOKEN_DIVIDE(49),            /* TOKEN_DIVIDE  */
    S_TOKEN_MODULO(50),            /* TOKEN_MODULO  */
    S_TOKEN_ASSIGN(51),            /* TOKEN_ASSIGN  */
    S_TOKEN_PLUS_ASSIGN(52),       /* TOKEN_PLUS_ASSIGN  */
    S_TOKEN_MINUS_ASSIGN(53),      /* TOKEN_MINUS_ASSIGN  */
    S_TOKEN_MULTIPLY_ASSIGN(54),   /* TOKEN_MULTIPLY_ASSIGN  */
    S_TOKEN_DIVIDE_ASSIGN(55),     /* TOKEN_DIVIDE_ASSIGN  */
    S_TOKEN_MODULO_ASSIGN(56),     /* TOKEN_MODULO_ASSIGN  */
    S_TOKEN_EQ(57),                /* TOKEN_EQ  */
    S_TOKEN_NEQ(58),               /* TOKEN_NEQ  */
    S_TOKEN_LT(59),                /* TOKEN_LT  */
    S_TOKEN_LTE(60),               /* TOKEN_LTE  */
    S_TOKEN_GT(61),                /* TOKEN_GT  */
    S_TOKEN_GTE(62),               /* TOKEN_GTE  */
    S_TOKEN_AND(63),               /* TOKEN_AND  */
    S_TOKEN_OR(64),                /* TOKEN_OR  */
    S_TOKEN_NOT(65),               /* TOKEN_NOT  */
    S_TOKEN_AMP(66),               /* TOKEN_AMP  */
    S_TOKEN_PIPE(67),              /* TOKEN_PIPE  */
    S_TOKEN_XOR(68),               /* TOKEN_XOR  */
    S_TOKEN_LSHIFT(69),            /* TOKEN_LSHIFT  */
    S_TOKEN_RSHIFT(70),            /* TOKEN_RSHIFT  */
    S_TOKEN_DOUBLE_COLON(71),      /* TOKEN_DOUBLE_COLON  */
    S_TOKEN_DOT(72),               /* TOKEN_DOT  */
    S_TOKEN_SECURITY(73),          /* TOKEN_SECURITY  */
    S_TOKEN_COLON(74),             /* TOKEN_COLON  */
    S_TOKEN_SEMICOLON(75),         /* TOKEN_SEMICOLON  */
    S_TOKEN_COMMA(76),             /* TOKEN_COMMA  */
    S_TOKEN_ARROW(77),             /* TOKEN_ARROW  */
    S_TOKEN_FAT_ARROW(78),         /* TOKEN_FAT_ARROW  */
    S_TOKEN_PIPE_FORWARD(79),      /* TOKEN_PIPE_FORWARD  */
    S_TOKEN_OPTIONAL(80),          /* TOKEN_OPTIONAL  */
    S_TOKEN_COALESCE(81),          /* TOKEN_COALESCE  */
    S_TOKEN_RANGE(82),             /* TOKEN_RANGE  */
    S_TOKEN_RANGE_INC(83),         /* TOKEN_RANGE_INC  */
    S_TOKEN_MUTS(84),              /* TOKEN_MUTS  */
    S_TOKEN_SYSF(85),              /* TOKEN_SYSF  */
    S_TOKEN_SH(86),                /* TOKEN_SH  */
    S_TOKEN_LPAREN(87),            /* TOKEN_LPAREN  */
    S_TOKEN_RPAREN(88),            /* TOKEN_RPAREN  */
    S_TOKEN_LBRACE(89),            /* TOKEN_LBRACE  */
    S_TOKEN_RBRACE(90),            /* TOKEN_RBRACE  */
    S_TOKEN_LBRACKET(91),          /* TOKEN_LBRACKET  */
    S_TOKEN_RBRACKET(92),          /* TOKEN_RBRACKET  */
    S_TOKEN_TRY(93),               /* TOKEN_TRY  */
    S_TOKEN_CATCH(94),             /* TOKEN_CATCH  */
    S_TOKEN_FINALLY(95),           /* TOKEN_FINALLY  */
    S_TOKEN_THROW(96),             /* TOKEN_THROW  */
    S_TOKEN_EXCEPT(97),            /* TOKEN_EXCEPT  */
    S_TOKEN_RAISE(98),             /* TOKEN_RAISE  */
    S_TOKEN_IDENTIFIER(99),        /* TOKEN_IDENTIFIER  */
    S_TOKEN_NUMBER(100),           /* TOKEN_NUMBER  */
    S_TOKEN_FLOAT(101),            /* TOKEN_FLOAT  */
    S_TOKEN_STRING(102),           /* TOKEN_STRING  */
    S_TOKEN_F_STRING(103),         /* TOKEN_F_STRING  */
    S_YYACCEPT(104),               /* $accept  */
    S_program(105),                /* program  */
    S_statement_list(106),         /* statement_list  */
    S_unsafe_stmt(107),            /* unsafe_stmt  */
    S_continue_statement(108),     /* continue_statement  */
    S_statement(109),              /* statement  */
    S_sysf_expr(110),              /* sysf_expr  */
    S_sh_expr(111),                /* sh_expr  */
    S_nnl_statement(112),          /* nnl_statement  */
    S_try_statement(113),          /* try_statement  */
    S_catch_block(114),            /* catch_block  */
    S_finally_block(115),          /* finally_block  */
    S_throw_statement(116),        /* throw_statement  */
    S_jmp_statement(117),          /* jmp_statement  */
    S_import_statement(118),       /* import_statement  */
    S_import_constraints(119),     /* import_constraints  */
    S_import_options(120),         /* import_options  */
    S_name_list(121),              /* name_list  */
    S_export_statement(122),       /* export_statement  */
    S_packet_decl(123),            /* packet_decl  */
    S_function_decl(124),          /* function_decl  */
    S_param_list(125),             /* param_list  */
    S_param(126),                  /* param  */
    S_type(127),                   /* type  */
    S_dict_expr(128),              /* dict_expr  */
    S_dict_entries(129),           /* dict_entries  */
    S_dict_entry_list(130),        /* dict_entry_list  */
    S_dict_access(131),            /* dict_access  */
    S_return_type(132),            /* return_type  */
    S_let_decl(133),               /* let_decl  */
    S_const_decl(134),             /* const_decl  */
    S_if_statement(135),           /* if_statement  */
    S_break_statement(136),        /* break_statement  */
    S_for_statement(137),          /* for_statement  */
    S_while_statement(138),        /* while_statement  */
    S_loop_statement(139),         /* loop_statement  */
    S_match_statement(140),        /* match_statement  */
    S_match_cases(141),            /* match_cases  */
    S_match_case(142),             /* match_case  */
    S_pattern(143),                /* pattern  */
    S_struct_decl(144),            /* struct_decl  */
    S_struct_fields(145),          /* struct_fields  */
    S_struct_field(146),           /* struct_field  */
    S_enum_decl(147),              /* enum_decl  */
    S_enum_variants(148),          /* enum_variants  */
    S_module_decl(149),            /* module_decl  */
    S_impl_decl(150),              /* impl_decl  */
    S_function_decl_list(151),     /* function_decl_list  */
    S_return_statement(152),       /* return_statement  */
    S_expression(153),             /* expression  */
    S_binary_expr(154),            /* binary_expr  */
    S_unary_expr(155),             /* unary_expr  */
    S_lambda_expr(156),            /* lambda_expr  */
    S_array_access(157),           /* array_access  */
    S_primary_expr(158),           /* primary_expr  */
    S_f_string(159),               /* f_string  */
    S_member_access(160),          /* member_access  */
    S_call_expr(161),              /* call_expr  */
    S_argument_list(162),          /* argument_list  */
    S_array_expr(163),             /* array_expr  */
    S_await_expr(164),             /* await_expr  */
    S_spawn_expr(165),             /* spawn_expr  */
    S_array_items(166),            /* array_items  */
    S_struct_expr(167),            /* struct_expr  */
    S_struct_init_fields(168);     /* struct_init_fields  */


    private final int yycode_;

    SymbolKind (int n) {
      this.yycode_ = n;
    }

    private static final SymbolKind[] values_ = {
      SymbolKind.S_YYEOF,
      SymbolKind.S_YYerror,
      SymbolKind.S_YYUNDEF,
      SymbolKind.S_TOKEN_DICT,
      SymbolKind.S_TOKEN_MAP,
      SymbolKind.S_TOKEN_FN,
      SymbolKind.S_TOKEN_LET,
      SymbolKind.S_TOKEN_CONST,
      SymbolKind.S_TOKEN_RETURN,
      SymbolKind.S_TOKEN_IF,
      SymbolKind.S_TOKEN_ELSE,
      SymbolKind.S_TOKEN_FOR,
      SymbolKind.S_TOKEN_WHILE,
      SymbolKind.S_TOKEN_LOOP,
      SymbolKind.S_TOKEN_BREAK,
      SymbolKind.S_TOKEN_CONTINUE,
      SymbolKind.S_TOKEN_IMPORT,
      SymbolKind.S_TOKEN_EXPORT,
      SymbolKind.S_TOKEN_PACKET,
      SymbolKind.S_TOKEN_STRUCT,
      SymbolKind.S_TOKEN_ENUM,
      SymbolKind.S_TOKEN_IMPL,
      SymbolKind.S_TOKEN_MATCH,
      SymbolKind.S_TOKEN_TYPE,
      SymbolKind.S_TOKEN_TRUE,
      SymbolKind.S_TOKEN_FALSE,
      SymbolKind.S_TOKEN_NIL,
      SymbolKind.S_TOKEN_AS,
      SymbolKind.S_TOKEN_IN,
      SymbolKind.S_TOKEN_FROM,
      SymbolKind.S_TOKEN_PUB,
      SymbolKind.S_TOKEN_NEW,
      SymbolKind.S_TOKEN_UNSAFE,
      SymbolKind.S_TOKEN_NNL,
      SymbolKind.S_TOKEN_JMP,
      SymbolKind.S_TOKEN_MODULE,
      SymbolKind.S_TOKEN_ONLY,
      SymbolKind.S_TOKEN_TIMEOUT,
      SymbolKind.S_TOKEN_SANDBOX,
      SymbolKind.S_TOKEN_ALLOW_FFI,
      SymbolKind.S_TOKEN_ASYNC,
      SymbolKind.S_TOKEN_AWAIT,
      SymbolKind.S_TOKEN_SPAWN,
      SymbolKind.S_TOKEN_LAMBDA,
      SymbolKind.S_TOKEN_EXTENDS,
      SymbolKind.S_TOKEN_UNDERSCORE,
      SymbolKind.S_TOKEN_PLUS,
      SymbolKind.S_TOKEN_MINUS,
      SymbolKind.S_TOKEN_MULTIPLY,
      SymbolKind.S_TOKEN_DIVIDE,
      SymbolKind.S_TOKEN_MODULO,
      SymbolKind.S_TOKEN_ASSIGN,
      SymbolKind.S_TOKEN_PLUS_ASSIGN,
      SymbolKind.S_TOKEN_MINUS_ASSIGN,
      SymbolKind.S_TOKEN_MULTIPLY_ASSIGN,
      SymbolKind.S_TOKEN_DIVIDE_ASSIGN,
      SymbolKind.S_TOKEN_MODULO_ASSIGN,
      SymbolKind.S_TOKEN_EQ,
      SymbolKind.S_TOKEN_NEQ,
      SymbolKind.S_TOKEN_LT,
      SymbolKind.S_TOKEN_LTE,
      SymbolKind.S_TOKEN_GT,
      SymbolKind.S_TOKEN_GTE,
      SymbolKind.S_TOKEN_AND,
      SymbolKind.S_TOKEN_OR,
      SymbolKind.S_TOKEN_NOT,
      SymbolKind.S_TOKEN_AMP,
      SymbolKind.S_TOKEN_PIPE,
      SymbolKind.S_TOKEN_XOR,
      SymbolKind.S_TOKEN_LSHIFT,
      SymbolKind.S_TOKEN_RSHIFT,
      SymbolKind.S_TOKEN_DOUBLE_COLON,
      SymbolKind.S_TOKEN_DOT,
      SymbolKind.S_TOKEN_SECURITY,
      SymbolKind.S_TOKEN_COLON,
      SymbolKind.S_TOKEN_SEMICOLON,
      SymbolKind.S_TOKEN_COMMA,
      SymbolKind.S_TOKEN_ARROW,
      SymbolKind.S_TOKEN_FAT_ARROW,
      SymbolKind.S_TOKEN_PIPE_FORWARD,
      SymbolKind.S_TOKEN_OPTIONAL,
      SymbolKind.S_TOKEN_COALESCE,
      SymbolKind.S_TOKEN_RANGE,
      SymbolKind.S_TOKEN_RANGE_INC,
      SymbolKind.S_TOKEN_MUTS,
      SymbolKind.S_TOKEN_SYSF,
      SymbolKind.S_TOKEN_SH,
      SymbolKind.S_TOKEN_LPAREN,
      SymbolKind.S_TOKEN_RPAREN,
      SymbolKind.S_TOKEN_LBRACE,
      SymbolKind.S_TOKEN_RBRACE,
      SymbolKind.S_TOKEN_LBRACKET,
      SymbolKind.S_TOKEN_RBRACKET,
      SymbolKind.S_TOKEN_TRY,
      SymbolKind.S_TOKEN_CATCH,
      SymbolKind.S_TOKEN_FINALLY,
      SymbolKind.S_TOKEN_THROW,
      SymbolKind.S_TOKEN_EXCEPT,
      SymbolKind.S_TOKEN_RAISE,
      SymbolKind.S_TOKEN_IDENTIFIER,
      SymbolKind.S_TOKEN_NUMBER,
      SymbolKind.S_TOKEN_FLOAT,
      SymbolKind.S_TOKEN_STRING,
      SymbolKind.S_TOKEN_F_STRING,
      SymbolKind.S_YYACCEPT,
      SymbolKind.S_program,
      SymbolKind.S_statement_list,
      SymbolKind.S_unsafe_stmt,
      SymbolKind.S_continue_statement,
      SymbolKind.S_statement,
      SymbolKind.S_sysf_expr,
      SymbolKind.S_sh_expr,
      SymbolKind.S_nnl_statement,
      SymbolKind.S_try_statement,
      SymbolKind.S_catch_block,
      SymbolKind.S_finally_block,
      SymbolKind.S_throw_statement,
      SymbolKind.S_jmp_statement,
      SymbolKind.S_import_statement,
      SymbolKind.S_import_constraints,
      SymbolKind.S_import_options,
      SymbolKind.S_name_list,
      SymbolKind.S_export_statement,
      SymbolKind.S_packet_decl,
      SymbolKind.S_function_decl,
      SymbolKind.S_param_list,
      SymbolKind.S_param,
      SymbolKind.S_type,
      SymbolKind.S_dict_expr,
      SymbolKind.S_dict_entries,
      SymbolKind.S_dict_entry_list,
      SymbolKind.S_dict_access,
      SymbolKind.S_return_type,
      SymbolKind.S_let_decl,
      SymbolKind.S_const_decl,
      SymbolKind.S_if_statement,
      SymbolKind.S_break_statement,
      SymbolKind.S_for_statement,
      SymbolKind.S_while_statement,
      SymbolKind.S_loop_statement,
      SymbolKind.S_match_statement,
      SymbolKind.S_match_cases,
      SymbolKind.S_match_case,
      SymbolKind.S_pattern,
      SymbolKind.S_struct_decl,
      SymbolKind.S_struct_fields,
      SymbolKind.S_struct_field,
      SymbolKind.S_enum_decl,
      SymbolKind.S_enum_variants,
      SymbolKind.S_module_decl,
      SymbolKind.S_impl_decl,
      SymbolKind.S_function_decl_list,
      SymbolKind.S_return_statement,
      SymbolKind.S_expression,
      SymbolKind.S_binary_expr,
      SymbolKind.S_unary_expr,
      SymbolKind.S_lambda_expr,
      SymbolKind.S_array_access,
      SymbolKind.S_primary_expr,
      SymbolKind.S_f_string,
      SymbolKind.S_member_access,
      SymbolKind.S_call_expr,
      SymbolKind.S_argument_list,
      SymbolKind.S_array_expr,
      SymbolKind.S_await_expr,
      SymbolKind.S_spawn_expr,
      SymbolKind.S_array_items,
      SymbolKind.S_struct_expr,
      SymbolKind.S_struct_init_fields
    };

    static final SymbolKind get(int code) {
      return values_[code];
    }

    public final int getCode() {
      return this.yycode_;
    }

    /* Return YYSTR after stripping away unnecessary quotes and
       backslashes, so that it's suitable for yyerror.  The heuristic is
       that double-quoting is unnecessary unless the string contains an
       apostrophe, a comma, or backslash (other than backslash-backslash).
       YYSTR is taken from yytname.  */
    private static String yytnamerr_(String yystr)
    {
      if (yystr.charAt (0) == '"')
        {
          StringBuffer yyr = new StringBuffer();
          strip_quotes: for (int i = 1; i < yystr.length(); i++)
            switch (yystr.charAt(i))
              {
              case '\'':
              case ',':
                break strip_quotes;

              case '\\':
                if (yystr.charAt(++i) != '\\')
                  break strip_quotes;
                /* Fall through.  */
              default:
                yyr.append(yystr.charAt(i));
                break;

              case '"':
                return yyr.toString();
              }
        }
      return yystr;
    }

    /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
       First, the terminals, then, starting at \a YYNTOKENS_, nonterminals.  */
    private static final String[] yytname_ = yytname_init();
  private static final String[] yytname_init()
  {
    return new String[]
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
  "struct_expr", "struct_init_fields", null
    };
  }

    /* The user-facing name of this symbol.  */
    public final String getName() {
      return yytnamerr_(yytname_[yycode_]);
    }

  };


  /**
   * Communication interface between the scanner and the Bison-generated
   * parser <tt>YYParser</tt>.
   */
  public interface Lexer {
    /* Token kinds.  */
    /** Token "end of file", to be returned by the scanner.  */
    static final int YYEOF = 0;
    /** Token error, to be returned by the scanner.  */
    static final int YYerror = 256;
    /** Token "invalid token", to be returned by the scanner.  */
    static final int YYUNDEF = 257;
    /** Token TOKEN_DICT, to be returned by the scanner.  */
    static final int TOKEN_DICT = 258;
    /** Token TOKEN_MAP, to be returned by the scanner.  */
    static final int TOKEN_MAP = 259;
    /** Token TOKEN_FN, to be returned by the scanner.  */
    static final int TOKEN_FN = 260;
    /** Token TOKEN_LET, to be returned by the scanner.  */
    static final int TOKEN_LET = 261;
    /** Token TOKEN_CONST, to be returned by the scanner.  */
    static final int TOKEN_CONST = 262;
    /** Token TOKEN_RETURN, to be returned by the scanner.  */
    static final int TOKEN_RETURN = 263;
    /** Token TOKEN_IF, to be returned by the scanner.  */
    static final int TOKEN_IF = 264;
    /** Token TOKEN_ELSE, to be returned by the scanner.  */
    static final int TOKEN_ELSE = 265;
    /** Token TOKEN_FOR, to be returned by the scanner.  */
    static final int TOKEN_FOR = 266;
    /** Token TOKEN_WHILE, to be returned by the scanner.  */
    static final int TOKEN_WHILE = 267;
    /** Token TOKEN_LOOP, to be returned by the scanner.  */
    static final int TOKEN_LOOP = 268;
    /** Token TOKEN_BREAK, to be returned by the scanner.  */
    static final int TOKEN_BREAK = 269;
    /** Token TOKEN_CONTINUE, to be returned by the scanner.  */
    static final int TOKEN_CONTINUE = 270;
    /** Token TOKEN_IMPORT, to be returned by the scanner.  */
    static final int TOKEN_IMPORT = 271;
    /** Token TOKEN_EXPORT, to be returned by the scanner.  */
    static final int TOKEN_EXPORT = 272;
    /** Token TOKEN_PACKET, to be returned by the scanner.  */
    static final int TOKEN_PACKET = 273;
    /** Token TOKEN_STRUCT, to be returned by the scanner.  */
    static final int TOKEN_STRUCT = 274;
    /** Token TOKEN_ENUM, to be returned by the scanner.  */
    static final int TOKEN_ENUM = 275;
    /** Token TOKEN_IMPL, to be returned by the scanner.  */
    static final int TOKEN_IMPL = 276;
    /** Token TOKEN_MATCH, to be returned by the scanner.  */
    static final int TOKEN_MATCH = 277;
    /** Token TOKEN_TYPE, to be returned by the scanner.  */
    static final int TOKEN_TYPE = 278;
    /** Token TOKEN_TRUE, to be returned by the scanner.  */
    static final int TOKEN_TRUE = 279;
    /** Token TOKEN_FALSE, to be returned by the scanner.  */
    static final int TOKEN_FALSE = 280;
    /** Token TOKEN_NIL, to be returned by the scanner.  */
    static final int TOKEN_NIL = 281;
    /** Token TOKEN_AS, to be returned by the scanner.  */
    static final int TOKEN_AS = 282;
    /** Token TOKEN_IN, to be returned by the scanner.  */
    static final int TOKEN_IN = 283;
    /** Token TOKEN_FROM, to be returned by the scanner.  */
    static final int TOKEN_FROM = 284;
    /** Token TOKEN_PUB, to be returned by the scanner.  */
    static final int TOKEN_PUB = 285;
    /** Token TOKEN_NEW, to be returned by the scanner.  */
    static final int TOKEN_NEW = 286;
    /** Token TOKEN_UNSAFE, to be returned by the scanner.  */
    static final int TOKEN_UNSAFE = 287;
    /** Token TOKEN_NNL, to be returned by the scanner.  */
    static final int TOKEN_NNL = 288;
    /** Token TOKEN_JMP, to be returned by the scanner.  */
    static final int TOKEN_JMP = 289;
    /** Token TOKEN_MODULE, to be returned by the scanner.  */
    static final int TOKEN_MODULE = 290;
    /** Token TOKEN_ONLY, to be returned by the scanner.  */
    static final int TOKEN_ONLY = 291;
    /** Token TOKEN_TIMEOUT, to be returned by the scanner.  */
    static final int TOKEN_TIMEOUT = 292;
    /** Token TOKEN_SANDBOX, to be returned by the scanner.  */
    static final int TOKEN_SANDBOX = 293;
    /** Token TOKEN_ALLOW_FFI, to be returned by the scanner.  */
    static final int TOKEN_ALLOW_FFI = 294;
    /** Token TOKEN_ASYNC, to be returned by the scanner.  */
    static final int TOKEN_ASYNC = 295;
    /** Token TOKEN_AWAIT, to be returned by the scanner.  */
    static final int TOKEN_AWAIT = 296;
    /** Token TOKEN_SPAWN, to be returned by the scanner.  */
    static final int TOKEN_SPAWN = 297;
    /** Token TOKEN_LAMBDA, to be returned by the scanner.  */
    static final int TOKEN_LAMBDA = 298;
    /** Token TOKEN_EXTENDS, to be returned by the scanner.  */
    static final int TOKEN_EXTENDS = 299;
    /** Token TOKEN_UNDERSCORE, to be returned by the scanner.  */
    static final int TOKEN_UNDERSCORE = 300;
    /** Token TOKEN_PLUS, to be returned by the scanner.  */
    static final int TOKEN_PLUS = 301;
    /** Token TOKEN_MINUS, to be returned by the scanner.  */
    static final int TOKEN_MINUS = 302;
    /** Token TOKEN_MULTIPLY, to be returned by the scanner.  */
    static final int TOKEN_MULTIPLY = 303;
    /** Token TOKEN_DIVIDE, to be returned by the scanner.  */
    static final int TOKEN_DIVIDE = 304;
    /** Token TOKEN_MODULO, to be returned by the scanner.  */
    static final int TOKEN_MODULO = 305;
    /** Token TOKEN_ASSIGN, to be returned by the scanner.  */
    static final int TOKEN_ASSIGN = 306;
    /** Token TOKEN_PLUS_ASSIGN, to be returned by the scanner.  */
    static final int TOKEN_PLUS_ASSIGN = 307;
    /** Token TOKEN_MINUS_ASSIGN, to be returned by the scanner.  */
    static final int TOKEN_MINUS_ASSIGN = 308;
    /** Token TOKEN_MULTIPLY_ASSIGN, to be returned by the scanner.  */
    static final int TOKEN_MULTIPLY_ASSIGN = 309;
    /** Token TOKEN_DIVIDE_ASSIGN, to be returned by the scanner.  */
    static final int TOKEN_DIVIDE_ASSIGN = 310;
    /** Token TOKEN_MODULO_ASSIGN, to be returned by the scanner.  */
    static final int TOKEN_MODULO_ASSIGN = 311;
    /** Token TOKEN_EQ, to be returned by the scanner.  */
    static final int TOKEN_EQ = 312;
    /** Token TOKEN_NEQ, to be returned by the scanner.  */
    static final int TOKEN_NEQ = 313;
    /** Token TOKEN_LT, to be returned by the scanner.  */
    static final int TOKEN_LT = 314;
    /** Token TOKEN_LTE, to be returned by the scanner.  */
    static final int TOKEN_LTE = 315;
    /** Token TOKEN_GT, to be returned by the scanner.  */
    static final int TOKEN_GT = 316;
    /** Token TOKEN_GTE, to be returned by the scanner.  */
    static final int TOKEN_GTE = 317;
    /** Token TOKEN_AND, to be returned by the scanner.  */
    static final int TOKEN_AND = 318;
    /** Token TOKEN_OR, to be returned by the scanner.  */
    static final int TOKEN_OR = 319;
    /** Token TOKEN_NOT, to be returned by the scanner.  */
    static final int TOKEN_NOT = 320;
    /** Token TOKEN_AMP, to be returned by the scanner.  */
    static final int TOKEN_AMP = 321;
    /** Token TOKEN_PIPE, to be returned by the scanner.  */
    static final int TOKEN_PIPE = 322;
    /** Token TOKEN_XOR, to be returned by the scanner.  */
    static final int TOKEN_XOR = 323;
    /** Token TOKEN_LSHIFT, to be returned by the scanner.  */
    static final int TOKEN_LSHIFT = 324;
    /** Token TOKEN_RSHIFT, to be returned by the scanner.  */
    static final int TOKEN_RSHIFT = 325;
    /** Token TOKEN_DOUBLE_COLON, to be returned by the scanner.  */
    static final int TOKEN_DOUBLE_COLON = 326;
    /** Token TOKEN_DOT, to be returned by the scanner.  */
    static final int TOKEN_DOT = 327;
    /** Token TOKEN_SECURITY, to be returned by the scanner.  */
    static final int TOKEN_SECURITY = 328;
    /** Token TOKEN_COLON, to be returned by the scanner.  */
    static final int TOKEN_COLON = 329;
    /** Token TOKEN_SEMICOLON, to be returned by the scanner.  */
    static final int TOKEN_SEMICOLON = 330;
    /** Token TOKEN_COMMA, to be returned by the scanner.  */
    static final int TOKEN_COMMA = 331;
    /** Token TOKEN_ARROW, to be returned by the scanner.  */
    static final int TOKEN_ARROW = 332;
    /** Token TOKEN_FAT_ARROW, to be returned by the scanner.  */
    static final int TOKEN_FAT_ARROW = 333;
    /** Token TOKEN_PIPE_FORWARD, to be returned by the scanner.  */
    static final int TOKEN_PIPE_FORWARD = 334;
    /** Token TOKEN_OPTIONAL, to be returned by the scanner.  */
    static final int TOKEN_OPTIONAL = 335;
    /** Token TOKEN_COALESCE, to be returned by the scanner.  */
    static final int TOKEN_COALESCE = 336;
    /** Token TOKEN_RANGE, to be returned by the scanner.  */
    static final int TOKEN_RANGE = 337;
    /** Token TOKEN_RANGE_INC, to be returned by the scanner.  */
    static final int TOKEN_RANGE_INC = 338;
    /** Token TOKEN_MUTS, to be returned by the scanner.  */
    static final int TOKEN_MUTS = 339;
    /** Token TOKEN_SYSF, to be returned by the scanner.  */
    static final int TOKEN_SYSF = 340;
    /** Token TOKEN_SH, to be returned by the scanner.  */
    static final int TOKEN_SH = 341;
    /** Token TOKEN_LPAREN, to be returned by the scanner.  */
    static final int TOKEN_LPAREN = 342;
    /** Token TOKEN_RPAREN, to be returned by the scanner.  */
    static final int TOKEN_RPAREN = 343;
    /** Token TOKEN_LBRACE, to be returned by the scanner.  */
    static final int TOKEN_LBRACE = 344;
    /** Token TOKEN_RBRACE, to be returned by the scanner.  */
    static final int TOKEN_RBRACE = 345;
    /** Token TOKEN_LBRACKET, to be returned by the scanner.  */
    static final int TOKEN_LBRACKET = 346;
    /** Token TOKEN_RBRACKET, to be returned by the scanner.  */
    static final int TOKEN_RBRACKET = 347;
    /** Token TOKEN_TRY, to be returned by the scanner.  */
    static final int TOKEN_TRY = 348;
    /** Token TOKEN_CATCH, to be returned by the scanner.  */
    static final int TOKEN_CATCH = 349;
    /** Token TOKEN_FINALLY, to be returned by the scanner.  */
    static final int TOKEN_FINALLY = 350;
    /** Token TOKEN_THROW, to be returned by the scanner.  */
    static final int TOKEN_THROW = 351;
    /** Token TOKEN_EXCEPT, to be returned by the scanner.  */
    static final int TOKEN_EXCEPT = 352;
    /** Token TOKEN_RAISE, to be returned by the scanner.  */
    static final int TOKEN_RAISE = 353;
    /** Token TOKEN_IDENTIFIER, to be returned by the scanner.  */
    static final int TOKEN_IDENTIFIER = 354;
    /** Token TOKEN_NUMBER, to be returned by the scanner.  */
    static final int TOKEN_NUMBER = 355;
    /** Token TOKEN_FLOAT, to be returned by the scanner.  */
    static final int TOKEN_FLOAT = 356;
    /** Token TOKEN_STRING, to be returned by the scanner.  */
    static final int TOKEN_STRING = 357;
    /** Token TOKEN_F_STRING, to be returned by the scanner.  */
    static final int TOKEN_F_STRING = 358;

    /** Deprecated, use YYEOF instead.  */
    public static final int EOF = YYEOF;


    /**
     * Method to retrieve the semantic value of the last scanned token.
     * @return the semantic value of the last scanned token.
     */
    Object getLVal();

    /**
     * Entry point for the scanner.  Returns the token identifier corresponding
     * to the next token and prepares to return the semantic value
     * of the token.
     * @return the token identifier corresponding to the next token.
     */
    int yylex() throws java.io.IOException;

    /**
     * Emit an errorin a user-defined way.
     *
     *
     * @param msg The string for the error message.
     */
     void yyerror(String msg);


  }


  /**
   * The object doing lexical analysis for us.
   */
  private Lexer yylexer;





  /**
   * Instantiates the Bison-generated parser.
   * @param yylexer The scanner that will supply tokens to the parser.
   */
  public YYParser (Lexer yylexer)
  {

    this.yylexer = yylexer;

  }



  private int yynerrs = 0;

  /**
   * The number of syntax errors so far.
   */
  public final int getNumberOfErrors () { return yynerrs; }

  /**
   * Print an error message via the lexer.
   *
   * @param msg The error message.
   */
  public final void yyerror(String msg) {
      yylexer.yyerror(msg);
  }



  private final class YYStack {
    private int[] stateStack = new int[16];
    private Object[] valueStack = new Object[16];

    public int size = 16;
    public int height = -1;

    public final void push (int state, Object value) {
      height++;
      if (size == height)
        {
          int[] newStateStack = new int[size * 2];
          System.arraycopy (stateStack, 0, newStateStack, 0, height);
          stateStack = newStateStack;

          Object[] newValueStack = new Object[size * 2];
          System.arraycopy (valueStack, 0, newValueStack, 0, height);
          valueStack = newValueStack;

          size *= 2;
        }

      stateStack[height] = state;
      valueStack[height] = value;
    }

    public final void pop () {
      pop (1);
    }

    public final void pop (int num) {
      // Avoid memory leaks... garbage collection is a white lie!
      if (0 < num) {
        java.util.Arrays.fill (valueStack, height - num + 1, height + 1, null);
      }
      height -= num;
    }

    public final int stateAt (int i) {
      return stateStack[height - i];
    }

    public final Object valueAt (int i) {
      return valueStack[height - i];
    }

    // Print the state stack on the debug stream.
    public void print (java.io.PrintStream out) {
      out.print ("Stack now");

      for (int i = 0; i <= height; i++)
        {
          out.print (' ');
          out.print (stateStack[i]);
        }
      out.println ();
    }
  }

  /**
   * Returned by a Bison action in order to stop the parsing process and
   * return success (<tt>true</tt>).
   */
  public static final int YYACCEPT = 0;

  /**
   * Returned by a Bison action in order to stop the parsing process and
   * return failure (<tt>false</tt>).
   */
  public static final int YYABORT = 1;



  /**
   * Returned by a Bison action in order to start error recovery without
   * printing an error message.
   */
  public static final int YYERROR = 2;

  /**
   * Internal return codes that are not supported for user semantic
   * actions.
   */
  private static final int YYERRLAB = 3;
  private static final int YYNEWSTATE = 4;
  private static final int YYDEFAULT = 5;
  private static final int YYREDUCE = 6;
  private static final int YYERRLAB1 = 7;
  private static final int YYRETURN = 8;


  private int yyerrstatus_ = 0;


  /**
   * Whether error recovery is being done.  In this state, the parser
   * reads token until it reaches a known state, and then restarts normal
   * operation.
   */
  public final boolean recovering ()
  {
    return yyerrstatus_ == 0;
  }

  /** Compute post-reduction state.
   * @param yystate   the current state
   * @param yysym     the nonterminal to push on the stack
   */
  private int yyLRGotoState (int yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS_] + yystate;
    if (0 <= yyr && yyr <= YYLAST_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS_];
  }

  private int yyaction(int yyn, YYStack yystack, int yylen)
  {
    /* If YYLEN is nonzero, implement the default value of the action:
       '$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    Object yyval = (0 < yylen) ? yystack.valueAt(yylen - 1) : yystack.valueAt(0);

    switch (yyn)
      {
          case 2: /* program: statement_list  */
  if (yyn == 2)
    /* "parser.y":112  */
                   {
        program_root = create_program_node(((node_list)(yystack.valueAt (0))));
    };
  break;


  case 3: /* statement_list: statement  */
  if (yyn == 3)
    /* "parser.y":118  */
              {
        yyval = create_node_list();
        add_to_node_list(yyval, ((node)(yystack.valueAt (0))));
    };
  break;


  case 4: /* statement_list: statement_list statement  */
  if (yyn == 4)
    /* "parser.y":122  */
                               {
        add_to_node_list(((node_list)(yystack.valueAt (1))), ((node)(yystack.valueAt (0))));
        yyval = ((node_list)(yystack.valueAt (1)));
    };
  break;


  case 5: /* unsafe_stmt: TOKEN_UNSAFE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 5)
    /* "parser.y":128  */
                                                          {
        yyval = create_unsafe_node(((node_list)(yystack.valueAt (1))));
    };
  break;


  case 6: /* continue_statement: TOKEN_CONTINUE  */
  if (yyn == 6)
    /* "parser.y":133  */
                   {
        yyval = create_continue_node();
    };
  break;


  case 30: /* statement: expression  */
  if (yyn == 30)
    /* "parser.y":163  */
                 {
        yyval = create_expr_statement(((node)(yystack.valueAt (0))));
    };
  break;


  case 31: /* sysf_expr: TOKEN_SYSF TOKEN_LPAREN expression TOKEN_RPAREN  */
  if (yyn == 31)
    /* "parser.y":168  */
                                                    {
        yyval = create_sysf_node(((node)(yystack.valueAt (1))));
    };
  break;


  case 32: /* sysf_expr: TOKEN_SYSF expression  */
  if (yyn == 32)
    /* "parser.y":171  */
                            {
        yyval = create_sysf_node(((node)(yystack.valueAt (0))));
    };
  break;


  case 33: /* sh_expr: TOKEN_SH TOKEN_LPAREN expression TOKEN_RPAREN  */
  if (yyn == 33)
    /* "parser.y":177  */
                                                  {
        yyval = create_sh_node(((node)(yystack.valueAt (1))));
    };
  break;


  case 34: /* sh_expr: TOKEN_SH expression  */
  if (yyn == 34)
    /* "parser.y":180  */
                          {
        yyval = create_sh_node(((node)(yystack.valueAt (0))));
    };
  break;


  case 35: /* nnl_statement: TOKEN_NNL TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 35)
    /* "parser.y":186  */
                                                                        {
        yyval = create_nnl_node(((string)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 36: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block  */
  if (yyn == 36)
    /* "parser.y":192  */
                                                                   {
        yyval = create_try_node(((node_list)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))), NULL);
    };
  break;


  case 37: /* try_statement: TOKEN_TRY TOKEN_LBRACE statement_list TOKEN_RBRACE catch_block finally_block  */
  if (yyn == 37)
    /* "parser.y":195  */
                                                                                   {
        yyval = create_try_node(((node_list)(yystack.valueAt (3))), ((node)(yystack.valueAt (1))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 38: /* catch_block: TOKEN_CATCH TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 38)
    /* "parser.y":201  */
                                                                                                    {
        yyval = create_catch_node(((string)(yystack.valueAt (4))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 39: /* catch_block: TOKEN_EXCEPT TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 39)
    /* "parser.y":204  */
                                                                                                       {
        yyval = create_catch_node(((string)(yystack.valueAt (4))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 40: /* finally_block: TOKEN_FINALLY TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 40)
    /* "parser.y":210  */
                                                           {
        yyval = create_finally_node(((node_list)(yystack.valueAt (1))));
    };
  break;


  case 41: /* throw_statement: TOKEN_THROW expression  */
  if (yyn == 41)
    /* "parser.y":216  */
                           {
        yyval = create_throw_node(((node)(yystack.valueAt (0))));
    };
  break;


  case 42: /* throw_statement: TOKEN_RAISE expression  */
  if (yyn == 42)
    /* "parser.y":219  */
                             {
        yyval = create_throw_node(((node)(yystack.valueAt (0))));
    };
  break;


  case 43: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER  */
  if (yyn == 43)
    /* "parser.y":224  */
                               {
        yyval = create_jmp_node(((string)(yystack.valueAt (0))), NULL);
    };
  break;


  case 44: /* jmp_statement: TOKEN_JMP TOKEN_IDENTIFIER expression  */
  if (yyn == 44)
    /* "parser.y":227  */
                                            {
        yyval = create_jmp_node(((string)(yystack.valueAt (1))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 45: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER  */
  if (yyn == 45)
    /* "parser.y":233  */
                                  {
        yyval = create_import_node(((string)(yystack.valueAt (0))), NULL, NULL);
    };
  break;


  case 46: /* import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_IDENTIFIER  */
  if (yyn == 46)
    /* "parser.y":236  */
                                              {
        char* path = malloc(strlen(((string)(yystack.valueAt (0)))) + 3);
        sprintf(path, "./%s", ((string)(yystack.valueAt (0))));
        yyval = create_import_node(path, NULL, NULL);
        free(path);
    };
  break;


  case 47: /* import_statement: TOKEN_IMPORT TOKEN_DOT TOKEN_DOT TOKEN_DOT TOKEN_IDENTIFIER  */
  if (yyn == 47)
    /* "parser.y":242  */
                                                                  {
        char* path = malloc(strlen(((string)(yystack.valueAt (0)))) + 4);
        sprintf(path, "../%s", ((string)(yystack.valueAt (0))));
        yyval = create_import_node(path, NULL, NULL);
        free(path);
    };
  break;


  case 48: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_STRING  */
  if (yyn == 48)
    /* "parser.y":248  */
                                                            {
        yyval = create_import_node(((string)(yystack.valueAt (0))), ((string)(yystack.valueAt (2))), NULL);
    };
  break;


  case 49: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_FROM TOKEN_DOT TOKEN_IDENTIFIER  */
  if (yyn == 49)
    /* "parser.y":252  */
                                                                          {
        char* path = malloc(strlen(((string)(yystack.valueAt (0)))) + 3);
        sprintf(path, "./%s", ((string)(yystack.valueAt (0))));
        yyval = create_import_node(path, ((string)(yystack.valueAt (3))), NULL);
        free(path);
    };
  break;


  case 50: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER TOKEN_AS TOKEN_IDENTIFIER  */
  if (yyn == 50)
    /* "parser.y":258  */
                                                              {
        yyval = create_import_node(((string)(yystack.valueAt (2))), ((string)(yystack.valueAt (0))), NULL);
    };
  break;


  case 51: /* import_statement: TOKEN_IMPORT TOKEN_IDENTIFIER import_constraints  */
  if (yyn == 51)
    /* "parser.y":261  */
                                                       {
        yyval = create_import_node(((string)(yystack.valueAt (1))), NULL, ((node)(yystack.valueAt (0))));
    };
  break;


  case 52: /* import_constraints: TOKEN_LBRACE import_options TOKEN_RBRACE  */
  if (yyn == 52)
    /* "parser.y":267  */
                                             {
        yyval = ((node)(yystack.valueAt (1)));
    };
  break;


  case 53: /* import_options: TOKEN_ONLY TOKEN_COLON TOKEN_LBRACKET name_list TOKEN_RBRACKET  */
  if (yyn == 53)
    /* "parser.y":273  */
                                                                   {
        yyval = create_constraints_node("only", ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 54: /* import_options: import_options TOKEN_COMMA import_options  */
  if (yyn == 54)
    /* "parser.y":276  */
                                                {
        yyval = merge_constraints(((node)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 55: /* name_list: TOKEN_IDENTIFIER  */
  if (yyn == 55)
    /* "parser.y":282  */
                     {
        yyval = create_node_list();
        add_to_node_list(yyval, create_identifier_node(((string)(yystack.valueAt (0)))));
    };
  break;


  case 56: /* name_list: name_list TOKEN_COMMA TOKEN_IDENTIFIER  */
  if (yyn == 56)
    /* "parser.y":286  */
                                             {
        add_to_node_list(((node_list)(yystack.valueAt (2))), create_identifier_node(((string)(yystack.valueAt (0)))));
        yyval = ((node_list)(yystack.valueAt (2)));
    };
  break;


  case 57: /* export_statement: TOKEN_EXPORT TOKEN_IDENTIFIER  */
  if (yyn == 57)
    /* "parser.y":293  */
                                  {
        yyval = create_export_node(((string)(yystack.valueAt (0))));
    };
  break;


  case 58: /* packet_decl: TOKEN_PACKET TOKEN_IDENTIFIER TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 58)
    /* "parser.y":299  */
                                                                           {
        yyval = create_packet_node(((string)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 59: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 59)
    /* "parser.y":305  */
                                                                                                                        {
        yyval = create_function_node(((string)(yystack.valueAt (7))), ((node_list)(yystack.valueAt (5))), ((node)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 60: /* function_decl: TOKEN_PUB TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 60)
    /* "parser.y":308  */
                                                                                                                                    {
        yyval = create_public_function_node(((string)(yystack.valueAt (7))), ((node_list)(yystack.valueAt (5))), ((node)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 61: /* function_decl: TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 61)
    /* "parser.y":311  */
                                                                                                                                      {
        ASTNode* node = create_function_node(((string)(yystack.valueAt (7))), ((node_list)(yystack.valueAt (5))), ((node)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        yyval = node;
    };
  break;


  case 62: /* function_decl: TOKEN_PUB TOKEN_ASYNC TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 62)
    /* "parser.y":317  */
                                                                                                                                                {
        ASTNode* node = create_function_node(((string)(yystack.valueAt (7))), ((node_list)(yystack.valueAt (5))), ((node)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
        node->type = NODE_ASYNC_FUNCTION;
        node->function.is_async = 1;
        node->function.is_public = 1;
        yyval = node;
    };
  break;


  case 63: /* function_decl: TOKEN_FN TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN return_type TOKEN_ARROW expression  */
  if (yyn == 63)
    /* "parser.y":324  */
                                                                                                        {
        ASTNodeList* body = create_node_list();
        ASTNode* return_stmt = create_return_node(((node)(yystack.valueAt (0))));
        add_to_node_list(body, return_stmt);
        yyval = create_function_node(((string)(yystack.valueAt (6))), ((node_list)(yystack.valueAt (4))), ((node)(yystack.valueAt (2))), body);
    };
  break;


  case 64: /* param_list: %empty  */
  if (yyn == 64)
    /* "parser.y":333  */
                {
        yyval = NULL;
    };
  break;


  case 65: /* param_list: param  */
  if (yyn == 65)
    /* "parser.y":336  */
            {
        yyval = create_node_list();
        add_to_node_list(yyval, ((node)(yystack.valueAt (0))));
    };
  break;


  case 66: /* param_list: param_list TOKEN_COMMA param  */
  if (yyn == 66)
    /* "parser.y":340  */
                                   {
        add_to_node_list(((node_list)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
        yyval = ((node_list)(yystack.valueAt (2)));
    };
  break;


  case 67: /* param: TOKEN_IDENTIFIER  */
  if (yyn == 67)
    /* "parser.y":347  */
                     {
        yyval = create_identifier_node(((string)(yystack.valueAt (0))));
    };
  break;


  case 68: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
  if (yyn == 68)
    /* "parser.y":350  */
                                        {
        yyval = create_param_node(((string)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 69: /* type: TOKEN_IDENTIFIER  */
  if (yyn == 69)
    /* "parser.y":356  */
                     {
        yyval = create_type_node(((string)(yystack.valueAt (0))));
    };
  break;


  case 70: /* type: TOKEN_IDENTIFIER TOKEN_OPTIONAL  */
  if (yyn == 70)
    /* "parser.y":359  */
                                      {
        yyval = create_optional_type_node(((string)(yystack.valueAt (1))));
    };
  break;


  case 71: /* type: TOKEN_LBRACKET TOKEN_RBRACKET type  */
  if (yyn == 71)
    /* "parser.y":362  */
                                         {
        yyval = create_array_type_node(((node)(yystack.valueAt (0))));
    };
  break;


  case 72: /* dict_expr: TOKEN_DICT TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
  if (yyn == 72)
    /* "parser.y":370  */
                                                      {
        yyval = create_dict_node(((node_list)(yystack.valueAt (1))));
    };
  break;


  case 73: /* dict_expr: TOKEN_MAP TOKEN_LBRACE dict_entries TOKEN_RBRACE  */
  if (yyn == 73)
    /* "parser.y":373  */
                                                       {
        yyval = create_dict_node(((node_list)(yystack.valueAt (1))));
    };
  break;


  case 74: /* dict_entries: %empty  */
  if (yyn == 74)
    /* "parser.y":379  */
                {
        yyval = NULL;
    };
  break;


  case 75: /* dict_entries: dict_entry_list  */
  if (yyn == 75)
    /* "parser.y":382  */
                      {
        yyval = ((node_list)(yystack.valueAt (0)));
    };
  break;


  case 76: /* dict_entry_list: expression TOKEN_FAT_ARROW expression  */
  if (yyn == 76)
    /* "parser.y":388  */
                                          {
        yyval = create_node_list();
        ASTNode* pair = create_binary_op(((node)(yystack.valueAt (2))), OP_ASSIGN, ((node)(yystack.valueAt (0))));
        add_to_node_list(yyval, pair);
    };
  break;


  case 77: /* dict_entry_list: dict_entry_list TOKEN_COMMA expression TOKEN_FAT_ARROW expression  */
  if (yyn == 77)
    /* "parser.y":393  */
                                                                        {
        ASTNode* pair = create_binary_op(((node)(yystack.valueAt (2))), OP_ASSIGN, ((node)(yystack.valueAt (0))));
        add_to_node_list(((node_list)(yystack.valueAt (4))), pair);
        yyval = ((node_list)(yystack.valueAt (4)));
    };
  break;


  case 78: /* dict_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
  if (yyn == 78)
    /* "parser.y":402  */
                                                          {
        // Détecter si c'est un accès dictionnaire ou tableau
        // Par défaut, c'est un accès tableau, mais on peut différencier par le type
        // Pour l'instant, on crée un nœud d'accès dictionnaire
        yyval = create_dict_access_node(((node)(yystack.valueAt (3))), ((node)(yystack.valueAt (1))));
    };
  break;


  case 79: /* return_type: %empty  */
  if (yyn == 79)
    /* "parser.y":421  */
                {
        yyval = NULL;
    };
  break;


  case 80: /* return_type: TOKEN_COLON type  */
  if (yyn == 80)
    /* "parser.y":424  */
                       {
        yyval = ((node)(yystack.valueAt (0)));
    };
  break;


  case 81: /* return_type: TOKEN_ARROW primary_expr  */
  if (yyn == 81)
    /* "parser.y":427  */
                               {
        // Pour les retours directs: -> expr
        yyval = create_return_direct_node(((node)(yystack.valueAt (0))));
    };
  break;


  case 82: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
  if (yyn == 82)
    /* "parser.y":434  */
                                                       {
        yyval = create_let_node(((string)(yystack.valueAt (2))), NULL, ((node)(yystack.valueAt (0))));
    };
  break;


  case 83: /* let_decl: TOKEN_LET TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
  if (yyn == 83)
    /* "parser.y":437  */
                                                                          {
        yyval = create_let_node(((string)(yystack.valueAt (4))), ((node)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 84: /* let_decl: TOKEN_PUB TOKEN_LET TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
  if (yyn == 84)
    /* "parser.y":440  */
                                                                   {
        ASTNode* node = create_let_node(((string)(yystack.valueAt (2))), NULL, ((node)(yystack.valueAt (0))));
        node->var_decl.is_public = 1;
        yyval = node;
    };
  break;


  case 85: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
  if (yyn == 85)
    /* "parser.y":446  */
                                                          {
        yyval = create_muts_node(((string)(yystack.valueAt (2))), NULL, ((node)(yystack.valueAt (0))));
    };
  break;


  case 86: /* let_decl: TOKEN_MUTS TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expression  */
  if (yyn == 86)
    /* "parser.y":449  */
                                                                           {
        yyval = create_muts_node(((string)(yystack.valueAt (4))), ((node)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 87: /* const_decl: TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
  if (yyn == 87)
    /* "parser.y":454  */
                                                         {
        yyval = create_const_node(((string)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 88: /* const_decl: TOKEN_PUB TOKEN_CONST TOKEN_IDENTIFIER TOKEN_ASSIGN expression  */
  if (yyn == 88)
    /* "parser.y":457  */
                                                                     {
        // Créer une constante publique
        ASTNode* node = create_const_node(((string)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
        node->var_decl.is_public = 1;
        yyval = node;
    };
  break;


  case 89: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 89)
    /* "parser.y":466  */
                                                                 {
        yyval = create_if_node(((node)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))), NULL);
    };
  break;


  case 90: /* if_statement: TOKEN_IF expression TOKEN_LBRACE statement_list TOKEN_RBRACE TOKEN_ELSE TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 90)
    /* "parser.y":469  */
                                                                                                                       {
        yyval = create_if_node(((node)(yystack.valueAt (7))), ((node_list)(yystack.valueAt (5))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 91: /* break_statement: TOKEN_BREAK  */
  if (yyn == 91)
    /* "parser.y":474  */
                {
        yyval = create_break_node();
    };
  break;


  case 92: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON expression TOKEN_SEMICOLON expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 92)
    /* "parser.y":479  */
                                                                                                                                                      {
        ASTNode* init = create_let_node(((string)(yystack.valueAt (9))), NULL, ((node)(yystack.valueAt (7))));
        ASTNode* cond = ((node)(yystack.valueAt (5)));
        ASTNode* inc = create_expr_statement(((node)(yystack.valueAt (3))));
        yyval = create_for_node(init, cond, inc, ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 93: /* for_statement: TOKEN_FOR expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 93)
    /* "parser.y":485  */
                                                                    {
        yyval = create_while_node(((node)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 94: /* for_statement: TOKEN_FOR TOKEN_IDENTIFIER TOKEN_IN expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 94)
    /* "parser.y":488  */
                                                                                              {
        // for x in array { ... }
        ASTNode* array_expr = ((node)(yystack.valueAt (3)));
        ASTNodeList* body = ((node_list)(yystack.valueAt (1)));
        
        // Créer un nœud spécial pour for-in
        ASTNode* node = malloc(sizeof(ASTNode));
        node->type = NODE_FOR_IN;
        node->for_in.var = strdup(((string)(yystack.valueAt (5))));
        node->for_in.collection = array_expr;
        node->for_in.body = body;
        yyval = node;
    };
  break;


  case 95: /* while_statement: TOKEN_WHILE expression TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 95)
    /* "parser.y":504  */
                                                                    {
        yyval = create_while_node(((node)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 96: /* loop_statement: TOKEN_LOOP TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 96)
    /* "parser.y":510  */
                                                        {
        yyval = create_loop_node(((node_list)(yystack.valueAt (1))));
    };
  break;


  case 97: /* match_statement: TOKEN_MATCH expression TOKEN_LBRACE match_cases TOKEN_RBRACE  */
  if (yyn == 97)
    /* "parser.y":517  */
                                                                 {
        yyval = create_match_node(((node)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 98: /* match_cases: match_case  */
  if (yyn == 98)
    /* "parser.y":523  */
               {
        yyval = create_node_list();
        add_to_node_list(yyval, ((node)(yystack.valueAt (0))));
    };
  break;


  case 99: /* match_cases: match_cases match_case  */
  if (yyn == 99)
    /* "parser.y":527  */
                             {
        add_to_node_list(((node_list)(yystack.valueAt (1))), ((node)(yystack.valueAt (0))));
        yyval = ((node_list)(yystack.valueAt (1)));
    };
  break;


  case 100: /* match_case: pattern TOKEN_FAT_ARROW expression  */
  if (yyn == 100)
    /* "parser.y":534  */
                                       {
        yyval = create_match_case_node(((node)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 101: /* pattern: TOKEN_NUMBER  */
  if (yyn == 101)
    /* "parser.y":540  */
                 {
        yyval = create_pattern_number(((number)(yystack.valueAt (0))));
    };
  break;


  case 102: /* pattern: TOKEN_STRING  */
  if (yyn == 102)
    /* "parser.y":543  */
                   {
        yyval = create_pattern_string(((string)(yystack.valueAt (0))));
    };
  break;


  case 103: /* pattern: TOKEN_IDENTIFIER  */
  if (yyn == 103)
    /* "parser.y":546  */
                       {
        yyval = create_pattern_ident(((string)(yystack.valueAt (0))));
    };
  break;


  case 104: /* pattern: TOKEN_UNDERSCORE  */
  if (yyn == 104)
    /* "parser.y":549  */
                       {
        yyval = create_pattern_wildcard();
    };
  break;


  case 105: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
  if (yyn == 105)
    /* "parser.y":555  */
                                                                          {
        yyval = create_struct_node(((string)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 106: /* struct_decl: TOKEN_STRUCT TOKEN_IDENTIFIER TOKEN_EXTENDS TOKEN_IDENTIFIER TOKEN_LBRACE struct_fields TOKEN_RBRACE  */
  if (yyn == 106)
    /* "parser.y":558  */
                                                                                                           {
        yyval = create_struct_extend_node(((string)(yystack.valueAt (5))), ((string)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 107: /* struct_fields: %empty  */
  if (yyn == 107)
    /* "parser.y":564  */
                {
        yyval = NULL;
    };
  break;


  case 108: /* struct_fields: struct_field  */
  if (yyn == 108)
    /* "parser.y":567  */
                   {
        yyval = create_node_list();
        add_to_node_list(yyval, ((node)(yystack.valueAt (0))));
    };
  break;


  case 109: /* struct_fields: struct_fields TOKEN_COMMA struct_field  */
  if (yyn == 109)
    /* "parser.y":571  */
                                             {
        add_to_node_list(((node_list)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
        yyval = ((node_list)(yystack.valueAt (2)));
    };
  break;


  case 110: /* struct_fields: struct_fields struct_field  */
  if (yyn == 110)
    /* "parser.y":575  */
                                 {
        add_to_node_list(((node_list)(yystack.valueAt (1))), ((node)(yystack.valueAt (0))));
        yyval = ((node_list)(yystack.valueAt (1)));
    };
  break;


  case 111: /* struct_field: TOKEN_IDENTIFIER TOKEN_COLON type  */
  if (yyn == 111)
    /* "parser.y":582  */
                                      {
        yyval = create_field_node(((string)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 112: /* enum_decl: TOKEN_ENUM TOKEN_IDENTIFIER TOKEN_LBRACE enum_variants TOKEN_RBRACE  */
  if (yyn == 112)
    /* "parser.y":588  */
                                                                        {
        yyval = create_enum_node(((string)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 113: /* enum_variants: %empty  */
  if (yyn == 113)
    /* "parser.y":594  */
                {
        yyval = NULL;
    };
  break;


  case 114: /* enum_variants: TOKEN_IDENTIFIER  */
  if (yyn == 114)
    /* "parser.y":597  */
                       {
        yyval = create_node_list();
        add_to_node_list(yyval, create_identifier_node(((string)(yystack.valueAt (0)))));
    };
  break;


  case 115: /* enum_variants: enum_variants TOKEN_COMMA TOKEN_IDENTIFIER  */
  if (yyn == 115)
    /* "parser.y":601  */
                                                 {
        add_to_node_list(((node_list)(yystack.valueAt (2))), create_identifier_node(((string)(yystack.valueAt (0)))));
        yyval = ((node_list)(yystack.valueAt (2)));
    };
  break;


  case 116: /* module_decl: TOKEN_MODULE TOKEN_IDENTIFIER  */
  if (yyn == 116)
    /* "parser.y":608  */
                                  {
        // Créer un nœud nil pour éviter l'erreur
        yyval = create_expr_statement(create_nil_node());
    };
  break;


  case 117: /* impl_decl: TOKEN_IMPL TOKEN_IDENTIFIER TOKEN_LBRACE function_decl_list TOKEN_RBRACE  */
  if (yyn == 117)
    /* "parser.y":615  */
                                                                             {
        yyval = create_impl_node(((string)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 118: /* function_decl_list: %empty  */
  if (yyn == 118)
    /* "parser.y":621  */
                {
        yyval = NULL;
    };
  break;


  case 119: /* function_decl_list: function_decl  */
  if (yyn == 119)
    /* "parser.y":624  */
                    {
        yyval = create_node_list();
        add_to_node_list(yyval, ((node)(yystack.valueAt (0))));
    };
  break;


  case 120: /* function_decl_list: function_decl_list function_decl  */
  if (yyn == 120)
    /* "parser.y":628  */
                                       {
        add_to_node_list(((node_list)(yystack.valueAt (1))), ((node)(yystack.valueAt (0))));
        yyval = ((node_list)(yystack.valueAt (1)));
    };
  break;


  case 121: /* return_statement: TOKEN_RETURN expression  */
  if (yyn == 121)
    /* "parser.y":635  */
                            {
        yyval = create_return_node(((node)(yystack.valueAt (0))));
    };
  break;


  case 122: /* return_statement: TOKEN_RETURN  */
  if (yyn == 122)
    /* "parser.y":638  */
                   {
        yyval = create_return_node(NULL);
    };
  break;


  case 126: /* binary_expr: expression TOKEN_PLUS expression  */
  if (yyn == 126)
    /* "parser.y":650  */
                                     {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_ADD, ((node)(yystack.valueAt (0))));
    };
  break;


  case 127: /* binary_expr: expression TOKEN_MINUS expression  */
  if (yyn == 127)
    /* "parser.y":653  */
                                        {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_SUB, ((node)(yystack.valueAt (0))));
    };
  break;


  case 128: /* binary_expr: expression TOKEN_MULTIPLY expression  */
  if (yyn == 128)
    /* "parser.y":656  */
                                           {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_MUL, ((node)(yystack.valueAt (0))));
    };
  break;


  case 129: /* binary_expr: expression TOKEN_DIVIDE expression  */
  if (yyn == 129)
    /* "parser.y":659  */
                                         {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_DIV, ((node)(yystack.valueAt (0))));
    };
  break;


  case 130: /* binary_expr: expression TOKEN_MODULO expression  */
  if (yyn == 130)
    /* "parser.y":662  */
                                         {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_MOD, ((node)(yystack.valueAt (0))));
    };
  break;


  case 131: /* binary_expr: expression TOKEN_EQ expression  */
  if (yyn == 131)
    /* "parser.y":665  */
                                     {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_EQ, ((node)(yystack.valueAt (0))));
    };
  break;


  case 132: /* binary_expr: expression TOKEN_NEQ expression  */
  if (yyn == 132)
    /* "parser.y":668  */
                                      {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_NEQ, ((node)(yystack.valueAt (0))));
    };
  break;


  case 133: /* binary_expr: expression TOKEN_LT expression  */
  if (yyn == 133)
    /* "parser.y":671  */
                                     {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_LT, ((node)(yystack.valueAt (0))));
    };
  break;


  case 134: /* binary_expr: expression TOKEN_LTE expression  */
  if (yyn == 134)
    /* "parser.y":674  */
                                      {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_LTE, ((node)(yystack.valueAt (0))));
    };
  break;


  case 135: /* binary_expr: expression TOKEN_GT expression  */
  if (yyn == 135)
    /* "parser.y":677  */
                                     {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_GT, ((node)(yystack.valueAt (0))));
    };
  break;


  case 136: /* binary_expr: expression TOKEN_GTE expression  */
  if (yyn == 136)
    /* "parser.y":680  */
                                      {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_GTE, ((node)(yystack.valueAt (0))));
    };
  break;


  case 137: /* binary_expr: expression TOKEN_AND expression  */
  if (yyn == 137)
    /* "parser.y":683  */
                                      {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_AND, ((node)(yystack.valueAt (0))));
    };
  break;


  case 138: /* binary_expr: expression TOKEN_OR expression  */
  if (yyn == 138)
    /* "parser.y":686  */
                                     {
        yyval = create_binary_op(((node)(yystack.valueAt (2))), OP_OR, ((node)(yystack.valueAt (0))));
    };
  break;


  case 139: /* binary_expr: expression TOKEN_ASSIGN expression  */
  if (yyn == 139)
    /* "parser.y":689  */
                                         {
        yyval = create_assign_node(((node)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
    };
  break;


  case 140: /* binary_expr: expression TOKEN_PLUS_ASSIGN expression  */
  if (yyn == 140)
    /* "parser.y":692  */
                                              {
        yyval = create_assign_op_node(((node)(yystack.valueAt (2))), OP_ADD_ASSIGN, ((node)(yystack.valueAt (0))));
    };
  break;


  case 141: /* binary_expr: expression TOKEN_MINUS_ASSIGN expression  */
  if (yyn == 141)
    /* "parser.y":695  */
                                               {
        yyval = create_assign_op_node(((node)(yystack.valueAt (2))), OP_SUB_ASSIGN, ((node)(yystack.valueAt (0))));
    };
  break;


  case 142: /* binary_expr: expression TOKEN_MULTIPLY_ASSIGN expression  */
  if (yyn == 142)
    /* "parser.y":698  */
                                                  {
        yyval = create_assign_op_node(((node)(yystack.valueAt (2))), OP_MUL_ASSIGN, ((node)(yystack.valueAt (0))));
    };
  break;


  case 143: /* binary_expr: expression TOKEN_DIVIDE_ASSIGN expression  */
  if (yyn == 143)
    /* "parser.y":701  */
                                                {
        yyval = create_assign_op_node(((node)(yystack.valueAt (2))), OP_DIV_ASSIGN, ((node)(yystack.valueAt (0))));
    };
  break;


  case 144: /* binary_expr: expression TOKEN_MODULO_ASSIGN expression  */
  if (yyn == 144)
    /* "parser.y":704  */
                                                {
        yyval = create_assign_op_node(((node)(yystack.valueAt (2))), OP_MOD_ASSIGN, ((node)(yystack.valueAt (0))));
    };
  break;


  case 145: /* unary_expr: TOKEN_NOT expression  */
  if (yyn == 145)
    /* "parser.y":710  */
                         {
        yyval = create_unary_op(OP_NOT, ((node)(yystack.valueAt (0))));
    };
  break;


  case 146: /* unary_expr: TOKEN_MINUS expression  */
  if (yyn == 146)
    /* "parser.y":713  */
                             {
        yyval = create_unary_op(OP_NEG, ((node)(yystack.valueAt (0))));
    };
  break;


  case 147: /* lambda_expr: TOKEN_LAMBDA param_list TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 147)
    /* "parser.y":720  */
                                                                     {
        yyval = create_lambda_node(((node_list)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 148: /* lambda_expr: TOKEN_LAMBDA TOKEN_LPAREN param_list TOKEN_RPAREN TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 148)
    /* "parser.y":723  */
                                                                                                 {
        yyval = create_lambda_node(((node_list)(yystack.valueAt (4))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 149: /* array_access: primary_expr TOKEN_LBRACKET expression TOKEN_RBRACKET  */
  if (yyn == 149)
    /* "parser.y":730  */
                                                          {
        yyval = create_array_access_node(((node)(yystack.valueAt (3))), ((node)(yystack.valueAt (1))));
    };
  break;


  case 150: /* primary_expr: TOKEN_NUMBER  */
  if (yyn == 150)
    /* "parser.y":736  */
                 {
        yyval = create_number_node(((number)(yystack.valueAt (0))));
    };
  break;


  case 151: /* primary_expr: TOKEN_FLOAT  */
  if (yyn == 151)
    /* "parser.y":739  */
                  {
        yyval = create_float_node(((float_val)(yystack.valueAt (0))));
    };
  break;


  case 152: /* primary_expr: TOKEN_STRING  */
  if (yyn == 152)
    /* "parser.y":742  */
                   {
        yyval = create_string_node(((string)(yystack.valueAt (0))));
    };
  break;


  case 153: /* primary_expr: TOKEN_TRUE  */
  if (yyn == 153)
    /* "parser.y":745  */
                 {
        yyval = create_bool_node(1);
    };
  break;


  case 154: /* primary_expr: TOKEN_FALSE  */
  if (yyn == 154)
    /* "parser.y":748  */
                  {
        yyval = create_bool_node(0);
    };
  break;


  case 155: /* primary_expr: TOKEN_NIL  */
  if (yyn == 155)
    /* "parser.y":751  */
                {
        yyval = create_nil_node();
    };
  break;


  case 156: /* primary_expr: TOKEN_IDENTIFIER  */
  if (yyn == 156)
    /* "parser.y":754  */
                       {
        yyval = create_identifier_node(((string)(yystack.valueAt (0))));
    };
  break;


  case 157: /* primary_expr: TOKEN_LPAREN expression TOKEN_RPAREN  */
  if (yyn == 157)
    /* "parser.y":757  */
                                           {
        yyval = ((node)(yystack.valueAt (1)));
    };
  break;


  case 171: /* f_string: TOKEN_F_STRING  */
  if (yyn == 171)
    /* "parser.y":776  */
                   {
        yyval = parse_f_string(((string)(yystack.valueAt (0))));
    };
  break;


  case 172: /* member_access: primary_expr TOKEN_DOT TOKEN_IDENTIFIER  */
  if (yyn == 172)
    /* "parser.y":782  */
                                            {
        yyval = create_member_access(((node)(yystack.valueAt (2))), ((string)(yystack.valueAt (0))));
    };
  break;


  case 173: /* member_access: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER  */
  if (yyn == 173)
    /* "parser.y":785  */
                                                       {
        yyval = create_static_access(((node)(yystack.valueAt (2))), ((string)(yystack.valueAt (0))));
    };
  break;


  case 174: /* call_expr: primary_expr TOKEN_LPAREN argument_list TOKEN_RPAREN  */
  if (yyn == 174)
    /* "parser.y":791  */
                                                         {
        yyval = create_call_node(((node)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 175: /* call_expr: primary_expr TOKEN_DOUBLE_COLON TOKEN_IDENTIFIER TOKEN_LPAREN argument_list TOKEN_RPAREN  */
  if (yyn == 175)
    /* "parser.y":794  */
                                                                                               {
        yyval = create_method_call_node(((node)(yystack.valueAt (5))), ((string)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 176: /* argument_list: %empty  */
  if (yyn == 176)
    /* "parser.y":800  */
                {
        yyval = NULL;
    };
  break;


  case 177: /* argument_list: expression  */
  if (yyn == 177)
    /* "parser.y":803  */
                 {
        yyval = create_arg_list();
        add_arg(yyval, ((node)(yystack.valueAt (0))));
    };
  break;


  case 178: /* argument_list: argument_list TOKEN_COMMA expression  */
  if (yyn == 178)
    /* "parser.y":807  */
                                           {
        add_arg(((node_list)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
        yyval = ((node_list)(yystack.valueAt (2)));
    };
  break;


  case 179: /* array_expr: TOKEN_LBRACKET array_items TOKEN_RBRACKET  */
  if (yyn == 179)
    /* "parser.y":814  */
                                              {
        yyval = create_array_node(((node_list)(yystack.valueAt (1))));
    };
  break;


  case 180: /* await_expr: TOKEN_AWAIT primary_expr  */
  if (yyn == 180)
    /* "parser.y":829  */
                             {
        yyval = create_await_node(((node)(yystack.valueAt (0))));
    };
  break;


  case 181: /* await_expr: TOKEN_AWAIT TOKEN_LBRACE statement_list TOKEN_RBRACE  */
  if (yyn == 181)
    /* "parser.y":832  */
                                                           {
        yyval = create_await_block_node(((node_list)(yystack.valueAt (1))));
    };
  break;


  case 182: /* spawn_expr: TOKEN_SPAWN primary_expr  */
  if (yyn == 182)
    /* "parser.y":839  */
                             {
        yyval = create_spawn_node(((node)(yystack.valueAt (0))));
    };
  break;


  case 183: /* array_items: %empty  */
  if (yyn == 183)
    /* "parser.y":851  */
                {
        yyval = NULL;
    };
  break;


  case 184: /* array_items: expression  */
  if (yyn == 184)
    /* "parser.y":854  */
                 {
        yyval = create_node_list();
        add_to_node_list(yyval, ((node)(yystack.valueAt (0))));
    };
  break;


  case 185: /* array_items: array_items TOKEN_COMMA expression  */
  if (yyn == 185)
    /* "parser.y":858  */
                                         {
        add_to_node_list(((node_list)(yystack.valueAt (2))), ((node)(yystack.valueAt (0))));
        yyval = ((node_list)(yystack.valueAt (2)));
    };
  break;


  case 186: /* struct_expr: TOKEN_NEW TOKEN_IDENTIFIER TOKEN_LBRACE struct_init_fields TOKEN_RBRACE  */
  if (yyn == 186)
    /* "parser.y":865  */
                                                                            {
        yyval = create_struct_init_node(((string)(yystack.valueAt (3))), ((node_list)(yystack.valueAt (1))));
    };
  break;


  case 187: /* struct_init_fields: %empty  */
  if (yyn == 187)
    /* "parser.y":871  */
                {
        yyval = NULL;
    };
  break;


  case 188: /* struct_init_fields: TOKEN_IDENTIFIER TOKEN_COLON expression  */
  if (yyn == 188)
    /* "parser.y":874  */
                                              {
        yyval = create_node_list();
        add_to_node_list(yyval, create_field_init_node(((string)(yystack.valueAt (2))), ((node)(yystack.valueAt (0)))));
    };
  break;


  case 189: /* struct_init_fields: struct_init_fields TOKEN_COMMA TOKEN_IDENTIFIER TOKEN_COLON expression  */
  if (yyn == 189)
    /* "parser.y":878  */
                                                                             {
        add_to_node_list(((node_list)(yystack.valueAt (4))), create_field_init_node(((string)(yystack.valueAt (2))), ((node)(yystack.valueAt (0)))));
        yyval = ((node_list)(yystack.valueAt (4)));
    };
  break;



/* "parser.java":2350  */

        default: break;
      }

    yystack.pop(yylen);
    yylen = 0;
    /* Shift the result of the reduction.  */
    int yystate = yyLRGotoState(yystack.stateAt(0), yyr1_[yyn]);
    yystack.push(yystate, yyval);
    return YYNEWSTATE;
  }




  /**
   * Parse input from the scanner that was specified at object construction
   * time.  Return whether the end of the input was reached successfully.
   *
   * @return <tt>true</tt> if the parsing succeeds.  Note that this does not
   *          imply that there were no syntax errors.
   */
  public boolean parse() throws java.io.IOException

  {


    /* Lookahead token kind.  */
    int yychar = YYEMPTY_;
    /* Lookahead symbol kind.  */
    SymbolKind yytoken = null;

    /* State.  */
    int yyn = 0;
    int yylen = 0;
    int yystate = 0;
    YYStack yystack = new YYStack ();
    int label = YYNEWSTATE;



    /* Semantic value of the lookahead.  */
    Object yylval = null;

    yyerrstatus_ = 0;
    yynerrs = 0;

    /* Initialize the stack.  */
    yystack.push (yystate, yylval);



    for (;;)
      switch (label)
      {
        /* New state.  Unlike in the C/C++ skeletons, the state is already
           pushed when we come here.  */
      case YYNEWSTATE:

        /* Accept?  */
        if (yystate == YYFINAL_)
          return true;

        /* Take a decision.  First try without lookahead.  */
        yyn = yypact_[yystate];
        if (yyPactValueIsDefault (yyn))
          {
            label = YYDEFAULT;
            break;
          }

        /* Read a lookahead token.  */
        if (yychar == YYEMPTY_)
          {

            yychar = yylexer.yylex ();
            yylval = yylexer.getLVal();

          }

        /* Convert token to internal form.  */
        yytoken = yytranslate_ (yychar);

        if (yytoken == SymbolKind.S_YYerror)
          {
            // The scanner already issued an error message, process directly
            // to error recovery.  But do not keep the error token as
            // lookahead, it is too special and may lead us to an endless
            // loop in error recovery. */
            yychar = Lexer.YYUNDEF;
            yytoken = SymbolKind.S_YYUNDEF;
            label = YYERRLAB1;
          }
        else
          {
            /* If the proper action on seeing token YYTOKEN is to reduce or to
               detect an error, take that action.  */
            yyn += yytoken.getCode();
            if (yyn < 0 || YYLAST_ < yyn || yycheck_[yyn] != yytoken.getCode())
              label = YYDEFAULT;

            /* <= 0 means reduce or error.  */
            else if ((yyn = yytable_[yyn]) <= 0)
              {
                if (yyTableValueIsError (yyn))
                  label = YYERRLAB;
                else
                  {
                    yyn = -yyn;
                    label = YYREDUCE;
                  }
              }

            else
              {
                /* Shift the lookahead token.  */
                /* Discard the token being shifted.  */
                yychar = YYEMPTY_;

                /* Count tokens shifted since error; after three, turn off error
                   status.  */
                if (yyerrstatus_ > 0)
                  --yyerrstatus_;

                yystate = yyn;
                yystack.push (yystate, yylval);
                label = YYNEWSTATE;
              }
          }
        break;

      /*-----------------------------------------------------------.
      | yydefault -- do the default action for the current state.  |
      `-----------------------------------------------------------*/
      case YYDEFAULT:
        yyn = yydefact_[yystate];
        if (yyn == 0)
          label = YYERRLAB;
        else
          label = YYREDUCE;
        break;

      /*-----------------------------.
      | yyreduce -- Do a reduction.  |
      `-----------------------------*/
      case YYREDUCE:
        yylen = yyr2_[yyn];
        label = yyaction(yyn, yystack, yylen);
        yystate = yystack.stateAt (0);
        break;

      /*------------------------------------.
      | yyerrlab -- here on detecting error |
      `------------------------------------*/
      case YYERRLAB:
        /* If not already recovering from an error, report this error.  */
        if (yyerrstatus_ == 0)
          {
            ++yynerrs;
            if (yychar == YYEMPTY_)
              yytoken = null;
            yyreportSyntaxError (new Context (yystack, yytoken));
          }

        if (yyerrstatus_ == 3)
          {
            /* If just tried and failed to reuse lookahead token after an
               error, discard it.  */

            if (yychar <= Lexer.YYEOF)
              {
                /* Return failure if at end of input.  */
                if (yychar == Lexer.YYEOF)
                  return false;
              }
            else
              yychar = YYEMPTY_;
          }

        /* Else will try to reuse lookahead token after shifting the error
           token.  */
        label = YYERRLAB1;
        break;

      /*-------------------------------------------------.
      | errorlab -- error raised explicitly by YYERROR.  |
      `-------------------------------------------------*/
      case YYERROR:
        /* Do not reclaim the symbols of the rule which action triggered
           this YYERROR.  */
        yystack.pop (yylen);
        yylen = 0;
        yystate = yystack.stateAt (0);
        label = YYERRLAB1;
        break;

      /*-------------------------------------------------------------.
      | yyerrlab1 -- common code for both syntax error and YYERROR.  |
      `-------------------------------------------------------------*/
      case YYERRLAB1:
        yyerrstatus_ = 3;       /* Each real token shifted decrements this.  */

        // Pop stack until we find a state that shifts the error token.
        for (;;)
          {
            yyn = yypact_[yystate];
            if (!yyPactValueIsDefault (yyn))
              {
                yyn += SymbolKind.S_YYerror.getCode();
                if (0 <= yyn && yyn <= YYLAST_
                    && yycheck_[yyn] == SymbolKind.S_YYerror.getCode())
                  {
                    yyn = yytable_[yyn];
                    if (0 < yyn)
                      break;
                  }
              }

            /* Pop the current state because it cannot handle the
             * error token.  */
            if (yystack.height == 0)
              return false;


            yystack.pop ();
            yystate = yystack.stateAt (0);
          }

        if (label == YYABORT)
          /* Leave the switch.  */
          break;



        /* Shift the error token.  */

        yystate = yyn;
        yystack.push (yyn, yylval);
        label = YYNEWSTATE;
        break;

        /* Accept.  */
      case YYACCEPT:
        return true;

        /* Abort.  */
      case YYABORT:
        return false;
      }
}




  /**
   * Information needed to get the list of expected tokens and to forge
   * a syntax error diagnostic.
   */
  public static final class Context
  {
    Context (YYStack stack, SymbolKind token)
    {
      yystack = stack;
      yytoken = token;
    }

    private YYStack yystack;


    /**
     * The symbol kind of the lookahead token.
     */
    public final SymbolKind getToken ()
    {
      return yytoken;
    }

    private SymbolKind yytoken;
    static final int NTOKENS = YYParser.YYNTOKENS_;

    /**
     * Put in YYARG at most YYARGN of the expected tokens given the
     * current YYCTX, and return the number of tokens stored in YYARG.  If
     * YYARG is null, return the number of expected tokens (guaranteed to
     * be less than YYNTOKENS).
     */
    int getExpectedTokens (SymbolKind yyarg[], int yyargn)
    {
      return getExpectedTokens (yyarg, 0, yyargn);
    }

    int getExpectedTokens (SymbolKind yyarg[], int yyoffset, int yyargn)
    {
      int yycount = yyoffset;
      int yyn = yypact_[this.yystack.stateAt (0)];
      if (!yyPactValueIsDefault (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative
             indexes in YYCHECK.  In other words, skip the first
             -YYN actions for this state because they are default
             actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST_ - yyn + 1;
          int yyxend = yychecklim < NTOKENS ? yychecklim : NTOKENS;
          for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck_[yyx + yyn] == yyx && yyx != SymbolKind.S_YYerror.getCode()
                && !yyTableValueIsError(yytable_[yyx + yyn]))
              {
                if (yyarg == null)
                  yycount += 1;
                else if (yycount == yyargn)
                  return 0; // FIXME: this is incorrect.
                else
                  yyarg[yycount++] = SymbolKind.get(yyx);
              }
        }
      if (yyarg != null && yycount == yyoffset && yyoffset < yyargn)
        yyarg[yycount] = null;
      return yycount - yyoffset;
    }
  }



  /**
   * Build and emit a "syntax error" message in a user-defined way.
   *
   * @param ctx  The context of the error.
   */
  private void yyreportSyntaxError(Context yyctx) {
      yyerror("syntax error");
  }

  /**
   * Whether the given <code>yypact_</code> value indicates a defaulted state.
   * @param yyvalue   the value to check
   */
  private static boolean yyPactValueIsDefault (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  /**
   * Whether the given <code>yytable_</code>
   * value indicates a syntax error.
   * @param yyvalue the value to check
   */
  private static boolean yyTableValueIsError (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  private static final short yypact_ninf_ = -300;
  private static final short yytable_ninf_ = -1;

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
  private static final short[] yypact_ = yypact_init();
  private static final short[] yypact_init()
  {
    return new short[]
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
  }

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
  private static final short[] yydefact_ = yydefact_init();
  private static final short[] yydefact_init()
  {
    return new short[]
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
  }

/* YYPGOTO[NTERM-NUM].  */
  private static final short[] yypgoto_ = yypgoto_init();
  private static final short[] yypgoto_init()
  {
    return new short[]
    {
    -300,  -300,    61,  -300,  -300,    -7,  -300,  -300,  -300,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,    25,  -300,  -300,  -300,
    -185,  -111,   138,  -191,  -300,   251,  -300,  -300,  -299,  -300,
    -300,  -300,  -300,  -300,  -300,  -300,  -300,  -300,    69,  -300,
    -300,    27,  -255,  -300,  -300,  -300,  -300,  -300,  -300,    -6,
    -300,  -300,  -300,  -300,   -25,  -300,  -300,  -300,    49,  -300,
    -300,  -300,  -300,  -300,  -300
    };
  }

/* YYDEFGOTO[NTERM-NUM].  */
  private static final short[] yydefgoto_ = yydefgoto_init();
  private static final short[] yydefgoto_init()
  {
    return new short[]
    {
       0,    48,    49,    50,    51,    52,    53,    54,    55,    56,
     343,   372,    57,    58,    59,   184,   258,   383,    60,    61,
      62,   125,   126,   245,    63,   165,   166,    64,   349,    65,
      66,    67,    68,    69,    70,    71,    72,   273,   274,   275,
      73,   262,   263,    74,   265,    75,    76,   268,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,   235,    87,
      88,    89,   136,    90,   281
    };
  }

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
  private static final short[] yytable_ = yytable_init();
  private static final short[] yytable_init()
  {
    return new short[]
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
  }

private static final short[] yycheck_ = yycheck_init();
  private static final short[] yycheck_init()
  {
    return new short[]
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
  }

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
  private static final short[] yystos_ = yystos_init();
  private static final short[] yystos_init()
  {
    return new short[]
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
  }

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  private static final short[] yyr1_ = yyr1_init();
  private static final short[] yyr1_init()
  {
    return new short[]
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
  }

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
  private static final byte[] yyr2_ = yyr2_init();
  private static final byte[] yyr2_init()
  {
    return new byte[]
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
  }




  /* YYTRANSLATE_(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
     as returned by yylex, with out-of-bounds checking.  */
  private static final SymbolKind yytranslate_(int t)
  {
    // Last valid token kind.
    int code_max = 358;
    if (t <= 0)
      return SymbolKind.S_YYEOF;
    else if (t <= code_max)
      return SymbolKind.get(yytranslate_table_[t]);
    else
      return SymbolKind.S_YYUNDEF;
  }
  private static final byte[] yytranslate_table_ = yytranslate_table_init();
  private static final byte[] yytranslate_table_init()
  {
    return new byte[]
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
  }


  private static final int YYLAST_ = 3268;
  private static final int YYEMPTY_ = -2;
  private static final int YYFINAL_ = 140;
  private static final int YYNTOKENS_ = 104;


}
/* "parser.y":890  */


void yyerror(const char* msg) {
    fprintf(stderr, "Error at line %d: %s near '%s'\n", yylineno, msg, yytext);
}

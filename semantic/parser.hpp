/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 17 "parser.y"
 
	extern int yylineno;
	#include "ast.hpp" 	
	#include <string>

#line 55 "parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_and = 258,                   /* "and"  */
    T_end = 259,                   /* "end"  */
    T_list = 260,                  /* "list"  */
    T_ref = 261,                   /* "ref"  */
    T_bool = 262,                  /* "bool"  */
    T_exit = 263,                  /* "exit"  */
    T_mod = 264,                   /* "mod"  */
    T_return = 265,                /* "return"  */
    T_char = 266,                  /* "char"  */
    T_false = 267,                 /* "false"  */
    T_true = 268,                  /* "true"  */
    T_new = 269,                   /* "new"  */
    T_skip = 270,                  /* "skip"  */
    T_decl = 271,                  /* "decl"  */
    T_for = 272,                   /* "for"  */
    T_nil = 273,                   /* "nil"  */
    T_tail = 274,                  /* "tail"  */
    T_head = 275,                  /* "head"  */
    T_def = 276,                   /* "def"  */
    T_nilq = 277,                  /* "nil?"  */
    T_if = 278,                    /* "if"  */
    T_else = 279,                  /* "else"  */
    T_elsif = 280,                 /* "elsif"  */
    T_not = 281,                   /* "not"  */
    T_int = 282,                   /* "int"  */
    T_or = 283,                    /* "or"  */
    T_assign = 284,                /* ":="  */
    T_ge = 285,                    /* ">="  */
    T_le = 286,                    /* "<="  */
    T_neq = 287,                   /* "<>"  */
    T_constInt = 288,              /* T_constInt  */
    T_var = 289,                   /* T_var  */
    T_constChar = 290,             /* T_constChar  */
    T_constString = 291,           /* T_constString  */
    UPLUS = 292,                   /* UPLUS  */
    UMINUS = 293                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "parser.y"

	FunctionDefinition 			*func_def;
	FunctionDeclaration 		*func_decl;
	DefinitionList 				*def_list;
	Header 						*header;
	Stmt 						*stmt;
	StmtList 					*stmt_list;
	Formal 						*formal;
	FormalList 					*formal_list;
	Expr 						*expr;
	ExprList 					*expr_list;
	Var 						*var;
	VarList 					*var_list;
	VarDefinition 				*var_definition;
	If 							*ifClass;
	For 						*forClass;
	CallObject 					*call_object;
	Type 						type;

	char 						chr;
	int 						num;
	const char 					*str;

#line 134 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

%{
#include <cstdio>
#include "lexer.hpp"
#include "parser.hpp"



%}



%define parse.error verbose

// %union {
//   Block *block;
//   Stmt *stmt;
//   Expr *expr;
//   char str[32];
//   int num;
//   char c;
//   bool b;
//   BinOp *op;
// }

%token T_and	"and"
%token T_bool	"bool"
%token T_char	"char"
%token T_decl	"decl"
%token T_def	"def"
%token T_else	"else"
%token T_elsif	"elsif"
%token T_end	"end"
%token T_exit	"exit"
%token T_false	"false"
%token T_for	"for"
%token T_head	"head"
%token T_if		"if"
%token T_int	"int"
%token T_list	"list"
%token T_mod	"mod"
%token T_new	"new"
%token T_nil	"nil"
%token T_nilq	"nil?"
%token T_not	"not"
%token T_or		"or"
%token T_ref	"ref"
%token T_return	"return"
%token T_skip	"skip"
%token T_tail	"tail"
%token T_true	"true"
%token T_le		"<="
%token T_ge		">="
%token T_neq	"<>"
%token T_eq		"="
%token T_less	"<"
%token T_greater ">"
%token T_assign	":="
%token T_colon  ":"
%token T_lparen "("
%token T_rparen ")"
%token T_lbracket "["
%token T_rbracket "]"
%token T_semicolon ";"
%token T_comma ","
%token T_plus "+"
%token T_minus "-"
%token T_multiply "*"
%token T_divide "/"
%token T_listadd "#"

%token	T_var
%token	T_constInt
%token	T_constChar
%token	T_constString


// %type<block>	program stmt_list
// %type<stmt>		stmt
// %type<expr>		expr
// %type<op>		arithmetic_operator

// %type<name> header

// %type<type> type

// %type<stmt> func_decl
// %type<stmt> var_def
// %type<stmt> stmt


// %type<stmt> formal
// %type<stmt> formal_list
// %type<stmt> simple
// %type<stmt> simple_list
// %type<stmt> elsif_list


// %type<stmt> stmt_list

// %type<stmt> expr_list
// %type<expr> expr

// %type<atom> atom 

// %type<call> call

// %type<stmt> plus_or_minus
// %type<stmt> arithmetic_operator
// %type<stmt> relational_operator


%left T_or
%left T_and
%nonassoc T_not
%nonassoc T_eq T_neq T_greater T_less T_ge T_le
%right T_listadd
%left T_plus T_minus
%left T_multiply T_divide T_mod
%nonassoc UMINUS UPLUS







%%

program:
	func_def
;

func_def:
    T_def header T_colon definition_list stmt_list T_end
;

definition_list:
 /* nothing */
|   func_def definition_list
|   func_decl definition_list
|   var_def definition_list
;

header:
    T_var T_lparen formal_list T_rparen
|   type T_var T_lparen formal_list T_rparen
;

formal:
	type id_list
|	T_ref type id_list
;

formal_list:
    /* nothing */
|   formal
|   formal T_semicolon formal_list
;

type:
    T_int
|   T_bool
|   T_char
|   type T_lbracket T_rbracket
|   T_list T_lbracket type T_rbracket
;

func_decl:
    T_decl header
;

id_list:
    T_var T_comma id_list
|	T_var
;

var_def:
	type id_list
;

elsif_list:
	/* nothing */
|	T_elsif expr T_colon stmt_list elsif_list
;

else:
	/* nothing */
|	T_else T_colon stmt_list
;

stmt:
	simple
|	T_exit
|	T_return expr
|	T_if expr T_colon stmt_list elsif_list else T_end {  }
|	T_for simple_list T_semicolon expr T_semicolon simple_list T_colon stmt_list T_end
;

stmt_list:
	stmt stmt_list
|	stmt
;

simple:
	T_skip
|	atom T_assign expr
|	call
;

simple_list:
	simple
|	simple T_comma simple_list
;

expr_list:
	/* nothing */
|	expr
|	expr T_comma expr_list
;

call:
	T_var T_lparen expr_list T_rparen
;

atom:
	T_var
|	T_constString
|	atom T_lbracket expr T_rbracket
|	call
;


expr:
	atom
|	T_constInt
|	T_constChar
|	T_lparen expr T_rparen

|	T_plus expr %prec UPLUS
|	T_minus expr %prec UMINUS

|	expr T_plus expr
|	expr T_minus expr
|	expr T_multiply expr
|	expr T_divide expr
|	expr T_mod expr

|	expr T_eq expr
|	expr T_neq expr
|	expr T_greater expr
|	expr T_less expr
|	expr T_ge expr
|	expr T_le expr

|	T_true
|	T_false
|	T_not expr
|	expr T_and expr
|	expr T_or expr
|	T_new type T_lbracket expr T_rbracket
|	T_nil
|	T_nilq T_lparen expr T_rparen
|	expr T_listadd expr
|	T_head T_lparen expr T_rparen
|	T_tail T_lparen expr T_rparen
;


%%

void yyerror (const char * msg)
{
	fprintf(stderr,"error :  %s\n",msg);
	exit(1);
}

int main() 
{
  int result = yyparse();
  if (result == 0) 
  	printf("Success.\n");
  return result;
}
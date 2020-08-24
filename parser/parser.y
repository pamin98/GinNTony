%{
#include <cstdio>
#include "lexer.hpp"
%}
%define parse.error verbose

%token		T_and			"and"
%token		T_end			"end"
%token		T_list			"list"
%token		T_ref			"ref"
%token		T_bool			"bool"
%token		T_exit			"exit"
%token		T_mod			"mod"
%token		T_return		"return"
%token		T_char			"char"
%token		T_false			"false"
%token		T_true			"true"
%token		T_new			"new"
%token		T_skip			"skip"
%token		T_decl			"decl"
%token		T_for			"for"
%token		T_nil			"nil"
%token		T_tail			"tail"
%token		T_head			"head"
%token 		T_def			"def"
%token		T_nilq			"nil?"
%token		T_if			"if"
%token		T_else			"else"
%token		T_elsif			"elsif"
%token		T_not			"not"
%token		T_int			"int"
%token		T_or 			"or"
%token		T_assign		":="			
%token		T_ge			">="
%token		T_le 			"<="
%token		T_neq			"<>"
%token  	T_constInt		
%token		T_var
%token		T_constChar		
%token		T_constString	

%left "or"
%left "and"
%nonassoc "not"	
%nonassoc '=' '>' '<' "<=" ">=" "<>"
%right '#'
%left '+' '-'
%left '*' '/' "mod"
%nonassoc UPLUS UMINUS

%%

program:		
		func_def
		;

func_def:
		"def" header ':' definition_list stmt_list "end"
		;

definition_list:
		
		| func_def definition_list
		| func_decl definition_list
		| var_def definition_list
		;

stmt_list:
		  stmt
		| stmt stmt_list
		;

header:
		  T_var '(' formal_list ')'
		| type T_var '(' formal_list ')'
		;

formal_list:
		
		| formal formal_tail
		;

formal_tail:
		
		| ';' formal formal_tail
		;

formal:
		  type var_list
		| "ref" type var_list
		;

var_list:
		  T_var
		| T_var ',' var_list
		; 

type:
		  "int"
		| "bool"
		| "char"
		| type '[' ']'
		| "list" '[' type ']'
		;

func_decl:
		"decl" header
		;

var_def:
		type var_list
		;

stmt:
		  simple
		| "exit"
		| "return" expr
		| "if" expr ':' stmt_list elsif_list else "end"
		| "for" simple_list ';' expr ';' simple_list ':' stmt_list "end"
		;

elsif_list:
		
		| "elsif" expr ':' stmt_list elsif_list
		;

else:
		
		| "else" ':' stmt_list
		;

simple:
		  "skip"
		| atom ":=" expr
		| call
		;

simple_list:
		  simple
		| simple ',' simple_list
		;

call:
		T_var '(' expr_list ')'
		;

expr_list:
		
		| expr expr_tail
		;

expr_tail:
		
		| ',' expr expr_tail
		;

atom:
		  T_var
		| T_constString
		| atom '[' expr ']'
		| call
		;

expr:
		  atom
		| T_constInt
		| T_constChar
		| '(' expr ')'
		| '+' expr %prec UPLUS
		| '-' expr %prec UMINUS
		| expr '+' expr
		| expr '-' expr
		| expr '*' expr
		| expr '/' expr
		| expr "mod" expr
		| expr '=' expr
		| expr '>' expr
		| expr '<' expr
		| expr "<>" expr
		| expr "<=" expr
		| expr ">=" expr
		| "true"
		| "false"
		| "not" expr
		| expr "and" expr
		| expr "or" expr
		| "new" type '[' expr ']' 
		| "nil"
		| "nil?" '(' expr ')'
		| expr '#' expr
		| "head" '(' expr ')'
		| "tail" '(' expr ')'
		;

%%

int main() {
  int result = yyparse();
  if (result == 0) printf("Success.\n");
  return result;
}
%{
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <string.h>

#include "ast.hpp"
#include "lexer.hpp"



%}

%code requires 
{ 
	#include "ast.hpp" 	
	#include <string>
}

%define parse.error verbose

%union {
	StmtList *stmt_list;
	Stmt *stmt;
	Expr *expr;
	If *ifClass;
	For *forClass;
	ExprList* expr_list;
	CallObject *call_object;
	Var *var;
	std::string *type;
	VarList *var_list;
	VarDefinition *var_definition;
	Formal *formal;
	FormalList *formal_list;
	FunctionDefinition *func_def;
	FunctionDeclaration *func_decl;
	DefinitionList *def_list;
	Header *header;

	char chr;
	int num;
	char op;
	const char *str;
}

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
%token<num>  			T_constInt
%token<var>				T_var
%token<num>				T_constChar		
%token<str>				T_constString	


%left "or"
%left "and"
%nonassoc "not"	
%nonassoc '=' '>' '<' "<=" ">=" "<>"
%right '#'
%left '+' '-'
%left '*' '/' "mod"
%nonassoc UPLUS UMINUS


%type<ifClass> elsif_list
%type<stmt_list> stmt_list
%type<ifClass> else
%type<stmt> stmt
%type<stmt> simple
%type<expr> expr
%type<expr> atom
%type<expr_list> expr_list
%type<expr_list> expr_tail
%type<call_object> call
%type<type> type
%type<stmt_list> simple_list
%type<var_list> var_list
%type<var_definition> var_def
%type<formal> formal
%type<formal_list> formal_list
%type<formal_list> formal_tail
%type<def_list> definition_list
%type<func_def> func_def
%type<func_decl> func_decl
%type<header> header
%type<func_def> program

%%

program:		
		func_def
		;

func_def:
		"def" header ':' definition_list stmt_list "end"	{ $$ = new FunctionDefinition($2,$4,$5); }
		;

func_decl:
		"decl" header			{ $$ = new FunctionDeclaration($2); }
		;

definition_list:
									{ $$ = new DefinitionList(); }
	| func_def definition_list		{ $2->append($1); $$=$2; }
	| func_decl definition_list		{ $2->append($1); $$=$2; }
	| var_def definition_list		{ $2->append($1); $$=$2; }
	;

stmt_list:
			stmt			{ $$ = new StmtList($1); }
		|	stmt stmt_list	{ $2->append($1); $$=$2; }
		;

header:
		  T_var '(' formal_list ')'			{ $$ = new Header($1,$3); }
		| type T_var '(' formal_list ')'	{ $$ = new Header($2,$4,$1); }
		;

formal_list:
									{ $$ = new FormalList(); }
		|	formal formal_tail		{ $2->append($1) ; $$ = $2; }
		;

formal_tail:
									{ $$ = new FormalList(); }
		| ';' formal formal_tail	{ $3->append($2); $$ = $3; }
		;

formal:
		  type var_list			{ $$ = new Formal($1,$2); }
		| "ref" type var_list 	{ $$ = new Formal($2,$3,true); }
		; 

var_list:
		T_var 					{ $$ = new VarList($1); }
	|	T_var ',' var_list 		{ $3->append($1); $$ = $3; }
	; 

type:
		  "int"					{ $$ = new std::string("int"); }
		| "bool"				{ $$ = new std::string("bool"); }
		| "char"				{ $$ = new std::string("char"); }
		| type '[' ']'			{ $1->append("[]"); $$=$1; }
		| "list" '[' type ']'	{ $$ = new std::string("list ["); $$->append($3->c_str()) ; $$->append("]"); };
		;


var_def:
		type var_list			{ $$ = new VarDefinition($1,$2); }
		;


stmt:
		  simple															{ $$ = $1; }
		| "exit" 															{ $$ = new ExitStmt(); }
		| "return" expr 													{ $$ = new ReturnStmt($2); }
		| "if" expr ':' stmt_list elsif_list "end" 							{ $$ = new If($2,$4,$5); }	
		| "for" simple_list ';' expr ';' simple_list ':' stmt_list "end"	{ $$ = new For($2,$4,$6,$8); }
		;

elsif_list:
			else	{ $$ = $1; }
		|	"elsif" expr ':' stmt_list elsif_list	{ $$ = new If($2,$4,$5); }
		;

else:
		/* nothing */			{ $$ = NULL; }
		| "else" ':' stmt_list	{ $$ = new If(NULL,$3,NULL); }
		;

simple:
		  "skip"					{  }
		| atom ":=" expr			{ $$ = new AssignStmt($1,$3); }
		| call						{ $$ = $1; }
		;

simple_list:
		simple					{ $$ = new StmtList($1); }
	|	simple ',' simple_list	{ $3->append($1); $$ = $3; }
	;

call:
		T_var '(' expr_list ')' 	{ $$ = new CallObject($1,$3); }
		;

expr_list:
		/* nothing */ 				{ $$ = new ExprList(); }
		| expr expr_tail			{ $2->append($1); $2->reverse() ; $$ = $2; }
		;

expr_tail:
		 							{ $$ = new ExprList(); }
		| ',' expr expr_tail		{ $3->append($2) ; $$ = $3; }
		;

atom:
		  T_var						{ $$ = $1; }
		| T_constString				{ $$ = new ConstString($1); }
		| atom '[' expr ']'			{ $$ = new ArrayIndexing($1,$3); }		
		| call						{ $$ = $1; }
		;

expr:
		  atom						
		  	{ $$ = $1; }
		| T_constInt				{ $$ = new Const($1); }
		| T_constChar				{ $$ = new Const($1); }
		| '(' expr ')'				{ $$ = $2; }
		| '+' expr %prec UPLUS		{ $$ = new BinOp(NULL,'+',$2); }
		| '-' expr %prec UMINUS		{ $$ = new BinOp(NULL,'-',$2); }
		| expr '+' expr				{ $$ = new BinOp($1,'+',$3); }
		| expr '-' expr				{ $$ = new BinOp($1,'-',$3); }
		| expr '*' expr				{ $$ = new BinOp($1,'*',$3); }
		| expr '/' expr				{ $$ = new BinOp($1,'/',$3); }
		| expr "mod" expr			{ $$ = new BinOp($1,'%',$3); }
		| expr '=' expr				{ $$ = new RelOp($1,eq,$3); }
		| expr '>' expr				{ $$ = new RelOp($1,gt,$3); }
		| expr '<' expr				{ $$ = new RelOp($1,lt,$3); }
		| expr "<>" expr			{ $$ = new RelOp($1,neq,$3); }
		| expr "<=" expr			{ $$ = new RelOp($1,le,$3); }
		| expr ">=" expr			{ $$ = new RelOp($1,ge,$3); }
		| "true"					{ $$ = new LogOp(TRUE); }
		| "false"					{ $$ = new LogOp(FALSE); }
		| "not" expr				{ $$ = new LogOp(NOT,NULL,$2); }
		| expr "and" expr			{ $$ = new LogOp(AND,$1,$3); }
		| expr "or" expr			{ $$ = new LogOp(OR,$1,$3); }
		| "new" type '[' expr ']' 	{ $$ = new ArrayInit($2,$4); }
		| "nil"						{ $$ = new ListOp(nil,NULL,NULL); }
		| "nil?" '(' expr ')'		{ $$ = new ListOp(nilq,NULL,$3); }
		| expr '#' expr				{ $$ = new ListOp(append,$1,$3); }
		| "head" '(' expr ')'		{ $$ = new ListOp(head,NULL,$3); }
		| "tail" '(' expr ')'		{ $$ = new ListOp(tail,NULL,$3); }
		;

%%

int main() 
{
	int result = yyparse();
	if (result == 0) printf("Success.\n");
	return result;
}
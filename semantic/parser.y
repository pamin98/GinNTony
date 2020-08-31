%{
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "ast.hpp"
#include "lexer.hpp"
#include "symbol.hpp"

#define 	ST_SIZE 	257
%}

%code requires 
{ 
	#include "ast.hpp" 	
	#include <string>
}

%define parse.error verbose

%union {
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

%token	<num>  		T_constInt
%token	<str>		T_var
%token	<num>		T_constChar		
%token	<str>		T_constString	


%left "or"
%left "and"
%nonassoc "not"	
%nonassoc '=' '>' '<' "<=" ">=" "<>"
%right '#'
%left '+' '-'
%left '*' '/' "mod"
%nonassoc UPLUS UMINUS


%type	<func_def> 				program
%type	<func_def> 				func_def
%type	<func_decl>				func_decl
%type	<def_list>			 	definition_list
%type	<header> 				header_def
%type	<header> 				header_decl
%type	<formal> 				formal
%type	<formal_list> 			formal_list
%type	<formal_list> 			formal_head
%type	<var_list> 				var_list
%type	<var_definition> 		var_def
%type	<type> 					type
%type	<ifClass> 				elsif_list
%type	<ifClass> 				else
%type	<stmt> 					stmt
%type	<stmt> 					simple
%type	<stmt_list> 			simple_list
%type	<stmt_list> 			stmt_list
%type	<call_object> 			call
%type	<expr> 					expr
%type	<expr> 					atom
%type	<expr_list> 			expr_list
%type	<expr_list> 			expr_head

%%

program:		
		func_def						{ $1->sem(); }
		;

func_def:
		"def" header_def ':' definition_list stmt_list "end"	{ $$ = new FunctionDefinition($2,$4,$5, Func_Def); }
		;

func_decl:
		"decl" header_decl				{ $$ = new FunctionDeclaration($2); }
		;

definition_list:
										{ $$ = new DefinitionList(); }
		| definition_list func_def 		{ $1->append($2); $$=$1; }
		| definition_list func_decl 	{ $1->append($2); $$=$1; }
		| definition_list var_def 		{ $1->append($2); $$=$1; }
		;

stmt_list:
			stmt						{ $$ = new StmtList($1); }
		|	stmt_list stmt				{ $1->append($2); $$=$1; }
		;

header_def:
		  T_var '(' formal_list ')'			{ $$ = new Header($1, $3, typeVoid, Func_Def); }
		| type T_var '(' formal_list ')'	{ $$ = new Header($2, $4, $1, Func_Def); }
		;

header_decl:
		  T_var '(' formal_list ')'			{ $$ = new Header($1, $3, typeVoid, Func_Decl); }
		| type T_var '(' formal_list ')'	{ $$ = new Header($2, $4, $1, Func_Decl); }
		;

formal_list:
										{ $$ = new FormalList(); }
		|	formal_head formal 			{ $1->append($2) ; $$ = $1; }
		;

formal_head:
		  								{ $$ = new FormalList(); }
		| formal_head formal ';' 		{ $1->append($2); $$ = $1; }
		;

formal:
		  type var_list					{ $$ = new Formal($1,$2); }
		| "ref" type var_list 			{ $$ = new Formal($2,$3,true); }
		; 

var_list:
			T_var 						{ $$ = new VarList($1); }
		|	var_list ',' T_var			{ $1->append($3); $$ = $1; }
	; 

type:
		  "int"							{ $$ = typeInteger; }
		| "bool"						{ $$ = typeBoolean; }
		| "char"						{ $$ = typeChar; }
		| type '[' ']'					{ $$ = typeIArray($1); }
		| "list" '[' type ']'			{ $$ = typePointer($3); };
		;


var_def:
		type var_list					{ $$ = new VarDefinition($1,$2); }
		;


stmt:
		  simple															{ $$ = $1; }
		| "exit" 															{ $$ = new ExitStmt(); }
		| "return" expr 													{ $$ = new ReturnStmt($2); }
		| "if" expr ':' stmt_list elsif_list "end" 							{ $$ = new If($2,$4,$5); }	
		| "for" simple_list ';' expr ';' simple_list ':' stmt_list "end"	{ $$ = new For($2,$4,$6,$8); }
		;

elsif_list:
			else									{ $$ = $1; }
		|	"elsif" expr ':' stmt_list elsif_list	{ $$ = new If($2,$4,$5); }
		;

else:
		/* nothing */					{ $$ = NULL; }
		| "else" ':' stmt_list			{ $$ = new If(NULL,$3,NULL); }
		;

simple:
		  "skip"						{  }
		| atom ":=" expr				{ $$ = new AssignStmt($1,$3); }
		| call							{ $$ = $1; }
		;

simple_list:
			simple						{ $$ = new StmtList($1); }
		|	simple_list ',' simple		{ $1->append($3); $$ = $1; }
	;

call:
		T_var '(' expr_list ')' 		{ $$ = new CallObject($1,$3); }
		;

expr_list:
		/* nothing */ 					{ $$ = new ExprList(); }
		| expr_head expr				{ $1->append($2); $$ = $1; }
		;

expr_head:
		 								{ $$ = new ExprList(); }
		| expr_head expr ',' 			{ $1->append($2); $$ = $1; }
		;

atom:
		  T_var							{ $$ = new Var($1); }
		| T_constString					{ $$ = new ConstString($1); }
		| atom '[' expr ']'				{ $$ = new ArrayIndexing($1,$3); }		
		| call							{ $$ = $1; }
		;

expr:
		  atom						  	{ $$ = $1; }
		| T_constInt					{ $$ = new ConstInt($1); }
		| T_constChar					{ $$ = new ConstInt($1); }
		| '(' expr ')'					{ $$ = $2; }
		| '+' expr %prec UPLUS			{ $$ = new BinOp(NULL,'+',$2); }
		| '-' expr %prec UMINUS			{ $$ = new BinOp(NULL,'-',$2); }
		| expr '+' expr					{ $$ = new BinOp($1,'+',$3); }
		| expr '-' expr					{ $$ = new BinOp($1,'-',$3); }
		| expr '*' expr					{ $$ = new BinOp($1,'*',$3); }
		| expr '/' expr					{ $$ = new BinOp($1,'/',$3); }
		| expr "mod" expr				{ $$ = new BinOp($1,'%',$3); }
		| expr '=' expr					{ $$ = new RelOp($1,eq,$3); }
		| expr '>' expr					{ $$ = new RelOp($1,gt,$3); }
		| expr '<' expr					{ $$ = new RelOp($1,lt,$3); }
		| expr "<>" expr				{ $$ = new RelOp($1,neq,$3); }
		| expr "<=" expr				{ $$ = new RelOp($1,le,$3); }
		| expr ">=" expr				{ $$ = new RelOp($1,ge,$3); }
		| "true"						{ $$ = new LogOp(TRUE); }
		| "false"						{ $$ = new LogOp(FALSE); }
		| "not" expr					{ $$ = new LogOp(NOT,NULL,$2); }
		| expr "and" expr				{ $$ = new LogOp(AND,$1,$3); }
		| expr "or" expr				{ $$ = new LogOp(OR,$1,$3); }
		| "new" type '[' expr ']' 		{ $$ = new ArrayInit($2,$4); }
		| "nil"							{ $$ = new ListOp(nil,NULL,NULL); }
		| "nil?" '(' expr ')'			{ $$ = new ListOp(nilq,NULL,$3); }
		| expr '#' expr					{ $$ = new ListOp(append,$1,$3); }
		| "head" '(' expr ')'			{ $$ = new ListOp(head,NULL,$3); }
		| "tail" '(' expr ')'			{ $$ = new ListOp(tail,NULL,$3); }
		;	

%%

int main(){
	initSymbolTable(ST_SIZE);
	return yyparse();
}
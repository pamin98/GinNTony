%{
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "ast.hpp"
#include "lexer.hpp"
#include "symbol.hpp"


extern FILE *yyin;

bool optimize = false;
extern char *filename;


// ST_SIZE must be a prime number
#define 	ST_SIZE 	257
%}



%locations
%code requires 
{ 
	extern int yylineno;
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
		func_def						{ $1->sem(); $1->llvm_compile_and_dump(optimize, filename); }
		;

func_def:
		"def" header_def ':' definition_list stmt_list "end"	{ $$ = new FunctionDefinition($2,$4,$5); $$->set_line(yylineno); }
		;

func_decl:
		"decl" header_decl				{ $$ = new FunctionDeclaration($2); $$->set_line(yylineno); }
		;

definition_list:
										{ $$ = new DefinitionList(); $$->set_line(yylineno);}
		| definition_list func_def 		{ $1->append($2); $$=$1; }
		| definition_list func_decl 	{ $1->append($2); $$=$1; }
		| definition_list var_def 		{ $1->append($2); $$=$1; }
		;

stmt_list:
			stmt						{ $$ = new StmtList($1); $$->set_line(yylineno);}
		|	stmt_list stmt				{ $1->append($2); $$=$1; }
		;

header_def:
		  T_var '(' formal_list ')'			{ $$ = new Header($1, $3, typeVoid, Func_Def); $$->set_line(yylineno);}
		| type T_var '(' formal_list ')'	{ $$ = new Header($2, $4, $1, Func_Def); $$->set_line(yylineno);}
		;

header_decl:
		  T_var '(' formal_list ')'			{ $$ = new Header($1, $3, typeVoid, Func_Decl); $$->set_line(yylineno);}
		| type T_var '(' formal_list ')'	{ $$ = new Header($2, $4, $1, Func_Decl); $$->set_line(yylineno);}
		;

formal_list:
										{ $$ = new FormalList(); $$->set_line(yylineno);}
		|	formal_head formal 			{ $1->append($2) ; $$ = $1; }
		;

formal_head:
		  								{ $$ = new FormalList(); $$->set_line(yylineno);}
		| formal_head formal ';' 		{ $1->append($2); $$ = $1; }
		;

formal:
		  type var_list					{ $$ = new Formal($1,$2); $$->set_line(yylineno);}
		| "ref" type var_list 			{ $$ = new Formal($2,$3,true); $$->set_line(yylineno);}
		; 

var_list:
			T_var 						{ $$ = new VarList($1); $$->set_line(yylineno);}
		|	var_list ',' T_var			{ $1->append($3); $$ = $1; }
	; 

type:
		  "int"							{ $$ = typeInteger; }
		| "bool"						{ $$ = typeBoolean; }
		| "char"						{ $$ = typeChar; }
		| type '[' ']'					{ $$ = typeIArray($1); }
		| "list" '[' type ']'			{ $$ = typeList($3); };
		;


var_def:
		type var_list					{ $$ = new VarDefinition($1,$2); $$->set_line(yylineno);}
		;


stmt:
		  simple															{ $$ = $1; }
		| "exit" 															{ $$ = new ExitStmt(); $$->set_line(yylineno);}
		| "return" expr 													{ $$ = new ReturnStmt($2); $$->set_line(yylineno);}
		| "if" expr ':' stmt_list elsif_list "end" 							{ $$ = new If($2,$4,$5); $$->set_line(yylineno);}	
		| "for" simple_list ';' expr ';' simple_list ':' stmt_list "end"	{ $$ = new For($2,$4,$6,$8); $$->set_line(yylineno);}
		;

elsif_list:
			else									{ $$ = $1; }
		|	"elsif" expr ':' stmt_list elsif_list	{ $$ = new If($2,$4,$5); $$->set_line(yylineno);}
		;

else:
		/* nothing */					{ $$ = NULL; }
		| "else" ':' stmt_list			{ $$ = new If(NULL,$3,NULL); $$->set_line(yylineno);}
		;

simple:
		  "skip"						{ $$ = new SkipStmt(); $$->set_line(yylineno);}
		| atom ":=" expr				{ $$ = new AssignStmt($1,$3); $$->set_line(yylineno);}
		| atom ":="  "new" type '[' expr ']' { $$ = new ArrayInit($1,$4,$6); $$->set_line(yylineno);}
		| call							{ $$ = $1; }
		;

simple_list:
			simple						{ $$ = new StmtList($1); $$->set_line(yylineno);}
		|	simple_list ',' simple		{ $1->append($3); $$ = $1; }
	;

call:
		T_var '(' expr_list ')' 		{ $$ = new CallObject($1,$3); $$->set_line(yylineno);}
		;

expr_list:
		/* nothing */ 					{ $$ = new ExprList(); $$->set_line(yylineno);}
		| expr_head expr				{ $1->append($2); $$ = $1; }
		;

expr_head:
		 								{ $$ = new ExprList(); $$->set_line(yylineno);}
		| expr_head expr ',' 			{ $1->append($2); $$ = $1; }
		;

atom:
		  T_var							{ $$ = new Var($1); $$->set_line(yylineno);}
		| T_constString					{ $$ = new ConstString($1); $$->set_line(yylineno);}
		| T_constString '[' expr ']'	{ $$ = new ConstString($1,$3); $$->set_line(yylineno);}
		| T_var '[' expr ']'			{ $$ = new Var($1,$3); $$->set_line(yylineno);}		
		| call							{ $$ = $1; }
		;

expr:
		  atom						  	{ $$ = $1; }
		| T_constInt					{ $$ = new ConstInt($1); $$->set_line(yylineno);}
		| T_constChar					{ $$ = new ConstChar($1); $$->set_line(yylineno);}
		| '(' expr ')'					{ $$ = $2; }
		| '+' expr %prec UPLUS			{ $$ = new BinOp(NULL,'+',$2); $$->set_line(yylineno);}
		| '-' expr %prec UMINUS			{ $$ = new BinOp(NULL,'-',$2); $$->set_line(yylineno);}
		| expr '+' expr					{ $$ = new BinOp($1,'+',$3); $$->set_line(yylineno);}
		| expr '-' expr					{ $$ = new BinOp($1,'-',$3); $$->set_line(yylineno);}
		| expr '*' expr					{ $$ = new BinOp($1,'*',$3); $$->set_line(yylineno);}
		| expr '/' expr					{ $$ = new BinOp($1,'/',$3); $$->set_line(yylineno);}
		| expr "mod" expr				{ $$ = new BinOp($1,'%',$3); $$->set_line(yylineno);}
		| expr '=' expr					{ $$ = new RelOp($1,eq,$3); $$->set_line(yylineno);}
		| expr '>' expr					{ $$ = new RelOp($1,gt,$3); $$->set_line(yylineno);}
		| expr '<' expr					{ $$ = new RelOp($1,lt,$3); $$->set_line(yylineno);}
		| expr "<>" expr				{ $$ = new RelOp($1,neq,$3); $$->set_line(yylineno);}
		| expr "<=" expr				{ $$ = new RelOp($1,le,$3); $$->set_line(yylineno);}
		| expr ">=" expr				{ $$ = new RelOp($1,ge,$3); $$->set_line(yylineno);}
		| "true"						{ $$ = new LogOp(TRUE); $$->set_line(yylineno);}
		| "false"						{ $$ = new LogOp(FALSE); $$->set_line(yylineno);}
		| "not" expr					{ $$ = new LogOp(NOT,NULL,$2); $$->set_line(yylineno);}
		| expr "and" expr				{ $$ = new LogOp(AND,$1,$3); $$->set_line(yylineno);}
		| expr "or" expr				{ $$ = new LogOp(OR,$1,$3); $$->set_line(yylineno);}
		| "nil"							{ $$ = new ListOp(nil,NULL,NULL); $$->set_line(yylineno);}
		| "nil?" '(' expr ')'			{ $$ = new ListOp(nilq,NULL,$3); $$->set_line(yylineno);}
		| expr '#' expr					{ $$ = new ListOp(append,$1,$3); $$->set_line(yylineno);}
		| "head" '(' expr ')'			{ $$ = new ListOp(head,NULL,$3); $$->set_line(yylineno);}
		| "tail" '(' expr ')'			{ $$ = new ListOp(tail,NULL,$3); $$->set_line(yylineno);}
		;	

%%


int main(int argc, char *argv[])
{
	for(int i=1; i<argc; i++)
	{
		if(strcmp(argv[i], "-O") == 0)
			optimize = true;
		else
			filename = argv[i];
	}
	
	yyin = fopen(filename,"r");
	initSymbolTable(ST_SIZE);
	openScope();
	initPreBuiltFunctionsInST();
	int result = yyparse();
	destroySymbolTable();
	fclose(yyin);
	return result;
}
%option noyywrap

%{
#include "lexer.hpp"
#include "parser.hpp"

#define T_eof 0



int lineno = 1;
int commentLevel = 0;
%}

D 		[0-9]
W		[ \t\r]
L		[A-Za-z]
E 		\\[ntr0\\\'\"]
HD      [0-9a-fA-F]
H 		\\x{HD}{HD}

%x COMMENT 
%%

"and"						{ return T_and; }
"end"						{ return T_end; }
"list"						{ return T_list; }
"ref"						{ return T_ref; }
"bool"						{ return T_bool; }
"exit"						{ return T_exit; }
"mod"						{ return T_mod; }
"return"  					{ return T_return; }
"char" 						{ return T_char; }
"false"						{ return T_false; }
"true"						{ return T_true; }
"new"						{ return T_new; }
"skip"						{ return T_skip; }
"decl" 						{ return T_decl; }
"for"						{ return T_for; }
"nil"						{ return T_nil; }
"tail"						{ return T_tail; }
"head"						{ return T_head; }
"def"						{ return T_def; }
"nil?"						{ return T_nilq; }
"if"						{ return T_if; }
"else"						{ return T_else; }
"elsif"						{ return T_elsif; }
"not"						{ return T_not; }
"int"						{ return T_int; }
"or" 						{ return T_or; }
":="						{ return T_assign; }
"<="						{ return T_le; }
">="						{ return T_ge; }
"<>"						{ return T_neq; }
"="							{ return T_eq; }
">"							{ return T_greater; }
"<"							{ return T_less; }

":"							{ return T_colon; }
"("							{ return T_lparen; }
")"							{ return T_rparen; }
"["							{ return T_lbracket; }
"]"							{ return T_rbracket; }
";"							{ return T_semicolon; }
","							{ return T_comma; }
"+"							{ return T_plus; }
"-"							{ return T_minus; }
"*"							{ return T_multiply; }
"/"							{ return T_divide; }
"#"							{ return T_listadd; }


{L}({L}|{D}|_|\?)*			{ return T_var; }
{D}+						{ return T_constInt; }

\'([^\'\\\"]|{E}|{H})\'		{ return T_constChar; }
\"([^\'\"\\\n]|{E}|{H})*\"	{ return T_constString; }


%[^\n]*\n 					{ lineno = lineno + 1; }

"<*" 						{ commentLevel = commentLevel + 1; BEGIN(COMMENT); }
<COMMENT>"<*"				{ commentLevel = commentLevel + 1; }
<COMMENT>"*>"				{ commentLevel = commentLevel - 1; if (!commentLevel) BEGIN(INITIAL); }
<COMMENT>\n					{ lineno = lineno + 1; }
<COMMENT>\*					{ }
<COMMENT><					{ }
<COMMENT>[^<*\n]+			{ }

{W}							{ }
\n 							{ lineno = lineno + 1; }
<<EOF>>						{ return T_eof; }
.							{ fprintf(stderr, "Error: Found character %c with code %d in line %d.\n", yytext[0]>=32 ? yytext[0]:'?', yytext[0], lineno); exit(1); }
%%

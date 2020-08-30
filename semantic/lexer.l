%option noyywrap
%{
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include "lexer.hpp"
#include "parser.hpp"
#include "general.hpp"
#include "error.hpp"


#define		T_eof			0

int commentLevel = 0;

int getChar( char *chr){
	if(chr[0]!='\\')
		return chr[0];
	else
		switch(chr[1]){
			case 'n': return '\n';
			case 't': return '\t';
			case 'r': return '\r';
			case '0': return '\0';
			case '\\': return '\\';
			case '\'': return '\'';
			case '\"': return '\'';
			case 'x': { return (int)strtol(chr+2, NULL, 16); }
			default:
				internal("Unable to get char.Aborting...");
				exit(1);
		}
}

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

{L}({L}|{D}|_|\?)*			{ yylval.str = strdup(yytext);  return T_var; }
{D}+						{ yylval.num = atoi(yytext);  return T_constInt; }

\'([^\'\\\"]|{E}|{H})\'		{ yylval.chr = getChar(yytext); return T_constChar; }
\"([^\'\"\\\n]|{E}|{H})*\"	{ yylval.str = strdup(yytext); return T_constString; }

[+\-*/#=<>]					{ return yytext[0]; }
[\(\)\[\],;:]				{ return yytext[0]; }

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
.							{ fatal("found character %c with code %d.", yytext[0]>=32 ? yytext[0]:'?', yytext[0]); }

%%

void yyerror (const char * msg){
	error(msg);
	exit(1);
}

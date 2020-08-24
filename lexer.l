%option noyywrap

%{
#define		T_eof			0
#define		T_and			1001
#define		T_end			1002
#define		T_list			1003
#define		T_ref			1004
#define		T_bool			1005
#define		T_exit			1006
#define		T_mod			1007
#define		T_return		1008
#define		T_char			1009
#define		T_false			1010
#define		T_true			1011
#define		T_new			1012
#define		T_skip			1013
#define		T_decl			1014
#define		T_for			1015
#define		T_nil			1016
#define		T_tail			1017
#define		T_head			1018
#define 	T_def			1019
#define		T_nilq			1020
#define		T_if			1021
#define		T_else			1022
#define		T_elsif			1023
#define		T_not			1024
#define		T_int			1025
#define		T_or 			1026
#define		T_assign		1027
#define  	T_constInt		1028
#define		T_var			1029
#define		T_ge			1030
#define		T_le 			1031
#define		T_neq			1032
#define		T_constChar		1033
#define		T_constString	1034
//-----
#define		T_colon			1035
#define		T_lparen		1036
#define		T_rparen		1037
#define		T_lbracket		1038
#define		T_rbracket		1039
#define		T_semicolon		1040
#define		T_comma			1041
#define		T_plus			1042
#define 	T_minus			1043
#define		T_multiply		1044
#define		T_divide		1045

#define		T_eq			1046
#define		T_greater		1047
#define		T_less			1048
#define		T_listadd		1049



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



#ifdef yyFlexLexer
int main () {
  yyFlexLexer lexer;
  int token;
  do {
    token = lexer.yylex();
    printf("token=%d, lexeme=\"%s\"\n", token, lexer.YYText());
  } while (token != T_eof);
}
#else
int main () {
  int token;
  do {
    token = yylex();
    printf("token=%d, lexeme=\"%s\"\n", token, yytext);
  } while (token != T_eof);
}
#endif
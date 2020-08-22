%{
#include <stdio.h>
#include <stdlib.h>

#define T_eof	0

int  linecount=1;
char lastWhitespace=' ';
int  nesting;

int		fixChar		(char * str, int * shift);
int		fixHex		(char * str);
int		charToInt	(char );

enum tokenTypes
{
	T_and = 258,
	T_bool = 259,
	T_char = 260,
	T_decl = 261,
	T_def = 262,
	T_else = 263,
	T_elsif = 264,
	T_end = 265,
	T_exit = 266,
	T_false = 267,
	T_for = 268,
	T_head = 269,
	T_if = 270,
	T_int = 271,
	T_list = 272,
	T_mod = 273,
	T_new = 274,
	T_nil = 275,
	T_nilq = 276,
	T_not = 277,
	T_or = 278,
	T_ref = 279,
	T_return = 280,
	T_skip = 281,
	T_tail = 282,
	T_true = 283,
	T_le = 284,
	T_ge = 285,
	T_ne = 286,
	T_assign = 287,
	T_id = 288,
	T_int_const = 289,
	T_char_const = 290,
	T_string = 291
};

%}

L [A-Za-z]		
D [0-9]			
W [ \t\r]		
HEX [0-9|A-F|a-f] 	
ESCAPE \\(n|t|r|0|\\|\'|\"|x{HEX}{HEX})

%x COMMENT

%%

"and"		{ return T_and; }
"end"		{ return T_end; }
"list"		{ return T_list; }
"ref"		{ return T_ref; }
"bool"		{ return T_bool; }
"exit"		{ return T_exit; }
"mod"		{ return T_mod; }
"return"	{ return T_return; }
"char"		{ return T_char; }
"false"		{ return T_false; }
"new"		{ return T_new; }
"skip"		{ return T_skip; }
"decl"		{ return T_decl; }
"for"		{ return T_for; }
"nil"		{ return T_nil; }
"tail"		{ return T_tail; }
"def"		{ return T_def; }
"head"		{ return T_head; }
"nil?"		{ return T_nilq; }
"true"		{ return T_true; }
"else"		{ return T_else; }
"or"		{ return T_or; }
"int"		{ return T_int; }
"if"		{ return T_if; }
"not"		{ return T_not; }
"elsif"		{ return T_elsif; }


{L}({L}|{D}|_|\?)*	{ yylval.name=strdup(yytext); return T_id;}

{D}+				{ yylval.val=atoi(yytext); return T_int_const; }

\"([^\n\"\'\\]|{ESCAPE})*\" { yylval.name = strdup(yytext); return T_string; }

\'([^\"\'\\]|{ESCAPE})\'	{ yylval.val=fixChar(yytext+1,NULL); return T_char_const; /*first of yytext is ' so it is not passed*/ } 
 
[+|\-|*|/|#|=|<|>]	{ return yytext[0]; }
"<="				{ return T_le;	}
">="				{ return T_ge;}
"<>"				{ return T_ne;}

[\(|\)|\[|\]|,|;|:]	{ return yytext[0]; }
":="				{ return T_assign; }

%[^\n]*\n			{ /* nothing */ linecount++; }

"<*"				{ nesting=1;  BEGIN(COMMENT);}
<COMMENT>"<*"		{ nesting++; }
<COMMENT>"*>"		{ nesting--; if(nesting==0) BEGIN(INITIAL); }
<COMMENT>"\n"		{ linecount++; }
<COMMENT>"*"		{ /* nothing */ }
<COMMENT>[^*\n]		{ /* nothing */ }

{W}					{ lastWhitespace=yytext[0]; }
\n					{ linecount++; lastWhitespace='\n'; }

<<EOF>>				{ return T_eof; }

.					{ yyerror("char not recognised"); } 

%%


int fixChar(char * str, int *shift)
{
	int dummy;
	if(shift==NULL) shift=&dummy;
		
	*shift=1;
	if(str[0]!='\\') return str[0];	//regular character, not escape

	*shift=2;
	//indicator str[1] is the char after the backshlash of escape char
	switch(str[1]){
		case 'n': return '\n';
		case 't': return '\t';
		case 'r': return '\r';
		case '0': return '\0';
		case '\\': return '\\';
		case '\'': return '\'';
		case '\"': return '\'';
		case 'x': {*shift=4;  return fixHex(str+2); }
		default : internal("lexer: escape char, unmatched case");
	}
}

int fixHex(char * str)
{
	int d1,d2,hex;
	d1=charToInt(str[0]);
	d2=charToInt(str[1]);
	hex = d1*16 + d2;
	return hex;
}

int charToInt(char c)
{
	if(c>='0' && c<='9')
		return c-'0';
	else if(c>='a' && c<='f')
		return c-'a'+10;
	else if(c>='A' && c<='F')
		return c-'A'+10;
	else
		error("lexer: %s not a proper char expression",yytext); 
	return -1; //only on error
}
	

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


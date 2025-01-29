%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include "types.h"
	#include "parser.tab.h"
	
	// Buffer per accumulare stringhe multi-carattere
	char *current_string = NULL;

	// Funzione per resettare il buffer della stringa
	void reset_string_buffer() {
		if (current_string) {
			free(current_string);
			current_string = NULL;
		}
	}

	// Funzione per aggiungere frammenti al buffer
	void append_to_string(const char *fragment) {
		if (!current_string) {
			current_string = strdup(fragment);
		} else {
			size_t len = strlen(current_string) + strlen(fragment) + 1;
			current_string = realloc(current_string, len);
			strcat(current_string, fragment);
		}
	}
	

%}

DIGIT [0-9]+
OPERATOR [+-/!<>]
%x STRING COMMENT
%option noinput nounput noyywrap yylineno 

%%
"imagine"                       { return T_IMAGINE; }
"nah"				{ return T_NAH; }
"one_by_one"                    { return T_ONE_BY_ONE; }
"as_long_as"                    { return T_AS_LONG_AS; }
"go"                            { return T_GO; }
"all_set"                       { return T_ALL_SET; }
"throw_up"                      { return T_THROWUP; }
"+"        			{ return T_PLUS; }
"-"        			{ return T_MINUS; }
"*"        			{ return T_MULTIPLY; }
"/"        			{ return T_DIVIDE; }
"->"       			{ return T_FAI; }
"-->"				{ return T_EQUAL; }
"!->"      			{ return T_NEQUAL; }
">="       			{ return T_GEQUAL; }
"<="       			{ return T_LEQUAL; }
"<"        			{ return T_LESS; }
">"        			{ return T_GREATER; }
"send_back"                     { return T_SENDBACK; }
"in"				{ return T_IN; }
"a_new_one"			{ return T_A_NEW_ONE; }
"("				{ return T_LPAREN; }
")" 				{ return T_RPAREN; }
"{"				{ return T_LCURPAR; }
"}"				{ return T_RCURPAR; }
","				{ return T_COMMA; }
"zip"				{ return T_ZIP_TYPE; }
"whole_y"			{ return T_WHOLEY_TYPE; }
"floaty"			{ return T_FLOATY_TYPE; }	
"chain"				{ return T_STRING_TYPE; }
"rando"				{ return T_RANDO; }
"gimme"				{ return T_GIMME; }
"\n"				{  }
" "				{  }
"\t"				{  }
{DIGIT}"."{DIGIT}               { yylval.fnum = atof(yytext); return T_FLOATY; }
{DIGIT}                         { yylval.num = atoi(yytext); return T_WHOLEY; }
@x[0-9a-fA-F]+                  { yylval.num = strtol(yytext + 2, NULL, 16); return T_WHOLEY; }
"\^"                            { BEGIN(STRING); reset_string_buffer(); }
<STRING>[^\\^]+			{ append_to_string(yytext);}
<STRING>"\\gms"                 { append_to_string("\n");}
<STRING>"\\so"                  { append_to_string("\t"); }
<STRING>"\^"                    { 
					yylval.str= strdup(current_string);
					current_string = NULL;
					BEGIN(INITIAL);
					return T_STRING;
				}
"x\$"                           { BEGIN(COMMENT); }
<COMMENT>[^\$]+                  { ; }
<COMMENT>"\$x"                  { BEGIN(INITIAL); }
[a-zA-Z][_a-zA-Z0-9]*           { yylval.id = strdup(yytext); return T_IDENTIFIER; }
[^ ^\n^\t]{1}			{ return yytext[0]; }

%%



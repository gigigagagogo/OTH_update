%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
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
%option noyywrap yylineno 

%%
"imagine"                       { return T_IMAGINE; }
"nah"				{ return T_NAH; }
"one_by_one"                    { return T_ONE_BY_ONE; }
"as_long_as"                    { return T_AS_LONG_AS; }
"go"                            { return T_GO; }
"all_set"                       { return T_ALL_SET; }
"throw_up"                      { return T_THROWUP; }
"->"                            { return T_EQUAL; }
"!->"				{ return T_NEQUAL; }
"send_back"                     { return T_SENDBACK; }
{DIGIT}"."{DIGIT}               { yylval.fnum = atof(yytext); return T_FLOATY; }
{DIGIT}                         { yylval.num = atoi(yytext); return T_WHOLEY; }
"Chain"				{ return T_CHAIN; }
@x[0-9a-fA-F]+                  { yylval.num = strtol(yytext + 2, NULL, 16); return T_WHOLEY; }
"\^"                            { BEGIN(STRING); reset_string_buffer(); }
<STRING>[^\\^]+			{ append_to_string(yytext);}
<STRING>"\\gms"                 { append_to_string("\n");}
<STRING>"\\so"                  { append_to_string("\t"); }
<STRING>"\^"                    { 
					yylval.str= current_string;
					current_string = NULL;
					BEGIN(INITIAL);
					return T_STRING;
				}
"x\$"                           { BEGIN(COMMENT); }
<COMMENT>[^$]+                  { ; }
<COMMENT>"\$x"                  { BEGIN(INITIAL); }
[a-zA-Z][_a-zA-Z0-9]*           { yylval.id = strdup(yytext); return T_IDENTIFIER; }
{OPERATOR}			{ return T_OPERATOR; }
"=>"				{ return T_GEQUAL; }
"<="				{ return T_LEQUAL; }
%%


int main() {
    return 0;
}

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include "parser.tab.h"
	

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
"\^"                             { BEGIN(STRING); }
<STRING>"\\gms"                 { yylval.str = strdup(yytext); return T_GMS;}
<STRING>"\\so"                  { yylval.str = strdup(yytext); return T_SO; }
<STRING>"\^"                     { BEGIN(INITIAL); return T_STRING_END; }
"x\$"                            { BEGIN(COMMENT); }
<COMMENT>[^$]+                  { ; }
<COMMENT>"\$x"                   { BEGIN(INITIAL); }
[a-zA-Z][_a-zA-Z0-9]*           { yylval.id = strdup(yytext); return T_IDENTIFIER; }
{OPERATOR}			{ return T_OPERATOR; }
"=>"				{ return T_GEQUAL; }
"<="				{ return T_LEQUAL; }
%%


int main() {
    return 0;
}

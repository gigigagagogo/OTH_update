%{
#include "calc.tab.h"
%}
%option noyywrap nounput noinput yylineno
%%

[a-z]+  { yylval.str = strdup(yytext); return id; }
[0-9]+  { yylval.nr = atoi(yytext); return num; }
"+"     { return add; }
"-" 	{ return sub; }
"*"	{ return mul; }
"/"	{ return division; }
"="	{ return egu; }
"\^"	{ return ele; }
(\ |\n)
. return *yytext;

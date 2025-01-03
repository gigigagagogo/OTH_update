%{
	#include <stdio.h>
	#include <stdlib.h>
	enum {
	 EOI = 0,
	 NUM,
	 STR,
	 COMM
	};
	int num = 0;
	char *str;
	void addstr(char );
%}

DIGIT ([1-9][0-9]*|0)
%s STRING COMMENT
%option noyywrap
%%
{DIGIT}	{ num = atoi(yytext); return NUM;}
"\""	{ BEGIN(STRING); addstr('\0');}
<STRING>"\"" { BEGIN(INITIAL); return STR;}
<STRING>"\"\"" { addstr('"');}
<STRING>"/nl" { addstr('\n');}
<STRING>.    { addstr(*yytext);}
"/*"	{ BEGIN(COMMENT);}
<COMMENT>"*\\" { BEGIN(INITIAL);}
<COMMENT>(.|\n) ;
%%

void addstr (char ch){
	int l = strlen(str);
	str = realloc(str, l + 2);
	str[l] = ch;
	str[l+1] = '\0';
}

int main(){
	str = malloc(1);
	int token;
	do{
	token = yylex();
	  switch(token){
	    case NUM:
	      printf("Num found: %d\n", num);
	      break;
	    case STR:
	      printf("String found: '%s'\n", str);
	      break; 
	  }
       }while(token != EOI);
       exit(EXIT_SUCCESS);
}


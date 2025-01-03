%{
	#include<stdio.h>
	int counter_line = 0;
	int counter_word = 0;
	int counter_char = 0;
	char **files;
%}

%%
\n	{counter_line++;}
[^ \n]+	{counter_word++;}
. 	{counter_char++;}
%%

int yywrap (void) {
  if (yyin)
    fclose(yyin);
  if (*files == NULL) {
    return 1;
  } else {
    yyin = fopen(*files++, "r");

    return 0;
  }
}

//Funzione main
int main(int argc, char **argv){
	files = argv+1;
	yywrap();
	yylex();
	
	printf("Numero di:\nlinee = %d,\nparole = %d,\nchar = %d\n", counter_line, counter_word, counter_char);
	return 0;
}

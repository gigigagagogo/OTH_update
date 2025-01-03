%{
#include <stdio.h>
#include <ctype.h>
int count_odd = 0;
int count_even = 0;
void upper(char *);
void lower(char *);

enum {
	EVEN = 100,
	ODD
};	

%}
DIGIT [1-9]
DIGIT0 [0-9]
END "END"
ODD  ({DIGIT}{DIGIT0}*)?[13579]
EVEN (({DIGIT}{DIGIT0}*)?[02468]|0)

%%

{EVEN} {printf("even number: "); ECHO; return EVEN;}
{ODD} {printf("\nodd number: "); ECHO; return ODD;}
[a-zA-Z]{2}([a-zA-Z]{2})* {lower(yytext);}
[a-zA-Z]{1}([a-zA-Z]{2})* {upper(yytext);}

.*{END} {return 0;} 

%%

void upper(char *input){
	char *s = input;
	while(*s){
		printf("%c", toupper(*s));
		s++;
	}
	printf("\n");
}


void lower(char *input){
	char *s = input;
	while(*s){
		printf("%c", tolower(*s));
		s++;
	}
	printf("\n");
}
int main(){
	while(1){
		int token = yylex();
		switch(token){
			case 0:
				printf("Odd count: %d, Even count: %d\n", count_odd, count_even);
				exit(EXIT_SUCCESS);
			case EVEN:
				printf("cx");
				count_even++;
				break;
			case ODD:
				printf("dc");
				count_odd++;
				break;
			default:
				break;
		}
		printf("Odd number: %d\n", count_odd);
		printf("Even number: %d\n", count_even); 
		return 0;
	}
}

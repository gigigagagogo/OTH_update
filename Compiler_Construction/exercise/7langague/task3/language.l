%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>

	enum TOKEN{
		EOI = 0,
		T_IMAGINE,
		T_WHOLEY,
		T_FLOATY,
		T_ONE_BY_ONE,
		T_AS_LONG_AS,
		T_IDENTIFIER,
		T_STRING,
		T_OPERATOR,
		T_COMMENT,
		T_NEWLINE,
		T_GO,
		T_ALLSET,
		T_EQUAL,
		T_THROWUP,
		T_SENDBACK
	};

	typedef struct {
		int num;
		double fnum;
		char *str;
		char *id;
	} YYSTYPE;

	YYSTYPE yylval;
	
	extern FILE *yyin;
	extern char *yytext;		

	void addstr(const char* );

%}

DIGIT [0-9]+
OPERATOR [+-/!=<>]
%s STRING COMMENT
%option noyywrap 

%%
"imagine"                       { return T_IMAGINE; }
"one_by_one"                    { return T_ONE_BY_ONE; }
"as_long_as"                    { return T_AS_LONG_AS; }
"go"                            { return T_GO; }
"all_set"                       { return T_ALLSET; }
"throw_up"                      { return T_THROWUP; }
"->"                            { return T_EQUAL; }
"send_back"                     { return T_SENDBACK; }
{DIGIT}"."{DIGIT}               { yylval.fnum = atof(yytext); return T_FLOATY; }
{DIGIT}                         { yylval.num = atoi(yytext); return T_WHOLEY; }
@x[0-9a-fA-F]+                  { yylval.num = strtol(yytext + 2, NULL, 16); return T_WHOLEY; }
"\^"                             { BEGIN(STRING); addstr("\0"); }
<STRING>"\\gms"                 { addstr("\\gms"); }
<STRING>"\\so"                  { addstr("\\so"); }
<STRING>"\^"                     { BEGIN(INITIAL); return T_STRING; }
"x\$"                            { BEGIN(COMMENT); }
<COMMENT>[^$]+                  { ; }
<COMMENT>"\$x"                   { BEGIN(INITIAL); }
[a-zA-Z][_a-zA-Z0-9]*           { yylval.id = strdup(yytext); return T_IDENTIFIER; }
{OPERATOR}			{ return T_OPERATOR; }
%%

void addstr(const char* ch) {
    if (yylval.str == NULL) {
        yylval.str = strdup(ch);
    } else {
        int l = strlen(yylval.str);
        yylval.str = realloc(yylval.str, l + strlen(ch) + 1);
        if (!yylval.str) {
            fprintf(stderr, "Errore di allocazione della memoria\n");
            exit(1);
        }
        strcat(yylval.str, ch);
    }
}

void clear_memory() {
    if (yylval.str) {
        free(yylval.str);
        yylval.str = NULL;
    }
    if (yylval.id) {
        free(yylval.id);
        yylval.id = NULL;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Errore apertura file");
        return 1;
    }

    yyin = file; // Assegna il file a Flex
    int token;

    do {
        token = yylex();
        switch(token){
            case T_WHOLEY:
                printf("Token: WHOLEY, Value: %d\n", yylval.num);
                break;
            case T_FLOATY:
                printf("Token: FLOATY, Value: %f\n", yylval.fnum);
                break;
            case T_STRING:
                printf("Token: STRING, Value: %s\n", yylval.str);
                break;
            case T_IDENTIFIER:
                printf("Token: IDENTIFIER, Value: %s\n", yylval.id);
                break;
            case T_IMAGINE:
                printf("Token: IMAGINE (if)\n");
                break;
            case T_ONE_BY_ONE:
                printf("Token: ONE_BY_ONE (for)\n");
                break;
            case T_AS_LONG_AS:
                printf("Token: AS_LONG_AS (while)\n");
                break;
            case T_GO:
                printf("Token: GO (start block)\n");
                break;
            case T_ALLSET:
                printf("Token: ALL_SET (end block)\n");
                break;
            case T_THROWUP:
                printf("Token: THROW_UP (print)\n");
                break;
            case T_SENDBACK:
                printf("Token: SEND_BACK (return)\n");
                break;
            case T_OPERATOR:
                printf("Token: OPERATOR\n");
                break;
            case T_COMMENT:
                printf("Token: COMMENT\n");
                break;
            case T_NEWLINE:
                printf("Token: NEWLINE\n");
                break;
            default:
                printf("Token sconosciuto: %d\n", token);
                break;
        }
        clear_memory();
    } while(token != 0);

    fclose(file);
    return 0;
}

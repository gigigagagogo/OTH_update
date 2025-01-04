%{

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

    int yydebug = 1;
    extern int yylineno;

    void yyerror (const char *msg) { // gestisci e segnala errori di parsing
        fprintf(stderr, "Errore di parsing alla riga: %d\t%s\n", yylineno, msg);
    }

%}

%define parse.error verbose

%union {
    int num;
    double fnum;
    char *str;
    char *id;
}

%token <num> T_WHOLEY
%token <fnum> T_FLOATY
%token <id> T_IDENTIFIER
%token T_GO T_ALL_SET T_IMAGINE T_NAH T_ONE_BY_ONE T_AS_LONG_AS T_EQUAL T_NEQUAL T_GEQUAL T_LEQUAL T_OPERATOR T_CHAIN

%%

START:
    /* empty */
    |START statements
    ;

block:
    T_GO control_block T_ALL_SET
    ;

control_block:
      if_block
    | while_block
    | for_block
    ;

if_block:
    T_IMAGINE '(' condition ')' '{' statements '}'
    | T_IMAGINE '(' condition ')' '{' statements '}' T_NAH '{' statements '}'
    ;

while_block:
    T_AS_LONG_AS '(' condition ')' '{' statements '}'
    ;

for_block:
    T_ONE_BY_ONE '(' assignment ';' condition ';' assignment ')' '{' statements '}'
    ;

statements:
    statements statement
    | statement
    ;

statement:
    assignment ';'
    | block
    ;

assignment:
    T_IDENTIFIER T_EQUAL expression {
        $$ = $3;
    }
    ;

condition:
    expression
    ;

expression:
      T_WHOLEY
    | T_FLOATY
    | T_IDENTIFIER { $$ = get_symbol($1); }
    | T_IDENTIFIER T_NEQUAL expression { $$ = $1 != $3; }
    | T_IDENTIFIER T_GEQUAL expression { $$ = $1 >= $3; }
    | T_IDENTIFIER T_LEQUAL expression { $$ = $1 <= $3; }
    | T_IDENTIFIER T_OPERATOR expression {
        if (*$2 == '+') $$ = $1 + $3;
        else if (*$2 == '-') $$ = $1 - $3;
        else if (*$2 == '*') $$ = $1 * $3;
        else if (*$2 == '/') $$ = $1 / $3;
    }
    | '(' expression ')' { $$ = $2; }
    | '$' expression '$' { $$ = $2; }
    ;

%%

int main() {
    return yyparse();
}

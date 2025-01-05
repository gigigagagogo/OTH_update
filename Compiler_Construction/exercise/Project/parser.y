%{

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include"stack.h"

    int yydebug = 1;
    extern int yylineno;

    void yyerror (const char *msg); // gestisci e segnala errori di parsing

    int yylex(void);
    int var_get(char *id);
    int var_set(char *id, int val);
    stack_t *vars;

%}

%define parse.error verbose

%union {
    int num;
    double fnum;
    char *str;
    char *id;
    char op;
}

%token <num> T_WHOLEY
%token <fnum> T_FLOATY
%token <str> T_GMS
%token <str> T_SO
%token <id> T_IDENTIFIER
%token <op> T_OPERATOR
%token T_SENDBACK T_STRING_END T_THROWUP T_GO T_ALL_SET T_IMAGINE T_NAH T_ONE_BY_ONE T_AS_LONG_AS T_EQUAL T_NEQUAL T_GEQUAL T_LEQUAL T_CHAIN
%type <num> assignment condition expression statements 
%start START
%%

START:
    /* empty */
    |START statements { printf("Result: %d\n", $2); }
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
        $$ = $3; var_set($1, $3);
    }
    ;

condition:
    expression
    ;

expression:
      T_WHOLEY { $$ = $1; }
    | T_FLOATY { $$ = (int)$1; }
    | T_IDENTIFIER { $$ = var_get($1); }
    | T_IDENTIFIER T_NEQUAL expression { $$ = $1 != $3; }
    | T_IDENTIFIER T_GEQUAL expression { $$ = $1 >= $3; }
    | T_IDENTIFIER T_LEQUAL expression { $$ = $1 <= $3; }
    | T_IDENTIFIER T_OPERATOR expression {
	switch ($2) { // Usa $2 direttamente come char
            case '+': $$ = $1 + $3; break;
            case '-': $$ = $1 - $3; break;
            case '*': $$ = $1 * $3; break;
            case '/':
                if ($3 == 0) {
                    yyerror("Divisione per zero");
                    YYABORT;
                }
                $$ = $1 / $3; break;
        }    
    }
    | '(' expression ')' { $$ = $2; }
    | '$' expression '$' { $$ = $2; }
    ;

%%

int var_get(char *id) {
    val_t *v = s_lookup(vars, id);
    return v == NULL ? 0 : v->val;
}

int var_set(char *id, int val) {
    val_t *v = s_lookup(vars, id);
    if (v == NULL) {
        s_push(vars, (val_t){strdup(id), val});
    } else {
        v->val = val;
    }
    return val;
}

void yyerror(const char *s) {
    fprintf(stderr, "Errore alla riga %d: %s\n", yylineno, s);
}

int main() {
    vars = s_new();
    printf("Inizio parsing...\n");
    yyparse();
    return 0;
}

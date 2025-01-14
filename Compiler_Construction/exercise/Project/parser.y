%{

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "stack.h"
    #include "types.h"
    #define MAX_CHILD 3

    int yydebug = 1;
    extern int yylineno;

    void yyerror (const char *msg); 
    int yylex(void);
    int var_get(char *id);
    int var_set(char *id, int val);
    stack_t *vars;

enum ast_types{
	_INT = 100, _DOUBLE = 101, _STRING = 102,


	_INT_TYPE = 200, _DOUBLE_TYPE = 201, _STRING_TYPE = 202, _VOID_TYPE = 203, _IDENTIFIER = 204,

	_IF = 300, _FOR = 301, _WHILE = 302, _RETURN = 303, _PRINT = 304
};


typedef struct ast{
	int type;
	struct ast child[MAX_CHILD];
	union {
	  int i;
	  double d;
	  char *s;
        } val;
} ast_t;

ast_t *node0(int type){
 	ast_t *t = calloc(1, sizeof(ast_t)); 
	t -> type = type;
	return t;
} 

ast_t *node1(int type, ast_t *child0){
 	ast_t *t = calloc(1, sizeof(ast_t)); 
	t -> type = type;
	t -> child[0] = child0;  
	return t;
} 

%}

%define parse.error verbose

%union {
    int num;
    double fnum;
    char *str;
    char *id;
    char op;
    value_t val;
}

%left T_OPERATOR
%token  <num>T_WHOLEY
%token  T_FLOATY
%token  T_IDENTIFIER
%token   T_OPERATOR
%token  T_STRING
%type <ast_t> expression
%token <str>T_SENDBACK T_THROWUP T_GO T_ALL_SET T_IMAGINE T_NAH T_ONE_BY_ONE T_AS_LONG_AS T_EQUAL T_NEQUAL T_GEQUAL T_LEQUAL T_IN T_LPAREN T_RPAREN T_LCURPAR T_RCURPAR T_A_NEW_ONE 
T_ZIP_TYPE T_CHECK T_IS T_COLON T_DEFAULT T_COMMA T_WHOLEY_TYPE T_FLOATY_TYPE T_STRING_TYPE
%nonassoc T_EQUAL T_NEQUAL T_GEQUAL T_LEQUAL
%start START
%%

START:
	global_declaration     
    | START global_declaration
    ;

global_declaration:
    function_def
    | statements ';'
    ;


block:
     T_GO control_block T_ALL_SET
    ;

control_block:
	     if_block
    | while_block
    | for_block
    | switch_case
    ;

if_block:
	T_IMAGINE T_LPAREN  condition T_RPAREN T_LCURPAR statements T_RCURPAR
    | T_IMAGINE T_LPAREN condition T_RPAREN T_LCURPAR statements T_RCURPAR T_NAH T_LCURPAR statements T_RCURPAR
    ;

while_block:
	   T_AS_LONG_AS T_LPAREN condition T_RPAREN T_LCURPAR statements T_RCURPAR
    ;

for_block:
	 T_ONE_BY_ONE T_LPAREN T_IDENTIFIER T_IN T_LPAREN expression optional_step T_RPAREN T_RPAREN T_LCURPAR statements T_RCURPAR
	; 

optional_step:
	     ',' expression
	     | %empty
	     ;

statements:
	  statement
	  |statements statement      
    ;

statement:
	 assignment ';'
    | function_call ';'
    | block
    | T_SENDBACK expression ';'	{ $$ = node1(303, $2); }    
    | T_THROWUP expression ';'  { $$ = node1(304, $2);  }
    ;

assignment:
      T_IDENTIFIER T_EQUAL expression ';'
      types T_IDENTIFIER T_EQUAL expression ';'
    | types T_IDENTIFIER T_EQUAL expression ';'
    | types T_IDENTIFIER T_EQUAL expression ';'    
    ;

types:
     T_WHOLEY_TYPE	{ $$ = node0(200); }
     | T_FLOATY_TYPE	{ $$ = node0(201); }
     | T_STRING_TYPE 	{ $$ = node0(202); }
     | T_ZIP_TYPE	{ $$ = node0(203); }
     ;

condition:
	 expression
    ;

expression:
	  T_WHOLEY	{ $$ = node0(100); $$->val.num = $1;  }     
    | T_FLOATY 		{ $$ = node0(101); $$->val.fnum = $1; }				
    | T_STRING		{ $$ = node0(102); $$->val.s = $1; }				
    | T_IDENTIFIER	{ $$ = node0(204); } 
    | T_IDENTIFIER T_NEQUAL expression
    | T_IDENTIFIER T_GEQUAL expression
    | T_IDENTIFIER T_LEQUAL expression 
    | T_IDENTIFIER T_OPERATOR expression

function_def:
	    T_A_NEW_ONE types T_IDENTIFIER T_LPAREN param_list T_RPAREN T_LCURPAR statements T_RCURPAR
	;
function_call:
	     T_IDENTIFIER T_LPAREN arg_list T_RPAREN
	;
param_list:
	  expression T_IDENTIFIER
	  | param_list T_COMMA expression T_IDENTIFIER
	  | %empty
	  ;
arg_list:
	expression 
	| arg_list T_COMMA expression
	| %empty
	;
switch_case:
	 T_CHECK expression T_LCURPAR case_list T_RCURPAR
	 ;

case_list:
	 case_list T_IS expression T_COLON statements
	 | T_DEFAULT T_COLON statements
	 | %empty
	 ;
%%

/*
int var_get(char *id) {
    value_t *v = s_lookup(vars, id);
    return v == NULL ? 0 : v->u.i;
}

int var_set(char *id, value_t val) {
    value_t *v = s_lookup(vars, id);
    if (v == NULL) {
	s_push(vars, (value_t){strdup(id), val});
    } else {
	v -> type = val.type;
	v -> u = val.u;
    }
    return val.u.i;
}
*/
void yyerror(const char *s) {
    fprintf(stderr, "Errore alla riga %d: %s\n", yylineno, s);
}

int main() {
   
    printf("Inizio parsing...\n");
    yyparse();
    return 0;
}

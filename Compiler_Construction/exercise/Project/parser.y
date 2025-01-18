%{

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "stack.h"
    #include "types.h"

    int yydebug = 1;
    extern int yylineno;

    void yyerror (const char *msg); 
    int yylex(void);
    int var_get(char *id);
    int var_set(char *id, int val);
    stack_t *vars;
    ast_type *root = NULL; 
    extern FILE *yyin;

enum ast_types{
	_START = 1,

	_INT = 100, _DOUBLE = 101, _STRING = 102,

	_INT_TYPE = 200, _DOUBLE_TYPE = 201, _STRING_TYPE = 202, _VOID_TYPE = 203, _IDENTIFIER = 204,

	_IF = 300, _FOR = 301, _WHILE = 302, _RETURN = 303, _PRINT = 304,

	_NEQUAL = 400, _GEQUAL = 401, _LEQUAL = 402, _EQUAL = 403, _PLUS = 404, _MINUS = 405, _MULTIPLY = 406, _DIVIDE = 407, _LESS = 408, _GREATER = 409,
	
	_STATEMENTS = 500, _NEWFUNC = 501, _CONTROLBLOCK = 503, _DECLARATION = 504, _ASSIGNMENT = 505, _SWITCH = 506, _CASE = 507, _FUNCALL = 508, _ARGLIST = 509, _PARAMLIST = 510, 
	_OPTSTEP = 511
};



ast_type *node0(int type){
 	ast_type *t = calloc(1, sizeof(ast_type)); 
	t -> type = type;
	return t;
} 

ast_type *node1(int type, ast_type *child0){
 	ast_type *t = node0(type); 
	t -> type = type;
	t -> child[0] = child0;  
	return t;
} 

ast_type *node2(int type, ast_type *child0, ast_type *child1){
	ast_type *t = node0(type);
	t -> type = type;
	t -> child[0] = child0;
	t -> child[1] = child1;
	return t;
}

ast_type *node3(int type, ast_type *child0, ast_type *child1, ast_type *child2){
	ast_type *t = node0(type);                                                        
        t -> type = type;                                                                 
        t -> child[0] = child0;                                                           
        t -> child[1] = child1;
	t -> child[2] = child2;							   
        return t;    
}

ast_type *node4(int type, ast_type *child0, ast_type *child1, ast_type *child2, ast_type *child3){
        ast_type *t = node0(type);
        t -> type = type;
        t -> child[0] = child0;
        t -> child[1] = child1;
        t -> child[2] = child2;
	t -> child[3] = child3; 
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
    ast_type *ast;
}


%token  <num>T_WHOLEY
%token  <fnum>T_FLOATY
%token  <id>T_IDENTIFIER
%token  <str>T_STRING
%token <op> T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LESS T_GREATER T_GEQUAL T_LEQUAL 
%type <ast> expression statements statement types assignment declaration if_block while_block global_declaration function_def block control_block for_block switch_case
%type <ast> optional_step arg_list param_list function_call case_list 
%token <str>T_SENDBACK T_THROWUP T_GO T_ALL_SET T_IMAGINE T_NAH T_ONE_BY_ONE T_AS_LONG_AS T_IN T_LPAREN T_RPAREN T_LCURPAR T_RCURPAR T_A_NEW_ONE 
T_ZIP_TYPE T_CHECK T_IS T_COLON T_DEFAULT T_COMMA T_WHOLEY_TYPE T_FLOATY_TYPE T_STRING_TYPE
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE 
%left T_LESS T_GREATER T_GEQUAL T_LEQUAL
%nonassoc T_EQUAL T_NEQUAL
%start START
%%

START:
	global_declaration { root = node1(_START, $1); print_ast(root, 0); }     
    | START global_declaration { root = node2(_START, root, $2); print_ast(root, 0);}
        
;

global_declaration:
    function_def { $$ = $1; }
    | statement { $$ = $1; }
    ;


block:
     T_GO control_block T_ALL_SET { $$ = node1(_CONTROLBLOCK, $2); }
    ;

control_block:
	     if_block { $$ = $1; }
    | while_block { $$ = $1; }
    | for_block { $$ = $1; } 
    | switch_case { $$ = $1; }
    ;

if_block:
	T_IMAGINE T_LPAREN expression T_RPAREN T_LCURPAR statements T_RCURPAR T_NAH T_LCURPAR statements T_RCURPAR
    	{ $$ = node3(_IF, $3, $6, $10);  }
     ;

while_block:
	   T_AS_LONG_AS T_LPAREN expression T_RPAREN T_LCURPAR statements T_RCURPAR { $$ = node2(_WHILE, $3, $6); }
    ;



for_block:
	T_ONE_BY_ONE T_LPAREN T_IDENTIFIER T_IN T_LPAREN expression optional_step T_RPAREN T_RPAREN T_LCURPAR statements T_RCURPAR
	{ $$ = node4(_FOR, node0(_IDENTIFIER), $6, $7, $11); $$->child[0]->val.s = $3;}
	; 

optional_step:
	     T_COMMA expression { $$ = node1(_OPTSTEP, $2); }
	     | %empty { $$ = NULL; }
	     ;

statements:
	  statement ';' { $$ = $1; }
	  |statements statement ';' { $$ = node2(_STATEMENTS, $1, $2); }    
    ;

statement:
    declaration { $$ = node1(_DECLARATION, $1); } 
    | assignment { $$ = node1(_ASSIGNMENT, $1); }
    | function_call { $$ = $1; } 
    | block	{ $$ = $1; } 
    | T_SENDBACK expression 	{ $$ = node1(_RETURN, $2); }    
    | T_THROWUP expression  { $$ = node1(_PRINT, $2);  }
    ;

declaration:
	   types T_IDENTIFIER T_EQUAL expression  { 
	         $$ = node3(_EQUAL, $1, node0(_IDENTIFIER), $4); $$->child[1]->val.s = $2; }
	;

assignment:
      T_IDENTIFIER T_EQUAL expression { $$ = node2(_EQUAL, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    ;

types: 
      T_WHOLEY_TYPE	{ $$ = node0(_INT_TYPE); }
     | T_FLOATY_TYPE	{ $$ = node0(_DOUBLE_TYPE); }
     | T_STRING_TYPE 	{ $$ = node0(_STRING_TYPE); }
     | T_ZIP_TYPE	{ $$ = node0(_VOID_TYPE); }
     ;

expression:
	  T_WHOLEY	{ $$ = node0(_INT); $$->val.i = $1;  }     
    | T_FLOATY 		{ $$ = node0(_DOUBLE); $$->val.d = $1; }				
    | T_STRING		{ $$ = node0(_STRING); $$->val.s = $1; }				
    | T_IDENTIFIER	{ $$ = node0(_IDENTIFIER); $$->val.s = $1; } 
    | T_IDENTIFIER T_NEQUAL expression { $$ = node2(_NEQUAL, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    | T_IDENTIFIER T_GEQUAL expression { $$ = node2(_GEQUAL, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    | T_IDENTIFIER T_LEQUAL expression { $$ = node2(_LEQUAL, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    | T_IDENTIFIER T_PLUS expression { $$ = node2(_PLUS, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    | T_IDENTIFIER T_MINUS expression { $$ = node2(_MINUS, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    | T_IDENTIFIER T_DIVIDE expression { $$ = node2(_DIVIDE, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    | T_IDENTIFIER T_MULTIPLY expression { $$ = node2(_MULTIPLY, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    | T_IDENTIFIER T_LESS expression { $$ = node2(_LESS, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    | T_IDENTIFIER T_GREATER expression { $$ = node2(_GREATER, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; } 
function_def:
	T_A_NEW_ONE types T_IDENTIFIER T_LPAREN param_list T_RPAREN T_LCURPAR statements T_RCURPAR  { $$ = node4(_NEWFUNC, $2, node0(_IDENTIFIER), $5, $8); $$->child[1]->val.s = $3; } 
	;
function_call:
	     T_IDENTIFIER T_LPAREN arg_list T_RPAREN	{ $$ = node2(_FUNCALL, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
	;
param_list:
	  expression T_IDENTIFIER	{ $$ = node2(_PARAMLIST, $1, node0(_IDENTIFIER)); $$->child[1]->val.s = $2; }
	  | param_list T_COMMA expression T_IDENTIFIER	{ $$ = node3(_PARAMLIST, $1, $3, node0(_IDENTIFIER)); $$->child[2]->val.s = $4; }
	  | %empty	{ $$ = NULL; }
	  ;
arg_list:
	expression	{ $$ = node1(_ARGLIST, $1); }
	| arg_list T_COMMA expression { $$ = node2(_ARGLIST, $1, $3); }
	| %empty	{ $$ = NULL; }
	;
switch_case:	
	 T_CHECK expression T_LCURPAR case_list T_RCURPAR { $$ = node2(_SWITCH, $2, $4); }
	 ;

case_list:
	 case_list T_IS expression T_COLON statements { $$ = node3(_CASE, $1, $3, $5); }
	 | T_DEFAULT T_COLON statements { $$ = node1(_CASE, $3); }
	 | %empty	{ $$ = NULL; }
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

void print_ast(ast_type *node, int depth) {
    if (!node) return;

    // Stampa l'indentazione
    for (int i = 0; i < depth; i++) {
        if (i == depth - 1)
            printf("|-- ");
        else
            printf("|   ");
    }

    // Stampa il tipo e il valore del nodo
    printf("%d", node->type); // Tipo del nodo
    if (node->type == _INT) {
        printf(": %d", node->val.i);
    } else if (node->type == _DOUBLE) {
        printf(": %f", node->val.d);
    } else if (node->type == _STRING || node->type == _IDENTIFIER) {
        printf(": %s", node->val.s);
    }

    printf("\n");

    // Stampa i figli ricorsivamente
    for (int i = 0; i < 3; i++) { // Supponendo massimo 3 figli
        if (node->child[i]) {
            print_ast(node->child[i], depth + 1);
        }
    }
}


/*
int executor (ast_type *t){
	if(!t){
		return 0;
	}
	switch(t->type){
		case 	
	}
}
*/

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Apri il file specificato come argomento
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Assegna il file a yyin per il lexer
    yyin = file;

    printf("Inizio parsing del file: %s\n", argv[1]);

    // Avvia il parser
    yyparse();

    // Chiudi il file
    fclose(file);

    return 0;
}


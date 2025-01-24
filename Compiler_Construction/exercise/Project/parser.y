%{

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "types.h"
    #include "math.h"    
    #include "exec_fun.h"
    int yydebug = 1;
    extern int yylineno;
    void yyerror (const char *msg); 
    int yylex(void);
    int var_get(char *id);
    int var_set(char *id, int val);
    ast_type *root = NULL; 
    extern FILE *yyin;
    

ast_type *node0(int type){
 	ast_type *t = calloc(1, sizeof(ast_type)); 
	if ( t == NULL ){
		printf("Error memory allocation!");
		exit(EXIT_FAILURE);
	}
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

Scope *current_scope = NULL;

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
%type <ast> expression statements statement types assignment declaration if_block while_block global_declaration function_def block control_block for_block 
%type <ast> optional_step arg_list param_list function_call START 
%token <str>T_SENDBACK T_THROWUP T_GO T_ALL_SET T_IMAGINE T_NAH T_ONE_BY_ONE T_AS_LONG_AS T_IN T_LPAREN T_RPAREN T_LCURPAR T_RCURPAR T_A_NEW_ONE 
T_ZIP_TYPE T_COMMA T_WHOLEY_TYPE T_FLOATY_TYPE T_STRING_TYPE T_EQUAL
%right T_FAI T_EQUAL T_NEQUAL T_LESS T_GREATER T_LEQUAL T_GEQUAL T_COMMA  
%left T_MINUS T_PLUS
%left T_MULTIPLY T_DIVIDE
%start START
%%

START:
     global_declaration { root = node1(_START, $1); current_scope = enter_scope(current_scope); }
    | START global_declaration { root = node2(_START, root, $2); }
;

global_declaration:
    function_def { $$ = $1; }
    | statement ';' { $$ = $1; }
    ;

block:
     T_GO control_block T_ALL_SET { $$ = node1(_CONTROLBLOCK, $2); }
    ;

control_block:
	     if_block { $$ = $1; }
    | while_block { $$ = $1; }
    | for_block { $$ = $1; } 
    ;

if_block:
	T_IMAGINE T_LPAREN expression T_RPAREN T_LCURPAR statements T_RCURPAR
	{
		$$ = node2(_IF, $3, $6);
	}
	|T_IMAGINE T_LPAREN expression T_RPAREN T_LCURPAR statements T_RCURPAR T_NAH T_LCURPAR statements T_RCURPAR
    	{ 
		$$ = node3(_IF, $3, $6, $10);
	}
     ;

while_block:
	   T_AS_LONG_AS T_LPAREN expression T_RPAREN T_LCURPAR statements T_RCURPAR 
	   { 
		$$ = node2(_WHILE, $3, $6);
	   }
    ;

for_block:
	T_ONE_BY_ONE T_LPAREN T_IDENTIFIER T_IN T_LPAREN expression optional_step T_RPAREN T_RPAREN T_LCURPAR statements T_RCURPAR
	{ 
		$$ = node4(_FOR, node0(_IDENTIFIER), $6, $7, $11);
		$$->child[0]->val.s = $3;
		current_scope = enter_scope(current_scope); //Scope "for" variable 
	}
	; 

optional_step:
	     T_COMMA expression { $$ = node1(_OPTSTEP, $2); }
	     | %empty { $$ = NULL; }
	     ;
statements:
	statements statement ';' { $$ = node2(_STATEMENTS, $1, $2); }    
	| statement ';' { $$ = $1;}
;

statement:
    declaration { $$ = $1; } 
    | assignment { $$ = $1; }
    | function_call { $$ = $1; } 
    | block	{ $$ = $1; } 
    | T_SENDBACK expression 	{ $$ = node1(_RETURN, $2); }    
    | T_THROWUP T_LPAREN expression T_RPAREN { $$ = node1(_PRINT, $3);  }
    ;

declaration:
	   types T_IDENTIFIER T_FAI expression  {  
		$$ = node3(_DECLARATION, $1, node0(_IDENTIFIER), $4); $$->child[1]->val.s = $2; }
	;

assignment:
      T_IDENTIFIER T_FAI expression { $$ = node2(_ASSIGNMENT, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    ;

types: 
      T_WHOLEY_TYPE	{ $$ = node0(_INT_TYPE); }
     | T_FLOATY_TYPE	{ $$ = node0(_DOUBLE_TYPE); }
     | T_STRING_TYPE 	{ $$ = node0(_STRING_TYPE); }
     | T_ZIP_TYPE	{ $$ = node0(_VOID_TYPE); }
     ;

expression:
      T_WHOLEY		{ $$ = node0(_INT); $$->val.i = $1;  }     
    | T_FLOATY 		{ $$ = node0(_DOUBLE); $$->val.d = $1; }				
    | T_STRING		{ $$ = node0(_STRING); $$->val.s = $1; }				
    | T_IDENTIFIER	{ $$ = node0(_IDENTIFIER); $$->val.s = $1; } 
    | expression T_NEQUAL expression { $$ = node2(_NEQUAL, $1, $3);  }
    | expression T_GEQUAL expression { $$ = node2(_GEQUAL, $1, $3);  }
    | expression T_LEQUAL expression { $$ = node2(_LEQUAL, $1, $3);  }
    | expression T_PLUS expression { $$ = node2(_PLUS, $1, $3); }
    | expression T_MINUS expression { $$ = node2(_MINUS, $1, $3); }
    | expression T_DIVIDE expression { $$ = node2(_DIVIDE, $1, $3); }
    | expression T_MULTIPLY expression { $$ = node2(_MULTIPLY, $1, $3);}
    | expression T_LESS expression { $$ = node2(_LESS, $1, $3); }
    | expression T_GREATER expression { $$ = node2(_GREATER, $1, $3); }
    | expression T_FAI expression { $$ = node2(_FAI, $1, $3); }
    | expression T_EQUAL expression { $$ = node2(_EQUAL, $1, $3); }
    | T_LPAREN expression T_RPAREN  { $$ = node1(_PARENSTMT, $2); }
;

function_def:
	T_A_NEW_ONE types T_IDENTIFIER T_LPAREN param_list T_RPAREN T_LCURPAR statements T_RCURPAR  
	{
		 $$ = node4(_NEWFUNC, $2, node0(_IDENTIFIER), $5, $8); 
		 $$->child[1]->val.s = $3;	
	} 
	;
function_call:
	     T_IDENTIFIER T_LPAREN arg_list T_RPAREN	{ $$ = node2(_FUNCALL, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
	;
param_list:
	  types T_IDENTIFIER	{ $$ = node2(_PARAMLIST, $1, node0(_IDENTIFIER)); $$->child[1]->val.s = $2; }
	  | param_list T_COMMA types T_IDENTIFIER	{ $$ = node3(_PARAMLIST, $1, $3, node0(_IDENTIFIER)); $$->child[2]->val.s = $4; }
	  | %empty { $$ = NULL; }
	;
arg_list:
	expression	{ $$ = node1(_ARGLIST, $1); }
	| arg_list T_COMMA expression { $$ = node2(_ARGLIST, $1, $3); }
	| %empty	{ $$ = NULL; }
	;
%%


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
    for (int i = 0; i < MAX_CHILD; i++) { // Supponendo massimo 3 figli
        if (node->child[i]) {
            print_ast(node->child[i], depth + 1);
        }
    }
}

value_t executor(ast_type *node, Scope *current_scope) {
    value_t result = {0}; // Inizializza un valore predefinito
    if (!node) {
        return result;
    }

    switch (node->type) {
	case _START: {
    		for (int i = 0; i < MAX_CHILD; i++) {
        		if (node->child[i]) {
            			executor(node->child[i], current_scope);
        		}
    		}
    		break;
	}

	case _INT: {
            result.type = 0;
            result.u.i = node->val.i;
            break;
        }
        case _DOUBLE: {
            result.type = 1;
            result.u.d = node->val.d;
            break;
        }
        case _STRING: {
            result.type = 2;
            result.u.s = node->val.s;
            break;
        }

	case _PLUS: 
		value_t left = executor(node->child[0], current_scope), right = executor(node->child[1], current_scope);
		result = handle_plus(left, right, result);

	case _GREATER: { 
	    value_t left = executor(node->child[0], current_scope); 
    	    value_t right = executor(node->child[1], current_scope); 
    	    result = compare_values(left, right, 0, result); 
    	    break;
	}

	case _LESS: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 1, result);
    		break;
	}

	case _GEQUAL: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 2, result);
    		break;
	}

	case _LEQUAL: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 3, result);
    		break;
	}

	case _EQUAL: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 4, result);
    		break;
	}

	case _NEQUAL: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 5, result);
    		break;
	}

	case _PARENSTMT:
		result = executor(node->child[0], current_scope);	
		break;
	case _PRINT: {
		result = executor(node->child[0], current_scope);
		handle_print(result);
		break;
	}
	case _DECLARATION: {
    		handle_declaration(node, current_scope);
		break;
	}
	case _ASSIGNMENT: {
    		handle_assignment(node, current_scope);
		break;
	}
	case _IDENTIFIER: {
    		result = handle_identifier(node, current_scope);
		break;
	}
	case _CONTROLBLOCK:
		executor(node->child[0], current_scope);
		break;
	case _IF: {
 		handle_if(node, current_scope);
    		break;
	}
	case _WHILE: {
		handle_while(node, current_scope);
		break;	
	}	
	default: {
		printf("Error type %d\n", node->type);
		exit(EXIT_FAILURE);
	}
		
     }
    
	return result;
}
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    printf("Inizio parsing del file: %s\n", argv[1]);

    yyparse();
    
    if (root) {
        printf("AST completo:\n");
        print_ast(root, 0);

        printf("\nEsecuzione dell'AST:\n");
        executor(root, current_scope);

        current_scope = exit_scope(current_scope);
     
    }

    // Chiudi il file
    fclose(file);

    return 0;
}


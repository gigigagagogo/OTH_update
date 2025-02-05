%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "types.h"
    #include "math.h"    
    #include "exec_fun.h"

    int yydebug = 1; // Enables debug mode for parsing
    extern int yylineno; // Keeps track of the line number in the source file
    void yyerror (const char *msg); // Error handling function for the parser
    int yylex(void); // Function prototype for the lexer
    int var_get(char *id); // Function prototype to retrieve variable values
    int var_set(char *id, int val); // Function prototype to set variable values
    ast_type *root = NULL; // Root of the abstract syntax tree (AST)
    extern FILE *yyin; // File pointer for input
    node_s *head = NULL; // Pointer to the top of the stack

// Function to create a node with no children
ast_type *node0(int type){
 	ast_type *t = calloc(1, sizeof(ast_type)); 
	if ( t == NULL ){
		printf("Error memory allocation!");
		exit(EXIT_FAILURE);
	}
	t -> type = type;
	return t;
} 

// Function to create a node with one child
ast_type *node1(int type, ast_type *child0){
 	ast_type *t = node0(type); 
	t -> type = type;
	t -> child[0] = child0;  
	return t;
} 

// Function to create a node with two children
ast_type *node2(int type, ast_type *child0, ast_type *child1){
	ast_type *t = node0(type);
	t -> type = type;
	t -> child[0] = child0;
	t -> child[1] = child1;
	return t;
}

// Function to create a node with three children
ast_type *node3(int type, ast_type *child0, ast_type *child1, ast_type *child2){
	ast_type *t = node0(type);                                                        
        t -> type = type;                                                                 
        t -> child[0] = child0;                                                           
        t -> child[1] = child1;
	t -> child[2] = child2;							   
        return t;    
}

// Function to create a node with four children
ast_type *node4(int type, ast_type *child0, ast_type *child1, ast_type *child2, ast_type *child3){
        ast_type *t = node0(type);
        t -> type = type;
        t -> child[0] = child0;
        t -> child[1] = child1;
        t -> child[2] = child2;
	t -> child[3] = child3; 
        return t;
}

// Global scope pointer, used to track the current scope in the program
Scope *global_scope = NULL;

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
%type <ast> expression statements statement types assignment declaration if_block while_block global_declaration function_def block control_blocks control_block for_block
%type <ast> step arg_list param_list function_call START 
%token <str>T_SENDBACK T_THROWUP T_GO T_ALL_SET T_IMAGINE T_NAH T_ONE_BY_ONE T_AS_LONG_AS T_IN T_LPAREN T_RPAREN T_LCURPAR T_RCURPAR T_A_NEW_ONE 
T_ZIP_TYPE T_COMMA T_WHOLEY_TYPE T_FLOATY_TYPE T_STRING_TYPE T_EQUAL T_RANDO T_GIMME T_SIZE_UP T_JOIN_IN

%right T_FAI T_EQUAL T_NEQUAL T_LESS T_GREATER T_GEQUAL T_LEQUAL T_COMMA
%left T_OR
%left T_AND
%left T_MINUS T_PLUS
%left T_MULTIPLY T_DIVIDE
%left T_LPAREN '['

%%

START:
     global_declaration { root = node1(_START, $1); }
    | START global_declaration { root = node2(_START, root, $2); }
;

global_declaration:
    function_def { $$ = $1; }
    | statement ';' { $$ = $1; }
    ;

block:
     T_GO control_blocks T_ALL_SET { $$ = $2; }
    ;

control_blocks:
	control_block { $$ = node1(_CONTROLBLOCK, $1); }
	| control_blocks control_block { $$ = node2(_CONTROLBLOCK, $1, $2); }
	;
control_block:
	     if_block { $$ = $1; }
    | while_block { $$ = $1; }
    | for_block { $$ = $1; } 
    ;

if_block:
	T_IMAGINE T_LPAREN expression T_RPAREN T_LCURPAR statements T_RCURPAR
	{
		$$ = node3(_IF, $3, $6, NULL);
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
	T_ONE_BY_ONE T_LPAREN T_IDENTIFIER T_IN T_LPAREN step T_RPAREN T_RPAREN T_LCURPAR statements T_RCURPAR
	{ 
		$$ = node3(_FOR, node0(_IDENTIFIER), $6, $10);
		$$->child[0]->val.s = $3;
	}
	; 

step:
	expression T_COMMA expression T_COMMA expression { $$ = node3(_OPTSTEP, $1, $3, $5); }
	;
statements:
	statements statement ';' { $$ = node2(_STATEMENTS, $1, $2); }    
	| statement ';' { $$ = $1;}
;

statement:
    declaration { $$ = $1; } 
    | assignment { $$ = $1; }
    | expression { $$ = $1; }
    | block	{ $$ = $1; } 
    | T_SENDBACK expression 	{ $$ = node1(_RETURN, $2); }    
    | T_THROWUP T_LPAREN expression T_RPAREN { $$ = node1(_PRINT, $3);  }
    ;

declaration:
	   types T_IDENTIFIER	{ $$ = node2(_DECLARATION, $1, node0(_IDENTIFIER)); $$->child[1]->val.s = $2; }
	   | types T_IDENTIFIER T_FAI expression  { $$ = node3(_DECLARATION, $1, node0(_IDENTIFIER), $4); $$->child[1]->val.s = $2; }
	;

assignment:
      T_IDENTIFIER T_FAI expression { $$ = node2(_ASSIGNMENT, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
      | T_IDENTIFIER '[' expression ']' T_FAI expression { $$ = node3(_LIST_ASSIGNMENT, node0(_IDENTIFIER), $3, $6); $$->child[0]->val.s = $1; }
      ;

types: 
      T_WHOLEY_TYPE	{ $$ = node0(_INT_TYPE); }
     | T_FLOATY_TYPE	{ $$ = node0(_DOUBLE_TYPE); }
     | T_STRING_TYPE 	{ $$ = node0(_STRING_TYPE); }
     | T_ZIP_TYPE	{ $$ = node0(_VOID_TYPE); }
     | T_WHOLEY_TYPE '[' T_WHOLEY ']' { $$ = node2(_LIST_TYPE, node0(_INT_TYPE), node0(_INT)); $$->child[1]->val.i = $3; }
     | T_FLOATY_TYPE '[' T_WHOLEY ']' { $$ = node2(_LIST_TYPE, node0(_DOUBLE_TYPE), node0(_INT)); $$->child[1]->val.i = $3; }
     | T_STRING_TYPE '[' T_WHOLEY ']' { $$ = node2(_LIST_TYPE, node0(_STRING_TYPE), node0(_INT)); $$->child[1]->val.i = $3; }     
;

expression:
      T_WHOLEY		{ $$ = node0(_INT); $$->val.i = $1;  }     
    | T_FLOATY 		{ $$ = node0(_DOUBLE); $$->val.d = $1; }				
    | T_STRING		{ $$ = node0(_STRING); $$->val.s = $1; }				
    | T_IDENTIFIER	{ $$ = node0(_IDENTIFIER); $$->val.s = $1; } 
    | function_call { $$ = $1; }
    | expression T_NEQUAL expression { $$ = node2(_NEQUAL, $1, $3);  }
    | expression T_GEQUAL expression { $$ = node2(_GEQUAL, $1, $3);  }
    | expression T_LEQUAL expression { $$ = node2(_LEQUAL, $1, $3);  }
    | expression T_PLUS expression { $$ = node2(_PLUS, $1, $3); }
    | expression T_MINUS expression { $$ = node2(_MINUS, $1, $3); }
    | expression T_DIVIDE expression { $$ = node2(_DIVIDE, $1, $3); }
    | expression T_MULTIPLY expression { $$ = node2(_MULTIPLY, $1, $3);}
    | expression T_LESS expression { $$ = node2(_LESS, $1, $3); }
    | expression T_GREATER expression { $$ = node2(_GREATER, $1, $3); }
    | expression T_EQUAL expression { $$ = node2(_EQUAL, $1, $3); }
    | T_LPAREN expression T_RPAREN  { $$ = node1(_PARENSTMT, $2); }
    | T_IDENTIFIER '[' expression ']' { $$ = node2(_INDEX_ACCESS, node0(_IDENTIFIER), $3); $$->child[0]->val.s = $1; }
    | T_SIZE_UP T_LPAREN expression T_RPAREN { $$ = node1(_SIZE_UP, $3); }
    | expression T_AND expression { $$ = node2(_AND, $1, $3); }
    | expression T_OR expression { $$ = node2(_OR, $1, $3); }	    
    | T_GIMME T_LPAREN types T_RPAREN { $$ = node1(_GIMME, $3); }		    
    | T_RANDO T_LPAREN expression T_COMMA expression T_RPAREN { $$ = node2(_RANDO, $3, $5); }
    | T_JOIN_IN T_LPAREN T_IDENTIFIER T_COMMA expression T_RPAREN { $$ = node2(_JOIN_IN, node0(_IDENTIFIER), $5), $$->child[0]->val.s = $3; }
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
	  types T_IDENTIFIER	{ $$ = node3(_PARAMSLIST, NULL, $1, node0(_IDENTIFIER)); $$->child[2]->val.s = $2; }
	  | param_list T_COMMA types T_IDENTIFIER	{ $$ = node3(_PARAMSLIST, $1, $3, node0(_IDENTIFIER)); $$->child[2]->val.s = $4; }
	  | %empty { $$ = NULL; }
	;
arg_list:
	expression	{ $$ = node2(_ARGSLIST, NULL, $1); }
	| arg_list T_COMMA expression { $$ = node2(_ARGSLIST, $1, $3); }
	| %empty	{ $$ = NULL; }
	;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Errore alla riga %d: %s\n", yylineno, s);
}


// Function to print the AST
void print_ast(ast_type *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        if (i == depth - 1)
            printf("|-- ");
        else
            printf("|   ");
    }

    printf("%d", node->type); 
    if (node->type == _INT) {
        printf(": %d", node->val.i);
    } else if (node->type == _DOUBLE) {
        printf(": %f", node->val.d); 
    }else if (node->type == _STRING || node->type == _IDENTIFIER) {
        if (node->val.s) {
            printf(": ");
            
	  for (const char *c = node->val.s; *c != '\0'; c++) {
                if (*c == '\n') {
                    printf("\\gms"); 
                } else if (*c == '\t') {
                    printf("\\so"); 
                } else if (*c == '\\') {
                    printf("\\\\"); 
                } else {
                    putchar(*c); 
                }
            }
        } else {
            printf(": NULL");    
        }
    }

   printf("\n");

    for (int i = 0; i < MAX_CHILD; i++) { 
        if (node->child[i]) {
            print_ast(node->child[i], depth + 1);
        }
    }
}

value_t executor(ast_type *node, Scope *current_scope) {
    value_t result = {0}; 
    if (!node || current_scope->isReturn) {
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
	case _STATEMENTS: {
		if (node->child[0] != NULL) {
        		executor(node->child[0], current_scope);
    		}

    		if (node->child[1] != NULL) {
        		executor(node->child[1], current_scope);
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

	case _PLUS: { 
		value_t left = executor(node->child[0], current_scope), right = executor(node->child[1], current_scope);
		result = handle_plus(left, right, result);
		break;
	}
	case _MINUS: {
		value_t left = executor(node->child[0], current_scope), right = executor(node->child[1], current_scope);
		result = handle_minus(left, right, result);
		break;
	}
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

	case _AND: {
    		result = handle_and(node, current_scope, result);
		break;
	}

	case _OR: {
    		result = handle_or(node, current_scope, result);
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
	case _FOR: {
		handle_for(node, current_scope);
		break;	
	}
	case _NEWFUNC: {		
		handle_new_function(node, current_scope);
		break;
	}
	
	case _PARAMSLIST: {
		ht_set(current_scope->symbolTable, node->child[2]->val.s, s_pop(&head));	
		executor(node->child[0], current_scope);
		break;
	}
	case _RETURN: {
		current_scope->return_val = executor(node->child[0], current_scope);
		current_scope->isReturn = 1;
		break;
	}
	
	case _FUNCALL: {
 		result = handle_function_call(node, current_scope);
		break;
	}

	case _ARGSLIST: {
		executor(node->child[0], current_scope);
		result = executor(node->child[1], current_scope);
		s_push(&head, result);
		break;	
	}
	case _RANDO: {
    		result = handle_rando(node, current_scope, result);
		break;	
	}
	case _GIMME: {
    		result = handle_gimme(node, result);
		break;
		
	}
	case _INDEX_ACCESS: {
		result = handle_index_access(node, current_scope, result);
		break;
	}

	case _LIST_ASSIGNMENT: {
    		handle_list_assignment(node, current_scope);
		break;
	}

	case _SIZE_UP: {
		result = handle_size_up(node, current_scope, result);
    		break;
	}

	case _JOIN_IN: {
    		handle_join_in(node, current_scope);
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
    printf("Start parsing file: %s\n", argv[1]);

    yyparse();
    
    if (root) {
	printf("AST: \n");
	print_ast(root,0);
	printf("\n\n\n");	
	optimize_ast(root);
	printf("Optimized AST: \n");
        print_ast(root, 0);
     
        printf("\nExecution of AST:\n");
        
	global_scope = enter_scope(NULL);
	executor(root, global_scope);

        global_scope = exit_scope(global_scope);
     
    }

    fclose(file);

    return 0;
}


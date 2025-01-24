#include "exec_fun.h"

value_t handle_plus(value_t left, value_t right, value_t result){
   		if (left.type == 0 && right.type == 0){
			result.type = 0;
			result.u.i = left.u.i + right.u.i;
	}else if (left.type == 1 && right.type == 1){
       			result.type = 1;
       			result.u.d = left.u.d + right.u.d;
		}else if (left.type == 2 && right.type == 0){
			result.type = 2;
			int val = right.u.i;
			int i;
			if (right.u.i == 0){
				i = 1;
			}else{
				for(i = 0; 1; i++){
					if(right.u.i == 0){
						break;
					}
					right.u.i /= 10;
				}
			}
			int length = strlen(left.u.s) + i + 1;
			result.u.s = calloc(length, sizeof(char));
			char num[i+1];
			sprintf(num, "%d", val);
			strcat(result.u.s, left.u.s);
			strcat(result.u.s, num);
		}else if (left.type == 0  && right.type == 2){
			result.type = 2;
			int val = left.u.i;
			int i;
			if (left.u.i == 0){
				i = 1;
			}else{
				for(i = 0; 1; i++){
					if(left.u.i == 0){
						break;
					}
					left.u.i /= 10;
				}
			}
			int length = strlen(right.u.s) + i + 1;
			result.u.s = calloc(length, sizeof(char));
			if (!result.u.s){
				printf("Error memory allocation!");
				exit(EXIT_FAILURE);
}
			char num[i+1];
			sprintf(num, "%d", val);		
			strcat(result.u.s, num);
			strcat(result.u.s, right.u.s);
		}else if(left.type == 2 && right.type == 1){	
			result.type = 2;
			double val = right.u.d;
			int int_part = (int)fabs(val);	
			int i = 1;
			while(int_part >= 10){
				int_part /= 10;
				i++;
			}
			int length = strlen(left.u.s) + i + 1 + 4 + 1;
			result.u.s = calloc(length, sizeof(char));			
			if (!result.u.s){
				printf("Error memory allocation!");
				exit(EXIT_FAILURE);
			}
			char num[i+4+1];
			sprintf(num, "%.*f", 4, val);
			strcat(result.u.s, left.u.s);
			strcat(result.u.s, num);
		}else if(left.type == 1 && right.type == 2){	
			result.type = 2;
			double val = left.u.d;
			int int_part = (int)fabs(val);	
			int i = 1;
			while(int_part >= 10){
				int_part /= 10;
				i++;
			}
			int length = strlen(right.u.s) + i + 1 + 4 + 1;
			result.u.s = calloc(length, sizeof(char));			
			if (!result.u.s){
				printf("Error memory allocation!");
				exit(EXIT_FAILURE);
			}
			char num[i+4+1];
			sprintf(num, "%.*f", 4, val);
			strcat(result.u.s, num);	
			strcat(result.u.s, right.u.s);
		}else if(left.type == 2 && right.type == 2){
			result.type = 2;
			int length = strlen(left.u.s) + strlen(right.u.s) + 1;
			result.u.s = calloc(length, sizeof(char));	
			if (!result.u.s){
				printf("Error memory allocation!");
				exit(EXIT_FAILURE);
			}
			strcat(result.u.s, left.u.s);
			strcat(result.u.s, right.u.s);
		}else if ((left.type == 0 && right.type == 1) || (left.type == 1 && right.type == 0)) {
    			printf("Error: Cannot add int and double directly!\n");
    			exit(EXIT_FAILURE);
		}
    return result;
}
value_t handle_minus(value_t left, value_t right, value_t result){
	
	if ((left.type == 0 && right.type == 0) ||
    	(left.type == 1 && right.type == 1)) {
		if(left.type == 0 && right.type == 0){
			result.u.i = left.u.i + right.u.i;
		}else if(left.type == 1 && right.type == 1){
			result.u.d = left.u.d + right.u.d;
		}else if(left.type == 2 || right.type == 2){
			printf("Error: minus operator requires numeric operands (int or double).\n");
			exit(EXIT_FAILURE);
		}
	}else{
		printf("Error: minus operator requires both operands to be of the same type (either int or double).\n");
		exit(EXIT_FAILURE);
	}
	return result;
}
void handle_print(value_t result){	
	if(result.type == 0){
		printf("%d", result.u.i);	
	}else if(result.type == 1){
		printf("%lf", result.u.d);
	}else if(result.type == 2){
		if (result.u.s) {
                	printf("%s", result.u.s);
                 } else {
            		printf("Error: Attempting to print a NULL string\n");
            		exit(EXIT_FAILURE);
        	 }
        } else {
        	printf("Error: Unsupported type for print\n");
        	exit(EXIT_FAILURE);
    	}
}

void handle_declaration(ast_type *node, Scope *current_scope) {
    ast_type *type_node = node->child[0];
    ast_type *id_node = node->child[1];
    ast_type *expr_node = node->child[2];
   
    int var_type = type_node->type;
    value_t expr_value = executor(expr_node, current_scope);

    // Verifica il tipo dell'espressione
    if ((var_type == _INT_TYPE && expr_value.type != 0) ||
        (var_type == _DOUBLE_TYPE && expr_value.type != 1) ||
        (var_type == _STRING_TYPE && expr_value.type != 2)) {
        printf("Type error: mismatched types in declaration\n");
        exit(EXIT_FAILURE);
    }

    // Verifica che la variabile non esista già
    if (lookup(current_scope, id_node->val.s) != NULL) {
        printf("Error: Variable '%s' already defined in this scope\n", id_node->val.s);
        exit(EXIT_FAILURE);
    }

    if (expr_value.type == 2) { // Tipo stringa
        expr_value.u.s = strdup(expr_value.u.s);
        if (!expr_value.u.s) {
            printf("Error: Memory allocation failed for string\n");
            exit(EXIT_FAILURE);
        }
    }

    // Aggiungi la variabile alla symbol table
    ht_set(current_scope->symbolTable, id_node->val.s, expr_value);
}

void handle_assignment(ast_type *node, Scope *current_scope) {
    char *var_name = node->child[0]->val.s;
    value_t new_value = executor(node->child[1], current_scope); 
    value_t *var = lookup(current_scope, var_name);
    if (var == NULL) {
        printf("Error: Variable '%s' not declared\n", var_name);
        exit(EXIT_FAILURE);
    } 

    if (var->type != new_value.type) {
        printf("Type error: Cannot assign value of type %d to variable '%s' of type %d\n",
               new_value.type, var_name, var->type);
        exit(EXIT_FAILURE);
    }

    if (var->type == 2) { 
        free(var->u.s); 
        var->u.s = strdup(new_value.u.s);
    } else {
        *var = new_value; 
    }
}

value_t handle_identifier(ast_type *node, Scope *current_scope) {
    char *var_name = node->val.s;
    value_t *var = lookup(current_scope, var_name);

    if (!var) {
        printf("Error: Variable '%s' not declared\n", var_name);
        exit(EXIT_FAILURE);
    }
    // Verifica che la stringa sia valida
    if (var->type == 2 && !var->u.s) {
        printf("Error: Variable '%s' contains a NULL string\n", var_name);
        exit(EXIT_FAILURE);
    }
    return *var;
}

value_t compare_values(value_t left, value_t right, int operator_type, value_t result) {
    result.type = 0; 

    if ((left.type != 0 && left.type != 1) || (right.type != 0 && right.type != 1)) {
        printf("Error: Both operands must be numbers (int or double)\n");
        exit(EXIT_FAILURE);
    }

    double left_val = (left.type == 0) ? (double)left.u.i : left.u.d;
    double right_val = (right.type == 0) ? (double)right.u.i : right.u.d;

    switch (operator_type) {
        case 0: result.u.i = left_val > right_val; break;  // Maggiore
        case 1: result.u.i = left_val < right_val; break;  // Minore
        case 2: result.u.i = left_val >= right_val; break; // Maggiore o uguale
        case 3: result.u.i = left_val <= right_val; break; // Minore o uguale
        case 4: result.u.i = left_val == right_val; break; // Uguale
        case 5: result.u.i = left_val != right_val; break; // Diverso
        default:
            printf("Error: Invalid comparison operator\n");
            exit(EXIT_FAILURE);
    }

    return result;
}


void handle_if(ast_type *node, Scope *current_scope) {
    value_t condition = executor(node->child[0], current_scope);

    if (condition.type != 0) {
        printf("Error: Condition in 'if' must evaluate to an integer\n");
        exit(EXIT_FAILURE);
    }

    if (condition.u.i) { 
        current_scope = enter_scope(current_scope);
        executor(node->child[1], current_scope);    
        current_scope = exit_scope(current_scope);  
    } else if (node->child[2]) {
        current_scope = enter_scope(current_scope);
        executor(node->child[2], current_scope);  
        current_scope = exit_scope(current_scope); 
    }
}

void handle_while(ast_type *node, Scope *current_scope){
    ast_type *condition_node = node->child[0];
    ast_type *body_node = node->child[1];      

    Scope *loop_scope = enter_scope(current_scope);

    while (1) {
        value_t condition_value = executor(condition_node, loop_scope);

        if (condition_value.type != 0) {
            printf("Error: Condition in 'while' must be an integer\n");
            exit(EXIT_FAILURE);
        }

        if (condition_value.u.i == 0) {
            break;
        }

        executor(body_node, loop_scope);
    }

    exit_scope(loop_scope);
}


#include <stdbool.h>
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
			result.u.i = left.u.i - right.u.i;
		}else if(left.type == 1 && right.type == 1){
			result.u.d = left.u.d - right.u.d;
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
                	printf("%s",result.u.s);
                 } else {
            		printf("Error: Attempting to print a NULL string\n");
            		exit(EXIT_FAILURE);
        	 }
        } else {
        	printf("Error: Unsupported type for print\n");
        	exit(EXIT_FAILURE);
    	}
}

list_t *create_list(int type, int capacity){
	list_t *list = malloc(sizeof(list_t));
    	if (!list) {
        	printf("Error: Memory allocation for list failed\n");
        	exit(EXIT_FAILURE);
    	}

    	list->type = type; // Tipo degli elementi della lista
    	list->size = 0;    // Inizialmente vuota
    	list->capacity = capacity;

    	// Allocare spazio per gli elementi
    	list->elements = malloc(sizeof(value_t) * capacity);
    	if (!list->elements) {
        	printf("Error: Memory allocation for list elements failed\n");
        	free(list);
        	exit(EXIT_FAILURE);
    	}

    	return list;
}

void handle_declaration(ast_type *node, Scope *current_scope) {
    ast_type *type_node = node->child[0]; // Nodo del tipo (può essere _LIST_TYPE)
    ast_type *id_node = node->child[1];  // Nodo dell'identificatore
    ast_type *expr_node = node->child[2]; // Nodo dell'espressione opzionale (se presente)

    
    int var_type = type_node->type;

    // Verifica che la variabile non esista già
    if (lookup(current_scope, id_node->val.s) != NULL) {
        printf("Error: Variable '%s' already defined in this scope\n", id_node->val.s);
        exit(EXIT_FAILURE);
    }

    // Gestione delle liste
    if (var_type == _LIST_TYPE) {
        int elem_type = type_node->child[0]->type; // Tipo degli elementi della lista
	int capacity = type_node->child[1]->val.i; // Capacità specificata nella dichiarazione

        list_t *list = create_list(elem_type, capacity);

        value_t list_value;
        list_value.type = _LIST_TYPE;
        list_value.u.list = list;
        ht_set(current_scope->symbolTable, id_node->val.s, list_value);

    } else {
        value_t expr_value = executor(expr_node, current_scope);

        if ((var_type == _INT_TYPE && expr_value.type != 0) ||
            (var_type == _DOUBLE_TYPE && expr_value.type != 1) ||
            (var_type == _STRING_TYPE && expr_value.type != 2)) {
            printf("Type error: mismatched types in declaration for variable %s\n", id_node->val.s );
            exit(EXIT_FAILURE);
        }

        if (expr_value.type == 2) {
	    expr_value.u.s = strdup(expr_value.u.s);
            if (!expr_value.u.s) {
                printf("Error: Memory allocation failed for string\n");
                exit(EXIT_FAILURE);
            }
        }

        ht_set(current_scope->symbolTable, id_node->val.s, expr_value);
    }
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
    result.type = 0; // Risultato sarà sempre un intero (vero/falso)

    // Se entrambi sono stringhe, gestisci i confronti stringa
    if (left.type == 2 && right.type == 2) { // 2 rappresenta il tipo stringa
        switch (operator_type) {
            case 0: // Maggiore
                result.u.i = strcmp(left.u.s, right.u.s) > 0;
                break;
            case 1: // Minore
                result.u.i = strcmp(left.u.s, right.u.s) < 0;
                break;
            case 2: // Maggiore o uguale
                result.u.i = strcmp(left.u.s, right.u.s) >= 0;
                break;
            case 3: // Minore o uguale
                result.u.i = strcmp(left.u.s, right.u.s) <= 0;
                break;
            case 4: // Uguale
                result.u.i = strcmp(left.u.s, right.u.s) == 0;
                break;
            case 5: // Diverso
                result.u.i = strcmp(left.u.s, right.u.s) != 0;
                break;
            default:
                printf("Error: Invalid comparison operator for strings\n");
                exit(EXIT_FAILURE);
        }
        return result; // Ritorna immediatamente, confronto stringa gestito
    }

    // Se entrambi sono numeri (interi o double)
    if ((left.type == 0 || left.type == 1) && (right.type == 0 || right.type == 1)) {
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
                printf("Error: Invalid comparison operator for numbers\n");
                exit(EXIT_FAILURE);
        }
        return result; // Ritorna immediatamente, confronto numerico gestito
    }

    // Se tipi misti (esempio: numero e stringa), errore
    printf("Error: Unsupported types for comparison (left type: %d, right type: %d)\n", left.type, right.type);
    exit(EXIT_FAILURE);
}


void handle_if(ast_type *node, Scope *current_scope) {
    value_t condition = executor(node->child[0], current_scope);

    if (condition.type != 0) {
        printf("Error: Condition in 'if' must evaluate to an integer\n");
        exit(EXIT_FAILURE);
    }
	
    //print_all_scopes(current_scope); 

    if (condition.u.i) { 
        executor(node->child[1], current_scope);    
    } else {
        executor(node->child[2], current_scope);  
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
void handle_for(ast_type *node, Scope *current_scope) {
    Scope *loop_scope = enter_scope(current_scope);
    char *var_name = node->child[0]->val.s;

    ast_type *step_node = node->child[1];
    int start_value = executor(step_node->child[0], current_scope).u.i; 
    int end_value = executor(step_node->child[1], current_scope).u.i;   
    int step = executor(step_node->child[2], current_scope).u.i;        

    if (step <= 0) {
        printf("Error: Step value in 'for' must be a positive integer.\n");
        exit(EXIT_FAILURE);
    }

    value_t loop_var = { .type = 0, .u.i = start_value };
    ht_set(loop_scope->symbolTable, var_name, loop_var);

    while (loop_var.u.i < end_value) {
        executor(node->child[2], loop_scope); 
        loop_var.u.i += step; 
        ht_set(loop_scope->symbolTable, var_name, loop_var); 
    }
    current_scope = exit_scope(loop_scope);
}


// Controlla se un `return` esiste fuori da blocchi condizionali
bool has_return(ast_type *node) {
    if (!node) return false;

    // Se troviamo un `return` e non è dentro un `if`, `while` o `for`, è valido
    if (node->type == _RETURN) {
        return true;
    }

    // Se è un `if`, `while` o `for`, allora il `return` potrebbe non essere sempre eseguito
    if (node->type == _IF || node->type == _WHILE || node->type == _FOR) {
        return false;
    }

    // Controlla ricorsivamente nei figli
    for (int i = 0; i < MAX_CHILD; i++) {
        if (has_return(node->child[i])) {
            return true;
        }
    }

    return false;
}

void handle_new_function(ast_type *node, Scope *current_scope) {
    char *func_name = node->child[1]->val.s;

    if (lookup_function(current_scope, func_name)) {
        printf("Error: Function '%s' already declared in this scope.\n", func_name);
        exit(EXIT_FAILURE);
    }

    function_t *new_func = malloc(sizeof(function_t));
    if (!new_func) {
        printf("Error: Memory allocation for function '%s' failed.\n", func_name);
        exit(EXIT_FAILURE);
    }

    new_func->return_type = node->child[0]->type; 
    new_func->param_list = node->child[2];       
    new_func->body = node->child[3];            

    if(new_func->return_type != _VOID_TYPE){
	    if(!has_return(new_func->body)){
		    printf("Error: Function '%s' must have a return statement!\n", func_name);
		    exit(EXIT_FAILURE);
	    }
    } 

    value_t func_val;
    func_val.type = 3; // Tipo personalizzato per le funzioni
    func_val.u.ptr = new_func;

    ht_set(current_scope->functionTable, func_name, func_val);
}

value_t handle_function_call(ast_type *node, Scope *current_scope) {
    executor(node->child[1], current_scope); 
    char *func_name = node->child[0]->val.s;
    value_t *fun = lookup_function(current_scope, func_name);          

    if (fun->type != 3) {
        printf("Error: Function %s not found!\n", func_name);
    	exit(EXIT_FAILURE);
    } 

    function_t *f = (function_t *) fun->u.ptr;                                     
    Scope *func_scope = enter_scope(current_scope); 
     
    executor(f->param_list, func_scope);      
    executor(f->body, func_scope); 
    value_t result = func_scope->return_val;
    exit_scope(func_scope);
    return result;
}


int map_type(int declared_type) {
    switch (declared_type) {
        case _INT_TYPE:    // Tipo `whole_y`
            return 0;      // Tipo per `value_t` corrispondente
        case _DOUBLE_TYPE: // Tipo `floaty`
            return 1;      // Tipo per `value_t` corrispondente
        case _STRING_TYPE: // Tipo `string`
            return 2;      // Tipo per `value_t` corrispondente
        default:
            return -1;     // Tipo non supportato
    }
}

value_t handle_index_access(ast_type *node, Scope *current_scope, value_t result) {

    // Nome della variabile
    char *var_name = node->child[0]->val.s;
    // Cerca la variabile nel simbolo corrente
    value_t *var_value = lookup(current_scope, var_name);

    // Controllo se la variabile esiste
    if (!var_value) {
        printf("Error: Variable '%s' not declared\n", var_name);
        exit(EXIT_FAILURE);
    }

    // Ottieni l'indice
    int index = executor(node->child[1], current_scope).u.i;

    // Gestione per liste
    if (var_value->type == _LIST_TYPE) {
        if (index < 0 || index >= var_value->u.list->size) {
            printf("Error: Index out of bounds for list '%s'\n", var_name);
            exit(EXIT_FAILURE);
        }
        result = var_value->u.list->elements[index]; // Accedi all'elemento della lista

    // Gestione per stringhe
    } else if (var_value->type == 2) { // Tipo 2 rappresenta le stringhe
        if (index < 0 || index >= strlen(var_value->u.s)) {
            printf("Error: Index out of bounds for string '%s'\n", var_name);
            exit(EXIT_FAILURE);
        }
        result.type = 2; // Tipo stringa
        result.u.s = malloc(2); // Un carattere + terminatore
        if (!result.u.s) {
            printf("Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        result.u.s[0] = var_value->u.s[index];
        result.u.s[1] = '\0'; // Terminatore

    } else {
        printf("Error: Variable '%s' is neither a list nor a string\n", var_name);
        exit(EXIT_FAILURE);
    }

    return result;
}


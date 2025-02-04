#include <stdbool.h>
#include <time.h>
#include "exec_fun.h"

// Handles addition for integers, doubles, and string concatenation
value_t handle_plus(value_t left, value_t right, value_t result){
   		if (left.type == 0 && right.type == 0){ // Integer addition
			result.type = 0;
			result.u.i = left.u.i + right.u.i;
		}else if (left.type == 1 && right.type == 1){ // Double addition
       			result.type = 1;
       			result.u.d = left.u.d + right.u.d;
		}else if (left.type == 2 && right.type == 0){ // String + Integer
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
		}else if (left.type == 0  && right.type == 2){ // Integer + String
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
		}else if(left.type == 2 && right.type == 1){ // String + Double
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
		}else if(left.type == 1 && right.type == 2){ // Double + String
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
		}else if(left.type == 2 && right.type == 2){ // String + String
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
// Handles subtraction for integers and doubles
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

// Handles printing values of different types
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

// Function to create a new list
list_t *create_list(int type, int capacity){
	// Allocate memory for list structure
	list_t *list = malloc(sizeof(list_t));
    	if (!list) {
        	printf("Error: Memory allocation for list failed\n");
        	exit(EXIT_FAILURE);
    	}

    	list->type = type; // Set the ype of the elements stored in the list
    	list->size = 0;    
    	list->capacity = capacity;

	// Allocate memory for storing the elements of the list
    	list->elements = malloc(sizeof(value_t) * capacity);
    	if (!list->elements) {
        	printf("Error: Memory allocation for list elements failed\n");
        	free(list);
        	exit(EXIT_FAILURE);
    	}

    	return list; // Return the newly created list
}

// Handles variable declaration in the AST
void handle_declaration(ast_type *node, Scope *current_scope) {
    ast_type *type_node = node->child[0]; // Nodo del tipo (può essere _LIST_TYPE)
    ast_type *id_node = node->child[1];  // Nodo dell'identificatore
    ast_type *expr_node = node->child[2]; // Nodo dell'espressione opzionale (se presente)

    
    int var_type = type_node->type;

    // Check if the variable is already defined in the current scope
    if (lookup(current_scope, id_node->val.s) != NULL) {
        printf("Error: Variable '%s' already defined in this scope\n", id_node->val.s);
        exit(EXIT_FAILURE);
    }

    // Handle list type variables
    if (var_type == _LIST_TYPE) {
        int elem_type = type_node->child[0]->type; 
	int capacity = type_node->child[1]->val.i;

	// Create a new list with the specified type and capacity
        list_t *list = create_list(elem_type, capacity);

        value_t list_value;
        list_value.type = _LIST_TYPE;
        list_value.u.list = list;
       
	// Store the list in the symbol table
       	ht_set(current_scope->symbolTable, id_node->val.s, list_value);

    } else { // Handle standard variables (int, double, string)
        value_t expr_value = executor(expr_node, current_scope);

	// Ensure that the declared type matches the assigned value type
        if ((var_type == _INT_TYPE && expr_value.type != 0) ||
            (var_type == _DOUBLE_TYPE && expr_value.type != 1) ||
            (var_type == _STRING_TYPE && expr_value.type != 2)) {
            printf("Type error: mismatched types in declaration for variable %s\n", id_node->val.s );
            exit(EXIT_FAILURE);
        }

	// If the value is a string, duplicate it to avoid modifying original memory
        if (expr_value.type == 2) {
	    expr_value.u.s = strdup(expr_value.u.s);
            if (!expr_value.u.s) {
                printf("Error: Memory allocation failed for string\n");
                exit(EXIT_FAILURE);
            }
        }
	
	// Store the variable in the symbol table
        ht_set(current_scope->symbolTable, id_node->val.s, expr_value);
    }
}

// Function to handle variable assignment in the AST execution
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
// Function to retrieve the value of a variable given its identifier
value_t handle_identifier(ast_type *node, Scope *current_scope) {
    char *var_name = node->val.s;
    value_t *var = lookup(current_scope, var_name);

    if (!var) {
        printf("Error: Variable '%s' not declared\n", var_name);
        exit(EXIT_FAILURE);
    }
    
    if (var->type == 2 && !var->u.s) {
        printf("Error: Variable '%s' contains a NULL string\n", var_name);
        exit(EXIT_FAILURE);
    }
    return *var;
}

value_t compare_values(value_t left, value_t right, int operator_type, value_t result) {
    result.type = 0;

    // If both are strings 
    if (left.type == 2 && right.type == 2) { 
        switch (operator_type) {
	    case 0: // >
                result.u.i = strcmp(left.u.s, right.u.s) > 0;
                break;
            case 1: // <
                result.u.i = strcmp(left.u.s, right.u.s) < 0;
                break;
            case 2: // >=
                result.u.i = strcmp(left.u.s, right.u.s) >= 0;
                break;
            case 3: // <=
                result.u.i = strcmp(left.u.s, right.u.s) <= 0;
                break;
            case 4: // == 
                result.u.i = strcmp(left.u.s, right.u.s) == 0;
                break;
            case 5: // !=
                result.u.i = strcmp(left.u.s, right.u.s) != 0;
                break;
            default:
                printf("Error: Invalid comparison operator for strings\n");
                exit(EXIT_FAILURE);
        }
        return result; 
    }

    // If both are numbers (Integer or Double)
    if ((left.type == 0 || left.type == 1) && (right.type == 0 || right.type == 1)) {
        double left_val = (left.type == 0) ? (double)left.u.i : left.u.d;
        double right_val = (right.type == 0) ? (double)right.u.i : right.u.d;

        switch (operator_type) {
            case 0: result.u.i = left_val > right_val; break;  // > 
            case 1: result.u.i = left_val < right_val; break;  // <
            case 2: result.u.i = left_val >= right_val; break; // >=
            case 3: result.u.i = left_val <= right_val; break; // <=  
            case 4: result.u.i = left_val == right_val; break; // ==
            case 5: result.u.i = left_val != right_val; break; // !=
            default:
                printf("Error: Invalid comparison operator for numbers\n");
                exit(EXIT_FAILURE);
        }
        return result; 
    }

    printf("Error: Unsupported types for comparison (left type: %d, right type: %d)\n", left.type, right.type);
    exit(EXIT_FAILURE);
}

// Handle if
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

// Handle while 
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

// Handle for
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

// Function to check if a `return` statement exists outside conditional or loop blocks
bool has_return(ast_type *node) {
    if (!node) return false;

    // If the current node is a return statement and not inside a conditional/loop, return true
    if (node->type == _RETURN) {
        return true;
    }

    if (node->type == _IF || node->type == _WHILE || node->type == _FOR) {
        return false;
    }

    // Recursively check all child nodes for a `return` statement
    for (int i = 0; i < MAX_CHILD; i++) {
        if (has_return(node->child[i])) {
            return true;
        }
    }

    return false;
}

// Handles the creation of a new function and adds it to the function symbol table
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

    // Assign function properties: return type, parameter list, and function body
    new_func->return_type = node->child[0]->type; 
    new_func->param_list = node->child[2];       
    new_func->body = node->child[3];            

    // If the function is not void, ensure it contains a return statement
    if(new_func->return_type != _VOID_TYPE){
	    if(!has_return(new_func->body)){
		    printf("Error: Function '%s' must have a return statement!\n", func_name);
		    exit(EXIT_FAILURE);
	    }
    } 

    // Create a value_t object to store the function in the function table
    value_t func_val;
    func_val.type = 3; 
    func_val.u.ptr = new_func;

    // Insert the function into the current scope's function table
    ht_set(current_scope->functionTable, func_name, func_val);
}

// Handles the execution of a function call
value_t handle_function_call(ast_type *node, Scope *current_scope) {
    executor(node->child[1], current_scope); 
    char *func_name = node->child[0]->val.s;
    value_t *fun = lookup_function(current_scope, func_name);          

    // Check if the function exists
    if (fun->type != 3) {
        printf("Error: Function %s not found!\n", func_name);
    	exit(EXIT_FAILURE);
    } 

    // Retrieve the function details from the function table
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
        case _INT_TYPE:    // Type `whole_y`
            return 0;      
        case _DOUBLE_TYPE: // Type `floaty`
            return 1;      
        case _STRING_TYPE: // Type `string`
            return 2;     
        default:
            return -1;     // Non supported type 
    }
}
// Function to handle index list access
value_t handle_index_access(ast_type *node, Scope *current_scope, value_t result) {

    char *var_name = node->child[0]->val.s;
    value_t *var_value = lookup(current_scope, var_name);

    // Check if variable exists 
    if (!var_value) {
        printf("Error: Variable '%s' not declared\n", var_name);
        exit(EXIT_FAILURE);
    }

    // Get index
    int index = executor(node->child[1], current_scope).u.i;

    if (var_value->type == _LIST_TYPE) {
        if (index < 0 || index >= var_value->u.list->size) {
            printf("Error: Index out of bounds for list '%s'\n", var_name);
            exit(EXIT_FAILURE);
        }
        result = var_value->u.list->elements[index]; 

    } else if (var_value->type == 2) { 
        if (index < 0 || index >= strlen(var_value->u.s)) {
            printf("Error: Index out of bounds for string '%s'\n", var_name);
            exit(EXIT_FAILURE);
        }
        result.type = 2; 
        result.u.s = malloc(2); 
        if (!result.u.s) {
            printf("Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        result.u.s[0] = var_value->u.s[index];
        result.u.s[1] = '\0'; 

    } else {
        printf("Error: Variable '%s' is neither a list nor a string\n", var_name);
        exit(EXIT_FAILURE);
    }

    return result;
}

// Handles logical AND operation
value_t handle_and(ast_type *node, Scope *current_scope, value_t result) {
    result.type = 0; // Logical AND returns an integer (0 or 1)

    value_t left = executor(node->child[0], current_scope);
    if (left.type != 0) {
        printf("Error: Logical AND requires integer operands\n");
        exit(EXIT_FAILURE);
    }

    if (!left.u.i) { // Short-circuit evaluation: if left operand is false, return false
        result.u.i = 0;
        return result;
    }

    value_t right = executor(node->child[1], current_scope);
    if (right.type != 0) {
        printf("Error: Logical AND requires integer operands\n");
        exit(EXIT_FAILURE);
    }

    result.u.i = right.u.i; // Return the value of the right operand
    return result;
}

// Handles logical OR operation
value_t handle_or(ast_type *node, Scope *current_scope, value_t result) {
    result.type = 0; // Logical OR returns an integer (0 or 1)

    value_t left = executor(node->child[0], current_scope);
    if (left.type != 0) {
        printf("Error: Logical OR requires integer operands\n");
        exit(EXIT_FAILURE);
    }

    if (left.u.i) { // Short-circuit evaluation: if left operand is true, return true
        result.u.i = 1;
        return result;
    }

    value_t right = executor(node->child[1], current_scope);
    if (right.type != 0) {
        printf("Error: Logical OR requires integer operands\n");
        exit(EXIT_FAILURE);
    }

    result.u.i = right.u.i; // Return the value of the right operand
    return result;
}

// Generates a random number between min and max
value_t handle_rando(ast_type *node, Scope *current_scope, value_t result) {
    result.type = 0; // Random function returns an integer

    int min = executor(node->child[0], current_scope).u.i;
    int max = executor(node->child[1], current_scope).u.i;

    if (min > max) {
        printf("Error: Invalid range for random()\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    result.u.i = (rand() % (max - min + 1)) + min;

    return result;
}

// Handles user input based on type
value_t handle_gimme(ast_type *node, value_t result) {
    int input_type = node->child[0]->type; // Specified type

    if (input_type == _INT_TYPE) {
        int value;
        printf("Gimme a number: ");
        scanf("%d", &value);
        result.type = 0;
        result.u.i = value;

    } else if (input_type == _DOUBLE_TYPE) {
        double value;
        printf("Gimme a decimal: ");
        scanf("%lf", &value);
        result.type = 1;
        result.u.d = value;

    } else if (input_type == _STRING_TYPE) {
        char buffer[1024]; // Larger buffer to support longer input lines

        if (fgets(buffer, sizeof(buffer), stdin)) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0'; // Remove newline character
            }
            result.type = 2;
            result.u.s = strdup(buffer);
            if (!result.u.s) {
                printf("Error: Memory allocation failed for input string\n");
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Error: Failed to read string input\n");
            exit(EXIT_FAILURE);
        }

    } else {
        printf("Error: Unsupported type for gimme\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

// Function to manage list assignment 
void handle_list_assignment(ast_type *node, Scope *current_scope) {
    char *list_name = node->child[0]->val.s;
    value_t *list_value = lookup(current_scope, list_name);

    if (!list_value || list_value->type != _LIST_TYPE) {
        printf("Error: '%s' is not a list\n", list_name);
        exit(EXIT_FAILURE);
    }
    // Get index
    int index = executor(node->child[1], current_scope).u.i;

    if (index < 0 || index >= list_value->u.list->capacity) {
        printf("Error: Index %d out of bounds for list '%s'\n", index, list_name);
        exit(EXIT_FAILURE);
    }

    value_t new_value = executor(node->child[2], current_scope);
    if (new_value.type != map_type(list_value->u.list->type)) {
        printf("Error: Type mismatch in assignment to list '%s'\n", list_name);
        exit(EXIT_FAILURE);
    }

    if (new_value.type == 2) { // Handle string type
        new_value.u.s = strdup(new_value.u.s);
        if (!new_value.u.s) {
            printf("Error: Memory allocation failed for string\n");
            exit(EXIT_FAILURE);
        }
    }

    // Assign the value to the list at the specified index
    list_value->u.list->elements[index] = new_value;

    // Update the logical size of the list if necessary
    if (index >= list_value->u.list->size) {
        list_value->u.list->size = index + 1;
    }
}

// Function to manage append value in list
void handle_join_in(ast_type *node, Scope *current_scope) {
    char *list_name = node->child[0]->val.s;
    value_t *list_value = lookup(current_scope, list_name);

    if (!list_value || list_value->type != _LIST_TYPE) {
        printf("Error: '%s' is not a list\n", list_name);
        exit(EXIT_FAILURE);
    }

    if (list_value->u.list->size >= list_value->u.list->capacity) {
        printf("Error: List '%s' is full\n", list_name);
        exit(EXIT_FAILURE);
    }

    value_t new_value = executor(node->child[1], current_scope);

    if (new_value.type != map_type(list_value->u.list->type)) {
        printf("Error: Type mismatch in append to list '%s'\n", list_name);
        exit(EXIT_FAILURE);
    }

    if (new_value.type == 2) { // Handle string type
        new_value.u.s = strdup(new_value.u.s);
        if (!new_value.u.s) {
            printf("Error: Memory allocation failed for string append\n");
            exit(EXIT_FAILURE);
        }
    }

    // Append the new value to the list
    list_value->u.list->elements[list_value->u.list->size] = new_value;
    list_value->u.list->size++; // Increase the logical size of the list
}

// Handles retrieving the size of a list or string
value_t handle_size_up(ast_type *node, Scope *current_scope, value_t result) {
    result.type = 0; // Return type is always an integer

    if (node->child[0] == NULL) {
        printf("Error: 'size_up' called on a NULL node\n");
        exit(EXIT_FAILURE);
    }

    if (node->child[0]->type != _IDENTIFIER && node->child[0]->type != _INDEX_ACCESS) {
        printf("Error: 'size_up' can only be used with identifiers or index access\n");
        exit(EXIT_FAILURE);
    }

    if (node->child[0]->type == _IDENTIFIER) {
        char *var_name = node->child[0]->val.s;
        value_t *var_value = lookup(current_scope, var_name);

        if (!var_value) {
            printf("Error: Variable '%s' not found\n", var_name);
            exit(EXIT_FAILURE);
        }

        if (var_value->type == _LIST_TYPE) {
            result.u.i = var_value->u.list->size;
        } else if (var_value->type == 2) { // String type
            result.u.i = strlen(var_value->u.s);
        } else {
            printf("Error: 'size_up' not applicable to type of '%s'\n", var_name);
            exit(EXIT_FAILURE);
        }

    } else if (node->child[0]->type == _INDEX_ACCESS) {
        char *list_name = node->child[0]->child[0]->val.s;
        value_t *list_value = lookup(current_scope, list_name);

        if (!list_value || list_value->type != _LIST_TYPE) {
            printf("Error: '%s' is not a list\n", list_name);
            exit(EXIT_FAILURE);
        }

        int index = executor(node->child[0]->child[1], current_scope).u.i;
        if (index < 0 || index >= list_value->u.list->size) {
            printf("Error: Index out of bounds for list '%s'\n", list_name);
            exit(EXIT_FAILURE);
        }

        value_t element = list_value->u.list->elements[index];
        if (element.type != 2) {
            printf("Error: Element at index %d in list '%s' is not a string\n", index, list_name);
            exit(EXIT_FAILURE);
        }

        result.u.i = strlen(element.u.s);
    }

    return result;
}


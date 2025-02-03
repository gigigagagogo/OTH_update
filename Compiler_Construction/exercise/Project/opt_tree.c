#include "types.h"
#include <stdbool.h>

int evaluate_constant_expression(ast_type *node) {
    if (!node) return 0;

    switch (node->type) {
        case _INT:
            return node->val.i;
        case _GREATER:
            return evaluate_constant_expression(node->child[0]) > evaluate_constant_expression(node->child[1]);
        case _LESS:
            return evaluate_constant_expression(node->child[0]) < evaluate_constant_expression(node->child[1]);
        case _GEQUAL:
            return evaluate_constant_expression(node->child[0]) >= evaluate_constant_expression(node->child[1]);
        case _LEQUAL:
            return evaluate_constant_expression(node->child[0]) <= evaluate_constant_expression(node->child[1]);
        case _EQUAL:
            return evaluate_constant_expression(node->child[0]) == evaluate_constant_expression(node->child[1]);
        case _NEQUAL:
            return evaluate_constant_expression(node->child[0]) != evaluate_constant_expression(node->child[1]);
        default:
            return 0; // Se l'espressione non è costante, ritorniamo 0 per sicurezza
    }
}


void optimize_ast(ast_type *node) {
    if (!node) return ;

    for(int i = 0; i < 4; i++){
	    optimize_ast(node->child[i]);
    }

    switch (node->type) {
	    case _PLUS:
        case _MINUS:
        case _MULTIPLY:
        case _DIVIDE:
            if (node->child[0] && node->child[1]) {
                // Caso: entrambi interi
                if (node->child[0]->type == _INT && node->child[1]->type == _INT) {
                    int left = node->child[0]->val.i;
                    int right = node->child[1]->val.i;
                    int result = 0;

                    if (node->type == _PLUS) result = left + right;
                    else if (node->type == _MINUS) result = left - right;
                    else if (node->type == _MULTIPLY) result = left * right;
                    else if (node->type == _DIVIDE) {
                        if (right != 0) result = left / right;
                        else { printf("[ERROR] Division by zero detected!\n"); return; }
                    }
                    
                    node->type = _INT;
                    node->val.i = result;
                    free(node->child[0]);
                    free(node->child[1]);
                    node->child[0] = NULL;
                    node->child[1] = NULL;
                }
                // Caso: entrambi double o misti intero/double
                else if ((node->child[0]->type == _DOUBLE || node->child[0]->type == _INT) &&
                         (node->child[1]->type == _DOUBLE || node->child[1]->type == _INT)) {
                    double left = (node->child[0]->type == _DOUBLE) ? node->child[0]->val.d : (double) node->child[0]->val.i;
                    double right = (node->child[1]->type == _DOUBLE) ? node->child[1]->val.d : (double) node->child[1]->val.i;
                    double result = 0.0;

                    if (node->type == _PLUS) result = left + right;
                    else if (node->type == _MINUS) result = left - right;
                    else if (node->type == _MULTIPLY) result = left * right;
                    else if (node->type == _DIVIDE) {
                        if (right != 0.0) result = left / right;
                        else { printf("[ERROR] Division by zero detected!\n"); return; }
                    }
                    
                    node->type = _DOUBLE;
                    node->val.d = result;
                    free(node->child[0]);
                    free(node->child[1]);
                    node->child[0] = NULL;
                    node->child[1] = NULL;
                }
                // Caso: stringa + intero
                else if (node->child[0]->type == _STRING && node->child[1]->type == _INT) {
                    char buffer[50];
                    snprintf(buffer, sizeof(buffer), "%d", node->child[1]->val.i);
                    size_t len = strlen(node->child[0]->val.s) + strlen(buffer) + 1;
                    char *new_str = malloc(len);
                    strcpy(new_str, node->child[0]->val.s);
                    strcat(new_str, buffer);
                    node->type = _STRING;
                    node->val.s = new_str;
                    free(node->child[0]);
                    free(node->child[1]);
                    node->child[0] = NULL;
                    node->child[1] = NULL;
                }
                // Caso: intero + stringa
                else if (node->child[0]->type == _INT && node->child[1]->type == _STRING) {
                    char buffer[50];
                    snprintf(buffer, sizeof(buffer), "%d", node->child[0]->val.i);
                    size_t len = strlen(buffer) + strlen(node->child[1]->val.s) + 1;
                    char *new_str = malloc(len);
                    strcpy(new_str, buffer);
                    strcat(new_str, node->child[1]->val.s);
                    node->type = _STRING;
                    node->val.s = new_str;
                    free(node->child[0]);
                    free(node->child[1]);
                    node->child[0] = NULL;
                    node->child[1] = NULL;
                }
                // Caso: stringa + stringa
                else if (node->child[0]->type == _STRING && node->child[1]->type == _STRING) {
                    size_t len = strlen(node->child[0]->val.s) + strlen(node->child[1]->val.s) + 1;
                    char *new_str = malloc(len);
                    strcpy(new_str, node->child[0]->val.s);
                    strcat(new_str, node->child[1]->val.s);
                    node->type = _STRING;
                    node->val.s = new_str;
                    free(node->child[0]);
                    free(node->child[1]);
                    node->child[0] = NULL;
                    node->child[1] = NULL;
                }
                printf("[OPTIMIZATION] Computed constant expression.\n");
            }
            break;
	
	case _WHILE:
    if (node->child[0] && node->child[0]->type == _INT) {
        int condition_value = evaluate_constant_expression(node->child[0]);
        if (condition_value == 0) {
            printf("[OPTIMIZATION] Removing dead while loop.\n");
            free(node->child[0]);
            free(node->child[1]);
            node->type = _STATEMENTS;
            node->child[0] = NULL;
            node->child[1] = NULL;
        } else if (condition_value == 1) {
            printf("[OPTIMIZATION] Unrolling infinite while loop.\n");
            *node = *(node->child[1]); 
        }
    }
    break;

	
	case _FOR:
	    if (node->child[1] && node->child[1]->child[0] && node->child[1]->child[1] && node->child[1]->child[2]) {
        	if (node->child[1]->child[0]->type == _INT && 
            	node->child[1]->child[1]->type == _INT && 
            	node->child[1]->child[2]->type == _INT) {
            
            		int start = node->child[1]->child[0]->val.i;
            		int end = node->child[1]->child[1]->val.i;
            		int step = node->child[1]->child[2]->val.i;

            		if (start == end || step == 0) {
                		printf("[OPTIMIZATION] Removing dead for loop.\n");
                		free(node->child[0]);
                		free(node->child[1]);
                		free(node->child[2]);
                		node->type = _STATEMENTS;
                		node->child[0] = NULL;
                		node->child[1] = NULL;
                		node->child[2] = NULL;
            		}
        	}
    	}
    	break;

    }

}


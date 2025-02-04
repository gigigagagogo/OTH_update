#include "types.h"
#include <stdbool.h>


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

	case _AND:
            if (node->child[0] && node->child[1]) {
                if (node->child[0]->type == _INT && node->child[1]->type == _INT) {
                    node->type = _INT;
                    node->val.i = node->child[0]->val.i && node->child[1]->val.i;
                    free(node->child[0]);
                    free(node->child[1]);
                    node->child[0] = NULL;
                    node->child[1] = NULL;
                }
            }
            break;

        case _OR:
            if (node->child[0] && node->child[1]) {
                if (node->child[0]->type == _INT && node->child[1]->type == _INT) {
                    node->type = _INT;
                    node->val.i = node->child[0]->val.i || node->child[1]->val.i;
                    free(node->child[0]);
                    free(node->child[1]);
                    node->child[0] = NULL;
                    node->child[1] = NULL;
                }
            }
            break;

	case _LESS:
    		if (node->child[0] && node->child[1] && node->child[0]->type == _INT && node->child[1]->type == _INT) {
       			node->type = _INT;
       			node->val.i = node->child[0]->val.i < node->child[1]->val.i;
    		}
    		break;
	
	case _GREATER:
    		if (node->child[0] && node->child[1] && node->child[0]->type == _INT && node->child[1]->type == _INT) {
       			node->type = _INT;
       			node->val.i = node->child[0]->val.i > node->child[1]->val.i;
    		}
    		break;
	case _GEQUAL:	
    		if (node->child[0] && node->child[1] && node->child[0]->type == _INT && node->child[1]->type == _INT) {
       			node->type = _INT;
       			node->val.i = node->child[0]->val.i >= node->child[1]->val.i;
    		}
    		break;
	case _LEQUAL:
    		if (node->child[0] && node->child[1] && node->child[0]->type == _INT && node->child[1]->type == _INT) {
       			node->type = _INT;
       			node->val.i = node->child[0]->val.i <= node->child[1]->val.i;
    		}
    		break;
	case _EQUAL:	
    		if (node->child[0] && node->child[1] && node->child[0]->type == _INT && node->child[1]->type == _INT) {
       			node->type = _INT;
       			node->val.i = node->child[0]->val.i == node->child[1]->val.i;
    		}
    		break;
	case _NEQUAL:	
    		if (node->child[0] && node->child[1] && node->child[0]->type == _INT && node->child[1]->type == _INT) {
       			node->type = _INT;
       			node->val.i = node->child[0]->val.i != node->child[1]->val.i;
    		}
    		break;
	case _IF:
            if (node->child[0] && node->child[0]->type == _INT) {
                int condition_value = node->child[0]->val.i;
                ast_type *node_to_keep = NULL;

                if (condition_value) {
                    printf("[OPTIMIZATION] Removing unreachable else branch.\n");
                    node_to_keep = node->child[1];
                    free(node->child[2]);  
                    node->child[2] = NULL;
                } else {
                    if (node->child[2]) {
                        printf("[OPTIMIZATION] Replacing if with else block.\n");
                        node_to_keep = node->child[2];
                    } else {
                        printf("[OPTIMIZATION] Removing dead if statement.\n");
                        free(node->child[1]);
                        free(node->child[0]);
                        node->type = _STATEMENTS;
                        node->child[0] = NULL;
                        node->child[1] = NULL;
                        node->child[2] = NULL;
                        return;
                    }
                    free(node->child[1]);
                    node->child[1] = NULL;
                }

                free(node->child[0]);
                node->child[0] = NULL;

                if (node_to_keep) {
                    *node = *node_to_keep;
                }
            }
            break;
    	case _WHILE:
            if (node->child[0] && node->child[0]->type == _INT) {
                int condition_value = node->child[0]->val.i;
                if (condition_value == 0) {
                    printf("[OPTIMIZATION] Removing dead while loop.\n");
                    free(node->child[0]);
                    free(node->child[1]);
                    node->type = _STATEMENTS;
                    node->child[0] = NULL;
                    node->child[1] = NULL;
                }
            }
            break;
	

	
	}
}


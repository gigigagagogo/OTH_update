#include "types.h"
#include <stdbool.h>


void optimize_ast(ast_type *node) {
	if (!node) return ;
	
	// Recursively optimize all child nodes
	for(int i = 0; i < 4; i++){
		optimize_ast(node->child[i]);
	}

	switch (node->type) {
		// Constant folding: Evaluate arithmetic expressions with constant values
		case _PLUS:
		case _MINUS:
		case _MULTIPLY:
		case _DIVIDE:
			if (node->child[0] && node->child[1]) {
				// Case: both integer
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
				// Handle mixed integer/double calculations
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
				// Case: string + integer
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
				// Case: integer + string
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
				// Case: string + string
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

		// Dead code elimination: Remove redundant for-loops
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
		 // Logical optimization for OR (||) and AND (&&)
		case _OR:
			if (node->child[0] && node->child[1]) {
				ast_type *left = node->child[0];
				ast_type *right = node->child[1];

				if (left->type == _PARENSTMT) left = left->child[0];
				if (right->type == _PARENSTMT) right = right->child[0];

				if (left->type == _INT && right->type == _INT) {
					node->type = _INT;
					node->val.i = (left->val.i || right->val.i);
					free(node->child[0]);
					free(node->child[1]);
					node->child[0] = NULL;
					node->child[1] = NULL;
				} else if (left->type == _INT && left->val.i == 1) {
					node->type = _INT;
					node->val.i = 1;
					free(node->child[1]);
					node->child[1] = NULL;
				} else if (left->type == _INT && left->val.i == 0) {
					*node = *right;
					free(right);
				}
			}
			break;

		case _AND:
			if (node->child[0] && node->child[1]) {
				ast_type *left = node->child[0];
				ast_type *right = node->child[1];

				if (left->type == _PARENSTMT) left = left->child[0];
				if (right->type == _PARENSTMT) right = right->child[0];

				if (left->type == _INT && right->type == _INT) {
					node->type = _INT;
					node->val.i = (left->val.i && right->val.i);
					free(node->child[0]);
					free(node->child[1]);
					node->child[0] = NULL;
					node->child[1] = NULL;
				} else if (left->type == _INT && left->val.i == 0) {
					node->type = _INT;
					node->val.i = 0;
					free(node->child[1]);
					node->child[1] = NULL;
				} else if (left->type == _INT && left->val.i == 1) {
					*node = *right;
					free(right);
				}
			}
			break;

        	// Constant folding for comparison operators
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
	        // Dead code elimination for unreachable if and while conditions
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


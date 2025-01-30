#ifndef EXEC_FUN_H
#define EXEC_FUN_H

#include "types.h"

value_t handle_plus(value_t left, value_t right, value_t result);
value_t handle_minus(value_t left, value_t right, value_t result);
void handle_print(value_t result);
void handle_declaration(ast_type *node, Scope *current_scope);
void handle_assignment(ast_type *node, Scope *current_scope);
value_t handle_identifier(ast_type *node, Scope *current_scope);
void handle_if(ast_type *node, Scope *current_scope);
void handle_while(ast_type *node, Scope *current_scope);
value_t compare_values(value_t left, value_t right, int operator_type, value_t result);
void handle_for(ast_type *node, Scope *current_scope); 
void handle_new_function(ast_type *node, Scope *current_scope);
value_t handle_function_call(ast_type *node, Scope *current_scope);
int map_type(int declared_type);
#endif //EXEC_FUN_H

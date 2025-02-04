#ifndef EXEC_FUN_H
#define EXEC_FUN_H

#include "types.h"

// Arithmetic operations
value_t handle_plus(value_t left, value_t right, value_t result);
value_t handle_minus(value_t left, value_t right, value_t result);

// Printing functions
void handle_print(value_t result);

// Variable handling
void handle_declaration(ast_type *node, Scope *current_scope);
void handle_assignment(ast_type *node, Scope *current_scope);
value_t handle_identifier(ast_type *node, Scope *current_scope);

// Control flow handling
void handle_if(ast_type *node, Scope *current_scope);
void handle_while(ast_type *node, Scope *current_scope);
void handle_for(ast_type *node, Scope *current_scope);

// Comparison operations
value_t compare_values(value_t left, value_t right, int operator_type, value_t result);
value_t handle_and(ast_type *node, Scope *current_scope, value_t result);
value_t handle_or(ast_type *node, Scope *current_scope, value_t result);

// Function handling
void handle_new_function(ast_type *node, Scope *current_scope);
value_t handle_function_call(ast_type *node, Scope *current_scope);

// Miscellaneous operations
int map_type(int declared_type);
value_t handle_index_access(ast_type *node, Scope *current_scope, value_t result);
void handle_list_assignment(ast_type *node, Scope *current_scope);

//Built-in Function
value_t handle_rando(ast_type *node, Scope *current_scope, value_t result);
value_t handle_gimme(ast_type *node, value_t result);
void handle_join_in(ast_type *node, Scope *current_scope);
value_t handle_size_up(ast_type *node, Scope *current_scope, value_t result);


#endif // EXEC_FUN_H


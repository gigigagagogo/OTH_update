#include "types.h"
Scope *enter_scope (Scope *current_scope){
	Scope *new_scope = malloc (sizeof(Scope));
	if (new_scope == NULL){
		printf("Error memory allocation!");
		exit(EXIT_FAILURE);
	}
	new_scope->symbolTable = create_ht(10);
	new_scope->functionTable = create_ht(10);
	new_scope->parent = current_scope;
	return new_scope;
}

Scope *exit_scope (Scope *current_scope){
	if (current_scope == NULL){
		return NULL;
	}
	Scope *parent = current_scope->parent;
	free(current_scope->symbolTable);
	free(current_scope);
	return parent;
}

value_t *lookup (Scope *current_scope, const char *key){
	Scope *scope = current_scope;
	value_t *value;
	while (scope != NULL){
		value = search(scope->symbolTable, key);
		if (value && value->type != -1){
			return value;
		}
		scope = scope->parent;
	}
	return NULL;
}

value_t *lookup_function(Scope *current_scope, const char *func_name) {
    Scope *scope = current_scope;
    while (scope != NULL) {
        value_t *func = search(scope->functionTable, func_name);
        if (func && func->type != -1) { // Funzione trovata
            return func;
        }
        scope = scope->parent; // Passa allo scope padre
    }
    return NULL; // Funzione non trovata
}


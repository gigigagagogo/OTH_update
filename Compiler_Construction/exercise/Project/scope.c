#include "types.h"

// Creates a new scope and links it to the parent scope
Scope *enter_scope(Scope *current_scope) {
    Scope *new_scope = malloc(sizeof(Scope));
    if (new_scope == NULL) {
        printf("Error memory allocation!");
        exit(EXIT_FAILURE);
    }

    new_scope->symbolTable = create_ht(10);  // Create a new hash table for variables
    new_scope->functionTable = create_ht(10); // Create a new hash table for functions
    new_scope->parent = current_scope;       // Link to the parent scope
    memset(&new_scope->return_val, 0, sizeof(value_t)); // Initialize return value
    new_scope->isReturn = 0;                 // Set return flag to false

    return new_scope;
}

// Exits the current scope and returns to the parent scope
Scope *exit_scope(Scope *current_scope) {
    if (current_scope == NULL) {
        return NULL;
    }

    Scope *parent = current_scope->parent; // Get the parent scope
    free(current_scope->symbolTable);      // Free variable symbol table
    free(current_scope);                   // Free the current scope

    return parent; // Return to the parent scope
}

// Looks up a variable in the current scope or any parent scope
value_t *lookup(Scope *current_scope, const char *key) {
    Scope *scope = current_scope;
    value_t *value;

    while (scope != NULL) {
        value = search(scope->symbolTable, key); // Search in the current scope
        if (value && value->type != -1) {
            return value; // Variable found
        }
        scope = scope->parent; // Move to the parent scope
    }

    return NULL; // Variable not found
}

// Looks up a function in the current scope or any parent scope
value_t *lookup_function(Scope *current_scope, const char *func_name) {
    Scope *scope = current_scope;

    while (scope != NULL) {
        value_t *func = search(scope->functionTable, func_name); // Search for function
        if (func && func->type != -1) {
            return func; // Function found
        }
        scope = scope->parent; // Move to the parent scope
    }

    return NULL; // Function not found
}


#ifndef TYPES_H
#define TYPES_H
#define MAX_CHILD 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct list_t list_t;

// Value type used to store different types of data
typedef struct {
    int type; 
    union {
        int i;         // Integer value
        double d;      // Double value
        char *s;       // String value
        void *ptr;     // Generic pointer
        list_t *list;  // Pointer to a list structure
    } u;             
    int size; // Used for lists and arrays
} value_t;

// Node structure for a stack implementation
typedef struct stackNode {
    value_t val;
    struct stackNode *next;
} node_s;

// Structure for handling lists in the language
struct list_t {
    int type;          // Data type of elements in the list
    value_t *elements; // Pointer to array of elements
    int size;          // Current size of the list
    int capacity;      // Maximum allocated capacity
};

// Abstract Syntax Tree (AST) node structure
typedef struct ast {
    int type;                        // Type of AST node
    struct ast *child[MAX_CHILD];     // Array of child nodes
    union {
        int i;        // Integer value
        double d;     // Double value
        char *s;      // String value
    } val;
} ast_type;

// Hash table node for symbol tables
typedef struct node {
    char *key;          // Identifier name
    value_t value;      // Value associated with the identifier
    struct node *next;  // Pointer to next node (for collision handling)
} Node;

// Hash table structure for variable and function storage
typedef struct ht {
    Node **entries;  // Array of entries (buckets)
    int size;        // Total size of hash table
    int count;       // Current number of stored elements
} ht_str;

// Scope structure for managing nested symbol tables
typedef struct Scope {
    ht_str *symbolTable;    // Variable symbol table
    ht_str *functionTable;  // Function symbol table
    struct Scope *parent;   // Pointer to the parent scope
    value_t return_val;     // Stores function return values
    int isReturn;           // Flag to indicate if return has been executed
} Scope;

// Structure for defining a function
typedef struct {
    int return_type;      // Return type of the function
    ast_type *param_list; // List of function parameters
    ast_type *body;       // Function body (AST node)
} function_t;

// Enumeration of AST node types
enum ast_types {
    _START = 1,

    _INT = 100, _DOUBLE = 101, _STRING = 102,

    _INT_TYPE = 200, _DOUBLE_TYPE = 201, _STRING_TYPE = 202, _VOID_TYPE = 203, _IDENTIFIER = 204, _LIST_TYPE = 205,
    _IF = 300, _FOR = 301, _WHILE = 302, _RETURN = 303, _PRINT = 304,

    _NEQUAL = 400, _GEQUAL = 401, _LEQUAL = 402, _EQUAL = 403, _PLUS = 404, _MINUS = 405, 
    _MULTIPLY = 406, _DIVIDE = 407, _LESS = 408, _GREATER = 409, _FAI = 410, _AND = 411, _OR = 412,

    _STATEMENTS = 500, _NEWFUNC = 501, _CONTROLBLOCK = 503, _DECLARATION = 504, _ASSIGNMENT = 505, 
    _FUNCALL = 508, _ARGLIST = 509, _ARGSLIST = 510, _OPTSTEP = 511, _PARENSTMT = 512, _EXPR = 513, 
    _RANDO = 514, _GIMME = 515, _INDEX_ACCESS = 516, _LIST_ASSIGNMENT = 517, _SIZE_UP = 518, _JOIN_IN = 519, 
    _PARAMLIST = 520, _PARAMSLIST = 521
};

// Function declarations

// Parser functions
void print_ast(ast_type *node, int depth);
value_t executor(ast_type *node, Scope *current_scope);

// Symbol table functions
void print_all_scopes(Scope *scope);
void print_symbol_table(ht_str *symbolTable);
void free_ht(ht_str *hashtable);
void resize_table(ht_str *hashtable);
value_t *search(ht_str *hashtable, const char *key);
Node *ht_pair(const char *key, const value_t value);
void ht_set(ht_str *hashtable, const char *key, const value_t value);
unsigned int hash_function(const char *key, int size);
ht_str *create_ht(int size);

// Scope management functions
Scope *enter_scope(Scope *current_scope);
Scope *exit_scope(Scope *current_scope);
value_t *lookup(Scope *current_scope, const char *key);
value_t *lookup_function(Scope *current_scope, const char *func_name);

// Stack functions
void s_push(node_s **head, value_t data);
value_t s_pop(node_s **head);
int s_empty(node_s **head);

// AST optimization
void optimize_ast(ast_type *node);

#endif // TYPES_H


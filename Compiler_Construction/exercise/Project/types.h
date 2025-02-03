#ifndef TYPES_H
#define TYPES_H
#define MAX_CHILD 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct list_t list_t;

typedef struct {
    int type; 
    union {
        int i;        
        double d;    
        char *s;
   	void *ptr;
	list_t *list;	
    } u;             
    int size;
} value_t;

typedef struct stackNode{
	value_t val;
	struct stackNode *next;
}node_s;

struct list_t{
    int type;  // Tipo dei valori nella lista (es: _INT_TYPE, _DOUBLE_TYPE, ecc.)
    value_t *elements; // Puntatore all'array di elementi
    int size; // Numero di elementi nella lista
    int capacity; // Capacità massima allocata
};



typedef struct ast {
        int type;
        struct ast *child[MAX_CHILD];
        union {
          int i;
          double d;
          char *s;
        } val;
} ast_type;

typedef struct node{
	char *key;
	value_t value;
	struct node *next;
}Node;

typedef struct ht{
	Node **entries;
	int size;
	int count;
}ht_str;

typedef struct Scope{
	ht_str *symbolTable;
	ht_str *functionTable;
	struct Scope *parent;
	value_t return_val;
	int isReturn;
}Scope;

typedef struct {
    int return_type;       // Tipo di ritorno (_INT_TYPE, _DOUBLE_TYPE, ecc.)
    ast_type *param_list;  // Lista dei parametri
    ast_type *body;        // Corpo della funzione
} function_t;

enum ast_types{
	_START = 1,

	_INT = 100, _DOUBLE = 101, _STRING = 102,

	_INT_TYPE = 200, _DOUBLE_TYPE = 201, _STRING_TYPE = 202, _VOID_TYPE = 203, _IDENTIFIER = 204, _LIST_TYPE = 205,
	_IF = 300, _FOR = 301, _WHILE = 302, _RETURN = 303, _PRINT = 304,

	_NEQUAL = 400, _GEQUAL = 401, _LEQUAL = 402, _EQUAL = 403, _PLUS = 404, _MINUS = 405, _MULTIPLY = 406, _DIVIDE = 407, _LESS = 408, _GREATER = 409, _FAI = 410, _AND = 411, _OR = 412,
	
	_STATEMENTS = 500, _NEWFUNC = 501, _CONTROLBLOCK = 503, _DECLARATION = 504, _ASSIGNMENT = 505, _FUNCALL = 508, _ARGLIST = 509,_ARGSLIST = 510, 
	_OPTSTEP = 511, _PARENSTMT = 512, _EXPR = 513, _RANDO = 514, _GIMME = 515, _INDEX_ACCESS =516, _LIST_ASSIGNMENT = 517, _SIZE_UP = 518, _JOIN_IN = 519, _PARAMLIST = 520, 
	_PARAMSLIST = 521
};


//parser file functions
void print_ast(ast_type *node, int depth);
value_t executor(ast_type *node, Scope *current_scope);

//symbol_table file functions
void print_all_scopes(Scope *scope);
void print_symbol_table(ht_str *symbolTable);
void free_ht (ht_str *hashtable);
void resize_table (ht_str *hashtable);
value_t *search (ht_str *hashtable, const char *key);
Node *ht_pair (const char *key, const value_t value);
void ht_set (ht_str *hashtable, const char *key, const value_t value);
unsigned int hash_function (const char *key, int size);
ht_str *create_ht (int size);

//scope file functions
Scope *enter_scope (Scope *current_scope);
Scope *exit_scope (Scope *current_scope);
value_t *lookup (Scope *current_scope, const char *key);
value_t *lookup_function(Scope *current_scope, const char *func_name);

//stack functions
void s_push(node_s **head, value_t data);
value_t s_pop(node_s **head);
int s_empty(node_s **head);

//Opt tree
void optimize_ast(ast_type *node);

#endif // TYPES_H

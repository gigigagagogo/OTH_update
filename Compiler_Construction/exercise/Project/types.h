#ifndef TYPES_H
#define TYPES_H
#define MAX_CHILD 4

typedef struct {
    int type; 
    union {
        int i;        
        double d;    
        char *s;     
    } u;             
} value_t;

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
	struct Scope *parent;
}Scope;


//parser file functions
void print_ast(ast_type *node, int depth);
int executor(ast_type *node, Scope *current_scope);

//symbol_table file functions
void free_ht (ht_str *hashtable);
void resize_table (ht_str *hashtable);
void *search (ht_str *hashtable, const char *key);
Node *ht_pair (const char *key, const value_t value);
void ht_set (ht_str *hashtable, const char *key, const value_t value);
unsigned int hash_function (const char *key, int size);
ht_str *create_ht (int size);

//scope file functions
Scope *enter_scope (Scope *current_scope);
Scope *exit_scope (Scope *current_scope);
value_t *lookup (Scope *current_scope, const char *key);
#endif // TYPES_H

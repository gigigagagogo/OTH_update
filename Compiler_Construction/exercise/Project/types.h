#ifndef TYPES_H
#define TYPES_H
#define MAX_CHILD 3

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


#endif // TYPES_H


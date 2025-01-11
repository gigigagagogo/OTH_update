#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int type; 
    union {
        int i;        
        double d;    
        char *s;     
    } u;             
} value_t;

#endif // TYPES_H


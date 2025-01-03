#ifndef _GRAMMAR_H
#define _GRAMMAR_H

typedef struct grammar {
        char *lhs;
        char *rhs;
} rules;

typedef struct nodeg {
        struct nodeg *prev;
        rules rule;
        struct nodeg *next; 
} node_g;



int generate_rules(node_g **head, node_g **tail);
int enqueue_grammar(node_g **head, node_g **tail, rules *grule);
void print_rules(node_g *head);

#endif /* _GRAMMAR_H */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
  char *id;
  int val;
} val_t;

typedef struct {
  val_t *val;
  int size;
} stack_t;

stack_t *s_new (void);
void s_push (stack_t *s, val_t elem);
val_t s_pop (stack_t *s);
int s_isempty (stack_t *s);
val_t *s_lookup (stack_t *s, char *id);

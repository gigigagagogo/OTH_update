#include <stdlib.h>
#include <string.h>
#include "stack.h"

stack_t *s_new (void) {
  return calloc(1, sizeof (stack_t));
}

void s_push (stack_t *s, val_t elem) {
  s->val = realloc(s->val, (s->size+1)*sizeof elem);
  s->val[s->size++] = elem;
}

val_t s_pop (stack_t *s) {
  return s->val[--s->size];
}

int s_isempty (stack_t *s) {
  return s->size == 0;
}

val_t *s_lookup (stack_t *s, char *id) {
  for (int i = 0; i < s->size; i++) {
    if (strcmp(s->val[i].id, id) == 0)
      return s->val+i;
  }
  return NULL;
}

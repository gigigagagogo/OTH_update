#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Stack implementation */

typedef int val_t;
typedef struct {
  val_t *val;
  int size;
} stack_t;

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

val_t s_peek (stack_t *s) {
  if (s_isempty(s))
    return 0;
  return s->val[s->size-1];
}

/* Generic DPDA implementation */

struct dpda {
  int initial;
  int (*transition)(int state, char ch, stack_t *stack);
};

struct dpda *create_dpda (int i, int (*t)(int, char, stack_t *)) {
    struct dpda *dpda = malloc(sizeof *dpda);

    dpda->initial = i;
    dpda->transition = t;

    return dpda;
}

struct dpda_ctx {
    struct dpda *dpda;
    int state;
    stack_t *stack;
    char *input;
    int offset;
};

struct dpda_ctx *dpda_new_ctx (struct dpda *dpda, char *word) {
    struct dpda_ctx *ctx = malloc (sizeof *ctx);

    ctx->dpda = dpda;
    ctx->state = dpda->initial;
    ctx->input = strdup(word);
    ctx->stack = s_new();
    ctx->offset = 0;

    return ctx;
}

int run_dpda (struct dpda_ctx *ctx) {
    while (ctx->input[ctx->offset] != '\0') {
        // Input word not fully consumed yet
        // Get next character and advance offset
        char ch = ctx->input[ctx->offset++];
        // Call the transition function of the dpda
        ctx->state = ctx->dpda->transition(ctx->state, ch, ctx->stack);
        if (ctx->state == 0)
            return 0; // We hit an invalid state, bail out
    }
    if (!s_isempty(ctx->stack))
      return 0;

    return 1;
}


/* Transition function for Exercise 6 */

int dpda1_transition (int st, char ch, stack_t *stack) {
    char s_ch = s_peek(stack);
    switch (st) {
        case 1: switch (ch) {
                case 'a': s_push(stack, 'a'); return 1;
                case 'b': s_push(stack, 'b'); return 1;
                case '.': return 2;
                default : return 0;
      } case 2: switch (ch) {
                case 'a': if (s_ch == 'a') { s_pop(stack); return 2; }
                          return 0;
                case 'b': if (s_ch == 'b') { s_pop(stack); return 2; }
                default : return 0;
      }
    }
    return 0; // Fallthrough
}

int main (int argc, char **argv) {
    struct dpda *dpda1 = create_dpda(1, dpda1_transition);
    
    struct dpda_ctx *dpda1_ctx = dpda_new_ctx(dpda1, argv[1]);
    int result = run_dpda(dpda1_ctx);

    printf("Word %s was %saccepted\n", dpda1_ctx->input, result ? "" : "NOT ");
}


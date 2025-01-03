#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


/* Generic DFA implementation */

struct dfa {
  int initial;
  int (*transition)(int state, char ch);
};

struct dfa *create_dfa (int i, int (*t)(int, char)) {
    struct dfa *dfa = malloc(sizeof *dfa);

    dfa->initial = i;
    dfa->transition = t;

    return dfa;
}

struct dfa_ctx {
    struct dfa *dfa;
    int state;
    char *input;
    int offset;
};

struct dfa_ctx *dfa_new_ctx (struct dfa *dfa, char *word) {
    struct dfa_ctx *ctx = malloc (sizeof *ctx);

    ctx->dfa = dfa;
    ctx->state = dfa->initial;
    ctx->input = strdup(word);
    ctx->offset = 0;

    return ctx;
}

int run_dfa (struct dfa_ctx *ctx) {
    while (ctx->input[ctx->offset] != '\0') {
        // Input word not fully consumed yet
        // Get next character and advance offset
        char ch = ctx->input[ctx->offset++];
        // Call the transition function of the dfa
        ctx->state = ctx->dfa->transition(ctx->state, ch);
        if (ctx->state == 0)
            return 0; // We hit an invalid state, bail out
    }

    return ctx->state < 0;
}


char *generate_word (void) {
  int len = random() % 20;
  char *word = malloc(len+1), *ptr = word;

  while (len--) {
    *ptr++ = '0' + rand()%2;
  }
  *ptr = '\0';

  return word;
}


/* Transition function for Exercise 3 */

int dfa3_transition (int st, char ch) {
    switch (st) {
        case 1: switch (ch) {
                case '0': return 1;
                case '1': return 2;
                default : return 0;
      } case 2: switch (ch) {
                case '0': return 3;
                case '1': return 2;
                default : return 0;
      } case 3: switch (ch) {
                case '0': return 1;
                case '1': return 4;
                default : return 0;
      } case 4: switch (ch) {
                case '0': return -5;
                case '1': return 4;
                default : return 0;
      } case -5: switch (ch) {
                case '0': return -6;
                case '1': return 4;
                default : return 0;
      } case -6: switch (ch) {
                case '0': return -6;
                case '1': return 2;
                default : return 0;
      } 
    }
    return 0; // Fallthrough
}

int main (int argc, char **argv) {
    srand(time(NULL));

    struct dfa *dfa3 = create_dfa(1, dfa3_transition);
    
    do {
      char *word = (argc == 2) ? argv[1] : generate_word();

      struct dfa_ctx *dfa3_ctx = dfa_new_ctx(dfa3, word);
      int result = run_dfa(dfa3_ctx);

      printf("Word %s was %saccepted\n", dfa3_ctx->input, result ? "" : "NOT ");
    } while (argc != 2);
}





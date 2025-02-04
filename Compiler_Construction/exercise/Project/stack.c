#include <stdio.h>
#include <stdlib.h>
#include "types.h"

// Pushes a value onto the stack
void s_push(node_s **head, value_t data) {
    node_s *newNode = calloc(1, sizeof(node_s));

    if (newNode == NULL) {
        printf("Error with memory allocation!\n");
        exit(EXIT_FAILURE);
    }

    // Handle string duplication to avoid pointer issues
    if (data.type == 2) { // Type 2 represents a string
        newNode->val.type = 2;
        newNode->val.u.s = strdup(data.u.s);
    } else {
        newNode->val = data;
    }

    newNode->next = *head;
    *head = newNode;
}

// Pops a value from the stack and returns it
value_t s_pop(node_s **head) {
    node_s *temp = *head;

    if (temp == NULL) {
        printf("Error: Stack underflow!\n");
        exit(EXIT_FAILURE);
    }

    value_t record = temp->val;

    // Move the head to the next node
    *head = temp->next;
    free(temp);

    return record;
}

// Checks if the stack is empty
int s_empty(node_s **head) {
    return (*head == NULL);
}

// CFarer Exercise 24: C23 - nullptr
// TOPIC: C23 nullptr keyword
// DIFFICULTY: Intermediate
// REQUIRES: C23 (-std=c2x / -std=c23)
//
// C23 introduces 'nullptr' - a typed null pointer constant (type nullptr_t).
// It is safer than the old NULL macro because it is always a pointer type,
// never accidentally an integer.
//
// Old way:   int *p = NULL;
// C23 way:   int *p = nullptr;
//
// Task: Fix the three TODO lines to use 'nullptr' instead of NULL or 0.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *node_new(int v) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == nullptr) return nullptr;   // already correct - study this line
    n->value = v;
    n->next  = NULL;   // TODO: replace NULL with nullptr
    return n;
}

int main(void) {
    Node *head = NULL;   // TODO: replace NULL with nullptr

    head = node_new(42);
    assert(head != nullptr);
    assert(head->value == 42);
    assert(head->next == nullptr);

    free(head);
    head = 0;   // TODO: replace 0 with nullptr

    assert(head == nullptr);
    printf("nullptr works correctly in C23!\n");
    return 0;
}

// I AM NOT DONE

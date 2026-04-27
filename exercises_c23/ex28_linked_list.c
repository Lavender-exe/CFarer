// CFarer Exercise 28: Linked List
// TOPIC: Dynamic allocation, structs, pointers - putting it all together
// DIFFICULTY: Advanced
//
// A singly linked list: each node holds a value and a pointer to the next node.
// The last node's 'next' is NULL (or nullptr in C23).
//
// Task: Implement the three functions below.
//   list_push_front  - allocate a new node and prepend it to *head
//   list_length      - count the nodes
//   list_free        - free every node

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int          value;
    struct Node *next;
} Node;

// Prepend a new node with 'value' to the list pointed at by *head.
void list_push_front(Node **head, int value) {
    // TODO
}

// Return the number of nodes in the list.
int list_length(Node *head) {
    // TODO
    return 0;
}

// Free all nodes.
void list_free(Node *head) {
    // TODO
}

int main(void) {
    Node *list = nullptr;

    list_push_front(&list, 3);
    list_push_front(&list, 2);
    list_push_front(&list, 1);

    assert(list_length(list) == 3);
    assert(list->value        == 1);
    assert(list->next->value  == 2);

    list_free(list);
    list = nullptr;

    assert(list_length(list) == 0);

    printf("Linked list works correctly!\n");
    return 0;
}

// I AM NOT DONE

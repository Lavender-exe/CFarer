// CFarer Exercise 23: Pointers to Pointers
// TOPIC: int **, replacing a pointer through a function
// DIFFICULTY: Intermediate
//
// A pointer-to-pointer stores the address of a pointer variable:
//   int x = 1;
//   int *p  = &x;
//   int **pp = &p;    // pp points at p
//   **pp              // the value p points at (1)
//
// This is how functions REPLACE a caller's pointer (think Node **head in a
// linked list, or char **argv).
//
// Task:
//   1. Implement replace_int(int **pp, int *new_target) - make *pp point at
//      new_target.
//   2. Implement allocate_int(int **out, int value) - allocate ONE int on the
//      heap, store the pointer in *out, write value into it. Return 0 on
//      success, -1 if malloc failed. Warm-up for the next exercise.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// TODO: implement replace_int
void replace_int(int **pp, int *new_target) {
}

// TODO: implement allocate_int (returns 0 on success, -1 on failure)
int allocate_int(int **out, int value) {
    return -1;
}

int main(void) {
    int a = 1, b = 2;
    int *p = &a;
    int **pp = &p;

    assert(**pp == 1);

    replace_int(pp, &b);   // equivalent: replace_int(&p, &b)
    assert(*p == 2);

    int *heap_val = NULL;
    assert(allocate_int(&heap_val, 99) == 0);
    assert(*heap_val == 99);
    free(heap_val);

    printf("Pointer-to-pointer works!\n");
    return 0;
}

// I AM NOT DONE

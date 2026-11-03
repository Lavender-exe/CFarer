// CFarer Exercise 15: Pointers
// TOPIC: &, *, pointer declaration
// DIFFICULTY: Intermediate
//
// A pointer stores the memory address of another variable.
//   int *p = &x;   // p points to x
//   *p = 42;       // write through the pointer (changes x)
//
// Task: Fix the swap() function so it actually swaps *a and *b.

#include <stdio.h>
#include <assert.h>

void swap(int *a, int *b) {
    // TODO: swap the values that a and b point to
    // Hint: you need a temporary variable
}

int main(void) {
    int x = 10, y = 20;
    swap(&x, &y);
    assert(x == 20);
    assert(y == 10);

    int p = 1, q = 99;
    swap(&p, &q);
    assert(p == 99);
    assert(q == 1);

    printf("swap() works correctly!\n");
    return 0;
}

// I AM NOT DONE

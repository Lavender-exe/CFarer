// CFarer Exercise 14: Your First Pointer
// TOPIC: &, *, pointer declaration
// DIFFICULTY: Intermediate
//
// A pointer is a variable that stores the memory ADDRESS of another variable.
//   int x = 5;
//   int *p = &x;   // & takes the address of x, p now "points at" x
//   *p             // the * operator READS the value at that address (5)
//   *p = 42;       // the * operator WRITES through the pointer, changing x
//
// Mental model: p is a signpost. & builds a signpost. * follows the signpost.
//
// Task: make the asserts pass using only pointer operations.

#include <stdio.h>
#include <assert.h>

int main(void) {
    int x = 5;
    int *p;   // declared but not pointing anywhere yet

    // TODO 1: make p point at x
    p = nullptr;   // placeholder: replace this line

    assert(p == &x);      // p holds the address of x
    assert(*p == 5);      // reading through the pointer sees x's value

    // TODO 2: change x to 42 by writing THROUGH p (do not touch x directly)
    *p = 0;

    assert(x == 42);

    int y = 100;
    // TODO 3: re-point p at y, then set y to 7 through p
    p = nullptr;   // placeholder: replace this line with two lines

    assert(y == 7);
    assert(x == 42);      // x is untouched now

    printf("Pointer basics work! x=%d, y=%d\n", x, y);
    return 0;
}

// I AM NOT DONE

// CFarer Exercise 24: Function Pointers - First Contact
// TOPIC: Declaring, assigning and calling function pointers
// DIFFICULTY: Intermediate
//
// A function pointer stores the address of a function:
//   int (*op)(int) = double_it;   // op now refers to double_it
//   op(5)                         // calls it: 10
//
// Read the declaration inside out: op is a pointer to a function taking int
// and returning int.
//
// Task:
//   1. Assign the right function to 'op' in each branch of pick().
//   2. Call through 'op' in run_twice() so it applies fn two times.

#include <stdio.h>
#include <assert.h>

int double_it(int x) { return x * 2; }
int square(int x)    { return x * x; }
int negate(int x)    { return -x; }

// mode 1 = double, mode 2 = square, mode 3 = negate
int (*pick(int mode))(int) {
    int (*op)(int) = double_it;   // placeholder: replace with the right
                                  // assignment for each mode
    // TODO: assign op based on mode
    return op;
}

int run_twice(int (*fn)(int), int x) {
    // TODO: apply fn two times and return the result
    return 0;
}

int main(void) {
    assert(pick(1)(5) == 10);
    assert(pick(2)(5) == 25);
    assert(pick(3)(5) == -5);

    assert(run_twice(double_it, 3) == 12);   // 3 -> 6 -> 12
    assert(run_twice(square, 2)    == 16);   // 2 -> 4 -> 16

    printf("Function pointers work!\n");
    return 0;
}

// I AM NOT DONE

// CFarer Exercise 10: Recursion
// TOPIC: Recursive functions
// DIFFICULTY: Intermediate
//
// Task: Implement factorial() recursively.
//   factorial(0) = 1
//   factorial(n) = n * factorial(n-1)  for n > 0

#include <stdio.h>
#include <assert.h>

long factorial(int n) {
    // TODO: base case + recursive case
    return 0;
}

int main(void) {
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(5) == 120);
    assert(factorial(10) == 3628800);

    printf("factorial() works correctly!\n");
    return 0;
}

// I AM NOT DONE

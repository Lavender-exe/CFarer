// CFarer Exercise 04: Arithmetic Operators
// TOPIC: +, -, *, /, %
// DIFFICULTY: Beginner
//
// C arithmetic operators:
//   +   addition
//   -   subtraction
//   *   multiplication
//   /   division  (integer division when both operands are int)
//   %   modulo    (remainder after division)
//
// Task: Fill in the expressions so every assert passes.

#include <stdio.h>
#include <assert.h>

int main(void) {
    int a = 20;
    int b = 6;

    int sum        = 0;   // TODO: a + b
    int difference = 0;   // TODO: a - b
    int product    = 0;   // TODO: a * b
    int quotient   = 0;   // TODO: a / b  (integer division)
    int remainder  = 0;   // TODO: a % b

    assert(sum        == 26);
    assert(difference == 14);
    assert(product    == 120);
    assert(quotient   == 3);
    assert(remainder  == 2);

    printf("All arithmetic checks passed!\n");
    return 0;
}

// I AM NOT DONE

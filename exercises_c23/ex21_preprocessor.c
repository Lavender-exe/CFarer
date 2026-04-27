// CFarer Exercise 21: Preprocessor Macros
// TOPIC: #define, macro functions, include guards
// DIFFICULTY: Intermediate
//
// The C preprocessor runs BEFORE compilation and performs textual substitution.
//
// Tasks:
//   1. Define a macro MAX(a, b) that expands to the larger of a or b.
//   2. Define a constant macro PI with the value 3.14159265358979.
//   3. Define a macro SQUARE(x) that expands to (x)*(x).
//      (Note the parentheses - they prevent operator-precedence surprises.)

#include <stdio.h>
#include <math.h>
#include <assert.h>

// TODO: define MAX(a, b)
// TODO: define PI
// TODO: define SQUARE(x)

int main(void) {
    assert(MAX(3, 7)     == 7);
    assert(MAX(-1, -5)   == -1);
    assert(MAX(4, 4)     == 4);

    assert(fabs(PI - 3.14159265358979) < 1e-10);

    assert(SQUARE(5)   == 25);
    assert(SQUARE(2+1) == 9);   // this would break without the parens!

    printf("Macros work correctly!\n");
    return 0;
}

// I AM NOT DONE

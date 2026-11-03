// CFarer Exercise 39: Generic Math Macros
// TOPIC: _Generic, type-safe generic functions
// DIFFICULTY: Advanced
//
// The standard library has separate abs() / fabs() / fabsf() for different types.
// With _Generic we can write a single ABS(x) macro that dispatches correctly.
//
// Task: Implement ABS(x) - a macro that returns the absolute value of x
// by dispatching to the right function based on type:
//   int    -> abs(x)      from <stdlib.h>
//   long   -> labs(x)     from <stdlib.h>
//   float  -> fabsf(x)    from <math.h>
//   double -> fabs(x)     from <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

// TODO: define ABS(x) using _Generic
#define ABS(x) (x)   // placeholder - replace this

int main(void) {
    assert(ABS(-5)     == 5);
    assert(ABS(5)      == 5);
    assert(ABS(-5L)    == 5L);
    assert(ABS(-2.5f)  == 2.5f);
    assert(ABS(-3.14)  == 3.14);

    // Confirm types are preserved (sizeof check)
    assert(sizeof(ABS(-5))    == sizeof(int));
    assert(sizeof(ABS(-5L))   == sizeof(long));
    assert(sizeof(ABS(-2.5f)) == sizeof(float));
    assert(sizeof(ABS(-3.14)) == sizeof(double));

    printf("ABS macro: %d  %ld  %f  %f\n",
           ABS(-7), ABS(-7L), (double)ABS(-2.5f), ABS(-3.14));
    return 0;
}

// I AM NOT DONE

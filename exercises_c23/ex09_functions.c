// CFarer Exercise 09: Functions
// TOPIC: Function definition, parameters, return values
// DIFFICULTY: Beginner
//
// Task: Implement the three functions below.
//   max2(a, b)        -> returns the larger of two ints
//   is_even(n)        -> returns 1 if n is even, 0 otherwise
//   celsius_to_f(c)   -> converts Celsius to Fahrenheit  (F = C * 9/5 + 32)

#include <stdio.h>
#include <assert.h>

// TODO: implement max2
int max2(int a, int b) {
    return 0;
}

// TODO: implement is_even
int is_even(int n) {
    return 0;
}

// TODO: implement celsius_to_f
double celsius_to_f(double c) {
    return 0.0;
}

int main(void) {
    assert(max2(3, 7)    == 7);
    assert(max2(10, -1)  == 10);
    assert(max2(5, 5)    == 5);

    assert(is_even(4)  == 1);
    assert(is_even(7)  == 0);
    assert(is_even(0)  == 1);

    assert(celsius_to_f(0.0)   == 32.0);
    assert(celsius_to_f(100.0) == 212.0);

    printf("All function checks passed!\n");
    return 0;
}

// I AM NOT DONE

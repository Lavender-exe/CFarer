// CFarer Exercise 25: C23 - typeof
// TOPIC: C23 typeof operator
// DIFFICULTY: Advanced
// REQUIRES: C23 (-std=c2x / -std=c23)
//
// typeof(expr) produces the TYPE of an expression at compile time -
// without evaluating the expression. It is useful for writing generic macros.
//
// Example:
//   int x = 5;
//   typeof(x) y = 10;   // y is int, same type as x
//
// Task: The SWAP macro below uses typeof to declare a tmp variable of
// the correct type. Fill in the macro body.

#include <stdio.h>
#include <assert.h>

// TODO: define SWAP(a, b) using typeof
// It should work for ANY type (int, double, char*, …)
#define SWAP(a, b) /* your implementation here */

int main(void) {
    int x = 1, y = 2;
    SWAP(x, y);
    assert(x == 2 && y == 1);

    double p = 1.5, q = 2.5;
    SWAP(p, q);
    assert(p == 2.5 && q == 1.5);

    char *s1 = "hello";
    char *s2 = "world";
    SWAP(s1, s2);
    assert(s1[0] == 'w');
    assert(s2[0] == 'h');

    printf("typeof-powered SWAP works for any type!\n");
    return 0;
}

// I AM NOT DONE

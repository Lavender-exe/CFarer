// CFarer Exercise 16: Structs
// TOPIC: struct definition, member access with .
// DIFFICULTY: Intermediate
//
// A struct groups related data under one name.
//
// Task:
//   1. Define a struct named Point with two double members: x and y.
//   2. Implement distance() - Euclidean distance between two Points.
//      Formula: sqrt((b.x-a.x)^2 + (b.y-a.y)^2)

#include <stdio.h>
#include <math.h>
#include <assert.h>

// TODO: define struct Point here

double distance(/* TODO: two Point parameters */) {
    return 0.0;
}

int main(void) {
    // Once struct Point is defined, these should work:
    struct Point origin = {0.0, 0.0};
    struct Point p      = {3.0, 4.0};

    double d = distance(origin, p);
    assert(fabs(d - 5.0) < 1e-9);   // 3-4-5 right triangle

    printf("distance = %.2f\n", d);
    return 0;
}

// I AM NOT DONE

// CFarer Exercise 17: typedef + struct
// TOPIC: typedef, struct, -> operator
// DIFFICULTY: Intermediate
//
// typedef lets you create an alias for a type so you don't need
// to write 'struct Foo' everywhere - just 'Foo'.
//
// The -> operator accesses struct members through a pointer:
//   ptr->member  is the same as  (*ptr).member
//
// Task:
//   1. Create a typedef so 'Vec2' is an alias for struct Vec2.
//   2. Implement vec2_add() which adds two Vec2 values.
//   3. Implement vec2_scale() which multiplies both components by s.

#include <stdio.h>
#include <assert.h>
#include <math.h>

// TODO: define struct Vec2 and typedef Vec2

// TODO: implement Vec2 vec2_add(Vec2 a, Vec2 b)

// TODO: implement Vec2 vec2_scale(Vec2 v, double s)

int main(void) {
    Vec2 a = {1.0, 2.0};
    Vec2 b = {3.0, 4.0};

    Vec2 sum = vec2_add(a, b);
    assert(fabs(sum.x - 4.0) < 1e-9);
    assert(fabs(sum.y - 6.0) < 1e-9);

    Vec2 scaled = vec2_scale(a, 3.0);
    assert(fabs(scaled.x - 3.0) < 1e-9);
    assert(fabs(scaled.y - 6.0) < 1e-9);

    printf("Vec2 operations work correctly!\n");
    return 0;
}

// I AM NOT DONE

// CFarer Exercise 16: Output Parameters
// TOPIC: Pointers as function "return channels"
// DIFFICULTY: Intermediate
//
// A C function returns exactly one value. Pointers let a function hand back
// several: the caller passes addresses, the callee writes through them.
//   void min_max(int a, int b, int *min_out, int *max_out)
// This is the same idea as the swap() you just fixed, one step further.
//
// Task: implement min_max() so it writes the smaller value through min_out
// and the larger value through max_out.

#include <stdio.h>
#include <assert.h>

void min_max(int a, int b, int *min_out, int *max_out) {
    // TODO: write the results through the two pointers
}

int main(void) {
    int lo = 0, hi = 0;

    min_max(3, 9, &lo, &hi);
    assert(lo == 3 && hi == 9);

    min_max(-2, -7, &lo, &hi);
    assert(lo == -7 && hi == -2);

    min_max(5, 5, &lo, &hi);
    assert(lo == 5 && hi == 5);

    printf("min_max() works correctly!\n");
    return 0;
}

// I AM NOT DONE

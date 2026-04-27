// CFarer Exercise 34: Integer Overflow Detection
// TOPIC: Signed overflow (UB), unsigned wraparound, safe arithmetic
// DIFFICULTY: Advanced  CATEGORY: Secure Code
//
// Signed integer overflow is UNDEFINED BEHAVIOR in C.
// Compilers may optimize around it in ways that break your program silently.
// Unsigned overflow is defined (wraps mod 2^N) but still a common bug.
//
// Safe pattern: check BEFORE the operation, not after.
//
//   BAD:  if (a + b < a) { overflow! }   <- a+b is already UB if signed
//   GOOD: if (b > INT_MAX - a) { overflow! }
//
// Task: Implement the four safe arithmetic functions.
// Each returns 1 on success (storing result in *out), 0 on overflow.

#include <stdio.h>
#include <limits.h>
#include <assert.h>

// Safe signed addition: returns 1 if ok, 0 if overflow
int safe_add(int a, int b, int *out) {
    // TODO: check before adding
    return 0;
}

// Safe signed subtraction
int safe_sub(int a, int b, int *out) {
    // TODO
    return 0;
}

// Safe signed multiplication
int safe_mul(int a, int b, int *out) {
    // TODO
    return 0;
}

// Safe unsigned addition (wraps - detect if result < either operand)
int safe_uadd(unsigned a, unsigned b, unsigned *out) {
    // TODO
    return 0;
}

int main(void) {
    int r;
    unsigned ur;

    assert(safe_add(100,  200, &r) == 1 && r == 300);
    assert(safe_add(INT_MAX, 1, &r) == 0);          // overflow
    assert(safe_add(INT_MIN, -1, &r) == 0);         // overflow

    assert(safe_sub(10, 3, &r) == 1 && r == 7);
    assert(safe_sub(INT_MIN, 1, &r) == 0);          // overflow

    assert(safe_mul(6, 7, &r) == 1 && r == 42);
    assert(safe_mul(INT_MAX, 2, &r) == 0);          // overflow
    assert(safe_mul(-1, INT_MIN, &r) == 0);         // overflow (INT_MIN/-1 = INT_MAX+1)

    assert(safe_uadd(10u, 20u, &ur) == 1 && ur == 30u);
    assert(safe_uadd(UINT_MAX, 1u, &ur) == 0);      // wraparound

    printf("All safe arithmetic checks passed!\n");
    return 0;
}

// I AM NOT DONE

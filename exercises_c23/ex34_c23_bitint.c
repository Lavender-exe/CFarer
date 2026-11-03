// CFarer Exercise 34: C23 - _BitInt(N)
// TOPIC: Bit-precise integer types
// DIFFICULTY: Advanced
// REQUIRES: C23 (-std=c2x / -std=c23) + a compiler that supports _BitInt
//           (GCC 13+, Clang 14+)
//
// _BitInt(N) declares an integer with EXACTLY N bits.
//   _BitInt(4)  -> 4-bit signed int  (range: -8 .. 7)
//   unsigned _BitInt(8) -> 8-bit unsigned (range: 0 .. 255)
//   _BitInt(64) -> 64-bit signed integer
//
// Arithmetic wraps: a 4-bit signed value 7 + 1 wraps to -8 (two's
// complement), an unsigned 8-bit 255 + 1 wraps to 0.
//
// Task: change the three declarations to the _BitInt types described in the
// TODO comments so every assert passes.

#include <stdio.h>
#include <assert.h>

int main(void) {
    // TODO 1: make 'small' a 4-bit signed _BitInt so 7 + 1 wraps to -8
    long small = 7;
    assert(small == 7);
    small += 1;
    assert(small == -8);

    // TODO 2: make 'byte_val' an unsigned 8-bit _BitInt so 255 + 1 wraps to 0
    unsigned long byte_val = 255;
    assert(byte_val == 255);
    byte_val += 1;
    assert(byte_val == 0);

    // TODO 3: make 'big' a _BitInt(64) holding exactly 10^18
    long long big = 1;
    assert(big == 1000000000000000000LL);

    printf("_BitInt works!  small=%d  byte_val=%u  big=%lld\n",
           (int)small, (unsigned)byte_val, (long long)big);
    return 0;
}

// I AM NOT DONE

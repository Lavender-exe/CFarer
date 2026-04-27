// CFarer Exercise 27: C23 - _BitInt(N)
// TOPIC: Bit-precise integer types
// DIFFICULTY: Advanced
// REQUIRES: C23 (-std=c2x / -std=c23) + a compiler that supports _BitInt
//           (GCC 13+, Clang 14+)
//
// _BitInt(N) declares an integer with EXACTLY N bits.
// This is useful in embedded/systems programming where bit widths matter.
//
//   _BitInt(4)  -> 4-bit signed int  (range: -8 .. 7)
//   unsigned _BitInt(4) -> 4-bit unsigned (range: 0 .. 15)
//   _BitInt(128) -> 128-bit signed integer!
//
// Task: Use _BitInt types to answer the questions in the asserts.

#include <stdio.h>
#include <assert.h>

int main(void) {
    // A 4-bit signed integer can hold values -8 to 7.
    _BitInt(4) small = 7;
    assert(small == 7);

    // Overflow wraps: 7 + 1 in a 4-bit signed = -8
    small += 1;
    assert(small == -8);   // two's complement wraparound

    // Unsigned 8-bit
    unsigned _BitInt(8) byte_val = 255;
    assert(byte_val == 255);
    byte_val += 1;
    assert(byte_val == 0);   // unsigned 8-bit overflow wraps to 0

    // Large integers: 64-bit custom
    _BitInt(64) big = 1000000000LL * 1000000000LL;   // 10^18
    assert(big > 0);

    printf("_BitInt works!  small=%d  byte_val=%u  big=%lld\n",
           (int)small, (unsigned)byte_val, (long long)big);
    return 0;
}

// I AM NOT DONE

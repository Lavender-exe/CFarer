// CFarer Exercise 03: printf Format Specifiers
// TOPIC: printf, format specifiers
// DIFFICULTY: Beginner
//
// printf uses format specifiers as placeholders for values:
//   %d  -> int
//   %f  -> float / double (note: %f prints 6 decimal places, e.g. 3.140000)
//   %c  -> char
//   %s  -> string (char array / pointer)
//   %zu -> size_t  (unsigned size)
//
// printf returns the number of characters printed - the asserts use that
// to check that you picked the RIGHT specifier, not just any specifier.
//
// Task: Replace each ??? inside the format strings with the correct specifier.
// Expected output:
//   Count: 42
//   Pi: 3.14
//   Letter: Z
//   Name: Alice

#include <stdio.h>
#include <assert.h>

int main(void) {
    int    count  = 42;
    double pi     = 3.14;
    char   letter = 'Z';
    char   name[] = "Alice";

    assert(printf("Count: ???\n",  count) == 10);   // "Count: 42\n"
    assert(printf("Pi: ???\n",     pi)     == 13);   // "Pi: 3.140000\n"
    assert(printf("Letter: ???\n", letter) == 10);   // "Letter: Z\n"
    assert(printf("Name: ???\n",   name)   == 12);   // "Name: Alice\n"

    return 0;
}

// I AM NOT DONE

// CFarer Exercise 03: printf Format Specifiers
// TOPIC: printf, format specifiers
// DIFFICULTY: Beginner
//
// printf uses format specifiers as placeholders for values:
//   %d  -> int
//   %f  -> float / double
//   %c  -> char
//   %s  -> string (char array / pointer)
//   %zu -> size_t  (unsigned size)
//
// Task: Replace each ??? inside the format strings with the correct specifier.
// Expected output:
//   Count: 42
//   Pi: 3.14
//   Letter: Z
//   Name: Alice

#include <stdio.h>

int main(void) {
    int    count  = 42;
    double pi     = 3.14;
    char   letter = 'Z';
    char   name[] = "Alice";

    printf("Count: ???\n",  count);   // fix the specifier
    printf("Pi: ???\n",     pi);      // fix the specifier
    printf("Letter: ???\n", letter);  // fix the specifier
    printf("Name: ???\n",   name);    // fix the specifier

    return 0;
}

// I AM NOT DONE

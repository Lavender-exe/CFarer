// CFarer Exercise 26: C23 - constexpr
// TOPIC: C23 constexpr for compile-time constants
// DIFFICULTY: Advanced
// REQUIRES: C23 (-std=c2x / -std=c23)
//
// C23 adds 'constexpr' - a typed, scoped compile-time constant.
// Unlike #define, constexpr has a type and obeys scope rules.
//
//   constexpr int LIMIT = 100;
//   constexpr double TAU = 6.28318530717958;
//
// constexpr variables can be used as array sizes, case labels, and
// anywhere else a compile-time integer constant is required.
//
// Task: Replace the #define constants with constexpr declarations,
// then use BUFFER_SIZE as a stack array size.

#include <stdio.h>
#include <assert.h>
#include <string.h>

// TODO: replace these #define constants with constexpr declarations
#define BUFFER_SIZE 64
#define MAX_RETRIES 3
#define GRAVITY     9.81

int main(void) {
    // Using BUFFER_SIZE as a VLA/array size (valid because constexpr is
    // a compile-time constant, unlike a runtime variable).
    char buf[BUFFER_SIZE];
    memset(buf, 0, sizeof(buf));
    strncpy(buf, "CFarer", BUFFER_SIZE - 1);

    assert(sizeof(buf) == BUFFER_SIZE);
    assert(strcmp(buf, "CFarer") == 0);
    assert(MAX_RETRIES == 3);
    assert(GRAVITY > 9.8 && GRAVITY < 9.82);

    printf("constexpr: BUFFER_SIZE=%d  MAX_RETRIES=%d  GRAVITY=%.2f\n",
           (int)BUFFER_SIZE, (int)MAX_RETRIES, (double)GRAVITY);
    return 0;
}

// I AM NOT DONE

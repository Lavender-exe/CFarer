// CFarer Exercise 06: switch Statement
// TOPIC: switch, case, break, default
// DIFFICULTY: Beginner
//
// Task: Complete day_name() using a switch statement.
// It receives a day number (1=Monday … 7=Sunday) and returns its name.
// Return "unknown" for any other value.

#include <stdio.h>
#include <assert.h>
#include <string.h>

const char *day_name(int day) {
    switch (day) {
        // TODO: add cases 1-7 and a default
    }
    return "unknown";
}

int main(void) {
    assert(strcmp(day_name(1), "Monday")    == 0);
    assert(strcmp(day_name(3), "Wednesday") == 0);
    assert(strcmp(day_name(7), "Sunday")    == 0);
    assert(strcmp(day_name(9), "unknown")   == 0);

    printf("day_name() works correctly!\n");
    return 0;
}

// I AM NOT DONE

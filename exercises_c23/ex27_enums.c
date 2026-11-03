// CFarer Exercise 27: Enums
// TOPIC: enum, named constants
// DIFFICULTY: Intermediate
//
// An enum assigns integer names to sequential constants.
// By default they start at 0 and increment.
//
// Task: Define a Direction enum with values NORTH, SOUTH, EAST, WEST.
// Then implement direction_name() which returns the string for each value.

#include <stdio.h>
#include <assert.h>
#include <string.h>

// TODO: define enum Direction (NORTH, SOUTH, EAST, WEST)

// TODO: implement direction_name
const char *direction_name(/* Direction d */) {
    return "unknown";
}

int main(void) {
    assert(strcmp(direction_name(NORTH), "NORTH") == 0);
    assert(strcmp(direction_name(SOUTH), "SOUTH") == 0);
    assert(strcmp(direction_name(EAST),  "EAST")  == 0);
    assert(strcmp(direction_name(WEST),  "WEST")  == 0);

    printf("Direction enum works correctly!\n");
    return 0;
}

// I AM NOT DONE

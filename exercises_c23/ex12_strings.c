// CFarer Exercise 12: Strings
// TOPIC: char arrays, null terminator, string length
// DIFFICULTY: Intermediate
//
// In C, a string is a char array ending with '\0' (null terminator).
//
// Task: Implement my_strlen() WITHOUT using <string.h>.
// It must count characters up to (but not including) the '\0'.

#include <stdio.h>
#include <assert.h>

int my_strlen(const char *s) {
    // TODO: count characters until you hit '\0'
    return 0;
}

int main(void) {
    assert(my_strlen("")        == 0);
    assert(my_strlen("hello")   == 5);
    assert(my_strlen("CFarer")  == 6);
    assert(my_strlen("C\0bad")  == 1);  // stops at first '\0'

    printf("my_strlen() works correctly!\n");
    return 0;
}

// I AM NOT DONE

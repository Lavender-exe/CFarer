// CFarer Exercise 13: Standard String Functions
// TOPIC: <string.h> - strlen, strcpy, strcat, strcmp
// DIFFICULTY: Intermediate
//
// NEXT: the next exercise introduces pointers, the most important (and
// trickiest) idea in C. Take it slow.
//
// Task: Use functions from <string.h> to build a greeting string.
// Starting from an empty buffer, concatenate first name + " " + last name,
// then check the result equals "Ada Lovelace" and its length is 12.

#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void) {
    char first[] = "Ada";
    char last[]  = "Lovelace";
    char buf[64] = "";   // start empty

    // TODO: use strcpy / strcat to build "Ada Lovelace" in buf

    assert(strcmp(buf, "Ada Lovelace") == 0);
    assert(strlen(buf) == 12);

    printf("Greeting: %s  (length %zu)\n", buf, strlen(buf));
    return 0;
}

// I AM NOT DONE

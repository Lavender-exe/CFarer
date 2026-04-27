// CFarer Exercise 05: if / else
// TOPIC: Conditionals
// DIFFICULTY: Beginner
//
// Task: Write the body of classify() so it returns:
//   "negative" when n < 0
//   "zero"     when n == 0
//   "positive" when n > 0

#include <stdio.h>
#include <assert.h>
#include <string.h>

const char *classify(int n) {
    // TODO: return the correct string based on n
    return "";
}

int main(void) {
    assert(strcmp(classify(-5), "negative") == 0);
    assert(strcmp(classify(0),  "zero")     == 0);
    assert(strcmp(classify(7),  "positive") == 0);

    printf("classify() works correctly!\n");
    return 0;
}

// I AM NOT DONE

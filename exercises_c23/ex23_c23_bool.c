// CFarer Exercise 23: C23 - bool, true, false
// TOPIC: C23 boolean keywords
// DIFFICULTY: Intermediate
// REQUIRES: C23 compiler flag (-std=c2x or -std=c23)
//
// Before C23 you needed:  #include <stdbool.h>
// In C23, 'bool', 'true', and 'false' are built-in keywords.
// No include needed!
//
// Task: Implement is_palindrome() which returns true if a string reads
// the same forwards and backwards, false otherwise.
// Do NOT include <stdbool.h>.

#include <stdio.h>
#include <string.h>
#include <assert.h>
// No <stdbool.h> needed in C23!

bool is_palindrome(const char *s) {
    // TODO: compare s[i] with s[len-1-i] for i from 0 to len/2
    return false;
}

int main(void) {
    assert(is_palindrome("racecar") == true);
    assert(is_palindrome("level")   == true);
    assert(is_palindrome("a")       == true);
    assert(is_palindrome("")        == true);
    assert(is_palindrome("hello")   == false);
    assert(is_palindrome("ab")      == false);

    printf("is_palindrome() works! (using C23 bool)\n");
    return 0;
}

// I AM NOT DONE

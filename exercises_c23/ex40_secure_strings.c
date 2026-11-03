// CFarer Exercise 40: Secure String Handling
// TOPIC: Buffer overflows, snprintf, strncpy, strncat
// DIFFICULTY: Intermediate  CATEGORY: Secure Code
//
// NEVER use these in production:
//   gets()          - no bounds check, always overflows
//   sprintf()       - no bounds check on output buffer
//   strcpy()        - no bounds check on destination
//   strcat()        - no bounds check on destination
//
// ALWAYS prefer the bounded versions:
//   fgets(buf, sizeof(buf), stdin)
//   snprintf(buf, sizeof(buf), fmt, ...)
//   strncpy(dst, src, sizeof(dst) - 1); dst[sizeof(dst)-1] = '\0';
//   strncat(dst, src, sizeof(dst) - strlen(dst) - 1);
//
// Task: Fix the four UNSAFE calls below to use their safe equivalents.
// Each is marked with a // UNSAFE comment.

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BUFSIZE 16

int main(void) {
    char dst[BUFSIZE];
    char result[BUFSIZE];
    const char *long_src = "This string is way too long for the buffer!!!!!";

    // UNSAFE: strcpy - no bounds check
    strcpy(dst, long_src);   // TODO: fix with strncpy + manual null term

    // UNSAFE: strcat - no bounds check
    char greeting[BUFSIZE] = "Hello";
    strcat(greeting, ", World! Extra overflow text here.");  // TODO: fix with strncat

    // UNSAFE: sprintf - no output bounds check
    int value = 42;
    sprintf(result, "Value = %d and some extra padding text!!!", value);  // TODO: fix with snprintf

    // Verify safe behavior: dst must be at most BUFSIZE-1 chars
    assert(strlen(dst)      < BUFSIZE);
    assert(strlen(greeting) < BUFSIZE);
    assert(strlen(result)   < BUFSIZE);

    printf("dst:      [%s]\n", dst);
    printf("greeting: [%s]\n", greeting);
    printf("result:   [%s]\n", result);
    printf("All buffers stayed within bounds!\n");
    return 0;
}

// I AM NOT DONE

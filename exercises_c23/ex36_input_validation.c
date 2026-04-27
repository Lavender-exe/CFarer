// CFarer Exercise 36: Input Validation
// TOPIC: Sanitizing untrusted input, strtol, format string safety
// DIFFICULTY: Advanced  CATEGORY: Secure Code
//
// Never trust input.  Common attack surfaces:
//   - Integer parsing: atoi() has NO error detection - use strtol()
//   - Format strings: printf(user_input) is dangerous - ALWAYS use printf("%s", s)
//   - Length checks: reject input that exceeds expected bounds
//
// Task: Fix parse_port() which parses a port number string.
// Requirements:
//   - Must reject non-numeric input (return -1)
//   - Must reject partial parses like "80abc" (return -1)
//   - Must reject out-of-range values (valid ports: 1..65535) (return -1)
//   - Returns the port number on success

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

int parse_port(const char *s) {
    // UNSAFE current implementation:
    return atoi(s);   // TODO: replace with strtol + full validation
}

// Safe print: never pass untrusted strings directly as format
void safe_log(const char *msg) {
    // UNSAFE: printf(msg);    <- format string vulnerability!
    printf("%s\n", msg);   // this one is already correct - study it
}

int main(void) {
    assert(parse_port("80")     == 80);
    assert(parse_port("443")    == 443);
    assert(parse_port("65535")  == 65535);

    assert(parse_port("0")      == -1);      // 0 is not a valid port
    assert(parse_port("65536")  == -1);      // out of range
    assert(parse_port("-1")     == -1);      // negative
    assert(parse_port("80abc")  == -1);      // trailing garbage
    assert(parse_port("abc")    == -1);      // not a number
    assert(parse_port("")       == -1);      // empty string
    assert(parse_port("99999")  == -1);      // too large

    safe_log("Input validation passed!");
    return 0;
}

// I AM NOT DONE

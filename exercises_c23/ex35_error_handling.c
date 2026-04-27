// CFarer Exercise 35: Error Handling Patterns
// TOPIC: errno, perror, return-code discipline, cleanup on error
// DIFFICULTY: Advanced  CATEGORY: Secure Code
//
// Production C code handles every error path.
// Key rules:
//   1. Check EVERY syscall / library return value
//   2. On failure, use errno + perror() / strerror() to explain why
//   3. Clean up (close files, free memory) on EVERY exit path - including errors
//   4. Never ignore a return value silently
//
// Task: Fix open_and_read() so it:
//   a) Checks fopen() for NULL and returns -1 on failure
//   b) Reads up to (bufsize-1) bytes safely
//   c) Null-terminates the buffer
//   d) ALWAYS closes the file before returning (even on read error)
//   e) Returns number of bytes read on success, -1 on any error

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

// Returns bytes read (>=0) or -1 on error.
// Buffer is always null-terminated on success.
long open_and_read(const char *path, char *buf, size_t bufsize) {
    // TODO: fix this implementation
    FILE *fp = fopen(path, "r");
    // missing: NULL check

    size_t n = fread(buf, 1, bufsize, fp);
    // missing: null termination
    // missing: guaranteed fclose

    return (long)n;
}

int main(void) {
    // Create a temp file with known content
    {
        FILE *f = fopen("test_input.txt", "w");
        assert(f != nullptr);
        fputs("Hello, CFarer!\n", f);
        fclose(f);
    }

    char buf[32];

    // Happy path
    long n = open_and_read("test_input.txt", buf, sizeof(buf));
    assert(n > 0);
    assert(buf[n] == '\0');               // must be null-terminated
    assert(strncmp(buf, "Hello", 5) == 0);

    // Error path: file does not exist - must return -1, not crash
    long err = open_and_read("does_not_exist.txt", buf, sizeof(buf));
    assert(err == -1);

    remove("test_input.txt");
    printf("Error handling works correctly!\n");
    return 0;
}

// I AM NOT DONE

// CFarer Exercise 42: Error Handling Patterns
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
// Task: finish open_and_read() so it:
//   a) Returns -1 on fopen failure and reports the reason with perror()
//   b) Reads at most bufsize - 1 bytes so the terminator always fits
//      (the current fread(buf, 1, bufsize, ...) is a buffer overflow
//      waiting for a file that is bufsize bytes or larger)
//   c) Null-terminates the buffer (already done - but only safe after (b))
//   d) Closes the file on EVERY exit path (already done - keep it that way)
//   e) Returns the byte count on success, -1 on ANY error
//      (the -2 / -3 placeholders below must all become -1)

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

// Returns bytes read (>=0) or -1 on error.
// Buffer is always null-terminated on success.
long open_and_read(const char *path, char *buf, size_t bufsize) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        return -2;   // TODO (a): return -1 instead, and report the error
                     // with perror() so the user knows WHY it failed
    }

    size_t n = fread(buf, 1, bufsize, fp);   // TODO (b): read at most
                                             // bufsize - 1 bytes so the
                                             // terminator always fits
    if (ferror(fp)) {
        fclose(fp);
        return -3;   // TODO (c): return -1 here too - every error path
                     // reports failure the same way
    }

    buf[n] = '\0';   // null-terminate (correct - but only safe once (b) is fixed)
    fclose(fp);       // cleanup - needed on EVERY exit path
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

// CFarer Exercise 44: Secure Memory Handling
// TOPIC: Zeroing sensitive data, use-after-free prevention, double-free
// DIFFICULTY: Advanced  CATEGORY: Secure Code
//
// Rules for sensitive data (passwords, keys, tokens):
//   1. Zero memory before freeing - compiler may optimize away plain memset!
//      Use a volatile pointer or platform API (SecureZeroMemory on Windows,
//      explicit_bzero on Linux, or a volatile loop).
//   2. Set pointer to NULL immediately after free (prevents use-after-free).
//   3. Never free a pointer twice.
//
// Task:
//   a) Implement secure_zero(ptr, len) - zero memory in a way the
//      compiler CANNOT optimize away (use a volatile write loop).
//   b) Fix secure_free() to zero the buffer, then free, then NULL the pointer.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Zero memory using volatile writes - optimizer cannot remove these.
void secure_zero(void *ptr, size_t len) {
    // TODO: cast ptr to volatile unsigned char* and write 0 to each byte
}

// Securely free a buffer: zero it, free it, null the caller's pointer.
void secure_free(void **ptr, size_t len) {
    if (!ptr || !*ptr) return;
    // TODO: call secure_zero, then free(*ptr), then set *ptr = nullptr
}

int main(void) {
    // Allocate a "password" buffer
    size_t sz  = 32;
    char  *buf = (char *)malloc(sz);
    assert(buf != nullptr);
    memcpy(buf, "supersecretpassword\0", 20);

    // Verify it has content before zeroing
    assert(buf[0] == 's');

    secure_zero(buf, sz);

    // Every byte must be 0 after secure_zero
    for (size_t i = 0; i < sz; i++)
        assert(((unsigned char *)buf)[i] == 0);

    // secure_free must null the pointer
    void *vbuf = buf;
    secure_free(&vbuf, sz);
    assert(vbuf == nullptr);   // must be nulled

    printf("Secure memory handling works!\n");
    return 0;
}

// I AM NOT DONE

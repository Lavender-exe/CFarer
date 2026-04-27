// CFarer - Linux Internals Exercise 03
// TOPIC: mmap + mprotect - anonymous executable memory
// DIFFICULTY: Intermediate  PLATFORM: Linux
// PURPOSE: Linux internals / shellcode staging
//
// mmap(MAP_ANONYMOUS | MAP_PRIVATE) allocates memory backed by nothing (no file).
// mprotect() changes the protection flags on an existing mapping.
//
// Common shellcode staging pattern:
//   1. mmap(PROT_READ|PROT_WRITE)  - write shellcode
//   2. mprotect(PROT_READ|PROT_EXEC) - make executable, remove write
//   3. Call as function pointer
//
// W^X (write XOR execute): never have a page both writable and executable.
// This is enforced by NX (no-execute) hardware + kernel.
// SELinux/AppArmor may also deny mprotect to PROT_EXEC on anonymous mappings.
//
// Task:
//   1. mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)
//   2. Copy the provided ret_stub[] shellcode into the mapping.
//   3. mprotect(ptr, 4096, PROT_READ|PROT_EXEC)
//   4. Cast ptr to void(*)(void) and call it - it just executes 'ret'.
//   5. Print "returned from shellcode" to verify execution.
//   6. munmap(ptr, 4096).

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

// Minimal shellcode: just a 'ret' instruction (C3 on x86-64)
// Safe to call - immediately returns to caller.
static const unsigned char ret_stub[] = { 0xC3 };

int main(void) {
    // TODO 1: mmap anonymous RW page
    void *ptr = MAP_FAILED; // replace with mmap call
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    printf("mapped at: %p\n", ptr);

    // TODO 2: copy ret_stub into the mapping
    // memcpy(ptr, ret_stub, sizeof(ret_stub));

    // TODO 3: mprotect to PROT_READ|PROT_EXEC (remove write)
    // if (mprotect(ptr, 4096, PROT_READ | PROT_EXEC) != 0) {
    //     perror("mprotect");
    //     munmap(ptr, 4096);
    //     return 1;
    // }

    // TODO 4: cast to function pointer and call
    // void (*fn)(void) = (void(*)(void))ptr;
    // fn();
    // printf("returned from shellcode\n");

    // TODO 5: munmap(ptr, 4096)
    return 0;
}

// I AM NOT DONE

// CFarer - Malware Development Exercise 08
// TOPIC: API Hashing - resolve functions by hash, not name string
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized security research / red-team education
//
// Storing "VirtualAlloc", "CreateThread" etc. as plaintext strings makes
// static analysis trivial.  API hashing stores only a 32-bit hash of the
// function name; the resolver walks the export table, hashes each name,
// and returns the match.
//
// Common hash: djb2   hash = hash*33 + c   (seed = 5381)
//
// Task:
//   1. Implement djb2(name) - compute the djb2 hash of an ASCII string.
//   2. Implement hash_get_proc(module_base, target_hash) - walk exports
//      and return the function whose djb2 hash equals target_hash.
//   3. Precompute hashes for "VirtualAlloc" and "GetSystemInfo" and verify.

#include <windows.h>
#include <stdio.h>
#include <assert.h>

unsigned int djb2(const char *name) {
    // TODO: seed=5381, for each byte: hash = hash*33 ^ c
    return 0;
}

void *hash_get_proc(HMODULE base, unsigned int target_hash) {
    // TODO: walk export table, hash each name, return VA on match
    return NULL;
}

int main(void) {
    // Precompute the hashes you need - never store the strings in production
    unsigned int hash_va  = djb2("VirtualAlloc");
    unsigned int hash_gsi = djb2("GetSystemInfo");

    printf("djb2(\"VirtualAlloc\")  = 0x%08X\n", hash_va);
    printf("djb2(\"GetSystemInfo\") = 0x%08X\n", hash_gsi);

    HMODULE k32 = GetModuleHandleA("kernel32.dll");

    void *va_our  = hash_get_proc(k32, hash_va);
    void *va_real = (void*)GetProcAddress(k32, "VirtualAlloc");
    printf("hash_get_proc(VirtualAlloc) : %p\n", va_our);
    printf("GetProcAddress(VirtualAlloc): %p\n", va_real);
    assert(va_our != NULL && va_our == va_real);

    void *gsi_our  = hash_get_proc(k32, hash_gsi);
    void *gsi_real = (void*)GetProcAddress(k32, "GetSystemInfo");
    assert(gsi_our != NULL && gsi_our == gsi_real);

    printf("API hashing works!\n");
    return 0;
}

// I AM NOT DONE

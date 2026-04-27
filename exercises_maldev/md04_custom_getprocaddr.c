// CFarer - Malware Development Exercise 04
// TOPIC: Custom GetProcAddress - API resolution without imports
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Authorized security research / red-team education
//
// Malware often resolves API addresses at runtime to avoid leaving
// obvious import table entries for static analysis.
// The technique: walk the export directory manually (as in md03)
// and implement the same logic as GetProcAddress yourself.
//
// Task: Implement my_get_proc_addr(module_base, func_name).
// It must return the same address as GetProcAddress for any named export.
// Do NOT call GetProcAddress or any string-comparison API - use your own
// loop with strcmp or manual comparison.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void *my_get_proc_addr(HMODULE base, const char *func_name) {
    // TODO: walk the export directory to find func_name
    // Return the function's absolute VA, or NULL if not found
    return NULL;
}

int main(void) {
    HMODULE k32 = LoadLibraryA("kernel32.dll");
    assert(k32 != NULL);

    // Verify our resolver matches the real one
    void *real  = (void *)GetProcAddress(k32, "VirtualAlloc");
    void *ours  = my_get_proc_addr(k32, "VirtualAlloc");
    printf("GetProcAddress : %p\n", real);
    printf("my_get_proc_addr: %p\n", ours);
    assert(real != NULL && real == ours);

    real = (void *)GetProcAddress(k32, "CreateFileA");
    ours = my_get_proc_addr(k32, "CreateFileA");
    assert(real == ours);

    assert(my_get_proc_addr(k32, "DoesNotExist_xyz") == NULL);

    printf("Custom GetProcAddress works!\n");
    FreeLibrary(k32);
    return 0;
}

// I AM NOT DONE

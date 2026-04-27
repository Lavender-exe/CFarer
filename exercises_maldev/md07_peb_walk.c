// CFarer - Malware Development Exercise 07
// TOPIC: PEB Walk - resolving kernel32 without LoadLibrary/GetProcAddress
// DIFFICULTY: Advanced  PLATFORM: Windows x64
// PURPOSE: Authorized security research / red-team education
//
// The Process Environment Block (PEB) is always at gs:[0x60] on x64.
// PEB.Ldr -> PEB_LDR_DATA -> InMemoryOrderModuleList
// Each LIST_ENTRY points to an LDR_DATA_TABLE_ENTRY containing:
//   BaseDllName (UNICODE_STRING)
//   DllBase     (loaded module base)
//
// Malware uses this to find kernel32 / ntdll without calling any imports,
// avoiding obvious LoadLibrary calls in the import table.
//
// Task: Implement peb_get_module(name_w) that walks the PEB module list
// and returns the base address of the module with that wide-char name.

#include <windows.h>
#include <winternl.h>  // PPEB, PEB_LDR_DATA, LDR_DATA_TABLE_ENTRY
#include <stdio.h>
#include <wchar.h>

// Returns base address of module with BaseDllName == name_w (case-insensitive)
// or NULL if not found.
HMODULE peb_get_module(const wchar_t *name_w) {
#ifdef _WIN64
    // TODO:
    // 1. Read PEB from gs:[0x60]
    //    PPEB peb = (PPEB)__readgsqword(0x60);
    // 2. Get peb->Ldr->InMemoryOrderModuleList
    // 3. Walk the doubly-linked list comparing BaseDllName
    // 4. Return DllBase of the matching entry
#endif
    return NULL;
}

int main(void) {
    HMODULE k32_peb  = peb_get_module(L"KERNEL32.DLL");
    HMODULE k32_real = GetModuleHandleA("kernel32.dll");

    printf("PEB walk result :  %p\n", (void*)k32_peb);
    printf("GetModuleHandle:   %p\n", (void*)k32_real);

    if (k32_peb && k32_peb == k32_real)
        printf("Match! PEB walk successful.\n");
    else
        printf("Mismatch - check your walk.\n");

    return (k32_peb == k32_real) ? 0 : 1;
}

// I AM NOT DONE

// CFarer - Malware Development Exercise 03
// TOPIC: PE Export Directory - resolving exported function names
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Authorized security research / red-team education
//
// The Export Directory (data directory index 0) maps function names to RVAs.
// Structure:
//   IMAGE_EXPORT_DIRECTORY
//     NumberOfNames        count of named exports
//     AddressOfNames       RVA -> array of RVAs pointing to name strings
//     AddressOfFunctions   RVA -> array of function RVAs
//     AddressOfNameOrdinals RVA -> array of ordinal indices
//
// Name lookup: for name index i,
//   name    = base + AddressOfNames[i]
//   ordinal = AddressOfNameOrdinals[i]
//   fn_rva  = AddressOfFunctions[ordinal]
//   fn_va   = base + fn_rva
//
// Task: Load kernel32.dll and walk its export table.
// Print the first 20 exported function names and their absolute addresses.

#include <windows.h>
#include <stdio.h>
#include <assert.h>

int main(void) {
    HMODULE base = LoadLibraryA("kernel32.dll");
    if (!base) { fprintf(stderr, "LoadLibrary failed\n"); return 1; }

    PIMAGE_DOS_HEADER dos  = (PIMAGE_DOS_HEADER)base;
    PIMAGE_NT_HEADERS nt   = (PIMAGE_NT_HEADERS)((BYTE*)base + dos->e_lfanew);

    // TODO: get the export directory from the data directory
    // Index: IMAGE_DIRECTORY_ENTRY_EXPORT (== 0)
    DWORD export_rva = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    PIMAGE_EXPORT_DIRECTORY exp = NULL;  // TODO: compute VA from base + export_rva

    // TODO: resolve the three address arrays
    DWORD  *names    = NULL;
    WORD   *ordinals = NULL;
    DWORD  *funcs    = NULL;
    assert(exp != NULL && names && ordinals && funcs);  // gate

    // TODO: loop min(20, exp->NumberOfNames) times, print name and address

    FreeLibrary(base);
    return 0;
}

// I AM NOT DONE

// CFarer - Malware Development Exercise 01
// TOPIC: PE File Format - DOS and NT Headers
// DIFFICULTY: Beginner  PLATFORM: Windows
// PURPOSE: Authorized security research / red-team education
//
// Every Windows executable is a Portable Executable (PE).
// Structure (in order on disk):
//   IMAGE_DOS_HEADER    (starts with MZ magic: 0x5A4D)
//     .e_lfanew         -> offset to IMAGE_NT_HEADERS
//   IMAGE_NT_HEADERS
//     Signature         (PE\0\0 = 0x00004550)
//     IMAGE_FILE_HEADER
//     IMAGE_OPTIONAL_HEADER
//       AddressOfEntryPoint  (RVA of first instruction)
//       ImageBase            (preferred load address)
//       NumberOfRvaAndSizes  (how many data directories)
//
// Task: Parse the PE headers of the running process.
//   1. Get the module base address with GetModuleHandleA(NULL)
//   2. Cast to IMAGE_DOS_HEADER* and verify MZ magic
//   3. Walk e_lfanew to IMAGE_NT_HEADERS and verify PE signature
//   4. Print: ImageBase, AddressOfEntryPoint, NumberOfSections

#include <windows.h>
#include <stdio.h>
#include <assert.h>

int main(void) {
    // TODO: get base address of this process's PE image
    HMODULE base = NULL;   // replace with GetModuleHandleA(NULL)
    assert(base != NULL);  // gate: fails until you resolve the base

    // TODO: cast to PIMAGE_DOS_HEADER and check Magic == IMAGE_DOS_SIGNATURE
    PIMAGE_DOS_HEADER dos = NULL;

    // TODO: walk e_lfanew to get PIMAGE_NT_HEADERS
    PIMAGE_NT_HEADERS nt  = NULL;
    assert(nt != NULL && nt->Signature == IMAGE_NT_SIGNATURE);

    // TODO: print the three fields listed above

    return 0;
}

// I AM NOT DONE

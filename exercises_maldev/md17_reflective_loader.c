// CFarer - Maldev Exercise 17
// TOPIC: Reflective Loader - Manual PE Mapping (foundations)
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// Reflective DLL loading maps a PE image into memory manually, without using
// LoadLibrary.  The DLL is already in memory (e.g., downloaded over network)
// and contains a ReflectiveLoader export that performs its own relocation.
//
// Manual PE mapping steps:
//   1. Allocate memory at the PE's preferred base (or any address if relocs present)
//   2. Copy headers
//   3. Map each section to its VirtualAddress
//   4. Apply base relocations (IMAGE_BASE_RELOCATION)
//   5. Resolve imports (IMAGE_IMPORT_DESCRIPTOR)
//   6. Call entry point (DllMain or exported function)
//
// THIS EXERCISE: Implement steps 1-3 - allocate + copy headers + map sections.
//   Use the CURRENT PROCESS's own ntdll.dll image in memory as the "DLL to remap".
//   Read it from disk (as in md13), then map it manually into a new allocation.
//   DO NOT run the re-mapped copy - just verify section VAs look correct.

#include <windows.h>
#include <stdio.h>

int main(void) {
    // Step 1: Get ntdll from disk (same as md13)
    char path[MAX_PATH];
    GetSystemDirectoryA(path, MAX_PATH);
    strcat_s(path, MAX_PATH, "\\ntdll.dll");

    HANDLE hFile    = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ,
                                  NULL, OPEN_EXISTING, 0, NULL);
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    BYTE  *disk_img = (BYTE*)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (!disk_img) { fprintf(stderr, "map failed\n"); return 1; }

    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)disk_img;
    PIMAGE_NT_HEADERS nt  = (PIMAGE_NT_HEADERS)(disk_img + dos->e_lfanew);
    SIZE_T image_size     = nt->OptionalHeader.SizeOfImage;
    SIZE_T headers_size   = nt->OptionalHeader.SizeOfHeaders;

    printf("SizeOfImage:   0x%llx\n", (ULONGLONG)image_size);
    printf("SizeOfHeaders: 0x%llx\n", (ULONGLONG)headers_size);
    printf("Sections:      %u\n",     nt->FileHeader.NumberOfSections);

    // TODO 1: VirtualAlloc(NULL, image_size, MEM_COMMIT|MEM_RESERVE,
    //           PAGE_EXECUTE_READWRITE) -> new_base
    BYTE *new_base = NULL;
    if (!new_base) { fprintf(stderr, "VirtualAlloc failed\n"); return 1; }
    printf("New base: %p\n", (void*)new_base);

    // TODO 2: memcpy(new_base, disk_img, headers_size)  - copy PE headers
    // memcpy(new_base, disk_img, headers_size);

    // TODO 3: Map sections - for each section, copy raw data to VirtualAddress
    PIMAGE_SECTION_HEADER sec = IMAGE_FIRST_SECTION(nt);
    for (WORD i = 0; i < nt->FileHeader.NumberOfSections; i++) {
        printf("  %-8.8s  RVA=0x%08lX  raw=0x%08lX  vsize=0x%08lX\n",
               sec[i].Name,
               sec[i].VirtualAddress,
               sec[i].PointerToRawData,
               sec[i].Misc.VirtualSize);

        // TODO: if PointerToRawData != 0:
        //   memcpy(new_base + sec[i].VirtualAddress,
        //          disk_img + sec[i].PointerToRawData,
        //          sec[i].SizeOfRawData)
    }

    // TODO 4: verify first 4 bytes at new_base match DOS magic (MZ)
    // printf("MZ check: %c%c\n", new_base[0], new_base[1]);

    // Cleanup - do NOT execute new_base
    VirtualFree(new_base, 0, MEM_RELEASE);
    UnmapViewOfFile(disk_img);
    CloseHandle(hMapping);
    CloseHandle(hFile);
    printf("Manual mapping complete (no execution)\n");
    return 0;
}

// I AM NOT DONE

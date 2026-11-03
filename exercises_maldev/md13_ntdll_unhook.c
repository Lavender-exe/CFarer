// CFarer - Malware Development Exercise 13
// TOPIC: NTDLL Unhooking - restore hooked syscall stubs
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// EDR/AV products hook ntdll.dll syscall stubs in the .text section to inspect
// every syscall before it enters the kernel.  Unhooking restores the original
// bytes by mapping a fresh copy of ntdll.dll from disk and copying the clean
// .text section over the in-memory (hooked) version.
//
// Steps:
//   1. Get the in-memory ntdll base: GetModuleHandleA("ntdll.dll")
//   2. Get the on-disk path: GetSystemDirectoryA + "\\ntdll.dll"
//   3. CreateFileA + CreateFileMapping + MapViewOfFile (disk copy)
//   4. Parse both copies' PE headers to locate the .text section RVA+size
//   5. VirtualProtect the in-memory .text to PAGE_EXECUTE_READWRITE
//   6. memcpy from disk .text -> in-memory .text
//   7. VirtualProtect restore original protection
//   8. UnmapViewOfFile, CloseHandle
//
// Task:
//   Complete steps 1-4 (read & compare first 16 bytes of .text from both copies).
//   Print whether any byte differs (indicating a hook is present).
//   Steps 5-7 are optional bonus - implement with caution on live systems.

#include <windows.h>
#include <stdio.h>

static PIMAGE_SECTION_HEADER find_section(PVOID base, const char *name) {
    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)base;
    PIMAGE_NT_HEADERS nt  = (PIMAGE_NT_HEADERS)((BYTE*)base + dos->e_lfanew);
    PIMAGE_SECTION_HEADER sec = IMAGE_FIRST_SECTION(nt);
    WORD nsec = nt->FileHeader.NumberOfSections;
    for (WORD i = 0; i < nsec; i++) {
        if (strncmp((char*)sec[i].Name, name, 8) == 0)
            return &sec[i];
    }
    return NULL;
}

int main(void) {
    // TODO 1: get in-memory ntdll base
    //   HMODULE mem_ntdll = GetModuleHandleA("ntdll.dll");
    HMODULE mem_ntdll = NULL; // replace

    // TODO 2: build disk path and open+map disk ntdll
    char path[MAX_PATH];
    GetSystemDirectoryA(path, MAX_PATH);
    strcat_s(path, MAX_PATH, "\\ntdll.dll");
    printf("ntdll path: %s\n", path);

    //   HANDLE hFile    = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,
    //                                 OPEN_EXISTING, 0, NULL);
    //   HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    //   PVOID  disk_ntdll = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    HANDLE hFile    = INVALID_HANDLE_VALUE; // replace
    HANDLE hMapping = NULL;                 // replace
    PVOID  disk_ntdll = NULL;               // replace

    if (!mem_ntdll || !disk_ntdll) {
        fprintf(stderr, "failed to get ntdll copies\n");
        return 1;
    }

    // TODO 3: find .text section in both copies using find_section()
    PIMAGE_SECTION_HEADER mem_text  = NULL; // find_section(mem_ntdll, ".text")
    PIMAGE_SECTION_HEADER disk_text = NULL; // find_section(disk_ntdll, ".text")

    if (!mem_text || !disk_text) {
        fprintf(stderr, ".text section not found\n");
        return 1;
    }
    printf(".text RVA: 0x%lX  size: 0x%lX\n",
           mem_text->VirtualAddress, mem_text->Misc.VirtualSize);

    // TODO 4: compare first 16 bytes of .text from both copies
    BYTE *mem_bytes  = (BYTE*)mem_ntdll  + mem_text->VirtualAddress;
    BYTE *disk_bytes = (BYTE*)disk_ntdll + disk_text->PointerToRawData;

    int hooked = 0;
    printf("mem  .text[0..15]: ");
    for (int i = 0; i < 16; i++) { printf("%02X ", mem_bytes[i]);  }
    printf("\ndisk .text[0..15]: ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", disk_bytes[i]);
        if (disk_bytes[i] != mem_bytes[i]) hooked = 1;
    }
    printf("\nHooks detected: %s\n", hooked ? "YES" : "NO (clean)");

    // BONUS TODO: VirtualProtect + memcpy to unhook
    // (implement only if you understand the risk on a live system)

    if (disk_ntdll) UnmapViewOfFile(disk_ntdll);
    if (hMapping)   CloseHandle(hMapping);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
    return 0;
}

// I AM NOT DONE

// CFarer - Malware Development Exercise 02
// TOPIC: PE Sections - walking IMAGE_SECTION_HEADER
// DIFFICULTY: Beginner  PLATFORM: Windows
// PURPOSE: Authorized security research / red-team education
//
// After IMAGE_NT_HEADERS, PE sections are laid out sequentially.
// Each section has an IMAGE_SECTION_HEADER (40 bytes):
//   Name[8]             ASCII name (.text, .data, .rdata, …)
//   VirtualAddress      RVA where section is loaded
//   SizeOfRawData       size on disk
//   Characteristics     flags (IMAGE_SCN_MEM_EXECUTE, _READ, _WRITE)
//
// Macro to get the first section header:
//   IMAGE_FIRST_SECTION(nt_headers)
//
// Task: Print all sections of the running process:
//   Name | VirtualAddress | SizeOfRawData | Characteristics (hex)

#include <windows.h>
#include <stdio.h>

int main(void) {
    HMODULE            base = GetModuleHandleA(NULL);
    PIMAGE_DOS_HEADER  dos  = (PIMAGE_DOS_HEADER)base;
    PIMAGE_NT_HEADERS  nt   = (PIMAGE_NT_HEADERS)((BYTE*)base + dos->e_lfanew);

    WORD num_sections = nt->FileHeader.NumberOfSections;

    // TODO: use IMAGE_FIRST_SECTION(nt) to get PIMAGE_SECTION_HEADER
    // TODO: loop over num_sections, printing each section's fields

    return 0;
}

// I AM NOT DONE

// CFarer - Windows Internals Exercise 04
// TOPIC: Windows Registry - read, write, enumerate
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals education / authorized tooling
//
// The registry is a hierarchical database.  Key APIs:
//   RegOpenKeyExA / RegCreateKeyExA   - open or create a key
//   RegSetValueExA                    - write a value
//   RegQueryValueExA                  - read a value
//   RegEnumKeyExA / RegEnumValueA     - enumerate subkeys / values
//   RegDeleteValueA / RegDeleteKeyA   - delete
//   RegCloseKey                       - always close handles
//
// Task:
//   1. Create (or open) HKEY_CURRENT_USER\Software\CFarer\Test
//   2. Write a REG_DWORD value named "Version" = 1
//   3. Write a REG_SZ value named "Author" = "CFarer"
//   4. Read both values back and assert they match
//   5. Clean up: delete both values and the key

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define KEY_PATH "Software\\CFarer\\Test"

int main(void) {
    HKEY hkey = NULL;

    // TODO 1: RegCreateKeyExA to open/create KEY_PATH under HKCU
    // TODO 2: RegSetValueExA - write DWORD "Version" = 1
    // TODO 3: RegSetValueExA - write SZ "Author" = "CFarer"

    // TODO 4: Read back and assert
    DWORD version = 0;
    char  author[64] = {0};
    DWORD type, size;

    // Read DWORD
    size = sizeof(version);
    // TODO: RegQueryValueExA for "Version"
    assert(version == 1);

    // Read string
    size = sizeof(author);
    // TODO: RegQueryValueExA for "Author"
    assert(strcmp(author, "CFarer") == 0);

    printf("Version: %lu\n", version);
    printf("Author:  %s\n",  author);

    // TODO 5: RegDeleteValueA x2, RegDeleteKeyA, RegCloseKey

    printf("Registry operations successful!\n");
    return 0;
}

// I AM NOT DONE

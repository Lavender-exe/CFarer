// CFarer - Red Team Exercise 08
// TOPIC: Registry Persistence - HKCU\Software\Microsoft\Windows\CurrentVersion\Run
// DIFFICULTY: Beginner-Intermediate  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education - persistence
//
// The Run key executes programs at every user login.
// HKCU (current user) requires no admin rights.
// HKLM (local machine) requires admin and persists for all users.
//
// Common persistence locations:
//   HKCU\Software\Microsoft\Windows\CurrentVersion\Run
//   HKLM\Software\Microsoft\Windows\CurrentVersion\Run
//   HKCU\...\RunOnce  (fires once, then deletes itself)
//   HKLM\SYSTEM\CurrentControlSet\Services  (service install - admin)
//
// Task:
//   1. RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
//        0, KEY_SET_VALUE, &hKey)
//   2. RegSetValueExA(hKey, "CFarerTest", 0, REG_SZ, (BYTE*)payload_path, len)
//      Use GetModuleFileNameA(NULL, path, MAX_PATH) for current exe path.
//   3. Verify: RegQueryValueExA reads back the same path.
//   4. Clean up: RegDeleteValueA to remove the key (don't leave test persistence).
//   5. RegCloseKey.

#include <windows.h>
#include <stdio.h>

#define RUN_KEY "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define VALUE_NAME "CFarerTest"

int main(void) {
    char exe_path[MAX_PATH];
    GetModuleFileNameA(NULL, exe_path, MAX_PATH);
    printf("Payload path: %s\n", exe_path);

    HKEY hKey = NULL;
    // TODO 1: RegOpenKeyExA(HKEY_CURRENT_USER, RUN_KEY, 0, KEY_SET_VALUE, &hKey)
    LONG rc = ERROR_FILE_NOT_FOUND; // replace
    if (rc != ERROR_SUCCESS) {
        fprintf(stderr, "RegOpenKeyExA failed: %ld\n", rc);
        return 1;
    }

    // TODO 2: RegSetValueExA(hKey, VALUE_NAME, 0, REG_SZ,
    //           (BYTE*)exe_path, (DWORD)(strlen(exe_path)+1))
    rc = ERROR_CANTWRITE; // replace
    if (rc == ERROR_SUCCESS)
        printf("Persistence key written: HKCU\\%s\\%s\n", RUN_KEY, VALUE_NAME);

    // TODO 3: verify - RegQueryValueExA
    char verify[MAX_PATH] = {0};
    DWORD vlen = sizeof(verify), vtype = 0;
    // RegQueryValueExA(hKey, VALUE_NAME, NULL, &vtype, (BYTE*)verify, &vlen);
    // printf("Verified:  %s\n", verify);

    // TODO 4: cleanup - remove the test value (don't leave test persistence)
    // rc = RegDeleteValueA(hKey, VALUE_NAME);
    // if (rc == ERROR_SUCCESS) printf("(cleanup: run key removed)\n");

    // TODO 5: RegCloseKey(hKey)
    return 0;
}

// I AM NOT DONE

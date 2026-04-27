// CFarer - Windows Internals Exercise 06
// TOPIC: Access Tokens - enable privileges, impersonation
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Windows internals education / authorized tooling
//
// Every process/thread has an access token containing:
//   - SID (who you are)
//   - Privileges (what you're allowed to do)
//   - Integrity level
//
// To perform privileged operations (e.g. SeDebugPrivilege to open any process)
// you must first ENABLE the privilege even if it's in the token:
//
//   OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token)
//   LookupPrivilegeValueA(NULL, "SeDebugPrivilege", &luid)
//   AdjustTokenPrivileges(token, FALSE, &tp, ...)
//
// Task: Implement enable_privilege(priv_name).
// Then enable SeDebugPrivilege and verify by opening SYSTEM process (pid 4).

#include <windows.h>
#include <stdio.h>

// Returns TRUE if privilege was successfully enabled
BOOL enable_privilege(const char *priv_name) {
    HANDLE token;
    // TODO: OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &token)
    // TODO: LookupPrivilegeValueA(NULL, priv_name, &luid)
    // TODO: Fill TOKEN_PRIVILEGES tp: 1 privilege, Attributes=SE_PRIVILEGE_ENABLED
    // TODO: AdjustTokenPrivileges(token, FALSE, &tp, sizeof(tp), NULL, NULL)
    // TODO: Check GetLastError() == ERROR_SUCCESS (not just return value)
    // TODO: CloseHandle(token)
    return FALSE;
}

int main(void) {
    // Without SeDebugPrivilege, OpenProcess on pid 4 fails with ACCESS_DENIED
    HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, 4);
    printf("Before privilege: handle=%p  err=%lu\n", h, GetLastError());
    if (h) CloseHandle(h);

    BOOL ok = enable_privilege("SeDebugPrivilege");
    printf("enable_privilege: %s\n", ok ? "OK" : "FAILED");

    h = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, 4);
    printf("After privilege:  handle=%p  err=%lu\n", h, GetLastError());
    if (h) {
        printf("SeDebugPrivilege enabled - can open SYSTEM process!\n");
        CloseHandle(h);
    }
    return 0;
}

// I AM NOT DONE

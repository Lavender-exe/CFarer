// CFarer - Windows Internals Exercise 01
// TOPIC: Enumerating running processes with Toolhelp32
// DIFFICULTY: Beginner  PLATFORM: Windows
// PURPOSE: Windows internals education / authorized tooling
//
// The Toolhelp32 API lets you snapshot and walk:
//   Processes: CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
//              Process32First / Process32Next
//   Threads:   TH32CS_SNAPTHREAD
//   Modules:   TH32CS_SNAPMODULE
//
// PROCESSENTRY32 key fields:
//   th32ProcessID       PID
//   th32ParentProcessID PPID
//   cntThreads          thread count
//   szExeFile           image name (basename)
//
// Task: Print a table of all running processes:
//   PID  | PPID | Threads | Name

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <assert.h>

int main(void) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Snapshot failed: %lu\n", GetLastError());
        return 1;
    }

    PROCESSENTRY32 pe = { .dwSize = sizeof(pe) };
    int listed = 0;

    printf("%-8s %-8s %-8s %s\n", "PID", "PPID", "Threads", "Name");
    printf("%-8s %-8s %-8s %s\n", "---", "----", "-------", "----");

    // TODO: call Process32First, then loop with Process32Next
    //       printing pe.th32ProcessID, pe.th32ParentProcessID,
    //               pe.cntThreads, pe.szExeFile
    //       and counting each process with listed++

    assert(listed > 0);   // the snapshot must contain at least one process
    printf("%d processes listed\n", listed);
    CloseHandle(snap);
    return 0;
}

// I AM NOT DONE

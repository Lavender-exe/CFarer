// CFarer - Windows Internals Exercise 08
// TOPIC: Direct system calls via ntdll - Nt* / Zw* functions
// DIFFICULTY: Advanced  PLATFORM: Windows x64
// PURPOSE: Windows internals education / authorized tooling
//
// Win32 API (kernel32, advapi32 etc.) is a thin wrapper that eventually
// calls ntdll.dll stubs, which each do:
//   mov r10, rcx
//   mov eax, <syscall number>
//   syscall
//
// You can call ntdll functions directly, bypassing the Win32 layer.
// This is useful for understanding the real NT interface and for
// studying how security products hook Win32 API.
//
// Task: Use NtQuerySystemInformation to get the system uptime.
// Then use NtAllocateVirtualMemory as a direct equivalent to VirtualAlloc.
//
// Link: ntdll.lib is implicit on Windows; forward-declare the prototypes.

#include <windows.h>
#include <winternl.h>  // SYSTEM_INFORMATION_CLASS, etc.
#include <stdio.h>

// ntdll exports - not in SDK headers as function pointers, so load dynamically
typedef NTSTATUS (NTAPI *PFN_NtQuerySystemInformation)(
    SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);

typedef NTSTATUS (NTAPI *PFN_NtAllocateVirtualMemory)(
    HANDLE, PVOID*, ULONG_PTR, PSIZE_T, ULONG, ULONG);

#define NT_SUCCESS(s)  ((NTSTATUS)(s) >= 0)

int main(void) {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");

    // TODO: resolve NtQuerySystemInformation and NtAllocateVirtualMemory
    //       via GetProcAddress
    PFN_NtQuerySystemInformation NtQSI = NULL;
    PFN_NtAllocateVirtualMemory  NtAVM = NULL;

    // TODO: call NtQSI with SystemTimeOfDayInformation (class 3)
    // to get uptime - struct is SYSTEM_TIMEOFDAY_INFORMATION
    // Print BootTime and CurrentTime (LARGE_INTEGER as seconds)

    // TODO: call NtAVM to allocate a 4KB page (MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE)
    // Verify the pointer is non-NULL, write a value, read it back

    printf("Direct ntdll calls complete!\n");
    return 0;
}

// I AM NOT DONE

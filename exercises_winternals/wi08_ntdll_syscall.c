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
#include <assert.h>

// ntdll exports - not in SDK headers as function pointers, so load dynamically
typedef NTSTATUS (NTAPI *PFN_NtQuerySystemInformation)(
    SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);

typedef NTSTATUS (NTAPI *PFN_NtAllocateVirtualMemory)(
    HANDLE, PVOID*, ULONG_PTR, PSIZE_T, ULONG, ULONG);

#ifndef NT_SUCCESS
#define NT_SUCCESS(s)  ((NTSTATUS)(s) >= 0)
#endif

// Filled in by the TODOs below - the end-of-main asserts check them.
static ULONGLONG g_boot_time   = 0;   // BootTime as returned by NtQSI
static PVOID     g_alloc_base  = NULL;

int main(void) {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");

    // TODO: resolve NtQuerySystemInformation and NtAllocateVirtualMemory
    //       via GetProcAddress
    PFN_NtQuerySystemInformation NtQSI = NULL;
    PFN_NtAllocateVirtualMemory  NtAVM = NULL;

    // gate: both pointers must be resolved before anything else runs
    assert(NtQSI != NULL);
    assert(NtAVM != NULL);

    // TODO: call NtQSI with SystemTimeOfDayInformation (class 3)
    // to get uptime - struct is SYSTEM_TIMEOFDAY_INFORMATION
    // Print BootTime and CurrentTime (LARGE_INTEGER as seconds)
    // and store tod.BootTime.QuadPart into g_boot_time

    // TODO: call NtAVM to allocate a 4KB page (MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE)
    // Verify the pointer is non-NULL, write a value, read it back
    // and store the base pointer into g_alloc_base (VirtualFree it after)

    assert(g_boot_time  != 0);      // NtQSI returned a real boot time
    assert(g_alloc_base != NULL);   // NtAVM returned a usable page
    printf("Direct ntdll calls complete!\n");
    return 0;
}

// I AM NOT DONE

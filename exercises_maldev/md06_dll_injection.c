// CFarer - Malware Development Exercise 06
// TOPIC: DLL Injection via LoadLibrary + CreateRemoteThread
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized security research / red-team education
// !! Authorized lab use only !!
//
// Classic LoadLibrary injection:
//   1. OpenProcess()
//   2. VirtualAllocEx()           - RW memory for the DLL path string
//   3. WriteProcessMemory()       - write the path string
//   4. GetProcAddress(kernel32, "LoadLibraryA")
//   5. CreateRemoteThread()       - entry = LoadLibraryA, arg = path VA
//
// The remote thread calls LoadLibraryA(path) inside the target, which maps
// our DLL and runs DllMain(DLL_PROCESS_ATTACH).
//
// Task: Implement inject_dll(pid, dll_path).
// Provide an absolute path to a DLL you compiled for testing.

#include <windows.h>
#include <stdio.h>
#include <string.h>

int inject_dll(DWORD pid, const char *dll_path) {
    SIZE_T path_len = strlen(dll_path) + 1;
    HANDLE proc     = NULL;
    HANDLE thr      = NULL;
    LPVOID remote_path = NULL;
    int ret = 1;

    // TODO 1: OpenProcess PROCESS_ALL_ACCESS
    // TODO 2: VirtualAllocEx PAGE_READWRITE for path_len bytes
    // TODO 3: WriteProcessMemory - copy dll_path into remote_path
    // TODO 4: Resolve LoadLibraryA from kernel32
    // TODO 5: CreateRemoteThread(proc, ..., LoadLibraryA, remote_path, ...)
    // TODO 6: WaitForSingleObject, cleanup, return 0

    return ret;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pid> <C:\\full\\path\\to.dll>\n", argv[0]);
        return 1;
    }
    DWORD pid = (DWORD)atol(argv[1]);
    printf("Injecting '%s' into PID %lu\n", argv[2], (unsigned long)pid);
    return inject_dll(pid, argv[2]);
}

// I AM NOT DONE

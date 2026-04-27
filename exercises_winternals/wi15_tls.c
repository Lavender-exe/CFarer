// CFarer - Windows Internals Exercise 15
// TOPIC: Thread Local Storage (TLS)
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// TLS gives each thread its own copy of a variable.
// Use cases: errno, per-thread allocators, per-thread logging contexts.
//
// Dynamic TLS API:
//   TlsAlloc()                -> DWORD slot index (or TLS_OUT_OF_INDEXES)
//   TlsSetValue(slot, ptr)    -> store void* for current thread
//   TlsGetValue(slot)         -> retrieve void* for current thread
//   TlsFree(slot)             -> release the slot
//
// Each thread gets its OWN value for the same slot index.
// Threads never see each other's values.
//
// Task: Allocate a TLS slot, spawn 4 threads.
// Each thread stores its thread ID as the TLS value, then reads it back
// and verifies it matches GetCurrentThreadId().

#include <windows.h>
#include <stdio.h>
#include <assert.h>

static DWORD g_tls_slot = TLS_OUT_OF_INDEXES;

DWORD WINAPI tls_thread(LPVOID arg) {
    DWORD tid = GetCurrentThreadId();

    // TODO: TlsSetValue(g_tls_slot, (void*)(uintptr_t)tid)

    // Simulate some work
    Sleep(10);

    // TODO: read back with TlsGetValue and verify it equals tid
    DWORD stored = 0;   // = (DWORD)(uintptr_t)TlsGetValue(g_tls_slot)
    assert(stored == tid);

    printf("Thread %lu: TLS value %lu OK\n", tid, stored);
    return 0;
}

int main(void) {
    // TODO: g_tls_slot = TlsAlloc()
    assert(g_tls_slot != TLS_OUT_OF_INDEXES);

    HANDLE threads[4];
    for (int i = 0; i < 4; i++)
        threads[i] = CreateThread(NULL, 0, tls_thread, NULL, 0, NULL);
    WaitForMultipleObjects(4, threads, TRUE, 5000);
    for (int i = 0; i < 4; i++) CloseHandle(threads[i]);

    // TODO: TlsFree(g_tls_slot)
    printf("TLS exercise complete!\n");
    return 0;
}

// I AM NOT DONE

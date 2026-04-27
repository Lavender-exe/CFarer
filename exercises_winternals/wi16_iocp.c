// CFarer - Windows Internals Exercise 16
// TOPIC: I/O Completion Ports (IOCP) - scalable async I/O
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// IOCP is the Windows mechanism behind every high-performance server
// (nginx-on-windows, IIS, SQL Server, .NET ThreadPool, libuv, etc.).
//
// Model:
//   1. CreateIoCompletionPort() - create the port
//   2. CreateIoCompletionPort() again - associate a file/socket handle with it
//   3. Post overlapped I/O operations (ReadFile, WriteFile, WSARecv, ...)
//   4. Worker threads call GetQueuedCompletionStatus() - block until an I/O
//      completes, then process the result
//
// You can also manually post work items (no real I/O) with
//   PostQueuedCompletionStatus(port, bytes, key, overlapped)
// This is how thread pools push tasks to idle workers.
//
// Task: Use PostQueuedCompletionStatus to send 8 "tasks" to 4 worker threads.
// Workers sum all received 'bytes' values and print them.
// Post a sentinel (key=0xDEAD) to signal each worker to exit.

#include <windows.h>
#include <stdio.h>
#include <assert.h>

#define NUM_WORKERS  4
#define NUM_TASKS    8
#define SENTINEL_KEY ((ULONG_PTR)0xDEAD)

static volatile LONG g_total = 0;

DWORD WINAPI worker(LPVOID arg) {
    HANDLE port = (HANDLE)arg;
    while (1) {
        DWORD      bytes = 0;
        ULONG_PTR  key   = 0;
        OVERLAPPED *ov   = NULL;

        // TODO: GetQueuedCompletionStatus(port, &bytes, &key, &ov, INFINITE)
        // If key == SENTINEL_KEY: break
        // Otherwise: InterlockedAdd(&g_total, bytes)
    }
    return 0;
}

int main(void) {
    // TODO: CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, NUM_WORKERS)
    HANDLE port = NULL;
    assert(port);

    // Start workers
    HANDLE threads[NUM_WORKERS];
    for (int i = 0; i < NUM_WORKERS; i++)
        threads[i] = CreateThread(NULL, 0, worker, port, 0, NULL);

    // Post 8 tasks with values 1..8
    for (int i = 1; i <= NUM_TASKS; i++) {
        // TODO: PostQueuedCompletionStatus(port, i, 1 /*key=task*/, NULL)
    }

    // Post one sentinel per worker
    for (int i = 0; i < NUM_WORKERS; i++) {
        // TODO: PostQueuedCompletionStatus(port, 0, SENTINEL_KEY, NULL)
    }

    WaitForMultipleObjects(NUM_WORKERS, threads, TRUE, 5000);
    for (int i = 0; i < NUM_WORKERS; i++) CloseHandle(threads[i]);
    CloseHandle(port);

    // 1+2+3+4+5+6+7+8 = 36
    printf("Total = %ld (expected 36)\n", g_total);
    assert(g_total == 36);
    printf("IOCP exercise complete!\n");
    return 0;
}

// I AM NOT DONE

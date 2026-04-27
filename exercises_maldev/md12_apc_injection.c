// CFarer - Maldev Exercise 12
// TOPIC: APC Injection - QueueUserAPC to alertable thread
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// APC (Asynchronous Procedure Call) injection queues a callback to execute
// inside a target thread the next time that thread enters an ALERTABLE wait
// (SleepEx, WaitForSingleObjectEx, etc.).
//
// Unlike CreateRemoteThread, APC injection does not spawn a new thread -
// it hijacks an existing alertable thread, which is harder to detect.
//
// Steps for self-injection (no remote process needed for this exercise):
//   1. Allocate RWX memory in own process (VirtualAlloc).
//   2. Copy shellcode stub into it.
//   3. OpenThread(THREAD_SET_CONTEXT, FALSE, GetCurrentThreadId())
//      - or use a worker thread.
//   4. QueueUserAPC((PAPCFUNC)shellcode_addr, hThread, 0)
//   5. SleepEx(INFINITE, TRUE) - alertable wait triggers the APC.
//
// THIS EXERCISE: Use a benign APC callback (prints a message) instead of
// shellcode.  Focus on the mechanics of QueueUserAPC + alertable wait.
//
//   1. Write an apc_callback function that sets a global flag and prints.
//   2. OpenThread to get a handle to the current thread.
//   3. QueueUserAPC the callback.
//   4. SleepEx(100, TRUE) - enters alertable wait, drains APC queue.
//   5. Assert the global flag was set.

#include <windows.h>
#include <stdio.h>
#include <assert.h>

static volatile LONG g_apc_fired = 0;

VOID WINAPI apc_callback(ULONG_PTR param) {
    (void)param;
    InterlockedExchange(&g_apc_fired, 1);
    printf("APC callback fired in thread %lu\n", GetCurrentThreadId());
}

int main(void) {
    printf("Main thread ID: %lu\n", GetCurrentThreadId());

    // TODO 1: OpenThread(THREAD_SET_CONTEXT, FALSE, GetCurrentThreadId())
    HANDLE hThread = NULL; // replace with OpenThread call
    if (!hThread) {
        fprintf(stderr, "OpenThread failed: %lu\n", GetLastError());
        return 1;
    }

    // TODO 2: QueueUserAPC((PAPCFUNC)apc_callback, hThread, 0)
    DWORD queued = 0; // replace: queued = QueueUserAPC(...)
    if (!queued) {
        fprintf(stderr, "QueueUserAPC failed: %lu\n", GetLastError());
        CloseHandle(hThread);
        return 1;
    }
    printf("APC queued\n");

    // TODO 3: SleepEx(100, TRUE) - alertable wait drains APC queue
    //   DWORD r = SleepEx(100, TRUE);
    //   WAIT_IO_COMPLETION (0xC0) means an APC was delivered
    DWORD r = 0; // replace with SleepEx call
    printf("SleepEx returned: 0x%lX (%s)\n", r,
           r == WAIT_IO_COMPLETION ? "WAIT_IO_COMPLETION" : "other");

    // TODO 4: assert(g_apc_fired == 1)
    printf("g_apc_fired: %ld\n", g_apc_fired);

    CloseHandle(hThread);
    return (g_apc_fired == 1) ? 0 : 1;
}

// I AM NOT DONE

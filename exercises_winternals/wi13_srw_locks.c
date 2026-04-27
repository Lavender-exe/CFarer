// CFarer - Windows Internals Exercise 13
// TOPIC: Slim Reader/Writer Locks + Condition Variables
// DIFFICULTY: Intermediate  PLATFORM: Windows (Vista+)
// PURPOSE: Windows internals / systems programming
//
// SRWLOCK is lighter than a CRITICAL_SECTION or Mutex:
//   - Fits in a single pointer-sized value (no kernel object)
//   - Supports concurrent readers OR one exclusive writer
//   - Cannot be acquired recursively
//
//   SRWLOCK lk = SRWLOCK_INIT;
//   AcquireSRWLockShared(&lk)    / ReleaseSRWLockShared(&lk)
//   AcquireSRWLockExclusive(&lk) / ReleaseSRWLockExclusive(&lk)
//
// CONDITION_VARIABLE works with SRWLOCK:
//   SleepConditionVariableSRW(&cv, &lk, INFINITE, flags)
//   WakeConditionVariable(&cv)
//   WakeAllConditionVariable(&cv)
//
// Task: Implement a thread-safe counter using SRWLOCK.
// 4 reader threads repeatedly read the counter.
// 2 writer threads increment it 1000 times each.
// Final value must equal 2000.

#include <windows.h>
#include <stdio.h>
#include <assert.h>

static SRWLOCK         g_lock  = SRWLOCK_INIT;
static CONDITION_VARIABLE g_cv = CONDITION_VARIABLE_INIT;
static volatile long   g_counter = 0;
static volatile int    g_done    = 0;

DWORD WINAPI writer(LPVOID arg) {
    for (int i = 0; i < 1000; i++) {
        // TODO: AcquireSRWLockExclusive, increment g_counter,
        //       WakeAllConditionVariable, ReleaseSRWLockExclusive
    }
    return 0;
}

DWORD WINAPI reader(LPVOID arg) {
    long last = -1;
    while (!g_done) {
        // TODO: AcquireSRWLockShared, read g_counter, ReleaseSRWLockShared
        // print if value changed
        (void)last;
    }
    return 0;
}

int main(void) {
    HANDLE threads[6];
    // 2 writers
    threads[0] = CreateThread(NULL, 0, writer, NULL, 0, NULL);
    threads[1] = CreateThread(NULL, 0, writer, NULL, 0, NULL);
    // 4 readers
    for (int i = 2; i < 6; i++)
        threads[i] = CreateThread(NULL, 0, reader, NULL, 0, NULL);

    // Wait for writers
    WaitForMultipleObjects(2, threads, TRUE, 5000);
    g_done = 1;
    WaitForMultipleObjects(4, threads + 2, TRUE, 2000);

    for (int i = 0; i < 6; i++) CloseHandle(threads[i]);

    printf("Final counter: %ld\n", g_counter);
    assert(g_counter == 2000);
    printf("SRWLOCK concurrent counter works!\n");
    return 0;
}

// I AM NOT DONE

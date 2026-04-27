// CFarer - Windows Internals Exercise 07
// TOPIC: Kernel Objects - handles, reference counting, inheritance
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals education / authorized tooling
//
// Every kernel object (process, thread, file, mutex, event…) is managed
// by the Object Manager.  Handles are per-process indices into a table.
//
// Key rules:
//   - EVERY handle opened must be closed (CloseHandle / specific close fn)
//   - Handles can be duplicated across processes with DuplicateHandle()
//   - GetHandleInformation() reveals HANDLE_FLAG_INHERIT / PROTECT_FROM_CLOSE
//
// Task: Create a mutex and an event, then:
//   1. Print their handle values
//   2. Check and print their HandleFlags
//   3. Set HANDLE_FLAG_INHERIT on the mutex
//   4. Verify the flag was set
//   5. Duplicate the event handle to the current process (same process)
//   6. Signal the event and wait on the duplicate to confirm they alias
//   7. Close all handles

#include <windows.h>
#include <stdio.h>
#include <assert.h>

int main(void) {
    // TODO 1: CreateMutexA(NULL, FALSE, "CFarerMutex")
    HANDLE mtx = NULL;

    // TODO 2: CreateEventA(NULL, TRUE, FALSE, "CFarerEvent") - manual reset
    HANDLE evt = NULL;

    assert(mtx && evt);
    printf("Mutex handle:  %p\n", mtx);
    printf("Event handle:  %p\n", evt);

    // TODO 3: GetHandleInformation on each, print flags
    DWORD flags;
    // GetHandleInformation(mtx, &flags); printf("Mutex flags: 0x%lX\n", flags);

    // TODO 4: SetHandleInformation - set HANDLE_FLAG_INHERIT on mutex
    // TODO 5: Verify with GetHandleInformation

    // TODO 6: DuplicateHandle - duplicate evt into evt_dup
    HANDLE evt_dup = NULL;
    // DuplicateHandle(GetCurrentProcess(), evt,
    //                 GetCurrentProcess(), &evt_dup,
    //                 0, FALSE, DUPLICATE_SAME_ACCESS);

    // TODO 7: SetEvent(evt), then WaitForSingleObject(evt_dup, 100) == WAIT_OBJECT_0
    // Both handles alias the same object - signaling one affects the other

    // TODO 8: CloseHandle all three handles
    printf("Handle object exercises complete!\n");
    return 0;
}

// I AM NOT DONE

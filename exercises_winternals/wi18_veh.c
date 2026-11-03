// CFarer - Windows Internals Exercise 18
// TOPIC: Vectored Exception Handling (VEH) - lazy page allocation
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// VEH is called BEFORE SEH frame unwinding.
// A VEH handler is a process-wide callback registered with:
//   AddVectoredExceptionHandler(first, handler)
//     first=1: called before other VEH handlers
//     first=0: called after  other VEH handlers
//   Returns OPAQUE handle - pass to RemoveVectoredExceptionHandler()
//
// Handler signature:
//   LONG WINAPI handler(EXCEPTION_POINTERS *ep)
//   Returns: EXCEPTION_CONTINUE_EXECUTION  - fix it, retry the instruction
//            EXCEPTION_CONTINUE_SEARCH     - pass to next handler / SEH
//
// ExceptionRecord fields used here:
//   ExceptionCode == EXCEPTION_ACCESS_VIOLATION (0xC0000005)
//   ExceptionInformation[0]: 0 = read, 1 = write
//   ExceptionInformation[1]: the virtual address that was touched
//
// Use cases:
//   - Debug instrumentation (log every exception)
//   - Hardware breakpoint emulation (EXCEPTION_SINGLE_STEP)
//   - Software-based guard pages and LAZY ALLOCATION (this exercise)
//   - Anti-debug tricks (detect STATUS_BREAKPOINT = debugger attached)
//
// Task: implement a lazy allocator, the trick real allocators and emulators
// use:
//   1. Register a VEH that intercepts EXCEPTION_ACCESS_VIOLATION writes to
//      LAZY_ADDR. It should VirtualAlloc a committed RW page at that address,
//      set g_veh_fired = 1, and return EXCEPTION_CONTINUE_EXECUTION so the
//      faulting write retries.
//   2. Trigger the exception by writing through the LAZY_ADDR pointer.
//   3. Verify execution continued past the write and the value round-trips.
//
// If your handler is wrong the write stays unhandled and the process
// crashes - that crash IS the lesson about what an unhandled AV means.

#include <windows.h>
#include <stdio.h>
#include <assert.h>

#define LAZY_ADDR ((int *)0x20000000u)   // 512 MB - normally unmapped

static volatile int g_veh_fired = 0;

LONG WINAPI lazy_alloc_handler(EXCEPTION_POINTERS *ep) {
    if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION &&
        ep->ExceptionRecord->ExceptionInformation[0] == 1 &&           // write
        ep->ExceptionRecord->ExceptionInformation[1] == (ULONG_PTR)LAZY_ADDR) {
        // TODO 1: VirtualAlloc a single page at LAZY_ADDR:
        //         VirtualAlloc(LAZY_ADDR, 4096, MEM_COMMIT | MEM_RESERVE,
        //                      PAGE_READWRITE)
        // TODO 2: on success set g_veh_fired = 1 and return
        //         EXCEPTION_CONTINUE_EXECUTION (the write retries)
        return EXCEPTION_CONTINUE_SEARCH;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

int main(void) {
    // TODO 3: AddVectoredExceptionHandler(1, lazy_alloc_handler) -> save handle
    PVOID handler = NULL;

    // gate: without a registered VEH the write below would crash the process.
    assert(handler != NULL);

    // Trigger the access violation: LAZY_ADDR is not committed yet.
    *LAZY_ADDR = 42;

    printf("g_veh_fired: %d\n", g_veh_fired);
    printf("value read back: %d\n", *LAZY_ADDR);

    // TODO 4: RemoveVectoredExceptionHandler(handler)

    assert(g_veh_fired == 1);        // the handler fixed the fault
    assert(*LAZY_ADDR == 42);        // write retried and persisted
    printf("VEH lazy allocation worked - execution continued past the fault!\n");
    return 0;
}

// I AM NOT DONE

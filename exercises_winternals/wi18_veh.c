// CFarer - Windows Internals Exercise 18
// TOPIC: Vectored Exception Handling (VEH) + Vectored Continue Handlers
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
//   Returns: EXCEPTION_CONTINUE_EXECUTION  - fix it, retry instruction
//            EXCEPTION_CONTINUE_SEARCH     - pass to next handler / SEH
//
// Use cases:
//   - Debug instrumentation (log every exception)
//   - Hardware breakpoint emulation (EXCEPTION_SINGLE_STEP)
//   - Software-based guard pages
//   - Anti-debug tricks (detect STATUS_BREAKPOINT = debugger attached)
//
// Task:
//   1. Register a VEH that intercepts EXCEPTION_INT_DIVIDE_BY_ZERO.
//      It should fix the divisor to 1 and return CONTINUE_EXECUTION
//      so the instruction retries with divisor=1 (result = dividend).
//   2. Trigger the exception by actually dividing by zero.
//   3. Verify execution continued past the divide and result == dividend.

#include <windows.h>
#include <stdio.h>
#include <assert.h>

static volatile int g_veh_fired = 0;

LONG WINAPI div_zero_handler(EXCEPTION_POINTERS *ep) {
    if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO) {
        g_veh_fired = 1;
        // TODO: fix the divisor register so the instruction retries cleanly.
        // On x64 the quotient register is RAX, divisor is usually RCX or RDX.
        // The safest approach: set EDX:EAX = 0/1 by setting the context so
        // the divide produces 0 and continue.
        //
        // Hint: ep->ContextRecord->Rcx = 1;  (if divisor was in RCX)
        // OR:   advance RIP past the faulting instruction manually.
        //
        // For this exercise: set ep->ContextRecord->Rcx = 1 and return CONTINUE.
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

int main(void) {
    // TODO: AddVectoredExceptionHandler(1, div_zero_handler) -> save handle
    PVOID handler = NULL;

    // Trigger divide by zero using inline asm or volatile arithmetic.
    // We use a helper to prevent the compiler from optimising it away.
    volatile int divisor = 0;
    volatile int result  = 0;
    __try {
        result = 10 / divisor;
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        // If VEH handled it, we never get here.
        // If VEH did NOT handle it, SEH catches it here.
        printf("SEH caught it (VEH did not fix)\n");
    }

    printf("g_veh_fired: %d\n", g_veh_fired);
    printf("result: %d\n",      result);

    // TODO: RemoveVectoredExceptionHandler(handler)

    if (g_veh_fired)
        printf("VEH intercepted and continued execution!\n");
    return 0;
}

// I AM NOT DONE

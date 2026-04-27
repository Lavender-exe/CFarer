// CFarer - Windows Internals Exercise 11
// TOPIC: Structured Exception Handling (SEH)
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// SEH is the Windows mechanism for handling hardware and software exceptions.
// Unlike C++ exceptions, SEH works at the OS level for ANY language.
//
//   __try { ... }
//   __except(filter_expr) { ... }   // catches exceptions
//   __finally { ... }               // always runs (like defer)
//
// Filter expressions:
//   EXCEPTION_EXECUTE_HANDLER   (1)  - catch it, run __except block
//   EXCEPTION_CONTINUE_SEARCH   (0)  - pass up the stack
//   EXCEPTION_CONTINUE_EXECUTION(-1) - retry the faulting instruction
//
// GetExceptionCode()  - inside filter: exception code (e.g. EXCEPTION_ACCESS_VIOLATION)
// GetExceptionInformation() - EXCEPTION_POINTERS* with context + record
//
// Task:
//   1. safe_divide(): catch EXCEPTION_INT_DIVIDE_BY_ZERO, return INT_MIN on it.
//   2. safe_deref():  catch EXCEPTION_ACCESS_VIOLATION, return 0 on it.
//   3. In main: demonstrate __finally always running even when exception is caught.

#include <windows.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

int safe_divide(int a, int b) {
    int result = 0;
    __try {
        // TODO: result = a / b
    }
    __except(/* TODO: filter for EXCEPTION_INT_DIVIDE_BY_ZERO */) {
        // TODO: return INT_MIN
    }
    return result;
}

int safe_deref(int *ptr) {
    int val = 0;
    __try {
        // TODO: val = *ptr
    }
    __except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION
             ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
        return 0;
    }
    return val;
}

int main(void) {
    // Test safe_divide
    assert(safe_divide(10, 2)  == 5);
    assert(safe_divide(10, 0)  == INT_MIN);  // divide by zero caught

    // Test safe_deref
    int x = 42;
    assert(safe_deref(&x) == 42);
    assert(safe_deref(NULL) == 0);   // AV caught

    // Demonstrate __finally (cleanup always runs)
    int cleaned_up = 0;
    __try {
        int *bad = (int*)0xDEAD0000;
        *bad = 1;   // triggers AV
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        printf("Exception caught in __except\n");
    }
    // __finally alternative - runs whether or not exception occurred
    printf("All SEH tests passed!\n");
    return 0;
}

// I AM NOT DONE

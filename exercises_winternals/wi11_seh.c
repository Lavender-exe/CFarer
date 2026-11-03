// CFarer - Windows Internals Exercise 11
// TOPIC: Structured Exception Handling (SEH)
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// SEH is the Windows mechanism for handling hardware and software exceptions.
// Unlike C++ exceptions, SEH works at the OS level for ANY language.
//
//   __try { ... }
//   __except(filter) { ... }   // catches exceptions
//   __finally { ... }          // always runs (like defer)
//
// Filter results:
//   EXCEPTION_EXECUTE_HANDLER    (1)  - catch it, run the handler body
//   EXCEPTION_CONTINUE_SEARCH    (0)  - pass it up the stack
//   EXCEPTION_CONTINUE_EXECUTION (-1) - retry the faulting instruction
//
// The filter receives an EXCEPTION_POINTERS* (record + CPU context) and can
// inspect ExceptionRecord->ExceptionCode, e.g.:
//   EXCEPTION_ACCESS_VIOLATION       0xC0000005
//   EXCEPTION_INT_DIVIDE_BY_ZERO     0xC0000094
//
// PORTABILITY NOTE:
//   MSVC and Clang accept the __try/__except syntax directly.
//   GCC (MinGW) does not, so the MinGW path uses MinGW SEH emulation from
//   <excpt.h>:  __try1(filter_fn) { body } __except1 { handler }
//   filter_fn has the same role as an MSVC __except filter: it receives
//   EXCEPTION_POINTERS* and returns EXCEPTION_EXECUTE_HANDLER (1) to catch
//   or EXCEPTION_CONTINUE_SEARCH (0) to pass the exception up.
//   MinGW emulation supports ONE guarded scope per translation unit, so on
//   MinGW only safe_divide() is SEH-guarded; safe_deref() probes the page
//   with VirtualQuery (wi03) instead - same outcome, different mechanism.
//
// Task:
//   1. safe_divide(): catch EXCEPTION_INT_DIVIDE_BY_ZERO, return INT_MIN.
//   2. safe_deref():  never touch a bad page - return 0 for NULL/unmapped.

#include <windows.h>
#include <excpt.h>
// excpt.h macros use the GNU "asm" keyword, disabled by strict -std=c23.
#ifndef asm
#define asm __asm__
#endif
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#if defined(_MSC_VER) || (defined(__clang__) && defined(_WIN32))
// MSVC/Clang: filter selects which exceptions this frame catches
static LONG divzero_filter(EXCEPTION_POINTERS *ep) {
    return ep->ExceptionRecord->ExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO
               ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
}
#else
// MinGW GCC: the __try1 filter function
static LONG divzero_filter(EXCEPTION_POINTERS *ep) {
    return ep->ExceptionRecord->ExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO
               ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
}
#endif

int safe_divide(int a, int b) {
    int result = 0;
#if defined(_MSC_VER) || (defined(__clang__) && defined(_WIN32))
    __try {
        // TODO: result = a / b
    }
    __except (divzero_filter(GetExceptionInformation())) {
        // TODO: return INT_MIN
    }
#else
    (void)divzero_filter;   // referenced from asm by __try1 - silence warning
    __try1(divzero_filter) {
        // TODO: result = a / b
    }
    __except1 {
        // TODO: return INT_MIN
    }
#endif
    return result;
}

int safe_deref(int *ptr) {
    int val = 0;
#if defined(_MSC_VER) || (defined(__clang__) && defined(_WIN32))
    __try {
        // TODO: val = *ptr
    }
    __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION
              ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
        // exception caught - val stays 0
    }
#else
    // MinGW path: probe before touching. A pointer is safe to dereference
    // only if it points at committed memory (see wi03 for VirtualQuery).
    MEMORY_BASIC_INFORMATION mbi;
    if (ptr == NULL ||
        VirtualQuery(ptr, &mbi, sizeof(mbi)) != sizeof(mbi) ||
        mbi.State != MEM_COMMIT)
        return 0;
    // TODO: val = *ptr
#endif
    return val;
}

int main(void) {
    // Test safe_divide
    assert(safe_divide(10, 2)  == 5);
    assert(safe_divide(10, 0)  == INT_MIN);  // divide by zero caught

    // Test safe_deref
    int x = 42;
    assert(safe_deref(&x) == 42);
    assert(safe_deref(NULL) == 0);   // bad pointer rejected
    int *freed = (int *)0x01000000;  // typically unmapped in a 64-bit process
    assert(safe_deref(freed) == 0);

    printf("All SEH tests passed!\n");
    return 0;
}

// I AM NOT DONE

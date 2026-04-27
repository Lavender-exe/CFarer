// CFarer - Linux Internals Exercise 04
// TOPIC: sigaction - structured signal handling with ucontext
// DIFFICULTY: Intermediate  PLATFORM: Linux
// PURPOSE: Linux internals / systems programming
//
// sigaction() is the POSIX way to install signal handlers.
// Unlike signal(), it provides SA_SIGINFO which passes:
//   siginfo_t  *si   - signal source info (si_code, si_addr, si_pid, ...)
//   void       *uc   - ucontext_t - CPU register state at point of fault
//
// This is how debuggers and sanitizers intercept faults (SIGSEGV, SIGFPE, etc.)
// and recover or report them with full context.
//
// Task:
//   1. Install a SIGFPE handler using sigaction with SA_SIGINFO.
//   2. In the handler:
//      a. Print si->si_code (FPE_INTDIV = 1 for integer divide by zero).
//      b. Cast uc to ucontext_t*, print uc->uc_mcontext.gregs[REG_RIP].
//      c. Advance RIP past the faulting instruction by += 2 (idiv is 2 bytes).
//         (This is architecture-specific and fragile - for educational purposes.)
//   3. Trigger integer divide-by-zero: volatile int r = 1 / 0;
//   4. Print "survived SIGFPE" - verify execution continued.
//
// NOTE: Advancing RIP is fragile. VEH (Windows) and libsigsegv are cleaner
//       for production use. This exercise is strictly educational.

#include <stdio.h>
#include <signal.h>
#include <ucontext.h>
#include <string.h>

static volatile int g_caught = 0;

void fpe_handler(int sig, siginfo_t *si, void *uc_void) {
    (void)sig;
    ucontext_t *uc = (ucontext_t *)uc_void;
    g_caught = 1;
    printf("SIGFPE caught: si_code=%d (FPE_INTDIV=1)\n", si->si_code);
    printf("RIP at fault:  0x%llx\n",
           (unsigned long long)uc->uc_mcontext.gregs[REG_RIP]);

    // TODO: advance RIP past the faulting 'idiv' instruction (2 bytes on x86-64)
    // uc->uc_mcontext.gregs[REG_RIP] += 2;
}

int main(void) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = fpe_handler;

    // TODO 1: set SA_SIGINFO flag so handler receives siginfo_t + ucontext
    //   sa.sa_flags = SA_SIGINFO;
    //   sigaction(SIGFPE, &sa, NULL);

    // TODO 2: trigger integer divide-by-zero
    volatile int divisor = 0;
    volatile int result  = 0;
    // result = 1 / divisor;  // uncomment after installing handler

    printf("g_caught: %d\n", g_caught);
    if (g_caught)
        printf("survived SIGFPE\n");
    return 0;
}

// I AM NOT DONE

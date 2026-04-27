// CFarer - Linux Internals Exercise 02
// TOPIC: ptrace - attach to child, read registers
// DIFFICULTY: Intermediate  PLATFORM: Linux
// PURPOSE: Linux internals / debugger internals
//
// ptrace() is the syscall underlying all Linux debuggers (GDB, strace, ltrace).
// A tracer process can:
//   - Start a tracee with PTRACE_TRACEME
//   - Attach to a running process with PTRACE_ATTACH
//   - Read/write registers (PTRACE_GETREGS / PTRACE_SETREGS)
//   - Read/write memory (PTRACE_PEEKDATA / PTRACE_POKEDATA)
//   - Single-step (PTRACE_SINGLESTEP)
//   - Intercept syscalls (PTRACE_SYSCALL)
//
// Task:
//   1. fork() - create child process.
//   2. In child: ptrace(PTRACE_TRACEME, 0, NULL, NULL) then raise(SIGSTOP).
//   3. In parent: waitpid(child, &status, 0) to wait for child stop.
//   4. ptrace(PTRACE_GETREGS, child, NULL, &regs) - read registers.
//   5. Print child's RIP (instruction pointer) and RSP (stack pointer).
//   6. ptrace(PTRACE_CONT, child, NULL, NULL) - let child continue.
//   7. waitpid again for child to exit.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>   // struct user_regs_struct

int main(void) {
    pid_t child;

    // TODO 1: child = fork()
    child = -1; // replace with fork()
    if (child < 0) {
        perror("fork");
        return 1;
    }

    if (child == 0) {
        // Child process
        // TODO 2: ptrace(PTRACE_TRACEME, 0, NULL, NULL)
        //         raise(SIGSTOP)  - pause, let parent inspect
        printf("child: PID %d - waiting for tracer\n", getpid());
        // After PTRACE_CONT from parent, child exits normally
        return 0;
    }

    // Parent (tracer) process
    int status = 0;
    // TODO 3: waitpid(child, &status, 0)
    printf("parent: child PID %d stopped\n", child);

    struct user_regs_struct regs = {0};
    // TODO 4: ptrace(PTRACE_GETREGS, child, NULL, &regs)
    printf("child RIP: 0x%llx\n", (unsigned long long)regs.rip);
    printf("child RSP: 0x%llx\n", (unsigned long long)regs.rsp);

    // TODO 5: ptrace(PTRACE_CONT, child, NULL, NULL)
    // TODO 6: waitpid(child, &status, 0)  - wait for child to exit
    printf("child exited with status %d\n", WEXITSTATUS(status));
    return 0;
}

// I AM NOT DONE

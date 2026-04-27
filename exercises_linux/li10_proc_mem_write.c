// CFarer - Linux Internals Exercise 10
// TOPIC: /proc/pid/mem - ptrace-less process memory write
// DIFFICULTY: Advanced  PLATFORM: Linux
// PURPOSE: Linux internals / memory manipulation
//
// /proc/<pid>/mem is a file representing the full virtual address space of
// a process.  Seeking to an address and writing modifies that process's memory
// - without ptrace, without shared memory, without injecting a thread.
//
// Requirements:
//   - Caller must have ptrace permission over target (same UID or CAP_SYS_PTRACE)
//   - Since Linux 3.12 you must ALSO ptrace(PTRACE_ATTACH) first, or have
//     /proc/sys/kernel/yama/ptrace_scope = 0
//   - Writing to read-only mappings fails (EFAULT / EIO)
//
// Task:
//   1. Fork a child. Child: sets global g_val=0, then loops printing g_val every
//      100ms until g_val != 0, then prints the new value and exits.
//   2. Parent:
//      a. ptrace(PTRACE_ATTACH, child, NULL, NULL) + waitpid
//      b. Build path "/proc/<pid>/mem"
//      c. open(path, O_RDWR)
//      d. lseek64(fd, (off64_t)(uintptr_t)&child_g_val_addr, SEEK_SET)
//         NOTE: parent must pass the child's &g_val address via a pipe or
//         shared mapping - see approach below using pipe.
//      e. write(fd, &new_val, sizeof(new_val)) - patch child's g_val to 42
//      f. ptrace(PTRACE_DETACH, child, NULL, NULL)
//      g. waitpid for child.
//
// This exercise uses a pipe to pass &g_val from child to parent.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>

volatile int g_val = 0;

int main(void) {
    int pipefd[2];
    if (pipe(pipefd) < 0) { perror("pipe"); return 1; }

    pid_t child = fork();
    if (child < 0) { perror("fork"); return 1; }

    if (child == 0) {
        // Child: send &g_val to parent, then loop until g_val changes
        close(pipefd[0]);
        uintptr_t addr = (uintptr_t)&g_val;
        write(pipefd[1], &addr, sizeof(addr));
        close(pipefd[1]);

        int iters = 0;
        while (g_val == 0 && iters < 50) {
            usleep(100000); // 100ms
            iters++;
        }
        printf("child g_val = %d\n", g_val);
        return (g_val == 42) ? 0 : 1;
    }

    // Parent
    close(pipefd[1]);
    uintptr_t child_addr = 0;
    // TODO 1: read child's &g_val address from pipe
    // read(pipefd[0], &child_addr, sizeof(child_addr));
    close(pipefd[0]);
    printf("parent: child &g_val = 0x%lx\n", child_addr);

    // TODO 2: ptrace(PTRACE_ATTACH, child, NULL, NULL)
    //         waitpid(child, NULL, 0)

    // TODO 3: build /proc/<pid>/mem path and open O_RDWR
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/mem", child);
    int fd = -1; // replace: fd = open(path, O_RDWR)
    if (fd < 0) {
        perror("open /proc/pid/mem");
        kill(child, SIGKILL);
        return 1;
    }

    // TODO 4: lseek64 to child_addr and write 42
    int new_val = 42;
    // lseek64(fd, (off64_t)child_addr, SEEK_SET);
    // write(fd, &new_val, sizeof(new_val));
    (void)new_val;
    printf("parent: wrote 42 to child g_val\n");

    // TODO 5: ptrace(PTRACE_DETACH, child, NULL, NULL)
    // TODO 6: waitpid
    close(fd);
    int status = 0;
    waitpid(child, &status, 0);
    printf("child exited: %d\n", WEXITSTATUS(status));
    return 0;
}

// I AM NOT DONE

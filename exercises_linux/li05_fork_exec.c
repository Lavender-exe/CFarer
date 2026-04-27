// CFarer - Linux Internals Exercise 05
// TOPIC: fork / execve / waitpid - process creation
// DIFFICULTY: Beginner-Intermediate  PLATFORM: Linux
// PURPOSE: Linux internals / systems programming
//
// Every process on Linux is created by fork() + exec():
//   fork()    - clone the current process (copy-on-write)
//   execve()  - replace the process image with a new program
//   waitpid() - parent waits for child to exit, collects exit status
//
// This is how shells work: fork → child calls exec("/bin/ls") → parent waits.
//
// Task:
//   1. fork() - create child.
//   2. Child: execve("/bin/ls", {"/bin/ls", "-la", "/tmp", NULL}, envp=NULL)
//      Use execvp() to search PATH: execvp("ls", args).
//   3. Parent: waitpid(child, &status, 0).
//   4. Parent: check WIFEXITED(status) and print WEXITSTATUS(status).
//   5. Handle fork() == -1 (error) and child execvp() failure.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t child;

    // TODO 1: child = fork()
    child = -1; // replace

    if (child < 0) {
        perror("fork");
        return 1;
    }

    if (child == 0) {
        // Child process
        // TODO 2: execvp("ls", args) - replace child image with /bin/ls -la /tmp
        char *args[] = { "ls", "-la", "/tmp", NULL };
        // execvp(args[0], args);
        // If execvp returns, it failed:
        perror("execvp");
        _exit(127);
    }

    // Parent process
    int status = 0;
    // TODO 3: waitpid(child, &status, 0)
    printf("child PID %d\n", child);

    // TODO 4: check exit status
    // if (WIFEXITED(status))
    //     printf("child exited: %d\n", WEXITSTATUS(status));
    // else if (WIFSIGNALED(status))
    //     printf("child killed by signal %d\n", WTERMSIG(status));

    return 0;
}

// I AM NOT DONE

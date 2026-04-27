// CFarer - Linux Internals Exercise 08
// TOPIC: seccomp BPF - syscall sandboxing
// DIFFICULTY: Advanced  PLATFORM: Linux
// PURPOSE: Linux internals / sandboxing / security
//
// seccomp (secure computing mode) restricts which syscalls a process can make.
// BPF (Berkeley Packet Filter) programs define the filter policy.
// Used by: Chrome renderer, Docker, systemd, OpenSSH, browsers, containers.
//
// Two modes:
//   SECCOMP_SET_MODE_STRICT - only read/write/exit/_exit allowed
//   SECCOMP_SET_MODE_FILTER - BPF program decides per-syscall
//
// BPF filter for seccomp:
//   struct sock_filter code[] = {
//     BPF_STMT(BPF_LD|BPF_W|BPF_ABS, offsetof(struct seccomp_data, nr)), // load syscall nr
//     BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, __NR_write, 0, 1),  // if write -> allow
//     BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_KILL),            // else kill
//     BPF_STMT(BPF_RET|BPF_K, SECCOMP_RET_ALLOW),           // allow
//   };
//
// Task:
//   1. Install a BPF filter that allows: write, exit, exit_group, brk.
//      Kill process on any other syscall.
//   2. Call write(1, "sandbox OK\n", 11) - must succeed.
//   3. Attempt getpid() AFTER the filter - process should be killed (SIGSYS).
//   4. Print "after seccomp" BEFORE step 3 to show the filter is active.
//
// Compile: gcc -std=c11 -Wall -o li08 li08_seccomp_bpf.c
// Requires: Linux kernel >= 3.5, no special privileges needed.

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <linux/seccomp.h>
#include <linux/filter.h>
#include <linux/audit.h>
#include <linux/unistd.h>

static void install_filter(void) {
    struct sock_filter filter[] = {
        // Load syscall number
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
                 (offsetof(struct seccomp_data, nr))),
        // Allow: write
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_write,      0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
        // Allow: exit
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_exit,       0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
        // Allow: exit_group
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_exit_group, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
        // Allow: brk (needed by libc allocator)
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_brk,        0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
        // Default: kill
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
    };
    struct sock_fprog prog = {
        .len    = (unsigned short)(sizeof(filter) / sizeof(filter[0])),
        .filter = filter,
    };

    // TODO 1: prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)
    //   Required before installing a seccomp filter without CAP_SYS_ADMIN
    // prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);

    // TODO 2: syscall(__NR_seccomp, SECCOMP_SET_MODE_FILTER, 0, &prog)
    //   or: prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog)
    // syscall(__NR_seccomp, SECCOMP_SET_MODE_FILTER, 0, &prog);
}

int main(void) {
    printf("before seccomp\n");

    // TODO 3: call install_filter() to activate the sandbox
    // install_filter();

    write(1, "sandbox OK\n", 11);
    printf("after seccomp (write worked)\n");

    // TODO 4: uncomment to test kill - this should terminate the process with SIGSYS
    // pid_t p = getpid();  // getpid is not in the allow list
    // printf("getpid: %d (should never print)\n", p);

    return 0;
}

// I AM NOT DONE

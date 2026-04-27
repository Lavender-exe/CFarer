// CFarer - Linux Internals Exercise 01
// TOPIC: /proc Filesystem - parsing /proc/self/maps
// DIFFICULTY: Beginner  PLATFORM: Linux
// PURPOSE: Linux internals / systems programming
//
// The /proc virtual filesystem exposes kernel data structures as files.
// /proc/self/maps lists every virtual memory region of the current process:
//   address           perms offset  dev   inode      pathname
//   7f1a2b3c4000-...  r-xp  000000  08:01 12345      /lib/x86_64-linux-gnu/libc.so.6
//
// Fields:
//   perms: r=read, w=write, x=execute, p=private (CoW), s=shared
//
// Task:
//   1. fopen("/proc/self/maps", "r")
//   2. Read line by line with fgets.
//   3. Count total mappings.
//   4. Count and print executable (x) mappings.
//   5. Print the first mapping that contains "libc" or "[stack]".

#include <stdio.h>
#include <string.h>

int main(void) {
    // TODO 1: fopen("/proc/self/maps", "r") -> FILE *f
    FILE *f = NULL; // replace with fopen call
    if (!f) {
        perror("fopen /proc/self/maps");
        return 1;
    }

    char line[512];
    int total = 0;
    int exec_count = 0;

    while (fgets(line, sizeof(line), f)) {
        total++;

        // TODO 2: check if perms field (column 2) contains 'x'
        // The format is: "addr-addr perms ..." - perms starts after first space
        // Find the space, then check if the 3rd char of perms == 'x'
        char *perms = strchr(line, ' ');
        if (perms) {
            perms++; // skip the space
            // TODO: if perms[2] == 'x', increment exec_count
        }

        // TODO 3: print line if it contains "libc" or "[stack]"
        // if (strstr(line, "libc") || strstr(line, "[stack]"))
        //     printf("Notable: %s", line);
    }

    // TODO 4: fclose(f)
    printf("Total mappings:      %d\n", total);
    printf("Executable mappings: %d\n", exec_count);
    return 0;
}

// I AM NOT DONE

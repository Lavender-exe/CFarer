// CFarer - Linux Internals Exercise 07
// TOPIC: POSIX Shared Memory - shm_open + mmap IPC
// DIFFICULTY: Intermediate  PLATFORM: Linux
// PURPOSE: Linux internals / IPC
//
// POSIX shared memory lets two processes share a memory region without
// copying data through the kernel (unlike pipes/sockets).
//
// Pattern:
//   Producer:
//     shm_open("/myshm", O_CREAT|O_RDWR, 0600)
//     ftruncate(fd, size)
//     mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)
//     write data -> msync / munmap / shm_unlink
//
//   Consumer (separate process):
//     shm_open("/myshm", O_RDONLY, 0)
//     mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0)
//     read data -> munmap / close
//
// Task (single process, both roles):
//   1. shm_open("/cfarer_shm", O_CREAT|O_RDWR, 0600) - create/open shm object.
//   2. ftruncate(fd, 64) - set size to 64 bytes.
//   3. mmap RW shared.
//   4. snprintf(ptr, 64, "shared: %d", 42) - write to shared region.
//   5. Print the contents of ptr (same mapping - simulates reader).
//   6. munmap, close, shm_unlink("/cfarer_shm").
//
// Compile: gcc -std=c11 -Wall -o li07 li07_shm_posix.c -lrt

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define SHM_NAME "/cfarer_shm"
#define SHM_SIZE 64

int main(void) {
    // TODO 1: shm_open(SHM_NAME, O_CREAT|O_RDWR, 0600)
    int fd = -1; // replace with shm_open call
    if (fd < 0) {
        perror("shm_open");
        return 1;
    }

    // TODO 2: ftruncate(fd, SHM_SIZE)
    // ftruncate(fd, SHM_SIZE);

    // TODO 3: mmap(NULL, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)
    void *ptr = MAP_FAILED; // replace with mmap call
    if (ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        shm_unlink(SHM_NAME);
        return 1;
    }

    // TODO 4: write to shared region
    // snprintf((char*)ptr, SHM_SIZE, "shared: %d", 42);

    // TODO 5: read back and print
    printf("shm contents: %s\n", (char*)ptr);

    // TODO 6: cleanup
    // munmap(ptr, SHM_SIZE);
    // close(fd);
    // shm_unlink(SHM_NAME);
    return 0;
}

// I AM NOT DONE

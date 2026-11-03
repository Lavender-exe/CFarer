// CFarer - Windows Internals Exercise 10
// TOPIC: Named Shared Memory - IPC via CreateFileMapping(INVALID_HANDLE_VALUE)
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// Passing INVALID_HANDLE_VALUE to CreateFileMapping creates an anonymous
// section backed by the pagefile - NOT a file on disk.
// Give it a name and other processes can open it with OpenFileMapping().
//
// This is a clean, kernel-managed IPC mechanism with no network socket overhead.
// Used by: browsers (renderer↔browser process), game engines, IPC frameworks.
//
// Task: This single program spawns a "writer" thread and a "reader" thread
// that communicate through a named shared memory region called "CFarerShm".
//
//   Writer: maps the region, writes a magic value + message
//   Reader: maps the same region, waits for magic, reads message

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SHM_NAME  "CFarerShm"
#define SHM_SIZE  256
#define MAGIC     0xCAFEBABE

static volatile LONG g_reader_ok = 0;   // set to 1 when reader got the message

typedef struct {
    volatile LONG magic;
    char          message[240];
} ShmBlock;

DWORD WINAPI writer_thread(LPVOID arg) {
    // TODO: CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
    //                          0, SHM_SIZE, SHM_NAME)
    // TODO: MapViewOfFile -> ShmBlock*
    // TODO: write message, then set block->magic = MAGIC (atomic: use InterlockedExchange)
    // TODO: Sleep(500) to let reader consume, then UnmapViewOfFile + CloseHandle
    return 0;
}

DWORD WINAPI reader_thread(LPVOID arg) {
    Sleep(50);  // let writer create the mapping first
    // TODO: OpenFileMapping(FILE_MAP_READ, FALSE, SHM_NAME)
    // TODO: MapViewOfFile -> const ShmBlock*
    // TODO: spin-wait for block->magic == MAGIC (use InterlockedCompareExchange or volatile read)
    // TODO: printf the message
    // TODO: on success: InterlockedExchange(&g_reader_ok, 1)
    // TODO: UnmapViewOfFile + CloseHandle
    return 0;
}

int main(void) {
    HANDLE wt = CreateThread(NULL, 0, writer_thread, NULL, 0, NULL);
    HANDLE rt = CreateThread(NULL, 0, reader_thread, NULL, 0, NULL);
    HANDLE th[2] = {wt, rt};
    DWORD wr = WaitForMultipleObjects(2, th, TRUE, 5000);
    CloseHandle(wt); CloseHandle(rt);

    assert(wr == WAIT_OBJECT_0);      // both threads finished in time
    assert(g_reader_ok == 1);         // reader actually received the message
    printf("Shared memory IPC complete!\n");
    return 0;
}

// I AM NOT DONE

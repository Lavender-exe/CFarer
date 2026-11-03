// CFarer - Windows Internals Exercise 09
// TOPIC: Memory-Mapped Files - CreateFileMapping / MapViewOfFile
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// Memory-mapped files let you treat a file (or anonymous mapping) as if it
// were an array in memory.  The OS handles paging transparently.
// Used for: large file I/O, shared memory between processes, PE loading.
//
// Key APIs:
//   CreateFileMapping(file, NULL, protect, sizeHi, sizeLo, name)
//     -> HANDLE (mapping object)
//   MapViewOfFile(mapping, access, offsetHi, offsetLo, size)
//     -> void* (pointer into mapped region)
//   UnmapViewOfFile(ptr)
//   CloseHandle(mapping)
//
// Task:
//   1. Create a temp file and write "Hello from file\n" to it.
//   2. Open it read-only and map it into memory with CreateFileMapping.
//   3. Read the content through the pointer (no fread needed).
//   4. Unmap and close everything.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void) {
    const char *path    = "mmap_test.txt";
    const char *payload = "Hello from file\n";

    // TODO 0: create the payload file yourself:
    //   fopen(path, "w"), fputs(payload, f), fclose(f)

    // TODO 1: OpenFile for reading
    HANDLE hfile = INVALID_HANDLE_VALUE;   // CreateFileA(path, GENERIC_READ, FILE_SHARE_READ,
                                           //   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)
    assert(hfile != INVALID_HANDLE_VALUE); // gate: fails until TODO 0 + 1 are done

    // TODO 2: CreateFileMapping(hfile, NULL, PAGE_READONLY, 0, 0, NULL)
    HANDLE hmap = NULL;
    assert(hmap != NULL);

    // TODO 3: MapViewOfFile(hmap, FILE_MAP_READ, 0, 0, 0)
    const char *view = NULL;

    // gate: the mapped view must contain the payload
    assert(view != NULL && strncmp(view, "Hello", 5) == 0);
    printf("%s", view);

    // TODO 5: UnmapViewOfFile(view), CloseHandle(hmap), CloseHandle(hfile)

    remove(path);
    printf("Memory-mapped file read successfully!\n");
    return 0;
}

// I AM NOT DONE

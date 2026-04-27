// CFarer - Windows Internals Exercise 12
// TOPIC: Windows Heap API - HeapCreate / HeapAlloc / HeapWalk
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// Every process has a default heap (GetProcessHeap()).
// You can also create private heaps - isolated from the default heap,
// useful for:
//   - Arena allocators (destroy entire heap at once = O(1) free-all)
//   - Heap separation (corruption in one heap doesn't affect others)
//   - Custom alignment or grow limits
//
// Key APIs:
//   HeapCreate(flags, initialSize, maxSize)  -> HANDLE  (0=no limit)
//   HeapAlloc(heap, flags, size)             -> void*
//   HeapReAlloc(heap, flags, ptr, newSize)   -> void*
//   HeapFree(heap, flags, ptr)               -> BOOL
//   HeapDestroy(heap)                        -> destroy entire heap
//   HeapWalk(heap, &entry)                   -> enumerate heap blocks
//
// Task:
//   1. Create a private heap (max 1MB).
//   2. Allocate 3 blocks, write to them, verify reads.
//   3. Free one block, realloc another.
//   4. Walk the heap and count allocated blocks.
//   5. HeapDestroy (frees everything at once).

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void) {
    // TODO 1: HeapCreate(HEAP_NO_SERIALIZE, 4096, 1024*1024)
    HANDLE heap = NULL;
    assert(heap != NULL);

    // TODO 2: allocate three int blocks with HeapAlloc(heap, HEAP_ZERO_MEMORY, sizeof(int))
    int *a = NULL, *b = NULL, *c = NULL;
    *a = 10; *b = 20; *c = 30;
    assert(*a + *b + *c == 60);

    // TODO 3: HeapFree(heap, 0, b)
    //         b = HeapReAlloc(heap, HEAP_ZERO_MEMORY, a, sizeof(int) * 4)
    //         b[1] = 99;  assert(b[1] == 99)

    // TODO 4: Walk the heap and print block count
    PROCESS_HEAP_ENTRY entry = {0};
    int alloc_count = 0;
    // while (HeapWalk(heap, &entry)) {
    //     if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) alloc_count++;
    // }
    printf("Allocated blocks on private heap: %d\n", alloc_count);

    // TODO 5: HeapDestroy(heap) - frees all blocks in one call
    printf("Private heap operations complete!\n");
    return 0;
}

// I AM NOT DONE

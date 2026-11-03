// CFarer - Windows Internals Exercise 03
// TOPIC: Virtual Memory - VirtualQuery, page state, protection flags
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals education / authorized tooling
//
// Every process has a virtual address space.  VirtualQuery() walks it
// region by region, returning MEMORY_BASIC_INFORMATION:
//
//   BaseAddress       start of this region
//   RegionSize        size in bytes
//   State             MEM_COMMIT | MEM_RESERVE | MEM_FREE
//   Type              MEM_IMAGE | MEM_MAPPED | MEM_PRIVATE
//   Protect           PAGE_EXECUTE_READ | PAGE_READWRITE | PAGE_NOACCESS | ...
//
// Task: Walk the full virtual address space of the current process.
// Count and print:
//   - Total committed bytes
//   - Number of executable regions (Protect & PAGE_EXECUTE*)
//   - Number of RWX regions (read + write + execute - a red flag)

#include <windows.h>
#include <stdio.h>
#include <assert.h>

// Returns nonzero if protect flags include execute permission
static int is_exec(DWORD prot) {
    return prot & (PAGE_EXECUTE | PAGE_EXECUTE_READ |
                   PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
}

// Returns nonzero if region is RWX
static int is_rwx(DWORD prot) {
    return (prot & (PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
}

int main(void) {
    MEMORY_BASIC_INFORMATION mbi;
    BYTE *addr = NULL;

    SIZE_T total_committed = 0;
    int    exec_regions    = 0;
    int    rwx_regions     = 0;

    // TODO: loop calling VirtualQuery(addr, &mbi, sizeof(mbi))
    //   while return value > 0, advance addr += mbi.RegionSize
    //   accumulate totals

    // Every process commits memory, so an unimplemented loop fails here.
    assert(total_committed > 0);
    printf("Total committed : %zu bytes (%.1f MB)\n",
           total_committed, (double)total_committed / (1024*1024));
    printf("Executable regions: %d\n", exec_regions);
    printf("RWX regions (suspicious): %d\n", rwx_regions);
    return 0;
}

// I AM NOT DONE

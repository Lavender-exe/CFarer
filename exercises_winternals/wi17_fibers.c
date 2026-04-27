// CFarer - Windows Internals Exercise 17
// TOPIC: Fibers - cooperative multitasking within a thread
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// A Fiber is a manually-switched execution context (coroutine equivalent).
// Unlike threads, the OS never preempts a fiber - YOU decide when to switch.
// Used by: SQL Server, game engines (coroutine schedulers), scripting runtimes.
//
// Key APIs:
//   ConvertThreadToFiber(data) - turn current thread into a fiber, returns handle
//   CreateFiber(stackSize, fn, data) - create a new fiber (not yet running)
//   SwitchToFiber(handle)      - suspend current fiber, resume target fiber
//   GetFiberData()             - retrieve the void* data pointer of current fiber
//   DeleteFiber(handle)        - free fiber resources
//   ConvertFiberToThread()     - undo ConvertThreadToFiber
//
// Task: Implement a simple round-robin fiber scheduler.
// Create 3 worker fibers that each print their ID 3 times,
// yielding control back to the scheduler between prints.
// The scheduler fiber dispatches them in order.

#include <windows.h>
#include <stdio.h>

#define NUM_FIBERS 3
#define ITERATIONS 3

static LPVOID g_scheduler_fiber = NULL;
static LPVOID g_fibers[NUM_FIBERS];
static int    g_done[NUM_FIBERS];

typedef struct { int id; } FiberCtx;

VOID WINAPI fiber_fn(LPVOID arg) {
    FiberCtx *ctx = (FiberCtx *)arg;
    for (int i = 0; i < ITERATIONS; i++) {
        printf("Fiber %d - iteration %d\n", ctx->id, i);
        // TODO: SwitchToFiber(g_scheduler_fiber) to yield
    }
    g_done[ctx->id] = 1;
    // TODO: SwitchToFiber(g_scheduler_fiber) - back to scheduler when done
}

int main(void) {
    // TODO: ConvertThreadToFiber(NULL) - make main thread a fiber
    g_scheduler_fiber = NULL;

    FiberCtx ctxs[NUM_FIBERS];
    for (int i = 0; i < NUM_FIBERS; i++) {
        ctxs[i].id  = i;
        g_done[i]   = 0;
        // TODO: CreateFiber(0, fiber_fn, &ctxs[i])
        g_fibers[i] = NULL;
    }

    // Scheduler: round-robin until all fibers done
    int remaining = NUM_FIBERS;
    while (remaining > 0) {
        for (int i = 0; i < NUM_FIBERS; i++) {
            if (!g_done[i]) {
                // TODO: SwitchToFiber(g_fibers[i])
                if (g_done[i]) remaining--;
            }
        }
    }

    for (int i = 0; i < NUM_FIBERS; i++) DeleteFiber(g_fibers[i]);
    ConvertFiberToThread();
    printf("All fibers completed!\n");
    return 0;
}

// I AM NOT DONE

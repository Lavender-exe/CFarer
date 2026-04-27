// CFarer - Windows Internals Exercise 14
// TOPIC: Job Objects - process sandboxing and resource limits
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Windows internals / systems programming
//
// A Job object is a kernel object that groups processes.
// Once a process is in a job, limits apply to the whole group:
//   - CPU time limits
//   - Memory limits
//   - Max process count
//   - UI restrictions (can block desktop access)
//   - Network access (can block socket creation)
//
// When the job's kill-on-close flag is set and all handles close,
// all member processes are terminated - automatic cleanup.
//
// Key APIs:
//   CreateJobObjectA(NULL, name)
//   AssignProcessToJobObject(job, process)
//   SetInformationJobObject(job, class, info, size)
//   QueryInformationJobObject(job, class, buf, size, NULL)
//   IsProcessInJob(proc, job, &result)
//
// Task:
//   1. Create an anonymous job object.
//   2. Assign the current process to it.
//   3. Set a limit: max 4 active processes.
//   4. Set JOBOBJECT_BASIC_UI_RESTRICTIONS (UIRestrictions = 0) - no UI block.
//   5. Query the job's basic accounting info and print active process count.
//   6. Verify IsProcessInJob returns TRUE.

#include <windows.h>
#include <stdio.h>
#include <assert.h>

int main(void) {
    // TODO 1: CreateJobObjectA(NULL, NULL)
    HANDLE job = NULL;
    assert(job);

    // TODO 2: AssignProcessToJobObject(job, GetCurrentProcess())

    // TODO 3: set JOBOBJECT_BASIC_LIMIT_INFORMATION
    //   .LimitFlags = JOB_OBJECT_LIMIT_ACTIVE_PROCESS
    //   .ActiveProcessLimit = 4
    // via SetInformationJobObject(job, JobObjectBasicLimitInformation, &info, sizeof(info))

    // TODO 4: QueryInformationJobObject with JobObjectBasicAccountingInformation
    //   print TotalProcesses and ActiveProcesses

    // TODO 5: IsProcessInJob
    BOOL in_job = FALSE;
    // IsProcessInJob(GetCurrentProcess(), job, &in_job);
    printf("In job: %s\n", in_job ? "YES" : "NO");
    assert(in_job == TRUE);

    CloseHandle(job);
    printf("Job object exercise complete!\n");
    return 0;
}

// I AM NOT DONE

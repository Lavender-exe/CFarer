// CFarer - Windows Internals Exercise 19
// TOPIC: DeviceIoControl - user-mode to kernel-mode communication
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Windows internals / kernel programming
//
// Kernel drivers expose I/O control codes (IOCTLs) via DeviceIoControl().
// Format of a control code (CTL_CODE macro):
//   Bits 31-16: device type
//   Bits 15-14: required access
//   Bits 13-2:  function code
//   Bits 1-0:   transfer method (BUFFERED/DIRECT/NEITHER)
//
// This exercise communicates with two built-in Windows "devices":
//
//   \\.\PhysicalDrive0     - first physical disk
//     IOCTL_DISK_GET_DRIVE_GEOMETRY -> DISK_GEOMETRY (sectors, cylinders, bytes/sector)
//
//   \\.\C:                 - logical volume
//     FSCTL_GET_NTFS_VOLUME_DATA -> NTFS_VOLUME_DATA_BUFFER (cluster size, etc.)
//
// Task:
//   1. Open \\.\C: with GENERIC_READ | FILE_SHARE_READ | FILE_SHARE_WRITE.
//   2. Issue FSCTL_GET_NTFS_VOLUME_DATA via DeviceIoControl.
//   3. Print BytesPerCluster, BytesPerSector, NumberSectors.
//   NOTE: Requires admin rights for PhysicalDrive; C: NTFS query works as standard user.

#include <windows.h>
#include <winioctl.h>   // FSCTL_GET_NTFS_VOLUME_DATA, NTFS_VOLUME_DATA_BUFFER
#include <stdio.h>

int main(void) {
    // TODO 1: CreateFileA("\\\\.\\C:", GENERIC_READ,
    //           FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
    //           OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL)
    HANDLE vol = INVALID_HANDLE_VALUE;
    if (vol == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Open failed: %lu\n", GetLastError());
        return 1;
    }

    NTFS_VOLUME_DATA_BUFFER nvd = {0};
    DWORD returned = 0;

    // TODO 2: DeviceIoControl(vol, FSCTL_GET_NTFS_VOLUME_DATA,
    //           NULL, 0, &nvd, sizeof(nvd), &returned, NULL)
    BOOL ok = FALSE;

    if (ok) {
        printf("BytesPerCluster : %lu\n", nvd.BytesPerCluster);
        printf("BytesPerSector  : %lu\n", nvd.BytesPerSector);
        printf("NumberSectors   : %lld\n", nvd.NumberSectors.QuadPart);
        printf("TotalClusters   : %lld\n", nvd.TotalClusters.QuadPart);
        printf("FreeClusters    : %lld\n", nvd.FreeClusters.QuadPart);
    } else {
        fprintf(stderr, "IOCTL failed: %lu\n", GetLastError());
    }

    // TODO 3: CloseHandle(vol)
    return ok ? 0 : 1;
}

// I AM NOT DONE

// CFarer - Windows Internals Exercise 05
// TOPIC: Named Pipes - IPC between processes
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Windows internals education / authorized tooling
//
// Named pipes provide full-duplex IPC.  Used by:
//   - SMB file sharing (\\server\pipe\*)
//   - Many C2 frameworks (Cobalt Strike, Metasploit)
//   - Windows services communicating with clients
//
// Server side:
//   CreateNamedPipeA(name, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE|PIPE_WAIT,
//                   max_instances, out_buf, in_buf, timeout, NULL)
//   ConnectNamedPipe(pipe, NULL)   - block until client connects
//
// Client side:
//   WaitNamedPipeA(name, NMPWAIT_WAIT_FOREVER)
//   CreateFileA(name, GENERIC_READWRITE, 0, NULL, OPEN_EXISTING, 0, NULL)
//
// Task: This single program spawns a server thread and a client thread.
// Complete the server_thread() and client_thread() functions so they
// exchange the message "PING" -> "PONG".

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define PIPE_NAME "\\\\.\\pipe\\cfarer_test"

DWORD WINAPI server_thread(LPVOID arg) {
    // TODO:
    // 1. CreateNamedPipeA
    // 2. ConnectNamedPipe
    // 3. ReadFile - expect "PING"
    // 4. WriteFile - send "PONG"
    // 5. FlushFileBuffers, DisconnectNamedPipe, CloseHandle
    return 0;
}

DWORD WINAPI client_thread(LPVOID arg) {
    // TODO:
    // 1. WaitNamedPipeA
    // 2. CreateFileA to open the pipe
    // 3. WriteFile - send "PING"
    // 4. ReadFile  - expect "PONG"
    // 5. CloseHandle
    return 0;
}

int main(void) {
    HANDLE srv = CreateThread(NULL, 0, server_thread, NULL, 0, NULL);
    Sleep(100);   // let server set up pipe before client connects
    HANDLE cli = CreateThread(NULL, 0, client_thread, NULL, 0, NULL);

    HANDLE threads[2] = {srv, cli};
    WaitForMultipleObjects(2, threads, TRUE, 5000);
    CloseHandle(srv);
    CloseHandle(cli);

    printf("Named pipe exchange complete!\n");
    return 0;
}

// I AM NOT DONE

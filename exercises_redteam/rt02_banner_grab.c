// CFarer - Red Team Exercise 02
// TOPIC: Banner Grabbing - Service Fingerprinting
// DIFFICULTY: Beginner-Intermediate  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education
//
// Many services send a banner immediately on connect (FTP, SMTP, SSH, Telnet).
// HTTP servers respond to a GET request with headers including Server: version.
// Banner grabbing identifies running software and versions for vulnerability research.
//
// Task:
//   1. Connect TCP to 127.0.0.1:80 (HTTP) - or any open port on a test target.
//   2. Send "HEAD / HTTP/1.0\r\nHost: 127.0.0.1\r\n\r\n"
//   3. recv() up to 1024 bytes.
//   4. Print raw response (headers contain Server:, X-Powered-By:, etc.).
//   5. Attempt port 21 (FTP) - read banner WITHOUT sending anything.
//      FTP servers send "220 <banner>" on connect.
//   6. Handle WSAECONNREFUSED gracefully.

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")

static void grab_banner(const char *host, int port, const char *send_str) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons((u_short)port);
    inet_pton(AF_INET, host, &addr.sin_addr);

    printf("=== %s:%d ===\n", host, port);

    // TODO 1: connect(s, (struct sockaddr*)&addr, sizeof(addr))
    int conn = SOCKET_ERROR; // replace
    if (conn != 0) {
        int err = WSAGetLastError();
        printf("connect failed: %d%s\n", err,
               err == WSAECONNREFUSED ? " (REFUSED)" : "");
        closesocket(s);
        WSACleanup();
        return;
    }

    // TODO 2: if send_str is not NULL, send it
    if (send_str) {
        // send(s, send_str, (int)strlen(send_str), 0);
    }

    // TODO 3: recv up to 1024 bytes with 2 second timeout
    //   setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout))
    //   where timeout is DWORD timeout_ms = 2000;
    char buf[1025] = {0};
    int n = 0; // replace: n = recv(s, buf, sizeof(buf)-1, 0);
    if (n > 0) {
        buf[n] = '\0';
        printf("%s\n", buf);
    } else {
        printf("(no response)\n");
    }

    closesocket(s);
    WSACleanup();
}

int main(void) {
    // HTTP banner (send HEAD request)
    grab_banner("127.0.0.1", 80,
                "HEAD / HTTP/1.0\r\nHost: 127.0.0.1\r\n\r\n");

    // FTP banner (just connect, read greeting)
    grab_banner("127.0.0.1", 21, NULL);

    // SMTP banner
    grab_banner("127.0.0.1", 25, NULL);

    return 0;
}

// I AM NOT DONE

// CFarer - Red Team Exercise 01
// TOPIC: TCP Connect Port Scanner
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education
//
// A connect scan attempts a full TCP 3-way handshake on each port.
// If connect() succeeds: port is open.
// If connect() returns WSAECONNREFUSED: port is closed.
// If connect() times out: port is filtered (firewall).
//
// Use non-blocking sockets + select() for speed:
//   ioctlsocket(s, FIONBIO, &mode=1)  - set non-blocking
//   connect() returns WSAEWOULDBLOCK immediately
//   select(0, NULL, &write_set, &error_set, &tv)  - wait for connect result
//   FD_ISSET in write_set: connected; in error_set: refused
//
// Task:
//   1. WSAStartup.
//   2. For ports 20-25, 53, 80, 443, 445, 3389, 8080 on "127.0.0.1":
//      a. Create TCP socket.
//      b. Set non-blocking.
//      c. connect() - expect WSAEWOULDBLOCK.
//      d. select() with 200ms timeout.
//      e. Print "OPEN", "CLOSED", or "FILTERED".
//      f. closesocket.
//   3. WSACleanup.

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

#define TARGET "127.0.0.1"
static const int PORTS[] = { 20,21,22,23,25,53,80,443,445,3389,8080 };
#define NUM_PORTS (sizeof(PORTS)/sizeof(PORTS[0]))

static const char *scan_port(const char *host, int port) {
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) return "ERROR";

    // TODO: set non-blocking
    u_long mode = 1;
    // ioctlsocket(s, FIONBIO, &mode);
    (void)mode;

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons((u_short)port);
    inet_pton(AF_INET, host, &addr.sin_addr);

    // TODO: connect (expects WSAEWOULDBLOCK in non-blocking mode)
    connect(s, (struct sockaddr*)&addr, sizeof(addr));

    // TODO: select with 200ms timeout
    fd_set wset, eset;
    FD_ZERO(&wset); FD_ZERO(&eset);
    FD_SET(s, &wset); FD_SET(s, &eset);
    struct timeval tv = { 0, 200000 }; // 200ms
    int sel = 0; // replace: sel = select(0, NULL, &wset, &eset, &tv);

    const char *result = "FILTERED";
    if (sel > 0) {
        if (FD_ISSET(s, &eset))       result = "CLOSED";
        else if (FD_ISSET(s, &wset))  result = "OPEN";
    }

    closesocket(s);
    return result;
}

int main(void) {
    WSADATA wsa;
    // TODO: WSAStartup(MAKEWORD(2,2), &wsa)
    (void)wsa;

    printf("Scanning %s...\n\n", TARGET);
    printf("%-8s %s\n", "PORT", "STATE");
    printf("%-8s %s\n", "----", "-----");
    for (size_t i = 0; i < NUM_PORTS; i++) {
        const char *state = scan_port(TARGET, PORTS[i]);
        printf("%-8d %s\n", PORTS[i], state);
    }

    WSACleanup();
    return 0;
}

// I AM NOT DONE

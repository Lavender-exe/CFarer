// CFarer - Malware Development Exercise 09
// TOPIC: TCP Beacon - implant networking foundation
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// A beacon is the core of most implants: connect to C2, send a heartbeat,
// receive optional commands, sleep, repeat.
//
// Winsock basics:
//   WSAStartup()               - initialize WS2_32
//   getaddrinfo()              - resolve host:port -> ADDRINFOA linked list
//   socket(AF_INET,SOCK_STREAM,0) - TCP socket
//   connect(s, addr, addrlen) - 3-way handshake
//   send() / recv()            - blocking I/O
//   closesocket() / WSACleanup()
//
// Task:
//   1. WSAStartup(MAKEWORD(2,2), &wsa)
//   2. Resolve "127.0.0.1" port 4444 via getaddrinfo.
//   3. Create TCP socket and connect (it's OK if connection is refused -
//      the exercise just needs to reach connect() without crashing).
//   4. If connected: send the beacon string "BEACON\n" once.
//   5. Print "sent beacon" on success, or the WSAGetLastError() code on failure.
//   6. closesocket / freeaddrinfo / WSACleanup.
//
// NOTE: No listener needed - WSAECONNREFUSED (10061) is an acceptable result.

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

#define C2_HOST "127.0.0.1"
#define C2_PORT "4444"
#define BEACON_MSG "BEACON\n"

int main(void) {
    WSADATA wsa;
    // TODO 1: WSAStartup(MAKEWORD(2,2), &wsa)
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        fprintf(stderr, "WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }

    ADDRINFOA hints = {0}, *res = NULL;
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // TODO 2: getaddrinfo(C2_HOST, C2_PORT, &hints, &res)
    int rc = 1; // replace with the getaddrinfo call (placeholder forces the failure path)
    if (rc != 0) {
        fprintf(stderr, "getaddrinfo failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // TODO 3: socket(res->ai_family, res->ai_socktype, res->ai_protocol)
    SOCKET s = INVALID_SOCKET;

    if (s == INVALID_SOCKET) {
        fprintf(stderr, "socket failed: %d\n", WSAGetLastError());
        freeaddrinfo(res);
        WSACleanup();
        return 1;
    }

    // TODO 4: connect(s, res->ai_addr, (int)res->ai_addrlen)
    int conn = SOCKET_ERROR; // replace with connect call

    if (conn == 0) {
        // TODO 5: send(s, BEACON_MSG, (int)strlen(BEACON_MSG), 0)
        int sent = 0; // replace with send call
        if (sent > 0)
            printf("sent beacon (%d bytes)\n", sent);
        else
            printf("send failed: %d\n", WSAGetLastError());
    } else {
        int err = WSAGetLastError();
        if (err == WSAECONNREFUSED)
            printf("connect refused (10061) - no listener, but beacon logic works\n");
        else
            printf("connect failed: %d\n", err);
    }

    // TODO 6: closesocket(s), freeaddrinfo(res), WSACleanup()
    return 0;
}

// I AM NOT DONE

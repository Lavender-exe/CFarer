// CFarer - Maldev Exercise 14
// TOPIC: HTTP Beacon via WinINet
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// Most real-world implants use HTTP/S for C2 traffic because it blends with
// normal web traffic and often traverses proxies/firewalls.
//
// WinINet provides high-level HTTP functions that handle TLS, proxy detection
// (reads IE/system proxy settings), and redirects automatically.
//
// Beacon loop pattern:
//   InternetOpen -> InternetConnect -> HttpOpenRequest ->
//   HttpSendRequest -> InternetReadFile -> loop / sleep
//
// Task:
//   1. InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0)
//      - use PRECONFIG so system proxy is respected
//   2. InternetConnectA(hInet, "httpbin.org", 80, NULL, NULL,
//        INTERNET_SERVICE_HTTP, 0, 0)
//   3. HttpOpenRequestA(hConn, "GET", "/get", NULL, NULL, NULL, 0, 0)
//   4. HttpSendRequestA(hReq, NULL, 0, NULL, 0)
//   5. Read up to 512 bytes of response with InternetReadFile.
//   6. Print response body (first 256 chars).
//   7. Close all handles in reverse order.
//
// NOTE: If no internet access, WSAECONNREFUSED / ERROR_INTERNET_* is acceptable.
//       The exercise validates the WinINet call sequence.

#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#pragma comment(lib, "wininet.lib")

#define C2_HOST "httpbin.org"
#define C2_PORT 80
#define C2_PATH "/get"
#define USER_AGENT "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"

int main(void) {
    // TODO 1: InternetOpenA(USER_AGENT, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0)
    HINTERNET hInet = NULL; // replace with InternetOpenA call
    if (!hInet) {
        fprintf(stderr, "InternetOpen failed: %lu\n", GetLastError());
        return 1;
    }

    // TODO 2: InternetConnectA(hInet, C2_HOST, C2_PORT, NULL, NULL,
    //           INTERNET_SERVICE_HTTP, 0, 0)
    HINTERNET hConn = NULL; // replace with InternetConnectA call
    if (!hConn) {
        fprintf(stderr, "InternetConnect failed: %lu\n", GetLastError());
        InternetCloseHandle(hInet);
        return 1;
    }

    // TODO 3: HttpOpenRequestA(hConn, "GET", C2_PATH, NULL, NULL, NULL, 0, 0)
    HINTERNET hReq = NULL; // replace with HttpOpenRequestA call
    if (!hReq) {
        fprintf(stderr, "HttpOpenRequest failed: %lu\n", GetLastError());
        InternetCloseHandle(hConn);
        InternetCloseHandle(hInet);
        return 1;
    }

    // TODO 4: HttpSendRequestA(hReq, NULL, 0, NULL, 0)
    BOOL sent = FALSE; // replace with HttpSendRequestA call
    if (!sent) {
        DWORD err = GetLastError();
        printf("HttpSendRequest failed: %lu (no internet = expected)\n", err);
    } else {
        char buf[512] = {0};
        DWORD read = 0;
        // TODO 5: InternetReadFile(hReq, buf, sizeof(buf)-1, &read)
        BOOL ok = FALSE; // replace with InternetReadFile call
        if (ok && read > 0) {
            buf[read] = '\0';
            printf("Response (%lu bytes):\n%.256s\n", read, buf);
        }
    }

    // TODO 6: close handles in reverse order
    //   InternetCloseHandle(hReq);
    //   InternetCloseHandle(hConn);
    //   InternetCloseHandle(hInet);

    return 0;
}

// I AM NOT DONE

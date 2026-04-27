// CFarer - Red Team Exercise 10
// TOPIC: Pass-the-Hash - LogonUserA with NTLM hash
// DIFFICULTY: Advanced  PLATFORM: Windows
// PURPOSE: Authorized penetration testing education - lateral movement
//
// Pass-the-hash (PtH) authenticates to services using an NTLM hash instead
// of the plaintext password.  NTLM authentication uses the hash directly in
// the challenge-response - the password is never needed.
//
// Windows API approach: LogonUserA with LOGON32_LOGON_NEW_CREDENTIALS +
//   LOGON32_PROVIDER_WINNT50 accepts NTLM hashes as the password field when
//   combined with the correct flag set.
//
// Actually, the real Windows PtH trick uses NtLmSsp or Mimikatz's sekurlsa::pth
// which injects credentials directly into LSASS memory.  The LogonUser approach
// only works for service ticket (network) auth, not local token creation.
//
// THIS EXERCISE focuses on the credential structure:
//   1. Understand NTLM hash format: MD4(UTF-16-LE(password)) - 16 bytes hex.
//   2. Compute the NTLM hash of "Password123" using Windows CNG API:
//      BCryptOpenAlgorithmProvider(BCRYPT_MD4_ALGORITHM)
//      BCryptCreateHash -> BCryptHashData(utf16_password) -> BCryptFinishHash
//   3. Print hex hash and compare to known value:
//      MD4("Password123" in UTF-16) = 58a478135a93ac3bf058a5ea0e8fdb71
//   4. Bonus: attempt CreateProcessWithLogonW with the hash as password
//      (will fail auth but demonstrates the API surface).

#include <windows.h>
#include <bcrypt.h>
#include <stdio.h>
#pragma comment(lib, "bcrypt.lib")

// Known answer: NTLM of "Password123" = 58a478135a93ac3bf058a5ea0e8fdb71
static const char *KNOWN_HASH = "58a478135a93ac3bf058a5ea0e8fdb71";

int main(void) {
    const WCHAR *pw = L"Password123";
    DWORD pw_bytes  = (DWORD)(wcslen(pw) * sizeof(WCHAR));
    BYTE  hash[16]  = {0};
    DWORD hash_len  = 0;

    BCRYPT_ALG_HANDLE hAlg = NULL;
    BCRYPT_HASH_HANDLE hHash = NULL;

    // TODO 1: BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_MD4_ALGORITHM, NULL, 0)
    NTSTATUS st = 0; // replace
    if (!BCRYPT_SUCCESS(st)) {
        fprintf(stderr, "BCryptOpenAlgorithmProvider: 0x%lx\n", (ULONG)st);
        return 1;
    }

    // TODO 2: BCryptGetProperty(hAlg, BCRYPT_HASH_LENGTH, &hash_len, sizeof(hash_len), &res, 0)
    //   to confirm hash size == 16

    // TODO 3: BCryptCreateHash(hAlg, &hHash, NULL, 0, NULL, 0, 0)
    // TODO 4: BCryptHashData(hHash, (PUCHAR)pw, pw_bytes, 0)
    // TODO 5: BCryptFinishHash(hHash, hash, sizeof(hash), 0)

    printf("NTLM hash of 'Password123':\n");
    printf("computed: ");
    for (int i = 0; i < 16; i++) printf("%02x", hash[i]);
    printf("\n");
    printf("expected: %s\n", KNOWN_HASH);

    // Simple match check
    char computed[33] = {0};
    for (int i = 0; i < 16; i++) sprintf(computed + i*2, "%02x", hash[i]);
    printf("match: %s\n", strcmp(computed, KNOWN_HASH) == 0 ? "YES" : "NO");

    if (hHash) BCryptDestroyHash(hHash);
    if (hAlg)  BCryptCloseAlgorithmProvider(hAlg, 0);
    return 0;
}

// I AM NOT DONE

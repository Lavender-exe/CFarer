// CFarer - Malware Development Exercise 10
// TOPIC: XOR Payload Encoding / Decoding
// DIFFICULTY: Beginner-Intermediate  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// XOR encoding is the simplest obfuscation layer for shellcode:
//   encoded[i] = plaintext[i] ^ key[i % keylen]
//   decoded[i] = encoded[i]  ^ key[i % keylen]  (XOR is self-inverse)
//
// Use cases:
//   - Avoid static signature detection on raw shellcode bytes
//   - Multi-byte rolling XOR keys increase pattern entropy
//   - In implants: store encoded payload, decode into allocated RWX memory at runtime
//
// Task:
//   1. XOR-encode the stub payload with the provided 4-byte key.
//   2. XOR-decode the encoded buffer back into a new buffer.
//   3. Assert decoded bytes match original.
//   4. Print hex dump of original, encoded, and decoded buffers.
//
// NOTE: The "shellcode" here is just printable bytes - no execution.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Simulated shellcode stub (printable bytes for easy verification)
static const BYTE payload[] = {
    0x48, 0x31, 0xC0, 0x48, 0x31, 0xDB, 0x48, 0x31,
    0xC9, 0x48, 0x31, 0xD2, 0xB0, 0x3B, 0x0F, 0x05
};
#define PAYLOAD_LEN (sizeof(payload))

static const BYTE key[] = { 0xDE, 0xAD, 0xBE, 0xEF };
#define KEY_LEN (sizeof(key))

static void hex_dump(const char *label, const BYTE *buf, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++)
        printf("%02X ", buf[i]);
    printf("\n");
}

int main(void) {
    BYTE encoded[PAYLOAD_LEN];
    BYTE decoded[PAYLOAD_LEN];

    // TODO 1: XOR-encode payload into encoded[]
    //   for each i: encoded[i] = payload[i] ^ key[i % KEY_LEN]
    for (size_t i = 0; i < PAYLOAD_LEN; i++) {
        encoded[i] = 0; // TODO: replace with XOR expression
    }

    // TODO 2: XOR-decode encoded[] into decoded[]
    //   for each i: decoded[i] = encoded[i] ^ key[i % KEY_LEN]
    for (size_t i = 0; i < PAYLOAD_LEN; i++) {
        decoded[i] = 0; // TODO: replace with XOR expression
    }

    // TODO 3: assert memcmp(decoded, payload, PAYLOAD_LEN) == 0
    assert(memcmp(decoded, payload, PAYLOAD_LEN) == 0);  // gate: fails until TODO 1/2 done

    hex_dump("original", payload,  PAYLOAD_LEN);
    hex_dump("encoded ", encoded,  PAYLOAD_LEN);
    hex_dump("decoded ", decoded,  PAYLOAD_LEN);

    // Verify no byte in encoded matches original (key is non-zero so this holds
    // unless key byte happens to be 0 for that position - our key has none)
    int all_differ = 1;
    for (size_t i = 0; i < PAYLOAD_LEN; i++)
        if (encoded[i] == payload[i]) { all_differ = 0; break; }
    printf("all encoded bytes differ from plaintext: %s\n", all_differ ? "YES" : "NO");

    printf("XOR round-trip: %s\n",
        memcmp(decoded, payload, PAYLOAD_LEN) == 0 ? "PASS" : "FAIL");
    return 0;
}

// I AM NOT DONE

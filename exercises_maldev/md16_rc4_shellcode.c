// CFarer - Maldev Exercise 16
// TOPIC: RC4 Stream Cipher - Encrypt/Decrypt Shellcode
// DIFFICULTY: Intermediate  PLATFORM: Windows
// PURPOSE: Authorized malware research / red team education
//
// RC4 (Rivest Cipher 4) is a symmetric stream cipher.
// It uses a Key Scheduling Algorithm (KSA) to initialise a 256-byte state array,
// then a Pseudo-Random Generation Algorithm (PRGA) to XOR each plaintext byte.
//
// KSA:
//   S[i] = i for i in 0..255
//   j = 0
//   for i in 0..255: j = (j + S[i] + key[i%keylen]) % 256; swap(S[i], S[j])
//
// PRGA (keystream generation):
//   i = j = 0
//   for each byte: i=(i+1)%256; j=(j+S[i])%256; swap(S[i],S[j]); out = S[(S[i]+S[j])%256]
//   encrypt/decrypt: plaintext[n] ^ keystream[n]
//
// Task:
//   1. Implement rc4_init(state, key, keylen)   - KSA
//   2. Implement rc4_crypt(state, buf, buflen)  - PRGA in-place
//   3. Encrypt the stub payload with key "CFarer2025".
//   4. Decrypt the ciphertext back to plaintext.
//   5. Assert round-trip matches original.
//   6. Print entropy hint: count unique bytes in ciphertext vs plaintext.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct { unsigned char S[256]; unsigned int i, j; } RC4_CTX;

// TODO 1: KSA
void rc4_init(RC4_CTX *ctx, const unsigned char *key, size_t keylen) {
    // Initialize S[i] = i
    for (int i = 0; i < 256; i++) ctx->S[i] = (unsigned char)i;
    ctx->i = ctx->j = 0;

    // TODO: KSA mixing loop
    // unsigned j = 0;
    // for (int i = 0; i < 256; i++) {
    //     j = (j + ctx->S[i] + key[i % keylen]) % 256;
    //     unsigned char tmp = ctx->S[i]; ctx->S[i] = ctx->S[j]; ctx->S[j] = tmp;
    // }
}

// TODO 2: PRGA - XOR buf in-place
void rc4_crypt(RC4_CTX *ctx, unsigned char *buf, size_t buflen) {
    // for each byte:
    //   ctx->i = (ctx->i + 1) % 256;
    //   ctx->j = (ctx->j + ctx->S[ctx->i]) % 256;
    //   swap(S[i], S[j]);
    //   buf[n] ^= ctx->S[(ctx->S[ctx->i] + ctx->S[ctx->j]) % 256];
    (void)buf; (void)buflen;
}

static const unsigned char key[] = "CFarer2025";
#define KEY_LEN (sizeof(key) - 1)  // exclude null terminator

static const unsigned char payload[] = {
    0x48, 0x31, 0xC0, 0x48, 0x31, 0xDB, 0x48, 0x31,
    0xC9, 0x48, 0x31, 0xD2, 0xB0, 0x3B, 0x0F, 0x05,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
};
#define PAYLOAD_LEN sizeof(payload)

static void hex_dump(const char *label, const unsigned char *b, size_t n) {
    printf("%-10s ", label);
    for (size_t i = 0; i < n; i++) printf("%02X ", b[i]);
    printf("\n");
}

int main(void) {
    unsigned char ciphertext[PAYLOAD_LEN];
    unsigned char decrypted[PAYLOAD_LEN];
    memcpy(ciphertext, payload, PAYLOAD_LEN);
    memcpy(decrypted, payload, PAYLOAD_LEN);

    // TODO 3: encrypt
    RC4_CTX enc_ctx = {0};
    rc4_init(&enc_ctx, key, KEY_LEN);
    rc4_crypt(&enc_ctx, ciphertext, PAYLOAD_LEN);

    // TODO 4: decrypt (RC4 is symmetric - same operation with same key)
    RC4_CTX dec_ctx = {0};
    rc4_init(&dec_ctx, key, KEY_LEN);
    rc4_crypt(&dec_ctx, decrypted, PAYLOAD_LEN);  // actually decrypt the ciphertext
    // BUG: you encrypted the copy but decrypted the copy of payload - fix this

    hex_dump("plaintext", payload,    PAYLOAD_LEN);
    hex_dump("encrypted", ciphertext, PAYLOAD_LEN);
    hex_dump("decrypted", decrypted,  PAYLOAD_LEN);

    // TODO 5: assert(memcmp(decrypted, payload, PAYLOAD_LEN) == 0)
    printf("RC4 round-trip: %s\n",
        memcmp(decrypted, payload, PAYLOAD_LEN) == 0 ? "PASS" : "FAIL");
    return 0;
}

// I AM NOT DONE

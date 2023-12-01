#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SHA256_BLOCK_SIZE 64

// SHA-256 constants
static const uint32_t SHA256_CONSTANTS[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// SHA-256 context structure
typedef struct {
    uint32_t state[8];
    uint32_t count[2];
    uint8_t buffer[SHA256_BLOCK_SIZE];
} SHA256_CTX;

// Circular right shift
#define RIGHT_ROTATE(value, shift) (((value) >> (shift)) | ((value) << (32 - (shift))))

// SHA-256 initialization
void sha256_init(SHA256_CTX *context) {
    context->state[0] = 0x6a09e667;
    context->state[1] = 0xbb67ae85;
    context->state[2] = 0x3c6ef372;
    context->state[3] = 0xa54ff53a;
    context->state[4] = 0x510e527f;
    context->state[5] = 0x9b05688c;
    context->state[6] = 0x1f83d9ab;
    context->state[7] = 0x5be0cd19;
    context->count[0] = context->count[1] = 0;
}

// SHA-256 block processing
void sha256_process_block(SHA256_CTX *context, const uint8_t block[SHA256_BLOCK_SIZE]) {
    uint32_t state[8];
    uint32_t w[64];
    uint32_t temp1, temp2;

    // Copy state to working variables
    memcpy(state, context->state, sizeof(context->state));

    // Convert the input block to an array of 32-bit words
    for (int i = 0; i < 16; i++) {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }

    // Extend the first 16 words into the remaining 48 words of the message schedule array
    for (int i = 16; i < 64; i++) {
        uint32_t s0 = RIGHT_ROTATE(w[i - 15], 7) ^ RIGHT_ROTATE(w[i - 15], 18) ^ (w[i - 15] >> 3);
        uint32_t s1 = RIGHT_ROTATE(w[i - 2], 17) ^ RIGHT_ROTATE(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    // SHA-256 main loop
    for (int i = 0; i < 64; i++) {
        uint32_t s1 = RIGHT_ROTATE(state[4], 6) ^ RIGHT_ROTATE(state[4], 11) ^ RIGHT_ROTATE(state[4], 25);
        uint32_t ch = (state[4] & state[5]) ^ (~state[4] & state[6]);
        uint32_t temp1 = state[7] + s1 + ch + SHA256_CONSTANTS[i] + w[i];
        uint32_t s0 = RIGHT_ROTATE(state[0], 2) ^ RIGHT_ROTATE(state[0], 13) ^ RIGHT_ROTATE(state[0], 22);
        uint32_t maj = (state[0] & state[1]) ^ (state[0] & state[2]) ^ (state[1] & state[2]);
        uint32_t temp2 = s0 + maj;

        state[7] = state[6];
        state[6] = state[5];
        state[5] = state[4];
        state[4] = state[3] + temp1;
        state[3] = state[2];
        state[2] = state[1];
        state[1] = state[0];
        state[0] = temp1 + temp2;
    }



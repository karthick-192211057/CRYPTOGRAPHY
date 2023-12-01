#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MD5_BLOCK_SIZE 64

// MD5 context structure
typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    uint8_t buffer[MD5_BLOCK_SIZE];
} MD5_CTX;

// MD5 constants
static const uint32_t MD5_CONSTANTS[] = {
    0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476
};

// MD5 functions
#define F(X, Y, Z) (((X) & (Y)) | ((~X) & (Z)))
#define G(X, Y, Z) (((X) & (Z)) | ((Y) & (~Z)))
#define H(X, Y, Z) ((X) ^ (Y) ^ (Z))
#define I(X, Y, Z) ((Y) ^ ((X) | (~Z)))

// Circular left shift
#define LEFT_ROTATE(value, shift) (((value) << (shift)) | ((value) >> (32 - (shift))))

// MD5 round functions
#define MD5_ROUND(F, a, b, c, d, x, s, ac) \
    (a) = (a) + F(b, c, d) + (x) + (ac); \
    (a) = LEFT_ROTATE((a), (s)); \
    (a) = (a) + (b);

// MD5 initialization
void md5_init(MD5_CTX *context) {
    context->state[0] = MD5_CONSTANTS[0];
    context->state[1] = MD5_CONSTANTS[1];
    context->state[2] = MD5_CONSTANTS[2];
    context->state[3] = MD5_CONSTANTS[3];
    context->count[0] = context->count[1] = 0;
}

// MD5 block processing
void md5_process_block(MD5_CTX *context, const uint8_t block[MD5_BLOCK_SIZE]) {
    uint32_t a = context->state[0];
    uint32_t b = context->state[1];
    uint32_t c = context->state[2];
    uint32_t d = context->state[3];
    uint32_t x[16];

    // Convert the input block to an array


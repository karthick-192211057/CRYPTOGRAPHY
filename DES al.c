#include <stdio.h>
#include <stdint.h>

// Initial permutation table
int initial_permutation_table[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Example key (64 bits)
uint64_t key = 0x133457799BBCDFF1;

// Function to perform the initial permutation
uint64_t initial_permutation(uint64_t input) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        result |= ((input >> (64 - initial_permutation_table[i])) & 1) << (63 - i);
    }
    return result;
}

// Function to display the binary representation of a 64-bit integer
void print_binary(uint64_t num) {
    for (int i = 63; i >= 0; i--) {
        printf("%llu", (num >> i) & 1);
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    // Perform initial permutation on the key
    uint64_t permuted_key = initial_permutation(key);

    // Display the binary representation of the permuted key
    printf("Initial Permuted Key:\n");
    print_binary(permuted_key);

    return 0;
}


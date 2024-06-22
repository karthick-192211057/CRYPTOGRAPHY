#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute gcd
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to compute the modular inverse
int modInverse(int e, int phi) {
    int t = 0, newT = 1;
    int r = phi, newR = e;
    while (newR != 0) {
        int quotient = r / newR;
        int tempT = newT;
        newT = t - quotient * newT;
        t = tempT;

        int tempR = newR;
        newR = r - quotient * newR;
        r = tempR;
    }
    if (r > 1) return -1;  // No inverse exists
    if (t < 0) t = t + phi;
    return t;
}

// Function to compute (base^exp) % mod
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int p, q, e, message;
    
    // Get user input
    printf("Enter a prime number p: ");
    scanf("%d", &p);
    printf("Enter a prime number q: ");
    scanf("%d", &q);
    printf("Enter a public exponent e: ");
    scanf("%d", &e);
    printf("Enter the message to encrypt (integer): ");
    scanf("%d", &message);

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Ensure e is coprime with phi and 1 < e < phi
    if (gcd(e, phi) != 1) {
        printf("e and phi are not coprime. Choose a different e.\n");
        return -1;
    }

    int d = modInverse(e, phi);
    if (d == -1) {
        printf("Modular inverse of e and phi doesn't exist.\n");
        return -1;
    }

    printf("Original Message: %d\n", message);

    // Encryption: c = (message^e) % n
    int encrypted = modExp(message, e, n);
    printf("Encrypted Message: %d\n", encrypted);

    // Decryption: m = (encrypted^d) % n
    int decrypted = modExp(encrypted, d, n);
    printf("Decrypted Message: %d\n", decrypted);

    return 0;
}
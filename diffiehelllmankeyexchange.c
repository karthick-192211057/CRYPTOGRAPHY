#include <stdio.h>
#include <math.h>

int power(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    
    int q = 23; 
    int a = 5;  
    int xAlice = 6;
    int A = power(a, xAlice, q);   
    int xBob = 15;
    int B = power(a, xBob, q);
    int sAlice = power(B, xAlice, q);
    int sBob = power(A, xBob, q);
    printf("Shared secret for Alice: %d\n", sAlice);
    printf("Shared secret for Bob: %d\n", sBob);

    return 0;
}

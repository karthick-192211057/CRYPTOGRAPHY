#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void encipher(char *input, char *key, char *output);
void decipher(char *input, char *key, char *output);
int main() {
    char input[50], key[50], output[50];
    int choice;
    printf("Enter the Plain Text: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    printf("Enter the Key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    printf("\n1. Encrypt Text\n2. Decrypt Text\nEnter Your Choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        encipher(input, key, output);
        printf("\nEncrypted Text: %s\n", output);
    } else if (choice == 2) {
        decipher(input, key, output);
        printf("\nDecrypted Text: %s\n", output);
    } else {
        printf("\nInvalid Choice\n");
    }
    return 0;
}
void encipher(char *input, char *key, char *output) {
    for (int i = 0; i < strlen(input); i++) {
        output[i] = ((input[i] - 'A') + (key[i] - 'A')) % 26 + 'A';
    }
    output[strlen(input)] = '\0';
}
void decipher(char *input, char *key, char *output) {
    for (int i = 0; i < strlen(input); i++) {
        output[i] = ((input[i] - 'A') - (key[i] - 'A') + 26) % 26 + 'A';
    }
    output[strlen(input)] = '\0';
}


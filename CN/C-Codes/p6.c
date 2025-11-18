#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global definitions for polynomial
// G(x) = x^16 + x^12 + x^5 + 1 (A common CRC-16 polynomial)
// The string 'g' is the binary representation: 10001000000100001
const char POLYNOMIAL_G[] = "10001000000100001";
const int POLYNOMIAL_LEN = 17; // N = strlen(g)

// Data arrays and length
char data_frame[128] = {0}; // The original data (t)
char remainder[128] = {0};  // The current remainder/checksum (cs)
int data_len;               // Length of the original data (a)

/**
 * @brief Performs the XOR operation for the CRC division step.
 * cs = cs XOR g
 */
void xor_operation() {
    for (int i = 1; i < POLYNOMIAL_LEN; i++) {
        // Equivalent to: remainder[i] = remainder[i] ^ POLYNOMIAL_G[i];
        remainder[i] = (remainder[i] == POLYNOMIAL_G[i]) ? '0' : '1';
    }
}

/**
 * @brief Performs the CRC calculation (binary division).
 * Calculates the remainder for a given data_frame.
 */
void calculate_crc() {
    int i, j;
    int extended_data_len = data_len + POLYNOMIAL_LEN - 1;

    // 1. Initialize the remainder with the first N bits of the data_frame
    for (i = 0; i < POLYNOMIAL_LEN; i++) {
        remainder[i] = data_frame[i];
    }

    // 2. Perform the division
    for (j = POLYNOMIAL_LEN; j <= extended_data_len; j++) {
        // If the MSB of the remainder is '1', perform XOR
        if (remainder[0] == '1') {
            xor_operation();
        }

        // Shift the remainder left by 1 bit and bring in the next bit from the data_frame
        for (i = 0; i < POLYNOMIAL_LEN - 1; i++) {
            remainder[i] = remainder[i+1];
        }
        remainder[POLYNOMIAL_LEN - 1] = data_frame[j];
    }
}

int main() {
    printf("\n--- CRC Error Detection Simulation ---\n");

    // --- Sender Side ---

    printf("Enter data to transmit (binary string): ");
    scanf("%s", data_frame);

    data_len = strlen(data_frame);
    
    // 1. Append N-1 zeros to the data_frame
    for (int i = 0; i < POLYNOMIAL_LEN - 1; i++) {
        data_frame[data_len + i] = '0';
    }
    data_frame[data_len + POLYNOMIAL_LEN - 1] = '\0'; // Null-terminate the extended string

    printf("Generator Polynomial G(x) is : %s (Length N=%d)\n", POLYNOMIAL_G, POLYNOMIAL_LEN);
    printf("Data with %d appended zeros : %s\n", POLYNOMIAL_LEN - 1, data_frame);

    // 2. Calculate the CRC (checksum)
    calculate_crc();
    
    // The final remainder (checksum) is in the first N-1 bits of the remainder array
    char checksum[POLYNOMIAL_LEN];
    strncpy(checksum, remainder, POLYNOMIAL_LEN - 1);
    checksum[POLYNOMIAL_LEN - 1] = '\0';

    printf("Calculated Checksum C(x) is   : %s\n", checksum);

    // 3. Create the final codeword
    for (int i = 0; i < POLYNOMIAL_LEN - 1; i++) {
        data_frame[data_len + i] = remainder[i]; // Replace appended zeros with the checksum
    }
    printf("Final Codeword to be Sent     : %s\n", data_frame);

    // --- Error Injection (Optional) ---
    int inject_error;
    printf("\nTest Error detection (0=yes, 1=no) ? : ");
    scanf("%d", &inject_error);

    if (inject_error == 0) {
        int error_pos;
        printf("Enter bit position (0 to %d) to flip: ", data_len + POLYNOMIAL_LEN - 2);
        scanf("%d", &error_pos);

        if (error_pos >= 0 && error_pos < data_len + POLYNOMIAL_LEN - 1) {
            data_frame[error_pos] = (data_frame[error_pos] == '0') ? '1' : '0';
            printf("Errorneous Codeword Received  : %s\n", data_frame);
        } else {
            printf("Invalid position. No error injected.\n");
        }
    } else {
        printf("Received Codeword (No change) : %s\n", data_frame);
    }

    // --- Receiver Side ---

    // 4. Recalculate CRC on the received data_frame
    calculate_crc();

    // 5. Check the final remainder
    int is_remainder_zero = 1;
    for (int i = 0; i < POLYNOMIAL_LEN - 1; i++) {
        if (remainder[i] != '0') {
            is_remainder_zero = 0;
            break;
        }
    }
    
    printf("\nFinal Remainder at Receiver   : %s\n", remainder);

    if (is_remainder_zero) {
        printf("RESULT: No Error Detected (Remainder is all zeros).\n");
    } else {
        printf("RESULT: Error Detected (Non-zero Remainder).\n");
    }

    return 0;
}
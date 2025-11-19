#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- Configuration ---
const char POLYNOMIAL_G[] = "10001000000100001";
const int POLYNOMIAL_LEN = 17; // N = strlen(g)

// --- State Variables ---
char data_frame[128] = {0}; // Data/Codeword
char remainder[128] = {0};  // Current remainder
int data_len;               // Length of user input data

/**
 * @brief Performs the XOR operation for the CRC division step.
 */
void xor_operation() {
    for (int i = 1; i < POLYNOMIAL_LEN; i++) {
        remainder[i] = (remainder[i] == POLYNOMIAL_G[i]) ? '0' : '1';
    }
}

/**
 * @brief Performs the CRC calculation (binary division) on data_frame.
 */
void calculate_crc() {
    int extended_data_len = data_len + POLYNOMIAL_LEN - 1;

    // 1. Initialize the remainder with the first N bits of the data_frame
    for (int i = 0; i < POLYNOMIAL_LEN; i++) {
        remainder[i] = data_frame[i];
    }

    // 2. Perform the division
    for (int j = POLYNOMIAL_LEN; j <= extended_data_len; j++) {
        
        // If the MSB of the remainder is '1', perform XOR
        if (remainder[0] == '1') {
            xor_operation();
        }

        // Shift the remainder left by 1 bit
        for (int i = 0; i < POLYNOMIAL_LEN - 1; i++) {
            remainder[i] = remainder[i+1];
        }
        
        // Bring in the next bit from the data_frame
        remainder[POLYNOMIAL_LEN - 1] = data_frame[j];
    }
}

int main() {
    int inject_error;
    
    // --- Assume data_frame is read here ---
    printf("Enter data to transmit (binary string): ");
    scanf("%s", data_frame);
    data_len = strlen(data_frame);
    
    // --- 1. Sender Side: Prepare Data Frame ---
    
    // Append N-1 zeros (CRC size) to the data_frame
    for (int i = 0; i < POLYNOMIAL_LEN - 1; i++) {
        data_frame[data_len + i] = '0';
    }
    data_frame[data_len + POLYNOMIAL_LEN - 1] = '\0';

    // 2. Calculate the CRC (checksum) on the extended data
    calculate_crc();
    
    // 3. Create the final codeword by appending the calculated remainder
    for (int i = 0; i < POLYNOMIAL_LEN - 1; i++) {
        data_frame[data_len + i] = remainder[i]; // Replace appended zeros with the checksum
    }

    printf("\nFinal Codeword to be Sent: %s\n", data_frame);

    // --- Error Injection (Simplified) ---
    printf("Test Error detection (0=yes, 1=no) ? : ");
    scanf("%d", &inject_error);

    if (inject_error == 0) {
        int error_pos;
        printf("Enter bit position to flip: ");
        scanf("%d", &error_pos);
        
        // Flip the bit (logic is preserved)
        if (error_pos >= 0 && error_pos < data_len + POLYNOMIAL_LEN - 1) {
            data_frame[error_pos] = (data_frame[error_pos] == '0') ? '1' : '0';
        }
        printf("Errorneous Codeword Received: %s\n", data_frame);
    }
    
    // --- 4. Receiver Side: Check for Errors ---

    // Recalculate CRC on the received (potentially erroneous) data_frame
    calculate_crc();

    // 5. Check the final remainder (error detected if remainder is non-zero)
    int is_remainder_zero = 1;
    for (int i = 0; i < POLYNOMIAL_LEN - 1; i++) {
        if (remainder[i] != '0') {
            is_remainder_zero = 0;
            break;
        }
    }
    
    printf("\nFinal Remainder at Receiver: %s\n", remainder);

    if (is_remainder_zero) {
        printf("RESULT: No Error Detected.\n");
    } else {
        printf("RESULT: Error Detected.\n");
    }

    return 0;
}
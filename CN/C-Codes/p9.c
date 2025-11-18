#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS

// Function is small and simple, but kept for readability over a ternary operator.
int min(int x, int y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

int main() {
    // --- Input Variables ---
    int bucket_capacity;    // cap: Maximum size of the bucket (B)
    int output_rate;        // process: Constant output rate (R)
    int simulation_time_sec; // nsec: Number of seconds to simulate packet arrival

    // --- State Variables ---
    int current_bucket_size = 0; // count: Current number of bytes/packets in the bucket
    int packets_dropped = 0;     // drop: Packets dropped in the current second
    int packets_sent = 0;        // mini: Packets sent in the current second (min(current_bucket_size, output_rate))
    
    // --- Simulation Input ---
    int arrival_packets[25]; // inp: Array to store packet sizes entering per second

    printf("--- Leaky Bucket Traffic Shaping Simulation ---\n");

    printf("Enter the Bucket Capacity (Max Size): ");
    scanf("%d", &bucket_capacity);

    printf("Enter the Constant Output Rate (Packets/sec): ");
    scanf("%d", &output_rate);

    printf("Enter the No. of Seconds for Packet Arrival: ");
    scanf("%d", &simulation_time_sec);

    // Read arrival packet sizes for the simulation duration
    for (int i = 0; i < simulation_time_sec; i++) {
        printf("Enter the size of the packet entering at second %d: ", i + 1);
        scanf("%d", &arrival_packets[i]);
    }

    // --- Simulation Output Header ---
    printf("\n\n");
    printf("Second | Rec'd | Sent | Left in Bucket | Dropped\n");
    printf("-------|-------|------|----------------|--------\n");

    // --- Main Simulation Loop (While packets are arriving) ---
    int current_sec;
    for (current_sec = 0; current_sec < simulation_time_sec; current_sec++) {
        int incoming_packets = arrival_packets[current_sec];
        packets_dropped = 0;

        // 1. Packet Arrival and Dropping
        current_bucket_size += incoming_packets;
        
        if (current_bucket_size > bucket_capacity) {
            packets_dropped = current_bucket_size - bucket_capacity;
            current_bucket_size = bucket_capacity; // Bucket overflow; set to capacity
        }

        // 2. Packet Processing (Leaky Bucket Output)
        packets_sent = min(current_bucket_size, output_rate);
        current_bucket_size -= packets_sent;

        // 3. Print Results for the current second
        printf("%6d | %5d | %4d | %14d | %7d\n",
               current_sec + 1,
               incoming_packets,
               packets_sent,
               current_bucket_size,
               packets_dropped);
    }

    // --- Drain Loop (After all input packets have arrived) ---
    // Continue until the bucket is empty
    while (current_bucket_size > 0) {
        current_sec++;
        
        // 1. No new packets arrive (incoming_packets = 0)
        
        // 2. Packet Processing (Leaky Bucket Output)
        packets_sent = min(current_bucket_size, output_rate);
        current_bucket_size -= packets_sent;
        
        // 3. Print Results for the draining second
        printf("%6d | %5d | %4d | %14d | %7d\n",
               current_sec + 1,
               0, // No incoming packets
               packets_sent,
               current_bucket_size,
               0); // No drops in this phase since input is 0
    }

    return EXIT_SUCCESS;
}
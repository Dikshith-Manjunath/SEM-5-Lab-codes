#include <stdio.h>
#include <stdlib.h>

int min(int x, int y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

int main() {
    // --- Input Variables (Read from User) ---
    int bucket_capacity;    // Max size of the bucket (B)
    int output_rate;        // Constant output rate (R)
    int simulation_time_sec; // Number of seconds packets arrive

    // --- State Variables ---
    int current_bucket_size = 0; // Packets currently in the bucket
    int packets_dropped = 0;     // Packets dropped in a second
    int packets_sent = 0;        // Packets sent in a second

    // --- Simulation Input ---
    // Assuming inputs are read into these variables/array
    // For pure logic, we'll assume these are set by the user:
    
    // Example values (replace with actual user input via scanf)
    bucket_capacity = 10;
    output_rate = 3;
    simulation_time_sec = 5;
    int arrival_packets[] = {4, 6, 2, 5, 1}; // Packets arriving per second

    // --- Core Simulation Logic ---
    int current_sec;

    // 1. Simulation Loop (While packets are arriving)
    for (current_sec = 0; current_sec < simulation_time_sec; current_sec++) {
        int incoming_packets = arrival_packets[current_sec];
        packets_dropped = 0;

        // a. Packet Arrival and Dropping (Bucket Overflow Check)
        current_bucket_size += incoming_packets;
        
        if (current_bucket_size > bucket_capacity) {
            packets_dropped = current_bucket_size - bucket_capacity;
            current_bucket_size = bucket_capacity; // Cap at capacity
        }

        // b. Packet Processing (Constant Output)
        packets_sent = min(current_bucket_size, output_rate);
        current_bucket_size -= packets_sent;
        
        // --- Logic Checkpoints (For debugging/verification) ---
        // printf("Sec %d | In: %d | Sent: %d | Left: %d | Dropped: %d\n", 
        //         current_sec + 1, incoming_packets, packets_sent, 
        //         current_bucket_size, packets_dropped);
    }

    // 2. Drain Loop (After all input packets have arrived)
    while (current_bucket_size > 0) {
        current_sec++;
        
        // a. Packet Processing (Constant Output)
        packets_sent = min(current_bucket_size, output_rate);
        current_bucket_size -= packets_sent;
        
        // --- Logic Checkpoints (For debugging/verification) ---
        // printf("Sec %d | In: 0 | Sent: %d | Left: %d | Dropped: 0\n", 
        //         current_sec + 1, packets_sent, current_bucket_size);
    }

    return 0;
}
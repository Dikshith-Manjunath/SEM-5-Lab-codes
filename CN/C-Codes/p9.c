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
    // --- Configuration (Assumed Input Values) ---
    const int bucket_capacity = 10;
    const int output_rate = 3;
    const int simulation_time_sec = 5;
    const int arrival_packets[] = {4, 6, 2, 5, 1}; // Packets arriving per second

    // --- State Variables ---
    int current_bucket_size = 0;
    int packets_dropped = 0;
    int packets_sent = 0;
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
        
        // **********************************************
        // * PLACE LOGIC CHECKPOINTS HERE IF NEEDED *
        // **********************************************
    }

    // 2. Drain Loop (After all input packets have arrived)
    while (current_bucket_size > 0) {
        current_sec++; // Advance time
        
        // a. Packet Processing (Constant Output)
        // Note: No incoming packets or drops in this phase (incoming=0, dropped=0)
        packets_sent = min(current_bucket_size, output_rate);
        current_bucket_size -= packets_sent;
        
        // **********************************************
        // * PLACE LOGIC CHECKPOINTS HERE IF NEEDED *
        // **********************************************
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define INF 999 // Represents infinity (no direct link)

// Global arrays for costs and next-hop information
int cost[10][10]; // g: Current best cost
int via_node[10][10];    // via: Stores the next hop node index (0 to n-1)
int n;                         // n: Number of nodes

// --- Function to get initial link costs ---
void get_initial_costs() {
    printf("\nEnter the initial direct costs (use %d for no direct link):\n", INF);
    
    // Print column headers (A, B, C...)
    printf("\t");
    for (int j = 0; j < n; j++) {
        printf("%c\t", 'A' + j);
    }
    printf("\n");

    // Read the cost matrix
    for (int i = 0; i < n; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (i == j) {
                cost[i][j] = 0;
            }
        }
    }
}


// --- Core Distance Vector Logic (Bellman-Ford) ---
void run_distance_vector() {
    int i, j, k;
    
    // 1. Initialization of Next Hop (via_node)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            via_node[i][j] = i; 
        }
    }
    
    // 2. Main Relaxation Loop (runs N times to guarantee convergence)
    for (int iteration = 0; iteration < n; iteration++) {
        int changed = 0;
        
        // Loop through all possible Source Routers (i)
        for (i = 0; i < n; i++) {
            // Loop through all Intermediate Routers/Neighbors (j)
            for (j = 0; j < n; j++) {
                
                // Loop through all possible Destination Routers (k)
                for (k = 0; k < n; k++) {
                    
                    // Calculate new path cost: Cost(i -> j) + Cost(j -> k)
                    // Note: Check for INF to prevent overflow if costs are large, but usually not needed with 999
                    if (cost[i][j] != INF && cost[j][k] != INF) {
                        int new_cost = cost[i][j] + cost[j][k];

                        // Bellman-Ford Relaxation: Check if the new path is shorter
                        if (new_cost < cost[i][k]) {
                            cost[i][k] = new_cost;
                            via_node[i][k] = j;
                            changed = 1;
                        }
                    }
                }
            }
        }
        
        // Stop if no distance was updated
        if (changed == 0) {
            break; 
        }
    }
}

// --- Function to print the final routing tables ---
void print_routing_tables() {
    printf("\n--- Final Converged Routing Tables ---\n");
    for (int i = 0; i < n; i++) {
        printf("Table for Router %c:\n", 'A' + i);
        printf("Destination\tCost\tNext Hop\n");
        printf("--------------------------------\n");
        
        for (int j = 0; j < n; j++) {
            printf("%c\t\t%d\t%c\n", 
                   'A' + j, 
                   cost[i][j], 
                   'A' + via_node[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("--- Distance Vector Routing (Bellman-Ford) ---\n");
    printf("Enter the number of nodes (max %d): ", 10);
    scanf("%d", &n);

    if (n <= 0 || n > 10) {
        printf("Invalid number of nodes.\n");
        return EXIT_FAILURE;
    }

    get_initial_costs();
    
    run_distance_vector();

    print_routing_tables();

    return EXIT_SUCCESS;
}
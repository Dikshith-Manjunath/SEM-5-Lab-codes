#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS

#define MAX_NODES 10
#define INF 999 // Represents infinity (no direct link)

// Global arrays for simplicity in demonstration (used across main and functions)
int cost_matrix[MAX_NODES][MAX_NODES]; // g: Current cost matrix (distance vector)
int via_node[MAX_NODES][MAX_NODES];    // via: Stores the next hop node index (0 to n-1)
int num_nodes;                         // n: Number of nodes

/**
 * @brief Reads the initial direct costs (routing table) from the user.
 */
void get_initial_costs() {
    printf("\nEnter the initial direct costs (use %d for no direct link):\n", INF);
    
    // Print column headers
    printf("\t");
    for (int j = 0; j < num_nodes; j++) {
        printf("%c\t", 'A' + j);
    }
    printf("\n");

    // Read the matrix
    for (int i = 0; i < num_nodes; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < num_nodes; j++) {
            scanf("%d", &cost_matrix[i][j]);
            
            // Initialization: Every node's best path to itself is 0, via itself.
            if (i == j) {
                cost_matrix[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Prints the final routing table for all nodes.
 */
void print_routing_tables() {
    printf("\n--- Final Converged Routing Tables ---\n");
    for (int i = 0; i < num_nodes; i++) {
        printf("Table for Router %c (from Source %c):\n", 'A' + i, 'A' + i);
        printf("Destination\tCost\tNext Hop\n");
        printf("--------------------------------\n");
        
        for (int j = 0; j < num_nodes; j++) {
            printf("%c\t\t%d\t%c\n", 
                   'A' + j, 
                   cost_matrix[i][j], 
                   'A' + via_node[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Executes the Distance Vector Routing (Bellman-Ford) logic.
 * The core relaxation loop is run once, which is sufficient for a converged table
 * if the number of nodes (n) is the maximum diameter.
 */
void run_distance_vector() {
    int changed = 0;
    
    // Initialize via_node: Path from i to j is initially directly through i.
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            via_node[i][j] = i;
        }
    }
    
    // Distance Vector Update Loop: The algorithm guarantees convergence in at most N-1 iterations.
    // We run it N-1 times to ensure convergence, though the original code only ran it once inside a while(1) break.
    // Running it N times is safe and simple.
    for (int iteration = 0; iteration < num_nodes; iteration++) {
        changed = 0;
        
        // Loop through all possible source nodes (i)
        for (int i = 0; i < num_nodes; i++) {
            // Loop through all neighbors (j) whose table we are receiving/using
            for (int j = 0; j < num_nodes; j++) {
                // Only consider nodes j that are directly reachable from i (cost < INF)
                if (cost_matrix[i][j] < INF) {
                    // Loop through all possible destinations (k) in neighbor j's table
                    for (int k = 0; k < num_nodes; k++) {
                        
                        // Distance Vector Equation (Bellman-Ford Relaxation)
                        // New path cost from i to k via j = cost(i -> j) + cost(j -> k)
                        int new_cost = cost_matrix[i][j] + cost_matrix[j][k];

                        // If the new path is shorter than the currently known path
                        if (new_cost < cost_matrix[i][k]) {
                            cost_matrix[i][k] = new_cost; // Update cost
                            via_node[i][k] = j;           // Update next hop
                            changed = 1;
                        }
                    }
                }
            }
        }
        
        // Optimization: If no distances changed in an iteration, the algorithm has converged.
        if (changed == 0) {
            break; 
        }
    }
}

int main() {
    printf("--- Distance Vector Routing (Bellman-Ford) ---\n");
    printf("Enter the number of nodes (max %d): ", MAX_NODES);
    scanf("%d", &num_nodes);

    if (num_nodes <= 0 || num_nodes > MAX_NODES) {
        printf("Invalid number of nodes.\n");
        return EXIT_FAILURE;
    }

    get_initial_costs();
    
    // Note: The original code's single-iteration update followed by a break is simplified
    // into a standard, guaranteed-to-converge loop inside run_distance_vector().
    run_distance_vector();

    print_routing_tables();

    return EXIT_SUCCESS;
}
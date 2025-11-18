#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10
#define INF 999 // Represents infinity (no direct link)

// Global variables are minimized. All large arrays are passed via arguments.

/**
 * @brief Finds the shortest path from a single source to all other nodes using Dijkstra's algorithm.
 * * @param num_nodes The total number of nodes in the graph.
 * @param cost_matrix The adjacency matrix containing edge weights (costs).
 * @param source The starting node index.
 * @param distance The output array storing the shortest distance from the source to each node.
 * @param predecessor The output array storing the predecessor node for reconstructing the path.
 */
void dijkstra(int num_nodes, int cost_matrix[MAX_NODES][MAX_NODES], int source, int distance[], int predecessor[]) {
    int visited[MAX_NODES]; // Tracks whether a node has been included in the shortest path tree (s[])
    int current_node;       // The node selected in the current iteration (u)
    int neighbor_node;      // A neighbor node being checked (v)
    int min_dist;           // The minimum distance found in the current iteration

    // --- Initialization ---
    for (int i = 0; i < num_nodes; i++) {
        distance[i] = cost_matrix[source][i]; // Initial distance is the direct cost
        visited[i] = 0;                       // No node is visited initially
        predecessor[i] = source;              // Initial predecessor for all reachable nodes is the source
    }
    
    // The distance to the source node itself is 0, and it is marked as visited.
    visited[source] = 1;
    distance[source] = 0;

    // The main loop runs (num_nodes - 1) times to include all other nodes.
    for (int count = 1; count < num_nodes; count++) {
        min_dist = INF;
        current_node = -1;

        // 1. Find the unvisited node with the minimum distance (u)
        for (int i = 0; i < num_nodes; i++) {
            if (visited[i] == 0 && distance[i] < min_dist) {
                min_dist = distance[i];
                current_node = i;
            }
        }

        // If no reachable unvisited node is found (current_node == -1), we stop.
        if (current_node == -1) {
            return; 
        }

        // Mark the selected node as visited and include it in the Shortest Path Tree
        visited[current_node] = 1;

        // 2. Update the distances of its neighbors (Relaxation step)
        for (neighbor_node = 0; neighbor_node < num_nodes; neighbor_node++) {
            // Check only unvisited neighbors and ensure a valid edge exists
            if (visited[neighbor_node] == 0 && cost_matrix[current_node][neighbor_node] != INF) {
                
                // Relaxation Formula: distance[v] = min(distance[v], distance[u] + cost(u, v))
                if (distance[current_node] + cost_matrix[current_node][neighbor_node] < distance[neighbor_node]) {
                    distance[neighbor_node] = distance[current_node] + cost_matrix[current_node][neighbor_node];
                    predecessor[neighbor_node] = current_node; // Update the path
                }
            }
        }
    }
}

/**
 * @brief Prints the shortest path from the source to a specific destination node.
 */
void print_path(int source, int destination, const int distance[], const int predecessor[]) {
    if (distance[destination] == INF) {
        printf("Node %d is not reachable from source %d.\n", destination, source);
        return;
    }

    printf("Shortest Path to Node %d: ", destination);
    
    // Reconstruct path by tracing predecessors backward
    int path[MAX_NODES];
    int path_index = 0;
    int current = destination;
    
    while (current != source) {
        path[path_index++] = current;
        current = predecessor[current];
    }
    path[path_index++] = source; // Add the source node

    // Print the path in the correct order (Source -> Destination)
    for (int i = path_index - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) {
            printf(" -> ");
        }
    }
    
    printf(" (Total Cost: %d)\n", distance[destination]);
}

int main() {
    int cost_matrix[MAX_NODES][MAX_NODES];
    int num_nodes, source_node;
    int distance[MAX_NODES];   // Shortest distance from source to node i
    int predecessor[MAX_NODES]; // Predecessor of node i on the shortest path

    printf("--- Dijkstra's Algorithm: Shortest Path ---\n");
    printf("Enter the number of nodes (max %d): ", MAX_NODES);
    scanf("%d", &num_nodes);

    if (num_nodes <= 0 || num_nodes > MAX_NODES) {
        printf("Invalid number of nodes.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the cost matrix (use %d for no direct link):\n", INF);
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            scanf("%d", &cost_matrix[i][j]);
            // Ensure cost to self is 0
            if (i == j) {
                cost_matrix[i][j] = 0;
            }
        }
    }

    printf("Enter the source node index (0 to %d): ", num_nodes - 1);
    scanf("%d", &source_node);
    
    if (source_node < 0 || source_node >= num_nodes) {
        printf("Invalid source node.\n");
        return EXIT_FAILURE;
    }

    // Run Dijkstra's Algorithm
    dijkstra(num_nodes, cost_matrix, source_node, distance, predecessor);

    printf("\n--- Results from Source Node %d ---\n", source_node);
    
    // Print results for all nodes
    for (int dest_node = 0; dest_node < num_nodes; dest_node++) {
        if (source_node != dest_node) {
            print_path(source_node, dest_node, distance, predecessor);
        }
    }

    return EXIT_SUCCESS;
}
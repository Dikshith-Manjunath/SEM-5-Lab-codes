#include <stdio.h>
#include <stdlib.h>

#define INF 999 // Represents infinity (no direct link)

// Arrays used by the algorithm
int cost[10][10];
int dis[10];   // Shortest distance from source to node i
int pre[10]; // predecessor of node i on the shortest path
int n;

/**
 * @brief Finds the shortest path from a single source to all other nodes.
 */
void dijkstra(int s) {
    int visited[10] = {0}; // Tracks nodes included in the Shortest Path Tree
    int cur;
    int min_dist;

    // --- 1. Initialization ---
    for (int i = 0; i < n; i++) {
        dis[i] = cost[s][i];
        pre[i] = s;
    }

    visited[s] = 1;
    dis[s] = 0;

    // --- 2. Main Loop (N-1 iterations) ---
    for (int count = 1; count < n; count++) {
        min_dist = INF;
        cur = -1;

        // Find the unvisited node with the minimum dis (cur)
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0 && dis[i] < min_dist) {
                min_dist = dis[i];
                cur = i;
            }
        }

        // If no reachable unvisited node exists, exit
        if (cur == -1) {
            break;
        }

        // Mark the selected node as visited
        visited[cur] = 1;

        // --- 3. Relaxation Step ---
        for (int ne = 0; ne < n; ne++) {
            // Check unvisited nes with a valid edge from cur
            if (visited[ne] == 0 && cost[cur][ne] != INF) {
                
                // Relaxation: Update dis if a shorter path is found
                if (dis[cur] + cost[cur][ne] < dis[ne]) {
                    dis[ne] = dis[cur] + cost[cur][ne];
                    pre[ne] = cur; // Update the path
                }
            }
        }
    }
}

/**
 * @brief Prints the shortest path from source to destination.
 */
void print_path(int source, int destination) {
    if (dis[destination] == INF) {
        printf("Node %d is unreachable.\n", destination);
        return;
    }

    // Reconstruct path by tracing pres backward
    int path[10];ne
    int path_index = 0;
    int current = destination;
    
    while (current != source) {
        path[path_index++] = current;
        current = pre[current];
    }
    path[path_index++] = source;

    printf("Path to %d (Cost: %d): ", destination, dis[destination]);
    
    // Print the path in the correct order (Source -> Destination)
    for (int i = path_index - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\n");
}

int main() {
    int source_node;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter cost matrix (use %d for INF):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (i == j) {
                cost[i][j] = 0;
            }
        }
    }

    printf("Enter source node (0 to %d): ", n - 1);
    scanf("%d", &source_node);

    // Run Algorithm
    dijkstra(source_node);

    // Output Results
    printf("\n--- Shortest Paths from Node %d ---\n", source_node);
    for (int dest_node = 0; dest_node < n; dest_node++) {
        if (source_node != dest_node) {
            print_path(source_node, dest_node);
        }
    }

    return 0;
}
/*
Problem:
A transportation network contains cities connected by roads with different
costs. Implement Dijkstra's Shortest Path Algorithm using a weighted
adjacency matrix. Accept the number of vertices, matrix, and source vertex.
Compute and display the minimum distance from the source to every vertex.

Notes:
- Vertices are numbered from 1 to n.
- Enter 0 when there is no direct road between two different vertices.
- All edge weights must be non-negative.
*/

#include <stdio.h>

#define MAX 100
#define INF 1000000000

int main(void) {
    int graph[MAX][MAX];
    int distance[MAX];
    int visited[MAX] = {0};
    int n, source, i, j;
    int minDistance, current, nextVertex;

    printf("Enter number of vertices (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter the weighted adjacency matrix (%d x %d):\n", n, n);
    printf("Use 0 for no direct road and non-negative weights for roads.\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                printf("Invalid matrix input. Weights must be non-negative.\n");
                return 1;
            }
        }
    }

    printf("Enter source vertex (1-%d): ", n);
    if (scanf("%d", &source) != 1 || source < 1 || source > n) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    // Initialize distances: source is 0, all others are infinity.
    for (i = 0; i < n; i++)
        distance[i] = INF;
    distance[source - 1] = 0;

    // Select the unvisited vertex with the smallest known distance.
    for (i = 0; i < n - 1; i++) {
        minDistance = INF;
        current = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                current = j;
            }
        }

        // Remaining vertices are unreachable from the source.
        if (current == -1)
            break;

        visited[current] = 1;

        // Relax all edges leaving the selected vertex.
        for (nextVertex = 0; nextVertex < n; nextVertex++) {
            if (!visited[nextVertex] &&
                graph[current][nextVertex] > 0 &&
                distance[current] != INF &&
                distance[current] + graph[current][nextVertex] <
                    distance[nextVertex]) {
                distance[nextVertex] =
                    distance[current] + graph[current][nextVertex];
            }
        }
    }

    printf("\nShortest distances from source vertex %d:\n", source);
    printf("Destination\tShortest Distance\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t", i + 1);

        if (distance[i] == INF)
            printf("Unreachable\n");
        else
            printf("%d\n", distance[i]);
    }

    return 0;
}

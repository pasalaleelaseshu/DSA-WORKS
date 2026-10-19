/*
Problem:
A network of n locations is represented as a graph. Accept the graph using
an adjacency matrix, accept a starting vertex, perform a graph traversal,
display the visit order, and ensure that a vertex is not processed repeatedly.
Test with connected and partially connected graphs.

This program uses Breadth-First Search (BFS).
Vertices are numbered from 1 to n.
*/

#include <stdio.h>

#define MAX 100

int main(void) {
    int graph[MAX][MAX];
    int visited[MAX] = {0};
    int queue[MAX];
    int n, start, i, j;
    int front = 0, rear = 0;
    int current, foundAny = 0;

    printf("Enter number of vertices (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter the adjacency matrix (%d x %d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1) {
                printf("Invalid matrix input.\n");
                return 1;
            }
        }
    }

    printf("Enter starting vertex (1-%d): ", n);
    if (scanf("%d", &start) != 1 || start < 1 || start > n) {
        printf("Invalid starting vertex.\n");
        return 1;
    }

    // Mark a vertex visited when it is enqueued to prevent duplicates.
    visited[start - 1] = 1;
    queue[rear++] = start - 1;

    printf("\nBFS visit order: ");

    while (front < rear) {
        current = queue[front++];
        printf("%d ", current + 1);
        foundAny = 1;

        for (j = 0; j < n; j++) {
            if (graph[current][j] != 0 && !visited[j]) {
                visited[j] = 1;
                queue[rear++] = j;
            }
        }
    }

    if (!foundAny)
        printf("No vertices visited.");

    printf("\n");

    // Any unvisited vertices are not reachable from the chosen start.
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Vertex %d is not reachable from vertex %d.\n",
                   i + 1, start);
        }
    }

    return 0;
}

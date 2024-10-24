#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100000

// Graph structure with adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Function to create a node
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    return graph;
}

// Function to add edge
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to check if all vertices in the current clique are adjacent to vertex v
bool isClique(int b[MAX], Graph* graph, int bLen) {
    for (int i = 0; i < bLen; i++) {
        Node* temp = graph->adjLists[b[i]];
        bool found = false;
        while (temp) {
            if (temp->vertex == b[bLen]) {
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found)
            return false;
    }
    return true;
}

// Recursive function to find maximum clique
int maxCliqueUtil(Graph* graph, int i, int l, int b[MAX], int maxSize) {
    for (int j = i + 1; j < graph->numVertices; j++) {
        b[l] = j;
        if (isClique(b, graph, l)) {
            if (l + 1 > maxSize) 
                maxSize = l + 1;
            maxSize = maxCliqueUtil(graph, j, l + 1, b, maxSize);
        }
    }
    return maxSize;
}

// Function to find the size of the maximum clique
int maxClique(Graph* graph) {
    int b[MAX], maxSize = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        b[0] = i;
        maxSize = maxCliqueUtil(graph, i, 1, b, maxSize);
    }
    return maxSize;
}

// Main function to test the graph
int main() {
    int u, v, n, m;
    scanf("%d %d", &u, &v);
    Graph* graph = createGraph(u);
    for (int i = 0; i < v; i++){
        scanf("%d %d", &n, &m);
        addEdge(graph, n, m);
    }

    printf("%d\n", maxClique(graph));

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct node {
    int vertex;
    int weight;
    struct node* next;
} node_t;

typedef struct graph {
    int numVertices;
    node_t** adjLists;
} graph_t;

//* Function to create a node
node_t* createNode(int vertex, int weight) {
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//* Function to create a graph
graph_t* createGraph(int vertices) {
    graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
    graph->numVertices = vertices;

    graph->adjLists = (node_t**)malloc(vertices * sizeof(node_t*));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

//* Function to add an edge to the graph
void addEdge(graph_t* graph, int src, int dest, int weight) {
    //* Add edge from src to dest
    node_t* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    //* Add edge from dest to src (the graph is undirected)
    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

//* Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

//* Dijkstra's algorithm using adjacency list
int dijkstra(graph_t* graph, int src, int end) {
    int V = graph->numVertices;
    int dist[V];     //* Array to store the shortest distance from the source to each vertex
    bool visited[V]; //* Array to track visited vertices

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    //* Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);

        visited[u] = true;

        node_t* adjList = graph->adjLists[u];
        while (adjList != NULL) {
            int v = adjList->vertex;
            int weight = adjList->weight;

            //* Update dist[v] only if it's not yet visited, and the total weight of the path
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
            adjList = adjList->next;
        }
    }
    //* return -1 if no path from source to end
    return dist[end] == INT_MAX ? -1: dist[end];
}

int main() {
    int n, m, p;
    int u, v, w;
    int s, t;

    scanf("%d %d %d", &n, &m, &p);
    graph_t* graph = createGraph(n);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(graph, u, v, w);
    }

    for (int i = 0; i < p; i++) {
        scanf("%d %d", &s, &t);
        printf("%d\n", dijkstra(graph, s, t));
    }
    return 0;
}

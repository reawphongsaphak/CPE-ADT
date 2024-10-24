#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj[MAXN];
int visited[MAXN];
int discovery[MAXN];
int low[MAXN];
int parent[MAXN];
int articulation_point[MAXN];
int time_counter;

void add_edge(int u, int v) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void dfs(int u) {
    visited[u] = 1;
    discovery[u] = low[u] = ++time_counter;
    int children = 0;

    Node* current = adj[u];
    while (current != NULL) {
        int v = current->vertex;

        if (!visited[v]) {
            children++;
            parent[v] = u;
            dfs(v);

            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            if (parent[u] == -1 && children > 1) {
                articulation_point[u] = 1;
            }

            if (parent[u] != -1 && low[v] >= discovery[u]) {
                articulation_point[u] = 1;
            }
        } else if (v != parent[u]) {
            if (discovery[v] < low[u]) {
                low[u] = discovery[v];
            }
        }

        current = current->next;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(adj, 0, sizeof(adj));
    memset(visited, 0, sizeof(visited));
    memset(parent, -1, sizeof(parent));
    memset(articulation_point, 0, sizeof(articulation_point));

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    time_counter = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (articulation_point[i]) {
            if (found) printf(" ");
            printf("%d", i);
            found = 1;
        }
    }

    if (!found) {
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        Node* current = adj[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}

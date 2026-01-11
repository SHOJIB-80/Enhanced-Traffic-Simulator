#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXV 100
#define MAXP 10
#define INF INT_MAX

typedef struct Edge {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Vertex {
    Edge* head;
} Vertex;

typedef struct Graph {
    int V;
    Vertex* array;
} Graph;

// Create and initialize a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (Vertex*)malloc(V * sizeof(Vertex));
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;
}

// Add a directed edge from src to dest with given weight
void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->dest = dest;
    edge->weight = weight;
    edge->next = graph->array[src].head;
    graph->array[src].head = edge;
}

typedef struct {
    int v;
    int dist;
} HeapNode;

typedef struct {
    int size;
    HeapNode heap[MAXV];
} MinHeap;

// Initialize the min heap
void heapInit(MinHeap* h) {
    h->size = 0;
}

// Insert a node into the min heap
void heapPush(MinHeap* h, int v, int dist) {
    int i = h->size++;
    while (i > 0 && h->heap[(i - 1) / 2].dist > dist) {
        h->heap[i] = h->heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->heap[i].v = v;
    h->heap[i].dist = dist;
}

// Remove and return the minimum distance node from heap
HeapNode heapPop(MinHeap* h) {
    HeapNode root = h->heap[0];
    HeapNode last = h->heap[--h->size];

    int i = 0;
    while (2 * i + 1 < h->size) {
        int child = 2 * i + 1;
        if (child + 1 < h->size &&
            h->heap[child + 1].dist < h->heap[child].dist)
            child++;
        if (last.dist <= h->heap[child].dist)
            break;
        h->heap[i] = h->heap[child];
        i = child;
    }
    h->heap[i] = last;
    return root;
}

int D[MAXV][MAXP];
int parent[MAXV][MAXP];
int pathCount[MAXV];

int N, S, T;

//  Dijkstra algorithm to find multiple shortest paths
void dijkstra(Graph* graph) {
    for (int i = 0; i < N; i++) {
        pathCount[i] = 0;
        for (int j = 0; j < MAXP; j++) {
            D[i][j] = INF;
            parent[i][j] = -1;
        }
    }

    D[S][0] = 0;
    pathCount[S] = 1;

    MinHeap heap;
    heapInit(&heap);
    heapPush(&heap, S, 0);

    while (heap.size > 0) {
        HeapNode node = heapPop(&heap);
        int u = node.v;

        Edge* e = graph->array[u].head;
        while (e) {
            int v = e->dest;
            int w = e->weight;

            for (int p = 0; p < pathCount[u]; p++) {
                int newDist = D[u][p] + w;

                if (newDist < D[v][0]) {
                    for (int k = MAXP - 1; k > 0; k--) {
                        D[v][k] = D[v][k - 1];
                        parent[v][k] = parent[v][k - 1];
                    }
                    D[v][0] = newDist;
                    parent[v][0] = u;
                    pathCount[v] = 1;
                    heapPush(&heap, v, newDist);
                }
                else if (newDist == D[v][0] && pathCount[v] < MAXP) {
                    D[v][pathCount[v]] = newDist;
                    parent[v][pathCount[v]] = u;
                    pathCount[v]++;
                }
            }
            e = e->next;
        }
    }
}

// Print intermediate nodes of a shortest path
void printPath(int v, int p) {
    if (parent[v][p] == -1)
        return;
    printPath(parent[v][p], 0);
    if (parent[v][p] != S)
        printf("%d ", parent[v][p]);
}

// Main function for input, run Dijkstra, output results
int main() {
    int E;

    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &N, &E);

    Graph* graph = createGraph(N);

    printf("Enter each edge in format (u v w):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(graph, u, v, w);
    }

    printf("Enter source and destination node: ");
    scanf("%d %d", &S, &T);

    dijkstra(graph);

    printf("Minimum distance: %d\n", D[T][0]);
    printf("Number of shortest paths: %d\n", pathCount[T]);

    for (int i = 0; i < pathCount[T]; i++) {
        printf("Path %d intermediate nodes: ", i + 1);
        printPath(T, i);
        printf("\n");
    }

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>

// #define MAX_VERTICES 100

// // Structure to represent a node in adjacency list
// struct Node {
//     int vertex;
//     struct Node* next;
// };

// // Structure to represent the graph
// struct Graph {
//     int V; // Number of vertices
//     struct Node* adjList[MAX_VERTICES]; // Array of adjacency lists
// };

// // Function to create a new node
// struct Node* createNode(int v) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->vertex = v;
//     newNode->next = NULL;
//     return newNode;
// }

// // Function to create a graph with V vertices
// struct Graph* createGraph(int V) {
//     struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
//     graph->V = V;
//     for (int i = 0; i < V; i++) {
//         graph->adjList[i] = NULL;
//     }
//     return graph;
// }

// // Function to add an edge between two vertices
// void addEdge(struct Graph* graph, int src, int dest) {
//     struct Node* newNode = createNode(dest);
//     newNode->next = graph->adjList[src];
//     graph->adjList[src] = newNode;

//     newNode = createNode(src);
//     newNode->next = graph->adjList[dest];
//     graph->adjList[dest] = newNode;
// }

// // DFS function to find connected components
// void DFS(struct Graph* graph, int v, bool visited[]) {
//     visited[v] = true;
//     // printf("%d ", v);

//     struct Node* temp = graph->adjList[v];
//     while (temp!=NULL) {
//         int adjVertex = temp->vertex;
//         if (!visited[adjVertex]) {
//             DFS(graph, adjVertex, visited);
//         }
//         temp = temp->next;
//     }
// }

// // Function to find the number of connected components
// int noOfConnectedComponents(struct Graph* graph) {
//     bool visited[MAX_VERTICES] = {false};
//     int count = 0;

//     for (int v = 0; v < graph->V; v++) {
//         if (!visited[v]) {
//             DFS(graph, v, visited);
//             count++;
            
//         }
//         // printf("\n");
//     }

//     return count;
// }

// // Function to find the size of each connected component
// void sizeOfComponents(struct Graph* graph, int componentSizes[]) {
//     bool visited[MAX_VERTICES] = {false};
//     int count = 0;

//     for (int v = 0; v < graph->V; v++) {
//         if (!visited[v]) {
//             int size = 0;
//             DFS(graph, v, visited);
//             for (int i = 0; i < graph->V; i++) {
//                 if (visited[i]) {
//                     size++;
//                     visited[i] = false;
//                 }
//             }
//             componentSizes[count++] = size;
//         }
//     }
// }

// // Function to find the number of bridges
// int noOfBridgesUtil(struct Graph* graph, int u, bool visited[], int disc[], int low[], int parent) {
//     static int bridgeCount = 0;
//     visited[u] = true;
//     disc[u] = low[u] = ++bridgeCount;

//     struct Node* temp = graph->adjList[u];
//     while (temp) {
//         int v = temp->vertex;
//         if (!visited[v]) {
//             noOfBridgesUtil(graph, v, visited, disc, low, u);
//             low[u] = low[u] < low[v] ? low[u] : low[v];
//             if (low[v] > disc[u]) {
//                 bridgeCount++;
//             }
//         } else if (v != parent) {
//             low[u] = low[u] < disc[v] ? low[u] : disc[v];
//         }
//         temp = temp->next;
//     }
//     return bridgeCount;
// }

// int noOfBridges(struct Graph* graph) {
//     bool visited[MAX_VERTICES] = {false};
//     int disc[MAX_VERTICES] = {0};
//     int low[MAX_VERTICES] = {0};

//     return noOfBridgesUtil(graph, 0, visited, disc, low, -1);
// }

// // Function to find the number of articulation points
// int noOfArticulationPointsUtil(struct Graph* graph, int u, bool visited[], int disc[], int low[], int parent, int* articulationPointCount) {
//     static int time = 0;
//     visited[u] = true;
//     disc[u] = low[u] = ++time;

//     int children = 0;
//     struct Node* temp = graph->adjList[u];
//     while (temp) {
//         int v = temp->vertex;
//         if (!visited[v]) {
//             children++;
//             noOfArticulationPointsUtil(graph, v, visited, disc, low, u, articulationPointCount);
//             low[u] = low[u] < low[v] ? low[u] : low[v];
//             if (low[v] >= disc[u] && parent != -1) {
//                 *articulationPointCount += 1;
//             }
//         } else if (v != parent) {
//             low[u] = low[u] < disc[v] ? low[u] : disc[v];
//         }
//         temp = temp->next;
//     }

//     if (parent == -1 && children > 1) {
//         *articulationPointCount += 1;
//     }

//     return *articulationPointCount;
// }

// int noOfArticulationPoints(struct Graph* graph) {
//     bool visited[MAX_VERTICES] = {false};
//     int disc[MAX_VERTICES] = {0};
//     int low[MAX_VERTICES] = {0};
//     int articulationPointCount = 0;

//     return noOfArticulationPointsUtil(graph, 0, visited, disc, low, -1, &articulationPointCount);
// }

// // Driver function

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
# define MAX 100
void DFS(int v, int visited[], int adjMatrix[][MAX], int n){
    visited[v] = 1;
    for (int i = 0; i < n; i++){
        if (visited[adjMatrix[v][i]] == 0){
            DFS(i, visited, adjMatrix, n);
        }
    }
}
int noOfConnectedComponents(int adjMatrix[][MAX], int n){
    int visited[MAX] = {0};
    int count = 0;
    for (int v = 0; v < n; v++){
        if (!visited[v]){
            DFS(v, visited, adjMatrix, n);
            count++;
        }
    }
    return count;
}
int main() {
    int m;
    scanf("%d", &m); // Read the number of nodes

    // struct Graph* graph = createGraph(m);
    char menu;
    int v, w;
    bool visited[MAX] = {false};
    int adjMatrix[MAX][MAX];
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            adjMatrix[i][j] = -1;
        }
    }
    while(m--){
        int v,w;
        scanf("%d", &v);
        int x=0;
        while(scanf("%d", &w) && w == 1){
            adjMatrix[v-1][x] = v-1;
            x++;
            if(getchar() == '\n'){
                break;
            }
        }
    }
    printf("%d\n", noOfConnectedComponents(adjMatrix, m));
    // while (scanf(" %c", &menu) != EOF) {
    //     if (menu == 'n') {
    //         // Find number of connected components
    //         int connectedComponents = noOfConnectedComponents(graph);
    //         printf("%d\n", connectedComponents);
    //     } else if (menu == 's') {
    //         // Find size of each connected component
    //         int componentSizes[MAX] = {0};
    //         sizeOfComponents(graph, componentSizes);
    //         for (int i = 0; i < MAX_VERTICES; i++) {
    //             if (componentSizes[i] != 0) {
    //                 printf("%d ", componentSizes[i]);
    //             }
    //         }
    //         printf("\n");
    //         } else if (menu == 'b') {
    //             int bridges = noOfBridges(graph);
    //             printf("%d\n", bridges == 0 ? -1 : bridges);
    //         } else if (menu == 'a') {
    //             int articulationPoints = noOfArticulationPoints(graph);
    //             printf("%d\n", articulationPoints == 0 ? -1 : articulationPoints);
    //         } else if (menu == 't') {
    //             break;
    //         }
    //     }
    
    return 0;
}
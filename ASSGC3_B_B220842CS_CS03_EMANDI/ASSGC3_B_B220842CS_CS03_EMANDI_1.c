#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 1000
int minkey(int key[], int vis[], int V) {
    int min = INT_MAX;
    int mindex = -1; // Initialize mindex to -1
    for(int i = 0; i < V; i++) {
        if(vis[i] == 0 && key[i] < min) {
            min = key[i];
            mindex = i;
        }
    }
    // printf("%d\n", mindex);
    return mindex;
}

void primMST(int graph[][MAX], int V, int src, int *sum) {
    
    int parent[V];
    int key[V];
    int vis[V];
    for(int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        vis[i] = 0;
    }
    key[src] = 0;
    parent[src] = -1;
    
    for(int count = 0; count < V - 1; count++) {
        int u = minkey(key, vis, V);
        vis[u] = 1;
        // printf("u=%d\n", u);
        int x;
        for(int v = 0; v < V; v++) {
            // printf("%d %d %d %d\n", u, v, graph[u][v], key[v]);
            if(graph[u][v] && vis[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
                
                // printf("%d %d ",v,u);
                
            }
        }
        
    }
    for(int i = 0; i < V; i++) {
                
        *sum += key[i];
    }
    printf("%d\n",*sum);
    int minnn=10000;
    int min_i;
    int done[1001];
    for(int i=0;i<V;i++){
        done[i]=0;
    }
    done[src]=1;
    for(int i=0;i<V-1;i++){
        // for(int k=0;k<V;k++)
            // printf("%d ",done[k]);
        // printf("\n");
        for(int j=0;j<V;j++){
            if(done[j]==0 && minnn>key[j]){
                minnn=key[j];
                min_i=j;
            }
        }
        done[min_i]=1;
        minnn=10000;
        printf("%d %d ",parent[min_i],min_i);
    }
}
int main() {
    int V;
    scanf("%d", &V);
    int temp=V;
    // printf("%d\n", V);
    int graph[V][MAX];
    // int maxWeight = 0;
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
            // maxWeight=maxWeight>graph[i][j]?maxWeight:graph[i][j];
        }
    }
    // printf("gg%d\n", V);
    char c[4];
    scanf("%s", c);
    scanf("%s", c);
    // printf("gg%d\n", V);
    int src = c[2] - '0'; // Convert char to int
    // printf("%d\n", src); 
    
    
    int sum = 0;
    
    scanf("%s",c);
    primMST(graph, temp, src, &sum);
    
    // printf("%d\n", sum);
    return 1;
}

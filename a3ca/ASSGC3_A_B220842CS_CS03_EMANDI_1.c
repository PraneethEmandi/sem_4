#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 100

// DFS function to find connected components
void DFS(int adj[][MAX_VERTICES], int v, int *visited, int n){
    visited[v] = 1;
    for(int i = 0; i < n; i++){
        if(adj[v][i] != -1){
            if(visited[adj[v][i]] == 0){
                
                DFS(adj,adj[v][i], visited, n);
            }
        }
    }
}
void DFS_size(int adj[][MAX_VERTICES], int v, int *visited, int n, int *count){
    visited[v] = 1;
    for(int i = 0; i < n; i++){
        if(adj[v][i] != -1){
            if(visited[adj[v][i]] == 0){
                (*count) ++;
                DFS_size(adj,adj[v][i], visited, n, count);
                
            }
        }
    }
}
void DFS_AP(int adj[][100], int v, int *visited, int deleted, int n){
    visited[v] = 1;
    for(int i = 0; i < n; i++){
        if(adj[v][i] != -1){
            if(adj[v][i] != deleted){
                if(visited[adj[v][i]] == 0){
                    DFS_AP(adj, adj[v][i], visited, deleted, n);
                }
            }
        }
    }
}

void size_of_components(int n, int adj[][100]){
    int visited[MAX_VERTICES];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    int counts[MAX_VERTICES];
    for(int i = 0; i < n; i++){
        counts[i] = -1;
    }
    for(int i = 0; i < n; i++){
        int count = 1;
        if(visited[i] == 0){
            DFS_size(adj, i, visited, n, &count);
            counts[i] = count;
        }
    }

    for(int i = 0; i < n; i++){
        if(counts[i] != -1){
            printf("%d ",counts[i]);
        }
    }
    printf("\n");
}

int noOfConnectedComponents(int n, int adj[][MAX_VERTICES]){
    int visited[MAX_VERTICES];
    int count = 0;
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    for(int i = 0; i < n; i++){
        if(visited[i] == 0){
            int c = 0;
            DFS(adj,i,visited,n);
            count ++;
        }
    }
    return count;
}

int articulate_points(int n, int adj[][100], int x){
    int count = 0;
    for(int i = 0; i < n; i++){
        int visited[n];
        for(int i = 0; i < n; i++){
            visited[i] = 0;
        }
        int components = 0;
        for(int j = 0; j < n; j++){
            if(i != j){
                if(visited[j] == 0){
                    components++;
                    DFS_AP(adj, j, visited, i, n);
                }
            }
        }
        if(components > x){
            count++;
        }
    }
    return count;
}

int find_bridges(int n, int adj[][100]){
    int initial = noOfConnectedComponents(n, adj);
    int bridges = 0;
    int temp1, temp2;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(adj[i][j] != -1){
                temp1 = adj[i][j];
                adj[i][j] = -1;
                int newcomponents = noOfConnectedComponents(n, adj);
                if(newcomponents > initial){
                    bridges++;
                }
            }
            adj[i][j] = temp1;
        }
    }
    return bridges;
}

int main(){
    int n;
    scanf("%d",&n);
    int adj[100][100];
    int visited[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            adj[i][j] = -1;
        }
    }
    for(int i = 0; i < n; i++){
        int index;
        int v;
        scanf("%d",&index);
        int k = 0;
        while(scanf("%d",&v) == 1){
            adj[index-1][k] = v - 1;
            k++;
            if(getchar() == '\n'){
                break;
            }
        }
    }
    char call;
    int count;
    while(1){
        scanf("%c", &call);
        if(call == 't'){
            return 1;
        }
        else if(call == 'n'){
            count = noOfConnectedComponents(n, adj);
            printf("%d\n",count);
        }
        else if(call == 's'){
            size_of_components(n, adj);
        }
        else if(call == 'b'){
            printf("%d\n", find_bridges(n, adj));
        }
        else if(call == 'a'){
            int x = noOfConnectedComponents(n, adj);
            printf("%d\n",articulate_points(n, adj, x));
        }
    }

    return 1;
}
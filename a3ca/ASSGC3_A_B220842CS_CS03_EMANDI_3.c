#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void DFS(int source, int destination, int path[], int pathlen, int*  visited, int graph[][100], int* found){
    visited[source] = 1;
    path[pathlen++] = source;

    if(source == destination){
        (*found) = 1;
        for(int i = 0; i < pathlen; i++){
            printf("%d ",path[i]);
        }
        printf("\n");
    }
    else{
        for(int i = 0; graph[source][i] != -1; i++){
            int v = graph[source][i];
            if(!visited[v]){
                DFS(v, destination, path, pathlen, visited, graph, found);
            }
        }
    }
    visited[source] = 0;
}

void allPaths(int source, int destination, int* visited, int graph[][100]){
    int path[1000];
    int found = 0;
    DFS(source, destination, path, 0, visited, graph, &found);
    if(found == 0){
        printf("-1\n");
    }
}

int isCyclic(int n, int graph[][100], int *visited, int v, int parent){
    visited[v] = 1;
    for(int i = 0; graph[v][i] != -1; i++){
        if(visited[graph[v][i]] == 0){
            if(isCyclic(n, graph, visited, graph[v][i], v)){
                return 1;
            }
        }
        else if(graph[v][i] != parent){
            return 1;
        }
    }
    return 0;
}

int isValid(int n, int graph[][100]){
    int visited[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    if(isCyclic(n, graph, visited, 0, -1)){
        return -1;
    }
    for(int i = 0; i < n; i++){
        if(visited[i] == 0){
            return -1;
        }
    }
    return 1;
}

int main(){
    int n;
    scanf("%d",&n);
    int graph[n][100];
    int visited[n];
    memset(visited, 0, sizeof(visited));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 100; j++){
            graph[i][j] = -1;
        }
    }

    for(int i = 0; i < n; i++){
        int index;
        int v;
        scanf("%d",&index);
        int k = 0;
        if(getchar() == '\n'){
            continue;
        }
        while(scanf("%d",&v) == 1){
            graph[index][k] = v;
            k++;
            if(getchar() == '\n'){
                break;
            }
        }
    }

    int source,destination;
    char call;
    while(1){
        scanf("%c",&call);
        if(call == 'x'){
            return 1;
        }
        else if(call == 'a'){
            scanf("%d",&source);
            scanf("%d",&destination);
            allPaths(source, destination, visited, graph);
        }
        else if(call == 't'){
            printf("%d\n",isValid(n, graph));
        }
    }
}
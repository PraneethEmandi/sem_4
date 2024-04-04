#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int minDistance(int dist[], int vis[], int V) {
    int min = INT_MAX;
    int mindex = -1;
    for(int i = 1; i <= V; i++) {
        if(vis[i] == 0 && dist[i] < min) {
            min = dist[i];
            mindex = i;
        }
    }
    return mindex;
}
void dijkstra(int V,int graph[V+1][V+1], int edgeWeight[V+1][V+1],int src){
    int dist[V+1];
    int vis[V+1];
    for(int i=1;i<=V;i++){
        dist[i]=INT_MAX;
        vis[i]=0;
    }
    dist[src]=0;
    for(int i=1;i<=V;i++){
        int u=minDistance(dist,vis,V);
        vis[u]=1;
        for(int j=1;j<=V;j++){
            if(graph[u][j]!=0){
                if(dist[graph[u][j]]>dist[u]+edgeWeight[u][j]){
                    dist[graph[u][j]]=dist[u]+edgeWeight[u][j];
                }
            }
        }
    }
    for(int i=1;i<=V;i++){
        printf("%d ",dist[i]);
    }
}
int main(){
    int V;
    scanf("%d", &V);
    int graph[V+1][V+1];
    int u,v;
    for(int i=1;i<=V;i++){
        for(int j=1;j<=V;j++){
            graph[i][j]=0;
        }
    }
    for(int i=1;i<=V;i++){
        scanf("%d",&u);
        int k=1;
        while(scanf("%d",&v)==1){
            graph[u][k++]=v;
            if(getchar()=='\n')
                break;
        }
    }
    int edgeWeight[V+1][V+1];
    for(int i=1;i<=V;i++){
        scanf("%d",&u);
        int k=1;
        while(scanf("%d",&v)==1){
            edgeWeight[u][k++]=v;
            if(getchar()=='\n')
                break;
        }
    }
    for(int i=1;i<=V;i++){
        for(int j=1;j<=V;j++){
            if(graph[i][j]!=0)
            printf("%d ",graph[i][j]);
        }
        printf("\n");
    }
    for(int i=1;i<=V;i++){
        for(int j=1;j<=V;j++){
            if(graph[i][j]!=0)
            printf("%d ",edgeWeight[i][j]);
        }
        printf("\n");
    }
    int src;
    scanf("%d",&src);
    dijkstra(V,graph,edgeWeight,src);
    // printf("%d\n",dijkstra(V,graph,edgeWeight));
}
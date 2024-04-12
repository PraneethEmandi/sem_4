#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define vmax 100
int minDis(int dis[],int vis[],int n){
    int min=INT_MAX;
    int index=-1;
    for(int i=0;i<n;i++){
        if(vis[i]==0 && dis[i]<min){
            min=dis[i];
            index=i;
        }
    }
    return index;
}
int dijkstra(int adj[][vmax],int weight[][vmax],int src,int n){
    int vis[vmax]={0};
    int dis[vmax];
    for(int i=0;i<n;i++){
        dis[i]=INT_MAX;
    }
    dis[src]=0;
    for(int i=0;i<n;i++){
        int index=minDis(dis,vis,n);
        vis[index]=1;
        for(int j=0;j<n;j++){
            if(adj[index][j]!=-1){
                if(dis[adj[index][j]]>dis[index]+weight[index][j]){
                    dis[adj[index][j]]=dis[index]+weight[index][j];
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%d ",dis[i]);
    }
    printf("\n");
}
int main(){
    int n;
    scanf("%d",&n);
    int adj[n][vmax];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j]=-1;
        }
    }
    for(int i=0;i<n;i++){
        int u,v;
        scanf("%d",&u);
        u--;
        int k=0;
        while(scanf("%d",&v)==1){
            adj[u][k++]=v-1;
            if(getchar()=='\n')
                break;
        }
    }
    int weight[n][vmax];
    for(int i=0;i<n;i++){
        int u,v;
        scanf("%d",&u);
        u--;
        int k=0;
        while(scanf("%d",&v)==1){
            weight[u][k++]=v;
            if(getchar()=='\n')
                break;
        }
    }
    int src;
    scanf("%d",&src);
    dijkstra(adj,weight,src-1,n);
    
}
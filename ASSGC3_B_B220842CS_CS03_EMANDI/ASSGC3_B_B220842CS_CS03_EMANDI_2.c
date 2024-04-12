#include <stdio.h>
#include <stdlib.h>
struct DisjointSet{
    int *size;
    int *parent;
};
typedef struct DisjointSet* DisjointSet;
DisjointSet create(int n){
    DisjointSet ds=(DisjointSet)malloc(sizeof(struct DisjointSet));
    ds->size=(int*)calloc(n,sizeof(int));
    ds->parent=(int*)malloc((n)*sizeof(int));
    for(int i=0;i<n;i++){
        ds->parent[i]=i;
        ds->size[i]=1;
    }
    return ds;
}
int find(DisjointSet ds,int node){
    if(node==ds->parent[node]){
        return node;
    }
    return ds->parent[node]=find(ds,ds->parent[node]);
}
void Union(DisjointSet ds,int u,int v){
    int ulp_u=find(ds,u);
    int ulp_v=find(ds,v);
    if(ulp_u==ulp_v)
        return;
    if(ds->size[ulp_u]<ds->size[ulp_v]){
        ds->parent[ulp_u]=ulp_v;
        ds->size[ulp_v]+=ds->size[ulp_u];
    }
    else{
        ds->parent[ulp_v]=ulp_u;
        ds->size[ulp_u]+=ds->size[ulp_v];
    }
}
int MST(int n,int edge[][3],int cnt){
    DisjointSet ds=create(n);
    int minCost=0;
    for(int i=0;i<cnt;i++){
        int u=edge[i][0];
        int v=edge[i][1];
        if(find(ds,u)!=find(ds,v)){
            minCost+=edge[i][2];
            Union(ds,u,v);
        }
    }
    return minCost;
}
int compare(const void *a,const void *b){
    return ((int*)a)[2]-((int*)b)[2];
}
int main(){
    int n;
    scanf("%d",&n);
    int adj[n][n];
    int u,v;
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j]=-1;
        }
    }
    for(int i=0;i<n;i++){
        scanf("%d",&u);
        int k=0;
        while(scanf("%d",&v)==1){
            adj[u][k]=v;
            k++;
            cnt++;
            if(getchar()=='\n')
                break;
        }
    }
    int edgeWeight[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            edgeWeight[i][j]=-1;
        }
    }
    for(int i=0;i<n;i++){
        scanf("%d",&u);
        int k=0;
        while(scanf("%d",&v)==1){
            edgeWeight[u][k]=v;
            k++;
            if(getchar()=='\n')
                break;
        }
    }
    int edge[cnt][3];
    int k=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adj[i][j]!=-1){
                edge[k][0]=i;
                edge[k][1]=adj[i][j];
                edge[k][2]=edgeWeight[i][j];
                k++;
            }
            else
                break;
        }
    }
    qsort(edge,cnt,sizeof(edge[0]),compare);
    printf("%d",MST(n,edge,cnt));
    return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define vmax 100
struct q{
    int arr[vmax];
    int front;
    int rear;
};
typedef struct q* q;
int empty(q que){
    return que->front==que->rear;
}
void push(q que,int x){
    que->arr[(que->rear)++]=x;
}
void pop(q que){
    (que->front)++;
}
int front(q que){
    return que->front;
}
void bfs(int n,int adj[][vmax],int vis[],int i){
    struct q que;
    que.front=0;
    que.rear=0;
    push(&que,i);
    while(!empty(&que)){
        int node=front(&que);
        vis[node]=1;
        pop(&que);
        for(int i=0;i<n;i++){
            if(adj[node][i]==1 && vis[i]==0){
                push(&que,i);
            }
        }
    }
}
bool bfs_cycle(int n,int adj[][vmax],int vis[],int i){
    struct q que;
    que.front=0;
    que.rear=0;
    push(&que,i);
    int pathVis[vmax]={0};
    while(!empty(&que)){
        int node=front(&que);
        vis[node]=1;
        pathVis[node]=1;
        pop(&que);
        for(int j=0;j<n;j++){
            if(adj[node][j]==1){
                if(vis[j]==0)
                push(&que,i);
                else if(pathVis[i])
                return true;
            }
            
        }
    }
    return false;
}
bool isCycle(int n,int adj[][vmax]){
    int vis[vmax]={0};
    for(int i=0;i<n;i++){
                if(vis[i]==0){
                    if(bfs_cycle(n,adj,vis,i))
                        return true;
                }
            }
            return false;
}
int main(){
    int n;
    scanf("%d",&n);
    int adj[n][vmax];
    int adj2[n][vmax];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&adj[i][j]);
            adj2[j][i]=adj[i][j];
        }
    }
    char c;
    while(1){
        scanf(" %c",&c);
        if(c=='x')
            break;
        else if(c=='c'){
            int cnt=0;
            int vis[vmax]={0};
            for(int i=0;i<n;i++){
                if(vis[i]==0){
                    bfs(n,adj2,vis,i);
                    cnt++;
                }
            }
            printf("%d\n",cnt);
            }
        else if(c=='t'){
            if(isCycle(n,adj))
                printf("0\n");
            else
                printf("1\n");
        }
    }
    
    
}
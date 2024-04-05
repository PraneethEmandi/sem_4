#include <stdio.h>
#include <stdlib.h>

int main(){
    int V;
    scanf("%d", &V);
    int adj[V][V];
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            scanf("%d",&adj[i][j]);
            if(adj[i][j]==-1){
                adj[i][j]=101;
            }
        }
    }
    int shortPath[V][V];
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            shortPath[i][j]=adj[i][j];
        }
    }
    for(int k=0;k<V;k++){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                if(shortPath[i][j]>shortPath[i][k]+shortPath[k][j]){
                    shortPath[i][j]=shortPath[i][k]+shortPath[k][j];
                }
            }
        }
    }
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(shortPath[i][j]==101){
                printf("-1 ");
            }
            else{
                printf("%d ",shortPath[i][j]);
            }
        }
        printf("\n");
    }
    return 1;
}
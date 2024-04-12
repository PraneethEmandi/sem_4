#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int PrimsMST(int vis[], int n, int edgeWeight[][n],int idx, int flag){
    int min = 100000;
    int x,y;
    int temp = 0;
    int ans = 0;
    vis[idx] = 1;
    while(temp < n-1){
        min = 100000;
        x = 0;
        y = 0;
        for(int i = 0; i < n; i++){
            if(vis[i]){
                for(int j = 0; j < n; j++){
                    if(!vis[j] && edgeWeight[i][j]){
                        if(min > edgeWeight[i][j]){
                            min = edgeWeight[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        ans += edgeWeight[x][y];
        vis[y] = 1;
        if(flag){
            printf("%d %d ", x, y);
        }
        temp++;
    }
    return ans;
}

int main(){
    int n;
    scanf("%d",&n);
    int edgeWeight[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",&edgeWeight[i][j]);
        }
    }
    int vis[n];
    for(int i = 0; i < n; i++){
        vis[i] = 0;
    }
    char s;
    while(1){
        scanf("%c",&s);
        if(s == 'x'){
            return 1;
        }
        else if(s == 't'){
            int ans = PrimsMST(vis, n, edgeWeight,0, 0);
            printf("%d\n",ans);
        }
        else if(s == 's'){
            char str[1000];
            fgets(str, sizeof(str), stdin);
            int idx = 0;
            int len = strlen(str);
            for(int i = 0; i < len-1; i++){
                if(str[i] != ')' && str[i] != '(')
                    idx = idx * 10 + (str[i] - '0');
            }
            for(int i = 0; i < n; i++){
                vis[i] = 0;
            }
            int ans = PrimsMST(vis, n, edgeWeight, idx, 1); 
            printf("\n");
        }
    }
}
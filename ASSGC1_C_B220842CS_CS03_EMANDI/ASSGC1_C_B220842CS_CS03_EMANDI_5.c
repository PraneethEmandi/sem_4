#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100000
int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    long a[n];
    long cnt[MAX_SIZE]={0};
    int distinct=0;
    int i;
    for(i=0;i<k;i++){
        scanf("%ld",&a[i]);
        if(cnt[a[i]]==0){
            distinct++;
        }
        cnt[a[i]]++;
    }
    printf("%d ",distinct);
    for(i=k;i<n;i++){
        scanf("%ld",&a[i]);
        if(cnt[a[i-k]]==1){
            distinct--;
        }
        cnt[a[i-k]]--;
        if(cnt[a[i]]==0){
            distinct++;
        }
        cnt[a[i]]++;
        printf("%d ",distinct);
    }   
}
#include <stdio.h>
#include <stdlib.h>
#define vmax 100
struct node{
    int x;
    struct node* next;
};
typedef struct node* node;
node create(int val){
    node temp=(node)malloc(sizeof(struct node));
    temp->x=val;
    temp->next=NULL;
    return temp;
}
node insert(node head,int val){
    if(head==NULL)
        return head=create(val);
    node curr=head;
    node prev=NULL;
    while(curr!=NULL && curr->x<val){
        prev=curr;
        curr=curr->next;
    }
    node temp=create(val);
    if(prev==NULL){
        temp->next=head;
        head=temp;
        return head;
    }
    if(curr==NULL){
        prev->next=temp;
        return head;
    }
    prev->next=temp;
    temp->next=curr;
    return head;
}
void dfs(int adj[][vmax],int vis[],int point,int n,int *size){
    vis[point]=1;
    for(int j=0;j<n;j++){
        if(adj[point][j]!=-1){
            if(vis[adj[point][j]]==0){
                dfs(adj,vis,j,n,size);
                (*size)++;
            }
        }
        // else
        //     break;
    }
}
void components(int adj[][vmax],int n,int *cnt,node head,int vis[]){
    // int vis[n];
    // for(int i=0;i<n;i++){
    //     vis[i]=0;
    // }
    for(int i=0;i<n;i++){
        if(vis[i]==0){
            int size=1;
            dfs(adj,vis,i,n,&size);
            (*cnt)++;
            head=insert(head,size);
        }
    }
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
        int k,x;
        scanf("%d",&k);
        k--;
        int t=0;
        while(scanf("%d",&x)==1){
            adj[i][t++]=x-1;
            if(getchar()=='\n')
                break;
        }
    }
    int vis[vmax]={0};
    int cnt=0;
    node head=NULL;
    components(adj,n,&cnt,head,vis);
    char c;
    while(1){
        scanf(" %c",&c);
        if(c=='t')
            break;
        switch(c){
            case 'n':
                printf("%d\n",cnt);
                break;
            case 's':
                node temp=head;
                while(temp!=NULL){
                    printf("%d ",temp->x);
                    temp=temp->next;
                }
                printf("\n");
                break;
            case 'a':
                int art=0;
                for(int i=0;i<n;i++){
                    int vis2[vmax]={0};
                    vis2[i]=1;
                    int cnt2=0;
                    node head2=NULL;
                    components(adj,n,&cnt2,head2,vis2);
                    if(cnt2>cnt)
                        art++;
                }
                if(art==0)
                    printf("-1\n");
                else
                    printf("%d\n",art);
                break;
            case 'b':
                int bri=0;
                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        int vis2[vmax]={0};
                        int cnt2=0;
                        node head2=NULL;
                        if(adj[i][j]!=-1){
                            int temp=adj[i][j];
                            adj[i][j]=-1;
                            components(adj,n,&cnt2,head2,vis2);
                            adj[i][j]=temp;
                        }
                        if(cnt2>cnt)
                            bri++;
                    }   
                }
                if(bri==0)
                    printf("-1\n");
                else
                    printf("%d\n",bri);
                break;
                
        }
    }
    return 1;
}   
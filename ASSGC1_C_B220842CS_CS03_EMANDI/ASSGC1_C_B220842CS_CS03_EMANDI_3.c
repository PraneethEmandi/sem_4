#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//0-CS 1-EC 2-EE 3-CE
struct node
{
    char name[100];
    char rno[10];
    int age;
    int branch;
    struct node* next;
};
typedef struct node* node;
struct hashmap{
    int cnt[4];
    node map[4];
};
typedef struct hashmap* hashmap;
void initialize(hashmap hash){
    for(int i=0;i<4;i++){
        hash->map[i]=NULL;
        hash->cnt[i]=0;
    }
}
node create(char name[],char rno[],int age){
    node temp=(node)malloc(sizeof(struct node));
    strcpy(temp->rno,rno);
    strcpy(temp->name,name);
    temp->age=age;
    char b[3];
    strncpy(b,rno+7,2);
    // printf("%s",b);
    if(strcmp(b,"CS")==0)
    temp->branch=0;
    else if(strcmp(b,"EC")==0)
    temp->branch=1;
    else if(strcmp(b,"EE")==0)
    temp->branch=2;
    else
    temp->branch=3;
    // temp->cnt=0;
    temp->next=NULL;
    return temp;
}
void insert(hashmap hash,char name[],char rno[],int age){
    node temp=create(name,rno,age);
    int index=age;
    for(int i=0;i<strlen(name);i++){
        index+=(name[i]-'0');
    }
    index=index%4;
    hash->cnt[index]++;
    if(hash->map[index]==NULL){
        hash->map[index]=temp;
    }
    else{
        node curr=hash->map[index];
        node prev=NULL;
        while(curr!=NULL){
            prev=curr;
            curr=curr->next;
        }
        if (prev == NULL) {
        hash->map[index] = temp;
    } else {
        prev->next = temp;
    }
    }
}
void count(hashmap hash,int k){
    printf("%d ",hash->cnt[k]);
    if(hash->cnt[k]!=0){
        node temp=hash->map[k];
        while(temp!=NULL){
            printf("%s ",temp->name);
            temp=temp->next;
        }
    }
    printf("\n");
}
void branchcnt(hashmap hash,int index,int branch){
    int x=0;
    node temp=hash->map[index];
    while(temp!=NULL){
        if(temp->branch==branch){
            printf("%s ",temp->name);
            x++;
        }
        temp=temp->next;
    }
    if(x==0)
    printf("-1");
    printf("\n");
}
int main(){
    struct hashmap hash;
    initialize(&hash);
    char name[100],rno[10];
    int age;
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%s %s %d",name,rno,&age);
        insert(&hash,name,rno,age);
    }
    char c,b[3];
    int index;
    while(1){
        scanf(" %c",&c);
        if(c=='e')
            break;
        else if(c>='0' && c<='3'){
            scanf("%s",b);
            if(strcmp(b,"CS")==0 || strcmp(b,"cs")==0)
            branchcnt(&hash,c-'0',0);
            else if(strcmp(b,"EC")==0 || strcmp(b,"ec")==0)
            branchcnt(&hash,c-'0',1);
            else if(strcmp(b,"EE")==0 || strcmp(b,"ee")==0)
            branchcnt(&hash,c-'0',2);
            else
            branchcnt(&hash,c-'0',3);
        }
        else if(c=='c'){
            scanf("%d",&index);
            count(&hash,index);
    }
}
}

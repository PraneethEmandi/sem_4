#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000
typedef struct {
    int key;
    // int value;
} HashEntry;

typedef struct {
    HashEntry *map;
    int size;
} hashmap;

void initializeHashTable(hashmap *hash,int size){
    hash->map=(HashEntry*)malloc(size*sizeof(HashEntry));
    hash->size=size;
    for (int i = 0; i < size; i++) {
        hash->map[i].key = -1;
        // hashTable->table[i].value = -1;
    }
}
int hashFunction(int key,int size){
    return key%size;
}
void insert_linear(hashmap* hash,int key,int *cnt){
    int index=hashFunction(key,hash->size);
    while(hash->map[index].key!=-1){
        index=hashFunction(index+1,hash->size);
        (*cnt)++;
    }
    hash->map[index].key=key;
    printf("%d ",index);
}
void insert_quad(hashmap* hash,int key,int *cnt){
    int index=hashFunction(key,hash->size);
    int i=1;
    int temp=index;
    while(hash->map[index].key!=-1){
        index=hashFunction(temp+(i*i),hash->size);
        (*cnt)++;
        i++;
    }
    hash->map[index].key=key;
    printf("%d ",index);
}
void insert_double(hashmap* hash,int key,int *cnt,int prime){
    int index1=hashFunction(key,hash->size);
    int index2=hashFunction(prime-hashFunction(key,prime),hash->size);
    int i=0;
    int index=(index1+i*index2)%hash->size;
    while(hash->map[index].key!=-1){
        i++;
        index=(index1+i*index2)%hash->size;
        (*cnt)++;
        
    }
    hash->map[index].key=key;
    printf("%d ",index);
}
int main(){
    int size;
    scanf("%d",&size);
    hashmap hash;
    int cnt=0;
    int a[MAX_SIZE]={0};
    char c[MAX_SIZE];
    int k=0;
    scanf(" %[^\n]s",c);
   for (int i = 0; i < strlen(c); i++) {
        if (c[i] == ' ') {
            continue;
        }
        while (c[i] != ' ' && c[i] != '\0') {
            a[k] = a[k] * 10 + (c[i] - '0');
            i++;
        }
        k++;
    }
    // printf("k %d\n",k);
    initializeHashTable(&hash,size);
    for(int i=0;i<k;i++){
        insert_linear(&hash,a[i],&cnt);
    }
    printf("\n%d\n",cnt);
    cnt=0;
    initializeHashTable(&hash,size);
    for(int i=0;i<k;i++){
        insert_quad(&hash,a[i],&cnt);
    }
    printf("\n%d\n",cnt);
    cnt=0;
    initializeHashTable(&hash,size);
    int prime=0;
    int chk=1;
    
    for(int i=size-1;i>1;i--){
        for(int j=2;j<i;j++){
            if(i%j==0){
                // printf("%d\n",i);
                chk=0;
                break;
            }
        }
        if(chk==1){
                prime=i;
                break;
        }
        chk=1;
    }
    // printf("prime %d\n",prime);
    for(int i=0;i<k;i++){
        insert_double(&hash,a[i],&cnt,prime);
    }
    printf("\n%d\n",cnt);
    return 1;
}
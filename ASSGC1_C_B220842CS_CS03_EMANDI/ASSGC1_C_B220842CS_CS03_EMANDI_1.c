#include <stdio.h>
#include <stdlib.h>

// #define max 12

typedef struct {
    int key;
    // int value;
} HashEntry;

typedef struct {
    HashEntry *table;
} HashTable;

void initializeHashTable(HashTable *hashTable,int max) {
    hashTable->table=(HashEntry*)malloc(max*sizeof(HashEntry));
    for (int i = 0; i < max; i++) {
        hashTable->table[i].key = -1;
        // hashTable->table[i].value = -1;
    }
}

int hashFunction(int key, int size) {
    return key % size;
}

void insert(HashTable *hashTable, int key,int max) {
    int index = hashFunction(key, max);

    while (hashTable->table[index].key != -1) {
        index = (index + 1) % max;
    }

    hashTable->table[index].key = key;
    // hashTable->table[index].value = value;
}
int search(HashTable *hashTable, int key,int max) {
    int index = hashFunction(key, max);
    int count = 0;

    while (hashTable->table[index].key != key && hashTable->table[index].key != -1) {
        index = (index + 1) % max;
        ++count%max;
    }

    if (hashTable->table[index].key == key) {
        return 1;
    }

    return 0;
}
void unionOperation(int A[], int B[], int m, int n,int max) {
    int cnt = 0;
    HashTable hashTable;
    initializeHashTable(&hashTable,max);

    for (int i = 0; i < m; i++) {
        if(!search(&hashTable, A[i],max)){
        insert(&hashTable, A[i],max);
        cnt++;
        printf("%d ", A[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (!search(&hashTable, B[i],max)) {
            insert(&hashTable, B[i],max);
            cnt++;
            printf("%d ", B[i]);
        }
    }
    if (cnt == 0) {
        printf("-1");
    }
    printf("\n");
}

void intersectionOperation(int A[], int B[], int m, int n,int max) {
    // printf("%d %dx\n",A[0],B[0]);
    int cnt = 0;
    HashTable hashTableA, hashTableB;
    initializeHashTable(&hashTableA, max);
    initializeHashTable(&hashTableB, max);
    for (int i = 0; i < n; i++) {
        if(search(&hashTableB, B[i],max)==0)
        insert(&hashTableB, B[i],max);
    }
    for(int i=0;i<m;i++){
        if(search(&hashTableA, A[i],max)==0){
            insert(&hashTableA, A[i],max);
            if(search(&hashTableB, A[i],max)){
                cnt++;
                printf("%d ",A[i]);
            }
        }
    }
    if (cnt == 0) {
        printf("-1");
    }
    printf("\n");
}

void setDifferenceOperation(int A[], int B[], int m, int n,int max) {
    HashTable hashTable;
    initializeHashTable(&hashTable, max);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if(search(&hashTable, B[i],max)==0)
        insert(&hashTable, B[i],max);
    }

    for (int i = 0; i < m; i++) {
        if (search(&hashTable, A[i],max) == 0){
            insert(&hashTable, A[i],max);
            printf("%d ", A[i]);
            cnt++;
        }
    }
    if (cnt == 0) {
        printf("-1");
    }
    printf("\n");
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int max=m>n?2*m:2*n;
    int A[m], B[n];

    for (int i = 0; i < m; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }
    char c,x,y;
    while(1){
        scanf(" %c",&c);
        if(c=='u'){
            scanf(" %c %c",&x,&y);
            if(x=='A' && y=='B'){
                unionOperation(A, B, m, n,max);
            }
            else if(x=='B' && y=='A'){
                unionOperation(B, A, n, m,max);
            }
            
        }
        else if(c=='i'){
            scanf(" %c %c",&x,&y);
            if(x=='A' && y=='B'){
                intersectionOperation(A, B, m, n,max);
            }
            else if(x=='B' && y=='A'){
                intersectionOperation(B, A, n, m,max);
            }
        }
        else if(c=='s'){
            scanf(" %c %c",&x,&y);
            if(x=='A' && y=='B'){
                setDifferenceOperation(A, B, m, n,max);
            }
            else if(x=='B' && y=='A'){
                setDifferenceOperation(B, A, n, m,max);
            }
        }
        else if(c=='e'){
            break;
        }
    }
    return 1;
}

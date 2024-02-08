
#include <stdio.h>
#include <stdlib.h>

// #define MAX_SIZE 500

// Structure for Node in the hash table chain
struct Node {
    int key;
    struct Node* next;
};

// Structure for hash table
struct HashTable {
    int size;
    struct Node** table;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize hash table
void initializeHashTable(struct HashTable* ht, int size) {
    ht->size = size;
    ht->table = (struct Node**)malloc(size * sizeof(struct Node*));
    for (int i = 0; i < size; ++i) {
        ht->table[i] = NULL;
    }
}

// Function to insert key into hash table
void insert(struct HashTable* ht, int key) {
    int index = key % ht->size;
    struct Node* newNode = createNode(key);

    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        struct Node* current = ht->table[index];
        struct Node* prev = NULL;
        while (current != NULL && current->key < key) {
            prev = current;
            current = current->next;
        }
        if (current == NULL) {
            prev->next = newNode;
        } else if (current->key == key) {
            printf("-1\n");
            free(newNode);
            return;
        } else {
            newNode->next = current;
            if (prev == NULL) {
                ht->table[index] = newNode;
            } else {
                prev->next = newNode;
            }
        }
    }
}

// Function to search for a key in the hash table
void search(struct HashTable* ht, int key) {
    int index = key % ht->size;
    struct Node* current = ht->table[index];
    int position = 1;

    while (current != NULL && current->key != key) {
        current = current->next;
        position++;
    }

    if (current == NULL) {
        printf("-1\n");
    } else {
        printf("%d %d\n", index, position);
    }
}
//search without printing
int search_wp(struct HashTable* ht, int key) {
    int index = key % ht->size;
    struct Node* current = ht->table[index];
    int position = 1;

    while (current != NULL && current->key != key) {
        current = current->next;
        position++;
    }

    if (current == NULL) {
        return 0;
    } else {
        return 1;
    }
}
// Function to delete a key from the hash table
int deleteKey(struct HashTable* ht, int key) {
    int index = key % ht->size;
    struct Node* current = ht->table[index];
    struct Node* prev = NULL;
    int position = 1;

    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;
        position++;
    }

    if (current == NULL) {
        printf("-1\n");
        return 0;
    } else {
        if (prev == NULL) {
            ht->table[index] = current->next;
        } else {
            prev->next = current->next;
        }
        printf("%d %d\n", index, position);
        free(current);
    }
}

// Function to update a key in the hash table
void update(struct HashTable* ht, int oldKey, int newKey) {
    if(newKey==oldKey){
        search(ht,oldKey);
    }
    else{
        if(!search_wp(ht,newKey) && search_wp(ht,oldKey)){
            deleteKey(ht,oldKey);
            insert(ht,newKey);
        }
        else{
            printf("-1\n");
        }
    }
}

// Function to print elements in a chain
void printElementsInChain(struct HashTable* ht, int index) {
    if (index < 0 || index >= ht->size || ht->table[index] == NULL) {
        printf("-1\n");
        return;
    }
    struct Node* current = ht->table[index];
    while (current != NULL) {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct HashTable ht;
    int TableSize, key, oldKey, newKey;
    char operation;

    scanf("%d", &TableSize);
    initializeHashTable(&ht, TableSize);

    while (1) {
        scanf(" %c", &operation);
        if (operation == 'i') {
            scanf("%d", &key);
            insert(&ht, key);
        } else if (operation == 's') {
            scanf("%d", &key);
            search(&ht, key);
        } else if (operation == 'd') {
            scanf("%d", &key);
            deleteKey(&ht, key);
        } else if (operation == 'u') {
            scanf("%d %d", &oldKey, &newKey);
            update(&ht, oldKey, newKey);
        } else if (operation == 'p') {
            scanf("%d", &key);
            printElementsInChain(&ht, key);
        } else if (operation == 'e') {
            break;
        }
    }

    return 0;
}

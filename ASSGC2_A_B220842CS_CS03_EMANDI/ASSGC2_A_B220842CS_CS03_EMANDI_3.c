#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    char colour;
    struct Node* parent;
} Node;

typedef struct RedBlackTree {
    Node* root;
    int ll;
    int rr;
    int lr;
    int rl;
} RedBlackTree;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->colour = 'R';
    newNode->parent = NULL;
    return newNode;
}
struct que_element{
    Node* node;
    int h;
};
struct que{
    struct que_element* arr;
    int front;
    int rear;
    int size;
};
void enqueue(struct que* q, Node* node, int h){
    
    if(q->front==-1 && q->rear==-1)
    {
        q->rear++;
        q->front++;
    }
    else{
        q->rear++;
    }
    q->arr[q->rear].node = node;
    q->arr[q->rear].h = h;
    // q->rear++;
}
struct que_element dequeue(struct que* q){
    q->front++;
    return q->arr[q->front];
}
// void print(RedBlackTree* tree){
//     if(tree == NULL){
//         printf("( ) ");
//         return;
//     }
//     printf("(%d %c ",tree->,root->color);
//     print(root->left);

//     print(root->right);
//     printf(") ");
// }
void printLevelOrder(Node* root){
    if (root==NULL)
    {
        printf("( ) ");
        return;
    }
    printf("( %d %c ",root->data,root->colour);
    printLevelOrder(root->left);
    printLevelOrder(root->right);
    printf(") ");
    
}
// void printLevelOrder(RedBlackTree* tree){
//     if(tree->root==NULL){
//         printf("( )");
//         return;
//     }
//     struct que q;
//     q.arr = (struct que_element*)malloc(1000*sizeof(struct que_element));
//     q.front = -1;
//     q.rear = -1;
//     q.size = 1000;
//     enqueue(&q, tree->root, 0);
//     struct que_element temp=q.arr[q.front];
//     while(q.front!=q.rear-1){
//         int cnt=0;
//         int l=0;
//         printf("(");
//         // if(temp.node!=NULL)
//         printf("%d %c", temp.node->data, temp.node->colour);
//         // else
//         // printf("()");
//         // if(temp.node!=NULL){
//         if(temp.node->left!=NULL){
//             enqueue(&q, temp.node->left, temp.h+1);
//         }
//         else{
//             // enqueue(&q, NULL, temp.h+1);
//             l=1;
//             cnt++;
//         }
//         // }
//         // if(temp.node!=NULL){
//         if(temp.node->right!=NULL){
//             enqueue(&q, temp.node->right, temp.h+1);
//         }
//         else{
//             printf("()");
//             // enqueue(&q, NULL, temp.h+1);
//             cnt++;
//         }
//         // }
//         int h = temp.h;
//         temp=dequeue(&q);
//         if(cnt==2)
//             printf(")");
//         if(h==temp.h-1){
//             if(l==1)
//                 printf("()");
//             printf(")");
//         }
        
//     }
// }
// void printLevelOrder(RedBlackTree* tree) {
//     if (tree->root == NULL) {
//         printf("( )");
//         return;
//     }

//     // Queue to store nodes for level order traversal
//     Node* queue[1000];  // Assuming a maximum of 1000 nodes
//     int front = 0, rear = 0;
//     queue[rear++] = tree->root;

//     while (front < rear) {
//         Node* current = queue[front++];
//         printf("( %d %c ", current->data, current->colour);

//         if (current->left != NULL) {
//             printf("( %d %c ", current->left->data, current->left->colour);
//             queue[rear++] = current->left;
//         } else {
//             printf("( ) ");
//         }

//         if (current->right != NULL) {
//             printf("( %d %c ", current->right->data, current->right->colour);
//             queue[rear++] = current->right;
//         } else {
//             printf("( ) ");
//         }

//         printf(")");
//     }
// }


Node* rotateLeft(Node* node) {
    Node* x = node->right;
    Node* y = x->left;
    x->left = node;
    node->right = y;
    node->parent = x;
    if (y != NULL)
        y->parent = node;
    return x;
}

Node* rotateRight(Node* node) {
    Node* x = node->left;
    Node* y = x->right;
    x->right = node;
    node->left = y;
    node->parent = x;
    if (y != NULL)
        y->parent = node;
    return x;
}

Node* insertHelp(Node* root, int data, RedBlackTree* tree) {
    int f = 0;
    if (root == NULL)
        return createNode(data);
    else if (data < root->data) {
        root->left = insertHelp(root->left, data, tree);
        root->left->parent = root;
        if (root != tree->root) {
            if (root->colour == 'R' && root->left->colour == 'R')
                f = 1;
        }
    } else {
        root->right = insertHelp(root->right, data, tree);
        root->right->parent = root;
        if (root != tree->root) {
            if (root->colour == 'R' && root->right->colour == 'R')
                f = 1;
        }
    }

    if (tree->ll) {
        root = rotateLeft(root);
        root->colour = 'B';
        root->left->colour = 'R';
        tree->ll = 0;
    } else if (tree->rr) {
        root = rotateRight(root);
        root->colour = 'B';
        root->right->colour = 'R';
        tree->rr = 0;
    } else if (tree->rl) {
        root->right = rotateRight(root->right);
        root->right->parent = root;
        root = rotateLeft(root);
        root->colour = 'B';
        root->left->colour = 'R';
        tree->rl = 0;
    } else if (tree->lr) {
        root->left = rotateLeft(root->left);
        root->left->parent = root;
        root = rotateRight(root);
        root->colour = 'B';
        root->right->colour = 'R';
        tree->lr = 0;
    }

    if (f) {
        if (root->parent->right == root) {
            if (root->parent->left == NULL || root->parent->left->colour == 'B') {
                if (root->left != NULL && root->left->colour == 'R')
                    tree->rl = 1;
                else if (root->right != NULL && root->right->colour == 'R')
                    tree->ll = 1;
            } else {
                root->parent->left->colour = 'B';
                root->colour = 'B';
                if (root->parent != tree->root)
                    root->parent->colour = 'R';
            }
        } else {
            if (root->parent->right == NULL || root->parent->right->colour == 'B') {
                if (root->left != NULL && root->left->colour == 'R')
                    tree->rr = 1;
                else if (root->right != NULL && root->right->colour == 'R')
                    tree->lr = 1;
            } else {
                root->parent->right->colour = 'B';
                root->colour = 'B';
                if (root->parent != tree->root)
                    root->parent->colour = 'R';
            }
        }
        f = 0;
    }
    return root;
}

void inorderTraversalHelper(Node* node) {
    if (node != NULL) {
        inorderTraversalHelper(node->left);
        printf("%d ", node->data);
        inorderTraversalHelper(node->right);
    }
}

// void printTreeHelper(Node* root, int space) {
//     if (root != NULL) {
//         space += 10;
//         printTreeHelper(root->right, space);
//         printf("\n");
//         for (int i = 10; i < space; i++)
//             printf(" ");
//         printf("%d\n", root->data);
//         printTreeHelper(root->left, space);
//     }
// }

void insert(RedBlackTree* tree, int data) {
    if (tree->root == NULL) {
        tree->root = createNode(data);
        tree->root->colour = 'B';
    } else
        tree->root = insertHelp(tree->root, data, tree);
}

void inorderTraversal(RedBlackTree* tree) {
    inorderTraversalHelper(tree->root);
}

// void printTree(RedBlackTree* tree) {
//     printTreeHelper(tree->root, 0);
// }
// struct que{
//     node
// }
int main() {
    RedBlackTree t = {NULL, 0, 0, 0, 0};
    // t.root = NULL;
    char c[10];
    // int key;
    // scanf("%s", c);
    
    while(1){
        scanf(" %s", c);
        if(c[0]=='e')
            break;
        int l = strlen(c);
        int i=0;
        int key=0;
        while(c[i]!='\0'){
            key = key*10 + (c[i]-'0');
            i++;
        }
        // printf("%d\n", key);
        insert(&t, key);
        printLevelOrder(t.root);
        printf("\n");
        // inorderTraversal(&t);
        // scanf(" %s", c);
    }
    // inorderTraversal(&t);
    // printTree(&t);
      
    return 0;
}

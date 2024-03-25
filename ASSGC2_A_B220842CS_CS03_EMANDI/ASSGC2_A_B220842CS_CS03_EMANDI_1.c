#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    long val;
    struct TreeNode* left;
    struct TreeNode* right;
    long h;
};
struct queue {
    long front, rear, size;
    unsigned capacity;
    long* array;
};
typedef struct queue* Queue;
Queue createQueue(unsigned capacity) {
    Queue queue = (Queue)malloc(sizeof(struct queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (long*)malloc(queue->capacity * sizeof(long));
    return queue;
}
int isFull(Queue queue) {
    return (queue->size == queue->capacity);
}
int isEmpty(Queue queue) {
    return (queue->size == 0);
}
void enqueue(Queue queue, long item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}
long dequeue(Queue queue) {
    if (isEmpty(queue))
        return -1;
    long item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

typedef struct TreeNode* TreeNode;
#define max(a,b) (((a) > (b)) ? (a) : (b))
TreeNode create(long val) {
    TreeNode temp = (TreeNode)malloc(sizeof(struct TreeNode));
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    temp->h = 1; // Height of a single node is 1
    return temp;
}

long height(TreeNode node) {
    if (node == NULL)
        return 0;
    return node->h;
}

// long max(long a, long b) {
//     return (a > b) ? a : b;
// }

long balanceFactor(TreeNode node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

void updateHeight(TreeNode node) {
    if (node != NULL)
        node->h = 1 + max(height(node->left), height(node->right));
}

TreeNode leftRotate(TreeNode z) {
    if (z == NULL || z->right == NULL)
        return z;
    TreeNode y = z->right;
    TreeNode T = y->left;
    y->left = z;
    z->right = T;
    updateHeight(z);
    updateHeight(y);
    return y;
}

TreeNode rightRotate(TreeNode z) {
    if (z == NULL || z->left == NULL)
        return z;
    TreeNode y = z->left;
    TreeNode T = y->right;
    y->right = z;
    z->left = T;
    updateHeight(z);
    updateHeight(y);
    return y;
}

TreeNode insert(TreeNode root, long val, long* cnt_rr, long* cnt_lr) {
    if (root == NULL)
        return create(val);

    if (val < root->val) {
        root->left = insert(root->left, val, cnt_rr, cnt_lr);
    } else if (val > root->val) {
        root->right = insert(root->right, val, cnt_rr, cnt_lr);
    } else {
        return root; // No duplicates allowed
    }

    updateHeight(root);

    long balance = balanceFactor(root);

    if (balance > 1) {
        if (val < root->left->val) {
            root = rightRotate(root);
            (*cnt_rr)++;
        } else {
            root->left = leftRotate(root->left);
            root = rightRotate(root);
            (*cnt_rr)++;
            (*cnt_lr)++;
        }
    } else if (balance < -1) {
        if (val > root->right->val) {
            root = leftRotate(root);
            (*cnt_lr)++;
        } else {
            root->right = rightRotate(root->right);
            root = leftRotate(root);
            (*cnt_rr)++;
            (*cnt_lr)++;
        }
    }

    return root;
}

void preorder(TreeNode root) {
    if (root != NULL) {
        printf("%ld ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

int Ancestors(TreeNode root, long target, Queue q) {
    if (root == NULL)
        return 0;

    if (root->val == target) {
        enqueue(q, root->val);
        return 1;
    }

    if (Ancestors(root->left, target, q) || Ancestors(root->right, target, q)) {
        enqueue(q, root->val);
        return 1;
    }

    return 0;
}

int main() {
    TreeNode root = NULL;
    char c;
    long val;
    long cnt_lr = 0, cnt_rr = 0;
    Queue q;

    while (1) {
        scanf(" %c", &c);
        if (c == 'e')
            break;
        switch (c) {
            case 'i':
                scanf(" %ld", &val);
                root = insert(root, val, &cnt_rr, &cnt_lr);
                break;
            case 's':
                printf("%ld %ld\n", cnt_lr, cnt_rr);
                break;
			case 'x':
                scanf(" %ld", &val);
			    // long a[1000001] = {0};
                q=createQueue(1000001);
                int chk = Ancestors(root, val, q);

                if (chk == 0)
                    printf("-1");
                else {
                    while (!isEmpty(q))
                    {
                        printf("%ld ", dequeue(q));
                    }
                }
                printf("\n");
                break;
            case 'p':
                preorder(root);
                printf("\n");
                break;
            // case 'x':
            //     scanf(" %ld", &val);
			// 	long a[1000001] = {0};
            //     int chk = Ancestors(root, val, a, 0);

            //     if (chk == 0)
            //         printf("-1");
            //     else {
            //         for (int i = 0; a[i] != 0; i++)
            //             printf("%ld ", a[i]);
            //     }
            //     printf("\n");
            //     break;
        }
    }

    // Free allocated memory
    // Left as an exercise for clarity
    return 0;
}

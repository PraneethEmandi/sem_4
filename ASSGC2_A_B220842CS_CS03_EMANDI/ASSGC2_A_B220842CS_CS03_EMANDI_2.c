#include <stdlib.h>
#include <stdio.h>

struct TreeNode {
    long key;
    long val;
    struct TreeNode* left;
    struct TreeNode* right;
    long h;
};
typedef struct TreeNode* TreeNode;
#define max(a,b) (((a) > (b)) ? (a) : (b))
TreeNode create(long key, long val) {
    TreeNode temp = (TreeNode)malloc(sizeof(struct TreeNode));
    temp->key = key;
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    temp->h = 0; // Height of a single node is 1
    return temp;
}
long height(TreeNode node) {
    if (node == NULL)
        return 0;
    return node->h;
}
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
TreeNode insert(TreeNode root, long key, long val,long *size) {
    if (root == NULL)
        return create(key, val);
    if (key < root->key)
        root->left = insert(root->left, key, val,size);
    else if (key > root->key)
        root->right = insert(root->right, key, val,size);
    else{
        (*size)--;
        root->val = val;
        return root;
    }
    updateHeight(root);
    long bf = balanceFactor(root);
    if (bf > 1) {
        if (key < root->left->key) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (bf < -1) {
        if (key > root->right->key) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}
TreeNode lowbound(TreeNode root, long key) {
    if(root == NULL)
        return NULL;
    lowbound(root->left, key);
    if(root->key >= key)
        return root;
    lowbound(root->right, key);
}
TreeNode find(TreeNode root, long key) {
    if (root == NULL || root->key == key)
        return root;
    if (root->key < key)
        return find(root->right, key);
    return find(root->left, key);
}
void inorder(TreeNode root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%ld ", root->key);
    inorder(root->right);
}
int main(){
    TreeNode root = NULL;
    TreeNode node;
    char c;
    long key, val;
    long size=0;
    while(1){
        scanf("%c", &c);
        if(c=='t')
            break;
        switch(c){
            case 'i':
                scanf("%ld %ld", &key, &val);
                size++;
                root = insert(root, key, val,&size);
                
                break;
            case 'l':
                scanf("%ld", &key);
                node = lowbound(root, key);
                if(node == NULL)
                    printf("-1\n");
                else
                    printf("%ld %ld\n", node->key, node->val);
                break;
            case 'f':
                scanf("%ld", &key);
                node = find(root, key);
                if(node == NULL)
                    printf("-1\n");
                else
                    printf("%ld %ld\n", node->key, node->val);
                break;
            case 'p':
                if(root == NULL)
                    printf("-1");
                else
                    inorder(root);
                printf("\n");
                break;
            case 's':
                printf("%ld\n", size);
                break;
            case 'e':
                if(size == 0)
                    printf("1\n");
                else
                    printf("0\n");
        }
    }
    
}
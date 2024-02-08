#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    long val;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct TreeNode *TreeNode;

TreeNode create(long val) {
    TreeNode temp = (TreeNode)malloc(sizeof(struct TreeNode));
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int search(long in[], long ele, int st, int end) {
    for (int i = st; i <= end; i++) {
        if (in[i] == ele)
            return i;
    }
}

TreeNode build(long in[], long pre[], int st, int end, int *preindex) {
    if (st > end)
        return NULL;

    TreeNode node = create(pre[(*preindex)++]);

    if (st == end)
        return node;

    int inindex = search(in, node->val, st, end);
    node->left = build(in, pre, st, inindex - 1, preindex);
    node->right = build(in, pre, inindex + 1, end, preindex);

    return node;
}

long height(TreeNode root) {
    if (root == NULL)
        return 0;
    long lh = height(root->left);
    long rh = height(root->right);
    if (lh > rh)
        return lh + 1;
    else
        return rh + 1;
}

void zigzag(TreeNode root, long level, long oe) {
    if (root == NULL)
        return;
    if (level == 1) {
        printf("%ld ", root->val);
    } else if (level > 1) {
        if (oe % 2 != 0) {
            zigzag(root->left, level - 1, oe);
            zigzag(root->right, level - 1, oe);
        } else {
            zigzag(root->right, level - 1, oe);
            zigzag(root->left, level - 1, oe);
        }
    }
}

void printlevelorder(TreeNode root) {
    long h = height(root);
    for (long i = 1; i <= h; i++)
        zigzag(root, i, i);
}

void levelmax(TreeNode root, long level, long *max) {
    if (root == NULL)
        return;
    if (level == 1) {
        *max = *max > root->val ? *max : root->val;
    } else if (level > 1) {
        levelmax(root->left, level - 1, max);
        levelmax(root->right, level - 1, max);
    }
}

void printlevelmax(TreeNode root) {
    long h = height(root);
    for (long i = 1; i <= h; i++) {
        long max = 0;
        levelmax(root, i, &max);
        printf("%ld ", max);
    }
}

void llsum(TreeNode root, int leftcheck, long *sum) {
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL) {
        if (leftcheck) {
            *sum += root->val;
        }
    } else {
        llsum(root->left, 1, sum);
        llsum(root->right, 0, sum);
    }
}

void postorderTraversal(TreeNode root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%ld ", root->val);
    }
}
long diameter(TreeNode tree)
{
    // base case where tree is empty
    if (tree == NULL)
        return 0;
 
    // get the height of left and right sub-trees
    long lheight = height(tree->left);
    long rheight = height(tree->right);
 
    // get the diameter of left and right sub-trees
    long ldiameter = diameter(tree->left);
    long rdiameter = diameter(tree->right);
 
    // Return max of following three
    // 1) Diameter of left subtree
    // 2) Diameter of right subtree
    // 3) Height of left subtree + height of right subtree +
    // 1
    long temp=ldiameter>rdiameter?ldiameter:rdiameter;
    return temp>lheight+rheight+1?temp:lheight+rheight+1;
}
int main() {
    int n;
    scanf("%d", &n);
    long in[n], pre[n], i;
    for (i = 0; i < n; i++)
        scanf("%ld", &in[i]);
    for (i = 0; i < n; i++)
        scanf("%ld", &pre[i]);
    int preindex = 0;
    TreeNode root = build(in, pre, 0, n - 1, &preindex);
    char c;
    long h, sum;
    while (1) {
        scanf(" %c", &c);
        if(c=='e')
        break;
        switch (c) {
        case 'p':
            postorderTraversal(root);
            printf("\n");
            break;
        case 'z':
            printlevelorder(root);
            printf("\n");
            break;
        case 'm':
            printlevelmax(root);
            printf("\n");
            break;
        case 's':
            sum = 0;
            llsum(root, 0, &sum);
            printf("%ld\n", sum);
            break;
        case 'd':
            h = diameter(root);
            printf("%ld\n", h);
            break;
        }
    }
    return 1;
}

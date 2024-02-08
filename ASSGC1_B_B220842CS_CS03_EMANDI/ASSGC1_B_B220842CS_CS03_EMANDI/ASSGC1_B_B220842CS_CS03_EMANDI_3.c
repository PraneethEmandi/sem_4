#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode
{
    long val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode *TreeNode;

struct PrevStack
{
    TreeNode *stack;
    int top;
};

typedef struct PrevStack *PrevStack;

PrevStack createPrevStack(int size)
{
    PrevStack prevStack = (PrevStack)malloc(sizeof(struct PrevStack));
    prevStack->stack = (TreeNode *)malloc(size * sizeof(TreeNode));
    prevStack->top = -1;
    return prevStack;
}

void pushPrev(PrevStack prevStack, TreeNode node)
{
    prevStack->stack[++(prevStack->top)] = node;
}

TreeNode popPrev(PrevStack prevStack)
{
    if (prevStack->top == -1)
    {
        return NULL;
    }
    return prevStack->stack[(prevStack->top)--];
}

TreeNode create(long val)
{
    TreeNode temp = (TreeNode)malloc(sizeof(struct TreeNode));
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int height(TreeNode root)
{
    if (root == NULL)
        return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    if (lh > rh)
        return lh + 1;
    else
        return rh + 1;
}

void currlev(TreeNode root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
    {
        if (root->val != -1)
            printf("%ld ", root->val);
    }
    else if (level > 1)
    {
        currlev(root->left, level - 1);
        currlev(root->right, level - 1);
    }
}

void printlevelorder(TreeNode root)
{
    int h = height(root);
    for (int i = 1; i <= h; i++)
        currlev(root, i);
}

void PrintRangeValues(TreeNode root, long k1, long k2)
{
    if (root == NULL)
    {
        return;
    }
    PrintRangeValues(root->left, k1, k2);

    if (root->val >= k1 && root->val <= k2)
    {
        printf("%ld ", root->val);
    }
    PrintRangeValues(root->right, k1, k2);
}

TreeNode par_to_tree(TreeNode root, int n, char a[], PrevStack prevStack,int i)
{
    // int i = 1;
    TreeNode curr = root;
    for (; i < n; i++)
    {
        if (a[i] == '(')
        {
            i++;
            if (a[i] == ')')
            {
                if (curr->left == NULL)
                    curr->left = create(-1);
                else
                    curr->right = create(-1);
            }
            else
            {
                int val = 0;

                while (i < n && a[i] >= '0' && a[i] <= '9')
                {
                    val = val * 10 + (a[i] - '0');
                    i++;
                }
                // printf("val %d\n",val);
                i--;
                TreeNode temp = create(val);
                if (curr->left == NULL)
                {
                    curr->left = temp;
                    pushPrev(prevStack, curr);
                    curr = curr->left;
                }
                else
                {
                    curr->right = temp;
                    pushPrev(prevStack, curr);
                    curr = curr->right;
                }
            }
        }
        else if (a[i] == ')')
        {
            curr = popPrev(prevStack);
        }
    }

    return root;
}

void inorderTraversal(TreeNode root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        if (root->val != -1)
            printf("%ld ", root->val);
        inorderTraversal(root->right);
    }
}

int Ancestors(TreeNode root, long target)
{
    if (root == NULL)
        return 0;
    if (root->val == target)
    {
        printf("%ld ", root->val);
        return 1;
    }
    if (Ancestors(root->left, target) || Ancestors(root->right, target))
    {
        printf("%ld ", root->val);
        return 1;
    }
    else
        return 0;
}

int main()
{
    char a[1000001];
    scanf("%s", a);
    int i=0,val=0;
    int l = strlen(a);
    while (i < l && a[i] >= '0' && a[i] <= '9')
    {
        val = val * 10 + (a[i] - '0');
        i++;
    }
    TreeNode root=create(val);
    PrevStack prevStack = createPrevStack(l);
    root = par_to_tree(root, l, a, prevStack,i);

    long k1, k2;
    char c;
    while (1)
    {
        scanf(" %c", &c);
        if(c=='e'){
            break;
        }
        switch (c)
        {
        case 'p':
            scanf(" %ld %ld", &k1, &k2);
            PrintRangeValues(root, k1, k2);
            printf("\n");
            break;
        case 'a':
            scanf(" %ld", &k1);
            Ancestors(root, k1);
            printf("\n");
            break;
        }
    }
    return 1;
}

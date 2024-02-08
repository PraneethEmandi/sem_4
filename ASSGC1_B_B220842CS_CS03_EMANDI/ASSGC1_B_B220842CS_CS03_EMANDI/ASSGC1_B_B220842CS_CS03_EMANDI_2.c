#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    long val;
    struct TreeNode* left;
    struct TreeNode* right;
};

typedef struct TreeNode* TreeNode;

struct PrevStack {
    TreeNode* stack;
    int top;
};

typedef struct PrevStack* PrevStack;
struct Info{
    int isbst,min,max,sum,currmax;
};
typedef struct Info Info;
Info maxsumbst(TreeNode root,long *maxsum){
    if(root==NULL || root->val==-1){
        Info temp;
        temp.isbst=1;
        temp.min=1000000000;
        temp.max=-1000000000;
        temp.sum=0;
        temp.currmax=0;
        return temp;
    }
    if((root->left==NULL&&root->right==NULL)||(root->left->val==-1&&root->right->val==-1)){
        Info temp;
        temp.isbst=1;
        temp.min=root->val;
        temp.max=root->val;
        temp.sum=root->val;
        
        if(temp.sum>*maxsum){
            *maxsum=temp.sum;
        }
        temp.currmax=*maxsum;
        return temp;
    }
    Info left=maxsumbst(root->left,maxsum);
    Info right=maxsumbst(root->right,maxsum);
    Info temp;
    temp.sum=left.sum+right.sum+root->val;
    if(left.isbst==1&&right.isbst==1&&left.max<root->val&&right.min>root->val){
        temp.isbst=1;
        temp.min=left.min<root->val?left.min:root->val;
        temp.max=right.max>root->val?right.max:root->val;
        if(temp.sum>*maxsum){
            *maxsum=temp.sum;
        }
        temp.currmax=*maxsum;
    }
    else{
        temp.isbst=0;
        temp.currmax=*maxsum>left.currmax?*maxsum>right.currmax?*maxsum:right.currmax:left.currmax>right.currmax?left.currmax:right.currmax;
    }
    return temp;
}
PrevStack createPrevStack(int size) {
    PrevStack prevStack = (PrevStack)malloc(sizeof(struct PrevStack));
    prevStack->stack = (TreeNode*)malloc(size * sizeof(TreeNode));
    prevStack->top = -1;
    return prevStack;
}

void pushPrev(PrevStack prevStack, TreeNode node) {
    prevStack->stack[++(prevStack->top)] = node;
}

TreeNode popPrev(PrevStack prevStack) {
    if (prevStack->top == -1) {
        return NULL;
    }
    return prevStack->stack[(prevStack->top)--];
}

TreeNode create(long val) {
    TreeNode temp = (TreeNode)malloc(sizeof(struct TreeNode));
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int height(TreeNode root) {
    if (root == NULL)
        return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    if (lh > rh)
        return lh + 1;
    else
        return rh + 1;
}

void currlev(TreeNode root, int level) {
    if (root == NULL)
        return;
    if (level == 1) {
        if(root->val!=-1)
        printf("%ld ", root->val);
    } else if (level > 1) {
        currlev(root->left, level - 1);
        currlev(root->right, level - 1);
    }
}

void printlevelorder(TreeNode root) {
    int h = height(root);
    for (int i = 1; i <= h; i++)
        currlev(root, i);
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
void rightview(TreeNode root, int h, int rv[],int *rvsize){
	if(root==NULL)
		return;
	if(h==*rvsize){
        if(root->val!=-1){
		rv[*rvsize]=root->val;
        (*rvsize)++;
        }
	}
	rightview(root->right,h+1,rv,rvsize);
	rightview(root->left,h+1,rv,rvsize);
}
int main() {
    char a[1000001];
    scanf("%s", a);
    int l = strlen(a);
    int i=0,val=0;
    // int l = strlen(a);
    while (i < l && a[i] >= '0' && a[i] <= '9')
    {
        val = val * 10 + (a[i] - '0');
        i++;
    }
    TreeNode root=create(val);
    PrevStack prevStack = createPrevStack(l);
    root = par_to_tree(root, l, a, prevStack,i);
    char c;
    int rv[100];
    int rvsize=0;
    long maxsum=0;
    Info temp;
    while(1){
        scanf(" %c",&c);
        if(c=='e')
            break;
        switch(c){
            case 'l':
                printlevelorder(root);
                printf("\n");
                break;
            case 'r':
                rightview(root,0,rv,&rvsize);
                // printf("%d\n",rvsize);
                for(int i=0;i<rvsize;i++){
                    printf("%d ",rv[i]);
                }
                printf("\n");
                break;
            case 'm':
                temp=maxsumbst(root,&maxsum);
                printf("%ld\n",maxsum);
                break;
        }
    }
    return 1;
}

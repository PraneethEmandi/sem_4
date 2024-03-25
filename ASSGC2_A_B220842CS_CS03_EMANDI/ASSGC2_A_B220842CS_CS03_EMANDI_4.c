#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct list
{
    int data;
    char colour;
    struct list* parent;
    struct list* left;
    struct list* right;
};

struct list* createnode(int val, char ch)
{
    struct list* temp = (struct list*)malloc(sizeof(struct list));
    temp->data = val;
    temp->colour = ch;
    temp->left = NULL;
    temp->parent = NULL;
    temp->right = NULL;
    return temp;
}

struct list* tree(char ch[], int *i)
{
   struct list* root = NULL;
   int temp=0,truth = 0,trust = 0;char c;
   if(ch == NULL || ch[*i] == '\0')
   {
        return NULL;
   }
   if(ch[*i] == '(')
   {
        (*i)++;
        if(ch[*i]==' ')
            (*i)++;
        while((ch[*i]-'0') >= 0 && (ch[*i]-'0') <= 9)
        {
            temp = temp*10 + (ch[*i]-'0');
            (*i)++;
            truth = 1;
        }
        if(ch[*i] == ' ')
            (*i)++;
        if(ch[*i] == 'B' || ch[*i] == 'R')
        {
            c = ch[*i];
            trust = 1;
            (*i)++;
        }
        if(truth && trust)
        {
            root = createnode(temp,c);
            (*i)++;
        }
        else
        {
            root = NULL;
        }
        if(ch[*i]=='(')
        {
            root->left = tree(ch,i);
        if (root->left != NULL)
            root->left->parent = root;
        }       
        if(ch[*i] == ' ')
        {
           (*i)++;    
        }
        if(ch[*i] == '(')
        {
             root->right = tree(ch,i);
             if (root->right != NULL)
                root->right->parent = root;
        }
        if(ch[*i] == ' ')
        {
            (*i)++;    
        }
        if(ch[*i] == ')')
        {
            (*i)++;
        }
        return root; 
   }
}

int isredblack(struct list* root)
{
    if(root == NULL)
    {
        return 1;
    }
    if(root->colour == 'R')
    {
        if((root->left != NULL && root->left->colour == 'R') || (root->right != NULL && root->right->colour == 'R'))
        {
            return 0;
        }
    }
    int left = isredblack(root->left);
    int right = isredblack(root->right);

    if((left != right) || !(left & right)) 
    {
        return -1;
    }
    return (root->colour == 'B') ? left + 1 : left;

}

int blackroot(struct list* root)
{
    if(root == NULL)
    {
        return 1; 
    }
    if(root->colour != 'B')
    {
        return 0;
    }
    if(isredblack(root) == -1)
    {
        return 0;
    }
    return 1;
} 

int isbst(struct list *root,int left, int right)
{
    if(root == NULL)
        return 1;

    if(root->data >= left && root->data <= right)
    {
        int left_check = isbst(root->left, left, root->data - 1);
        int right_check = isbst(root->right, root->data + 1, right);

        return left_check && right_check;
    }
    
    return 0;
}

int main()
{
    char ch[1000];
    int i = 0;
    fgets(ch, 1000, stdin);
    struct list* root = NULL;
    root = tree(ch, &i);
    if(isbst(root,-1,9999))
    {
    if(blackroot(root))
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }
    }
    else
    {
        printf("0\n");
    }
    return 0;
}
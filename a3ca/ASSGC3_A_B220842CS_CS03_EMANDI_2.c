#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_VERTICES 100
struct q
{
    int arr[1000];
    int front;
    int last;
};
typedef struct q* que;

que create(que q){
    q = (que)malloc(sizeof(struct q));
    q->front = 0;
    q->last = 0;
    return q;
}

que enqueue(que q, int n){
    q->arr[q->last++] = n;
    return q;
}

que dequeue(que q){
    q->front ++;
    return q;
}

int front(que q){
    return q->arr[q->front];
}

int queueEmpty(que q){
    if(q->front == q->last){
        return 1;
    }
    return 0;
}

struct stack{
    int arr[1000];
    int top;
};
typedef struct stack* stack;

stack createStack(stack s){
    s =  (stack)malloc(sizeof(struct stack));
    s->top = -1;
    return s;
}

stack spush(stack s, int n){
    s->top++;
    s->arr[s->top] = n;
    return s;
}

stack spop(stack s){
    s->top--;
    return s;
}

int stackEmpty(stack s){
    if(s->top == -1){
        return 1;
    }
    return 0;
}

int top(stack s){
    if(!stackEmpty(s)){
        return s->arr[s->top];
    }
    return -1;
}

void BFS1(int adj[][100], int n, int *deg){
    int count = 0;
    int que[1000];
    int front = 0, rear = 0;
    for(int i = 0; i < n; i++){
        if(deg[i] == 0){
            que[rear++] = i;
        }
    }
    while(front < rear){
        int current = que[front++];
        count++;
        for(int j = 0; j < n; j++){
            if(adj[current][j] != 0){
                if(-- deg[j] == 0){
                    que[rear++] = j;
                }
            }
        }
    }
    if(count != n){
        printf("-1\n");
    }
    else{
        printf("1\n");
    }
}

void fill(int n, int adj[][100], int* visited, int v, stack* s){
    visited[v] = 1;
    for(int i = 0; i < n; i++){
        if(adj[v][i] == 1){
            if(visited[i] == 0){
                fill(n, adj, visited, i, s);
            }
        }
    }
    *s = spush(*s, v);
}

void BFS2(int n, int adj[][100], int* visited, int v){
    visited[v] = 1;
    que q;
    q = create(q);
    q = enqueue(q, v);
    while(!queueEmpty(q)){
        int fr = front(q);
        q = dequeue(q);
        for(int i = 0; i < n; i++){
            if(adj[fr][i] == 1){
                if(visited[i] == 0){
                    visited[i] = 1;
                    q = enqueue(q, i);
                }
            }
        }
    }
}

void STR_CON_COMPONENTS(int n, int adj[][100]){
    stack s = createStack(s);
    int visited[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }

    int count = 0;
    for(int i = 0; i < n; i++){
        if(visited[i] == 0){
            fill(n, adj, visited, i, &s);
        }
    }
    
    int transpose[n][100];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            transpose[i][j] = adj[j][i];
        }
    }
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    while(!stackEmpty(s)){
        int num = top(s);
        s = spop(s);
        if(visited[num] == 0){
            BFS2(n, transpose, visited, num);
            count++;
        }
    }
    printf("%d\n",count);
    // return count;
}

int main(){
    int n;
    scanf("%d",&n);
    int adj[n][MAX_VERTICES];
    int deg[n];
    memset(deg, 0, sizeof(deg));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",&adj[i][j]);
            if(adj[i][j] == 1){
                deg[j]++;
            }
        }
    }
    char call;
    while(1){
        scanf("%c",&call);
        if(call == 'x'){
            return 1;
        }
        else if(call == 't'){
            BFS1(adj, n, deg);
        }
        else if(call == 'c'){
            STR_CON_COMPONENTS(n, adj);
        }
    }
}
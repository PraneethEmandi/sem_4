#include <stdio.h>
#include <stdlib.h>
struct stack{
	char* arr;
	int n;
	int top;
};
typedef struct stack* stack;
stack create(int n){
	stack st=(stack)malloc(sizeof(struct stack));
	st->n=n;
	st->top=-1;
	st->arr=(char*)malloc(sizeof(sizeof(char)*n));
	return st;
}
void push(stack st,char c, int n){
	if(st->top + 1==n){
		printf("stack is full\n");
		exit(1);
	}
	st->arr[++st->top]=c;
}
void pop(stack st){
	if(st->top==-1){
		printf("stack is empty\n");
		exit(1);
	}
	st->top--;
}
int op(char c){
	if(c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='%')
	return 1;
	else
		return 0;
}
int main(){
	int n,cnt=0;
	scanf("%d",&n);
	char s[n];
	scanf(" %s",s);
	stack st=create(n);
	for(int i=0;i<n;i++){
		if(s[i]=='('){
			//open++;
			push(st,s[i],n);
		}
		else if(s[i]==')'){
			//close++;
			if(op(st->arr[st->top])==1){
				pop(st);
				pop(st);
			}
			else
				cnt++;
		}
		else if(op(s[i])==1)
		push(st,s[i],n);
	}
	if(cnt>0)
	printf("1\n");
	else
	printf("0\n");
	return 0;
}

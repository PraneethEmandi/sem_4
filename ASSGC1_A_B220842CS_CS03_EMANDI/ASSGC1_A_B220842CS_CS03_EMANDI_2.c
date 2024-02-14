#include <stdio.h>
#include <stdlib.h>

struct node{
	int val;
	struct node* next;
};
typedef struct node* node;
node create(int val){
	node temp=(node)malloc(sizeof(struct node));
	temp->val=val;
	temp->next=NULL;
}
void display(node head){
	node temp=head;
	if(head==NULL)
	printf("-1\n");
	while(temp!=NULL){
		printf("%d ",temp->val);
		temp=temp->next;
	}
	printf("\n");
}

node insert(node head,int val){
	node temp=create(val);
	if(head==NULL){
		head=temp;
		return head;
	}
	node curr=head;
	while(curr->next!=NULL){
		curr=curr->next;
	}
	curr->next=temp;
	return head;
}
node removed(node head,int i){
	node curr=head;
	node prev=NULL;
	if(head==NULL){
		printf("-1\n");
		return head;
	}
	if(i==1){
		printf("%d\n",head->val);
		head=head->next;
		free(curr);
		return head;
	}
	while(i!=1 || curr==NULL){
		prev=curr;
		curr=curr->next;
		i--;
	}
	if(curr==NULL)
	{
		printf("-1\n");
		
	}
	else
	{
		printf("%d\n",curr->val);
		prev->next=curr->next;
		free(curr);
	}
	return head;
}
node insertb(node head,int val){
	node temp=create(val);
	if(head==NULL){
		head=temp;
		return head;
	}
	temp->next=head;
	head=temp;
	return head;
}
		
node rduplicate(node head){
	node i=head;
	node prev=head;
	node j=head->next;
	if(head==NULL){
		printf("-1\n");
		return head;
	}
	while(i!=NULL){
		while(j!=NULL){
			if(i->val==j->val){
				prev->next=j->next;
				free(j);
				j=prev->next;
				
			}
			else{
				prev=j;
				j=j->next;
			}
		}
		//if(i->next!=NULL)
		i=i->next;
		if(i!=NULL)
		j=i->next;
		prev=i;
	}
	return head;
}
int pal(node head){
	node head2=NULL;
	node temp=head;
	while(temp!=NULL){
		head2=insertb(head2,temp->val);
		temp=temp->next;
	}
	//display(head);
	//display(head2);
	temp=head;
	node temp2=head2;
	while(temp!=NULL && temp2!=NULL){
		if(temp->val!=temp2->val)
			return 0;
		temp=temp->next;
		temp2=temp2->next;
	}
	return 1;
}
int main(){
	node head=NULL;
	int val;
	char ch;
	while(1){
	scanf(" %c",&ch);
		if(ch=='e')
			break;
		else{
			switch(ch){
				case 'a':
					scanf(" %d",&val);
					head=insert(head,val);
					break;
				case 'r':
					
					scanf(" %d",&val);
					head=removed(head,val);
					break;
				case 'd':
					display(rduplicate(head));
					break;
				case 'p':
					if(pal(head)==1)
						printf("Y\n");
					else
						printf("N\n");
					break;
				case 's':
					display(head);
					break;
			}
		}
	}
	return 1;
}
					

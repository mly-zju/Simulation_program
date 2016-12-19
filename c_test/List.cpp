#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "math.h"
using namespace std;

typedef struct node{
	int data;
	struct node *next;
}Node;

Node *head=NULL;

bool createList(){
	head=(Node *)malloc(sizeof(Node));
	if(head==NULL){
		return false;
	}
	head->data=0;
	head->next=NULL;
	return true;
}

bool addNode(Node *ele){
	if(head==NULL){
		return false;
	}
	Node *p=head;
	while(p->next!=NULL){
		p=p->next;
	}
	p->next=ele;
	ele->next=NULL;
	return true;
}

Node *getNode(int index){
	int i=0;
	Node *p=head->next;
	while(i!=index){
		p=p->next;
		i++;
	}
	return p;
}

bool insertNode(Node *ele, int index){
	Node *p=getNode(index-1);
	ele->next=p->next;
	p->next=ele;
	return true;
}

bool deleteNode(int index){
	Node *p=getNode(index-1);
	Node *q=p->next;
	p->next=q->next;
	free(q);
	return true;
}

bool reverseList(){
	int length=1;
	Node *p=head->next;
	if(p==NULL){
		return false;
	}
	Node *q=p->next;
	if(q==NULL){
		return true;
	}
	Node *t=NULL;
	do{
		t=q->next;
		q->next=p;
		p=q;
		q=t;
	}while(t!=NULL);
	head->next->next=NULL;
	head->next=p;
	return true;
}

int main(){
	int i=0;
	createList();
	for(i=0;i<5;i++){
		Node *tmp=(Node *)malloc(sizeof(Node));
		tmp->data=i;
		addNode(tmp);
	}
	Node *tmp=(Node *)malloc(sizeof(Node));
	tmp->data=100;
	insertNode(tmp,2);
	deleteNode(2);
	reverseList();
	Node *p=head->next;
	for(i=0;i<5;i++){
		cout<<p->data<<" ";
		p=p->next;
	}
	

}















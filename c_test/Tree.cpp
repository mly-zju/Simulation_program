#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "math.h"
using namespace std;

typedef struct biTree{
	int data;
	struct biTree *left,*right;
}biTree;

biTree *create(){
	int da;
	scanf("%d",&da);
	getchar();
	if(da==-1){
		return NULL;
	}
	else{
		biTree *btree=(biTree *)malloc(sizeof(biTree));
		btree->data=da;
		btree->left=create();
		btree->right=create();
		return btree;
	}
}

void preOrder(biTree *bitree){
	printf("%d\n",bitree->data);
	preOrder(bitree->left);
	preOrder(bitree->right);
}













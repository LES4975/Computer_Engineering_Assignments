#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct tree {
	int num;
	struct tree* left;
	struct tree* right;
}Node;

Node* getnode();
Node* initiateTree(Node*);
void buildTree(Node*);
void preOrder(Node*);
void searchTree(Node*);
void freeTree(Node*);

int main()
{
	int n, sch;
	scanf("%d", &n);
	Node* root = NULL;
	root = initiateTree(root);
	buildTree(root);
	scanf("%d", &sch);
	for (int i = 0; i < sch; i++)
		searchTree(root);
	freeTree(root);
	return 0;
}

Node* getnode()
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->left = NULL;
	p->right = NULL;
	return p;
}

Node* initiateTree(Node* root)
{
	int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	Node* p = getnode();
	p->num = x;
	if (y != 0)
	{
		p->left = getnode();
		p->left->num = y;
	}
	if (z != 0)
	{
		p->right = getnode();
		p->right->num = z;
	}
	return p;
}

void buildTree(Node* root)
{
	if (root->left != NULL)
		preOrder(root->left);
	if (root->right != NULL)
		preOrder(root->right);
}

void preOrder(Node* p)
{
	int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	if (y != 0)
	{
		p->left = getnode();
		p->left->num = y;
	}
	if (z != 0)
	{
		p->right = getnode();
		p->right->num = z;
	}
	if (y != 0)
		preOrder(p->left);
	if (z != 0)
		preOrder(p->right);
}

void searchTree(Node* root)
{
	char LR[101];
	int len, i;
	Node* p = root;
	scanf("%s", LR);
	len = strlen(LR);
	printf(" %d", root->num);
	for (i = 0; i < len; i++)
	{
		if (LR[i] == 'L')
			p = p->left;
		if (LR[i] == 'R')
			p = p->right;
		printf(" %d", p->num);
	}
	printf("\n");
}

void freeTree(Node* p)
{
	if (p->left != NULL)
		freeTree(p->left);
	if (p->right != NULL)
		freeTree(p->right);
	free(p);
}
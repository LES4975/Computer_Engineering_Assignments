#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct tree {
	struct tree* lChild;
	struct tree* rChild;
	struct tree* parent;
	int key;
}Node;

Node* getnode();
Node* expandExternal(Node*, int);
int findElement(Node*, int);
void insertItem(Node*, int);
Node* treeSearch(Node*, int);
int removeElement(Node*, int);
int isExternal(Node*);
int isInternal(Node*);
Node* inOrderSucc(Node*);//노드의 중위순회 후계자를 반환
void reduceExternal(Node*);
void printTree(Node*);
void freeTree(Node*);

int main()
{
	char command;
	int e, flag = 1, result;
	Node* tree = getnode();
	while (flag)
	{
		scanf("%c", &command);
		getchar();
		switch (command)
		{
		case 'i':
			scanf("%d", &e);
			getchar();
			insertItem(tree, e);
			break;
		case 'd':
			scanf("%d", &e);
			getchar();
			result = removeElement(tree, e);
			if (!result)
				printf("X\n");
			else
				printf("%d\n", result);
			break;
		case 's':
			scanf("%d", &e);
			getchar();
			result = findElement(tree, e);
			if (!result)
				printf("X\n");
			else
				printf("%d\n", result);
			break;
		case 'p':
			printTree(tree);
			break;
		case 'q':
			freeTree(tree);
			flag = 0;
			break;
		default:
			printf("error!\n");
			break;
		}
	}
	return 0;
}

Node* getnode()
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->lChild = NULL;
	p->rChild = NULL;
	p->parent = NULL;
	return p;
}

int findElement(Node* T, int k)
{
	Node* p = treeSearch(T, k);
	if (isExternal(p))
		return 0;
	else
		return p->key;
}
void insertItem(Node* t, int k)
{
	Node* p = treeSearch(t, k);
	if (isInternal(p))
		return;
	else
		p = expandExternal(p, k);
}

Node* expandExternal(Node* p, int k)
{
	p->lChild = getnode();
	p->lChild->parent = p;
	p->rChild = getnode();
	p->rChild->parent = p;
	p->key = k;
	return p;
}

Node* treeSearch(Node* t, int k)
{
	if (isExternal(t))
		return t;
	if (k == t->key)
		return t;
	else if (k < t->key)
		return treeSearch(t->lChild, k);
	else
		return treeSearch(t->rChild, k);
}

int removeElement(Node* t, int k)
{
	Node* w = treeSearch(t, k);
	if (isExternal(w))
		return 0;
	Node* z = w->lChild;
	int elem = w->key;
	if (!isExternal(z))
		z = w->rChild;
	if (isExternal(z))//case 1
		reduceExternal(z);
	else//case 2
	{
		Node* y = inOrderSucc(w);
		if (y == NULL)
			reduceExternal(z);
		else
		{
			z = y->lChild;
			w->key = y->key;//set node w to y->key
			reduceExternal(z);
		}
	}
	return elem;
}

int isExternal(Node* w)
{
	if (w->lChild == NULL || w->rChild == NULL)
		return 1;
	else
		return 0;
}

int isInternal(Node* w)
{
	if (w->lChild != NULL || w->rChild != NULL)
		return 1;
	else
		return 0;
}

Node* inOrderSucc(Node* w)//노드의 중위순회 후계자를 반환
{
	w = w->rChild;
	while (isInternal(w->lChild))
		w = w->lChild;
	return w;
}

Node* sibling(Node* w)
{
	if (w->parent == NULL)
		return NULL;//invalidNodeException()
	if (w->parent->lChild == w)
		return w->parent->rChild;
	else
		return w->parent->lChild;
}

void reduceExternal(Node* z)
{
	Node* w = z->parent;
	Node* zs = sibling(z);
	if (w->parent == NULL)
	{
		Node* tmp = w;
		w = zs;
		zs->parent = NULL;
		free(tmp);
	}
	else
	{
		Node* g = w->parent;
		zs->parent = g;
		if (w == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
		free(w);
	}
	free(z);
}

void printTree(Node* t)
{
	if (isExternal(t))
		return;
	else
		printf(" %d", t->key);
	if (t->lChild != NULL)
		printTree(t->lChild);
	if (t->rChild != NULL)
		printTree(t->rChild);
}

void freeTree(Node* t)
{
	if (t->lChild != NULL)
		freeTree(t->lChild);
	if (t->rChild != NULL)
		freeTree(t->rChild);
	if (t != NULL)
		free(t);
}
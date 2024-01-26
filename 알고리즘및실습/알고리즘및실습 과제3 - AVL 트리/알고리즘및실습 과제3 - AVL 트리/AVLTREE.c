#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct tree {
	struct tree* lChild;
	struct tree* rChild;
	int key;
	int height;
	struct tree* parent;
}Node;

Node* getnode();
void expandExternal(Node*);
int findElement(Node*, int);
void insertItem(Node*, int);
Node* treeSearch(Node*, int);
int removeElement(Node*, int);
//int removeElement(Node*, int);
int isExternal(Node*);
int isInternal(Node*);
Node* inOrderSucc(Node*);//노드의 중위순회 후계자를 반환
Node* reduceExternal(Node*);
void printTree(Node*);
void freeTree(Node*);
void searchAndFixAfterInsertion(Node*);
Node* restructure(Node* x, Node*, Node*);
int updateHeight(Node*);
int isBalanced(Node*);
void searchAndFixAfterRemoval(Node*);

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
		/*case 'd':
			scanf("%d", &e);
			getchar();
			result = removeElement(tree, e);
			if (!result)
				printf("X\n");
			else
				printf("%d\n", result);
			break;
			*/
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
			printf("\n");
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
	Node* w = treeSearch(t, k);
	if (isInternal(w))
		return;
	else
	{
		w->key = k;
		expandExternal(w);
		searchAndFixAfterInsertion(w);
		return;
	}
}

void expandExternal(Node* w)
{
	Node* l = getnode();
	Node* r = getnode();

	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = w;
	l->height = 0;

	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = w;
	r->height = 0;

	w->lChild = l;
	w->rChild = r;
	w->height = 1;
	return;

	/*
	p->lChild = getnode();
	p->lChild->parent = p;
	p->rChild = getnode();
	p->rChild->parent = p;
	p->key = k;
	return p;
	*/
	
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

Node* reduceExternal(Node* z)
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
	return zs;
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

void searchAndFixAfterInsertion(Node* w)
{
	w->lChild->height = 0;
	w->rChild->height = 0;
	w->height = 1;
	if (w->parent == NULL)
		return;
	Node* z = w->parent;
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;
	//불균형 고치기
	Node* x = NULL, *y = NULL;
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else
		x = y->rChild;
	Node* p = restructure(x, y, z);
}

Node* restructure(Node* x, Node* y, Node* z)
{
	//y는 x와 z의 부모
	Node*a, *b, *c, * T0, * T1, * T2, * T3;
	if (z->key < y->key && y->key < x->key)
	{
		a = z, b = y, c = x;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = c->lChild;
		T3 = c->rChild;
	}
	else if (x->key < y->key && y->key < z->key)
	{
		a = x, b = y, c = z;
		T0 = a->lChild;
		T1 = a->rChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else if (z->key < x->key && x->key < y->key)
	{
		a = z, b = x, c = y;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else//y<x<z
	{
		a = y, b = x, c = z;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}

	if (z->parent == NULL)//z가 루트노드가 되었을 때
	{
		z = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z)
	{
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else //z->parent->rChild==z
	{
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	//T0와 T1을 a의 왼쪽, 오른쪽 서브트리로 만들기
	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);
	//T2와 T3을 c의 왼쪽, 오른쪽 서브트리로 만들기
	c->lChild = T2;
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	//a와 c를 b의 왼쪽, 오른쪽 자식으로 만들기
	b->lChild = a;
	b->rChild = c;
	updateHeight(b);
	return b;
}

int updateHeight(Node* w)
{
	int h;
	if (w->lChild->height > w->rChild->height)
		h = w->lChild->height;
	else
		h = w->rChild->height;
	if (h != w->height)
	{
		w->height = h;
		return 1;
	}
	else
		return 0;
}

int isBalanced(Node* w)
{
	return(abs(w->lChild->height - w->rChild->height) < 2 ? 1 : 0);
}

int removeElement(Node* T, int k)
{
	Node* w = treeSearch(T, k);
	if (isExternal(w))
		return -1;
	Node* z = w->lChild, *zs;
	if (!isExternal(z))
		z = w->rChild;
	if (isExternal(z))
		zs = reduceExternal(z);
	else
	{
		Node* y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		zs = reduceExternal(z);
	}
	searchAndFixAfterRemoval(zs->parent);
	return k;
}

void searchAndFixAfterRemoval(Node* z)
{
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;

	//불균형 고치기
	Node* y = NULL, *x = NULL;
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else if (y->lChild->height < y->rChild->height)
		x = y->rChild;
	else
		if (z->lChild == y)
			x = y->lChild;
	Node* b = restructure(x, y, z);
	if (b->parent == NULL)
		return;
	searchAndFixAfterRemoval(b->parent);

}
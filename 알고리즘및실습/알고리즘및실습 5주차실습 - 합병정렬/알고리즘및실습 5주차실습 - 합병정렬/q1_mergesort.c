#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct list {
	struct list* next;
	int elem;
}Node;

Node* getnode();
Node* createList(int);
Node* mergeSort(Node*, int);//합병정렬하여 정렬된 결과를 오름차순으로 정렬
//int* rMergeSort(int*, int, int);
Node* merge(Node*, Node*);
void partition(Node*, int);
void printList(Node*);
void freeNode(Node*);

Node* L1 = NULL, * L2 = NULL;
int n1, n2;

int main()
{
	int n;
	scanf("%d", &n);
	Node* L = createList(n);
	L = mergeSort(L, n);
	printList(L);
	freeNode(L);
	return 0;
}

Node* getnode()
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->next = NULL;
	return p;
}

Node* createList(int n)
{
	int e;
	Node* L = NULL, * p = L;
	for (int i = 0; i < n; i++)
	{
		p = getnode();
		scanf("%d", &e);
		p->elem = e;
		p = p->next;
	}
	return L;
}

Node* mergeSort(Node* L, int n)
{
	if (L->next != NULL)
	{
		partition(L, n / 2);
		n1 = n / 2;
		n2 = n - n / 2;
		mergeSort(L1, n1);
		mergeSort(L2, n2);
		L = merge(L1, L2);
	}
	return L;
}

Node* merge(Node* L1, Node* L2)
{
	Node* L = NULL, *tmp = NULL;
	while (L1 != NULL && L2 != NULL)
	{
		if (L1->elem <= L2->elem)
		{
			tmp = L1->next;
			L = L1;
			L = L->next;
		}
		else
		{
			tmp = L2->next;
			L = L2;
			L = L->next;
		}
	}
	while (L1 != NULL)
	{
		tmp = L1->next;
		L = L1;
		L = L->next;
	}
	while (L2 != NULL)
	{
		tmp = L2->next;
		L = L2;
		L = L->next;
	}
	return L;
}

void partition(Node* L, int k)
{
	Node* p = L;
	L1 = L;
	for (int i = 2; i <= k; i++)
		p = p->next;
	L2 = p->next;
	p->next = NULL;
}

void printList(Node* L)
{
	Node* p = L;
	while (p != NULL)
	{
		printf(" %d", p->elem);
		p = p->next;
	}
}

void freeNode(Node* L)
{
	Node* p = L, *tmp = NULL;
	while (p != NULL)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}
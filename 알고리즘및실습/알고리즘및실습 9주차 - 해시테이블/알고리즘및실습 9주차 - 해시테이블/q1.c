#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
//분리연쇄법

typedef struct Hash{
	struct Hash* chain;
	int key;
}Node;

Node* getnode();
int findElement(Node*, int, int);//탐색
void insertItem(Node*, int, int);//삽입
Node* initBucketArray(int);//초기화
int removeElement(Node*, int, int);//삭제
void printHash(Node*, int);//출력
void freeNode(Node*, int);

int main()
{
	char command;
	int m, x, flag = 1;
	Node* A = NULL;
	scanf("%d", &m);
	getchar();
	A = initBucketArray(m);
	while (flag)
	{
		scanf("%c", &command);
		switch (command)
		{
		case 'i' :
			scanf("%d", &x);
			getchar();
			insertItem(A, m, x);
			break;
		
		case 's' :
			scanf("%d", &x);
			getchar();
			printf("%d\n", findElement(A, m, x));
			break;
			
		case 'd' :
			scanf("%d", &x);
			getchar();
			printf("%d\n", removeElement(A, m, x));
			break;
		
		case 'p' :
			getchar();
			printHash(A, m);
			break;
			
		case 'e' : 
			flag = 0;
			break;

		default :
			printf("error!\n");
			flag = 0;
			break;
		}
	}
	freeNode(A, m);
	return 0;
}

Node* getnode()
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->chain = NULL;
	return p;
}
/*
Node** initBucketArray(int m)
{
	Node** p = (Node**)malloc(sizeof(Node*) * m);
	for (int i = 0; i < m; i++)
		p[i] = NULL;
		//p[i]->chain = NULL;
	return p;
}
*/
Node* initBucketArray(int m)
{
	Node* p = (Node*)malloc(sizeof(Node) * m);
	for (int i = 0; i < m; i++)
		p[i].chain = NULL;//empty list
	return p;
}

int findElement(Node* A, int m, int k)
{
	int v = k % m, count = 0;
	Node* p = A + v;
	while (1)
	{
		if (p->chain == NULL)
			return 0;
		p = p->chain;
		count++;
		if (p->key == k)
			return count;
	}
}

void insertItem(Node* A, int m, int k)
{
	int v = k % m;
	Node* p = A + v;
	Node* tmp = getnode();
	tmp->key = k;
	if (p->chain == NULL)
		p->chain = tmp;
	else
	{
		tmp->chain = p->chain;
		p->chain = tmp;
	}
}
/*
int rfindElement(Node* p, int k, int count)//chain으로 내려가 원소를 탐색함
{
	if (p->key == k)
		return count + 1;
	else
	{
		if (isEmpty(p->chain))
			return 0;
		else
			return rfindElement(p->chain, k, count + 1);//자료형이 맞는 지 확인할 것
	}
}
*/
/*
void insertItem(Node** A, int m, int k)
{
	int v = k % m;
	Node* tmp = NULL, * p = getnode();
	//A[v].insertItem(k,e)
	if (isEmpty(A[v]))
	{
		A[v]->chain = p;
	}
	else	//충돌할 경우 작성
	{
		tmp = A[v]->chain;
		A[v]->chain = p;
		A[v]->chain->chain = tmp;
	}
}*/

int removeElement(Node* A, int m, int k)
{
	int v = k % m, count = 0;
	Node* p = A + v;
	while (1)
	{
		if (p->chain == NULL)
return 0;
		else
		{
		Node* tmp = p;
		p = p->chain;
		count++;
		if (p->key == k)
		{
			tmp->chain = p->chain;
			free(p);
			return count;
		}
		}
	}
}
/*
int removeElement(Node** A, int m, int k)
{
	int v = k % m;
	if (isEmpty(A[v]))
		return 0;
	else
	{
		if (k == A[v]->chain->key)
		{
			Node* tmp = A[v]->chain;
			A[v]->chain = A[v]->chain->chain;
			free(tmp);
			return 1;
		}
		else
			return rremoveElement(A[v]->chain, k, 1);
	}
}
*/
/*
int rremoveElement(Node* p, int k, int count)
{
	if (p->key == k)
	{
		//노드 삭제
		Node* tmp = p->chain;
		p->chain = p->chain->chain;
		free(tmp);
		return count + 1;
	}

	else
	{
		if (isEmpty(p->chain))
			return 0;
		else
			return rremoveElement(p->chain, k, count + 1);//자료형이 맞는 지 확인할 것
	}
}
*/

void printHash(Node* A, int m)
{
	Node* p = NULL;
	for (int i = 0; i < m; i++)
	{
		p = A + i;
		if (p->chain != NULL)
		{
			//p = p->chain;
			//printf(" %d", p->key);
			while (p->chain != NULL)
			{
				p = p->chain;
				printf(" %d", p->key);
			}
		}
	}
	printf("\n");
}

void freeNode(Node* A, int m)
{
	Node* p = NULL, *tmp = NULL;
	for (int i = 0; i < m; i++)
	{
		if ((A + i)->chain != NULL)
		{
			p = (A + i)->chain;
			tmp = p;
			while (tmp->chain != NULL)
			{
				p = p->chain;
				free(tmp);
				tmp = p;
			}
		}
	}
	free(A);
}
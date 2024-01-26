#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct list {
	int element;
	struct list* prev;
	struct list* next;
}Node;

Node* getnode();
void init(Node*, Node*);
void add(Node*, Node*, int, char);
void addNodebefore(Node*, char);
void delete(Node*, Node*, int);
char deleteNode(Node*);
char get(Node*, int);
void print(Node*, Node*);
void freeList(Node*, Node*);

int len = 0;

int main()
{
	int n, i, r;
	char cal, e;
	Node* head = getnode();
	Node* tail = getnode();
	init(head, tail);
	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++)
	{
		scanf("%c", &cal);
		getchar();
		switch (cal)
		{
		case 'A':
			scanf("%d", &r);
			getchar();
			scanf("%c", &e);
			getchar();
			add(head, tail, r, e);
			break;
		case 'D':
			scanf("%d", &r);
			getchar();
			delete(head, tail, r);
			break;
		case 'G':
			scanf("%d", &r);
			getchar();
			e = get(head, r);
			if (e != '0')
			{
				printf("%c\n", e);
			}
			break;
		case 'P':
			print(head, tail);
			printf("\n");
			break;
		default:
			printf("error!");
		}
	}
	freeList(head, tail);
	return 0;
}

Node* getnode()
{
	Node* p;
	p = (Node*)malloc(sizeof(Node));
	p->prev = NULL;
	p->next = NULL;
	return p;
}

void init(Node* h, Node* t)
{
	h->next = t;
	t->prev = h;
}

void add(Node* H, Node* T, int r, char e)
{
	if (r<1 || r>len + 1)
		printf("invalid position\n");
	else
	{
		if (len == 0)
		{
			Node* p = getnode();
			p->prev = H;
			p->next = T;
			H->next = p;
			T->prev = p;
			p->element = e;
		}
		else
		{
			Node* p = H;
			for (int i = 1; i <= r; i++)
				p = p->next;
			addNodebefore(p, e);
		}
		len++;
	}
}

void addNodebefore(Node* p, char e)
{
	Node* q = getnode();
	q->element = e;
	q->prev = p->prev;
	q->next = p;
	p->prev = q;
	q->prev->next = q;
}

void delete(Node* H, Node* T, int r)
{
	if (r<1 || r>len)
		printf("invalid position\n");
	else
	{
		Node* p = H;
		for (int i = 1; i <= r; i++)
			p = p->next;
		char e = deleteNode(p);
		len--;
	}
}

char deleteNode(Node* p)
{
	char e = p->element;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
	return e;
}

char get(Node* H, int r)
{
	if (r<1 || r>len)
	{
		printf("invalid position\n");
		return '0';
	}
	Node* p = H;
	for (int i = 1; i <= r; i++)
		p = p->next;
	return p->element;
}
void print(Node* H, Node* T)
{
	Node* p = H->next;
	while (p != T)
	{
		printf("%c", p->element);
		p = p->next;
	}
}

void freeList(Node* H, Node* T)
{
	Node* p = H;
	while (p != T)
	{
		p = p->next;
		free(p->prev);
	}
	free(T);
}
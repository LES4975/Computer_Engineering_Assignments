#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct list {
	int edge_index;
	struct list* next;
}Node;

typedef struct vertex {
	int vname;
	Node* incd;
	int d, p;//label
}Vertex;

typedef struct edge {
	int ename;
	int v1, v2;
	int weight;
}Edge;

typedef struct graph {
	Vertex* V;
	int V_size;
	Edge* E;
	int E_size;
}Graph;

typedef struct queue {
	int* arr;
	int f;
	int r;
	int N;
}Queue;

Node* getnode(int, Node*);
int opposite(Graph*, Node*, int);
void set_Edge(Graph*, int, int, int, int);
void insert_incd(Graph*, int, int, int);
void insert_Edge(Graph*, int, int, int, int);
void init_Vertex(Graph*, int);
void init_Edge(Graph*, int);
void build_Graph(Graph*, int, int);
void free_incd(Node*);
void free_Graph(Graph*);
void prim_JarnikMST(Graph*);



int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	Graph* G = (Graph*)malloc(sizeof(Graph));
	build_Graph(G, n, m);

	//알고리즘 수행
	prim_JarnikMST(G);

	free_Graph(G);
	return 0;
}

Node* getnode(int index, Node* linked)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->edge_index = index;
	p->next = linked;
	return p;
}

int opposite(Graph* G, Node* p, int vs)
{
	Edge e = G->E[p->edge_index];
	if (e.v1 == vs)
		return e.v2;
	else
		return e.v1;
}

void set_Edge(Graph* G, int index, int v1, int v2, int w)
{
	G->E[index].ename = index;
	G->E[index].v1 = v1;
	G->E[index].v2 = v2;
	G->E[index].weight = w;
}

void insert_incd(Graph* G, int index, int vs, int vd)
{
	Node* p = G->V[vs].incd, *tmp;
	while (p->next != NULL && opposite(G, p->next, vs) < vd)
	{
		printf("다음 노드로 이동\n");
		p = p->next;
	}

	if (p == G->V[index].incd)
		printf("head에 위치함\n");
	tmp = getnode(index, p->next);
	p->next = tmp;
	printf("insert_incd가 안 되나?\n");
}

void insert_Edge(Graph* G, int index, int v1, int v2, int w)
{
	set_Edge(G, index, v1, v2, w);
	insert_incd(G, index, v1, v2);
	if (v1 != v2)
		insert_incd(G, index, v2, v1);
}

void init_Vertex(Graph* G, int vsize)
{
	G->V = (Vertex*)malloc(sizeof(Vertex) * vsize);
	G->V_size = vsize;

	for (int i = 0; i < vsize; ++i)
	{
		G->V[i].vname = i;
		G->V[i].incd = getnode(-1, NULL);
	}
}

void init_Edge(Graph* G, int esize)
{
	G->E = (Edge*)malloc(sizeof(Edge) * esize);
	G->E_size = esize;

	int i;
	for (i = 0; i < esize; ++i)
	{
		G->E[i].ename = -1;
		G->E[i].v1 = -1;
		G->E[i].v2 = -1;
	}

	//정점과 간선 정보 입력받기
	int v1, v2, w;
	for (i = 0; i < esize; ++i)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		insert_Edge(G, i, v1, v2, w);
		printf("간선 입력 완료 : G->E[%d] : %d - %d : %d\n", i, G->E[i].v1, G->E[i].v2, G->E[i].weight);
	}
}
	

void build_Graph(Graph* G, int n, int m)
{
	init_Vertex(G, n);
	init_Edge(G, m);
}

void free_incd(Node* p)
{
	Node* tmp;
	while (p != NULL)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

void free_Graph(Graph* G)
{
	for (int i = 0; i < G->V_size; ++i)
		free_incd(G->V[i].incd);
	free(G->V);
	free(G->E);
	free(G);
}

void prim_JarnikMST(Graph* G)
{
	int i, u, z;
	Node* p = NULL;
	for (i = 0; i < G->V_size; ++i)
	{
		G->V[i].d = 9999;
		G->V[i].p = -1;
	}
	G->V[1].d = 0;
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->arr = (int*)malloc(sizeof(int) * G->V_size);
	for (i = 0; i < G->V_size; ++i)
		Q->arr[i] = G->V[i].vname;
	for (i = 0; i < G->V_size; i++)
		printf(" %d", Q->arr[i]);
	while (!isEmpty(Q))
	{
		u = removeMin(Q);
		p = G->V[u].incd->next;
		while (p != NULL)
		{
			z = opposite(G, p, u);
			if (G->E[p->edge_index].weight < G->V[z].d)//&&z in Q?
			{
				G->V[z].d = G->E[p->edge_index].weight;
				//p(z)<-e;
				//Q.replaceKey(z, G->E[p->edge_index].weight);
			}
		}
	}
}

int isEmpty(Queue* Q)
{
	if ((Q->r + 1) % Q->N == Q->f)
		return 1;
	else
		return 0;
}

int isFull(Queue* Q)
{
	if ((Q->r + 2) % Q->N == Q->f)
		return 1;
	else
		return 0;
}

void enqueue(Queue* Q, int e)
{
	if (isFull(Q))
		return;//fullQueueException()
	Q->r = (Q->r + 1) % Q->N;
	Q->arr[Q->r] = e;
}

int dequeue(Queue* Q)
{
	if (isEmpty(Q))
	{
		return 0;//emptyQueueException()
	}
	int e = Q->arr[Q->f];
	Q->f = (Q->f + 1) % Q->N;
	return e;
}

int removeMin(Queue* Q)
{
	int i, min = Q->arr[0];
	for (i = 0; i < Q->N; i++)
	{
		if (Q->arr[i] < min)
			min = Q->arr[i];
	}
	return min;
}
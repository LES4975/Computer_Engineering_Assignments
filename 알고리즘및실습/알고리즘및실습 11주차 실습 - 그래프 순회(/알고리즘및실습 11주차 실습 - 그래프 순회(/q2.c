#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define FRESH 0
#define Visited 1
#define TREE 2
#define CROSS 3

typedef struct vertex {
	int name;
	int label;
}Vertex;

typedef struct edges {
	int end1;
	int end2;
	int label;
}Edge;

typedef struct adj_graph {
	Vertex* V;
	Edge* E;
	int** adj_m;
	int V_n;
	int E_n;
}Graph;

typedef struct Queue {
	int front;
	int rear;
	int* q;
}Queue;

Graph* init_Graph(int, int);
int** init_adjancency(int);
void insert_Edge(Graph*, int, int, int);
void print_Graph(Graph*);
void free_Graph(Graph*);



int main()
{
	int n, m, s, v1, v2;
	scanf("%d %d %d", &n, &m, &s);
	Graph* G = init_Graph(n, m);

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &v1, &v2);
		insert_Edge(G, v1, v2, i);
	}
	print_Graph(G);
	//BFS(G);
	free_Graph(G);
	return 0;
}

Graph* init_Graph(int n, int m)
{
	//정점 생성하기
	Graph* G = (Graph*)malloc(sizeof(Graph));
	Vertex* v = (Vertex*)malloc(sizeof(Vertex)*n);
	G->V = v;
	G->V_n = n;
	for (int i = 0; i < G->V_n; i++)
	{
		v[i].name = i + 1;
		v[i].label = 0;
	}
	G->adj_m = init_adjancency(n);
	Edge* e = (Edge*)malloc(sizeof(Edge) * m);
	G->E = e;
	G->E_n = m;
	for (int i = 0; i < m; i++)
	{
		e[i].end1 = 0;
		e[i].end2 = 0;
		e[i].label = 0;
	}
	return G;
}

int** init_adjancency(int n)
{
	//인접행렬 생성하기
	int i, j;
	int** arr = (int**)malloc(sizeof(int*) * n);
	for (i = 0; i < n; i++)
		arr[i] = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			arr[i][j] = -1;
	return arr;
}

void insert_Edge(Graph* G, int v1, int v2, int index)
{
	//간선 추가하기
	int** p = G->adj_m;
	p[v1 - 1][v2 - 1] = index;
	p[v2 - 1][v1 - 1] = index;
	Edge* e = G->E;
	e[index].end1 = v1;
	e[index].end2 = v2;
}


void print_Graph(Graph* G)
{
	Vertex* v = G->V;
	int** p = G->adj_m;
	Edge* e = G->E;
	for (int i = 0; i < G->V_n; i++)
	{
		printf("%d :", v[i].name);
		for (int j = 0; j < G->V_n; j++)
		{
			if (p[i][j] != -1)
				printf(" %d ", j + 1);
		}
		printf("\n");
	}
}

/*
void BFS(Graph* G)
{
	Vertex* v = G->V;
	for (int i = 0; i < G->V_n; i++)
	{
		if (v[i].label == 0)
			BFS1(G, &v[i]);
	}
}
*/

void free_Graph(Graph* G)
{
	int i;
	int** p = G->adj_m;
	for (i = 0; i < G->V_n; i++)
		free(p[i]);
	free(p);
	free(G->E);
	free(G->V);
	free(G);
}

/*
Queue* createQueue(Graph* G)
{
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->q = (int*)malloc(sizeof(int) * 100);
	Q->front = 0;
	Q->rear = 0;
	return Q;
}

void enqueue(Queue* Q, int elem)
{

}
*/

void BFS(Graph* G, int s)
{
	int* L = (int*)malloc(sizeof(int) * G->V_n);
	L[0] = G->V[s - 1].name;
	G->V[s - 1].label = 1; //visited
	int i = 0, w;
	int** p;
	while (!isEmpty(L[i]))
	{

		for (int j = 0; j < G->V_n; j++)
		{
			if (G->E[p[s - 1][j]].label == 0)
			{
				w = opposite(G, s, p[s - 1][j]);
				if (G->V[w - 1].label == 0)
				{
					G->V[w - 1].label == 1;
					
				}
			}
		}
	}
}

int** createList(Graph* G)
{
	int** L = (int*)malloc(sizeof(int*) * G->V_n);
	for (int i = 0; i < G->V_n; i++)
	{
		L[i] = (int*)malloc(sizeof(int) * G->V_n);
		for (int j = 0; j < G->V_n; j++)
			L[i][j] = -1;
	}
}

int isEmpty(int* list)
{
	if (list[0] == -1)
		return 1;
	else
		return 0;
}

int opposite(Graph* G, int v, int index)
{
	if (G->E[index].end1 == v)
		return G->E[index].end2;
	else
		return G->E[index].end1;
}

/*
void BFS(Graph* G, int vertex)
{
	Queue* Q = createQueue();
	int i = 0;
	enqueue(Q, vertex);
	printf("%d visited \n", vertex);

	while (!isEmpty(Q))
	{
		vertex = dequeue(Q);
		for(i = vertex;i<G->V_n;i++)
			if (!G->V[i].label && G->adj_m[vertex][i] != -1)
			{
				G->V[i].label = 1;
				enqueue(Q, i);
				printf("%d visited\n", i);
			}
	}

}
*/
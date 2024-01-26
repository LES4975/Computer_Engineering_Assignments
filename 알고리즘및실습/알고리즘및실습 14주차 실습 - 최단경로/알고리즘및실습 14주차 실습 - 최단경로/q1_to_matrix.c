#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct vertex{
	int name;
	int d;
}Vertex;

typedef struct edges {
	int weight;
	int end1;
	int end2;
}Edge;

typedef struct adj_graph {
	Vertex* V;
	Edge* E;
	int** adj_m;
	int vsize;
	int esize;
}Graph;


Graph* init_Graph(int, int);
void set_Edge(Graph*);
void DijkstraShortestPaths(Graph*, int);

int* Q;
int Last = -1;

//가중치는 20을 넘지 않는다.
//중복 입력되는 간선은 없다.
//간선은 임의의 순서로 입력된다.

int main()
{
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	Graph* G = init_Graph(n, m);
	set_Edge(G);
	//그래프 설정 완료

	//최단거리 찾기
	DijkstraShortestPaths(G, s);

	free_Graph(G);
	return 0;
}

void DijkstraShortestPaths(Graph* G, int s)
{
	int i, u;
	for (i = 0; i <= G->vsize; ++i)
		G->V[i].d = 90000;
	G->V[s].d = 0;
	//Queue 생성
	Q = init_Queue(G->vsize);
	while (!Q_isEmpty())
	{
		u = removeMin();
	}
	

}

int* init_Queue(int vsize)
{
	Q = (int*)malloc(sizeof(int) * vsize);
	return Q;
}

int Q_isEmpty()
{
	if (Last == -1)
		return 1;
	else
		return 0;
}

int removeMin()
{
	int k = Q[0];
	int w = Q[Last];
	Q[0] = w;
	Last--;
	//z=rightChild(int w)
}

Graph* init_Graph(int n, int m)
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	int i;
	G->vsize = n;
	G->esize = m;
	for (i = 0; i < G->vsize; i++)
		G->V[i].name = i;
	G->adj_m = init_adjancency(G);
	for (i = 0; i < G->esize; i++)
	{
		G->E[i].end1 = -1;
		G->E[i].end2 = -1;
		G->E[i].weight = -1;
	}
	return G;
}

int** int_adjancency(Graph* G)
{
	int i, j;
	int** arr = (int**)malloc(sizeof(int*) * G->vsize);
	for (i = 0; i <= G->vsize; ++i)
		arr[i] = (int*)malloc(sizeof(int*) * G->vsize);
	for (i = 0; i <= G->vsize; ++i)
		for (j = 0; j <= G->vsize; ++j)
			for (j = 0; j < G->vsize; ++j)
				arr[i][j] = -1;
	return arr;
}

void set_Edge(Graph* G)
{
	int v1, v2, w;
	for (int i = 0; i < G->esize; i++)
	{
		scanf("%d %d %d", v1, v2, w);
		insert_Edge(G, i, v1, v2, w);
	}
}

void insert_Edge(Graph* G, int index, int a, int b, int w)
{
	int** p = G->adj_m;
	p[a][b] = index;
	p[b][a] = index;
	G->E[index].end1 = a;
	G->E[index].end2 = b;
	G->E[index].weight = w;
}

int opposite(Graph* G, int index, int vs)
{
	if (vs == G->E[index].end1)
		return G->E[index].end2;
	else
		return G->E[index].end1;
}

void free_Graph(Graph* G)
{
	for (int i = 0; i <= G->vsize; i++)
		free(G->adj_m[i]);
	free(G->adj_m);
	free(G->V);
	free(G->E);
	free(G);
}
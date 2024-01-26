#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct incidence {
	struct incidence* next;
	int edge_index;
}Adj;

typedef struct vertex {
	int vname;
	Adj* head;
}Vertex;

typedef struct edge {
	int index;
	int vs, vd;
	int weight;
}Edge;

typedef struct graph {
	int vsize, esize;
	Vertex* V;
	Edge* E;
}Graph;


Adj* getnode();
Graph* init_Graph(int, int);
void set_Vertex(Graph*, int);
void set_Edge(Graph*, int, int, int, int);
void insert_Adj(Graph*, Adj*, int);
int sum_of_weight(Graph*, int);
void free_Graph(Graph*);
void free_Adj(Graph*, int);
//void print_Graph(Graph*);

int main()
{
	int n, m, total_weight;
	scanf("%d %d", &n, &m);
	Graph* G = init_Graph(n, m);
	//print_Graph(G);
	//printf("그래프 출력 끝\n");
	for (int i = 0; i < G->vsize; i++)
	{
		total_weight = sum_of_weight(G, i);
		printf("%d %d\n", G->V[i].vname, total_weight);
	}
	free_Graph(G);
	return 0;
}

Adj* getnode()
{
	Adj* p = (Adj*)malloc(sizeof(Adj));
	p->next = NULL;
	p->edge_index = -1;
	return p;
}

Graph* init_Graph(int n, int m)
{
	int i, vs, vd, w;
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->V = (Vertex*)malloc(sizeof(Vertex) * n);
	G->vsize = n;
	G->E = (Edge*)malloc(sizeof(Edge) * m);
	G->esize = m;
	for (i = 0; i < n; i++)
		set_Vertex(G, i);

	for (i = 0; i < G->esize; i++)
	{
		scanf("%d %d %d", &vs, &vd, &w);
		set_Edge(G, i, vs, vd, w);
	}
	return G;
}

void set_Vertex(Graph* G, int i)
{
	G->V[i].vname = i + 1;
	G->V[i].head = getnode();
}

void set_Edge(Graph* G, int index, int vs, int vd, int weight)
{
	G->E[index].index = index;
	G->E[index].vs = vs;
	G->E[index].vd = vd;
	G->E[index].weight = weight;
	Adj* p = G->V[vs - 1].head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	insert_Adj(G, p, index);
}

void insert_Adj(Graph* G, Adj* p, int index)
{
	p->next = getnode();
	p->next->edge_index = index;
}

int sum_of_weight(Graph* G, int v_index)
{
	Adj* p;
	int Sum = 0;
	p = G->V[v_index].head;
	if (p->next == NULL)
		return 0;
	while (p->next != NULL)
	{
		Sum = Sum + G->E[p->next->edge_index].weight;
		p = p->next;
	}
	return Sum;
}

void free_Graph(Graph* G)
{
	int i;
	for (i = 0; i < G->vsize; i++)
		free_Adj(G, i);
	free(G->V);
	free(G->E);
	free(G);
}

void free_Adj(Graph* G, int index)
{
	Adj* p = G->V[index].head, *tmp;
	while (p != NULL)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

/*
void print_Graph(Graph* G)
{
	int i, edge_i;
	Adj* p;
	for (i = 0; i < G->vsize; i++)
	{
		printf("%d : ", G->V[i].vname);
		p = G->V[i].head;
		while (p->next != NULL)
		{
			edge_i = p->next->edge_index;
			printf("%d(%d) ", G->E[edge_i].vd, G->E[edge_i].weight);
			p = p->next;
		}
		printf("\n");
	}
}
*/
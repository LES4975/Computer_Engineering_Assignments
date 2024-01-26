#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Graph_Edge {
	int edge_index;
	int end1;
	int end2;
	int e_label;
}Edge;

typedef struct adj_list {
	struct adj_list* linked;
	int edge_index;
}Adj;

typedef struct Graph_Vertex {
	int name;
	int v_label;
	Adj* head;
}Vertex;

typedef struct graph {
	Vertex* V;
	Edge* E;
	int V_n;
	int E_n;
	int E_size;//현재 E 크기
}Graph;

Adj* get_list(int, Adj*);
int opposite(Graph*, Adj*, int);
void init_Vertex(Graph*, int);
void init_Graph(Graph*, int, int);
void init_Edge(Graph*, int);
void insert_Edge(Graph*, int, int, int);
void set_Edge(Graph*, int, int, int);
void insert_Adj(Graph*, int, int, int);
void free_Graph(Graph*);
void free_Adj(Adj*);
//void print_vertex(Graph*, int);
void DFS(Graph*, int);
void rDFS(Graph*, int);

int main()
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	int n, m, s, v1, v2;
	scanf("%d %d %d", &n, &m, &s);
	init_Graph(G, n, m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &v1, &v2);
		insert_Edge(G, i, v1, v2);
	}
	DFS(G, s);
	free_Graph(G);
	return 0;
}

Adj* get_list(int index, Adj* link)
{
	Adj* p = (Adj*)malloc(sizeof(Adj));
	p->edge_index = index;
	p->linked = link;
	return p;
}

int opposite(Graph* G, Adj* A, int vs)
{
	Edge e = G->E[A->edge_index];
	if (e.end1 == vs)
		return e.end2;
	else
		return e.end1;
}

void init_Vertex(Graph* G, int n)
{
	G->V_n = n;
	G->V = (Vertex*)malloc(sizeof(Vertex) * n);

	for (int i = 0; i < n; ++i)
	{
		G->V[i].name = i + 1;
		G->V[i].head = get_list(-1, NULL);
		G->V[i].v_label = 0;
	}
}

void init_Graph(Graph* G, int n, int m)
{
	init_Vertex(G, n);
	init_Edge(G, m);
}

void init_Edge(Graph* G, int m)
{
	G->E = (Edge*)malloc(sizeof(Edge) * m);
	G->E_n = m;

	for (int i = 0; i < m; ++i)
	{
		G->E[i].edge_index = i;
		G->E[i].end1 = -1;
		G->E[i].end2 = -1;
		G->E[i].e_label = 0;
	}

}

void insert_Edge(Graph* G, int index, int v1, int v2)
{
	set_Edge(G, index, v1, v2);
	insert_Adj(G, index, v1, v2);
	if (v1 != v2)
		insert_Adj(G, index, v2, v1);
}

void set_Edge(Graph* G, int index, int v1, int v2)
{
	G->E[index].edge_index = index;
	G->E[index].end1 = v1;
	G->E[index].end2 = v2;
	G->E[index].e_label = 0;
}

void insert_Adj(Graph* G, int index, int v1, int v2)
{
	Adj* p = G->V[v1 - 1].head, *tmp = NULL;
	
	while (p->linked != NULL && opposite(G, p->linked, v1) < v2)
		p = p->linked;
	//printf("v1 : %d v2 : %d  index : %d\n", v1, v2, index);
	tmp = get_list(index, p->linked);
	p->linked = tmp;
}

void free_Graph(Graph* G)
{
	for (int i = 0; i < G->V_n; ++i)
		free_Adj(G->V[i].head);
	free(G->V);
	free(G->E);
	free(G);
}

void free_Adj(Adj* p)
{
	Adj* tmp;
	while (p!=NULL)
	{
		tmp = p->linked;
		free(p);
		p = tmp;
	}
}
/*
void print_vertex(Graph* G, int v)
{
	Adj* p = G->V->head->linked;
	printf("%d ", G->V[v - 1].name);
	int w;
	while (p != NULL)
	{
		w = opposite(G, p, v);
		printf("- %d", w);
		p = p->linked;
	}
	printf("\n");
}
*/

void DFS(Graph* G, int s)
{
	//printf("DFS 진입 : v - %d\n", G->V[s-1].name);
	printf("%d\n", G->V[s-1].name);
	Vertex* v = G->V;
	v[s - 1].v_label = 1;
	Adj* p = v[s - 1].head->linked;
	int w;
	while(p!=NULL)
	{
		w = opposite(G, p, v[s - 1].name);
		if (v[w - 1].v_label == 0)
			DFS(G, w);
		p = p->linked;
	}
	/*
	//Fresh : 0, Visited = 1;
	Vertex* v = G->V;
	if (v[s - 1].v_label == 0)
		rDFS(G, s - 1);
	*/
}
/*
void rDFS(Graph* G, int index)
{
	//Tree : 2, Back = 3;
	G->V[index].v_label = 1;
	printf("index(%d) : %d\n", index, G->V[index].name);
	int v = G->V[index].name, w;
	Adj* p = G->V[index].head->linked;
	Edge* e = NULL;
	while (p)
	{
		if (G->E[p->edge_index].e_label == 0)
		{
			w = opposite(G, p, v);
			if (G->V[w - 1].v_label == 0)
			{
				G->E[p->edge_index].e_label = 2;
				rDFS(G, w);
			}
			else
				G->E[p->edge_index].e_label = 3;
		}
		p = p->linked;
	}
}

void rDFS(Graph* G, Vertex* V, int index)
{
	Edge* e = G->E;
	V[index].label = 1;
	Adj* p = V[index].head->linked;
	int e_i;
	while (p != NULL)
	{
		e_i = p->edge_index;
		if(e[e_i].label = 0)
			int w = 
	}
}*/

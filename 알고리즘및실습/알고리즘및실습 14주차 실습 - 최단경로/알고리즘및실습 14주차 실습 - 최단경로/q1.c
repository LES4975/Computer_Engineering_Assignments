#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct node {
	int edgeId;
	struct node* next;
} Node;
typedef struct vertex {
	int vname;
	int d;
	Node* incid_list;
} Vertex;
typedef struct edge {
	int ename;
	int vtx1, vtx2;
	int weight;
} Edge;
typedef struct graph {
	Vertex* vertices;
	int vsize;
	Edge* edges;
	int esize; 
} Graph;

Node* get_node(int, Node*);
int opposite(Graph*, Node*, int);
void set_edges_arr(Graph*, int, int, int, int);
void insert_incid_node(Graph*, int, int, int);
void add_edge(Graph*, int, int, int, int);
void set_vertices(Graph*, int);
void set_edges(Graph*, int);
void build_graph(Graph*, int, int);
void print_adj_vertices(Graph*, int);
void print_graph(Graph*);
void free_incid_list(Node*);
void free_graph(Graph*);

int* Q;

int main()
{
	Graph G;
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	build_graph(&G, n, m);
	print_graph(&G);

	free_graph(&G);
	return 0;
}

Node* get_node(int eid, Node* next)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->edgeId = eid;
	node->next = next;
	return node;
}

int opposite(Graph* G, Node* node, int vs)
{
	Edge e = G->edges[node->edgeId];
	return (e.vtx1 == vs) ? e.vtx2 : e.vtx1;
}

void set_edges_arr(Graph* G, int eid, int v1, int v2, int w)
{
	G->edges[eid].ename = eid;
	G->edges[eid].vtx1 = v1;
	G->edges[eid].vtx2 = v2;
	G->edges[eid].weight = w;
}

void insert_incid_node(Graph* G, int eid, int vs, int vd)
{
	//이 함수가 문제
	Node* node = G->vertices[vs].incid_list;
	Node* new_node;
	while (node->next && opposite(G, node->next, vs) < vd)
		node = node->next;
	new_node = get_node(eid, node->next);
	node->next = new_node; 
}

void add_edge(Graph* G, int eid, int v1, int v2, int w)
{
	set_edges_arr(G, eid, v1, v2, w);
	insert_incid_node(G, eid, v1, v2);
	if (v1 != v2)
		insert_incid_node(G, eid, v2, v1);
}

void set_vertices(Graph* G, int vsize)
{
	G->vertices = (Vertex*)malloc(sizeof(Vertex) * vsize);
	G->vsize = vsize;
	for (int i = 0; i < vsize; ++i)
	{
		G->vertices[i].vname = i; // 정점이름 설정
		G->vertices[i].incid_list = get_node(-1, NULL);
	}
}
void set_edges(Graph* G, int esize)
{
	G->edges = (Edge*)malloc(sizeof(Edge) * esize);
	G->esize = esize;
	for (int i = 0; i < esize; ++i)
	{ // 간선 배열 초기화
		G->edges[i].ename = -1; // 미사용 원소는 -1로 초기화
		G->edges[i].vtx1 = -1;
		G->edges[i].vtx2 = -1;
	}
	int v1, v2, w;
	for (int i = 0; i < esize; i++)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		add_edge(G, i, v1, v2, w);
	}
}

void build_graph(Graph* G, int n, int m)
{
	int vsize, esize;
	vsize = n;
	esize = m;
	set_vertices(G, vsize);
	set_edges(G, esize);
}

void print_adj_vertices(Graph* G, int vid)
{
	Node* node = G->vertices[vid].incid_list->next;
	printf("%d:", vid);
	while (node)
	{
		printf("[%d,", opposite(G, node, vid));
		printf(" %d] ", G->edges[node->edgeId].weight);
		node = node->next;
	}
	printf("\n");
}

void print_graph(Graph* G)
{
	int i;
	for (i = 0; i < G->vsize; ++i)
		print_adj_vertices(G, i);
}

void free_incid_list(Node* node)
{
	Node* p;
	while (node) {
		p = node->next;
		free(node);
		node = p;
	}
}

void free_graph(Graph* G)
{
	int i;
	for (i = 0; i < G->vsize; ++i)
		free_incid_list(G->vertices[i].incid_list);
	free(G->vertices);
	free(G->edges);
}

void DijkstraShortestPaths(Graph* G, int s)
{
	int i;
	for (i = 0; i < G->vsize; ++i)
		G->vertices[i].d = 90000;
	G->vertices[s].d = 0;
	Q = (int*)malloc(sizeof(int) * G->vsize);

}
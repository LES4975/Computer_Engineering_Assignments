#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct incidence_list
{
	int edge_index;
	struct incidence_list* linked;
}Incd;

typedef struct edges{
	int edge_name;//�߰� ����
	int weight;
	int end1;
	int end2;
}Edge;

typedef struct vertex
{
	int name;
	Incd* adj;
}Vertex;

typedef struct adj_graph {
	Vertex* V;
	Edge* E;
	int N;
}Graph;


void printGraph(Graph*, int);
Graph* init_Graph();
void modifyGraph(Graph*, int, int, int);
void insertEdge(Graph*, int, int , int , int );
void insert_incidence_list(Graph*, int, int, int);
Incd* get_list(int, Incd*);
void removeEdge(Graph*, int, int);
int opposite(Graph*, Incd*, int);
void free_Graph(Graph*);
void free_Incd(Incd*);


int main()
{
	int flag = 1, node_num, v_a, v_b, w;
	char command;
	Graph* G = init_Graph();
	while (flag)
	{
		scanf("%c", &command);
		getchar();
		switch (command)
		{
		case 'a':
			//��� �ѹ��� ������ ���� ������ ���,
			//�� �������� ���� ����ġ�� ��� �μ�, ��������,
			//���� : ����ȣ ����ġ ����ȣ ����ġ
			//�ƹ��͵� ������ -1 ���
			scanf("%d", &node_num);
			getchar();
			printGraph(G, node_num);
			break;
		case 'm':
			scanf("%d %d %d", &v_a, &v_b, &w);
			getchar();
			modifyGraph(G, v_a, v_b, w);
			break;
		case 'q'://���α׷� ����
			flag = 0;
			break;
		default:
			printf("error!\n");
			flag = 0;
			break;
		}
	}
	return 0;
}
//Vertex���� ��� �ѹ��� ��������Ʈ �����Ͱ� ����.
void printGraph(Graph* G, int n)
{
	printf("n��? : %d\n", n);
	Incd* p = p = G->V[n].adj->linked;
	while (p != NULL)
	{
		printf(" %d", opposite(G, p, n));
		printf(" %d", G->E[p->edge_index].weight);
		p = p->linked;
	}
	printf("\n");
}

Graph* init_Graph()
{
	int V_n = 7, E_n = 21, i;
	Graph* G = (Graph*)malloc(sizeof(Graph));
	//���� ����
	G->V = (Vertex*)malloc(sizeof(Vertex) * V_n);
	for (i = 0; i < V_n; i++)
	{
		G->V[i].name = i;
		G->V[i].adj = (Incd*)malloc(sizeof(Incd));
		G->V[i].adj->edge_index = -1;
		G->V[i].adj->linked = NULL;
	}
	//���� ����
	G->E = (Edge*)malloc(sizeof(Edge) * E_n);
	for (i = 0; i < E_n; i++)
	{
		G->E[i].edge_name = -1;//�̻�� ���Ҵ� -1�� �ʱ�ȭ
		G->E[i].end1 = -1;
		G->E[i].end2 = -1;
	}
	insertEdge(G, 0, 1, 2, 1);
	insertEdge(G, 1, 1, 3, 1);
	insertEdge(G, 2, 1, 4, 1);
	insertEdge(G, 3, 1, 6, 2);
	insertEdge(G, 4, 2, 3, 1);
	insertEdge(G, 5, 3, 5, 4);
	insertEdge(G, 6, 5, 5, 4);
	insertEdge(G, 7, 5, 6, 3);
	return G;
}

void modifyGraph(Graph* G, int a, int b, int w)
{
	if (w == 0)
		removeEdge(G, a, b);
	if ((a < 1 || a > 6) || (b < 1 || b > 6))
		printf("-1\n");
	Vertex v = G->V[a];
	Edge* e = G->E;
	Incd* p = v.adj->linked;
	while (p != NULL)
	{
		if (opposite(G, p, v.name) == b)
		{
			e[p->edge_index].weight = w;
			break;
		}
		p = p->linked;
	}
	if (p == NULL)
	{
		for(int i=0;i<G->N;i++)
			if (e[i].end1 == -1 && e[i].end2 == -1 && e[i].weight == -1)
			{
				insertEdge(G, i, a, b, w);
				break;
			}
	}
}

void insertEdge(Graph* G, int index, int v1, int v2, int w)
{
	Edge* e = G->E;
	*e = e[index];
	e->edge_name = index;
	e->end1 = v1;
	e->end2 = v2;
	e->weight = w;
	G->N++;
}

void insert_incidence_list(Graph* G, int index, int v1, int v2)
{
	Incd* p = G->V[v1].adj, *q;
	while (p->linked != NULL && opposite(G, p->linked, v1))
	{
		p = p->linked;
		q = get_list(index, p->linked);
		p->linked = q;
	}
}

Incd* get_list(int index, Incd* link)
{
	Incd* p = (Incd*)malloc(sizeof(Incd));
	p->edge_index = index;
	p->linked = link;
	return p;
}

void removeEdge(Graph* G, int v1, int v2)
{
	Incd* p = G->V[v1].adj;
	Incd* p2 = G->V[v2].adj;
	Incd* tmp;
	int index;
	while (p->linked)
	{
		if (v2 == opposite(G, p->linked, v1))
		{
			index = p->linked->edge_index;
			tmp = p->linked;
			p->linked = p->linked->linked;
			free(tmp);
			break;
		}
		p = p->linked;
	}
	while (p2->linked)
	{
		if (v1 == opposite(G, p2->linked, v2))
		{
			tmp = p2->linked;
			p2->linked = p2->linked->linked;
			free(tmp);
			break;
		}
	}

	Edge* e = G->E;
	e[index].end1 = -1;
	e[index].end2 = -1;
	e[index].weight = -1;
	G->N -= 1;
}

int opposite(Graph* G, Incd* p, int vs)
{
	Edge e = G->E[p->edge_index];
	if (e.end1 == vs)
		return e.end2;//�ݴ� ���� ���
	else
		return e.end1;
}

void free_Graph(Graph* G)
{
	int i;
	for (i = 0; i < 7; i++)
	{
		free_Incd(G->V[i].adj);
		free(G->V);
		free(G->E);
	}
}

void free_Incd(Incd* p)
{
	Incd* tmp;
	while (p)
	{
		tmp = p->linked;
		free(p);
		p = tmp;
	}
}

/*
#include <stdio.h>
#include <stdlib.h>
// ////////////////////////////////////////////
// �׷����� ��������Ʈ ������ �ʿ��� �ڷ���
// ////////////////////////////////////////////
typedef struct node {
int edgeId;
struct node *next;
} Node; // ��������Ʈ�� ���
typedef struct vertex {
int vname;
Node *incid_list;
} Vertex; // ���� �迭�� ����
typedef struct edge {
int ename;
int vtx1, vtx2; // ������ �� ����
int weight;
} Edge; // ���� �迭�� ����
typedef struct graph {
Vertex *vertices; // ���� �迭(���� �Ҵ�)
int vsize; // ���� �迭�� ũ��
Edge *edges; // ���� �迭(���� �Ҵ�)
int esize; // �꼱 �迭�� ũ��
} Graph; // �׷����� ���� ���

// ////////////////////////////////////////////
// �⺻ ��� �Լ�
// ////////////////////////////////////////////
// ���� ����Ʈ�� node�� �Ҵ��ϰ� �־��� ���ڷ� �ʱ�ȭ
Node *get_node(int eid, Node *next) {
Node *node = (Node *)malloc(sizeof(Node));
node->edgeId = eid;
node->next = next;
return node;
}
// ���� ����Ʈ�� ���(��������� vs)�� ��Ÿ���� ������ �ݴ��� ���� ã��
int opposite(Graph *G, Node *node, int vs) {
Edge e = G->edges[node->edgeId];
return (e.vtx1 == vs) ? e.vtx2 : e.vtx1;
}
// ////////////////////////////////////////////
// ���� �߰��� ���õ� �Լ���
// ////////////////////////////////////////////
// �����迭�� eid ���ҷ� ���� (v1,v2) ����
void set_edges_arr(Graph *G, int eid, int v1, int v2, int w) {
G->edges[eid].ename = eid;
G->edges[eid].vtx1 = v1;
G->edges[eid].vtx2 = v2;
G->edges[eid].weight = w;
}
// ��� vs�� ��������Ʈ�� ���� (vs, vd)�� ���� ��� �߰�
void insert_incid_node(Graph *G, int eid, int vs, int vd) {
Node *node = G->vertices[vs].incid_list;
Node *new_node;
// �ݴ��� ���� ��ȣ�� ������������ ���� ����Ʈ �����ϱ� ����
// ������ ��ġ�� �� ��� ã�� (��� ��� �ִ� ���� ����Ʈ�� �ڵ尡 �ܼ���)
while (node->next && opposite(G, node->next, vs) < vd) // node->next�� ����ӿ� �ָ�
node = node->next; // while�� ������ node�� ������ ��ġ�� �� ���
new_node = get_node(eid, node->next); // ������ ����� ���� ����
node->next = new_node; // node --> new_node �� ��ũ ����
}
// �׷����� ���� (v1, v2) �߰�
void add_edge(Graph *G, int eid, int v1, int v2, int w) {
set_edges_arr(G, eid, v1, v2, w); // ���� �迭�� eid ���ҿ� ���� ���� ����
insert_incid_node(G, eid, v1, v2); // ���� v1�� ��������Ʈ�� ��� �߰�
if (v1 != v2) // loop �� �ƴϸ�
insert_incid_node(G, eid, v2, v1); // �ݴ��� ����(v2)�� ��������Ʈ�� ��� �߰�
}

// ////////////////////////////////////////////
// �׷��� ������ ���� ���� ���� �Լ�
// ////////////////////////////////////////////
// �׷��� ���� ���� ����
void set_vertices(Graph *G, int vsize) {
G->vertices = (Vertex *)malloc(sizeof(Vertex)*vsize); // ���� �迭 �Ҵ�
G->vsize = vsize;
for (int i = 0; i < vsize; ++i) {
G->vertices[i].vname = i; // �����̸� ����
G->vertices[i].incid_list = get_node(-1, NULL); // ��� ��� �ޱ�
}
}
// �׷��� ���� ���� ����
void set_edges(Graph *G, int esize) {
G->edges = (Edge *)malloc(sizeof(Edge)*esize); // ���� �迭 �Ҵ�
G->esize = esize;
for (int i = 0; i < esize; ++i) { // ���� �迭 �ʱ�ȭ
G->edges[i].ename = -1; // �̻�� ���Ҵ� -1�� �ʱ�ȭ
G->edges[i].vtx1 = -1;
G->edges[i].vtx2 = -1;
}
add_edge(G, 0, 1, 2, 1); // �ǽ� 10���� ������ �׷��� ����
add_edge(G, 1, 6, 1, 2); // ���α׷��� �� �����ϴ� �� Ȯ���ϱ� ����
add_edge(G, 2, 1, 4, 1); // ���� �߰� ������ �Ϻη� ������
add_edge(G, 3, 2, 3, 1);
add_edge(G, 4, 3, 5, 4);
add_edge(G, 5, 1, 3, 1);
add_edge(G, 6, 5, 5, 4);
add_edge(G, 7, 5, 6, 3);
}
//�׷��� ����
void build_graph(Graph *G) {
int vsize, esize;
vsize = 7; // �ǽ� 10���� ������ �׷��� ���� (���� 0�� ��� ����)
esize = 21; // �ǽ� 10���� ������ �׷��� ���� (�ִ� 21���� ���� ����)
set_vertices(G, vsize);// ���� ���� ����
set_edges(G, esize); // ���� ���� ����
}

// ////////////////////////////////////////////
// �׷����� ���� ��°� �޸� ���� ���� �Լ�
// ////////////////////////////////////////////
// Ư�� ������ ����(���� ���� ��ȣ�� ������ ����ġ) ���
void print_adj_vertices(Graph *G, int vid) {
Node *node = G->vertices[vid].incid_list->next; // ����� ���� ���
printf("%d:", vid);
while (node) {
printf("[%d,", opposite(G, node, vid)); // �ݴ��� ���� ��ȣ ���
printf(" %d] ", G->edges[node->edgeId].weight); // ����ġ ���
node = node->next;
}
printf("\n");
}
// �׷����� ���� ���
void print_graph(Graph *G) {
int i;
for (i = 0; i < G->vsize; ++i)
print_adj_vertices(G, i);
}
// ��������Ʈ�� ���� ����
void free_incid_list(Node *node) {
Node *p;
while (node) {
p = node->next; // ���� ��� �ּ� �ӽ� ����
free(node); // node ����
node = p; // ���� ��� �ּҸ� node ������
}
}
// �׷����� �Ҵ�� �޸� ����
void free_graph(Graph *G)
{
int i;
for (i = 0; i < G->vsize; ++i) // ��������Ʈ ����
free_incid_list(G->vertices[i].incid_list);
free(G->vertices); // ���� �迭 ����
free(G->edges); // ���� �迭 ����
}

// ////////////////////////////////////////////
// main() �Լ�
// ////////////////////////////////////////////
int main()
{
Graph G; // �׷��� ���� ���� (�����Ҵ�)
build_graph(&G); // �׷��� ����
print_graph(&G); // �׷��� ���� ���
free_graph(&G); // �׷����� �޸� ����
return 0;
}
*/
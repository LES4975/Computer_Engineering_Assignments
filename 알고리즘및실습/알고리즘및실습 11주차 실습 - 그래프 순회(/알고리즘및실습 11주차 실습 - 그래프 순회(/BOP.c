#include <stdio.h>
#include <stdlib.h>
// ////////////////////////////////////////////
// �׷����� ��������Ʈ ������ �ʿ��� �ڷ���
// ////////////////////////////////////////////
typedef struct node {
	int edgeId;
	struct node* next;
} Node; // ��������Ʈ�� ���
typedef struct vertex {
	int vname;
	Node* incid_list;
} Vertex; // ���� �迭�� ����
typedef struct edge {
	int ename;
	int vtx1, vtx2; // ������ �� ����
	int weight;
} Edge; // ���� �迭�� ����
typedef struct graph {
	Vertex* vertices; // ���� �迭(���� �Ҵ�)
	int vsize; // ���� �迭�� ũ��
	Edge* edges; // ���� �迭(���� �Ҵ�)
	int esize; // �꼱 �迭�� ũ��
} Graph; // �׷����� ���� ���

// ////////////////////////////////////////////
// �⺻ ��� �Լ�
// ////////////////////////////////////////////
// ���� ����Ʈ�� node�� �Ҵ��ϰ� �־��� ���ڷ� �ʱ�ȭ
Node* get_node(int eid, Node* next) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->edgeId = eid;
	node->next = next;
	return node;
}
// ���� ����Ʈ�� ���(��������� vs)�� ��Ÿ���� ������ �ݴ��� ���� ã��
int opposite(Graph* G, Node* node, int vs) {
	Edge e = G->edges[node->edgeId];
	return (e.vtx1 == vs) ? e.vtx2 : e.vtx1;
}
// ////////////////////////////////////////////
// ���� �߰��� ���õ� �Լ���
// ////////////////////////////////////////////
// �����迭�� eid ���ҷ� ���� (v1,v2) ����
void set_edges_arr(Graph* G, int eid, int v1, int v2, int w) {
	G->edges[eid].ename = eid;
	G->edges[eid].vtx1 = v1;
	G->edges[eid].vtx2 = v2;
	G->edges[eid].weight = w;
}
// ��� vs�� ��������Ʈ�� ���� (vs, vd)�� ���� ��� �߰�
void insert_incid_node(Graph* G, int eid, int vs, int vd) {
	Node* node = G->vertices[vs].incid_list;
	Node* new_node;
	// �ݴ��� ���� ��ȣ�� ������������ ���� ����Ʈ �����ϱ� ����
	// ������ ��ġ�� �� ��� ã�� (��� ��� �ִ� ���� ����Ʈ�� �ڵ尡 �ܼ���)
	while (node->next && opposite(G, node->next, vs) < vd) // node->next�� ����ӿ� �ָ�
		node = node->next; // while�� ������ node�� ������ ��ġ�� �� ���
	new_node = get_node(eid, node->next); // ������ ����� ���� ����
	node->next = new_node; // node --> new_node �� ��ũ ����
}
// �׷����� ���� (v1, v2) �߰�
void add_edge(Graph* G, int eid, int v1, int v2, int w) {
	set_edges_arr(G, eid, v1, v2, w); // ���� �迭�� eid ���ҿ� ���� ���� ����
	insert_incid_node(G, eid, v1, v2); // ���� v1�� ��������Ʈ�� ��� �߰�
	if (v1 != v2) // loop �� �ƴϸ�
		insert_incid_node(G, eid, v2, v1); // �ݴ��� ����(v2)�� ��������Ʈ�� ��� �߰�
}

// ////////////////////////////////////////////
// �׷��� ������ ���� ���� ���� �Լ�
// ////////////////////////////////////////////
// �׷��� ���� ���� ����
void set_vertices(Graph* G, int vsize) {
	G->vertices = (Vertex*)malloc(sizeof(Vertex) * vsize); // ���� �迭 �Ҵ�
	G->vsize = vsize;
	for (int i = 0; i < vsize; ++i) {
		G->vertices[i].vname = i; // �����̸� ����
		G->vertices[i].incid_list = get_node(-1, NULL); // ��� ��� �ޱ�
	}
}
// �׷��� ���� ���� ����
void set_edges(Graph* G, int esize) {
	G->edges = (Edge*)malloc(sizeof(Edge) * esize); // ���� �迭 �Ҵ�
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
void build_graph(Graph* G) {
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
void print_adj_vertices(Graph* G, int vid) {
	Node* node = G->vertices[vid].incid_list->next; // ����� ���� ���
	printf("%d:", vid);
	while (node) {
		printf("[%d,", opposite(G, node, vid)); // �ݴ��� ���� ��ȣ ���
		printf(" %d] ", G->edges[node->edgeId].weight); // ����ġ ���
		node = node->next;
	}
	printf("\n");
}
// �׷����� ���� ���
void print_graph(Graph* G) {
	int i;
	for (i = 0; i < G->vsize; ++i)
		print_adj_vertices(G, i);
}
// ��������Ʈ�� ���� ����
void free_incid_list(Node* node) {
	Node* p;
	while (node) {
		p = node->next; // ���� ��� �ּ� �ӽ� ����
		free(node); // node ����
		node = p; // ���� ��� �ּҸ� node ������
	}
}
// �׷����� �Ҵ�� �޸� ����
void free_graph(Graph* G)
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
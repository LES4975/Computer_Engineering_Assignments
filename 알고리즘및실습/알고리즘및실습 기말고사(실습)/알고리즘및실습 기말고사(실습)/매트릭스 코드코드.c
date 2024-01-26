#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct vertex
{
	int name;
}Vertex;

typedef struct edges {
	int weight;
	int end1;
	int end2;
}Edge;

typedef struct adj_graph {
	Vertex V[6];
	Edge E[21];
	int** adj_m;
	int N;//최대 간선 수
}Graph;

Graph* init_Graph();
int** init_adjancency();
void print_Graph(Graph*, int);
void modify_Graph(Graph*, int, int, int);
void insert_Edge(Graph*, int, int, int);
void remove_Edge(Graph*, int, int);
void free_Graph(Graph*);

int main()
{
	int flag = 1, node_num, v_a, v_b, w;
	char command;
	Graph* G = init_Graph();
	Edge* e = G->E;
	while (flag)
	{
		scanf("%c", &command);
		getchar();
		switch (command)
		{
		case 'a':
			//노드 넘버를 가지는 노드와 인접한 노드,
			//그 노드까지의 간선 가중치를 모두 인쇄, 오름차순,
			//순서 : 노드번호 가중치 노드번호 가중치
			//아무것도 없으면 -1 출력
			scanf("%d", &node_num);
			getchar();
			print_Graph(G, node_num);
			break;
		case 'm':
			scanf("%d %d %d", &v_a, &v_b, &w);
			getchar();
			modify_Graph(G, v_a, v_b, w);
			break;
		case 'q'://프로그램 종료
			flag = 0;
			break;
		default:
			printf("error!\n");
			flag = 0;
			break;
		}
	}
	free_Graph(G);
	return 0;
}

Graph* init_Graph()
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->N = 21;
	Vertex* v = G->V;
	Edge* e = G->E;
	int i;
	for (i = 0; i < 6; i++)
		v[i].name = i + 1;
	G->adj_m = init_adjancency();
	for (i = 0; i < G->N; i++)
	{
		e[i].end1 = -1;
		e[i].end2 = -1;
		e[i].weight = -1;
	}
	insert_Edge(G, 1, 2, 1);
	insert_Edge(G, 1, 3, 1);
	insert_Edge(G, 1, 4, 1);
	insert_Edge(G, 1, 6, 2);
	insert_Edge(G, 2, 3, 1);
	insert_Edge(G, 3, 5, 4);
	insert_Edge(G, 5, 5, 4);
	insert_Edge(G, 5, 6, 3);
	return G;
}

int** init_adjancency()
{
	int i, j;
	int** arr = (int**)malloc(sizeof(int*) * 6);
	for (i = 0; i < 6; i++)
		arr[i] = (int*)malloc(sizeof(int) * 6);
	for (i = 0; i < 6; i++)
		for (j = 0; j < 6; j++)
			arr[i][j] = -1;
	return arr;
}

void print_Graph(Graph* G, int n)
{
	if (n < 1 || n>6)
	{
		printf("-1\n");
		return;
	}
	for (int i = 0; i < 6; i++)
		if (G->adj_m[n - 1][i] != -1)
			printf(" %d %d", i + 1, G->adj_m[n - 1][i]);
	printf("\n");
}

void modify_Graph(Graph* G, int a, int b, int w)
{
	if (w == 0)
	{
		remove_Edge(G, a, b);
		return;
	}
	if ((a < 1 || a > 6) || (b < 1 || b > 6))
		printf("-1\n");
	if (G->adj_m[a - 1][b - 1] == -1)
		insert_Edge(G, a, b, w);
	else
		if (G->adj_m[a - 1][b - 1] != w)
		{
			Edge* e = G->E;
			int index = G->adj_m[a - 1][b - 1];
			e[index].weight = w;
			G->adj_m[a - 1][b - 1] = w;
			G->adj_m[b - 1][a - 1] = w;
		}
}

void remove_Edge(Graph* G, int a, int b)
{
	int node1 = a, node2 = b;
	if (a > b)
	{
		node1 = b;
		node2 = a;
	}
	int index = 0;
	Edge* e = G->E;
	for (int i = 0; i < G->N; i++)
		if (e[i].end1 == node1 && e[i].end2 == node2)
		{
			index = i;
			break;
		}
	e[index].end1 = -1;
	e[index].end2 = -1;
	e[index].weight = -1;
	G->adj_m[a - 1][b - 1] = -1;
	G->adj_m[b - 1][a - 1] = -1;
}

void insert_Edge(Graph* G, int a, int b, int w)
{
	int** p = G->adj_m;
	p[a - 1][b - 1] = w;
	p[b - 1][a - 1] = w;
	Edge* e = G->E;
	int e1 = a, e2 = b;
	if (a > b)
	{
		e1 = b;
		e2 = a;
	}
	for (int i = 0; i < G->N; i++)
	{
		if (e[i].end1 == -1 && e[i].end2 == -1 && e[i].weight == -1)
		{
			e[i].end1 = e1;
			e[i].end2 = e2;
			e[i].weight = w;
			break;
		}
	}
}

void free_Graph(Graph* G)
{
	int** p = G->adj_m;
	for (int i = 0; i < 6; i++)
		free(p[i]);
	free(p);
	free(G);
}

/*

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Incd {
	struct Incd* linked;
	int w_num;
}Incd;

typedef struct vertex {
	int element;
	struct Incd* i_head;
}Vertex;

typedef struct edge {
	int weight;
	int end1;
	int end2;
}Edge;

struct Graph {
	Vertex vt[6];
	Edge Ed[21];
	int edge_cnt;
};

struct Graph* init_Graph();
void modify_Graph(struct Graph*, int, int, int);


int main()
{
	int flag = 1, node_num, v_a, v_b, w;
	char command;
	struct Graph* G = init_Graph();
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
			modify_Graph(G, v_a - 1, v_b - 1, w);
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
	return 0;
}

struct Graph* init_Graph()//그래프 초기화하기
{
	int i, cnt = 0;
	struct Graph* G = (struct Graph*)malloc(sizeof(struct Graph));
	for (i = 0; i < 6; i++)
	{
		G->vt->element = i + 1;
		G->vt->i_head = (Incd*)malloc(sizeof(Incd));
		G->vt->i_head->linked = NULL;
	}
	Vertex* p = G->vt;
	create_edge(G, 0, 1, 1);
	create_edge(G, 0, 2, 1);
	create_edge(G, 0, 3, 1);
	create_edge(G, 0, 5, 2);
	create_edge(G, 1, 2, 1);
	create_edge(G, 2, 4, 4);
	create_edge(G, 4, 4, 4);
	create_edge(G, 4, 5, 3);
	return G;
}

void print_Graph(struct Graph* G, int node)
{
	if (node < 1 || node > 5)
		printf("-1\n");
	else
	{

	}
}


void modify_Graph(struct Graph* G, int a, int b, int w)
{
	if (a> G->edge_cnt || b> G->edge_cnt)
	{
		printf("-1\n");
		return;
	}

	if (w == 0)
	{
		remove_edge(G, a, b);
	}
	else
	{
		Vertex* VA = G->vt + a;
		Vertex* VB = G->vt + b;
		Edge* p = G->Ed;
		int i;
		for (i = 0; i <= G->edge_cnt; i++)
		{
			if ((p + i)->end1 == VA->element - 1 && (p + i)->end2 == VB->element)
			{
				(p + i)->weight = w;
				break;
			}
		}
		if (i > G->edge_cnt)
			create_edge(G, a, b, w);
	}
}
//간선 (a, b)의 가중치를 w로 변경
//없으면 새로 생성
//w=0이면 간선 (a, b)를 삭제

void create_edge(struct Graph* G, int a, int b, int w)
{
	G->edge_cnt = G->edge_cnt + 1;
	Vertex* VA = G->vt + a;
	Vertex* VB = G->vt + b;
	Incd* V_a = VA->i_head;
	Incd* V_b = VB->i_head;
	int i = G->edge_cnt;
	Edge* p = G->Ed + i;
	p->weight = w;
	p->end1 = a;
	p->end2 = b;
	insert_edge(G, VA, V_a, a, i);
	insert_edge(G, VB, V_b, b, i);
}

void insert_edge(struct Graph* G, Vertex* V, Incd* V_i, int n, int i)
{
	int j, k, node;
	if (V_i->linked == NULL)
	{
		V_i->linked = (Incd*)malloc(sizeof(Incd));
		V_i->linked->w_num = i;

	}
	else
	{
		Edge* e = NULL;
		while (V_i->linked != NULL)
		{
			j = V_i->w_num;
			k = V_i->linked->w_num;
			
		}
	}

}

void remove_edge(struct Graph* G, int a, int b)
{
	Incd* tmp = NULL;
	Vertex* VA = G->vt + a;
	Vertex* VB = G->vt + b;
	int index;
	Edge* p = G->Ed;
	for (int i = 0; i <= G->edge_cnt; i++)
	{
		if (p->end1 == a && p->end2 == b)
			index = i;
	}
	Incd* V_a = VA->i_head;
	Incd* V_b = VB->i_head;

	while (V_a->linked->w_num != index)
		V_a = V_a->linked;
	tmp = V_a->linked;
	V_a->linked = tmp->linked;
	free(tmp);

	while (V_b->linked->w_num != index)
		V_b = V_b->linked;
	tmp = V_b->linked;
	V_b->linked = tmp->linked;
	free(tmp);
}

*/
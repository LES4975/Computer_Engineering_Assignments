#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 

typedef struct node {
	int vertex;
	struct node* link;
} node;

typedef struct {
	node* adj_list[MAX_SIZE];
	int n;                                    // 정점 개수 
} graphType;

void init(graphType* g, int n) {
	g->n = n;
	for (int i = 0; i < n; i++)              // 인접 리스트 초기화 
		g->adj_list[i] = NULL;
}

void insert_graph(graphType* g, int u, int v) {       // 인접리스트 삽입. 
	if ((u > g->n) || (v > g->n)) {                 // u : 시작 정점, v : 도착 정점 
		printf("정점 오류\n");
		return;
	}
	node* N = (node*)malloc(sizeof(node));
	N->vertex = v;                 // 도착 정점 삽입 
	N->link = NULL;
	if (g->adj_list[u]) {                         // 여기 질문입니다 !! 
		node* w = g->adj_list[u];
		while (w->link)
			w = w->link;
		w->link = N;
	}
	else
		g->adj_list[u] = N;
}

void insert_edge(graphType* g, int start, int end) {       // 마찬가지로 시작 정점과 도착 정점  
	//graphNode* N = (graphNode*)malloc(sizeof(graphNode));
	node* N = (node*)malloc(sizeof(node));
	if ((start >= g->n) || (end >= g->n)) {
		fprintf(stderr, "정점 번호 오류\n");
		return;
	}
	N->vertex = end;
	//N->link = g->adj_mat[start];
	N->link = g->adj_list[start];
	//g->adj_mat[start] = N;
	g->adj_list[start] = N;
}

// 함수 추가
void printGraph(graphType* g, int N) {
	node* temp = (node*)malloc(sizeof(node));
	for (int i = 0; i < N; i++) {
		if (g->adj_list[i] == NULL)
			printf("[%d] --> NULL\n", i);
		else {
			printf("[%d] --> ", i);
			temp = g->adj_list[i];
			while (temp != NULL) {
				printf("%d --> ", temp->vertex);
				temp = temp->link;
			}
			printf("NULL\n");
		}
	}
}

int main()
{
	node* temp = (node*)malloc(sizeof(node));
	graphType* adjGraph = (graphType*)malloc(sizeof(graphType));
	int N = 5;

	// 질문 1  -> 잘 작동함을 확인하였습니다.
	init(adjGraph, N);
	insert_graph(adjGraph, 2, 1);
	printGraph(adjGraph, N);
	printf("---------------------------------\n");

	// 질문 2  -> 잘 작동함을 확인하였습니다.
	init(adjGraph, N);
	insert_graph(adjGraph, 0, 1);
	insert_graph(adjGraph, 0, 2);
	insert_graph(adjGraph, 3, 2);
	insert_graph(adjGraph, 2, 4);
	insert_graph(adjGraph, 0, 3);
	printGraph(adjGraph, N);

	return 0;
}
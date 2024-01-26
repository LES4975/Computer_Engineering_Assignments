
Adj* get_list(int index, Adj* link)//리스트 생성 함수
{
	Adj* p = (Adj*)malloc(sizeof(Adj));
	p->edge_index = index;
	p->linked = link;
	return p;
}

int opposite(Graph* G, Adj* A, int vs)//반대쪽 정점을 반환하는 함수
{
	Edge e = G->E[A->edge_index];
	return (e.end1 == vs) ? e.end2 : e.end1;
}

void init_Vertex(Graph* G, int n)//정점 정보를 초기화하는 함수
{
	G->V_n = n;
	G->V = (Vertex*)malloc(sizeof(Vertex) * n);//정점 배열 메모리 할당

	for (int i = 0; i < n; ++i)
	{
		G->V[i].name = i + 1;//초기에 설정할 정점 정보는 인덱스보다 1 큰 값으로 한다.
		G->V[i].head = get_list(-1, NULL);//헤더 인접 리스트를 생성하여 연결한다.
		G->V[i].v_label = -1;//라벨은 -1로 초기화한다.
	}
}

void init_Graph(Graph* G, int n, int m)//그래프를 초기화하는 함수
{
	init_Vertex(G, n);//정점 초기화
	init_Edge(G, m);//간선 초기화
}

void init_Edge(Graph* G, int m)//간선을 초기화하는 함수
{
	G->E = (Edge*)malloc(sizeof(Edge) * m);//간선 배열 메모리 할당
	G->E_n = m;

	for (int i = 0; i < m; ++i)
	{
		G->E[i].end1 = -1;
		G->E[i].end2 = -1;
		G->E[i].e_label = -1;//정점과 라벨은 -1로 초기화한다.
	}

}

void insert_Edge(Graph* G, int index, int v1, int v2)//간선 삽입 함수
{
	set_Edge(G, index, v1, v2);//입력받은 정점을 간선 배열에 저장
	insert_Adj(G, index, v1, v2);//간선에 따른 리스트를 정점에 연결한다.
	if (v1 != v2)//v1가 v2와 같지 않을 경우 : 싸이클이 아닐 경우
		insert_Adj(G, index, v2, v1);//반대쪽 정점에도 간선에 따른 리스트를 연결한다.
}

void set_Edge(Graph* G, int index, int v1, int v2)//간선 배열에 정점과 라벨 저장
{
	G->E[index].end1 = v1;
	G->E[index].end2 = v2;
	G->E[index].e_label = -1;
}

void insert_Adj(Graph* G, int index, int v1, int v2)//인접 리스트 생성
{
	Adj* p = G->V[v1 - 1].head, * tmp = NULL;

	while (p->linked != NULL && opposite(G, p->linked, v1) < v2)//오름차순으로 저장하기 위해 적당한 위치를 찾는다.
		p = p->linked;
	tmp = get_list(index, p->linked);//위치를 찾았으면 리스트를 생성하여 연결한다.
	p->linked = tmp;
}

void free_Graph(Graph* G)//그래프 메모리 해제
{
	for (int i = 0; i < G->V_n; ++i)
		free_Adj(G->V[i].head);//정점마다 연결된 리스트 해제
	free(G->V);//정점 배열 해제
	free(G->E);//간선 배열 해제
	free(G);//그래프 해제
}

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//그래프가 자유 트리이면 트리의 중심과 중심의 이심율 출력하기
//그래프가 자유 트리가 아닐 경우 연결 요소의 개수 출력

typedef struct Graph_Edge {
	int end1;//정점 1
	int end2;//정점 2
	int e_label;//간선 라벨
}Edge;//간선 구조체 정의

typedef struct adj_list {
	struct adj_list* linked;//다음 리스트 포인터
	int edge_index;//간선 배열의 인덱스
}Adj;//인접리스트 구조체 정의

typedef struct Graph_Vertex {
	int name;//정점의 이름
	int v_label;//정점의 라벨
	Adj* head;//정점의 헤드 인접리스트 포인터
}Vertex;//정점 구조체 정의

typedef struct graph {
	Vertex* V;//정점 포인터
	Edge* E;//간선 포인터
	int V_n;//정점의 개수
	int E_n;//간선의 개수
}Graph;//그래프 구조체 정의

//비재귀적 탐색을 위한 스택용 구조체
typedef struct stack {
	int* arr;//스택 배열
	int t;//스택의 top
	int N;//스택의 크기
}Stack;//스택 구조체 선언

//함수에 대한 설명은 아래에 기술
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
//void print_Graph(Graph*);
//void print_adj_vertices(Graph*, int);
void DFS(Graph*, int);
//void rDFS(Graph*, int);
//-------------------------------
void findCenter(Graph*);
int numVertices(Graph*);
void removeLeaves(Graph*, int, int);
void removeVertex(Graph*, int);
void remove_Opposite_incd(Graph*, Adj*, int);
void print_center(Graph*);

int main()
{
	Graph* G = (Graph*)malloc(sizeof(Graph));//그래프 G 생성
	int n, m, v1, v2, flag = 0;
	scanf("%d %d", &n, &m);//정점과 간선의 개수 입력
	init_Graph(G, n, m);//그래프 초기화
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &v1, &v2);//간선 삽입을 위해 연결할 정점 입력
		insert_Edge(G, i, v1, v2);//간선 생성
	}

	//G에 싸이클이 있는지 조사하기
	for (int i = 0; i < G->V_n; ++i)
	{
		//DFS(G, i);
		if (flag != 0)
		{
			break;
		}
	}
	if (flag == 0)//G가 트리인 경우
		findCenter(G);//중심을 찾는다.

	free_Graph(G);//G의 메모리 해제
	return 0;
}


void free_Adj(Adj* p)//리스트 메모리 해제
{
	Adj* tmp;
	while (p != NULL)
	{
		tmp = p->linked;
		free(p);
		p = tmp;
	}
}

/*
void print_Graph(Graph* G)
{
	for (int i = 0; i < G->V_n; ++i)
		print_adj_vertices(G, i);
}

void print_adj_vertices(Graph* G, int index)
{
	Adj* p = G->V[index].head->linked;
	printf("%d:", G->V[index].name);
	while (p)
	{
		printf("%d, ", opposite(G, p, G->V[index].name));
		p = p->linked;
	}
	printf("\n");
}
*/

//스택 메쏘드
void initStack(Stack* S, int vsize)//스택 초기화
{
	S->arr = (int*)malloc(sizeof(int) * vsize);
	S->t = -1;
	S->N = vsize;
}

void pushStack(Stack* S, int e)//스택에 원소 삽입
{
	if (S->t == S->N - 1)
		return;//fullStackException()
	S->t++;
	S->arr[S->t] = e;
}

int isEmptyStack(Stack* S)//스택이 비어있는지 확인하는 함수
{
	if (S->t == -1)
		return 1;
	else
		return 0;
}

int popStack(Stack* S)//스택에서 원소 삭제하기
{
	if (isEmptyStack(S))
		return 0;//emptyStackexception()
	S->t--;
	return S->arr[S->t + 1];
}
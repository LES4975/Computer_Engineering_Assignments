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
	if(flag == 0)//G가 트리인 경우
		findCenter(G);//중심을 찾는다.

	free_Graph(G);//G의 메모리 해제
	return 0;
}


//******************************************
void DFS(Graph* G, int s)
{
	//printf("%d\n", G->V[s - 1].name);
	Vertex* v = G->V;
	v[s - 1].v_label = 1;
	Adj* p = v[s - 1].head->linked;
	int w;
	while (p != NULL)
	{
		w = opposite(G, p, v[s - 1].name);
		if (v[w - 1].v_label == 0)
			DFS(G, w);
		p = p->linked;
	}
}
//--------------------------------------------------
void findCenter(Graph* G)//중심 찾기 알고리즘
{
	Graph T = *G;
	int count = 1;
	while (numVertices(G) > 2)//정점의 개수가 2보다 크면 아직 트리 내에 중심이 아닌 정점이 존재한다.
	{
		removeLeaves(&T, 1, 0);//부모 정점은 NULL로 둔다.
		count++;//잎을 지워나갈 때마다 이심율을 증가시킨다.
	}
	print_center(&T);//남은 정점(중심)을 출력한다.
	printf("%d\n", count);//중심의 이심율을 출력한다.
}

//정점의 개수를 세는 알고리즘
int numVertices(Graph* G)
{
	int cnt = 0;
	for (int i = 0; i < G->V_n; ++i)
		if (G->V[i].name != -1)//정점의 이름이 존재하는 원소를 찾는다.
			cnt++;//존재하면 cnt를 증가시킨다.
	return cnt;//정점의 개수를 반환한다.
}

//잎 삭제 알고리즘
void removeLeaves(Graph* G, int v, int p)
{
	int c = 0, w;
	Adj* k = G->V[v - 1].head->linked;
	while (k != NULL)//연결된 간선이 존재할 경우
	{
		c = c + 1;
		w = opposite(G, k, v);
		if (w != p)//반대 정점이 부모 노드가 아닐 경우
			removeLeaves(G, w, v);//
	}
	if (c == 1)//해당 정점에 부모가 없을 때
		removeVertex(G, v);//정점을 삭제한다.
}

void removeVertex(Graph* G, int v)
{
	Adj* p = G->V[v - 1].head->linked, * tmp;
	while (p != NULL)
	{
		remove_Opposite_incd(G, p, v);//반대쪽 정점의 해당 간선 리스트도 삭제
		tmp = p->linked;
		free(p);//간선 메모리 해제
		p = tmp;
	}
	free(G->V[v - 1].head);//헤드 노드 메모리 해제
	G->V[v - 1].name = -1;
	G->V[v - 1].v_label = -1;//간선을 초기화한다.
}

void remove_Opposite_incd(Graph* G, Adj* p, int v)//반대쪽 정점에 연결된 간선 정보 삭제
{
	int index = p->edge_index;
	int w = opposite(G, p, v);
	Adj* q = G->V[w - 1].head, * tmp;
	while (q->linked != NULL)
	{
		if (q->linked->edge_index == index)//반복을 통해 간선 인덱스가 저장된 리스트를 찾는다.
		{
			//인접리스트 삭제(삭제 및 보완하기)
			tmp = q->linked->linked;
			free(q->linked);
			q->linked = tmp;

			//간선 정보 삭제
			G->E[index].end1 = -1;
			G->E[index].end2 = -1;
			G->E[index].e_label = -1;

			break;
		}
		q = q->linked;
	}
}

void print_center(Graph* G)
{
	for (int i = 0; i < G->V_n; ++i)
		if (G->V[i].name != -1)//삭제되지 않은 정점을 찾는다.
			printf("%d ", G->V[i].name);//정점이 삭제되지 않았다면, 곧 중심이므로 중심 이름을 출력한다.
	printf("\n");
}

//*******************************************

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
	Adj* p = G->V[v1 - 1].head, *tmp = NULL;

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

void free_Adj(Adj* p)//리스트 메모리 해제
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

/*
void print_vertex(Graph* G, int v)
{
	Adj* p = G->V->head->linked;
	printf("%d ", G->V[v].name);
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

/*
void DFS(Graph* G, int s)
{
	//printf("DFS 진입 : v - %d\n", G->V[s-1].name);
	printf("%d\n", G->V[s - 1].name);
	Vertex* v = G->V;
	v[s - 1].v_label = 1;
	Adj* p = v[s - 1].head->linked;
	int w;
	while (p != NULL)
	{
		w = opposite(G, p, v[s - 1].name);
		if (v[w - 1].v_label == 0)
			DFS(G, w);
		p = p->linked;
	}
	//Fresh : 0, Visited = 1;
	Vertex* v = G->V;
	if (v[s - 1].v_label == 0)
		rDFS(G, s - 1);
}
*/

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

*/

/*
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
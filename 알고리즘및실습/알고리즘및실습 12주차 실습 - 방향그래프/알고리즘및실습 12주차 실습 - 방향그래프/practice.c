#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct incidence_list {
	struct incidence_list* next;
	int edge_index;
}Adj;

typedef struct vertex {
	char vname;
	Adj* inEdges;
	Adj* outEdges;
	int inDegree;
}Vertex;

typedef struct edge {
	int origin;
	int destination;
	int index;
}Edge;

typedef struct graph {
	Vertex V[100];
	Edge E[1000];
	int V_n;
	int E_n;
}Graph;

typedef struct queue {
	int* Qu;
	int front;
	int rear;
	int size;
}Queue;

void buildGraph(Graph);
Adj* get_list();
char readchar();
int readline();
void insertVertex(char, int);
void insertDirectedEdge(char, char, int);
int index(char);
void addFirst(Adj*, int);
void topologicalSort();
Queue* initQueue(Graph);
void enqueue(Queue*, char);
char dequeue(Queue*);
int isFull(Queue*);
int isEmpty(Queue*);
void freeGraph();
void free_incid_list(Adj*);

Graph G;
int n, m;
int* topOrder, *in;

int main()
{
	buildGraph(G);
	topologicalSort();
	if (topOrder[0] == 0)
		printf("0");
	else
		for (int i = 1; i <= n; i++)
			printf(" %c", G.V[topOrder[i]].vname);
	freeGraph();
	return 0;
}

void buildGraph(Graph G)
{
	int n = readline(), vname;
	G.V_n = n;
	for (int i = 0; i < n; i++)//정점 삽입
	{
		printf("%d\n", i);
		vname = readchar();
		insertVertex(vname, i);
	}
	int m = readline(), uName, wName;
	G.E_n = m;
	for (int i = 0; i < m; i++)//간선 삽입
	{
		uName = readline();
		wName = readline();
		insertDirectedEdge(uName, wName, i);
	}
	return;
}


Adj* get_list()
{
	Adj* p = (Adj*)malloc(sizeof(Adj));
	p->edge_index = -1;
	p->next = NULL;
	return p;
}

char readchar()
{
	char v;
	scanf(" %c", &v);
	getchar();
	printf("%c 입력\n", v);
	return v;
}

int readline()
{
	int line;
	scanf("%d", &line);
	getchar();
	return line;
}

void insertVertex(char vName, int i)
{
	printf("정점을 삽입합니다. %c, %d\n", vName, i);
	G.V[i].vname = vName;
	G.V[i].outEdges = get_list();//진출부착간선리스트
	G.V[i].inEdges = get_list();//진입부착간선리스트
	G.V[i].inDegree = 0; //정점 i의 진입차수 초기화
}

void insertDirectedEdge(char uName, char wName, int i)
{
	int u = index(uName), w = index(wName);
	G.E[i].origin = u;
	G.E[i].destination = w;
	addFirst(G.V[u].outEdges, i);
	addFirst(G.V[w].inEdges, i);
	G.V[w].inDegree++;
	return;
}

int index(char vName)
{
	for (int i = 0; i < n; i++)
		if (G.V[i].vname == vName)
			return i;
}

void addFirst(Adj* H, int i)
{
	Adj* p= get_list();
	p->edge_index = i;//삽입해야 하는 원소가 이게 맞는지 확인
	p->next = H->next;
	H->next = p;
	return;
}

void topologicalSort()
{
	Queue* Q = initQueue(G);
	char u;
	for (int i = 0; i < n; i++)
	{
		in[i] = G.V[i].inDegree;
		if (in[i] == 0)
			enqueue(Q, G.V[i].vname);//진입차수가 0인 정점들을 Q에 삽입
	}
	int t = 1, e;//위상순위
	char w;
	Adj* p;
	while (!isEmpty(Q))
	{
		u = dequeue(Q);
		topOrder[t] = u;
		t = t + 1;
		p = G.V[u].outEdges;
		while (p != NULL)
		{
			e = G.V[u].outEdges->edge_index;
			w = G.E[e].destination;
			in[w] = in[w] - 1;
			if (in[w] == 0)
				enqueue(Q, w);
		}
	}

	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}

Queue* initQueue(Graph G)
{
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->size = G.V_n;
	Q->Qu = (int*)malloc(sizeof(int) * Q->size);
	Q->front = 0;
	Q->rear = Q->size - 1;
	return Q;
}

void enqueue(Queue* Q, char v)
{
	if (isFull(Q))
		return;
	Q->rear = (Q->rear + 1) % Q->size;
	Q->Qu[Q->rear] = v;
}

char dequeue(Queue* Q)
{
	if (isEmpty(Q))
		return -1;
	char e = Q->Qu[Q->front];
	Q->front = (Q->front + 1) % Q->size;
	return e;
}

int isFull(Queue* Q)
{
	if ((Q->rear + 2) % Q->size == Q->front)
		return 1;
	else
		return 0;
}

int isEmpty(Queue* Q)
{
	if ((Q->rear + 1) % Q->size == Q->front)
		return 1;
	else
		return 0;
}

void freeGraph()
{
	for (int i = 0; i < G.V_n; i++)
		free_incid_list(G.V[i].inEdges);
}

void free_incid_list(Adj* p)
{
	Adj* tmp;
	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}
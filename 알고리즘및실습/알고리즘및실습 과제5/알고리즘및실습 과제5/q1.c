#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//�׷����� ���� Ʈ���̸� Ʈ���� �߽ɰ� �߽��� �̽��� ����ϱ�
//�׷����� ���� Ʈ���� �ƴ� ��� ���� ����� ���� ���

typedef struct Graph_Edge {
	int end1;//���� 1
	int end2;//���� 2
	int e_label;//���� ��
}Edge;//���� ����ü ����

typedef struct adj_list {
	struct adj_list* linked;//���� ����Ʈ ������
	int edge_index;//���� �迭�� �ε���
}Adj;//��������Ʈ ����ü ����

typedef struct Graph_Vertex {
	int name;//������ �̸�
	int v_label;//������ ��
	Adj* head;//������ ��� ��������Ʈ ������
}Vertex;//���� ����ü ����

typedef struct graph {
	Vertex* V;//���� ������
	Edge* E;//���� ������
	int V_n;//������ ����
	int E_n;//������ ����
}Graph;//�׷��� ����ü ����

//������� Ž���� ���� ���ÿ� ����ü
typedef struct stack {
	int* arr;//���� �迭
	int t;//������ top
	int N;//������ ũ��
}Stack;//���� ����ü ����

//�Լ��� ���� ������ �Ʒ��� ���
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
	Graph* G = (Graph*)malloc(sizeof(Graph));//�׷��� G ����
	int n, m, v1, v2, flag = 0;
	scanf("%d %d", &n, &m);//������ ������ ���� �Է�
	init_Graph(G, n, m);//�׷��� �ʱ�ȭ
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &v1, &v2);//���� ������ ���� ������ ���� �Է�
		insert_Edge(G, i, v1, v2);//���� ����
	}

	//G�� ����Ŭ�� �ִ��� �����ϱ�
	for (int i = 0; i < G->V_n; ++i)
	{
		//DFS(G, i);
		if (flag != 0)
		{
			break;
		}
	}
	if(flag == 0)//G�� Ʈ���� ���
		findCenter(G);//�߽��� ã�´�.

	free_Graph(G);//G�� �޸� ����
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
void findCenter(Graph* G)//�߽� ã�� �˰���
{
	Graph T = *G;
	int count = 1;
	while (numVertices(G) > 2)//������ ������ 2���� ũ�� ���� Ʈ�� ���� �߽��� �ƴ� ������ �����Ѵ�.
	{
		removeLeaves(&T, 1, 0);//�θ� ������ NULL�� �д�.
		count++;//���� �������� ������ �̽����� ������Ų��.
	}
	print_center(&T);//���� ����(�߽�)�� ����Ѵ�.
	printf("%d\n", count);//�߽��� �̽����� ����Ѵ�.
}

//������ ������ ���� �˰���
int numVertices(Graph* G)
{
	int cnt = 0;
	for (int i = 0; i < G->V_n; ++i)
		if (G->V[i].name != -1)//������ �̸��� �����ϴ� ���Ҹ� ã�´�.
			cnt++;//�����ϸ� cnt�� ������Ų��.
	return cnt;//������ ������ ��ȯ�Ѵ�.
}

//�� ���� �˰���
void removeLeaves(Graph* G, int v, int p)
{
	int c = 0, w;
	Adj* k = G->V[v - 1].head->linked;
	while (k != NULL)//����� ������ ������ ���
	{
		c = c + 1;
		w = opposite(G, k, v);
		if (w != p)//�ݴ� ������ �θ� ��尡 �ƴ� ���
			removeLeaves(G, w, v);//
	}
	if (c == 1)//�ش� ������ �θ� ���� ��
		removeVertex(G, v);//������ �����Ѵ�.
}

void removeVertex(Graph* G, int v)
{
	Adj* p = G->V[v - 1].head->linked, * tmp;
	while (p != NULL)
	{
		remove_Opposite_incd(G, p, v);//�ݴ��� ������ �ش� ���� ����Ʈ�� ����
		tmp = p->linked;
		free(p);//���� �޸� ����
		p = tmp;
	}
	free(G->V[v - 1].head);//��� ��� �޸� ����
	G->V[v - 1].name = -1;
	G->V[v - 1].v_label = -1;//������ �ʱ�ȭ�Ѵ�.
}

void remove_Opposite_incd(Graph* G, Adj* p, int v)//�ݴ��� ������ ����� ���� ���� ����
{
	int index = p->edge_index;
	int w = opposite(G, p, v);
	Adj* q = G->V[w - 1].head, * tmp;
	while (q->linked != NULL)
	{
		if (q->linked->edge_index == index)//�ݺ��� ���� ���� �ε����� ����� ����Ʈ�� ã�´�.
		{
			//��������Ʈ ����(���� �� �����ϱ�)
			tmp = q->linked->linked;
			free(q->linked);
			q->linked = tmp;

			//���� ���� ����
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
		if (G->V[i].name != -1)//�������� ���� ������ ã�´�.
			printf("%d ", G->V[i].name);//������ �������� �ʾҴٸ�, �� �߽��̹Ƿ� �߽� �̸��� ����Ѵ�.
	printf("\n");
}

//*******************************************

Adj* get_list(int index, Adj* link)//����Ʈ ���� �Լ�
{
	Adj* p = (Adj*)malloc(sizeof(Adj));
	p->edge_index = index;
	p->linked = link;
	return p;
}

int opposite(Graph* G, Adj* A, int vs)//�ݴ��� ������ ��ȯ�ϴ� �Լ�
{
	Edge e = G->E[A->edge_index];
	return (e.end1 == vs) ? e.end2 : e.end1;
}

void init_Vertex(Graph* G, int n)//���� ������ �ʱ�ȭ�ϴ� �Լ�
{
	G->V_n = n;
	G->V = (Vertex*)malloc(sizeof(Vertex) * n);//���� �迭 �޸� �Ҵ�

	for (int i = 0; i < n; ++i)
	{
		G->V[i].name = i + 1;//�ʱ⿡ ������ ���� ������ �ε������� 1 ū ������ �Ѵ�.
		G->V[i].head = get_list(-1, NULL);//��� ���� ����Ʈ�� �����Ͽ� �����Ѵ�.
		G->V[i].v_label = -1;//���� -1�� �ʱ�ȭ�Ѵ�.
	}
}

void init_Graph(Graph* G, int n, int m)//�׷����� �ʱ�ȭ�ϴ� �Լ�
{
	init_Vertex(G, n);//���� �ʱ�ȭ
	init_Edge(G, m);//���� �ʱ�ȭ
}

void init_Edge(Graph* G, int m)//������ �ʱ�ȭ�ϴ� �Լ�
{
	G->E = (Edge*)malloc(sizeof(Edge) * m);//���� �迭 �޸� �Ҵ�
	G->E_n = m;

	for (int i = 0; i < m; ++i)
	{
		G->E[i].end1 = -1;
		G->E[i].end2 = -1;
		G->E[i].e_label = -1;//������ ���� -1�� �ʱ�ȭ�Ѵ�.
	}

}

void insert_Edge(Graph* G, int index, int v1, int v2)//���� ���� �Լ�
{
	set_Edge(G, index, v1, v2);//�Է¹��� ������ ���� �迭�� ����
	insert_Adj(G, index, v1, v2);//������ ���� ����Ʈ�� ������ �����Ѵ�.
	if (v1 != v2)//v1�� v2�� ���� ���� ��� : ����Ŭ�� �ƴ� ���
		insert_Adj(G, index, v2, v1);//�ݴ��� �������� ������ ���� ����Ʈ�� �����Ѵ�.
}

void set_Edge(Graph* G, int index, int v1, int v2)//���� �迭�� ������ �� ����
{
	G->E[index].end1 = v1;
	G->E[index].end2 = v2;
	G->E[index].e_label = -1;
}

void insert_Adj(Graph* G, int index, int v1, int v2)//���� ����Ʈ ����
{
	Adj* p = G->V[v1 - 1].head, *tmp = NULL;

	while (p->linked != NULL && opposite(G, p->linked, v1) < v2)//������������ �����ϱ� ���� ������ ��ġ�� ã�´�.
		p = p->linked;
	tmp = get_list(index, p->linked);//��ġ�� ã������ ����Ʈ�� �����Ͽ� �����Ѵ�.
	p->linked = tmp;
}

void free_Graph(Graph* G)//�׷��� �޸� ����
{
	for (int i = 0; i < G->V_n; ++i)
		free_Adj(G->V[i].head);//�������� ����� ����Ʈ ����
	free(G->V);//���� �迭 ����
	free(G->E);//���� �迭 ����
	free(G);//�׷��� ����
}

void free_Adj(Adj* p)//����Ʈ �޸� ����
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
	//printf("DFS ���� : v - %d\n", G->V[s-1].name);
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

//���� �޽��
void initStack(Stack* S, int vsize)//���� �ʱ�ȭ
{
	S->arr = (int*)malloc(sizeof(int) * vsize);
	S->t = -1;
	S->N = vsize;
}

void pushStack(Stack* S, int e)//���ÿ� ���� ����
{
	if (S->t == S->N - 1)
		return;//fullStackException()
	S->t++;
	S->arr[S->t] = e;
}

int isEmptyStack(Stack* S)//������ ����ִ��� Ȯ���ϴ� �Լ�
{
	if (S->t == -1)
		return 1;
	else
		return 0;
}

int popStack(Stack* S)//���ÿ��� ���� �����ϱ�
{
	if (isEmptyStack(S))
		return 0;//emptyStackexception()
	S->t--;
	return S->arr[S->t + 1];
}
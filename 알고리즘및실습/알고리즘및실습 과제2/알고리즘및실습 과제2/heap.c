#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//���� ����� ���� ����Ʈ ����ü
typedef struct heap {
	struct heap* left;//���� �ڽ� ������
	struct heap* right;//������ �ڽ� ������
	int key;//���� ����Ʈ�� Ű
	int level;//���� ����Ʈ�� ����
}Node;//�� �� ���� ����Ʈ ����ü�� �̸��� ���� �����Ѵ�.

Node* getnode();//��带 �����ϴ� �Լ�
Node* convertToCompleteBinaryTree(Node*, int*, int, int);//���� ���� Ʈ���� �����ϴ� �Լ�
Node* BuildHeap(Node*, int*, int);//��ȭ�� �����ϴ� �Լ�
void rBuildHeap(Node*);//BuildHeap �Լ� ������ ��͵Ǿ� ��ȭ�� �����ϴ� �Լ�
void ARRAY(Node*, int*);//����� ���� ������ ���� ���� Ʈ���� Ű�� �迭�� �����ϴ� �Լ�
void printHeap(int*, int);//���� Ű�� ����ϴ� �Լ�
void downHeap(Node*);//���� �ִ������� �����ϴ� �Լ�
void freeHeap(Node*);//���Ḯ��Ʈ�� �Ҵ�� �޸𸮸� �����ϴ� �Լ�
int isInternal(Node*);//���� Ʈ�� �� ���� ��带 �Ǻ��ϱ� ���� �Լ�


int main()
{
	int n, H[100];//�迭 ũ�⸦ �����ϴ� ���� n�� Ű�� ������ �迭 H�� ����
	Node* T = getnode();//���� Ʈ���� ��Ʈ ��尡 �� ��� T�� ����
	scanf("%d", &n);//n�� ���� �Է�
	for (int i = 1; i <= n; i++)//������� �Էµ� Ű�� ���� �迭 H�� ����
		scanf("%d", &H[i]);
	T = BuildHeap(T, H, n);//�� ����
	ARRAY(T, H);//���� Ű�� ���� ������� �迭 H�� ����
	printHeap(H, n);//�迭 H�� Ű ���� ���
	freeHeap(T);//���� �Ҵ�� �޸𸮸� �����Ѵ�.
	return 0;
}

Node* getnode()
{
	Node* p = (Node*)malloc(sizeof(Node));//��� p�� �����Ͽ� ���� �Ҵ�
	p->left = NULL;
	p->right = NULL;//�� �ڽ� ��� �����ʹ� ����ֵ��� �����Ѵ�.
	return p;//����� �ּҸ� ��ȯ
}

Node* BuildHeap(Node* T, int* H, int n)
{
	T = convertToCompleteBinaryTree(T, H, n, 1);//���� ���� Ʈ���� �����Ͽ� ��Ʈ ��忡 ��ȯ�Ѵ�.
	rBuildHeap(T);//������ �Ӽ��� �����ϱ� ���� rBuildHeap �Լ��� �����Ѵ�.
	return T;//��Ʈ ��带 ��ȯ
}

Node* convertToCompleteBinaryTree(Node* t, int* H, int n, int i)
{
	if (i <= n)//�ε���(i)�� ������ ������ ���� ���� ��� �Ʒ� �ڵ带 �����Ѵ�.
	{
		t->level = i;//�迭�� �ε����� ����� ������ ���Ѵ�.
		t->key = H[i];//�ش� �ε����� ���Ҹ� ����� Ű������ ���Ѵ�.
		t->left = getnode();
		t->right = getnode();//�� �ڽ� ��带 �����Ͽ� ���� ���� �����.
		t->left = convertToCompleteBinaryTree(t->left, H, n, 2 * i);
		t->right = convertToCompleteBinaryTree(t->right, H, n, 2 * i + 1);//���� ���� Ʈ�� ������ ��͸� ���� �ݺ��Ѵ�.
	}
	return t;//t�� ��ȯ
}

void rBuildHeap(Node* v)
{
	if (isInternal(v))//v�� ���� ����� ���
	{
		rBuildHeap(v->left);//���� �ڽ� ����� ������ �Ӽ��� �����Ѵ�.
		rBuildHeap(v->right);//������ �ڽ� ����� ������ �Ӽ��� �����Ѵ�.
		downHeap(v);//������ �Ӽ� ����
	}
}

void downHeap(Node* t)
{
	if(!isInternal(t))//�ڽĵ��� �ܺγ���� ��� downHeap �Լ��� �������� �ʴ´�.
		return;
	Node* bigger = t->left;//�ڽ��� Ű �� ū ���� ���� bigger�� �����Ѵ�.
	if (isInternal(t->right))
		if (t->right->key > bigger->key)//������ �ڽ��� Ű ���� ���� �ڽ��� Ű ������ Ŭ ���
			bigger = t->right;//bigger�� ������ �ڽ��� Ű ���� �����Ѵ�.
	if (t->key > bigger->key)
		return;//�ش� ����� Ű ���� �ڽ� ����� Ű ������ Ŭ ��� �Ʒ� �ڵ带 �������� �ʴ´�.
	int tmp = t->key;
	t->key = bigger->key;
	bigger->key = tmp; //Ű ���� ��ȯ�����ν� ������ �Ӽ��� �����Ѵ�.
	downHeap(bigger);//��ȯ�� �̿��� �ڽ� ���� ���
}

int isInternal(Node* p)
{
	if (p->left != NULL && p->right != NULL)//�ڽ� ����� �����Ϳ� �ּҰ� ����Ǿ� ���� ��� ��� p�� ���� ����̴�.
		return 1;
	else
		return 0;
}

void ARRAY(Node* T, int* H)
{
	if (isInternal(T))//��� T�� ���� ����� ���
	{
		H[T->level] = T->key;//�ش� ������ Ű ���� �����Ѵ�.
		ARRAY(T->left, H);//���� �ڽ� ���� ���
		ARRAY(T->right, H);//������ �ڽ� ���� ���
	}
}

void printHeap(int* H, int n)
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);//���� ������� Ű ���� ����Ѵ�.
}

void freeHeap(Node* H)//��� �޸� ������ ������ȸ ������ �����Ѵ�.
{
	if (H->left != NULL)
		freeHeap(H->left);//���� �ڽ� ��� �޸� ����
	if (H->right != NULL)
		freeHeap(H->right);//������ �ڽ� ��� �޸� ����
	free(H);//�ش� ��� �޸� ����
}

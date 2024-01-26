#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct tree {//Ʈ�� ����ü ����
	struct tree* lChild;//���� �ڽ� ������
	struct tree* rChild;//������ �ڽ� ������
	int key;//key �� ����
	int height;//����� ���� ����
	struct tree* parent;//�θ� ������
}Node;

Node* getnode();//��� �޸� �Ҵ� �� ��ȯ
void expandExternal(Node*);//�ܺ� ��� Ȯ��
int findElement(Node*, int);//���Ҹ� ã�� ��ȯ
void insertItem(Node*, int);//��� ����
Node* treeSearch(Node*, int);//���� Ʈ�� Ž��
int isExternal(Node*);//�ܺ� ��� ���� Ȯ��
int isInternal(Node*);//���� ��� ���� Ȯ��
Node* inOrderSucc(Node*);//����� ������ȸ �İ��ڸ� ��ȯ
void reduceExternal(Node*);//�ܺ� ��� ����
void printTree(Node*);//Ž�� Ʈ�� ���
void freeTree(Node*);//Ʈ�� �޸� ����
void searchAndFixAfterInsertion(Node*);//Ʈ�� Ž�� �� ���� ����, �ұ��� Ž��
void restructure(Node* x, Node*, Node*);//�ұ��� Ž�� �� ����
int updateHeight(Node*);//���� ����
int isBalanced(Node*);//���� ���� Ȯ��

int main()
{
	char command;//��ɾ� �Է� ����
	int e, flag = 1, result;//��� ���Ҹ� �Է¹޴� ����, �ݺ����� �����ϴ� ����, ������� �����ϴ� ����
	Node* tree = getnode();//��Ʈ ��� ����
	while (flag)
	{
		scanf("%c", &command);//��ɾ� �Է�
		getchar();
		switch (command)
		{
		case 'i'://��� ����
			scanf("%d", &e);//����� Ű �� �Է�
			getchar();
			insertItem(tree, e);//�Է¹������ ��带 �����Ѵ�.
			break;
		case 's'://��� Ž��
			scanf("%d", &e);//����� Ű �� �Է�
			getchar();
			result = findElement(tree, e);//�ش� ��尡 �ִ��� Ž���Ͽ� ������� ��ȯ�Ѵ�.
			if (!result)//�ش� ��尡 ������
				printf("X\n");//X�� ���
			else//������ ���
				printf("%d\n", result);//����� Ű �� ���
			break;
		case 'p'://��ü Ʈ�� ���
			printTree(tree);
			printf("\n");
			break;
		case 'q'://���α׷� ����
			freeTree(tree);//Ʈ���� �Ҵ�� �޸� ����
			flag = 0;//�ݺ����� �����ϱ� ���� flag�� 0�� ����
			break;
		default://�� ���� ��ɾ� �Է� ��
			printf("error!\n");//���� ǥ��
			break;
		}
	}
	return 0;
}

Node* getnode()
{
	Node* p = (Node*)malloc(sizeof(Node));//��� �޸� �Ҵ�
	p->lChild = NULL;
	p->rChild = NULL;
	p->parent = NULL;//���� �ڽ�, ������ �ڽ�, �θ� ��� �����͸� ��� �ʱ�ȭ�Ѵ�.
	return p;//�ش� ����� �ּ� ��ȯ
}

int findElement(Node* T, int k)
{
	Node* p = treeSearch(T, k);//Ʈ�� Ž���� ���� �ش� ��带 ã�´�.
	if (isExternal(p))//���� Ž���Ͽ��� ��尡 ���� ���
		return 0;//0�� ��ȯ
	else
		return p->key;//������ ��� �ش� ����� Ű �� ��ȯ
}
void insertItem(Node* t, int k)
{
	Node* w = treeSearch(t, k);//�ڽ��� ������ ��带 Ʈ�� Ž������ ã�´�.
	if (isInternal(w))//ã�� ��尡 ���� ����� ���, ��带 ������ �� ����.
		return;
	else
	{
		w->key = k;//Ű ���� ����
		expandExternal(w);//�ش� ���� Ʈ�� Ȯ��
		searchAndFixAfterInsertion(w);//���� �� AVL Ʈ���� ������ �����Ѵ�.
		return;
	}
}

void expandExternal(Node* w)
{
	Node* l = getnode();
	Node* r = getnode();//�ܺ� ��� 2�� ����

	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = w;
	l->height = 0;//���� �ڽ� ��带 �ʱ�ȭ�Ͽ� w�� ����

	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = w;
	r->height = 0;//������ �ڽ� ��带 �ʱ�ȭ�Ͽ� w�� ����

	w->lChild = l;//w�� ���� �ڽ� ��带 ����
	w->rChild = r;//w�� ������ �ڽ� ��带 ����
	w->height = 1;//w�� ���̴� 1
	return;
}

Node* treeSearch(Node* t, int k)
{
	if (isExternal(t))//Ž�� ���� ��尡 �ܺ� ����� ���
		return t;//��带 ��ȯ
	if (k == t->key)
		return t;//Ű�� ã���� ���, �ش� ��带 ��ȯ
	else if (k < t->key)
		return treeSearch(t->lChild, k);//���� �ڽ� ���� �Լ��� ���
	else
		return treeSearch(t->rChild, k);//������ �ڽ� ���� �Լ��� ���
}

int removeElement(Node* t, int k)
{
	Node* w = treeSearch(t, k);//��带 Ž���Ͽ� w�� ����
	if (isExternal(w))
		return 0;//�ܺ� ����� ��� Ű�� �����Ƿ� 0�� ��ȯ
	Node* z = w->lChild;
	int elem = w->key;
	if (!isExternal(z))//���� �ڽ� ��尡 �ܺ� ��尡 �ƴ� ���
		z = w->rChild;//z�� ������ �ڽ� ���� �Ѵ�.
	if (isExternal(z))//�ش� ��尡 �ܺ� ����� ���
		reduceExternal(z);//z�� ����
	else//�� �ڽ� ��� ���� ����� ���
	{
		Node* y = inOrderSucc(w);//���� ��ȸ �İ��ڸ� ��ȯ�޴´�.
		if (y == NULL)//���� ��ȸ �İ��ڰ� ���� ���
			reduceExternal(z);//z�� ����
		else
		{
			z = y->lChild;//z�� y�� ���� �ڽ� ���
			w->key = y->key;//w�� Ű ���� y�� Ű ������ �Ѵ�.
			reduceExternal(z);//z�� ����
		}
	}
	return elem;//������ Ű ���� ��ȯ�Ѵ�.
}

int isExternal(Node* w)
{
	if (w->lChild == NULL || w->rChild == NULL)//�ڽ��� �� �� �ϳ��� ���� ���
		return 1;//�ܺ� ����̴�.
	else
		return 0;//�ڽ��� ���� ��� ���� ����̹Ƿ� 0�� ��ȯ
}

int isInternal(Node* w)
{
	if (w->lChild != NULL || w->rChild != NULL)//�ڽ��� �� �� �ϳ��� ���� ���
		return 1;//���� ����̴�.
	else
		return 0;//��� �ڽ��� ���� ��� �ܺ� ����̹Ƿ� 0�� ��ȯ
}

Node* inOrderSucc(Node* w)
{
	w = w->rChild;//w�� ������ ���� �̵�
	while (isInternal(w->lChild))//���� ��ȸ�� ��� Ž���� �ݺ�
		w = w->lChild;//�ش� ����� ���� �ڽ� ���� �̵�
	return w;//�ݺ� �� �ش� ��带 ��ȯ
}

Node* sibling(Node* w)
{
	if (w->parent == NULL)//��Ʈ ����� ���
		return NULL;
	if (w->parent->lChild == w)//w�� ���� �ڽ��� ���
		return w->parent->rChild;//w�� ������ ������ ��ȯ
	else//w�� ������ �ڽ��� ���
		return w->parent->lChild;//w�� ���� ������ ��ȯ
}

void reduceExternal(Node* z)
{
	Node* w = z->parent;//z�� �θ� ��� �����͸� w�� ����
	Node* zs = sibling(z);//z�� ���� ��带 ����
	if (w->parent == NULL)//��Ʈ ����� ���
	{
		Node* tmp = w;
		w = zs;//��ȯ���� ���� ��带 ��Ʈ ���� ����
		zs->parent = NULL;//�θ� ��� ������ �ʱ�ȭ
		free(tmp);//��Ʈ ��带 ����
	}
	else
	{
		Node* g = w->parent;//w�� �θ� ��带 g�� ����
		zs->parent = g;//���� ����� �θ� ��嵵 w�� �θ� ���� ����.
		if (w == g->lChild)//w�� g�� ���� �ڽ��� ���
			g->lChild = zs;//zs�� ���� �ڽ����� ����
		else//w�� g�� ������ �ڽ��� ���
			g->rChild = zs;//zs�� ������ �ڽ����� ����
		free(w);//w�� ����
	}
	free(z);//���������� z�� ����
}

void printTree(Node* t)
{
	if (isExternal(t))//Ʈ���� �ƴ� ���
		return;
	else//��� ����� ���� ��ȸ�� ������
		printf(" %d", t->key);//Ű �� ���
	if (t->lChild != NULL)
		printTree(t->lChild);//���� �ڽ� ���� ���
	if (t->rChild != NULL)
		printTree(t->rChild);//������ �ڽ� ���� ���
}

void freeTree(Node* t)
{//��� �޸� ������ ���� ��ȸ�� ������.
	if (t->lChild != NULL)
		freeTree(t->lChild);//���� �ڽ� ���� ���
	if (t->rChild != NULL)
		freeTree(t->rChild);//������ �ڽ� ���� ���
	if (t != NULL)
		free(t);
}

void searchAndFixAfterInsertion(Node* w)
{
	w->lChild->height = 0;
	w->rChild->height = 0;//w�� �ڽ� ����� ���̴� ��� 0�̰�,
	w->height = 1;//w�� ���̴� 1�̴�.
	if (w->parent == NULL)//w�� ��Ʈ ����� ��� 
		return;
	Node* z = w->parent;//z�� w�� �θ� ���� �Ѵ�.
	while (updateHeight(z) && isBalanced(z))//�ڽ� ���� ���̰� 2���� ũ�� ������ �����ϰ� ���� ���
	{
		if (z->parent == NULL)//��Ʈ ��忡 �����Ͽ��� �� �ش� �Լ� ����
			return;
		z = z->parent;//�θ� ���� �̵��Ͽ� �ݺ�
	}
	if (isBalanced(z))//z�� ������ �̷�� ���� ���
		return;
	//�ұ����� �����Ѵ�.
	Node* x = NULL, * y = NULL;
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;//y�� ã�� �����Ѵ�.

	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else
		x = y->rChild;//x�� ã�� �����Ѵ�.
	//y�� z�� ��� �ڽ�, x�� z�� ��� �����̴�.
	restructure(x, y, z);//�� ������ �ұ����� �����Ѵ�.
}

void restructure(Node* x, Node* y, Node* z)
{
	Node* a, * b, * c, * T0, * T1, * T2, * T3;
	if (z->key < y->key && y->key < x->key)//Ű ���� ���Ѵ�. z<y<x
	{
		a = z, b = y, c = x;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = c->lChild;
		T3 = c->rChild;
	}
	else if (x->key < y->key && y->key < z->key)// x<y<z
	{
		a = x, b = y, c = z;
		T0 = a->lChild;
		T1 = a->rChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else if (z->key < x->key && x->key < y->key)// z<x<y
	{
		a = z, b = x, c = y;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else//y<x<z
	{
		a = y, b = x, c = z;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	//a,b,c�� ��Ʈ�� T0, T1, T2, T3�� Ű �� �񱳷� �����Ѵ�.
	if (z->parent == NULL)//z�� ��Ʈ����� ��
	{
		z = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z)//z�� ���� �ڽ��� ���
	{
		z->parent->lChild = b;
		b->parent = z->parent;//b�� ������ �ڽ����� �Ѵ�.
	}
	else //z�� ������ �ڽ��� ���
	{
		z->parent->rChild = b;
		b->parent = z->parent;//b�� ���� �ڽ����� �Ѵ�.
	}

	//T0�� T1�� a�� ����, ������ ����Ʈ���� �����
	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);//a�� ���̸� ����
	//T2�� T3�� c�� ����, ������ ����Ʈ���� �����
	c->lChild = T2;
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);//c�� ���̸� ����

	//a�� c�� b�� ����, ������ �ڽ����� �����
	b->lChild = a;
	b->rChild = c;
	updateHeight(b);//b�� ���̸� ����
}

int updateHeight(Node* w)
{
	int h;
	if (w->lChild->height > w->rChild->height)
		h = w->lChild->height;//���� �ڽ��� ���̰� Ŭ ��� ���� �ڽ��� ���̸� �����Ѵ�.
	else
		h = w->rChild->height;//������ �ڽ��� ���̰� Ŭ ��� ������ �ڽ��� ���̸� �����Ѵ�.
	if (h != w->height)//������ �ڽ��� ���̸� w�� ���̿� ���Ͽ�, ��ġ���� ���� ���
	{
		w->height = h;//w�� ���̸� h�� ��ġ�ϰ� �Ѵ�.
		return 1;//1�� ��ȯ
	}
	else//���̰� ��ġ�� ���
		return 0;//0�� ��ȯ
}

int isBalanced(Node* w)
{//�ڽİ��� ���� ���̰� 2���� ũ�� 1�� ��ȯ, �׷��� ������ 0�� ��ȯ
	if (w->lChild->height > w->rChild->height)
		return(w->lChild->height - w->rChild->height < 2 ? 1 : 0);
	else
		return(w->rChild->height - w->lChild->height < 2 ? 1 : 0);
}
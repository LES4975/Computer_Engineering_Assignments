#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct tree {//트리 구조체 선언
	struct tree* lChild;//왼쪽 자식 포인터
	struct tree* rChild;//오른쪽 자식 포인터
	int key;//key 값 변수
	int height;//노드의 높이 변수
	struct tree* parent;//부모 포인터
}Node;

Node* getnode();//노드 메모리 할당 및 반환
void expandExternal(Node*);//외부 노드 확장
int findElement(Node*, int);//원소를 찾아 반환
void insertItem(Node*, int);//노드 삽입
Node* treeSearch(Node*, int);//이진 트리 탐색
int isExternal(Node*);//외부 노드 여부 확인
int isInternal(Node*);//내부 노드 여부 확인
Node* inOrderSucc(Node*);//노드의 중위순회 후계자를 반환
void reduceExternal(Node*);//외부 노드 삭제
void printTree(Node*);//탐색 트리 출력
void freeTree(Node*);//트리 메모리 해제
void searchAndFixAfterInsertion(Node*);//트리 탐색 및 높이 설정, 불균형 탐색
void restructure(Node* x, Node*, Node*);//불균형 탐색 후 수리
int updateHeight(Node*);//높이 갱신
int isBalanced(Node*);//균형 여부 확인

int main()
{
	char command;//명령어 입력 변수
	int e, flag = 1, result;//대상 원소를 입력받는 변수, 반복문을 제어하는 변수, 결과값을 저장하는 변수
	Node* tree = getnode();//루트 노드 생성
	while (flag)
	{
		scanf("%c", &command);//명령어 입력
		getchar();
		switch (command)
		{
		case 'i'://노드 삽입
			scanf("%d", &e);//노드의 키 값 입력
			getchar();
			insertItem(tree, e);//입력받은대로 노드를 삽입한다.
			break;
		case 's'://노드 탐색
			scanf("%d", &e);//노드의 키 값 입력
			getchar();
			result = findElement(tree, e);//해당 노드가 있는지 탐색하여 결과값을 반환한다.
			if (!result)//해당 노드가 없으면
				printf("X\n");//X를 출력
			else//존재할 경우
				printf("%d\n", result);//노드의 키 값 출력
			break;
		case 'p'://전체 트리 출력
			printTree(tree);
			printf("\n");
			break;
		case 'q'://프로그램 종료
			freeTree(tree);//트리에 할당된 메모리 해제
			flag = 0;//반복문을 종료하기 위해 flag에 0을 저장
			break;
		default://그 외의 명령어 입력 시
			printf("error!\n");//에러 표시
			break;
		}
	}
	return 0;
}

Node* getnode()
{
	Node* p = (Node*)malloc(sizeof(Node));//노드 메모리 할당
	p->lChild = NULL;
	p->rChild = NULL;
	p->parent = NULL;//왼쪽 자식, 오른쪽 자식, 부모 노드 포인터를 모두 초기화한다.
	return p;//해당 노드의 주소 반환
}

int findElement(Node* T, int k)
{
	Node* p = treeSearch(T, k);//트리 탐색을 통해 해당 노드를 찾는다.
	if (isExternal(p))//만약 탐색하여도 노드가 없을 경우
		return 0;//0을 반환
	else
		return p->key;//존재할 경우 해당 노드의 키 값 반환
}
void insertItem(Node* t, int k)
{
	Node* w = treeSearch(t, k);//자식을 삽입할 노드를 트리 탐색으로 찾는다.
	if (isInternal(w))//찾은 노드가 내부 노드일 경우, 노드를 삽입할 수 없다.
		return;
	else
	{
		w->key = k;//키 값을 저장
		expandExternal(w);//해당 노드로 트리 확장
		searchAndFixAfterInsertion(w);//삽입 후 AVL 트리로 조정을 수행한다.
		return;
	}
}

void expandExternal(Node* w)
{
	Node* l = getnode();
	Node* r = getnode();//외부 노드 2개 생성

	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = w;
	l->height = 0;//왼쪽 자식 노드를 초기화하여 w에 연결

	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = w;
	r->height = 0;//오른쪽 자식 노드를 초기화하여 w에 연결

	w->lChild = l;//w에 왼쪽 자식 노드를 연결
	w->rChild = r;//w에 오른쪽 자식 노드를 연결
	w->height = 1;//w의 높이는 1
	return;
}

Node* treeSearch(Node* t, int k)
{
	if (isExternal(t))//탐색 중인 노드가 외부 노드일 경우
		return t;//노드를 반환
	if (k == t->key)
		return t;//키를 찾았을 경우, 해당 노드를 반환
	else if (k < t->key)
		return treeSearch(t->lChild, k);//왼쪽 자식 노드로 함수를 재귀
	else
		return treeSearch(t->rChild, k);//오른쪽 자식 노드로 함수를 재귀
}

int removeElement(Node* t, int k)
{
	Node* w = treeSearch(t, k);//노드를 탐색하여 w에 저장
	if (isExternal(w))
		return 0;//외부 노드일 경우 키가 없으므로 0을 반환
	Node* z = w->lChild;
	int elem = w->key;
	if (!isExternal(z))//왼쪽 자식 노드가 외부 노드가 아닐 경우
		z = w->rChild;//z를 오른쪽 자식 노드로 한다.
	if (isExternal(z))//해당 노드가 외부 노드일 경우
		reduceExternal(z);//z를 삭제
	else//두 자식 모두 내부 노드일 경우
	{
		Node* y = inOrderSucc(w);//중위 순회 후계자를 반환받는다.
		if (y == NULL)//중위 순회 후계자가 없을 경우
			reduceExternal(z);//z를 삭제
		else
		{
			z = y->lChild;//z는 y의 왼쪽 자식 노드
			w->key = y->key;//w의 키 값을 y의 키 값으로 한다.
			reduceExternal(z);//z를 삭제
		}
	}
	return elem;//삭제한 키 값을 반환한다.
}

int isExternal(Node* w)
{
	if (w->lChild == NULL || w->rChild == NULL)//자식이 둘 중 하나라도 없을 경우
		return 1;//외부 노드이다.
	else
		return 0;//자식이 있을 경우 내부 노드이므로 0을 반환
}

int isInternal(Node* w)
{
	if (w->lChild != NULL || w->rChild != NULL)//자식이 둘 중 하나라도 있을 경우
		return 1;//내부 노드이다.
	else
		return 0;//어느 자식이 없을 경우 외부 노드이므로 0을 반환
}

Node* inOrderSucc(Node* w)
{
	w = w->rChild;//w의 오른쪽 노드로 이동
	while (isInternal(w->lChild))//중위 순회로 노드 탐색을 반복
		w = w->lChild;//해당 노드의 왼쪽 자식 노드로 이동
	return w;//반복 후 해당 노드를 반환
}

Node* sibling(Node* w)
{
	if (w->parent == NULL)//루트 노드일 경우
		return NULL;
	if (w->parent->lChild == w)//w가 왼쪽 자식일 경우
		return w->parent->rChild;//w의 오른쪽 형제를 반환
	else//w가 오른쪽 자식일 경우
		return w->parent->lChild;//w의 왼쪽 형제를 반환
}

void reduceExternal(Node* z)
{
	Node* w = z->parent;//z의 부모 노드 포인터를 w에 저장
	Node* zs = sibling(z);//z의 형제 노드를 저장
	if (w->parent == NULL)//루트 노드일 경우
	{
		Node* tmp = w;
		w = zs;//반환받은 형제 노드를 루트 노드로 설정
		zs->parent = NULL;//부모 노드 포인터 초기화
		free(tmp);//루트 노드를 삭제
	}
	else
	{
		Node* g = w->parent;//w의 부모 노드를 g에 저장
		zs->parent = g;//형제 노드의 부모 노드도 w의 부모 노드와 같다.
		if (w == g->lChild)//w가 g의 왼쪽 자식일 경우
			g->lChild = zs;//zs를 왼쪽 자식으로 설정
		else//w가 g의 오른쪽 자식일 경우
			g->rChild = zs;//zs를 오른쪽 자식으로 설정
		free(w);//w를 삭제
	}
	free(z);//마지막으로 z를 삭제
}

void printTree(Node* t)
{
	if (isExternal(t))//트리가 아닐 경우
		return;
	else//노드 출력은 선위 순회를 따른다
		printf(" %d", t->key);//키 값 출력
	if (t->lChild != NULL)
		printTree(t->lChild);//왼쪽 자식 노드로 재귀
	if (t->rChild != NULL)
		printTree(t->rChild);//오른쪽 자식 노드로 재귀
}

void freeTree(Node* t)
{//노드 메모리 해제는 후위 순회를 따른다.
	if (t->lChild != NULL)
		freeTree(t->lChild);//왼쪽 자식 노드로 재귀
	if (t->rChild != NULL)
		freeTree(t->rChild);//오른쪽 자식 노드로 재귀
	if (t != NULL)
		free(t);
}

void searchAndFixAfterInsertion(Node* w)
{
	w->lChild->height = 0;
	w->rChild->height = 0;//w의 자식 노드의 높이는 모두 0이고,
	w->height = 1;//w의 높이는 1이다.
	if (w->parent == NULL)//w가 루트 노드일 경우 
		return;
	Node* z = w->parent;//z를 w의 부모 노드로 한다.
	while (updateHeight(z) && isBalanced(z))//자식 간의 높이가 2보다 크고 균형을 유지하고 있을 경우
	{
		if (z->parent == NULL)//루트 노드에 도달하였을 때 해당 함수 종료
			return;
		z = z->parent;//부모 노드로 이동하여 반복
	}
	if (isBalanced(z))//z가 균형을 이루고 있을 경우
		return;
	//불균형을 수리한다.
	Node* x = NULL, * y = NULL;
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;//y를 찾아 설정한다.

	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else
		x = y->rChild;//x를 찾아 설정한다.
	//y는 z의 어느 자식, x는 z의 어느 손자이다.
	restructure(x, y, z);//이 노드들의 불균형을 수리한다.
}

void restructure(Node* x, Node* y, Node* z)
{
	Node* a, * b, * c, * T0, * T1, * T2, * T3;
	if (z->key < y->key && y->key < x->key)//키 값을 비교한다. z<y<x
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
	//a,b,c와 부트리 T0, T1, T2, T3을 키 값 비교로 결정한다.
	if (z->parent == NULL)//z가 루트노드일 때
	{
		z = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z)//z가 왼쪽 자식일 경우
	{
		z->parent->lChild = b;
		b->parent = z->parent;//b를 오른쪽 자식으로 한다.
	}
	else //z가 오른쪽 자식일 경우
	{
		z->parent->rChild = b;
		b->parent = z->parent;//b를 왼쪽 자식으로 한다.
	}

	//T0와 T1을 a의 왼쪽, 오른쪽 서브트리로 만들기
	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);//a의 높이를 갱신
	//T2와 T3을 c의 왼쪽, 오른쪽 서브트리로 만들기
	c->lChild = T2;
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);//c의 높이를 갱신

	//a와 c를 b의 왼쪽, 오른쪽 자식으로 만들기
	b->lChild = a;
	b->rChild = c;
	updateHeight(b);//b의 높이를 갱신
}

int updateHeight(Node* w)
{
	int h;
	if (w->lChild->height > w->rChild->height)
		h = w->lChild->height;//왼쪽 자식의 높이가 클 경우 왼쪽 자식의 높이를 저장한다.
	else
		h = w->rChild->height;//오른쪽 자식의 높이가 클 경우 오른쪽 자식의 높이를 저장한다.
	if (h != w->height)//저장한 자식의 높이를 w의 높이와 비교하여, 일치하지 않을 경우
	{
		w->height = h;//w의 높이를 h와 일치하게 한다.
		return 1;//1을 반환
	}
	else//높이가 일치할 경우
		return 0;//0을 반환
}

int isBalanced(Node* w)
{//자식간의 높이 차이가 2보다 크면 1을 반환, 그렇지 않으면 0을 반환
	if (w->lChild->height > w->rChild->height)
		return(w->lChild->height - w->rChild->height < 2 ? 1 : 0);
	else
		return(w->rChild->height - w->lChild->height < 2 ? 1 : 0);
}
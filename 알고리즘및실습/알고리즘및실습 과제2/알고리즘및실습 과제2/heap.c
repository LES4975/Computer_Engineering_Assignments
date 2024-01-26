#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//힙에 사용할 연결 리스트 구조체
typedef struct heap {
	struct heap* left;//왼쪽 자식 포인터
	struct heap* right;//오른쪽 자식 포인터
	int key;//연결 리스트의 키
	int level;//연결 리스트의 레벨
}Node;//이 후 연결 리스트 구조체의 이름을 노드로 정의한다.

Node* getnode();//노드를 생성하는 함수
Node* convertToCompleteBinaryTree(Node*, int*, int, int);//완전 이진 트리를 생성하는 함수
Node* BuildHeap(Node*, int*, int);//힙화를 수행하는 함수
void rBuildHeap(Node*);//BuildHeap 함수 내에서 재귀되어 힙화를 수행하는 함수
void ARRAY(Node*, int*);//노드의 레벨 순서에 따라 이진 트리의 키를 배열에 저장하는 함수
void printHeap(int*, int);//힙의 키를 출력하는 함수
void downHeap(Node*);//힙을 최대힙으로 조정하는 함수
void freeHeap(Node*);//연결리스트에 할당된 메모리를 해제하는 함수
int isInternal(Node*);//이진 트리 내 내부 노드를 판별하기 위한 함수


int main()
{
	int n, H[100];//배열 크기를 결정하는 변수 n과 키를 저장할 배열 H를 선언
	Node* T = getnode();//이진 트리의 루트 노드가 될 노드 T를 선언
	scanf("%d", &n);//n의 값을 입력
	for (int i = 1; i <= n; i++)//순서대로 입력된 키의 값을 배열 H에 저장
		scanf("%d", &H[i]);
	T = BuildHeap(T, H, n);//힙 생성
	ARRAY(T, H);//힙의 키를 레벨 순서대로 배열 H에 저장
	printHeap(H, n);//배열 H의 키 값을 출력
	freeHeap(T);//힙에 할당된 메모리를 해제한다.
	return 0;
}

Node* getnode()
{
	Node* p = (Node*)malloc(sizeof(Node));//노드 p를 선언하여 동적 할당
	p->left = NULL;
	p->right = NULL;//두 자식 노드 포인터는 비어있도록 설정한다.
	return p;//노드의 주소를 반환
}

Node* BuildHeap(Node* T, int* H, int n)
{
	T = convertToCompleteBinaryTree(T, H, n, 1);//완전 이진 트리를 생성하여 루트 노드에 반환한다.
	rBuildHeap(T);//힙순서 속성을 복구하기 위해 rBuildHeap 함수로 진입한다.
	return T;//루트 노드를 반환
}

Node* convertToCompleteBinaryTree(Node* t, int* H, int n, int i)
{
	if (i <= n)//인덱스(i)가 원소의 갯수를 넘지 않을 경우 아래 코드를 수행한다.
	{
		t->level = i;//배열의 인덱스를 노드의 레벨로 정한다.
		t->key = H[i];//해당 인덱스의 원소를 노드의 키값으로 정한다.
		t->left = getnode();
		t->right = getnode();//두 자식 노드를 연결하여 내부 노드로 만든다.
		t->left = convertToCompleteBinaryTree(t->left, H, n, 2 * i);
		t->right = convertToCompleteBinaryTree(t->right, H, n, 2 * i + 1);//완전 이진 트리 구축을 재귀를 통해 반복한다.
	}
	return t;//t를 반환
}

void rBuildHeap(Node* v)
{
	if (isInternal(v))//v가 내부 노드일 경우
	{
		rBuildHeap(v->left);//왼쪽 자식 노드의 힙순서 속성을 복구한다.
		rBuildHeap(v->right);//오른쪽 자식 노드의 힙순서 속성을 복구한다.
		downHeap(v);//힙순서 속성 복구
	}
}

void downHeap(Node* t)
{
	if(!isInternal(t))//자식들이 외부노드일 경우 downHeap 함수를 수행하지 않는다.
		return;
	Node* bigger = t->left;//자식의 키 중 큰 값을 변수 bigger에 저장한다.
	if (isInternal(t->right))
		if (t->right->key > bigger->key)//오른쪽 자식의 키 값이 왼쪽 자식의 키 값보다 클 경우
			bigger = t->right;//bigger에 오른쪽 자식의 키 값을 저장한다.
	if (t->key > bigger->key)
		return;//해당 노드의 키 값이 자식 노드의 키 값보다 클 경우 아래 코드를 수행하지 않는다.
	int tmp = t->key;
	t->key = bigger->key;
	bigger->key = tmp; //키 값을 교환함으로써 힙순서 속성을 복구한다.
	downHeap(bigger);//교환에 이용한 자식 노드로 재귀
}

int isInternal(Node* p)
{
	if (p->left != NULL && p->right != NULL)//자식 노드의 포인터에 주소가 저장되어 있을 경우 노드 p는 내부 노드이다.
		return 1;
	else
		return 0;
}

void ARRAY(Node* T, int* H)
{
	if (isInternal(T))//노드 T가 내부 노드일 경우
	{
		H[T->level] = T->key;//해당 레벨의 키 값을 저장한다.
		ARRAY(T->left, H);//왼쪽 자식 노드로 재귀
		ARRAY(T->right, H);//오른쪽 자식 노드로 재귀
	}
}

void printHeap(int* H, int n)
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);//레벨 순서대로 키 값을 출력한다.
}

void freeHeap(Node* H)//노드 메모리 해제는 후위순회 순서로 수행한다.
{
	if (H->left != NULL)
		freeHeap(H->left);//왼쪽 자식 노드 메모리 해제
	if (H->right != NULL)
		freeHeap(H->right);//오른쪽 자식 노드 메모리 해제
	free(H);//해당 노드 메모리 해제
}

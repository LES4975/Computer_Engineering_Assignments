#include <stdio.h>
#pragma warning(disable:4996)

void inPlaceHeapSort();//n개의 키로 구성된 무순배열을 제자리 힙 정렬
void printArray();//배열에 저장된 키들을 차례로 인쇄, O(n)시간 소요
void downHeap(int, int);
void rBuildHeap(int);
void swapElements(int*, int*);
//void buildHeap();
int Internal(int);
int External(int);

int H[172], n;

int main()//초기 리스트에 대해 힙 정렬의 1단계, 2단계 작업을 수행 후 인쇄
{
	int num;
	scanf("%d", &num);
	for (int i = 1; i <= num; i++)
		scanf("%d", &H[i]);
	n = num;
	rBuildHeap(1);
	inPlaceHeapSort();
	printArray();
	return 0;
}

void swapElements(int* p, int* q)
{
	int tmp;
	tmp = *p;
	*p = *q;
	*q = tmp;
}

void inPlaceHeapSort()//무순배열을 제자리 힙 정렬
{
	for (int i = n; i > 1; i--)
	{
		swapElements(H + 1, H + i);
		downHeap(1, i - 1);
	}
}

void printArray()//배열에 저장된 키들을 차례로 인쇄, O(n)시간 소요
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
}
//한 번 더 생각해 보기 
void downHeap(int i, int last)
{
	int left = 2 * i, right = 2 * i + 1;
	if (left > last)
		return;
	else
	{
		int big;
		big = left;
		if (right <= last)
		{
			if (H[big] < H[right])
				big = right;
		}
		if (H[i] > H[big])
			return;
		else
			swapElements(H + i, H + big);
		downHeap(big, last);
	}
	printf("\n");
}

void rBuildHeap(int i)
{
	if (i > n)
		return;
	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i, n);
}

int Internal(int i)
{
	if (i <= (n + n + 1) / 2)
		return 1;
	else
		return 0;
}

int External(int i)
{
	if (i > (n + n + 1) / 2)
		return 1;
	else
		return 0;
}
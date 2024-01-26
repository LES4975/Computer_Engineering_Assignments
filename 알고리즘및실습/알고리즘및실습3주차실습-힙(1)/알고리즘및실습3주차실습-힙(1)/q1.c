#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void insertItem(int);
int removeMax();
void printHeap();
void upHeap(int);
void downHeap(int);
int Internal(int);
int External(int);

int H[172], n = 0;

int main()
{
	char com;
	int p = 1, k;
	while (p)
	{
		scanf("%c", &com);
		getchar();
		switch (com)
		{
		case 'i'://키를 힙에 삽입하고 0을 인쇄
			scanf("%d", &k);
			getchar();
			insertItem(k);
			printf("0\n");
			break;
		case 'd'://힙에서 삭제하여 반환된 키를 인쇄
			printf("%d\n", removeMax());
			break;
		case 'p'://힙의 내용을 레벨 순서로 인쇄
			printHeap();
			break;
		case 'q'://프로그램 종료
			p = 0;
			break;
		default:
			printf("error!\n");
			p = 0;
			break;
		}
	}
	return 0;
}

void insertItem(int key)
{
	n = n + 1;
	H[n] = key;
	upHeap(n);
}

void upHeap(int i)
{
	if (i == 1)
		return;
	else
	{
		int tmp, parent = i / 2;
		if (H[i] < H[parent])
			return;
		else
		{
			tmp = H[i];
			H[i] = H[parent];
			H[parent] = tmp;
		}
		i = parent;
		upHeap(i);
	}
}

int removeMax()
{
	int key = H[1];
	H[1] = H[n];
	n = n - 1;
	downHeap(1);
	return key;
}
//노드 판단은 인덱스로
void downHeap(int i)
{
	int left = 2 * i, right = 2 * i + 1;
	if (External(left) && External(right))
		return;
	else
	{
		printf("내부노드 연산\n");
		int tmp, big;
		big = left;
		if (Internal(right))
		{
			if (H[big] < H[right])
				big = right;
		}
		if (H[i] > H[big])
		{
			printf("%d는 %d보다 크다.", H[i], H[big]);
			return;
		}
		else
		{
			tmp = H[i];
			H[i] = H[big];
			H[big] = tmp;
		}
		i = big;
		downHeap(i);
	}
}

void printHeap()
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}

int Internal(int i)
{
	if (i <= (n+n+1) / 2)
		return 1;
	else
		return 0;
}

int External(int i)
{
	if (i > (n+n+1) / 2)
		return 1;
	else
		return 0;
}
//이진트리를 배열로 구현, 순차힙을 삽입식으로 생성
//최대힙으로 구현 : 최댓값 삭제로 삭제 작업을 수행
//배열 인덱스 0은 비워 둔다.
//중복 키 검사는 필요 없다.
//O(1)공간으로 수행
//최대 공간<= 100

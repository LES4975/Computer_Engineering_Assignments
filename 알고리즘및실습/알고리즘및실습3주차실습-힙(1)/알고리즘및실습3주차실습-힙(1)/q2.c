#include <stdio.h>
#pragma warning(disable:4996)

void rBuildHeap(int);
void buildHeap();
void printHeap();
void downHeap(int);
int Internal(int);
int External(int);


int H[172], n;

int main() //표준입력으로 키를 한꺼번에 입력받는다.
{
	int num;
	scanf("%d", &num);
	for (int i = 1; i <= num; i++)
		scanf("%d", &H[i]);
	n = num;
	rBuildHeap(1);
	buildHeap();
	printHeap();
	//표준출력으로 생성된 힙을 인쇄한다.
	return 0;
}

void rBuildHeap(int i)
{
	if (i > n)
		return;
	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
}

void buildHeap()
{
	for (int i = n / 2; i > 0; i--)
		downHeap(i);
}

void downHeap(int i)
{
	int left = 2 * i, right = 2 * i + 1;
	if (External(left) && External(right))
		return;
	else
	{
		int tmp, big;
		big = left;
		if (Internal(right))
		{
			if (H[big] < H[right])
				big = right;
		}
		if (H[i] > H[big])
			return;
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
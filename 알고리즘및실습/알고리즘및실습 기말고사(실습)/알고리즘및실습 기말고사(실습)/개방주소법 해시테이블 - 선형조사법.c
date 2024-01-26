#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int* initBucketArray(int*, int);
void insertItem(int*, int, int);
int findElement(int*, int, int);
int getNextBucket(int, int, int);
int isEmpty(int);

int main()
{
	int M, n, flag = 1, x, search;
	char command;
	scanf("%d %d", &M, &n);
	getchar();
	int* A = (int*)malloc(sizeof(int) * M);
	A = initBucketArray(A, M);
	while (flag)
	{
		scanf("%c", &command);
		switch (command)
		{
		case 'i':
			scanf("%d", &x);
			getchar();
			insertItem(A, M, x);
			break;

		case 's':
			scanf("%d", &x);
			getchar();
			search = findElement(A, M, x);
			printf("%d", search);
			if (search != -1)
				printf(" %d", x);
			printf("\n");
			break;

		case 'e':
			flag = 0;
			break;

		default:
			printf("error!");
			flag = 0;
			break;
		}
	}
	free(A);
	return 0;
}

int* initBucketArray(int* A, int M)
{
	for (int i = 0; i < M; i++)
		A[i] = 0;
	return A;
}

int findElement(int* A, int M, int k)
{
	int v = k % M, i = 0, b;
	while (i < M)
	{
		b = getNextBucket(v, i, M);
		if (isEmpty(A[b]))
			return -1;
		else if (k == A[b])
			return b;
		else
			i++;
	}
	if (i == M)
		return -1;//NoSuchKey
}

void insertItem(int* A, int M, int k)
{
	int v = k % M, i = 0, b;
	while (i < M)
	{
		b = getNextBucket(v, i, M);
		if (isEmpty(A[b]))
		{
			A[b] = k;
			break;
		}
		else
			i++;
	}
	//overflowException()
	if (i != 0)//충돌이 있었을 경우
		for (int j = 0; j < i; j++)
			printf("C");
	printf("%d\n", b);
}

int getNextBucket(int v, int i, int M) //선형조사법
{
	return (v + i) % M;
}

int isEmpty(int p)
{
	if (p == 0)
		return 1;
	else
		return 0;
}

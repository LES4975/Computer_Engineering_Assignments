#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int hash1(int, int);
int hash2(int, int);
int* initBucketArray(int*, int);
void insertItem(int*, int, int, int);
int findElement(int*, int, int, int);
int getNextBucket(int, int, int, int, int);
void printHashtable(int*, int);
int isEmpty(int);

int main()
{
	int M, n, q, flag = 1, x, search;
	char command;
	scanf("%d %d %d", &M, &n, &q);
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
			insertItem(A, M, q, x);
			break;

		case 's':
			scanf("%d", &x);
			getchar();
			search = findElement(A, M, q, x);
			printf("%d", search);
			if (search != -1)
				printf(" %d", x);
			printf("\n");
			break;

		case 'p':
			getchar();
			printHashtable(A, M);
			break;
		case 'e':
			printHashtable(A, M);
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

int hash1(int x, int M)
{
	return x % M;
}

int hash2(int x, int q)
{
	return q - (x % q);
}

int* initBucketArray(int* A, int M)
{
	for (int i = 0; i < M; i++)
		A[i] = 0;
	return A;
}

int findElement(int* A, int M, int q, int k)
{
	int v = hash1(k, M), i = 0, b;
	while (i < M)
	{
		b = getNextBucket(v, i, M, q, k);
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

void insertItem(int* A, int M, int q, int k)
{
	int v = k % M, i = 0, b;
	while (i < M)
	{
		b = getNextBucket(v, i, M, q, k);
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

int getNextBucket(int v, int i, int M, int q, int k) //이중해싱
{
	return (v + i * hash2(k, q)) % M;
}

void printHashtable(int* A, int M)
{
	for (int i = 0; i < M; i++)
		printf(" %d", A[i]);
	printf("\n");
}

int isEmpty(int p)
{
	if (p == 0)
		return 1;
	else
		return 0;
}

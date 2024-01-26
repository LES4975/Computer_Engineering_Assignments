#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void insertNum(int*, int);
void sortNum(int*, int);

int main()
{
	int n, * arr = NULL;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * n);
	insertNum(arr, n);
	sortNum(arr, n);
	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);
	return 0;
}

void insertNum(int* p, int n)
{
	int e;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &e);
		p[i] = e;
	}
}

void sortNum(int* p, int n)
{
	int e;
	/*
	int max, k;
	for (int i = 1; i < n; i++)
	{
		e = p[i];
		max = i;
		for (int j = i - 1; j >= 0; j--)
		{
			if (p[j] > p[i])
				max = j;
		}
		for (k = i; k >= max; k--)
			p[k] = p[k - 1];
		p[k + 1] = e;
	}
	교재 참고하기*/
	for (int i = 1; i < n; i++)
	{
		e = p[i];
		int j = i - 1;
		while (j >= 0 && p[j] > e)
		{
			p[j + 1] = p[j];
			j--;
		}
		p[j + 1] = e;
	}
}
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void insertNum(int*, int);
void sortNum(int*, int);

int main()
{
	int n, *arr = NULL;
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
	int tmp, max;
	for (int i = n - 1; i >= 0; i--)
	{
		max = i;
		for (int j = i - 1; j >= 0; j--)
			if (p[j] > p[max])
				max = j;
		tmp = p[i];
		p[i] = p[max];
		p[max] = tmp;
	}
}
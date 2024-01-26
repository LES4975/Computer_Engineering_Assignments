#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int* mergeSort(int*, int);
int* rMergeSort(int*, int, int);
int* merge(int*, int, int, int);
int* partition(int*, int);

int main()
{
	int n, *A = NULL;
	scanf("%d", &n);
	A = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);
	A = mergeSort(A, n);
	for (int i = 0; i < n; i++)
		printf(" %d", A[i]);
	free(A);
	return 0;
}

int* mergeSort(int* A, int n)
{
	A = rMergeSort(A, 0, n - 1);
	return A;
}

int* rMergeSort(int* A, int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		A = rMergeSort(A, l, m);
		A = rMergeSort(A, m + 1, r);
		A = merge(A, l, m, r);
	}
	return A;
}

int* merge(int* A, int l, int m, int r)
{
	int* B = (int*)malloc(sizeof(int) * (r + 1));
	int i = l, k = l, j = m + 1;
	while (i <= m && j <= r)
	{
		if (A[i] <= A[j])
			B[k++] = A[i++];
		else
			B[k++] = A[j++];
	}
	while (i <= m)
		B[k++] = A[i++];
	while (j <= r)
		B[k++] = A[j++];
	for (k = l; k <= r; k++)
	{
		A[k] = B[k];
	}
	return A;
}
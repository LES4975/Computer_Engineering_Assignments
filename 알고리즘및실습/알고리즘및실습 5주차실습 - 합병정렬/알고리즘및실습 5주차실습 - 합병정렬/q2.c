#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct INDEX
{
	int a, b;
}Index;

void quickSort(int*, int);
void inPlaceQuickSort(int*, int, int);
int findPivot(int*, int, int);
Index* inPlacePartition(int*, int, int, int);

int main()
{
	int n, *L = NULL;
	scanf("%d", &n);
	L = (int*)malloc(sizeof(int) * n);
	quickSort(L, n);
	for (int i = 0; i < n; i++)
		printf(" %d", L[i]);
	free(L);
	return 0;
}

void quickSort(int* L, int n)
{
	for (int i = 0; i < n; i++)
		scanf("%d", &L[i]);
	int l = 0, r = n - 1;
	inPlaceQuickSort(L, l, r);
}

void inPlaceQuickSort(int* L, int l, int r)
{
	if (l >= r)
		return;
	int k = findPivot(L, l, r);
	Index* p = NULL;
	p = inPlacePartition(L, l, r, k);
	inPlaceQuickSort(L, l, p->a - 1);
	inPlaceQuickSort(L, p->b + 1, r);
	free(p);
}

int findPivot(int* L, int l, int r)
{
	int k = (l + r) / 2;
	return k;
}

Index* inPlacePartition(int* L, int l, int r, int k)
{
	int p = L[k], tmp;
	tmp = L[k];
	L[k] = L[r];
	L[r] = tmp;
	int i = l, j = r - 1;
	while (i <= j)
	{
		while (i <= j && L[i] <= p)
			i++;
		while (j >= i && L[j] >= p)
			j--;
		if (i < j)
		{
			tmp = L[i];
			L[i] = L[j];
			L[j] = tmp;
		}
	}
	tmp = L[i];
	L[i] = L[r];
	L[r] = tmp;
	Index* AB = (Index*)malloc(sizeof(Index));
	AB->a = i;
	AB->b = i;
	return AB;
}


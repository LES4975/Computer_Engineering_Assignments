#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int* initializeDictionary(int*, int, int*);
void searchKey(int*, int, int, int*);
void Binarysearch(int*, int, int, int, int*);

int main()
{
	int n, k, *D = NULL, index = -1;
	scanf("%d %d", &n, &k);
	D = (int*)malloc(sizeof(int) * n);
	D = initializeDictionary(D, n, &index);
	searchKey(D, n, k, &index);
	printf(" %d", index);
	free(D);
	return 0;
}

int* initializeDictionary(int* D, int n, int* index)
{
	for (int i = 0; i < n; i++)
		scanf("%d", &D[i]);
	return D;
}

void searchKey(int* D, int n, int k, int* index)
{
	if (D[0] > k)
		return;
	Binarysearch(D, 0, n - 1, k, index);
}

void Binarysearch(int* D, int l, int r, int key, int* index)
{
	if (l > r)
	{
		if (key < D[r])
			*index = r - 1;
		else
			*index = r;
		return;
	}
	int mid = (l + r) / 2;
	if (key == D[mid])
	{
		*index = mid;
		return;
	}
	else if (key > D[mid])
		Binarysearch(D, mid + 1, r, key, index);
	else // key < D[mid]
		Binarysearch(D, l, mid - 1, key, index);
}
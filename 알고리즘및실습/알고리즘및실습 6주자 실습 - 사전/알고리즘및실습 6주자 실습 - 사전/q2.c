#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int* initializeDictionary(int*, int);
int searchKey(int*, int, int);

int main()
{
	int n, k, * D = NULL, index = 0;
	scanf("%d %d", &n, &k);
	D = (int*)malloc(sizeof(int) * n);
	D = initializeDictionary(D, n);
	index = searchKey(D, n, k);
	printf(" %d", index);
	free(D);
	return 0;
}


int* initializeDictionary(int* D, int n)
{
	for (int i = 0; i < n; i++)
		scanf("%d", &D[i]);
	return D;
}

int searchKey(int* D, int n, int k)
{
	//int index = 0;
	if (D[0] > k)
		return 0;
	int l = 0, r = n - 1, mid;
	while (l <= r)
	{
		mid = (l + r) / 2;
		if (k == D[mid])
			return mid;
		else if (k < D[mid])
			r = mid - 1;
		else
			l = mid + 1;
	}
	//l>r
	return l;
}
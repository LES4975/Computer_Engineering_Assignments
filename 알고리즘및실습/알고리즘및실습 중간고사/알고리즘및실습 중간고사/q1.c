#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void sortHeap(int*, int);
void upHeap(int*, int, int);
void printHeap(int*, int);
int main()
{
	int n, H[172]; //N = 100
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &H[i]);
	sortHeap(H, n);
	printHeap(H, n);
	return 0;
}

void sortHeap(int* H, int n)
{
	int i = n;
	while (i > 1)
	{
		upHeap(H, n, i);
		i--;
	}
}

void upHeap(int* H, int n, int k)
{
	int tmp;
	if (k <= 1)
		return;
	int parent = k / 2;
	if (H[k] > H[parent])
	{
		tmp = H[k];
		H[k] = H[parent];
		H[parent] = tmp;
	}
	if (H[k] < H[parent])
		upHeap(H, n, parent);
	else
		upHeap(H, n, k);
}

void printHeap(int* H, int n)
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
}
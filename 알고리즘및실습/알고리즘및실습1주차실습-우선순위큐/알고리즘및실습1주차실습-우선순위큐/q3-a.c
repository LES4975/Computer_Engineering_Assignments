#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

void insertNum(int*, int*, int);
void SelectionSort(int*, int);
void InsertSort(int*, int);

int main() //정렬이 안 된 랜덤 데이터가 주어진 경우
{
	int n, * A = NULL, * B = NULL;
	scanf("%d", &n);
	A = (int*)malloc(sizeof(int) * n);
	B = (int*)malloc(sizeof(int) * n);
	insertNum(A, B, n);
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	//선택정렬 시간 체크
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	SelectionSort(A, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("선택정렬: %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart)*1000);
	
	//삽입정렬 시간 체크
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	InsertSort(A, n);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("삽입정렬: %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
	return 0;
}

void insertNum(int* p, int* q, int n)
{
	int e;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		e = rand()%10000;
		p[i] = e;
		q[i] = e;
	}
}

void SelectionSort(int* p, int n)
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

void InsertSort(int* p, int n)
{
	int e;
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
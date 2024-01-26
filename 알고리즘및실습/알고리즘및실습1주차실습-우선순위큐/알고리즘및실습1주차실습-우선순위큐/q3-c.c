#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

void insertNum(int*, int*, int);
void ReverseSort(int*, int);//데이터를 역순으로 정렬하는 함수
void SelectionSort(int*, int);
void InsertSort(int*, int);

int main() //정렬이 안 된 데이터가 주어진 경우
{
	int n, * A = NULL, * B = NULL;
	scanf("%d", &n);
	int k = n;
	for (int i = 0; i < 10; i++)
	{
		A = (int*)malloc(sizeof(int) * k);
		B = (int*)malloc(sizeof(int) * k);//배열 A와 B를 k만큼 동적할당한다.
		insertNum(A, B, k);//

		LARGE_INTEGER ticksPerSec;
		LARGE_INTEGER start, end, diff;
		ReverseSort(A, k);//배열 A를 역순으로 정렬한다.
		ReverseSort(B, k);//배열 B를 역순으로 정렬한다.

		//선택정렬 시간 체크
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		SelectionSort(A, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("A: %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		//삽입정렬 시간 체크
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		InsertSort(B, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("B: %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		k += n;
		free(A);
		free(B);
	}
	return 0;
}

void insertNum(int* p, int* q, int n)
{
	int e;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		e = rand() % 10000;
		p[i] = e;
		q[i] = e;//배열 A와 B에 원소를 저장한다.
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

void ReverseSort(int* p, int n)//데이터를 역순 정렬하는 함수
{//정렬 방식은 선택 정렬과 비슷하다.
	int tmp, max;
	for (int i = 0; i < n - 1; i++)//i를 0부터 n-2까지 증가시키며 반복한다.
	{
		max = i;
		for (int j = i + 1; j < n; j++)//j를 i+1부터 n-1까지 증가시키며 반복한다.
			if (p[j] > p[max])
				max = j;//j번째 원소가 최댓값보다 클 경우 최댓값의 인덱스를 j로 한다.
		tmp = p[i];
		p[i] = p[max];
		p[max] = tmp;//최댓값과 현재 위치의 원소를 교환한다.
	}
}

//i를 n-1부터 0이 될 때까지 감소시키며 반복한다.
//max에 현재 인덱스를 저장한다.
//최댓값을 찾는 반복을 j가 i-1부터 0이 될 때까지 감소시키며 반복한다.
//반복 중 큰 값을 찾았을 경우
//최댓값의 인덱스를 현재 j의 값으로 변경한다.
//최댓값의 인덱스를 찾았으면 p[i]와 p[max]를 서로 교환한다.

//삽입 정렬의 수행 시간을 출력한다.
//배열 A와 B에 데이터를 저장한다.
//배열 A에 선택 정렬을 실행한다.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

void insertNum(int*, int*, int);//데이터 삽입 함수
void SelectionSort(int*, int);//선택 정렬 함수
void InsertSort(int*, int);//삽입 정렬 함수

int main() //정렬이 안 된 랜덤 데이터가 주어진 경우
{
	int n, * A = NULL, * B = NULL;
	scanf("%d", &n);//N을 입력받는다.
	int k = n;//변수 k에 N의 값을 저장한다. k는 반복을 수행할 때마다 n만큼 늘어난다.

	for (int i = 0; i < 10; i++)//반복은 10회까지 수행한다.
	{
		A = (int*)malloc(sizeof(int) * k);//배열 A를 크기 k만큼 동적할당
		B = (int*)malloc(sizeof(int) * k);//배열 B를 크기 k만큼 동적할당
		insertNum(A, B, k);
		LARGE_INTEGER ticksPerSec;
		LARGE_INTEGER start, end, diff;

		//선택 정렬 수행시간 체크
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		SelectionSort(A, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("A: %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
		//삽입 정렬 수행시간 체크
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		InsertSort(B, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("B: %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
		k += n; //n의 값을 증가시켜서 수행할 경우 사용할 스크립트
		free(A);
		free(B);//배열 A와 B의 메모리 해제
	}
	return 0;
}

void insertNum(int* p, int* q, int n)//데이터 삽입 함수
{
	int e;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		e = rand() % 10000;//0부터 9999까지의 난수를 발생시킨다.
		p[i] = e;
		q[i] = e;
	}
}

void SelectionSort(int* p, int n)//선택 정렬 함수
{
	int tmp, min;
	for (int i = 0; i < n- 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
			if (p[j] < p[min])
				min = j;
		tmp = p[i];
		p[i] = p[min];
		p[min] = tmp;
	}
}

void InsertSort(int* p, int n)//삽입 정렬 함수
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
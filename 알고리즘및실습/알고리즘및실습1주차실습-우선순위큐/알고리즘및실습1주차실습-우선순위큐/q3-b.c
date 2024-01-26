#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

void insertNum(int*, int);//정순 데이터를 배열에 저장하는 함수
void SelectionSort(int*, int);//선택 정렬 함수
void InsertSort(int*, int);//삽입 정렬 함수

int main() //정렬된 데이터가 주어질 경우
{
	int n, * A = NULL, * B = NULL;
	scanf("%d", &n);//N을 입력
	int k = n;//k를 선언, k는 반복이 거듭될수록 n씩 증가할 것이다.
	for (int i = 0; i < 10; i++)
	{
		A = (int*)malloc(sizeof(int) * k);
		B = (int*)malloc(sizeof(int) * k);
		insertNum(A, k);//배열 A에 값을 저장한다.
		insertNum(B, k);//배열 B를 값을 저장한다.
		LARGE_INTEGER ticksPerSec;
		LARGE_INTEGER start, end, diff;

		InsertSort(A, k);//배열 A를 정렬한다.
		InsertSort(B, k);//배열 B를 정렬한다.

		//선택정렬 시간 체크
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		SelectionSort(A, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.12f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
		//삽입정렬 시간 체크
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		InsertSort(B, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.12f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		k += n; //k를 n만큼 증가시킬 때 사용한다.
		free(A);
		free(B);//A와 B에 할당된 메모리를 해제한다
	}
	
	return 0;
}

void insertNum(int* p, int n)//정순 데이터를 배열에 저장하는 함수
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)//0부터 n까지 배열에 저장한다.
		p[i] = i;
}

void SelectionSort(int* p, int n)//선택 정렬 함수
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

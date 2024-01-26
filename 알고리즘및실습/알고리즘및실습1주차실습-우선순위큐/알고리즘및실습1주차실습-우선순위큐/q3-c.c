#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

void insertNum(int*, int*, int);
void ReverseSort(int*, int);//�����͸� �������� �����ϴ� �Լ�
void SelectionSort(int*, int);
void InsertSort(int*, int);

int main() //������ �� �� �����Ͱ� �־��� ���
{
	int n, * A = NULL, * B = NULL;
	scanf("%d", &n);
	int k = n;
	for (int i = 0; i < 10; i++)
	{
		A = (int*)malloc(sizeof(int) * k);
		B = (int*)malloc(sizeof(int) * k);//�迭 A�� B�� k��ŭ �����Ҵ��Ѵ�.
		insertNum(A, B, k);//

		LARGE_INTEGER ticksPerSec;
		LARGE_INTEGER start, end, diff;
		ReverseSort(A, k);//�迭 A�� �������� �����Ѵ�.
		ReverseSort(B, k);//�迭 B�� �������� �����Ѵ�.

		//�������� �ð� üũ
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		SelectionSort(A, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("A: %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		//�������� �ð� üũ
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
		q[i] = e;//�迭 A�� B�� ���Ҹ� �����Ѵ�.
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

void ReverseSort(int* p, int n)//�����͸� ���� �����ϴ� �Լ�
{//���� ����� ���� ���İ� ����ϴ�.
	int tmp, max;
	for (int i = 0; i < n - 1; i++)//i�� 0���� n-2���� ������Ű�� �ݺ��Ѵ�.
	{
		max = i;
		for (int j = i + 1; j < n; j++)//j�� i+1���� n-1���� ������Ű�� �ݺ��Ѵ�.
			if (p[j] > p[max])
				max = j;//j��° ���Ұ� �ִ񰪺��� Ŭ ��� �ִ��� �ε����� j�� �Ѵ�.
		tmp = p[i];
		p[i] = p[max];
		p[max] = tmp;//�ִ񰪰� ���� ��ġ�� ���Ҹ� ��ȯ�Ѵ�.
	}
}

//i�� n-1���� 0�� �� ������ ���ҽ�Ű�� �ݺ��Ѵ�.
//max�� ���� �ε����� �����Ѵ�.
//�ִ��� ã�� �ݺ��� j�� i-1���� 0�� �� ������ ���ҽ�Ű�� �ݺ��Ѵ�.
//�ݺ� �� ū ���� ã���� ���
//�ִ��� �ε����� ���� j�� ������ �����Ѵ�.
//�ִ��� �ε����� ã������ p[i]�� p[max]�� ���� ��ȯ�Ѵ�.

//���� ������ ���� �ð��� ����Ѵ�.
//�迭 A�� B�� �����͸� �����Ѵ�.
//�迭 A�� ���� ������ �����Ѵ�.
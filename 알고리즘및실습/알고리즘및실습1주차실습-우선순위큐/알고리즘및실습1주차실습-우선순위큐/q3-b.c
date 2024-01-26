#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

void insertNum(int*, int);//���� �����͸� �迭�� �����ϴ� �Լ�
void SelectionSort(int*, int);//���� ���� �Լ�
void InsertSort(int*, int);//���� ���� �Լ�

int main() //���ĵ� �����Ͱ� �־��� ���
{
	int n, * A = NULL, * B = NULL;
	scanf("%d", &n);//N�� �Է�
	int k = n;//k�� ����, k�� �ݺ��� �ŵ�ɼ��� n�� ������ ���̴�.
	for (int i = 0; i < 10; i++)
	{
		A = (int*)malloc(sizeof(int) * k);
		B = (int*)malloc(sizeof(int) * k);
		insertNum(A, k);//�迭 A�� ���� �����Ѵ�.
		insertNum(B, k);//�迭 B�� ���� �����Ѵ�.
		LARGE_INTEGER ticksPerSec;
		LARGE_INTEGER start, end, diff;

		InsertSort(A, k);//�迭 A�� �����Ѵ�.
		InsertSort(B, k);//�迭 B�� �����Ѵ�.

		//�������� �ð� üũ
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		SelectionSort(A, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.12f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
		//�������� �ð� üũ
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		InsertSort(B, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.12f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		k += n; //k�� n��ŭ ������ų �� ����Ѵ�.
		free(A);
		free(B);//A�� B�� �Ҵ�� �޸𸮸� �����Ѵ�
	}
	
	return 0;
}

void insertNum(int* p, int n)//���� �����͸� �迭�� �����ϴ� �Լ�
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)//0���� n���� �迭�� �����Ѵ�.
		p[i] = i;
}

void SelectionSort(int* p, int n)//���� ���� �Լ�
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

void InsertSort(int* p, int n)//���� ���� �Լ�
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

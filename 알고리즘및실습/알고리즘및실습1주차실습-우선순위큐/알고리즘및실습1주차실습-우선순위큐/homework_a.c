#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

void insertNum(int*, int*, int);//������ ���� �Լ�
void SelectionSort(int*, int);//���� ���� �Լ�
void InsertSort(int*, int);//���� ���� �Լ�

int main() //������ �� �� ���� �����Ͱ� �־��� ���
{
	int n, * A = NULL, * B = NULL;
	scanf("%d", &n);//N�� �Է¹޴´�.
	int k = n;//���� k�� N�� ���� �����Ѵ�. k�� �ݺ��� ������ ������ n��ŭ �þ��.

	for (int i = 0; i < 10; i++)//�ݺ��� 10ȸ���� �����Ѵ�.
	{
		A = (int*)malloc(sizeof(int) * k);//�迭 A�� ũ�� k��ŭ �����Ҵ�
		B = (int*)malloc(sizeof(int) * k);//�迭 B�� ũ�� k��ŭ �����Ҵ�
		insertNum(A, B, k);
		LARGE_INTEGER ticksPerSec;
		LARGE_INTEGER start, end, diff;

		//���� ���� ����ð� üũ
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		SelectionSort(A, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("A: %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
		//���� ���� ����ð� üũ
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		InsertSort(B, k);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("B: %.12f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
		k += n; //n�� ���� �������Ѽ� ������ ��� ����� ��ũ��Ʈ
		free(A);
		free(B);//�迭 A�� B�� �޸� ����
	}
	return 0;
}

void insertNum(int* p, int* q, int n)//������ ���� �Լ�
{
	int e;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		e = rand() % 10000;//0���� 9999������ ������ �߻���Ų��.
		p[i] = e;
		q[i] = e;
	}
}

void SelectionSort(int* p, int n)//���� ���� �Լ�
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
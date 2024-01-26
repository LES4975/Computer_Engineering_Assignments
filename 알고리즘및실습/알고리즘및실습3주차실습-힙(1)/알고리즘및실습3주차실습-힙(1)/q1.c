#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void insertItem(int);
int removeMax();
void printHeap();
void upHeap(int);
void downHeap(int);
int Internal(int);
int External(int);

int H[172], n = 0;

int main()
{
	char com;
	int p = 1, k;
	while (p)
	{
		scanf("%c", &com);
		getchar();
		switch (com)
		{
		case 'i'://Ű�� ���� �����ϰ� 0�� �μ�
			scanf("%d", &k);
			getchar();
			insertItem(k);
			printf("0\n");
			break;
		case 'd'://������ �����Ͽ� ��ȯ�� Ű�� �μ�
			printf("%d\n", removeMax());
			break;
		case 'p'://���� ������ ���� ������ �μ�
			printHeap();
			break;
		case 'q'://���α׷� ����
			p = 0;
			break;
		default:
			printf("error!\n");
			p = 0;
			break;
		}
	}
	return 0;
}

void insertItem(int key)
{
	n = n + 1;
	H[n] = key;
	upHeap(n);
}

void upHeap(int i)
{
	if (i == 1)
		return;
	else
	{
		int tmp, parent = i / 2;
		if (H[i] < H[parent])
			return;
		else
		{
			tmp = H[i];
			H[i] = H[parent];
			H[parent] = tmp;
		}
		i = parent;
		upHeap(i);
	}
}

int removeMax()
{
	int key = H[1];
	H[1] = H[n];
	n = n - 1;
	downHeap(1);
	return key;
}
//��� �Ǵ��� �ε�����
void downHeap(int i)
{
	int left = 2 * i, right = 2 * i + 1;
	if (External(left) && External(right))
		return;
	else
	{
		printf("���γ�� ����\n");
		int tmp, big;
		big = left;
		if (Internal(right))
		{
			if (H[big] < H[right])
				big = right;
		}
		if (H[i] > H[big])
		{
			printf("%d�� %d���� ũ��.", H[i], H[big]);
			return;
		}
		else
		{
			tmp = H[i];
			H[i] = H[big];
			H[big] = tmp;
		}
		i = big;
		downHeap(i);
	}
}

void printHeap()
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}

int Internal(int i)
{
	if (i <= (n+n+1) / 2)
		return 1;
	else
		return 0;
}

int External(int i)
{
	if (i > (n+n+1) / 2)
		return 1;
	else
		return 0;
}
//����Ʈ���� �迭�� ����, �������� ���Խ����� ����
//�ִ������� ���� : �ִ� ������ ���� �۾��� ����
//�迭 �ε��� 0�� ��� �д�.
//�ߺ� Ű �˻�� �ʿ� ����.
//O(1)�������� ����
//�ִ� ����<= 100

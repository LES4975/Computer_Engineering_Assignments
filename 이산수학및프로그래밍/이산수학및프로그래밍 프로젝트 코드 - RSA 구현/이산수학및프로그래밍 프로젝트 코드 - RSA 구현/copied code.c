#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void selete(int pi, int* e)
{
	int i, j, tmp = 1;
	for (i = 2; j < pi; i++)
	{
		for (j = 1; j <= i; j++)
			if (i % j == 0 && pi % j == 0)
				tmp = j;
		if (tmp == 1)
		{
			*e = i;
			break;
		}
		tmp = 1;
	}
}

void selectpk(int* p, int* q)
{
	int random;
	int i, j;
	int ck, ck2 = 0;
	srand((unsigned)time(NULL));
	random = (rand() % 100);

	for (i = random; 1; i++)
	{
		for (j = 2; j < i / 2 + 1; j++)
		{
			if (i % j == 0)
			{
				ck = 1;
				break;
			}
			ck = 0;
		}
		if (ck == 0 && ck2 == 1)
		{
			*q = i;
			break;
		}
		if (ck == 0 && ck2 == 0)
		{
			*p = i;
			ck2 = 1;
		}

	}//�ش� ���� �̻��� ū �Ҽ� 2���� ��� ���� p�� k�� ���
		
}

void selectd(int e, int pi, int* d)
{
	int i;
	for (i = 2; i < pi; i++)//1<d<pi
		if ((e * i) % pi == 1)//e*d�� pi�� �������� �� 1
			*d = i;
}

void main()
{
	int i, j;//�ݺ���
	int sum = 1;
	int word;
	char string[501];//����
	char string2[501] = { 0, };//��ȣȭ�� ���Ͽ��� �ҷ��� ���ڿ�

	int p, q;//�Ҽ� 2��
	int n;
	int pi;//���� �Լ� = (p-1)(q-1)
	int e; //e
	int d; // d

	FILE* output, * input, * output2;
	output = fopen("./��ȣ��.txt", "w");//��ȣȭ �� ����
	selectpk(&p, &q);//������ �Ҽ��� ��� ����

	n = p * q;
	pi = (p - 1) * (q - 1);
	selecte(pi, &e);//e�� ���Ѵ�. e�� pi�� ���μ��̴�. 1<e<pi

	selectd(e, pi, &d);//d�� ���Ѵ�. e*d�� pi�� �������� �� 1�� ���´�.
	//p, q�� ��� pi, e, d�� ����Ѵ�.
	//n, e�� �����ϰ�, �������� ��з� �Ѵ�.

	printf("��ȣȭ �� ������ 500bytes �̳��� �Է��Ͻÿ� : ");
	gets(string);

	for (i = 0; i < strlen(string); i++)
	{
		for (j = 0; j < e; j++)
		{
			sum *= (int)string[i];//c = m^e mod n
			sum %= n;
		}
		fprintf(output, "%d\n", sum);
		sum = 1;
	}
	//��ȣȭ ��

	printf("��ȣȭ �� ������ ./��ȣ��.txt�� ����\n");

	fclose(output);//��ȣ�� ���� ����

	fflush(stdin);

	printf("��ȣȭ�� �ϱ� ���� Ű �Է�\n");
	getchar();
	//---------------------------------

	input = fopen("./��ȣ��.txt", "r");//��ȣȭ�� ����(��ȣȭ�� ����)
	output = fopen("./����.txt", "w");//��ȣȭ�� ����

	i = 0;
	while (!feof(input))
	{
		fscanf(input, "%d\n", &word);

		for (j = 0; j < d; j++)
		{
			sum *= word;//m = c^d mod n
			sum %= n;
		}
		string[i++] = (char)sum;
		sum = 1;
	}//��ȣȭ

	fputs(string2, output);
	printf("��ȣȭ�� ������ ./����.txt�� ����\n");

	fcloseall();
	return 0;
}
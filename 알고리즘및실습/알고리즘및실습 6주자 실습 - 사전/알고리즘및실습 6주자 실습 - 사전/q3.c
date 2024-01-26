#include <stdio.h>
#pragma warning(disable:4996)

void search_k(int*, int*, int*, int*);

int main()
{
	int a, b, cnt, k = 0;

	scanf("%d %d %d", &a, &b, &cnt);
	getchar();
	search_k(&a, &b, &cnt, &k);
	printf("%d", k);
	return 0;
}

void search_k(int *a, int *b, int* cnt, int *k)
{
	int m = (*a + *b) / 2;
	char YN;
	scanf("%c", &YN);
	if (*a == *b)//¸¶Áö¸· Àç±Í
	{
		*k = *a;
		return;
	}
	else
	{
		*cnt = *cnt - 1;
		if (YN == 'Y')
		{
			*a = m + 1;
			search_k(a, b, cnt, k);
		}
		else // YN == 'N'
		{
			*b = m;
			search_k(a, b, cnt, k);
		}
	}
}
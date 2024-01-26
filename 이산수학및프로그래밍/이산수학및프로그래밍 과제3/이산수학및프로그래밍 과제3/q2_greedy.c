#include <stdio.h>
#pragma warning(disable:4996)

int main()
{
	int N, change;
	printf("Please insert a cash : ");
	scanf("%d", &N);
	change = N;
	int c[4] = { 0 };
	//c[0] = the number of 10 won;
	//c[1] = the number of 50 won;
	//c[2] = the number of 100 won;
	//c[3] = the number of 500 won;
	while (change >= 500)
	{
		change = change - 500;
		c[3]++;
	}
	while (change >= 100)
	{
		change = change - 100;
		c[2]++;
	}
	while (change >= 50)
	{
		change = change - 50;
		c[1]++;
	}
	while (change >= 10)
	{
		change = change - 10;
		c[0]++;
	}
	printf("the minimum number of coins to make a change for N(%d \\)= %d coins", N, c[0] + c[1] + c[2] + c[3]);
	if (change != 0)
		printf("\nchange : %d \\", change);
	printf("\n\n\n");
	return 0;
}
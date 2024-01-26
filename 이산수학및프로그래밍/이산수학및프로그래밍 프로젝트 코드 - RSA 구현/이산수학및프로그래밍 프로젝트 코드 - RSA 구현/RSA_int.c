#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#include <string.h>

int n, p, q, e, d, M, EM, DM;

void Key_Generation();
int pi();
int gcd(int, int);
void Find_e(int);
void Find_d(int);
void Encryption();
void Decryption();

int main()
{
	Key_Generation();
	printf("Public Key {%d, %d}\n", e, n);
	getchar();
	printf(".\n.\n.\n.\n.\n.\n");
	printf("Insert your number : ");
	scanf("%d", &M);
	//암호화
	Encryption();
	//잘못된 키에 대한 검출은 따로 하지 않는다.
	//복호화
	Decryption();
	return 0;
}

void Key_Generation()
{
	printf("Enter the value of p and q : ");
	scanf("%d %d", &p, &q);
	n = p * q;//n = p*q
	int Pi = pi();
	Find_e(Pi);
	Find_d(Pi);
	printf("N = %d, E = %d\n", n, e);
}

int pi()
{
	printf("p : %d, q = %d\n", p, q);
	return (p - 1) * (q - 1);
}

int gcd(int n1, int n2)//Euclid
{
	int tmp;
	while (1)
	{
		tmp = n1 % n2;
		if (tmp == 0)
			return n2;
		n1 = n2;
		n2 = tmp;
	}
}

void Find_e(int Pi)
{
	for (int i = 2; i < Pi; i++)
	{
		if (gcd(i, Pi) == 1)
		{
			e = i;
			break;
		}
	}
	printf("e : %d\n", e);
}

void Find_d(int Pi)
{
	for (int i = 2; i < Pi; i++)
	{
		if (e * i % Pi == 1)
		{
			d = i;
			break;
		}
	}
	printf("d : %d\n", d);
}

void Encryption()
{
	int i, C = 1;
	for (i = 0; i < e; i++)
		C *= M;
	printf("C : %d\n", C);
	C %= n;
	EM = C;
	printf("Encrypted number: %d\n", EM);
}

void Decryption()
{
	int i, D = 1;
	for (i = 0; i < d; i++)
		D *= EM;
	printf("D : %d\n", D);
	D %= n;
	DM = D;
	printf("Decrypted number: %d\n", DM);
}
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#include <string.h>

int n, p, q, e, d;

void Key_Generation();//Key generation function
int pi();//Calculating ¥õ(n)
int gcd(int, int);//Calculating gcd(n1, n2)
void Find_e(int);//Calculating the exponent, e
void Find_d(int);//Calculating the private key, d
void Encryption(char*, int*, int*, int*);//Encryption Function
void Decryption(char*, int*, int*, int*);//Decryption Function

int main()
{
	char Sen[101];//Temporary array to insert index of space
	int M[101], EM[101], DM[101], space[101] = { 0 };//M : plain message array, EM : encrypted message array, DM : decrypted message array
	Key_Generation();//Generating keys to operate RSA system
	printf("Public Key {%d, %d}\n", e, n);//n and e are public key, so this code print these key.
	getchar();
	printf(".\n.\n.\n");
	printf("Enter your message(within 100 characters) : ");//Write the message which you want to encrypt.
	gets(Sen);//Enter the message
	for (int i = 0; i < (int)strlen(Sen); i++)
		M[i] = Sen[i];//Remember the location of space
	//Encryption
	Encryption(Sen, M, EM, space);
	//Decryption
	Decryption(Sen, EM, DM, space);
	return 0;
}

void Key_Generation()
{
	printf("Enter the value of p and q : ");//In this code, we have to select two prime number
	scanf("%d %d", &p, &q);
	n = p * q;//n = p*q
	int Pi = pi();//(p-1)*(q-1)
	Find_e(Pi);//Calculate e
	Find_d(Pi);//Calculate d
}

int pi()
{
	return (p - 1) * (q - 1);//¥õ(n)
}

int gcd(int n1, int n2)//Euclidean algrithm is used to find gcd.
{
	int tmp;
	while (1)//Repeat this loop until find gcd
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
	for (int i = 2; i < Pi; i++)//e must be smaller than ¥õ(n)
	{
		if (gcd(i, Pi) == 1)//e and ¥õ(n) are pair of relatively prime number
		{
			e = i;//If i satisfied the condition, terminate this loop and make value of e to i
			break;
		}
	}
}

void Find_d(int Pi)
{
	for (int i = 2; i < Pi; i++)
	{
		if (e * i % Pi == 1)//d is an inverse of e modulo ¥õ(n)
		{
			d = i;//If i satisfied the condition, terminate this loop and make value of d to i
			break;
		}
	}
}

void Encryption(char* Sen, int* M, int* EM, int* space)//Encryption
{
	int i, j, len = strlen(Sen), C, tmp;
	for (i = 0; i < len; i++)
	{
		if (M[i] == 32)
			space[i] = 1;
		tmp = M[i];
		tmp = tmp - 96;//Subtract 96 from tmp, because the ascii code of 'a' is 96
		C = 1;
		for (j = 0; j < e; j++)
		{
			C *= tmp;
			C %= n;
		}
		EM[i] = C + 96;//When loop finished, insert C+'a' to encrypted message array.
	}
	printf("Encrypted Sentence : ");
	for (i = 0; i < len; i++)
		printf("%c", EM[i]);//Show the encrypted message.
}

void Decryption(char* Sen, int* EM, int* DM, int* space)
{
	int i, j, len = strlen(Sen), M, tmp;
	for (i = 0; i < len; i++)
	{
		tmp = EM[i] - 96;//Subtract 96 from EM[i], because the ascii code of 'a' is 96
		M = 1;
		for (j = 0; j < d; j++)
		{
			M *= tmp;
			M %= n;
		}
		DM[i] = M + 96;//When loop finished, insert M + 'a' to decrypted message array.
	}
	printf("\nDecrypted Sentence : ");
	for (i = 0; i < len; i++)
	{
		if (space[i] == 1)
			printf(" ");
		else
			printf("%c", DM[i]);
	}//Show the decrypted message.
	printf("\n\n");
}
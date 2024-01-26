#include<stdio.h>
/*ras*/
long pow_(long i, long j, long k) {
	double l, temp, p = 1;
	for (temp = 0; temp < j; temp++) {
		p = (p * ((double)i));
		l = (long)(p / k); //소수점 삭제.
		p = p - (l * k);
	}
	return (long)p;
}
int encryption(int input, int e, int n) {
	int i = pow_(input, e, n);
	printf("입력받은 수의 rsa암호화 결과= %d\n", i);
	return i;
}
int Decryption(int input, int d, int n) {
	int i = pow_(input, d, n);
	printf("암호화된 수의 rsa복호화 결과= %d\n", i);
	return i;
}
int main() {
	int input;
	scanf("%d", &input);
	int p = 17, q = 11;
	int e = 7, d = 23, N = p * q;
	input = encryption(input, e, N);
	Decryption(input, d, N);
	return 0;
}
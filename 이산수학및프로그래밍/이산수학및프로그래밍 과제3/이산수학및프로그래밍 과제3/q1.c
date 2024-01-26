#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

/*3항 검색 알고리즘은 연속 분할을 통해 증가하는
정수 리스트에서 요소를 찾는다.
목록을 두 개의 하위 목록으로 분할하는 바이너리 검색과 대조적으로
크기가 같거나 가능한 한 같게 세 개의 하위 목록으로 나열하고
검색을 적절한 부분으로 제한한다. 의사 코드는 다음과 같습니다.
선택한 프로그래밍 언어를 사용하여 다음과 같은 의사코드를 구현합니다.
출력물의 스크린샷을 코드와 함께 첨부합니다.*/

/*
x : integer
a1, a2, ..., an : increasing integers

i = 1
j = n
while i<j-1
	l = floor to (i+j)/3
	u = floor to 2(i+j)/3
	if(x>au) then i = u+1
	else if (x>al) then
		i = l+1
		j = u
	else j = l
if x = a, then location = i
else if x = aj, then location = j
else location = 0
return location
(location is the subscript of the term equal to x (0 if not found)
*/

int tenary_search(int, int, int, int*);

int main()
{
	int i, j, x, * a;
	i = 1;
	printf("insert N : ");
	scanf("%d", &j); //j = MAX
	a = (int*)malloc(sizeof(int) * (j+1));
	for (int k = i; k <= j; k++)
		a[k] = k;
	scanf("%d", &x);//x>=1&&x<=MAX
	int location;
	location = tenary_search(i, j, x, a);
	if(x)
		printf("The location of x is : %d\n", location);
	else
		printf("The location is not found.\n");
	free(a);
	return 0;
}

int tenary_search(int i, int j, int x, int* a)
{
	int l, u, cnt = 0;
	while (i < (j - 1))
	{
		l = (2 * i + j) / 3;
		u = (2 * j + i) / 3;
		if (x > a[u])
			i = u + 1;
		else if (x > a[l])
		{
			i = l + 1;
			j = u;
		}
		else
			j = l;
	}
	if (x == a[i])
		return i;
	else if (x == a[j])
		return j;
	else
		return 0;//x is not found.
}
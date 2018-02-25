//1503077_四位拓海
//情報システムゼミ#3課題_bas-03-02.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define NO 10

//vc[]の各要素をdivisorで割った商と余りを別々の配列に格納
void division(const int vc[], int no, int divisor, int quot[], int rest[])
{
	int i;

	for (i = 0; i < no; i++) {
		quot[i] = vc[i] / divisor;
		rest[i] = vc[i] % divisor;
	}
}

//test
void test_division(void)
{
	int i, divisor;
	int vc[NO] = { 1,2,3,4,5,6,7,8,9,10 };
	int quot[NO], rest[NO];

	printf("割る値を入力してください。:"); scanf("%d", &divisor);

	division(vc, NO, divisor, quot, rest);

	for (i = 0; i < NO; i++) {
		printf("vc[%d]=%d  quot[%d]=%d  rest[%d]=%d  \n", i, vc[i], i, quot[i], i, rest[i]);
	}
}

//エントリポイント
void main()
{
	test_division();
}
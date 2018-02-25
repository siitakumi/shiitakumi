//1503077_四位拓海
//情報システムゼミ#2課題_bas-02-03.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#define NUM 100 //配列の要素数

//数列を配列に埋め込む
void fill_sequence(int s[], int size)
{
	for (int i = 0, j = -2; i < size; i++, j++) {
		if (i == 0) {
			s[i] = 1;
		}
		else if (i == 1) {
			s[i] = 2;
		}
		else {
			s[i] = s[i - 2] + pow(-1, j) * s[i - 1];
		}
	}
}

//test
void test_fill_sequence(void)
{
	int s[NUM];

	fill_sequence(s, NUM);

	for (int i = 0; i < NUM; i++) 
		printf("%d ", s[i]);
}

//エントリポイント
void main()
{
	test_fill_sequence();
}
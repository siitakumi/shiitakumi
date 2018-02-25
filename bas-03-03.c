//1503077_四位拓海
//情報システムゼミ#3課題_bas-03-03.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//静的変数を用いた足し込み演算
int tashikomi(int num) 
{
	static int sum;
	
	sum += num;

	return(sum);
}

//test
void test_tashikomi(void)
{
	printf("[%d]\n", tashikomi(5));
	printf("[%d]\n", tashikomi(3));
	printf("[%d]\n", tashikomi(10));
	printf("[%d]\n", tashikomi(-1));
}

//エントリポイント
void main()
{
	test_tashikomi();
}
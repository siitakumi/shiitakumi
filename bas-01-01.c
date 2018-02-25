//1503077_四位拓海
//情報システムゼミ#1課題_bas-01-01.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define START_NUM 1
#define FINISH_NUM 100

//仮引数が「3の倍数」か「3が付く数字」かの判定
void judge_with_three(int num)
{
	//3の倍数を検出
	if (num % 3 == 0) {
		printf("	%d*", num);
	}
	//1の位が3の数字を検出
	else if (num % 10 == 3) {
		printf("	%d*", num);
	}
	//2の位が3の数字を検出
	else if (29<num && num<40) {
		printf("	%d*", num);
	}
	else {
		printf("	%d", num);
	}
}

//3の倍数か3がつく数字か判定しながら、
//指定の値から値までを順に表示する関数
void prus_num(void)
{
	int i;
	for (i = START_NUM; i < FINISH_NUM; i++) {
		judge_with_three(i);
	}
}

//エントリポイント
void main() 
{
	prus_num();
	puts("\n");
}
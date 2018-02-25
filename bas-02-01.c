//1503077_四位拓海
//情報システムゼミ#2課題_bas-02-01.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//配列の中にある整数が存在するか調査(0オリジンから)
int search_from_array(int num, const int array[], int size)
{
	for (int i = 0; i < size; i++) {
		//numはarray[]の何番目かに存在したらその場所を早期return
		if (array[i] == num)  return i;
	}
	return -1; //存在しなかった
}

//test
void test_search_from_array(void)
{
	int array[] = { 23,0,-32,89,54 };
	int num, index;
	int size = sizeof(array) / sizeof(array[0]);

	puts("好きな整数を入力してください。"); scanf("%d", &num);

	index = search_from_array(num, array, size);

	if (index == -1) {
		printf("あなたが入力した整数%dは、配列arrayには存在しませんでした。", num);
	}
	else {
		printf("あなたが入力した整数%dは配列arrayの%d番目にありました。\n", num, index);
	}
}

//エントリポイント
void main()
{
	test_search_from_array();
}
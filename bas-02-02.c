//1503077_四位拓海
//情報システムゼミ#2課題_bas-02-02.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//配列に連続して存在する値は1個残してあとは0に
void same_num_to_zero(int array[], int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i; j++) {
			if (array[j] == array[i]) array[i] = 0;
		}
	}
}

//test
void test_same_num_to_zero(void)
{
	int array[] = { 3,52,28,32,52,99,28,3,3,71 };
	int size = sizeof(array) / sizeof(array[0]);

	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	puts("\n");

	same_num_to_zero(array, size); //arrayを書き換える

	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	puts("\n");
}

//エントリポイント
void main()
{
	test_same_num_to_zero();
}
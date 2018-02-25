//1503077_四位拓海
//情報システムゼミ#7課題_bas-07-02.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> //for exit()

//ファイルをオープン＆エラーチェック＆ファイルへのポインタ格納
FILE *fopen_and_check(const char *fname, const char *mode)
{
	FILE *fp;
	fp = fopen(fname, mode);

	if (fp == NULL) {
		printf("Can't open file:[%s].\n", fname);
		exit(1);
	}
	return(fp);
}

//計算する
int calculation(int left_section, const char operation, int right_section)
{
	int ans;

	switch (operation) {
	case '+':
		ans = left_section + right_section;
		break;
	case'-':
		ans = left_section - right_section;
		break;
	case '*':
		ans = left_section * right_section;
		break;
	case'/':
		//分母が0の時エラー処理
		if (right_section == 0) {
			printf("Error! Divide by 0 was done.\n");
			exit(1);
		}
		ans = left_section / right_section;
		break;
	default:
		//*/-+いずれでもない時のエラー処理
		printf("Error! Can't calculate, Operator error.\n");
		exit(1);
	}
	return ans;
}

//ファイルの中にある2項式を計算、出力
void calculate_four_arithmetic_operations_in_file(FILE *fp_r)
{
	int stat;
	int ans = 0;
	int left_section, right_section;
	char operation;

	for (;;) {
		stat = fscanf(fp_r, "%d %c %d", &left_section, &operation, &right_section);
		if (stat == EOF) {
			break;
		}
		ans = calculation(left_section, operation, right_section);
		printf("%d\n", ans);
	}
}

//test
void test_calculate_four_arithmetic_operations_in_file(void)
{
	FILE *fp_r;

	fp_r = fopen_and_check("keisan.txt", "r");

	calculate_four_arithmetic_operations_in_file(fp_r);

	fclose(fp_r);

	printf("正常に終了しました。");
}

//エントリポイント
void main()
{
	test_calculate_four_arithmetic_operations_in_file();
}
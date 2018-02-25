//1503077_四位拓海
//情報システムゼミ#4課題_bas-04-01.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//空白を除いた文字列strの長さを返す関数
int strlen_without_spase(const char str[])
{
	int i, strlen;
	int tmp = 0;

	for (i = 0; str[i] != '\0'; i++){
		if (str[i] != ' ') tmp++;
	}

	strlen = tmp;

	return(strlen);
}

//test
void test_strlen_without_spase(void)
{
	char str1[] = "foo";
	char str2[] = "foo bar";
	char str3[] = "foo  bar baz";

	printf("%s: %d\n", str1, strlen_without_spase(str1));
	printf("%s: %d\n", str2, strlen_without_spase(str2));
	printf("%s: %d\n", str3, strlen_without_spase(str3));
}

//エントリポイント
void main()
{
	test_strlen_without_spase();
}

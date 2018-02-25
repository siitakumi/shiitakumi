//1503077_四位拓海
//情報システムゼミ#4課題_bas-04-02.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//文字列src[]の中の連続した文字を1文字にまとめ、dest[]に書き込む
void str_squeeze(char dest[], const char src[])
{
	int i,seqence_num = 0;

	//連続した文字は最後の文字のみ埋め込む
	for (i = 0; src[i] != '\0';i++) {
		if (src[i + 1] != src[i]) {
			dest[seqence_num] = src[i];
			seqence_num++;
		}
	}
	//最後にナル文字を埋め込む
	dest[seqence_num] = '\0';
}

//test
void test_str_squeeze(void)
{
	int i;
	char str1[] = "aabbbccddddeffgghiii";
	char str2[30];

	str_squeeze(str2, str1);

	//str1出力
	for (i = 0; str1[i] != '\0'; i++) {
		printf("%c", str1[i]);
	}
	puts("\n");

	//str2出力
	for (i = 0; str2[i]!='\0'; i++) {
		printf("%c", str2[i]);
	}
	puts("\n");
}

//エントリポイント
void main()
{
	test_str_squeeze();
}

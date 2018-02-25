//1503077_四位拓海
//情報システムゼミ#5課題_bas-05-01.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//混ぜこぜ関数
void str_mazekoze(char *s3, char *s1, char *s2)
{
	//[継続条件]s1、s2どちらかが終端に未到達
	while (*s1 || *s2)
	{
		//s1が終端に到達していない
		if (*s1)*s3++ = *s1++;

		//s2が終端に到達していない
		if (*s2)*s3++ = *s2++;
	}
	*s3 = '\0';
}

//test
void test_str_mazekoze(void)
{
	char str1[] = "aaaaa";
	char str2[] = "bbb";
	char str3[20];
	str_mazekoze(str3, str1, str2);
	printf("str1: [%s]\n", str1);
	printf("str2: [%s]\n", str2);
	printf("str3: [%s]\n", str3);

	char str4[] = "shiitakumi";
	char str5[] = "kujipon";
	char str6[20];
	str_mazekoze(str6, str4, str5);
	printf("str4: [%s]\n", str4);
	printf("str5: [%s]\n", str5);
	printf("str6: [%s]\n", str6);

	char str7[] = " 114514";
	char str8[] = "yaranaika ";
	char str9[20];
	str_mazekoze(str9, str7, str8);
	printf("str7: [%s]\n", str7);
	printf("str8: [%s]\n", str8);
	printf("str9: [%s]\n", str9);

}

//エントリポイント
void main()
{
	test_str_mazekoze();
}

//1503077_四位拓海
//情報システムゼミ#5課題_bas-05-02.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//アドレスとドメインをそれぞれ別の文字列にコピー
void split_mail_address(char *name, char *domain, const char *address)
{
	for (;;){
		switch (*name++ = *address++)
		{
		case'@': name[-1] = '\0';
			strcpy(domain, address);
			return;
		
		case'\0':*domain = '\0';
			return;
		}
	}
}

//test
void test_split_mail_address(void)
{
	char addr[] = "114514@gmail.com";
	char str1[20];
	char str2[20];

	split_mail_address(str1, str2, addr);

	printf("E-mail : [%s]\n", addr);
	printf("host名 : [%s]\n", str1);
	printf("dmain名: [%s]\n", str2);
}

//エントリポイント
void main()
{
	test_split_mail_address();
}

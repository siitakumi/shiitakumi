//1503077_四位拓海
//情報システムゼミ#8課題_bas-08-01.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>	//for exit(),EXIT_FAILURE,fgets()
#include<string.h>	//for strlen(),strcmp(),strcpy()
#include<ctype.h>	//for isalnum()
#define STR_MAX (256+1)	//1行の最大文字（+1はナル文字）
#define CONFIG_FILE "config.txt"
#define ROW 10 //読みこめる設定項目は10個(行)まで

typedef struct {
	char conf_name[100];	//設定項目名
	int conf_num;			//数値（負数OK）
}conf_fdata;

//ファイルオープン&エラーチェック
FILE *fopen_and_check(const char fname[], const char mode[])
{
	FILE *fp;
	if ((fp = fopen(fname, mode)) == NULL) {
		printf("Error! File can't open.[%s]\n", fname);
		exit(EXIT_FAILURE);
	}
	else {
		printf("File opened.[%s]\n", fname);
	}
	return(fp);
}

//fdata構造体の初期化
void clear_struct_of_setteing(conf_fdata fdata[], int size)
{
	int i;

	for (i = 0; i < size; i++) {
		strcpy(fdata[i].conf_name,"NULL");
		fdata[i].conf_num = -999;
	}
}

//設定項目数制限チェック(10行まで)
int over_row_check(int fdata_now, int row)
{
	return(fdata_now > row);
}

//read_config_file
void read_config_file(char config_fname[],conf_fdata fdata[],int size)
{
	FILE *config_fp;
	char str_buf[STR_MAX];
	int fdata_now = 0;
	int line_num = 0;

	config_fp = fopen_and_check(config_fname, "r");

	while (fgets(str_buf, STR_MAX, config_fp) != NULL)
	{
		size_t str_buf_len = strlen(str_buf);

		//行頭にスペースがあってはいけない
		if (str_buf[0] == ' ') {
			puts("syntax error!\n");
			printf("[%d]line of setting aitem is ploblem.\n", fdata_now);
			exit(EXIT_FAILURE);
		}
		//空行、#から始まる、2文字未満の行は（continue文によって）無視
		else if (str_buf_len < 2 || str_buf[0] == '#' || str_buf[0] == '\n') {
			printf("%s", str_buf);
			line_num++;
			continue;
		}
		//読み込んだ個数は2個か
		else if (sscanf(str_buf, "%[a-zA-Z0-9_]:%*[ ]%d", fdata[fdata_now].conf_name, &fdata[fdata_now].conf_num) != 2) {
			puts("syntax error!\n");
			printf("[%d]line of setting aitem is ploblem.\n", fdata_now);
			exit(EXIT_FAILURE);
		}
		//格納
		else if (sscanf(str_buf, "%[a-zA-Z0-9_]:%*[ ]%d", fdata[fdata_now].conf_name, &fdata[fdata_now].conf_num) == 2) {
			printf("[%s]:[%d]\n", fdata[fdata_now].conf_name, fdata[fdata_now].conf_num);

			fdata_now++;
			line_num++;
		}

		//設定項目数が指定より多いか
		if (over_row_check(fdata_now, ROW)) {
			puts("Error!");
			puts("There are more than 10 setteing items.\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("\n設定項目数[%d]個/[%s]%d行\n\n", fdata_now, CONFIG_FILE, line_num);

	fclose(config_fp);
}

//設定項目に対応する値を検索
int search_config(char search_conf_name[], conf_fdata fdata[], int size)
{
	int i;

	for (i = 0; i <= size; i++) {
		//一致したらそれに対応する数値を返す
		if (fdata[i].conf_num != -999 && strcmp(search_conf_name, fdata[i].conf_name) == 0) {
			return(fdata[i].conf_num);
		}
	}
	//ここまできたら入力が誤っていると判断
	printf("Search error!\n");
	printf("The setting item name does'nt apply.\n");
	exit(EXIT_FAILURE);
}

//test
void test_read_config_file(void)
{
	conf_fdata fdata[ROW];
	char search_conf_name[100];
	int val = 0;

	//設定項目を格納する配列を初期化する
	clear_struct_of_setteing(fdata, ROW);

	//読み込む
	read_config_file(CONFIG_FILE, fdata, ROW);

	//参照（検索）
	printf("参照したい値の設定項目名を入力してください。>>");
	scanf("%s", search_conf_name);
	val = search_config(search_conf_name, fdata, ROW);
	printf("[%d]\n", val);
}

//エントリポイント
void main()
{
	test_read_config_file();
}
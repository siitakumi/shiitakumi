//1503077_�l�ʑ�C
//���V�X�e���[�~#8�ۑ�_bas-08-01.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>	//for exit(),EXIT_FAILURE,fgets()
#include<string.h>	//for strlen(),strcmp(),strcpy()
#include<ctype.h>	//for isalnum()
#define STR_MAX (256+1)	//1�s�̍ő啶���i+1�̓i�������j
#define CONFIG_FILE "config.txt"
#define ROW 10 //�ǂ݂��߂�ݒ荀�ڂ�10��(�s)�܂�

typedef struct {
	char conf_name[100];	//�ݒ荀�ږ�
	int conf_num;			//���l�i����OK�j
}conf_fdata;

//�t�@�C���I�[�v��&�G���[�`�F�b�N
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

//fdata�\���̂̏�����
void clear_struct_of_setteing(conf_fdata fdata[], int size)
{
	int i;

	for (i = 0; i < size; i++) {
		strcpy(fdata[i].conf_name,"NULL");
		fdata[i].conf_num = -999;
	}
}

//�ݒ荀�ڐ������`�F�b�N(10�s�܂�)
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

		//�s���ɃX�y�[�X�������Ă͂����Ȃ�
		if (str_buf[0] == ' ') {
			puts("syntax error!\n");
			printf("[%d]line of setting aitem is ploblem.\n", fdata_now);
			exit(EXIT_FAILURE);
		}
		//��s�A#����n�܂�A2���������̍s�́icontinue���ɂ���āj����
		else if (str_buf_len < 2 || str_buf[0] == '#' || str_buf[0] == '\n') {
			printf("%s", str_buf);
			line_num++;
			continue;
		}
		//�ǂݍ��񂾌���2��
		else if (sscanf(str_buf, "%[a-zA-Z0-9_]:%*[ ]%d", fdata[fdata_now].conf_name, &fdata[fdata_now].conf_num) != 2) {
			puts("syntax error!\n");
			printf("[%d]line of setting aitem is ploblem.\n", fdata_now);
			exit(EXIT_FAILURE);
		}
		//�i�[
		else if (sscanf(str_buf, "%[a-zA-Z0-9_]:%*[ ]%d", fdata[fdata_now].conf_name, &fdata[fdata_now].conf_num) == 2) {
			printf("[%s]:[%d]\n", fdata[fdata_now].conf_name, fdata[fdata_now].conf_num);

			fdata_now++;
			line_num++;
		}

		//�ݒ荀�ڐ����w���葽����
		if (over_row_check(fdata_now, ROW)) {
			puts("Error!");
			puts("There are more than 10 setteing items.\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("\n�ݒ荀�ڐ�[%d]��/[%s]%d�s\n\n", fdata_now, CONFIG_FILE, line_num);

	fclose(config_fp);
}

//�ݒ荀�ڂɑΉ�����l������
int search_config(char search_conf_name[], conf_fdata fdata[], int size)
{
	int i;

	for (i = 0; i <= size; i++) {
		//��v�����炻��ɑΉ����鐔�l��Ԃ�
		if (fdata[i].conf_num != -999 && strcmp(search_conf_name, fdata[i].conf_name) == 0) {
			return(fdata[i].conf_num);
		}
	}
	//�����܂ł�������͂�����Ă���Ɣ��f
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

	//�ݒ荀�ڂ��i�[����z�������������
	clear_struct_of_setteing(fdata, ROW);

	//�ǂݍ���
	read_config_file(CONFIG_FILE, fdata, ROW);

	//�Q�Ɓi�����j
	printf("�Q�Ƃ������l�̐ݒ荀�ږ�����͂��Ă��������B>>");
	scanf("%s", search_conf_name);
	val = search_config(search_conf_name, fdata, ROW);
	printf("[%d]\n", val);
}

//�G���g���|�C���g
void main()
{
	test_read_config_file();
}
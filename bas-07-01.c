//1503077_�l�ʑ�C
//���V�X�e���[�~#7�ۑ�_bas-07-01.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>  //for strlen()
#include<stdlib.h>	//for exit(),EXIT_FAILURE 

#define READFILE1_1_NAME "test1_file1_zemi_kadai7.txt"
#define READFILE1_2_NAME "test1_file2_zemi_kadai7.txt"
#define WRITEFILE1_NAME "test1_file_of_write_zemi_kadai7.txt"

#define READFILE2_1_NAME "test2_file1_zemi_kadai7.txt"
#define READFILE2_2_NAME "test2_file2_zemi_kadai7.txt"
#define WRITEFILE2_NAME "test2_file_of_write_zemi_kadai7.txt"

#define READFILE3_1_NAME "test3_file1_zemi_kadai7.txt"
#define READFILE3_2_NAME "test3_file2_zemi_kadai7.txt"
#define WRITEFILE3_NAME "test3_file_of_write_zemi_kadai7.txt"

#define READFILE4_1_NAME "test4_file1_zemi_kadai7.txt"
#define READFILE4_2_NAME "test4_file2_zemi_kadai7.txt"
#define WRITEFILE4_NAME "test4_file_of_write_zemi_kadai7.txt"

#define READFILE5_1_NAME "test5_file1_zemi_kadai7.txt"
#define READFILE5_2_NAME "test5_file2_zemi_kadai7.txt"
#define WRITEFILE5_NAME "test5_file_of_write_zemi_kadai7.txt"

#define READFILE6_1_NAME "test6_file1_zemi_kadai7.txt"
#define READFILE6_2_NAME "test6_file2_zemi_kadai7.txt"
#define WRITEFILE6_NAME "test6_file_of_write_zemi_kadai7.txt"

#define GYOU_MAX 256

//�I�[�v�����G���[�`�F�b�N���t�@�C���ւ̃|�C���^�i�[
FILE *fopen_and_check(const char *fname, const char *mode)
{
	FILE *fp;
	fp = fopen(fname, mode);

	if (fp == NULL) {
		printf("Can't open file:[%s].\n", fname);
		exit(EXIT_FAILURE);
	}
	return(fp);
}

//�ǂݎ������s���t�@�C���ɏ����o������
char *read_print(FILE *fp_r, FILE *fp_w, char *line_unit)
{
	char *stat;

	stat = fgets(line_unit, GYOU_MAX, fp_r);
	if (stat != NULL) {
		fprintf(fp_w, "%s", line_unit);
		//printf("%s", line_unit);
	}
	return(stat);
}

//�s�P�ʂō����������t�@�C���ɏ����o��
void mazekoze_write_by_line_unit(FILE *fp1_r, FILE *fp2_r, FILE *fp_w)
{
	char *stat1;
	char *stat2;
	char line_unit[GYOU_MAX + 1 + 1];//�I�[�����A���s����

	do {
		stat1 = read_print(fp1_r, fp_w, line_unit);
		stat2 = read_print(fp2_r, fp_w, line_unit);
	} while (stat1 != NULL && stat2 != NULL);

	//�Ώۂ̂�����߂��c���Ă�
	if (stat1 != NULL) {
		do {
			stat1 = read_print(fp1_r, fp_w, line_unit);
		} while (stat1 != NULL);
	}

	//�Ώۂ̂�����߂��c���Ă�
	if (stat2 != NULL) {
		do {
			stat2 = read_print(fp2_r, fp_w, line_unit);
		} while (stat2 != NULL);
	}
}

//test
void test_mazekoze_by_line_unit(void)
{
	FILE *fp1_r;
	FILE *fp2_r;
	FILE *fp_w;
	
	//test1[f1 > f2]
	fp1_r = fopen_and_check(READFILE1_1_NAME, "r");
	fp2_r = fopen_and_check(READFILE1_2_NAME, "r");
	fp_w = fopen_and_check(WRITEFILE1_NAME, "w");

	mazekoze_write_by_line_unit(fp1_r, fp2_r, fp_w);

	fclose(fp1_r);
	fclose(fp2_r);
	fclose(fp_w);

	printf("[test1]����ɏ����ł��܂����B\n");

	//test2[f1 < f2]
	fp1_r = fopen_and_check(READFILE2_1_NAME, "r");
	fp2_r = fopen_and_check(READFILE2_2_NAME, "r");
	fp_w = fopen_and_check(WRITEFILE2_NAME, "w");

	mazekoze_write_by_line_unit(fp1_r, fp2_r, fp_w);

	fclose(fp1_r);
	fclose(fp2_r);
	fclose(fp_w);

	printf("[test2]����ɏ����ł��܂����B\n");

	//test3[f1 == f2]
	fp1_r = fopen_and_check(READFILE3_1_NAME, "r");
	fp2_r = fopen_and_check(READFILE3_2_NAME, "r");
	fp_w = fopen_and_check(WRITEFILE3_NAME, "w");

	mazekoze_write_by_line_unit(fp1_r, fp2_r, fp_w);

	fclose(fp1_r);
	fclose(fp2_r);
	fclose(fp_w);

	printf("[test3]����ɏ����ł��܂����B\n");

	//test4[f1 is empty]
	//�I�[�v�����G���[�`�F�b�N���t�@�C���ւ̃|�C���^�i�[
	fp1_r = fopen_and_check(READFILE4_1_NAME, "r");
	fp2_r = fopen_and_check(READFILE4_2_NAME, "r");
	fp_w = fopen_and_check(WRITEFILE4_NAME, "w");

	mazekoze_write_by_line_unit(fp1_r, fp2_r, fp_w);

	fclose(fp1_r);
	fclose(fp2_r);
	fclose(fp_w);

	printf("[test4]����ɏ����ł��܂����B\n");

	//test5[f2 is empty]
	fp1_r = fopen_and_check(READFILE5_1_NAME, "r");
	fp2_r = fopen_and_check(READFILE5_2_NAME, "r");
	fp_w = fopen_and_check(WRITEFILE5_NAME, "w");

	mazekoze_write_by_line_unit(fp1_r, fp2_r, fp_w);

	fclose(fp1_r);
	fclose(fp2_r);
	fclose(fp_w);

	printf("[test5]����ɏ����ł��܂����B\n");

	//test6[both empty]
	fp1_r = fopen_and_check(READFILE6_1_NAME, "r");
	fp2_r = fopen_and_check(READFILE6_2_NAME, "r");
	fp_w = fopen_and_check(WRITEFILE6_NAME, "w");

	mazekoze_write_by_line_unit(fp1_r, fp2_r, fp_w);

	fclose(fp1_r);
	fclose(fp2_r);
	fclose(fp_w);

	printf("[test6]����ɏ����ł��܂����B\n");
}

//�G���g���|�C���g
void main()
{
	test_mazekoze_by_line_unit();
}
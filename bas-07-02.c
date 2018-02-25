//1503077_�l�ʑ�C
//���V�X�e���[�~#7�ۑ�_bas-07-02.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> //for exit()

//�t�@�C�����I�[�v�����G���[�`�F�b�N���t�@�C���ւ̃|�C���^�i�[
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

//�v�Z����
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
		//���ꂪ0�̎��G���[����
		if (right_section == 0) {
			printf("Error! Divide by 0 was done.\n");
			exit(1);
		}
		ans = left_section / right_section;
		break;
	default:
		//*/-+������ł��Ȃ����̃G���[����
		printf("Error! Can't calculate, Operator error.\n");
		exit(1);
	}
	return ans;
}

//�t�@�C���̒��ɂ���2�������v�Z�A�o��
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

	printf("����ɏI�����܂����B");
}

//�G���g���|�C���g
void main()
{
	test_calculate_four_arithmetic_operations_in_file();
}
//1503077_四位拓海
//情報システムゼミ#1課題_bas-01-02.c【再提出】
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MOTHER_NUMBER 999 //分母の最大値

//円周率の計算
double calculation_pai(double mother_number)
{
	double tmp = 0.0;
	double pai = 0.0;

	for (int i=1, hugou=1; i<=mother_number; i+=2, hugou=-hugou){
		tmp += hugou * 1.0 / (double)i;
	}
	pai = 4.0 * tmp;

	return pai;
}

//エントリポイント
void main()
{
	printf("π=%f", calculation_pai(MOTHER_NUMBER));
}
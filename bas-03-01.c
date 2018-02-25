//1503077_四位拓海
//情報システムゼミ#3課題_bas-03-01.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h> //cos()
#define PI 3.14159265358979

//階乗関数
double kaijou(double x)
{
	double tmp = 1.0;
	double ans;

	for (int i = 1; i <= x; i++) {
		tmp *= i;
	}
	ans = tmp;
	return(ans);
}

//cos()
double my_cos(double kakudo)
{
	double cos_ans = 0.0;
	double tmp = 0.0;
	int n_max = 9;

	for (int i = 0; i < n_max; i++) {
		tmp += pow(-1.0, (double)i) / kaijou(2.0 * i) * pow(kakudo, 2.0 * i);
	}
	cos_ans = tmp;

	return (cos_ans);
}

//test
void test_my_cos()
{
	double rad, cs, ans;
	//30°毎に表示
	for (int deg = 0; deg <= 360; deg += 30) {
		rad = deg * PI / 180.0; //ラジアン変換
		cs = cos(rad);			//比較のため、ライブラリのcos()を使う
		ans = my_cos(rad);		//my_cos()
		printf("%3d  %3.3f  %3.3f  %3.3f\n", deg, rad, cs, ans);
	}
}

//エントリポイント
void main()
{
	test_my_cos();
}
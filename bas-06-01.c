//1503077_四位拓海
//情報システムゼミ#6課題_bas-06-01.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h> //strcmp()
#include<stdlib.h> //qsort()
#define NAMELEN 30

typedef struct
{
	char name[NAMELEN];	//商品名
	int unit_price;		//単価
	int quantity;		//数量
}receipt_t;

//構造体メンバを読み込み、比較する関数
//voidへのポインタp1とp2を比較対象のreceipt_tへのポインタにキャスト
//アロー演算子を使ってメンバを読み込み、差を計算する
//正、負のいずれかの値を返す（0は返却しないようにする）
int cmp_member_of_structure(const void *p1, const void *p2)
{
	//p1とp2が指す単価を比較する
	int vlu = (((receipt_t*)p1)->unit_price) - (((receipt_t*)p2)->unit_price);

	//単価が同じ場合、p1とp2が指す購入個数の順にソートするようにする
	if (vlu == 0) {
		vlu = (((receipt_t*)p1)->quantity) - (((receipt_t*)p2)->quantity);
	}

	//それでも同じ場合、p1とp2が指す商品名の文字列の大小関係でソートするようにする
	if (vlu == 0) {
		vlu = strcmp((((receipt_t*)p1)->name), (((receipt_t*)p2)->name));
	}
	return vlu;
}

//test
void test_sort_by_unit_price(void)
{
	int i, sum;
	int tmp = 0;
	int multi_price = 0; //単価と個数の積

	//静的埋め込みで初期化
	receipt_t receipt1[] = {
		{ "大きな焼きおにぎり",279,2 },
		{ "ごつ盛りソース焼きそば",99,1 },
		{ "イチオシキムチ",159,1 },
		{ "アセロラビタミンC",99,1 },
		{ "綾鷹にごりほのかペコらく",119,1 },
		{ "くめ納豆秘伝金印ミニ3",69,1 },
		{ "生おろしわさび",59,2 },
		{ "富士山天然水",57,1 },
		{ "レジ袋3円",3,1 },
		{ "おーいお茶",137,1 },
		{ "ハイランドハニーバナナ",199,1 },
		{ "ｼｸﾞﾉ028青",120,1 }
	};

	//配列要素の個数
	int size = sizeof receipt1 / sizeof(receipt_t);

	printf("四位が最後に入手したレシートの商品一覧\n\n");
	for (i = 0; i < size; i++) {
		printf("%4d円 [%s  %1d個]\n", receipt1[i].unit_price, receipt1[i].name, receipt1[i].quantity);
	}
	puts("\n");

	//この一覧を単価順にソート
	//もし価格が同じ場合は購入個数順にソート
	//もしそれも同じ場合は商品名の文字列の大小関係でソート
	qsort(receipt1, size, sizeof(receipt_t), cmp_member_of_structure);

	printf("四位が最後に入手したレシートの商品を単価順にソート\n\n");
	printf("  [単価] [個数] [価格] [商品名]\n");
	for (i = 0; i < size; i++) {
		//単価*個数の価格も計算し、合計値も表示しておく
		multi_price = receipt1[i].unit_price * receipt1[i].quantity;
		tmp += multi_price;

		printf("%4d円   X   %d = %4d %s\n", receipt1[i].unit_price, receipt1[i].quantity, multi_price, receipt1[i].name);
	}
	sum = tmp;
	printf("\n合計[%4d円]\n", sum);
	puts("\n");
}

//test_sum_price

//エントリポイント
void main()
{
	test_sort_by_unit_price();
}

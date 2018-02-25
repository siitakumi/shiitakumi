//1503077_四位拓海
//情報システムゼミ#5課題_bas-05-03.c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//整数keta_suu中のセットされたビット数を返す
int count_bits(unsigned keta_suu)
{
	int bits = 0;
	while (keta_suu) {
		if (keta_suu & 1U)bits++;
		keta_suu >>= 1;
	}
	return bits;
}

//unsigned型のビット数を返す
int int_bits(void)
{
	return count_bits(~0U);
}

//unsigned型のビット内容を表示
void print_bits(unsigned keta_suu)
{
	int i;
	for (i = int_bits() - 1; i >= 0; i--) {
		putchar(((keta_suu >> i) & 1U) ? '1' : '0');
	}
}

//IPアドレスの10進変換
unsigned long ipadr_to_seisuu(const char *ip)
{
	unsigned long one_oc, two_oc, three_oc, four_oc;
	unsigned long ans;

	//パースする
	sscanf(ip, "%d.%d.%d.%d", &one_oc, &two_oc, &three_oc, &four_oc);

	//それぞれシフト演算して足し込む
	ans = (one_oc << 24) + (two_oc << 16) + (three_oc << 8) + four_oc;

	//ビット標記の確認
	printf("\n4オクテッド  ="); print_bits(one_oc);
	printf("\n左シフト     ="); print_bits(one_oc << 24);
	printf("\n3オクテッド  ="); print_bits(two_oc);
	printf("\n左シフト     ="); print_bits(two_oc << 16);
	printf("\n2オクテッド  ="); print_bits(three_oc);
	printf("\n左シフト     ="); print_bits(three_oc << 8);
	printf("\n1オクテッド  ="); print_bits(four_oc);
	
	printf("\n2進IPアドレス="); print_bits(ans);

	putchar('\n');
	putchar('\n');

	return ans;
}

//test
void test_ipadr_to_seisuu(void)
{
	char ip_addr1[] = "192.168.0.1";
	printf("[%s]\n", ip_addr1);

	char ip_addr2[] = "172.22.40.34";
	printf("[%s]\n", ip_addr2);

	char ip_addr3[] = "255.255.255.222";
	printf("[%s]\n", ip_addr3);

	char ip_addr4[] = "045.40.32.001";
	printf("[%s]\n", ip_addr4);

	printf("10進変換 = [%u]\n", ipadr_to_seisuu(ip_addr1));
	printf("    正解 = [3232235521]\n");

	printf("10進変換 = [%u]\n", ipadr_to_seisuu(ip_addr2));
	printf("    正解 = [2887133218]\n");

	printf("10進変換 = [%u]\n", ipadr_to_seisuu(ip_addr3));
	printf("    正解 = [4294967262]\n");

	printf("10進変換 = [%u]\n", ipadr_to_seisuu(ip_addr4));
	printf("    正解 = [757604353]\n");
}

//エントリポイント
void main()
{
	test_ipadr_to_seisuu();
}

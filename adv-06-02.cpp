//情報システムゼミ#14
//1503077_四位拓海
//adv-06-02.cpp
#include<stdlib.h> //for exit()
#include<iostream>
#include<string> //for std::string

struct gakusei {
	std::string gakuseki;
	std::string name;
};

//代入
void substitution(std::string info)
{
	int i, j;
	struct gakusei gakuseis;
	
	//学籍番号のみをメンバgakusekiに格納
	for (i = 0;info[i]!=',';i++){
		gakuseis.gakuseki= gakuseis.gakuseki + info[i];
		
		if (info[i] == '\0') {
			printf("不正な文字列です。");
			exit(EXIT_FAILURE);
		}
	}

	//名前のみをメンバnameに格納
	for (j = i + 1; info[j] != '\0'; j++) {
		gakuseis.name = gakuseis.name + info[j];
	}
}

//エントリポイント
void main()
{
	std::string info;
	
	std::cout << "学籍番号と名前を,で区切りながら入力してください。";
	std::cin >> info;

	substitution(info);
}

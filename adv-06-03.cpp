//情報システムゼミ#14
//1503077_四位拓海
//adv-06-03.cpp
#include<stdlib.h> //for exit()
#include<iostream>
#include<string> //for std::string
#include<vector> //for std::vector

struct gakusei {
	std::string gakuseki;
	std::string name;
};

//代入
void substitution(std::string info)
{
	int i, j;
	std::vector<struct gakusei>gakuseis;
	struct gakusei tmp;

	//学籍番号のみをメンバgakusekiに格納
	for (i = 0;info[i]!=',';i++){
		tmp.gakuseki= tmp.gakuseki + info[i];
		
		if (info[i] == '\0') {
			printf("不正な文字列です。");
			exit(EXIT_FAILURE);
		}
	}

	//名前のみをメンバnameに格納
	for (j = i + 1; info[j] != '\0'; j++) {
		tmp.name = tmp.name + info[j];
	}
	
	//コピーしてデータを格納
	gakuseis.push_back(tmp);
}

//エントリポイント
void main()
{
	std::string info;
	
	std::cout << "学籍番号と名前を,で区切りながら入力してください。"<<std::endl;
	std::cout << "終了：@+Enterキー" << std::endl;

	for (;;) {
		
		std::cin >> info;

		if (info == "@") {
			break;
		}

		substitution(info);
	}
}
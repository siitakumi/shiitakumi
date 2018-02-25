//情報システムゼミ#14-1
//1503077_四位拓海
//adv-06-01.cpp
#include<iostream>
#include<string> //for std::string

//一文字ずつ表示する
void print_each(std::string name)
{
	std::string str_growth;

	for (int i = 0; i < name.size(); i++) {
		str_growth = str_growth + name[i];
		std::cout << str_growth << std::endl;
	}
}

//エントリポイント
void main()
{
	std::string name;
	std::cout << "名前を入れてください。>";
	std::cin >> name;

	print_each(name);
}

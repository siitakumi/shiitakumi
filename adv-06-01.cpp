//���V�X�e���[�~#14-1
//1503077_�l�ʑ�C
//adv-06-01.cpp
#include<iostream>
#include<string> //for std::string

//�ꕶ�����\������
void print_each(std::string name)
{
	std::string str_growth;

	for (int i = 0; i < name.size(); i++) {
		str_growth = str_growth + name[i];
		std::cout << str_growth << std::endl;
	}
}

//�G���g���|�C���g
void main()
{
	std::string name;
	std::cout << "���O�����Ă��������B>";
	std::cin >> name;

	print_each(name);
}

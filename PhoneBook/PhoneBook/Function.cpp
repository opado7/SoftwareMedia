#include <fstream>
#include <string>
#include <iostream>
#include "Phonebook.h"

using namespace std;

void Save_array(string array) //���ڿ��� �����Ϳ� ����
{
	fstream file("save.dat", ios::out);

	if (file)
	{
		file << array;
		cout << "���� �Ϸ�" << '\n';
	}
	else { cout << "�����߻�" << '\n'; }

	file.close();
	return;
}

bool Atleast_one() //�ּ� �Ѱ� �̻��� ����ó�� ����Ǿ��ִ��� �˻�
{
	fstream file("save.dat");
	file.seekg(0, ios::end);

	if (file.tellg() == 0) return false;
	return true;
}

string Return_list() //������ ��ü�� ���ڿ��� �־� ����
{
	fstream file("save.dat", ios::in);
	string phone_list;

	file.seekg(0, ios::end);
	int size = file.tellg();
	phone_list.resize(size);
	file.seekg(0, ios::beg);
	file.read(&phone_list[0], size);

	return phone_list;
}

int Return_startindex(int index) //�˻������ � �� �߰��� ������� �� �� ��ü ����� ���� ���� ù �ε����� ã�� �Լ�
{
	string array = Return_list();
	while (true)
	{
		if (index <= 0) break;
		if (array[index] == '\n') return index + 1;
		index--;
	}
	return index;
}
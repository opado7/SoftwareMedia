#include <fstream>
#include <string>
#include <iostream>
#include "Phonebook.h"

using namespace std;

void Save_array(string array) //문자열을 데이터에 저장
{
	fstream file("save.dat", ios::out);

	if (file)
	{
		file << array;
		cout << "저장 완료" << '\n';
	}
	else { cout << "오류발생" << '\n'; }

	file.close();
	return;
}

bool Atleast_one() //최소 한개 이상의 연락처가 저장되어있는지 검사
{
	fstream file("save.dat");
	file.seekg(0, ios::end);

	if (file.tellg() == 0) return false;
	return true;
}

string Return_list() //데이터 전체를 문자열에 넣어 리턴
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

int Return_startindex(int index) //검색결과가 어떤 줄 중간에 있을경우 그 줄 전체 출력을 위해 줄의 첫 인덱스를 찾는 함수
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
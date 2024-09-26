#include <fstream>
#include <string>
#include <iostream>
#include "Phonebook.h"

using namespace std;

bool Atleast_one();
void Save_array(string array);
string Return_list();
int Return_startindex(int index);

void Information::Start_menu()
{
	int choice = 0;

	while (true) {
		cout << "----------------------------------------------------" << '\n';
		cout << "1. 새로운 전화번호 추가" << '\n';
		cout << "2. 기존 전화번호 검색" << '\n';
		cout << "3. 현재 전화번호부 전체 출력" << '\n';
		cout << "4. 전화번호 수정" << '\n';
		cout << "5. 프로그램 종료" << '\n';
		cout << "----------------------------------------------------" << '\n';
		cin >> choice;

		switch (choice)
		{
		case 1:
			Add_Phone();
			break;
		case 2:
			Search();
			break;
		case 3:
			Print_all();
			break;
		case 4:
			Edit_number();
			break;
		case 5:
			std::cout << "프로그램을 종료합니다" << '\n';
			return;
		default:
			std::cout << "잘못 입력하셨습니다." << '\n';
			break;
		}
	}
}

void Information::Add_Phone()
{
	fstream file("save.dat", ios::app);
	string name, phone_num;

	cout << "이름과 전화번호를 띄어쓰기로 구분하여 입력해주십시오." << '\n';
	cin >> name >> phone_num;
	cout << '\n';

	if (file) {
		file << name << " " << phone_num << '\n';
		cout << "성공적으로 추가되었습니다." << "\n";
	}
	else { cout << "오류가 발생하였습니다." << '\n'; return; }

	file.close();

}

void Information::Search()
{
	fstream file("save.dat");
	string search;
	string phone_list = Return_list();

	if (!Atleast_one()) { cout << "저장되어 있는 연락처가 없습니다." << '\n'; return; }

	cout << "검색하실 단어를 입력해주십시오." << '\n';
	cin >> search;

	int start = phone_list.find(search, 0);

	if (start == -1) { cout << "검색 결과가 없습니다." << endl; return; }
	cout << "**************************************" << '\n';
	while (start != -1)
	{
		int end = phone_list.find("\n", start);
		start = Return_startindex(end - 1);
		cout << phone_list.substr(start, end - start) << '\n';
		start = phone_list.find(search, end);
	}
	cout << "**************************************" << '\n';

	file.close();
}

void Information::Print_all()
{
	fstream file("save.dat");
	string line;
	int choice, num = 0;

	if (!Atleast_one()) { cout << "저장되어 있는 연락처가 없습니다." << '\n'; return; }
	cout << "**************************************" << '\n';

	while (!file.eof())
	{
		if (num == 14)
		{
			cout <<'\n';
			cout << "다음페이지로 넘어가시려면 0, 종료하시려면 1을 입력해주십시오. ";
			cin >> choice;
			if (choice == 0)
			{
				num = 0;
				cout << "----------------------------------------------------" << '\n';
			}
			else break;
		}
		getline(file, line);
		cout << line << '\n';
		num++;
	}

	cout << "**************************************" << '\n';
	file.close();
}

void Information::Edit_number()
{
	fstream file("save.dat", ios::app);
	string search, edit;
	int choice;
	string phone_list = Return_list();

	if (!Atleast_one()) { cout << "저장되어 있는 연락처가 없습니다!" << '\n'; return; }

	cout << "수정하실 연락처의 이름이나 번호를 입력하여주십시오." << '\n';
	cin >> search;
	
	int start = phone_list.find(search, 0);

	if (start != -1) 
	{
		int end = phone_list.find('\n', start);
		start = Return_startindex(end - 1);

		cout << "**************************************" << '\n';
		cout << phone_list.substr(start, end - start) << '\n';
		cout << "**************************************" << '\n';
		cout << "어떤 항목을 수정하시겠습니까? 이름: 1 번호: 2 삭제: 3 취소: 0 " << '\n';
		cin >> choice;

		int cut = phone_list.find(' ', start);

		switch (choice)
		{
		case 1:
			cout << "바꾸실 내용을 입력하여 주십시오.";
			cin >> edit;
			phone_list.replace(start, cut - start, edit);
			break;
		case 2:
			cout << "바꾸실 내용을 입력하여 주십시오.";
			cin >> edit;
			phone_list.replace(cut + 1, end - cut - 1, edit);
			break;
		case 3:
			phone_list.erase(start, end - start +1);
			break;
		case 0:
			break;
		default: 
			cout << "잘못 입력하셨습니다." << '\n';
			break;
		}

		Save_array(phone_list);
	}
	else { cout << "항목을 찾을 수 없습니다." << '\n'; }
	
	file.close();
}


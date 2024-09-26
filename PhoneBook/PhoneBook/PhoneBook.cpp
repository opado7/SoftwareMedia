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
		cout << "1. ���ο� ��ȭ��ȣ �߰�" << '\n';
		cout << "2. ���� ��ȭ��ȣ �˻�" << '\n';
		cout << "3. ���� ��ȭ��ȣ�� ��ü ���" << '\n';
		cout << "4. ��ȭ��ȣ ����" << '\n';
		cout << "5. ���α׷� ����" << '\n';
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
			std::cout << "���α׷��� �����մϴ�" << '\n';
			return;
		default:
			std::cout << "�߸� �Է��ϼ̽��ϴ�." << '\n';
			break;
		}
	}
}

void Information::Add_Phone()
{
	fstream file("save.dat", ios::app);
	string name, phone_num;

	cout << "�̸��� ��ȭ��ȣ�� ����� �����Ͽ� �Է����ֽʽÿ�." << '\n';
	cin >> name >> phone_num;
	cout << '\n';

	if (file) {
		file << name << " " << phone_num << '\n';
		cout << "���������� �߰��Ǿ����ϴ�." << "\n";
	}
	else { cout << "������ �߻��Ͽ����ϴ�." << '\n'; return; }

	file.close();

}

void Information::Search()
{
	fstream file("save.dat");
	string search;
	string phone_list = Return_list();

	if (!Atleast_one()) { cout << "����Ǿ� �ִ� ����ó�� �����ϴ�." << '\n'; return; }

	cout << "�˻��Ͻ� �ܾ �Է����ֽʽÿ�." << '\n';
	cin >> search;

	int start = phone_list.find(search, 0);

	if (start == -1) { cout << "�˻� ����� �����ϴ�." << endl; return; }
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

	if (!Atleast_one()) { cout << "����Ǿ� �ִ� ����ó�� �����ϴ�." << '\n'; return; }
	cout << "**************************************" << '\n';

	while (!file.eof())
	{
		if (num == 14)
		{
			cout <<'\n';
			cout << "������������ �Ѿ�÷��� 0, �����Ͻ÷��� 1�� �Է����ֽʽÿ�. ";
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

	if (!Atleast_one()) { cout << "����Ǿ� �ִ� ����ó�� �����ϴ�!" << '\n'; return; }

	cout << "�����Ͻ� ����ó�� �̸��̳� ��ȣ�� �Է��Ͽ��ֽʽÿ�." << '\n';
	cin >> search;
	
	int start = phone_list.find(search, 0);

	if (start != -1) 
	{
		int end = phone_list.find('\n', start);
		start = Return_startindex(end - 1);

		cout << "**************************************" << '\n';
		cout << phone_list.substr(start, end - start) << '\n';
		cout << "**************************************" << '\n';
		cout << "� �׸��� �����Ͻðڽ��ϱ�? �̸�: 1 ��ȣ: 2 ����: 3 ���: 0 " << '\n';
		cin >> choice;

		int cut = phone_list.find(' ', start);

		switch (choice)
		{
		case 1:
			cout << "�ٲٽ� ������ �Է��Ͽ� �ֽʽÿ�.";
			cin >> edit;
			phone_list.replace(start, cut - start, edit);
			break;
		case 2:
			cout << "�ٲٽ� ������ �Է��Ͽ� �ֽʽÿ�.";
			cin >> edit;
			phone_list.replace(cut + 1, end - cut - 1, edit);
			break;
		case 3:
			phone_list.erase(start, end - start +1);
			break;
		case 0:
			break;
		default: 
			cout << "�߸� �Է��ϼ̽��ϴ�." << '\n';
			break;
		}

		Save_array(phone_list);
	}
	else { cout << "�׸��� ã�� �� �����ϴ�." << '\n'; }
	
	file.close();
}


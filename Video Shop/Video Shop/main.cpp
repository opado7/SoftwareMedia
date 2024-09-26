#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void Print_video();
void Print_user();
void rent_video();
void return_video();
void Add_info();
void Del_info();
void Search_video(string word);
void Search_guest(string word);

int main() {

	char choice;//������� �޴� ����
	string search;//�˻� Ű����

	while (true) {
		cout << "********************************************************" << endl;
		cout << "1. ���� ��� �˻��ϱ�" << endl;
		cout << "2. ȸ�� ���� �˻��ϱ�" << endl;
		cout << "3. ���� �뿩" << endl;
		cout << "4. ���� �ݳ�" << endl;
		cout << "5. ���� ��� ���" << endl;
		cout << "6. ȸ�� ��� ���" << endl;
		cout << "7. ���� / ȸ�� �߰�" << endl;
		cout << "8. ���� / ȸ�� ����" << endl;
		cout << "0. ����" << endl;
		cout << "********************************************************" << endl;

		cin >> choice;
		cin.ignore();

		switch (choice)
		{
		case '1':
			cout << "�˻��Ͻ� ���� ������ �Է��� �ֽʽÿ�." << endl;
			getline(cin, search);
			Search_video(search);
			break;
		case '2':
			cout << "�˻��Ͻ� ȸ�� �̸��� �Է��� �ֽʽÿ�." << endl;
			getline(cin, search);
			Search_guest(search);
			break;
		case '3':
			rent_video();
			break;
		case '4':
			return_video();
			break;
		case '5':
			Print_video();
			break;
		case '6':
			Print_user();
			break;
		case '7':
			Add_info();
			break;
		case '8':
			Del_info();
			break;
		case '0':
			cout << "���α׷��� �����մϴ�." << endl;
			return 0;
		default:
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
			break;
			}
		}
}
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

	char choice;//사용자의 메뉴 선택
	string search;//검색 키워드

	while (true) {
		cout << "********************************************************" << endl;
		cout << "1. 비디오 목록 검색하기" << endl;
		cout << "2. 회원 정보 검색하기" << endl;
		cout << "3. 비디오 대여" << endl;
		cout << "4. 비디오 반납" << endl;
		cout << "5. 비디오 목록 출력" << endl;
		cout << "6. 회원 목록 출력" << endl;
		cout << "7. 비디오 / 회원 추가" << endl;
		cout << "8. 비디오 / 회원 삭제" << endl;
		cout << "0. 종료" << endl;
		cout << "********************************************************" << endl;

		cin >> choice;
		cin.ignore();

		switch (choice)
		{
		case '1':
			cout << "검색하실 비디오 제목을 입력해 주십시오." << endl;
			getline(cin, search);
			Search_video(search);
			break;
		case '2':
			cout << "검색하실 회원 이름을 입력해 주십시오." << endl;
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
			cout << "프로그램을 종료합니다." << endl;
			return 0;
		default:
			cout << "잘못 입력하셨습니다." << endl;
			break;
			}
		}
}
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> Return_rawvideolist();
vector<string> Return_videolist();
vector<string> Return_guestlist();

void Print_video()
{
	vector<string> list = Return_videolist();
	if (list[0] == "-1") { return; } //파일이 열리지 않을경우

	for (int i = 0; i < list.size(); i++)
	{
		//if (list[i].size() > 1) //데이터의 아무것도 써져있지 않은 줄이 출력되는것을 방지
		{
			cout << i + 1 << ". " << list[i] << endl;
			cout << endl;
		}
	}
}

void Print_user()
{
	vector<string> list = Return_guestlist();
	if (list[0] == "-1") { return; } //파일이 열리지 않을경우

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].size() > 1) //데이터의 아무것도 써져있지 않은 줄이 출력되는것을 방지
		{
			cout << i + 1 << ". " << list[i] << endl;
			cout << endl;
		}
	}
}

void Search_video(string word)
{
	vector<string> video_list = Return_videolist();
	int check_num = 0;//검색 결과가 최소 한개 이상 있는지 확인함

	if (video_list[0] == "-1") { return; }
	
	cout << '\n';

	for (int i = 0; i < video_list.size(); i++)
	{
		if (video_list[i].find(word) != -1)
		{
			cout << i + 1 << ". " << video_list[i] << endl; //번호를 붙여서 출력
			check_num++;
		}
	}

	if (check_num == 0) { cout << "검색 결과가 없습니다!" << endl; return; }
}

void Search_guest(string word)
{
	vector<string> guest_list = Return_guestlist();
	int check_num = 0;

	if (guest_list[0] == "-1") { return; }

	for (int i = 0; i < guest_list.size(); i++)
	{
		if (guest_list[i].find(word) != -1)
		{
			cout << i + 1 << ". " << guest_list[i] << endl; //번호를 붙여서 출력
			check_num++;
		}
	}

	if (check_num == 0) { cout << "검색 결과가 없습니다!" << endl; return; }
}

vector<int> Search_videotool(vector<string> list2, string search_for)
{
	vector<int> Result;
	string a, b;
	int i = 0, j = 0;
	vector<int> error = { -1 }; //에러 발생시 리턴하는 벡터
	bool Atleast_one = false; //검색 결과가 최소 한개 이상 있는지 검사

	for (i = 0; i < list2.size(); i++)
	{
		if (list2[i].find(search_for) != -1)
		{
			a = list2[i];
			for (j = 0; j < a.size(); j++)
			{
				if (a[j] == '/') break; //대출상태 표시하는곳을 삭제하고 출력
			}
			b = a.substr(0, j - 1);
			cout << i + 1 << ". " << b << endl;
			Atleast_one = true;
			Result.push_back(i);
		}
	}

	if (Atleast_one == false) { cout << "검색 결과가 없습니다!" << endl; return error; } //검색 결과가 없을 때
	return Result;

}

vector<int> Search_guesttool(vector<string> list2, string search_for)
{
	vector<int> Result;
	vector<int> error = { -1 }; //에러 발생시 리턴하는 벡터
	bool Atleast_one = false; //검색 결과가 최소 한개 이상 있는지 검사

	for (int i = 0; i < list2.size(); i++)
	{
		if (list2[i].find(search_for) != -1)
		{
			cout << i + 1 << ". " << list2[i] << endl; //번호를 붙여서 출력
			Atleast_one = true;
			Result.push_back(i);

		}
	}

	if (Atleast_one == false) { cout << "검색 결과가 없습니다!" << endl; return error; } //검색 결과가 없을 때
	return Result;

}

bool save_videodata(vector<string> array)
{
	fstream file("data.dat");

	if (!file) { cout << "파일을 여는데 오류가 발생했습니다." << endl; return false; } //파일을 열 수 없을 경우의 처리문

	for (int i = 0; i < array.size(); i++)
	{
		if (array[i].size() > 5) {file << array[i]<<'\n'; } //빈 줄이 추가되는것을 막는 처리문
	}

	file.close();
	return true;
}

bool save_guestdata(vector<string> array)
{
	fstream file("guest.dat");

	if (!file) { cout << "파일을 여는데 오류가 발생했습니다." << endl; return false; } //파일을 열 수 없을 경우의 처리문

	for (int i = 0; i < array.size(); i++)
	{
		if (array[i].size() > 0) { file << array[i] << '\n'; }
	}

	file.close();
	return true;
}

void rent_video()
{
	string guest, name, check_number;
	vector<string> video_list = Return_rawvideolist();
	vector<string> guest_list = Return_guestlist();
	int video_choice = 0, guest_choice = 0;

	if (video_list[0] == "-1" || guest_list[0] == "-1") { return; }

	cout << "대여할 비디오 제목을 입력해주십시오." << endl;
	cin >> name;

	vector <int> return_choice = Search_videotool(video_list, name);

	if (return_choice[0] == -1) { return; } //검색 결과가 없을 경우
	else if (return_choice.size() != 1)  //검색 결과가 2개 이상일 경우
	{
		cout << "대여하실 비디오에 해당되는 번호를 입력해주십시오." << endl;
		cin >> video_choice;
		video_choice--;
		for (int i = 0; i < return_choice.size(); i++)
		{
			if (video_choice == return_choice[i]) break;
			if (i == return_choice.size()) { cout << "잘못 입력하셨습니다." << endl; return; }//사용자가 목록에 있는 번호 이외의 번호를 입력하였을 경우
		}
	}
	else //검색 결과가 1개일 경우
	{
		video_choice = return_choice[0];
	}

	check_number = video_list[video_choice].back();
	if (check_number !="0") { cout << "이 비디오는 현재 다른사람이 대여중입니다!" << endl; return; }//문자열 맨 뒤 문자로 대출중인지 판별

	cout << '\n';

	cin.ignore();
	cout << "회원님의 이름을 입력하여주십시오." << endl;
	getline(cin, guest);

	vector<int> return_choice2 = Search_guesttool(guest_list, guest);

	if (return_choice2[0] == -1) { return; }//검색 결과가 없을 경우
	else if (return_choice2.size() != 1) //검색 결과가 2개 이상일 경우
	{
		cout << "위의 목록에서 고객님에게 해당되는 정보의 번호를 선택해주십시오." << endl;
		cin >> guest_choice;
		guest_choice--;

		for (int i = 0; i < return_choice2.size(); i++)
		{
			if (guest_choice == return_choice2[i]) break;
			if (i == return_choice2.size()) { cout << "잘못 입력하셨습니다." << endl; return; }//사용자가 목록에 있는 번호 이외의 번호를 입력하였을 경우
		}
	}
	else //검색 결과가 1개일 경우
	{
		guest_choice = return_choice2[0];
	}

	video_list[video_choice].pop_back();
	video_list[video_choice].append(guest_list[guest_choice]);

	cout << '\n';

	if (save_videodata(video_list)) { cout << "성공!" << endl; } //수정된 데이터 저장

	return;
}

void return_video()
{
	string name;
	vector<string> video_list = Return_rawvideolist();
	int video_choice = 0;

	if (video_list[0] == "-1") { return; }

	cout << "반납할 비디오 제목을 입력해주십시오." << endl;
	getline(cin, name);

	vector <int> return_choice = Search_videotool(video_list, name);

	if (return_choice[0] == -1) { return; }//검색 결과가 없을 경우
	else if (return_choice.size() != 1) //검색 결과가 2개 이상일 경우
	{
		cout << "반납하실 비디오에 해당되는 번호를 입력해주십시오." << endl;
		cin >> video_choice;

		video_choice--;

		for (int i = 0; i < return_choice.size(); i++)
		{
			if (video_choice == return_choice[i]) break;
			if (i == return_choice.size()) { cout << "잘못 입력하셨습니다." << endl; return; }
		}
	}
	else//검색 결과가 1개일 경우
	{
		video_choice = return_choice[0];
	}

	if (video_list[video_choice].back() == '0') { cout << "이 비디오는 대출중인 상태가 아닙니다!" << endl; return; } //문자열 맨 뒤 문자로 대출중인지 판별

	int start = video_list[video_choice].find("/"); //문자열에서 대출상태 표시 변경
	int end = video_list[video_choice].find("\n");
	video_list[video_choice].replace(start, end - start - 1, "/ 0");

	if (save_videodata(video_list)) { cout << "반납 완료되었습니다!" << endl; } //데이터 저장
	return;

}

void Add_info()
{
	vector<string> video_list = Return_rawvideolist(); //비디오 리스트를 받아옴
	vector<string> guest_list = Return_guestlist(); //회원 리스트를 받아옴
	char choice; //사용자의 선택
	string new_video, new_guest; //새로운 비디오와 회원을 받는 변수

	if (video_list[0] == "-1" || guest_list[0] == "-1") { return; }

	cout << "비디오를 추가하시려면 0, 회원을 추가하시려면 1을 입력해주십시오." << endl;
	cin >> choice;

	if (choice == '0') //비디오 추가
	{
		cin.ignore();
		cout << "추가하실 비디오의 제목을 입력해주십시오." << endl;
		getline(cin, new_video);
		new_video.append(" / 0"); //대출상태 표시
		video_list.push_back(new_video);
		if (save_videodata(video_list)) { cout << "추가 완료되었습니다!" << endl; } //데이터 저장
	}
	else if (choice == '1')//회원 추가
	{
		cin.ignore();
		cout << "추가하실 회원의 이름을 입력해주십시오." << endl;
		getline(cin, new_guest);
		guest_list.push_back(new_guest);
		if (save_guestdata(guest_list)) { cout << "추가 완료되었습니다!" << endl; }
	}
	else { cout << "잘못 입력하셨습니다." << endl; } //잘못 입력시

	return;
}

void Del_info()
{
	vector<string> video_list = Return_rawvideolist();
	vector<string> guest_list = Return_guestlist();
	char choice;
	int video_choice, guest_choice;
	string del_video, del_guest;

	if (video_list[0] == "-1" || guest_list[0] == "-1") { return; }

	cout << "비디오를 삭제하시려면 0, 회원을 삭제하시려면 1을 입력해주십시오." << endl;
	cin >> choice;
	if (choice == '0') //비디오 삭제
	{
		cout << "삭제하실 비디오의 제목을 입력해주십시오." << endl;
		getline(cin, del_video);

		vector <int> return_choice = Search_videotool(video_list, del_video);

		if (return_choice[0] == -1) { return; } //검색 결과가 없을 경우
		else if (return_choice.size() != 1)  //검색 결과가 2개 이상일 경우
		{
			cout << "삭제하실 비디오에 해당되는 번호를 입력해주십시오." << endl;
			cin >> video_choice;
			video_choice--;
			for (int i = 0; i < return_choice.size(); i++)
			{
				if (video_choice == return_choice[i]) break;
				if (i == return_choice.size()) { cout << "잘못 입력하셨습니다." << endl; return; }//사용자가 목록에 있는 번호 이외의 번호를 입력하였을 경우
			}
		}
		else //검색 결과가 1개일 경우
		{
			video_choice = return_choice[0];
		}

		video_list.erase(video_list.begin() + video_choice);

		if (save_videodata(video_list)) { cout << "삭제 완료되었습니다!" << endl; } //데이터 저장
	}
	else if (choice == '1')//회원 삭제
	{
		cout << "삭제하실 회원의 이름을 입력해주십시오." << endl;
		getline(cin, del_guest);
		vector <int> return_choice = Search_guesttool(guest_list, del_guest);

		if (return_choice[0] == -1) { return; } //검색 결과가 없을 경우
		else if (return_choice.size() != 1)  //검색 결과가 2개 이상일 경우
		{
			cout << "삭제하실 비디오에 해당되는 번호를 입력해주십시오." << endl;
			cin >> guest_choice;
			guest_choice--;
			for (int i = 0; i < return_choice.size(); i++)
			{
				if (guest_choice == return_choice[i]) break;
				if (i == return_choice.size()) { cout << "잘못 입력하셨습니다." << endl; return; }//사용자가 목록에 있는 번호 이외의 번호를 입력하였을 경우
			}
		}

		else //검색 결과가 1개일 경우
		{
			guest_choice = return_choice[0];
		}

		video_list.erase(video_list.begin() + guest_choice);

		if (save_guestdata(guest_list)) { cout << "삭제 완료되었습니다!" << endl; }
	}
	else { cout << "잘못 입력하셨습니다." << endl; } //잘못 입력시

	return;
}
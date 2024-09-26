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
	if (list[0] == "-1") { return; } //������ ������ �������

	for (int i = 0; i < list.size(); i++)
	{
		//if (list[i].size() > 1) //�������� �ƹ��͵� �������� ���� ���� ��µǴ°��� ����
		{
			cout << i + 1 << ". " << list[i] << endl;
			cout << endl;
		}
	}
}

void Print_user()
{
	vector<string> list = Return_guestlist();
	if (list[0] == "-1") { return; } //������ ������ �������

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].size() > 1) //�������� �ƹ��͵� �������� ���� ���� ��µǴ°��� ����
		{
			cout << i + 1 << ". " << list[i] << endl;
			cout << endl;
		}
	}
}

void Search_video(string word)
{
	vector<string> video_list = Return_videolist();
	int check_num = 0;//�˻� ����� �ּ� �Ѱ� �̻� �ִ��� Ȯ����

	if (video_list[0] == "-1") { return; }
	
	cout << '\n';

	for (int i = 0; i < video_list.size(); i++)
	{
		if (video_list[i].find(word) != -1)
		{
			cout << i + 1 << ". " << video_list[i] << endl; //��ȣ�� �ٿ��� ���
			check_num++;
		}
	}

	if (check_num == 0) { cout << "�˻� ����� �����ϴ�!" << endl; return; }
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
			cout << i + 1 << ". " << guest_list[i] << endl; //��ȣ�� �ٿ��� ���
			check_num++;
		}
	}

	if (check_num == 0) { cout << "�˻� ����� �����ϴ�!" << endl; return; }
}

vector<int> Search_videotool(vector<string> list2, string search_for)
{
	vector<int> Result;
	string a, b;
	int i = 0, j = 0;
	vector<int> error = { -1 }; //���� �߻��� �����ϴ� ����
	bool Atleast_one = false; //�˻� ����� �ּ� �Ѱ� �̻� �ִ��� �˻�

	for (i = 0; i < list2.size(); i++)
	{
		if (list2[i].find(search_for) != -1)
		{
			a = list2[i];
			for (j = 0; j < a.size(); j++)
			{
				if (a[j] == '/') break; //������� ǥ���ϴ°��� �����ϰ� ���
			}
			b = a.substr(0, j - 1);
			cout << i + 1 << ". " << b << endl;
			Atleast_one = true;
			Result.push_back(i);
		}
	}

	if (Atleast_one == false) { cout << "�˻� ����� �����ϴ�!" << endl; return error; } //�˻� ����� ���� ��
	return Result;

}

vector<int> Search_guesttool(vector<string> list2, string search_for)
{
	vector<int> Result;
	vector<int> error = { -1 }; //���� �߻��� �����ϴ� ����
	bool Atleast_one = false; //�˻� ����� �ּ� �Ѱ� �̻� �ִ��� �˻�

	for (int i = 0; i < list2.size(); i++)
	{
		if (list2[i].find(search_for) != -1)
		{
			cout << i + 1 << ". " << list2[i] << endl; //��ȣ�� �ٿ��� ���
			Atleast_one = true;
			Result.push_back(i);

		}
	}

	if (Atleast_one == false) { cout << "�˻� ����� �����ϴ�!" << endl; return error; } //�˻� ����� ���� ��
	return Result;

}

bool save_videodata(vector<string> array)
{
	fstream file("data.dat");

	if (!file) { cout << "������ ���µ� ������ �߻��߽��ϴ�." << endl; return false; } //������ �� �� ���� ����� ó����

	for (int i = 0; i < array.size(); i++)
	{
		if (array[i].size() > 5) {file << array[i]<<'\n'; } //�� ���� �߰��Ǵ°��� ���� ó����
	}

	file.close();
	return true;
}

bool save_guestdata(vector<string> array)
{
	fstream file("guest.dat");

	if (!file) { cout << "������ ���µ� ������ �߻��߽��ϴ�." << endl; return false; } //������ �� �� ���� ����� ó����

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

	cout << "�뿩�� ���� ������ �Է����ֽʽÿ�." << endl;
	cin >> name;

	vector <int> return_choice = Search_videotool(video_list, name);

	if (return_choice[0] == -1) { return; } //�˻� ����� ���� ���
	else if (return_choice.size() != 1)  //�˻� ����� 2�� �̻��� ���
	{
		cout << "�뿩�Ͻ� ������ �ش�Ǵ� ��ȣ�� �Է����ֽʽÿ�." << endl;
		cin >> video_choice;
		video_choice--;
		for (int i = 0; i < return_choice.size(); i++)
		{
			if (video_choice == return_choice[i]) break;
			if (i == return_choice.size()) { cout << "�߸� �Է��ϼ̽��ϴ�." << endl; return; }//����ڰ� ��Ͽ� �ִ� ��ȣ �̿��� ��ȣ�� �Է��Ͽ��� ���
		}
	}
	else //�˻� ����� 1���� ���
	{
		video_choice = return_choice[0];
	}

	check_number = video_list[video_choice].back();
	if (check_number !="0") { cout << "�� ������ ���� �ٸ������ �뿩���Դϴ�!" << endl; return; }//���ڿ� �� �� ���ڷ� ���������� �Ǻ�

	cout << '\n';

	cin.ignore();
	cout << "ȸ������ �̸��� �Է��Ͽ��ֽʽÿ�." << endl;
	getline(cin, guest);

	vector<int> return_choice2 = Search_guesttool(guest_list, guest);

	if (return_choice2[0] == -1) { return; }//�˻� ����� ���� ���
	else if (return_choice2.size() != 1) //�˻� ����� 2�� �̻��� ���
	{
		cout << "���� ��Ͽ��� ���Կ��� �ش�Ǵ� ������ ��ȣ�� �������ֽʽÿ�." << endl;
		cin >> guest_choice;
		guest_choice--;

		for (int i = 0; i < return_choice2.size(); i++)
		{
			if (guest_choice == return_choice2[i]) break;
			if (i == return_choice2.size()) { cout << "�߸� �Է��ϼ̽��ϴ�." << endl; return; }//����ڰ� ��Ͽ� �ִ� ��ȣ �̿��� ��ȣ�� �Է��Ͽ��� ���
		}
	}
	else //�˻� ����� 1���� ���
	{
		guest_choice = return_choice2[0];
	}

	video_list[video_choice].pop_back();
	video_list[video_choice].append(guest_list[guest_choice]);

	cout << '\n';

	if (save_videodata(video_list)) { cout << "����!" << endl; } //������ ������ ����

	return;
}

void return_video()
{
	string name;
	vector<string> video_list = Return_rawvideolist();
	int video_choice = 0;

	if (video_list[0] == "-1") { return; }

	cout << "�ݳ��� ���� ������ �Է����ֽʽÿ�." << endl;
	getline(cin, name);

	vector <int> return_choice = Search_videotool(video_list, name);

	if (return_choice[0] == -1) { return; }//�˻� ����� ���� ���
	else if (return_choice.size() != 1) //�˻� ����� 2�� �̻��� ���
	{
		cout << "�ݳ��Ͻ� ������ �ش�Ǵ� ��ȣ�� �Է����ֽʽÿ�." << endl;
		cin >> video_choice;

		video_choice--;

		for (int i = 0; i < return_choice.size(); i++)
		{
			if (video_choice == return_choice[i]) break;
			if (i == return_choice.size()) { cout << "�߸� �Է��ϼ̽��ϴ�." << endl; return; }
		}
	}
	else//�˻� ����� 1���� ���
	{
		video_choice = return_choice[0];
	}

	if (video_list[video_choice].back() == '0') { cout << "�� ������ �������� ���°� �ƴմϴ�!" << endl; return; } //���ڿ� �� �� ���ڷ� ���������� �Ǻ�

	int start = video_list[video_choice].find("/"); //���ڿ����� ������� ǥ�� ����
	int end = video_list[video_choice].find("\n");
	video_list[video_choice].replace(start, end - start - 1, "/ 0");

	if (save_videodata(video_list)) { cout << "�ݳ� �Ϸ�Ǿ����ϴ�!" << endl; } //������ ����
	return;

}

void Add_info()
{
	vector<string> video_list = Return_rawvideolist(); //���� ����Ʈ�� �޾ƿ�
	vector<string> guest_list = Return_guestlist(); //ȸ�� ����Ʈ�� �޾ƿ�
	char choice; //������� ����
	string new_video, new_guest; //���ο� ������ ȸ���� �޴� ����

	if (video_list[0] == "-1" || guest_list[0] == "-1") { return; }

	cout << "������ �߰��Ͻ÷��� 0, ȸ���� �߰��Ͻ÷��� 1�� �Է����ֽʽÿ�." << endl;
	cin >> choice;

	if (choice == '0') //���� �߰�
	{
		cin.ignore();
		cout << "�߰��Ͻ� ������ ������ �Է����ֽʽÿ�." << endl;
		getline(cin, new_video);
		new_video.append(" / 0"); //������� ǥ��
		video_list.push_back(new_video);
		if (save_videodata(video_list)) { cout << "�߰� �Ϸ�Ǿ����ϴ�!" << endl; } //������ ����
	}
	else if (choice == '1')//ȸ�� �߰�
	{
		cin.ignore();
		cout << "�߰��Ͻ� ȸ���� �̸��� �Է����ֽʽÿ�." << endl;
		getline(cin, new_guest);
		guest_list.push_back(new_guest);
		if (save_guestdata(guest_list)) { cout << "�߰� �Ϸ�Ǿ����ϴ�!" << endl; }
	}
	else { cout << "�߸� �Է��ϼ̽��ϴ�." << endl; } //�߸� �Է½�

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

	cout << "������ �����Ͻ÷��� 0, ȸ���� �����Ͻ÷��� 1�� �Է����ֽʽÿ�." << endl;
	cin >> choice;
	if (choice == '0') //���� ����
	{
		cout << "�����Ͻ� ������ ������ �Է����ֽʽÿ�." << endl;
		getline(cin, del_video);

		vector <int> return_choice = Search_videotool(video_list, del_video);

		if (return_choice[0] == -1) { return; } //�˻� ����� ���� ���
		else if (return_choice.size() != 1)  //�˻� ����� 2�� �̻��� ���
		{
			cout << "�����Ͻ� ������ �ش�Ǵ� ��ȣ�� �Է����ֽʽÿ�." << endl;
			cin >> video_choice;
			video_choice--;
			for (int i = 0; i < return_choice.size(); i++)
			{
				if (video_choice == return_choice[i]) break;
				if (i == return_choice.size()) { cout << "�߸� �Է��ϼ̽��ϴ�." << endl; return; }//����ڰ� ��Ͽ� �ִ� ��ȣ �̿��� ��ȣ�� �Է��Ͽ��� ���
			}
		}
		else //�˻� ����� 1���� ���
		{
			video_choice = return_choice[0];
		}

		video_list.erase(video_list.begin() + video_choice);

		if (save_videodata(video_list)) { cout << "���� �Ϸ�Ǿ����ϴ�!" << endl; } //������ ����
	}
	else if (choice == '1')//ȸ�� ����
	{
		cout << "�����Ͻ� ȸ���� �̸��� �Է����ֽʽÿ�." << endl;
		getline(cin, del_guest);
		vector <int> return_choice = Search_guesttool(guest_list, del_guest);

		if (return_choice[0] == -1) { return; } //�˻� ����� ���� ���
		else if (return_choice.size() != 1)  //�˻� ����� 2�� �̻��� ���
		{
			cout << "�����Ͻ� ������ �ش�Ǵ� ��ȣ�� �Է����ֽʽÿ�." << endl;
			cin >> guest_choice;
			guest_choice--;
			for (int i = 0; i < return_choice.size(); i++)
			{
				if (guest_choice == return_choice[i]) break;
				if (i == return_choice.size()) { cout << "�߸� �Է��ϼ̽��ϴ�." << endl; return; }//����ڰ� ��Ͽ� �ִ� ��ȣ �̿��� ��ȣ�� �Է��Ͽ��� ���
			}
		}

		else //�˻� ����� 1���� ���
		{
			guest_choice = return_choice[0];
		}

		video_list.erase(video_list.begin() + guest_choice);

		if (save_guestdata(guest_list)) { cout << "���� �Ϸ�Ǿ����ϴ�!" << endl; }
	}
	else { cout << "�߸� �Է��ϼ̽��ϴ�." << endl; } //�߸� �Է½�

	return;
}
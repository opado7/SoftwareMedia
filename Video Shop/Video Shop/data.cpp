#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> Return_rawvideolist()
{
	fstream file("data.dat");
	vector<string> list;
	vector<string> error{ "-1" };
	string word;

	if (!file) { cout << "������ ���µ� ������ �߻��߽��ϴ�." << endl; return error; }

	while (!file.eof())
	{
		getline(file, word); //���پ� �����ͼ� ���� ���� ����
		if(word.size() > 5) list.push_back(word);
	}

	file.close();
	return list;
}

vector<string> Return_videolist()
{
	fstream file("data.dat");
	vector<string> list;
	vector<string> error{ "-1" };
	string a, b;
	int i;

	if (!file) { cout << "������ ���µ� ������ �߻��߽��ϴ�." << endl; return error; }

	while (!file.eof())
	{
		getline(file, a);
		if (a.size() > 5) 
		{
			
			for (i = 0; i < a.size(); i++)
			{
				if (a[i] == '/') break; //���پ� �����ͼ� ���� ���� �����ϴ°� ������, ���� ���ⱸ�й��ڸ� �����Ͽ� ������
			}
			b = a.substr(0, i - 1);
			list.push_back(b);
		}
	}

	file.close();
	return list;
}

vector<string> Return_guestlist()
{
	fstream file("guest.dat");
	vector<string> list;
	vector<string> error{ "-1" };
	string a;

	if (!file) { cout << "������ ���µ� ������ �߻��߽��ϴ�." << endl; return error; }

	while (!file.eof())
	{
		getline(file, a); //���پ� �����ͼ� ���� ���� ����
		if (a.size() > 5) list.push_back(a);
	}

	file.close();
	return list;
}
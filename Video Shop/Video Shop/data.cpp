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

	if (!file) { cout << "파일을 여는데 문제가 발생했습니다." << endl; return error; }

	while (!file.eof())
	{
		getline(file, word); //한줄씩 가져와서 벡터 내에 저장
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

	if (!file) { cout << "파일을 여는데 문제가 발생했습니다." << endl; return error; }

	while (!file.eof())
	{
		getline(file, a);
		if (a.size() > 5) 
		{
			
			for (i = 0; i < a.size(); i++)
			{
				if (a[i] == '/') break; //한줄씩 가져와서 백터 내에 저장하는건 같으나, 뒤의 대출구분문자를 삭제하여 저장함
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

	if (!file) { cout << "파일을 여는데 문제가 발생했습니다." << endl; return error; }

	while (!file.eof())
	{
		getline(file, a); //한줄씩 가져와서 벡터 내에 저장
		if (a.size() > 5) list.push_back(a);
	}

	file.close();
	return list;
}
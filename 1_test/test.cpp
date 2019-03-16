
#include<iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>
#include<unordered_map>


using namespace std;

int main(int argc, char *argv[])
{
	int N(0);
	vector<string> vecstr;
	string temp;

	cin >> N;
	while (N)
	{
		cin >> temp;
		vecstr.push_back(temp);
		N--;
	}


	for (int i(0); i < vecstr.size(); i++)
	{

		for (int j(0); j < vecstr[i].size() - 3; j++)
		{
			char ch1(vecstr[i][j]), ch2(vecstr[i][j + 1]), ch3(vecstr[i][j + 2]);
			if (ch2 == ch1 && ch3 == ch2)
			{
				vecstr[i].erase(vecstr[i].begin() + j + 2);
				j--;
				continue;
			}
			if (vecstr[i].size() - j >= 4)
			{
				char ch4(vecstr[i][j + 3]);
				if (ch1 == ch2 && ch3 == ch4)
				{
					vecstr[i].erase(vecstr[i].begin() + j + 3);
					j--;
					continue;
				}
			}
		}
	}

	for (int i(0); i < vecstr.size(); i++)
		cout << vecstr[i] << endl;

	return 0;
}
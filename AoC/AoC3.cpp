#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

std::vector<string> SplitString(const string& str, const string split)
{
	std::vector<string> r;
	int splitBegin = 0;
	int splitPos = str.find(split, splitBegin);
	while (splitPos != string::npos)
	{
		r.push_back(str.substr(splitBegin, splitPos - splitBegin));
		splitBegin = splitPos + split.length();
		splitPos = str.find(split, splitBegin + 1);
	}
	r.push_back(str.substr(splitBegin, splitPos));
	return r;
}

bool CheckTriangle(const string& points)
{
	int p[3];
	int currentIndex = 0;
	string currenNum;
	for (char c : points)
	{
		if (c != ' ')
			currenNum += c;
		else
		{
			if (currenNum != "")
			{
				p[currentIndex] = stoi(currenNum);
				++currentIndex;
				currenNum = "";
			}
		}
	}
	p[currentIndex] = stoi(currenNum);

	if (p[0] + p[1] > p[2] && p[1] + p[2] > p[0] && p[2] + p[0] > p[1])
		return true;
	return false;
}

void main3()
{
	ifstream input;
	input.open("./Inputs/Input3.txt");
	string line;
	int count = 0;
	if (input.is_open())
	{
		while (getline(input, line))
		{
			if (CheckTriangle(line))
				++count;
		}
	}
	else
		cout << "Failed to open file Input3.txt" << endl;

	cout << "There are " << count << " possible triangles in this set" << endl;

	cin.get();
}
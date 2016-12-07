#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void main6()
{
	vector<string> strings;
	fstream input;
	input.open("./Inputs/Input6.txt");
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			strings.push_back(line);
		}
	}
	else
		cout << "Failed to open input6.txt" << endl;

	string result = "--------";
	for (int i = 0; i < 8; ++i)
	{
		map<char, int> charCount;
		for (string s : strings)
		{
			++charCount[s[i]];
		}

		char highestChar = 'a';
		int lowCount = INT_MAX;
		for (auto it = charCount.begin(); it != charCount.end(); ++it)
		{
			if (it->second < lowCount)
			{
				highestChar = it->first;
				lowCount = it->second;
			}
		}

		result[i] = highestChar;
	}

	cout << result << endl;
	cin.get();
}
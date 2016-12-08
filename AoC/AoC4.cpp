#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

using namespace std;

int CheckRoom(string line)
{
	regex rgxCheckSum("\\[[a-z]+\\]");
	regex rgxID("[0-9]+");
	smatch checkSumMatch, roomIDMatch;
	regex_search(line, checkSumMatch, rgxCheckSum);
	regex_search(line, roomIDMatch, rgxID);
	string checkSum = checkSumMatch.str().substr(1, checkSumMatch.str().length() - 2);
	int roomId = stoi(roomIDMatch.str());
	line = line.substr(0, line.rfind('-'));

	map<char, int> m;
	for (auto c : line)
	{
		if (c != '-')
			++m[c];
	}

	bool isReal = true;
	for (size_t i = 0; i < checkSum.length() - 1; ++i)
	{
		if ((m[checkSum[i]] < m[checkSum[i + 1]]) || (m[checkSum[i]] == m[checkSum[i + 1]] && checkSum[i] > checkSum[i + 1]) || m[checkSum[i]] == 0 || m[checkSum[i + 1]] == 0)
		{
			isReal = false;
			break;
		}
	}

	for (size_t i = 0; i < line.length(); ++i)
	{
		if (line[i] == '-')
			line[i] = ' ';
		else
		{
			int num = line[i] - 'a';
			num += roomId;
			num %= 26;
			line[i] = num + 'a';
		}
	}

	if (line.find("north") != string::npos)
		cout << line << "in room " << roomId << endl;

	return isReal ? roomId : 0;
}

void main4()
{
	ifstream input;
	input.open("./Inputs/Input4.txt");
	int result = 0;
	string line;
	if (input.is_open())
	{
		while (getline(input, line))
		{
			result += CheckRoom(line);
		}
	}
	else
		cout << "Failed to open Input4.txt" << endl;

	cout << "the sum of the sector IDs of the real rooms is " << result << endl;
	cin.get();
}
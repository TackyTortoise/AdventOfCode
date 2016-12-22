#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Swap(const size_t pos1, const size_t pos2, string& str)
{
	string copy = str;
	str[pos1] = copy[pos2];
	str[pos2] = copy[pos1];
}

void RotateLeft(const size_t offset, string& str)
{
	string copy = str;
	for (size_t i = 0; i < str.size(); ++i)
	{
		str[i] = copy[(i + offset) % str.size()];
	}
}

void RotateRight(const size_t offset, string& str)
{
	string copy = str;
	for (size_t i = 0; i < str.size(); ++i)
	{
		int index = i - offset;
		while (index < 0)
			index += str.size();
		str[i] = copy[index];
	}
}

string Scramble(const string in, const vector<string>& instructions)
{
	ifstream input("Inputs/Input21.txt");
	string myString = in;
	//cout << myString << endl;
	for (string line : instructions)
	{
		if (line.find("swap position") != string::npos)
		{
			int pos1 = line[line.find(" with") - 1] - '0';
			int pos2 = line[line.size() - 1] - '0';
			Swap(pos1, pos2, myString);
			//cout << "Swap " << pos1 << " and " << int(line[line.size() - 1] - '0') << " : " << myString << endl;
		}
		else if (line.find("swap letter") != string::npos)
		{
			char firstLetter = line[line.find(" with") - 1];
			char secondLetter = line[line.size() - 1];
			int pos1 = myString.find(firstLetter);
			int pos2 = myString.find(secondLetter);
			Swap(pos1, pos2, myString);
			//cout << "Swap " << firstLetter << " and " << secondLetter << " : " << myString << endl;
		}
		else if (line.find("rotate based") != string::npos)
		{
			char letter = line[line.size() - 1];
			int offset = myString.find(letter);
			offset += offset >= 4 ? 2 : 1;
			RotateRight(offset, myString);
			//cout << "Rotate based on " << letter << " offset " << offset << " : " << myString << endl;
		}
		else if (line.find("rotate") != string::npos)
		{
			int offset = line[line.find(" step") - 1] - '0';
			if (line.find("left") != string::npos)
				RotateLeft(offset, myString);
			else
				RotateRight(offset, myString);
			//cout << "Rotate with index " << offset << " : " << myString << endl;
		}
		else if (line.find("reverse") != string::npos)
		{
			int pos1 = line[line.find(" through") - 1] - '0';
			int pos2 = line[line.size() - 1] - '0';
			reverse(myString.begin() + pos1, myString.begin() + pos2 + 1);
			//cout << "Reversed " << pos1 << " through " << pos2 << " : " << myString << endl;
		}
		else if (line.find("move") != string::npos)
		{
			int pos1 = line[line.find(" to") - 1] - '0';
			int pos2 = line[line.size() - 1] - '0';
			char letter = myString[pos1];
			myString.erase(myString.begin() + pos1);
			myString.insert(myString.begin() + pos2, letter);
			//cout << "Moved " << pos1 << " to " << pos2 << " : " << myString << endl;
		}

	}

	cout << myString << endl;

	input.close();
	return myString;
}

string UnScramble(const string in, const vector<string>& instructions)
{
	ifstream input("Inputs/Input21.txt");
	string myString = in;
	for (string line : instructions)
	{
		if (line.find("swap position") != string::npos)
		{
			int pos1 = line[line.find(" with") - 1] - '0';
			int pos2 = line[line.size() - 1] - '0';
			Swap(pos1, pos2, myString);
		}
		else if (line.find("swap letter") != string::npos)
		{
			char firstLetter = line[line.find(" with") - 1];
			char secondLetter = line[line.size() - 1];
			int pos1 = myString.find(firstLetter);
			int pos2 = myString.find(secondLetter);
			Swap(pos1, pos2, myString);
		}
		else if (line.find("rotate based") != string::npos)
		{
			char letter = line[line.size() - 1];
			int offset = myString.find(letter);
			if (offset % 2 == 0)
				offset = offset / 2 + 5;
			else
				offset -= offset / 2;
			if (offset == 0)
				offset = 9;
			RotateLeft(offset, myString);
		}
		else if (line.find("rotate") != string::npos)
		{
			int offset = line[line.find(" step") - 1] - '0';
			if (line.find("left") != string::npos)
				RotateRight(offset, myString);
			else
				RotateLeft(offset, myString);
		}
		else if (line.find("reverse") != string::npos)
		{
			int pos1 = line[line.find(" through") - 1] - '0';
			int pos2 = line[line.size() - 1] - '0';
			reverse(myString.begin() + pos1, myString.begin() + pos2 + 1);
		}
		else if (line.find("move") != string::npos)
		{
			int pos1 = line[line.find(" to") - 1] - '0';
			int pos2 = line[line.size() - 1] - '0';
			if (pos1 > pos2)
				int t = 0;
			char letter = myString[pos2];
			myString.erase(myString.begin() + pos2);
			myString.insert(myString.begin() + pos1, letter);
		}
	}

	cout << myString << endl;

	input.close();
	return myString;
}

void main()
{
	ifstream input("Inputs/Input21.txt");
	vector<string> instructions;
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			instructions.push_back(line);
		}
	}
	else
		cout << "Failed to open Input21.txt" << endl;

	string g = Scramble("abcdefgh", instructions);
	reverse(instructions.begin(), instructions.end());
	string r = UnScramble(g, instructions);

	string in = "fdhbcgea";
	int ts = 1;
	for (int i = 0; i < instructions.size() - ts + 1; i += ts)
	{
		vector<string> test;
		for (int j = 0; j < ts; ++j)
			test.push_back(instructions[i + j]);
		string o = Scramble("abcdefgh", vector<string>{test});
		//reverse(test.begin(), test.end());
		string t = UnScramble(o, vector<string>{test});
		if (t != "abcdefgh")
			int c = 0;
	}
	cin.get();
}
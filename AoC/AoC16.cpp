#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int DESIRED_LENGTH = 35651584;

void GenerateData(string& str)
{
	string copy = str;
	reverse(copy.begin(), copy.end());
	for (int i = 0; i < copy.length(); ++i)
	{
		copy[i] = copy[i] == '0' ? '1' : '0';
	}
	str += '0' + copy;
}

string GenerateChecksum(const string& str)
{
	string check;
	for (int i = 0; i < str.length(); i += 2)
	{
		if (str[i] == str[i + 1])
			check += '1';
		else
			check += '0';
	}
	return check;
}

void main16()
{
	string input = "11100010111110100";
	while (input.length() < DESIRED_LENGTH)
	{
		GenerateData(input);
	}
	string checkSum = GenerateChecksum(input.substr(0, DESIRED_LENGTH));
	while(checkSum.length() % 2 == 0)
	{
		checkSum = GenerateChecksum(checkSum);
	}
	cout << "The checksum is: " << checkSum << endl;
	cin.get();
}
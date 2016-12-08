#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool SupportsTLS(const std::string& s)
{
	bool result = false;
	bool inBraces = false;
	for (size_t i = 0; i < s.length() - 3; ++i)
	{
		if (s[i] == '[')
			inBraces = true;
		if (s[i] == ']')
			inBraces = false;
		if (s[i] != s[i + 1] && s[i + 1] == s[i + 2] && s[i] == s[i + 3])
		{
			if (inBraces)
				return false;

			result = true;
		}
	}

	return result;
}

bool SupportsSSL(const std::string& s)
{
	vector<string> supernetseqs;
	vector<string> hypernetseqs;
	bool inBrackets = false;

	for (size_t i = 0; i < s.length() - 2; ++i)
	{
		if (s[i] == '[')
			inBrackets = true;
		if (s[i] == ']')
			inBrackets = false;

		if (s[i] != s[i + 1] && s[i] == s[i + 2] && s[i+1] != '[' && s[i+1] != ']')
		{
			if (inBrackets)
			{
				hypernetseqs.push_back(s.substr(i, 3));
			}
			else
			{
				supernetseqs.push_back(s.substr(i, 3));
			}
		}
	}
	
	for (string h : hypernetseqs)
	{
		string inv;
		inv += h[1];
		inv += h[0];
		inv += h[1];
		if (find(supernetseqs.begin(), supernetseqs.end(), inv) != supernetseqs.end())
			return true;
	}

	return false;
}

void main7()
{
	fstream input;
	input.open("./Inputs/Input7.txt");
	int count = 0;
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			if (SupportsSSL(line))
				++count;
		}
	}
	else
		cout << "Failed to open Input7.txt" << endl;

	cout << "# of IPs that support SSL " << count << endl;

	cin.get();
}
#include <iostream>
#include <string>

using namespace std;

string GetNextRow(const string& r)
{
	string result;
	for (int i = 0; i < r.size(); ++i)
	{
		char left = i > 0 ? r[i - 1] : '.';
		char center = r[i];
		char right = i < r.size() - 1 ? r[i + 1] : '.';

		if ((left == '^' && center == '^' && right == '.')
			|| (left == '.' && center == '^' && right == '^')
			|| (left == '^' && center == '.' && right == '.')
			|| (left == '.' && center == '.' && right == '^'))
		{
			result.push_back('^');
		}
		else
		{
			result.push_back('.');
		}
	}
	return result;
}

void main18()
{
	size_t safeTiles = 0;
	string input = "...^^^^^..^...^...^^^^^^...^.^^^.^.^.^^.^^^.....^.^^^...^^^^^^.....^.^^...^^^^^...^.^^^.^^......^^^^";
	for (auto c : input)
	{
		if (c == '.')
			++safeTiles;
	}
	//cout << input << endl;
	for (int i = 0; i < 399999; ++i)
	{
		input = GetNextRow(input);
		//cout << input << endl;
		for (auto c : input)
		{
			if (c == '.')
				++safeTiles;
		}
	}
	cout << "Total amount of safe tiles: " << safeTiles << endl;
	cin.get();
}
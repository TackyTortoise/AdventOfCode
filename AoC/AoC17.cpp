#include <time.h>
#include <cstdlib>
#include <iostream>
#include "md5wrapper.h"
#include <vector>
#include <random>

using namespace std;
mt19937 RAND_GEN;

string GetRandomPath(const string& input)
{
	md5wrapper md5;
	int gridSize = 4;
	int currentPos = 0;
	string path;
	vector<char> options;
	int randNr;
	while (currentPos != 15)
	{
		options.clear();
		string hash = md5.getHashFromString(input + path);
		if (hash[0] >= 'b' && hash[0] <= 'f' && currentPos / gridSize > 0)
			options.push_back('U');
		if (hash[1] >= 'b' && hash[1] <= 'f' && currentPos / gridSize < gridSize - 1)
			options.push_back('D');
		if (hash[2] >= 'b' && hash[2] <= 'f' && currentPos % gridSize > 0)
			options.push_back('L');
		if (hash[3] >= 'b' && hash[3] <= 'f' && currentPos % gridSize < gridSize - 1)
			options.push_back('R');

		if (options.size() == 0)
		{
			path += "FAILED";
			break;
		}

		randNr = RAND_GEN();
		switch (options[randNr % options.size()])
		{
		case 'U':
			currentPos -= gridSize;
			path += 'U';

			break;
		case 'D':
			currentPos += gridSize;
			path += 'D';
			break;
		case 'L':
			--currentPos;
			path += 'L';
			break;
		case 'R':
			++currentPos;
			path += 'R';
			break;
		default:
			cout << "Invalid option" << endl;
			break;
		}
	}
	return path;
}

void main()
{
	srand(time(nullptr));
	vector<string> paths;
	int maxLength = 0;
	for (int i = 0; i < INT_MAX; ++i)
	{
		string t = GetRandomPath("pvhmgsws");
		if (t.rfind("FAILED") == string::npos && find(paths.begin(), paths.end(), t) == paths.end())
		{
			cout << t << endl;
			paths.push_back(t);
			if (t.size() > maxLength)
			{
				maxLength = t.size();
				cout << "Found new max length: " << maxLength << endl;
			}
		}
	}
	cout << "Paths found: " << paths.size() << endl;
	for (auto p : paths)
		cout << p << endl;

	cin.get();
}

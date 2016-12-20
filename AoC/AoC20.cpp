#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

void main()
{
	regex rgx("\\d+");

	unsigned int lowestFreeIP = 0;
	vector<string> inputs;
	ifstream input("Inputs/Input20.txt");
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			inputs.push_back(line);
		}
	}
	else
		cout << "Failed to open Input20.txt" << endl;

	//part1
	/*for (auto it = inputs.begin(); it != inputs.end();)
	{
		string t = *it;
		sregex_iterator next(t.begin(), t.end(), rgx);
		sregex_iterator end;
		vector<unsigned int> sm;
		while (next != end) {
			std::smatch match = *next;
			sm.push_back(stoul(match.str()));
			++next;
		}
		int rangeLow = sm[0];
		int rangeHigh = sm[1];
		if (lowestFreeIP <= rangeHigh && lowestFreeIP >= rangeLow)
		{
			inputs.erase(it);
			it = inputs.begin();
			lowestFreeIP = rangeHigh + 1;
		}
		else
			++it;
	}*/

	//part2
	lowestFreeIP = numeric_limits<unsigned int>::max();
	bool * ips = new bool[lowestFreeIP];
	memset(ips, false, lowestFreeIP);
	for (auto it = inputs.begin(); it != inputs.end(); ++it)
	{
		int dashPos = it->find('-');
		unsigned int rangeLow = stoul(it->substr(0, dashPos));
		unsigned int rangeHigh = stoul(it->substr(dashPos + 1));
		unsigned int IPCount = rangeHigh - rangeLow + 1;
		bool* start = ips + rangeLow;
		for (unsigned int i = 0; i < IPCount; ++i)
		{
			if (start[i] == false)
			{
				--lowestFreeIP;
				start[i] = true;
			}
		}
	}
	++lowestFreeIP;
	cout << "Lowest not blocked IP: " << lowestFreeIP << endl;
	delete[] ips;
	cin.get();
}
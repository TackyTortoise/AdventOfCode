#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>

using namespace std;

struct Disc
{
	Disc(int pc, int sp) : positionCount(pc), startPosition(sp) {}
	int positionCount = 0;
	int startPosition = 0;
};

int main()
{
	vector<Disc> discs;
	ifstream input("Inputs/Input15.txt");
	regex rgx("\\d+");
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			std::sregex_iterator next(line.begin(), line.end(), rgx);
			std::sregex_iterator end;
			vector<int> sm;
			while (next != end) {
				std::smatch match = *next;
				sm.push_back(stoi(match.str()));
				++next;
			}
			discs.push_back(Disc(sm[1], sm[3]));
		}
	}
	else
		cout << "Failed to open Input15.txt" << endl;

	//part 2
	discs.push_back(Disc(11, 0));

	for (size_t t = 5;; ++t)
	{
		bool correct = true;
		for (int i = 0; i < discs.size(); ++i)
		{
			if ((discs[i].startPosition + t + i + 1) % discs[i].positionCount != 0)
			{
				correct = false;
				break;
			}
		}

		if (correct)
		{
			cout << "Correct setting at time = " << t << endl;
			break;
		}
	}

	cin.get();
}
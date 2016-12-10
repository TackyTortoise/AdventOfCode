#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

const int searchHigh = 61;
const int searchLow = 17;

regex rgxDigit("[[:digit:]]+");

struct Bot
{
	int high = 0;
	int low = INT_MAX;
	void Print() const
	{
		cout << "low value: " << low << ", high value: " << high << endl;
	}
};

void GiveBotValue(int value, int botNr, map<int, Bot>& bots)
{
	if (value < bots[botNr].low)
	{
		if (bots[botNr].low != INT_MAX)
			bots[botNr].high = bots[botNr].low;
		bots[botNr].low = value;
	}
	else if (value > bots[botNr].high)
	{
		if (bots[botNr].high != 0)
			bots[botNr].low = bots[botNr].high;
		bots[botNr].high = value;
	}
}

void InitializeBots(const vector<string>& instructions, map<int, Bot>& bots)
{
	for (const string instr : instructions)
	{
		std::sregex_iterator next(instr.begin(), instr.end(), rgxDigit);
		std::sregex_iterator end;
		vector<int> sm;
		while (next != end) {
			std::smatch match = *next;
			sm.push_back(stoi(match.str()));
			++next;
		}
		GiveBotValue(sm[0], sm[1], bots);
	}
}

int lastInstructionSize = INT_MAX;

bool GiveInstructions(vector<string>& instructions, map<int, Bot>& bots)
{
	//checking for infinite loop
	if (instructions.size() >= lastInstructionSize)
	{
		cout << "instruction count not getting smaller or reached zero" << endl;
		return true;
	}

	lastInstructionSize = instructions.size();

	for (auto it = instructions.begin(); it != instructions.end();)
	{
		string instr = *it;
		std::sregex_iterator next(instr.begin(), instr.end(), rgxDigit);
		std::sregex_iterator end;
		vector<int> sm;
		while (next != end) {
			std::smatch match = *next;
			sm.push_back(stoi(match.str()));
			++next;
		}
		int botNr = sm[0];
		int lowToNr = sm[1];
		int highToNr = sm[2];

		//check if bot has 2 chips
		if (bots[botNr].high == 0 || bots[botNr].low == INT_MAX)
		{
			++it;
			continue;
		}

		//part 1
		/*if (bots[botNr].high == searchHigh && bots[botNr].low == searchLow)
		{
			cout << "Found bot that compared values: " << bots[botNr].high << " and " << bots[botNr].low << " botnumber: " << botNr << endl;
			return true;
		}*/

		//check whether to go to output or other bot
		int outputPos = instr.find("output");
		bool discardLow = false;
		bool discardHigh = false;
		if (outputPos != string::npos)
		{
			if (outputPos < instr.find("high"))
				discardLow = true;
			else
				discardHigh = true;
		}

		if (instr.find("output", outputPos + 6) != string::npos)
			discardHigh = true;

		//push to other bot
		if (!discardLow)
		{
			GiveBotValue(bots[botNr].low, lowToNr, bots);
		}
		//push to output
		else
		{
			GiveBotValue(bots[botNr].low, 500 + lowToNr, bots);
		}
		//clear value
		bots[botNr].low = INT_MAX;

		//push to other bot
		if (!discardHigh)
		{
			GiveBotValue(bots[botNr].high, highToNr, bots);
		}
		//push to output
		else
		{
			GiveBotValue(bots[botNr].high, 500 + lowToNr, bots);
		}
		//clear value
		bots[botNr].high = 0;

		//erase instruction
		vector<string>::iterator erpos = find(instructions.begin(), instructions.end(), instr);
		it = instructions.erase(erpos);
	}

	return false;
}

void main10()
{
	vector<string> initializeInstructions;
	vector<string> giveInstructions;
	map<int, Bot> bots;

	ifstream input("./Inputs/Input10.txt");
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			if (line.find("value") != string::npos)
				initializeInstructions.push_back(line);
			else if (line.find("gives") != string::npos)
				giveInstructions.push_back(line);
			else
				cout << "Something went wrong with the instruction" << endl;
		}
	}
	else
		cout << "Failed to open Input10.txt" << endl;

	InitializeBots(initializeInstructions, bots);

	while (true)
	{
		if (GiveInstructions(giveInstructions, bots))
			break;
	}

	cout << "output 0 ";
	bots[500].Print();
	cout << endl;

	cout << "output 1 ";
	bots[501].Print();
	cout << endl;

	cout << "output 2 ";
	bots[502].Print();
	cout << endl;

	cout << "done" << endl;
	cin.get();
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <algorithm>
#include <cctype>

using namespace std;

//NEEDS TO BE BUILD IN 64 BIT FOR PART 2

string Foo(string& in, int& openPos, int& closePos)
{
	string result;

	regex rgx("[[:digit:]]+");
	string instruction;
	int copyLength = 0;
	int copyTimes = 0;

	while (openPos != string::npos)
	{
		instruction = in.substr(openPos + 1, closePos - openPos - 1);
		std::sregex_iterator next(instruction.begin(), instruction.end(), rgx);
		std::sregex_iterator end;
		vector<int> sm;
		while (next != end) {
			std::smatch match = *next;
			sm.push_back(stoi(match.str()));
			++next;
		}

		copyLength = sm[0];
		copyTimes = sm[1];

		for (int i = 0; i < copyTimes; ++i)
		{
			result += in.substr(closePos + 1, copyLength);
		}

		in = in.substr(closePos + copyLength + 1);
		openPos = in.find('(');
		closePos = in.find(')');
		result += in.substr(0, openPos);
	}

	return result;
}

size_t Bar(string& in)
{
	int openPos = in.find('(');
	int closePos = in.find(')');
	size_t result = 0;

	result += in.find('(');

	if (openPos == string::npos)
		return in.length();

	in = in.substr(openPos);
	openPos = in.find('(');
	closePos = in.find(')');
	smatch firstInstruction;
	regex instrrgx("\([[:digit:]]+x[[:digit:]]+\)");
	regex digitrgx("[[:digit:]]+");

	regex_search(in, firstInstruction, instrrgx);
	string t = firstInstruction.str();

	int length;
	int times;
	{
		std::sregex_iterator next(t.begin(), t.end(), digitrgx);
		std::sregex_iterator end;
		vector<int> sm;
		while (next != end) {
			std::smatch match = *next;
			sm.push_back(stoi(match.str()));
			++next;
		}

		length = sm[0];
		times = sm[1];
	}

	while (in.find('(') != string::npos)
	{
		result += in.find('(');
		in = in.substr(in.find('('));
		smatch thisInstruction;
		regex_search(in, thisInstruction, instrrgx);
		string e = thisInstruction.str();

		int le;
		int ti;
		{
			std::sregex_iterator next(e.begin(), e.end(), digitrgx);
			std::sregex_iterator end;
			vector<int> sm;
			while (next != end) {
				std::smatch match = *next;
				sm.push_back(stoi(match.str()));
				++next;
			}

			le = sm[0];
			ti = sm[1];
		}

		string operateOn = in.substr(in.find(')') + 1, le);
		size_t r = Bar(operateOn);
		result += r * ti;

		if (operateOn.find('(') != string::npos)
			in = operateOn;
		else
			in = in.substr(in.find(')') + le + 1);
	}
	return result;
}

void main()
{
	ifstream input;
	input.open("./Inputs/Input9.txt");
	string result;
	size_t a = 0;
	if (input.is_open())
	{

		stringstream ss;
		ss << input.rdbuf();
		string in = ss.str();
		in.erase(remove_if(in.begin(), in.end(), [](char c) {return isspace(static_cast<unsigned char>(c)); }), in.end());

		//Part 1
		int openPos = in.find('(');
		int closePos = in.find(')');
		result += in.substr(0, openPos);
		result += Foo(in, openPos, closePos);

		//Part2
		in = ss.str();
		a = Bar(in);
		a += in.length();


	}
	else
		cout << "Failed to open Input9.txt" << endl;

	cout << "Decompressed length: " << result.length() << endl;
	cout << "Decompressed length: " << a << endl;

	cin.get();
}
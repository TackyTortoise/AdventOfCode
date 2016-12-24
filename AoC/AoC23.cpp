#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Registery
{
	char name;
	int value;
};

int HandleInstruction(const string& instruction, vector<Registery>& registeries, vector<string>& instructionVector, const int instructionIndex)
{
	int firstSpace = instruction.find(' ');
	int secondSpace = instruction.find(' ', firstSpace + 1);
	if (instruction.find("cpy") != string::npos)
	{
		string value = instruction.substr(firstSpace + 1, secondSpace - firstSpace - 1);
		char destinyRegister = instruction[instruction.length() - 1];
		if (value.length() == 1 && value[0] >= 'a' && value[0] <= 'd')
		{
			//Copy register value
			registeries[destinyRegister - 'a'].value = registeries[value[0] - 'a'].value;
		}
		else
		{
			//copy integer value
			registeries[destinyRegister - 'a'].value = stoi(value);
		}
	}
	else if (instruction.find("inc") != string::npos)
	{
		++registeries[instruction[instruction.length() - 1] - 'a'].value;
	}
	else if (instruction.find("dec") != string::npos)
	{
		--registeries[instruction[instruction.length() - 1] - 'a'].value;
	}
	else if (instruction.find("jnz") != string::npos)
	{
		string value = instruction.substr(firstSpace + 1, secondSpace - firstSpace - 1);
		string dist = instruction.substr(secondSpace + 1);
		int jumpDistance;
		//jump digit
		if (dist.size() > 1 || dist[0] < 'a' || dist[0] > 'd')
			jumpDistance = stoi(dist);
		//jump registery value
		else
			jumpDistance = registeries[dist[0] - 'a'].value;

		if (value.length() == 1 && value[0] >= 'a' && value[0] <= 'd')
		{
			//check registery value
			if (registeries[value[0] - 'a'].value != 0)
				return jumpDistance;
		}
		else if (stoi(value) != 0)
		{
			return jumpDistance;
		}
	}
	else if (instruction.find("tgl") != string::npos)
	{
		int offset = registeries[instruction[instruction.size() - 1] - 'a'].value;
		//outside of program
		if (instructionIndex + offset > instructionVector.size() - 1)
			return 1;

		int changeIndex = instructionIndex + offset;
		string changeInstr = instructionVector[changeIndex];
		int fs = changeInstr.find(' ');
		int ss = changeInstr.find(' ', fs + 1);

		//one argument instruction
		if (ss == string::npos)
		{
			char argument = changeInstr.back();
			//invalid inc or dec
			if (argument < 'a' || argument > 'd')
				return 1;

			if (changeInstr.find("inc") != string::npos)
				changeInstr = "dec ";
			else
				changeInstr = "inc ";
			changeInstr += argument;
		}

		//two argument instruction
		else
		{
			string firstArg = changeInstr.substr(fs + 1, ss - fs - 1);
			string secondArg = changeInstr.substr(ss + 1);

			if (changeInstr.find("jnz") != string::npos)
			{
				changeInstr = "cpy " + firstArg + ' ' + secondArg;
				if (secondArg.size() > 1 || secondArg[0] < 'a' || secondArg[0] > 'd')
					return 1;
			}
			else
			{
				changeInstr = "jnz " + firstArg + ' ' + secondArg;
			}
		}
		instructionVector[changeIndex] = changeInstr;
	}

	return 1;
}

void main23()
{
	vector<Registery> regs{ { 'a', 12 },{ 'b', 0 },{ 'c', 0 },{ 'd', 0 } };
	vector<string> instructions;
	ifstream input("./Inputs/Input23.txt");
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			instructions.push_back(line);
		}
	}
	else
		cout << "Failed to open Input23.txt";

	for (int i = 0; i < instructions.size();)
	{
		i += HandleInstruction(instructions[i], regs, instructions, i);
	}

	cout << "Value of registery a: " << regs[0].value << endl;
	cin.get();
}
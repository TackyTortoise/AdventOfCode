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

int HandleInstruction(const string& instruction, vector<Registery>& registeries)
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
	if (instruction.find("inc") != string::npos)
	{
		++registeries[instruction[instruction.length() - 1] - 'a'].value;
	}
	if (instruction.find("dec") != string::npos)
	{
		--registeries[instruction[instruction.length() - 1] - 'a'].value;
	}
	if (instruction.find("jnz") != string::npos)
	{
		string value = instruction.substr(firstSpace + 1, secondSpace - firstSpace - 1);
		int jumpDistance = stoi(instruction.substr(secondSpace + 1));
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
	return 1;
}

void main12()
{
	vector<Registery> regs{ {'a', 0}, {'b', 0}, {'c', 1}, {'d', 0} };
	vector<string> instructions;
	ifstream input("./Inputs/Input12.txt");
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			instructions.push_back(line);
		}
	}
	else
		cout << "Failed to open Input12.txt";

	for (int i = 0; i < instructions.size();)
	{
		i += HandleInstruction(instructions[i], regs);
	}

	cout << "Value of registery a: " << regs[0].value << endl;
	cin.get();
}
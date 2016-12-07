#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int GetNextKey(const char direction, int currentKey, const int gridsize)
{
	switch (direction)
	{
	case 'U':
		if ((currentKey - 1) / gridsize > 0)
			currentKey -= gridsize;
		break;

	case 'D':
		if ((currentKey - 1) / gridsize < gridsize - 1)
			currentKey += gridsize;
		break;

	case 'L':
		if ((currentKey - 1) % gridsize > 0)
			--currentKey;
		break;

	case 'R':
		if ((currentKey - 1) % gridsize < gridsize - 1)
			++currentKey;
		break;

	default:
		cout << "Invalid direction in GetNextKey function!" << endl;
		break;
	}

	return currentKey;
}

void main2()
{	
	string keyCombo;

	int gridSize = 3;
	int currentKey = 5;
	std::ifstream inputStream;
	inputStream.open("./Inputs/Input2.txt");
	if (inputStream.is_open())
	{
		string inputString;
		while (getline(inputStream, inputString))
		{
			for (char c : inputString)
			{
				currentKey = GetNextKey(c, currentKey, gridSize);
			}

			keyCombo += to_string(currentKey);
		}
	}
	else
		cout << "Failed to open Input2 file" << endl;

	cout << "The combination of the door is: " << keyCombo << endl;

	cin.get();
}
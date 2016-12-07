#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Key
{
	Key(char value):Value(value){}
	char Value = 0;
	Key* right = nullptr;
	Key* left = nullptr;
	Key* up = nullptr;
	Key* down = nullptr;
};

Key* GetNextKey(const char direction, Key* currentKey, const int gridsize)
{
	Key* nextKey = nullptr;
	switch (direction)
	{
	case 'U':
			nextKey = currentKey->up;
		break;

	case 'D':
			nextKey = currentKey->down;
		break;

	case 'L':
			nextKey = currentKey->left;
		break;

	case 'R':
			nextKey = currentKey->right;
		break;

	default:
		cout << "Invalid direction in GetNextKey function!" << endl;
		break;
	}

	if (nextKey != nullptr)
		return nextKey;
	return currentKey;
}

void main2p2()
{
	string keyCombo;

	Key one('1');
	Key two('2');
	Key three('3');
	Key four('4');
	Key five('5');
	Key six('6');
	Key seven('7');
	Key eight('8');
	Key nine('9');
	Key aKey('A');
	Key bKey('B');
	Key cKey('C');
	Key dKey('D');

	one.down = &three;

	two.right = &three;
	two.down = &six;

	three.up = &one;
	three.left = &two;
	three.right = &four;
	three.down = &seven;

	four.left = &three;
	four.down = &eight;

	five.right = &six;

	six.left = &five;
	six.up = &two;
	six.right = &seven;
	six.down = &aKey;

	seven.up = &three;
	seven.right = &eight;
	seven.left = &six;
	seven.down = &bKey;

	eight.up = &four;
	eight.right = &nine;
	eight.left = &seven;
	eight.down = &cKey;

	nine.left = &eight;

	aKey.up = &six;
	aKey.right = &bKey;

	bKey.up = &seven;
	bKey.right = &cKey;
	bKey.down = &dKey;
	bKey.left = &aKey;

	cKey.up = &eight;
	cKey.left = &bKey;

	dKey.up = &bKey;

	int gridSize = 3;
	Key* currentKey = &five;
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

			keyCombo += currentKey->Value;
		}
	}
	else
		cout << "Failed to open Input2 file" << endl;

	cout << "The combination of the door is: " << keyCombo << endl;

	cin.get();
}
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
int Direction = 0;
/*
* 0 = UP
* 1 = RIGHT
* 2 = DOWN
* 3 = LEFT
*/
int width = 500;
int gridSize = width * width;

vector<int> visited;

void CheckPosition(int cPos)
{
	for (int p : visited)
	{
		if (p == cPos)
		{
			int endRow = cPos % width;
			int endColumn = cPos / width;

			int rowDif = abs(width / 2 - endRow);
			int colDif = abs(width / 2 - endColumn);

			int distanceInBlocks = rowDif + colDif;
			cout << "Visited the same block " << distanceInBlocks << " away from the start position" << endl;
			break;
		}
	}
	visited.push_back(cPos);
}

void HandleInstruction(string in, int& cPos)
{
	char direction = in[0];
	int distance = stoi(in.substr(1));

	//turn
	switch (direction)
	{
	case 'R':
		Direction++;
		Direction %= 4;
		break;
	case 'L':
		Direction--;
		if (Direction < 0)
			Direction = 3;
		break;
	default:
		cout << "invalid input in handleInstruction function" << endl;
		break;
	}

	//walk
	switch (Direction)
	{
	case 0: //UP
		for (int i = 0; i < distance; ++i)
		{
			cPos -= width;
			CheckPosition(cPos);
		}
		//cPos -= distance * width;
		break;
	case 1: //RIGHT
		for (int i = 0; i < distance; ++i)
		{
			++cPos;
			CheckPosition(cPos);
		}
		//cPos += distance;
		break;
	case 2: //DOWN
		for (int i = 0; i < distance; ++i)
		{
			cPos += width;
			CheckPosition(cPos);
		}
		//cPos += distance * width;
		break;
	case 3: //LEFT
		for (int i = 0; i < distance; ++i)
		{
			--cPos;
			CheckPosition(cPos);
		}
		//cPos -= distance;
		break;
	default:
		cout << "Current direction is invalid" << endl;
	}
}


void main1()
{
	ifstream input;
	input.open("./Inputs/Input.txt");

	int startPos = gridSize / 2 + width / 2;
	int currentPos = startPos;
	visited.push_back(currentPos);
	if (input.is_open())
	{
		stringstream stream;
		stream << input.rdbuf();
		string text = stream.str();

		int commaPos = text.find(',');
		while (commaPos != string::npos)
		{
			string instruction = text.substr(0, commaPos);
			text = text.substr(commaPos + 2);
			commaPos = text.find(',');
			HandleInstruction(instruction, currentPos);
		}

		if (text.length() < 4)
			HandleInstruction(text, currentPos);
	}
	else
		cout << "Failed to open input file";

	int startRow = startPos % width;
	int startColumn = startPos / width;

	int endRow = currentPos % width;
	int endColumn = currentPos / width;

	int rowDif = abs(startRow - endRow);
	int colDif = abs(startColumn - endColumn);

	int distanceInBlocks = rowDif + colDif;

	cout << "You are now " << distanceInBlocks << " away from your start position" << endl;
	cin.get();
}
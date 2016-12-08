#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

const int WIDTH = 50;
const int HEIGHT = 6;

void PrintScreen(int * screen)
{
	for (int i = 0; i < WIDTH * HEIGHT; ++i)
	{
		if (i % 5 == 0)
			cout << ' ';
		cout << screen[i];
		if (i % WIDTH == WIDTH - 1)
			cout << endl;
	}
}

void ProcessLine(const string& instruction, int * screen)
{
	regex rgx("[[:digit:]]+");
	std::sregex_iterator next(instruction.begin(), instruction.end(), rgx);
	std::sregex_iterator end;
	vector<int> sm;
	while (next != end) {
		std::smatch match = *next;
		sm.push_back(stoi(match.str()));
		++next;
	}

	if (instruction.find("rect") != string::npos)
	{
		int onWidth = sm[0];
		int onHeight = sm[1];

		for (int r = 0; r < onHeight; ++r)
		{
			for (int c = 0; c < onWidth; ++c)
			{
				screen[r * WIDTH + c] = 1;
			}
		}
	}
	else if (instruction.find("row") != string::npos)
	{
		int row = sm[0];
		int offset = sm[1];


		for (int t = 0; t < offset; ++t)
		{
			int originalLine[WIDTH];
			for (int i = 0; i < WIDTH; ++i)
			{
				originalLine[i] = screen[row * WIDTH + i];
			}

			for (int i = 0; i < WIDTH; ++i)
			{
				if (i == 0)
				{
					screen[row * WIDTH + i] = originalLine[WIDTH - 1];
					continue;
				}

				screen[row * WIDTH + i] = originalLine[i - 1];
			}
		}
	}
	else if (instruction.find("column") != string::npos)
	{
		int column = sm[0];
		int offset = sm[1];

		for (int t = 0; t < offset; ++t)
		{
			int originalCol[HEIGHT];
			for (int i = 0; i < HEIGHT; ++i)
			{
				originalCol[i] = screen[i * WIDTH + column];
			}

			for (int i = 0; i < HEIGHT; ++i)
			{
				if (i == 0)
				{
					screen[i * WIDTH + column] = originalCol[HEIGHT - 1];
					continue;
				}

				screen[i * WIDTH + column] = originalCol[i - 1];
			}
		}
	}
}

void main8()
{
	int screen[WIDTH * HEIGHT];
	for (int i = 0; i < WIDTH * HEIGHT; ++i)
		screen[i] = 0;

	fstream input;
	input.open("./Inputs/Input8.txt");
	if (input.is_open())
	{
		string line;
		while (getline(input, line))
		{
			ProcessLine(line, screen);
			//cout << line << endl;
			//PrintScreen(screen);
			//cout << endl;
		}
	}
	else
		cout << "Failed to open Input8.txt" << endl;

	PrintScreen(screen);

	int pixelsOn = 0;
	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		if (screen[i] == 1)
			++pixelsOn;
	}

	cout << "Amount of pixels that are on: " << pixelsOn << endl;
	cin.get();
}
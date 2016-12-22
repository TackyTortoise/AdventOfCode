#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

typedef unsigned int uint;

const int GRID_WIDTH = 35;
const int GRID_HEIGHT = 29;

struct GridNode
{
	GridNode() :Size(0), Used(0) {}
	GridNode(uint s, uint u) :Size(s), Used(u) {}
	uint Size = 0;
	uint Used = 0;
	uint GetAvailableSpace() const { return Size - Used; }
	uint GetUsePercentage() const { return static_cast<float>(Used) / Size * 100; }
};

void PrintGrid(const vector<GridNode>& grid)
{
	for (int i = 0; i < grid.size(); ++i)
	{
		if (i == GRID_WIDTH - 1)
			cout << 'G';
		else
		{
			if (grid[i].Used == 0)
				cout << '_';
			else if (grid[i].GetUsePercentage() > 85 || grid[i].Size > 100)
				cout << '#';
			else
				cout << '.';
		}
		if (i % GRID_WIDTH == GRID_WIDTH - 1)
			cout << endl;
	}
}

void main()
{
	vector<GridNode> grid(GRID_WIDTH * GRID_HEIGHT);

	regex rgxDigit("\\d+");

	ifstream inputFile("Inputs/Input22.txt");
	if (inputFile.is_open())
	{
		string line;
		while (getline(inputFile, line))
		{
			if (line[0] == '/')
			{
				std::sregex_iterator next(line.begin(), line.end(), rgxDigit);
				std::sregex_iterator end;
				vector<int> sm;
				while (next != end) {
					std::smatch match = *next;
					sm.push_back(stoi(match.str()));
					++next;
				}

				int gridX = sm[0];
				int gridY = sm[1];
				int size = sm[2];
				int used = sm[3];
				grid[gridX + gridY * GRID_WIDTH].Size = size;
				grid[gridX + gridY * GRID_WIDTH].Used = used;
			}
		}
	}
	else
		cout << "Failed to open Input22.txt" << endl;

	inputFile.close();

	uint viableCounter = 0;
	for (int i = 0; i <= grid.size(); ++i)
	{
		GridNode nodeA = grid[i];
		if (nodeA.Used == 0)
			continue;
		for (int j = 0; j < grid.size(); ++j)
		{
			if (i == j)
				continue;
			GridNode nodeB = grid[j];
			if (nodeA.Used < nodeB.GetAvailableSpace())
				++viableCounter;
		}
	}

	cout << "number of viable nodes: " << viableCounter << endl;

	PrintGrid(grid);
	
	//part2
	//26 initial steps to move empty space next to target data
	//33 * 5 to move data to x = 1
	//move data 1 more time
	//26 + 33 * 5 + 1 = 192	 

	cin.get();
}
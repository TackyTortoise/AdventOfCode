#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Triangle
{
	Triangle(int x, int y, int z) : L1(x), L2(y), L3(z)
	{}
	int L1 = 0;
	int L2 = 0;
	int L3 = 0;
};

int CheckTriangles(const vector<Triangle>& p)
{
	int possibleCount = 0;
	for (int cR = 0; cR < p.size(); cR += 3)
	{
		int one = p[cR].L1;
		int two = p[cR + 1].L1;
		int three = p[cR + 2].L1;
		if (one + two > three && two + three > one && three + one > two)
			++possibleCount;

		one = p[cR].L2;
		two = p[cR + 1].L2;
		three = p[cR + 2].L2;
		if (one + two > three && two + three > one && three + one > two)
			++possibleCount;

		one = p[cR].L3;
		two = p[cR + 1].L3;
		three = p[cR + 2].L3;
		if (one + two > three && two + three > one && three + one > two)
			++possibleCount;
	}
	return possibleCount;
}

void main32()
{
	vector<Triangle> pointList;
	ifstream input;
	input.open("./Inputs/Input3.txt");
	string line;
	int count = 0;
	if (input.is_open())
	{
		while (getline(input, line))
		{
			int p[3];
			int currentIndex = 0;
			string currenNum;
			for (char c : line)
			{
				if (c != ' ')
					currenNum += c;
				else
				{
					if (currenNum != "")
					{
						p[currentIndex] = stoi(currenNum);
						++currentIndex;
						currenNum = "";
					}
				}
			}
			p[currentIndex] = stoi(currenNum);
			pointList.push_back(Triangle(p[0], p[1], p[2]));
		}
	}
	else
		std::cout << "Failed to open file Input3.txt" << endl;

	std::cout << "There are " << CheckTriangles(pointList) << " possible triangles in this set" << endl;

	std::cin.get();
}
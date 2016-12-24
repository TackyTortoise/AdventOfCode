#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <fstream>

using namespace std;

const int FavNumber = 1350;
const int SIZE = 50;

struct Point
{
	Point(int X, int Y, bool Open) : x(X), y(Y), open(Open) {}
	int x = 0;
	int y = 0;
	bool open = false;

	float GScore = 0.f;
	float HScore = 0.f;
	float FScore = 0.f;
	float TileCost = 0.f;
	Point* parent = nullptr;
};

bool GetWallOrOpen(int x, int y)
{
	int num = x*x + 3 * x + 2 * x*y + y + y*y;
	num += FavNumber;
	int bitCount = 0;
	for (int i = 0; i < 32; ++i)
	{
		if (num >> i & 1)
			++bitCount;
	}

	//Open
	if (bitCount % 2 == 0)
		return true;
	//Closed
	else
		return false;
}

class AStarGrid
{
public:
	AStarGrid()
	{
		for (int r = 0; r < SIZE; ++r)
		{
			for (int c = 0; c < SIZE; ++c)
			{
				Elements.push_back(new Point(c, r, GetWallOrOpen(c, r)));
			}
		}

		//Draw();
	}

	~AStarGrid()
	{
		for (auto e : Elements)
		{
			delete e;
			e = nullptr;
		}
		Elements.clear();
	}

	Point* GetElement(int x, int y)
	{
		return Elements[y * SIZE + x];
	}

	void ClearParents()
	{
		for (auto e : Elements)
		{
			e->parent = nullptr;
		}
	}

	vector<Point*> GetNeighbours(Point* p)
	{
		vector<Point *> result;
		int PointIndex;
		auto found = std::find(Elements.begin(), Elements.end(), p);
		int index = found - Elements.begin();

		//Up
		if (p->y > 0 && Elements[index - SIZE]->open)
			result.push_back(Elements[index - SIZE]);

		//Down
		if (p->y < SIZE - 1 && Elements[index + SIZE]->open)
			result.push_back(Elements[index + SIZE]);

		//Left
		if (p->x > 0 && Elements[index - 1]->open)
			result.push_back(Elements[index - 1]);

		//Right
		if (p->x < SIZE - 1 && Elements[index + 1]->open)
			result.push_back(Elements[index + 1]);

		return result;
	}

	void Draw()
	{
		for (int i = 0; i < Elements.size(); ++i)
		{
			char c = Elements[i]->open ? '.' : '#';
			cout << c;
			if (i % SIZE == SIZE - 1)
				cout << endl;
		}
	}
	vector<Point *>Elements;
};

class PathFinder
{
public:
	const std::vector<Point*>& FindPath(Point* startElement, Point* endElement, AStarGrid* grid)
	{
		ClearContainers();
		if (startElement == endElement)
		{
			m_vPath.push_back(startElement);
			return m_vPath;
		}

		deque<Point*> openList;
		deque<Point*> closedList;

		Point* currentPoint = nullptr;
		openList.push_back(startElement);

		while (openList.size() != 0)
		{
			//get node with lowest f score
			float lowestFScore = numeric_limits<float>::max();

			for (auto el : openList)
			{
				if (el->FScore < lowestFScore)
				{
					currentPoint = el;
					lowestFScore = el->FScore;
				}
			}

			//pop current of open list and push in closed list
			openList.erase(std::remove_if(openList.begin(), openList.end(),
				[currentPoint](const Point* e) { return currentPoint == e; }));

			closedList.push_back(currentPoint);

			//retrieve neighboors
			auto nb = grid->GetNeighbours(currentPoint);

			//if end is in neighbours return
			if (find(nb.begin(), nb.end(), endElement) != nb.end())
			{
				endElement->parent = currentPoint;
				openList.clear();
				break;
			}

			//else go over all neighbours
			for (auto n : nb)
			{
				if (find(closedList.begin(), closedList.end(), n) != closedList.end()) {continue;}
				else
				{
					//if node not in open list, compute score and add it
					if (find(openList.begin(), openList.end(), n) == openList.end())
					{
						//set parent to current element
						n->parent = currentPoint;

						//calculate h, g and f score
						//g = current.g + cost(dist current and this) ---> OR ues GetTileCost() if using hard value (needs extra support for diagonal movement)
						float cost = Euclidean(abs(currentPoint->x - n->x), abs(currentPoint->y - n->y));
						n->GScore = n->parent->GScore + cost;

						//h = distance this and goal
						n->HScore = Euclidean(abs(n->x - endElement->x), abs(n->y - endElement->y));

						//f = g + h
						n->FScore = n->GScore + n->HScore;

						//add to openlist
						openList.push_back(n);
					}
				}
			}
		}

		m_vPath.push_back(endElement);
		m_vPath.push_back(currentPoint);
		Point* nextElement = currentPoint->parent;
		while (nextElement != nullptr)
		{
			//part 2 make faster
			if (m_vPath.size() > 100)
				break;
			m_vPath.push_back(nextElement);
			nextElement = nextElement->parent;
		}
		return m_vPath;
	}
	void ClearContainers()
	{
		m_vPath.clear();
	}

private:
	std::vector<Point*> m_vPath;
	inline float HeuristicManhatten(int x, int y)
	{
		return float(x + y);
	}
	inline float Euclidean(int x, int y)
	{
		return float(sqrt(x*x + y*y));
	}
};

void main()
{
	AStarGrid* grid = new AStarGrid();
	//grid->Draw();
	PathFinder* finder = new PathFinder();
	auto n = grid->GetNeighbours(grid->GetElement(0, 0));
	auto path = finder->FindPath(grid->GetElement(1, 1), grid->GetElement(31, 39), grid);
	grid->ClearParents();

	ofstream output("Output.txt");
	int counter = 0;
	for (int i = 0; i < SIZE * SIZE; ++i)
	{
		if (!grid->Elements[i]->open)
			continue;
		path = finder->FindPath(grid->GetElement(0, 0), grid->Elements[i], grid);
		grid->ClearParents();
		if (path.size() <= 50)
		{
			++counter;
			output << "Reached Point: " << grid->Elements[i]->x << ", " << grid->Elements[i]->y << endl;
		}
	}
	
	//cout << "steps taken: " << path.size() - 1 << endl;
	cout << "Positions reached in 50 steps at most " << counter << endl;
	cin.get();
	output.close();

	delete grid;
	grid = nullptr;

	delete finder;
	grid = nullptr;

}
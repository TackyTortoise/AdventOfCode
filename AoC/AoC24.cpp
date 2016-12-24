#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <cctype>

using namespace std;

const int WIDTH = 183;
const int HEIGHT = 45;
int shortestPathLength = INT_MAX;

struct Point
{
	Point(int X, int Y, bool Open) : x(X), y(Y), open(Open) {}
	int x = 0;
	int y = 0;
	bool open = false;

	float GScore = 0.f;
	float HScore = 0.f;
	float FScore = 0.f;
	Point* parent = nullptr;

	bool operator== (Point other) const
	{
		return x == other.x && y == other.y && open == other.open;
	}
};

ostream& operator<<(ostream& s, const Point p)
{
	return s << "[" << p.x << ", " << p.y << "]";
}

class AStarGrid
{
public:
	AStarGrid(const vector<Point*>& elements) : Elements(elements)
	{
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
		return Elements[y * WIDTH + x];
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
		if (p->y > 0 && Elements[index - WIDTH]->open)
			result.push_back(Elements[index - WIDTH]);

		//Down
		if (p->y < HEIGHT - 1 && Elements[index + WIDTH]->open)
			result.push_back(Elements[index + WIDTH]);

		//Left
		if (p->x > 0 && Elements[index - 1]->open)
			result.push_back(Elements[index - 1]);

		//Right
		if (p->x < WIDTH - 1 && Elements[index + 1]->open)
			result.push_back(Elements[index + 1]);

		return result;
	}

	void Draw()
	{
		for (int i = 0; i < Elements.size(); ++i)
		{
			char c = Elements[i]->open ? '.' : '#';
			cout << c;
			if (i % WIDTH == WIDTH - 1)
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
				if (find(closedList.begin(), closedList.end(), n) != closedList.end())
				{
					continue;
				}
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

		m_vPath.push_back(endElement);
		m_vPath.push_back(currentPoint);
		Point* nextElement = currentPoint->parent;
		while (nextElement != nullptr)
		{
			//part 2 make faster
			if (m_vPath.size() > shortestPathLength + 1)
				nextElement = nullptr;
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
	inline float TestHeuristic(int x ,int y)
	{
		return float(sqrt(x + y) * (x + y));
	}
	inline float Octile(int x, int y)
	{
		auto f = sqrt(2) - 1;
		return float((x < y) ? f * x + y : f * y + x);
	}
	inline float Euclidean(int x, int y)
	{
		return float(sqrt(x*x + y*y));
	}
	inline float Chebyshev(int x, int y)
	{
		return std::max(x, y);
	}
};

bool operator< (Point p1, Point p2)
{
	if (p1.x != p2.x)
		return p1.x < p2.x;

	if (p1.y != p2.y)
		return p1.y < p2.y;

	return p1.open;
}

struct myPath
{
	myPath(Point s, Point e, unsigned int l) :start(s), end(e), length(l) {}
	Point start;
	Point end;
	unsigned int length;
};

void main24()
{
	//read input / initialize points
	ifstream inputFile("Inputs/Input24.txt");
	vector<Point*> points;
	points.resize(WIDTH * HEIGHT);
	int index = 0;

	vector<Point> pointsToVisit;

	if (inputFile.is_open())
	{
		string line;
		while (getline(inputFile, line))
		{
			for (char c : line)
			{
				points[index] = new Point(index % WIDTH, index / WIDTH, c == '#' ? false : true);
				if (std::isdigit(c))
					pointsToVisit.push_back(Point(index % WIDTH, index / WIDTH, true));
				++index;
			}
		}
	}
	else
		cout << "Failed to open Input24.txt" << endl;

	//set up grid
	AStarGrid* grid = new AStarGrid(points);

	//ofstream output("Output.txt");
	//for (int i = 0; i < grid->Elements.size(); ++i)
	//{
	//	char c = grid->Elements[i]->open ? '.' : '#';
	//	output << c;
	//	if (i % WIDTH == WIDTH - 1)
	//		output << endl;
	//}
	//output.close();

	//grid->Draw();
	PathFinder finder;

	//calculate distances between points
	vector<myPath> myPaths;
	for (int i = 0; i < pointsToVisit.size(); ++i)
	{
		for (int j = i + 1; j < pointsToVisit.size(); ++j)
		{
			if (pointsToVisit[i].x == 53 && pointsToVisit[j].x == 141)
				int t = 0;
			auto foundPath = finder.FindPath(grid->GetElement(pointsToVisit[i].x, pointsToVisit[i].y), grid->GetElement(pointsToVisit[j].x, pointsToVisit[j].y), grid);
			grid->ClearParents();
			myPaths.push_back(myPath(pointsToVisit[i], pointsToVisit[j], foundPath.size() - 1));
		}
	}

	//get rid of first point to visit, to later always put it back in first place
	Point startPoint = pointsToVisit[0];
	pointsToVisit.erase(pointsToVisit.begin());

	//vector for permutations
	vector<int> perm(pointsToVisit.size());
	for (int i = 0; i < pointsToVisit.size(); ++i)
		perm[i] = i;

	vector<Point> shortestPath;
	while (next_permutation(perm.begin(), perm.end()))
	{
		//set up current desired path
		vector<Point> path;
		for (int c = 0; c < perm.size(); ++c)
		{
			path.push_back(pointsToVisit[perm[c]]);
		}
		//insert where bot begins
		path.insert(path.begin(), startPoint);
		path.push_back(startPoint);

		//calculate path distance
		int totalPathLength = 0;
		for (int i = 0; i < path.size() - 1; ++i)
		{
			for (auto p : myPaths)
			{
				if ((p.start == path[i] && p.end == path[i + 1]) || (p.start == path[i + 1] && p.end == path[i]))
				{
					totalPathLength += p.length;
					break;
				}
			}
		}

		//check if shortest
		if (totalPathLength < shortestPathLength)
		{
			shortestPathLength = totalPathLength;
			shortestPath = path;
		}
	}

	cout << "shortest path found: " << shortestPathLength << endl;

	for (int i = 0; i < shortestPath.size() - 1; ++i)
	{
		int l = 0;
		for (auto p : myPaths)
		{
			if ((p.start == shortestPath[i] && p.end == shortestPath[i + 1]) || (p.start == shortestPath[i + 1] && p.end == shortestPath[i]))
			{
				l += p.length;
				break;
			}
		}
		cout << shortestPath[i] << " -> " << shortestPath[i + 1] << " length: " << l << endl;
	}
	cout << endl;

	inputFile.close();
	cin.get();
}
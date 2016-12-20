#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <list>

using namespace std;

struct Elf
{
	int number;
	int presents;
};

void part1()
{
	clock_t begin = clock();
	vector<Elf> elves(3017957);
	for (int i = 0; i < elves.size(); ++i)
	{
		elves[i].number = i + 1;
		elves[i].presents = 1;
	}
	Elf* lastElf = nullptr;
	bool stopLoop = false;
	while (!stopLoop)
	{
		Elf* ptr = elves.data();
		for (int i = 0; i < elves.size(); ++i)
		{
			if (ptr[i].presents == 0)
			{
				continue;
			}

			bool foundNext = false;
			for (int e = i + 1; e < elves.size(); ++e)
			{
				if (ptr[e].presents != 0)
				{
					ptr[i].presents += ptr[e].presents;
					ptr[e].presents = 0;
					foundNext = true;
					break;
				}
			}

			if (!foundNext)
			{
				for (int e = 0; e < i; ++e)
				{
					if (ptr[e].presents != 0)
					{
						ptr[i].presents += ptr[e].presents;
						ptr[e].presents = 0;
						break;
					}
					if (e == i - 1)
					{
						stopLoop = true;
						lastElf = ptr + i;
					}
				}
			}
		}
	}

	std::cout << "Elf " << lastElf->number << " gets all the presents: " << lastElf->presents << endl;
	clock_t end = clock();
	std::cout << "Time pointer function " << double(end - begin) / CLOCKS_PER_SEC << endl;

	std::cout << std::endl;
}

struct Node
{
	Node(int num, Node* previous, Node* nextNode)
	{
		//elf.number = num;
		//elf.presents = presentCount;
		number = num;
		prev = previous;
		next = nextNode;
	}
	int number;
	Node* prev = nullptr;
	Node* next = nullptr;

	Node* Advance(int count)
	{
		Node* result = this;
		for (int i = 0; i < count; ++i)
		{
			result = result->next;
		}
		return result;
	}
};

void ListMethod2(int num)
{
	clock_t begin = clock();
	
	const int ELFCOUNT = num;
	Node* start = new Node(1, nullptr, nullptr);
	Node* current = start;
	for (int i = 2; i < ELFCOUNT + 1; ++i)
	{
		current->next = new Node(i, current, nullptr);
		current = current->next;
	}
	cout << "Done initializing list" << endl;
	current->next = start;
	start->prev = current;

	current = start->prev;
	int halfcircle = (ELFCOUNT) / 2;
	auto opposite = start->prev->prev->Advance(halfcircle + ELFCOUNT % 2);
	int alternator = ELFCOUNT % 2 == 0 ? 1 : 0;
	int elvesLeft = ELFCOUNT;
	while (elvesLeft > 1)
	{
		current = current->next;
		opposite = opposite->Advance(1 + alternator);
		++alternator %= 2;

		//remove from linked list
		opposite->prev->next = opposite->next;
		opposite->next->prev = opposite->prev;
		--elvesLeft;
	}

	clock_t end = clock();
	double diff = double(end - begin) / CLOCKS_PER_SEC;
	cout << "List method time: " << diff << endl;
	cout << "Elf " << current->number << endl;
}

void main19()
{
	part1();
	ListMethod2(3017957);
	cin.get();
}
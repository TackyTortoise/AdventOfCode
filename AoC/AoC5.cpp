#include <iostream>
#include <sstream>
#include "md5wrapper.h"

using namespace std;

void main5()
{
	md5wrapper md5;
	string password = "--------";
	string input = "uqwqemis";
	int passFound = 0;
	long index = 0;
	while (passFound < 8)
	{
		stringstream check;
		check << input << index;
		string hash = md5.getHashFromString(check.str());
		if (hash.substr(0,5) == "00000")
		{
			int position = hash[5] - '0';
			cout << "Found position " << position << " letter " << hash[6] << endl;
			if (position <= 7)
			{
				if (password[position] == '-')
				{
					password[position] = hash[6];
					++passFound;
					cout << "Found valid character " << hash[5] << endl;
				}
			}
		}

		index++;
	}
	cout << "Passkey is: " << password << endl;
	cin.get(); 
}
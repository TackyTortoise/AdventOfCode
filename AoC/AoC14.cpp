#include "md5wrapper.h"
#include <string>
#include <iostream>
#include <map>

using namespace std;

void main14()
{
	map<int, string> hashes;
	md5wrapper md5;
	string input = "ihaygndm";
	int validHashes = 0;
	for (int i = 10; i < INT_MAX; ++i)
	{
		string h = input + to_string(i);
		string hash;
		//produce hash if it doesn't exist yet
		if (hashes.find(i) == hashes.end())
		{
			hash = md5.getHashFromString(h);
			for (int p = 0; p < 2016; ++p)
				hash = md5.getHashFromString(hash);
			hashes[i] = hash;
		}
		else
			hash = hashes[i];

		for (int e = 0; e < hash.size() - 2; ++e)
		{
			//three consecutive same numbers
			if (hash[e] == hash[e + 1] && hash[e] == hash[e + 2])
			{
				string nums;
				for (int t = 0; t < 5; ++t)
					nums += hash[e];
				bool valid = false;
				//check next thousand hashes
				for (int c = 1; c < 1000; ++c)
				{
					string h2 = input + to_string(i + c);
					string hash2;
					if (hashes.find(i + c) == hashes.end())
					{
						hash2 = md5.getHashFromString(h2);
						for (int p = 0; p < 2016; ++p)
							hash2 = md5.getHashFromString(hash2);
						hashes[i + c] = hash2;
					}
					else
						hash2 = hashes[i + c];
					if (hash2.find(nums) != string::npos)
					{
						valid = true;
						break;
					}
				}
				if (valid)
				{
					++validHashes;
					cout << "found key at position " << i << endl;
					break;
				}
				break;
			}
		}

		if (validHashes == 64)
		{
			cout << i << endl;
			break;
		}
	}

	cin.get();
}
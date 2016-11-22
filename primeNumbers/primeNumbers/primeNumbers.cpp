#include "stdafx.h"
#include <iostream>
#include <set>
#include <vector>
#include <set>
#include <iterator>
#include "processPrimeNumbers.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "invalid arguents count\n" << "usage: primenumbers.exe <your upper bound>\n";
		return 1;
	}
	int userUpperBound = atoi(argv[1]);
	if (!IsCorrectUpperBound(userUpperBound))
	{
		cout << "You entered the wrong upper limit. It should be in range from 2 to 100.000.000\n";
		return 1;
	}
	set<unsigned> primeNumbersSet = GeneratePrimeNumbersSet(userUpperBound);
	copy(primeNumbersSet.begin(), primeNumbersSet.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	cout << primeNumbersSet.size() << endl;
    return 0;
}


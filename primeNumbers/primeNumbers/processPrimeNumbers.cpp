#include "stdafx.h"
#include <set>
#include <vector>
#include <iterator>
#include "processPrimeNumbers.h"

using namespace std;

static const int UPPER_BOUND = 100000000;
static const int MIN_PRIME_NUMBER = 2;

bool IsCorrectUpperBound(unsigned userUpperBound)
{
	return ((userUpperBound >= MIN_PRIME_NUMBER) && (userUpperBound <= UPPER_BOUND));
}

void FindPrimeNumbers(unsigned userUpperBound, vector<bool> &primeNumbers)
{
	int limit = int(sqrt(userUpperBound));
	size_t primeNumbersSize = primeNumbers.size();
	for (size_t i = MIN_PRIME_NUMBER; i < primeNumbersSize; i += MIN_PRIME_NUMBER)
	{
		primeNumbers[i] = false;
	}
	for (int i = 1; i < limit; i += MIN_PRIME_NUMBER)
	{
		if (primeNumbers[i])
		{
			for (size_t j = i; j < primeNumbersSize; j += i + MIN_PRIME_NUMBER)
			{
				if ((primeNumbers[j]) && (j != i))
				{
					primeNumbers[j] = false;
				}
			}
		}
	}
}

set<unsigned> AddElementsiInPrimeNumbersSet(unsigned userUpperBound, vector<bool> &primeNumbers)
{
	set<unsigned> primeNumbersSet;
	size_t primeNumbersSize = primeNumbers.size();
	for (size_t i = 0; i < primeNumbersSize; ++i)
	{
		if (primeNumbers[i])
		{
			primeNumbersSet.emplace(i + MIN_PRIME_NUMBER);
		}
	}
	return primeNumbersSet;
}

set<unsigned> GeneratePrimeNumbersSet(unsigned userUpperBound)
{
	vector<bool> primeNumbers(userUpperBound - 1, true);
	FindPrimeNumbers(userUpperBound, primeNumbers);

	return AddElementsiInPrimeNumbersSet(userUpperBound, primeNumbers);
}
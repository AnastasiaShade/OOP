#pragma once

#include "stdafx.h"
#include <set>
#include <vector>

using namespace std;


bool IsCorrectUpperBound(const unsigned userUpperBound);

void FindPrimeNumbers(unsigned userUpperBound, vector<bool> &primeNumbers);
set<unsigned> AddElementsiInPrimeNumbersSet(unsigned userUpperBound, vector<bool> &primeNumbers);
set<unsigned> GeneratePrimeNumbersSet(unsigned userUpperBound);
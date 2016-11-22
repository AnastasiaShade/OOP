#pragma once
#include "stdafx.h"
#include <vector>

using namespace std;

vector<double> ReadElements();
double CalculateNonNegativeNumbersSum(vector<double> &elements);
bool IsEven(int position);
void ProcessElements(vector<double> &elements);
void SortElements(vector<double> &elements);
void PrintElements(vector<double> const& elements);

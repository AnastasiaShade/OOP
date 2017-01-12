#include "stdafx.h"
#include "processVector.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <cmath>
#include <algorithm>

using namespace std;

vector<double> ReadElements()
{
	vector<double> elements;
	double numbers;
	while (cin >> numbers)
	{
		elements.insert(elements.end(), numbers);
	}
	return elements;
}

double CalculateNonNegativeNumbersSum(vector<double> &elements)
{
	double sum = 0;
	for (vector<double>::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		if (*it > 0)
		{
			sum += round((*it) * 1000)/1000;
		}
	}
	return sum;
}

bool IsEven(int position)
{
	return position % 2 == 0;
}

void ProcessElements(vector<double> &elements)
{
	double sumOfNonNegativeNumbers = CalculateNonNegativeNumbersSum(elements);
	for (size_t position = 0; position < elements.size(); ++position)
	{
		IsEven(position) ? elements[position] *= 2 : elements[position] -= sumOfNonNegativeNumbers;
	}
}

void SortElements(vector<double> &elements)
{
	sort(elements.begin(), elements.end());
}

void PrintElements(vector<double> &elements)
{
	copy(elements.begin(), elements.end(), ostream_iterator<double>(cout, " "));
	cout << "\n";
}
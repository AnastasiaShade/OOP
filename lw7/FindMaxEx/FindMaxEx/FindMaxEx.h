#pragma once
#include "stdafx.h"
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}
	T max = arr.front();
	for (auto it = arr.begin() + 1; it != arr.end(); ++it)
	{
		if (less(max, *it))
		{
			max = *it;
		}
	}
	maxValue = max;
	return true;
}
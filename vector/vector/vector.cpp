#include "stdafx.h"
#include "processVector.h"
#include <vector>

using namespace std;

int main()
{
	auto elements = ReadElements();
	ProcessElements(elements);
	SortElements(elements);
	PrintElements(elements);
    return 0;
}


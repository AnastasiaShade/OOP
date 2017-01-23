// StringStack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "StringStack.h"
#include <cassert>

void DoSomething(const CStringStack & s)
{
	CStringStack s1;
	s1 = s;
}

int main()
{
	CStringStack s1;
	s1.Push("one");
	s1.Pop();

	CStringStack s2;
	s2.Push("hello");

	s2 = s1;
	assert(s2.GetSize() == 0);

	return 0;
}

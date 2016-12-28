// Stack.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "MyStack.h"
#include <iostream>

int main()
{
	CMyStack<int> stack;
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Push(4);
	stack.Push(5);
	CMyStack<int> otherStack = CMyStack<int>();
	std::cout << stack.GetSize() << "\n";
	std::cout << otherStack.GetSize() << "\n";
    return 0;
}


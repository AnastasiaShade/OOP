#pragma once
#include "stdafx.h"
#include <memory>

template <typename T>
class CMyStack
{
	struct Stack
	{
		Stack(T const& value, Stack *next)
			: value(value)
			, next(next)
		{
		}
		T value;
		Stack *next;
	};
public:
	CMyStack()
		: m_top(nullptr)
		, m_size(0)
	{
	};

	CMyStack(CMyStack &copiedStack)
	{
		Stack *tmp = copiedStack.m_top;
		Stack *currentTop = new Stack(tmp->value, nullptr);
		m_top = currentTop;
		tmp = tmp->next;
		while (tmp != nullptr)
		{
			currentTop->next = new Stack(tmp->value, nullptr);
			currentTop = currentTop->next;
			tmp = tmp->next;
		}
		m_size = copiedStack.GetSize();
	};

	CMyStack(CMyStack && removedStack)
		: m_top(nullptr)
		, m_size(0)
	{
		m_top = removedStack.m_top;
		m_size = removedStack.m_size;
		removedStack.m_top = nullptr;
		removedStack.m_size = 0;
	};

	~CMyStack()
	{
		Clear();
	};

	void Push(T const& element)
	{
		Stack *tmp = m_top;
		m_top = new Stack(element, tmp);
		++m_size;
	};

	void Pop()
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}

		Stack *tmp = m_top;
		m_top = m_top->next;
		delete tmp;
		--m_size;
	};

	T GetTopElement()const
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}
		return m_top->value;
	};


	void Clear()
	{
		while (m_top != nullptr)
		{
			Pop();
		}
	};

	bool IsEmpty()const
	{
		return m_top == nullptr;
	};

	size_t GetSize()const
	{
		return m_size;
	};

	CMyStack& operator=(CMyStack && copiedStack)
	{
		if (std::addressof(copiedStack) != this)
		{
			Stack *tmp = copiedStack.m_top;
			Stack *currentTop = new Stack(tmp->value, nullptr);
			m_top = currentTop;
			tmp = tmp->next;
			while (tmp != nullptr)
			{
				currentTop->next = new Stack(tmp->value, nullptr);
				currentTop = currentTop->next;
				tmp = tmp->next;
			}
			m_size = copiedStack.GetSize();
		}
		return *this;
	};

	CMyStack& operator=(CMyStack & removedStack)
	{
		if (std::addressof(removedStack) != this)
		{
			m_top = removedStack.m_top;
			m_size = removedStack.m_size;
			removedStack.m_top = nullptr;
			removedStack.m_size = 0;
		}
		return *this;
	};

private:
	Stack *m_top;
	size_t m_size;
};


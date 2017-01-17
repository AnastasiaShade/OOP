#pragma once
#include "stdafx.h"

template <typename T>
class CMyStack
{
	struct Node
	{
		Node(T const& value, std::shared_ptr<Node> const& next)
			: value(value)
			, next(next)
		{
		}
		T value;
		std::shared_ptr<Node> next;
	};
public:
	CMyStack()
		: m_top(nullptr)
		, m_size(0)
	{
	};

	CMyStack(CMyStack const& copiedStack) // потенциальная утечка памяти
	{
		if (copiedStack.m_top != nullptr)
		{
			std::shared_ptr<Node> temporaryStack = copiedStack.m_top;
			std::shared_ptr<Node> stackTop;
			while (temporaryStack != nullptr)
			{
				stackTop = std::make_shared<Node>(temporaryStack->value, nullptr);
				stackTop = stackTop->next;
				temporaryStack = temporaryStack->next;
			}
		}
		m_top = copiedStack.m_top;
		m_size = copiedStack.m_size;
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
		std::shared_ptr<Node> tmp = m_top;
		m_top = std::make_shared<Node>(element, tmp);
		++m_size;
	};

	void Pop()
	{
		if (IsEmpty())
		{
			throw std::logic_error("Stack is empty");
		}

		std::shared_ptr<Node> tmp = m_top;
		m_top = m_top->next;
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

	CMyStack& operator=(CMyStack & copiedStack) // дублирование кода, потенциальная утечка памяти
	{
		if (std::addressof(copiedStack) != this)
		{
			CMyStack<T> temporaryStack(copiedStack);
			std::swap(*this, temporaryStack);
		}
		return *this;
	};

	CMyStack& operator=(CMyStack && removedStack)
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
	std::shared_ptr<Node> m_top;
	size_t m_size;
};

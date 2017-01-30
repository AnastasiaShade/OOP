#include "stdafx.h"
#include "StringStack.h"


CStringStack::CStringStack()
	: m_top(nullptr)
	, m_size(0)
{
}

CStringStack::~CStringStack()
{
	Clear();
}

CStringStack::CStringStack(CStringStack const& copiedStack)
	: m_top(nullptr)
	, m_size(0)
{
	if (copiedStack.m_top != nullptr)
	{
		try
		{
			std::shared_ptr<Node> temporaryStack = copiedStack.m_top;
			m_top = std::make_shared<Node>(temporaryStack->value, nullptr);
			std::shared_ptr<Node> stackTop = m_top;
			while (temporaryStack->next != nullptr)
			{
				stackTop->next = std::make_shared<Node>(temporaryStack->next->value, nullptr);
				stackTop = stackTop->next;
				temporaryStack = temporaryStack->next;
			}
			m_size = copiedStack.m_size;
		}
		catch (std::exception & err)
		{
			Clear();
		}
	}
}

CStringStack::CStringStack(CStringStack && removedStack)
	: m_top(removedStack.m_top)
	, m_size(removedStack.m_size)
{
	removedStack.m_top = nullptr;
	removedStack.m_size = 0;
}

void CStringStack::Push(std::string const& element)
{
	m_top = std::make_shared<Node>(element, m_top);
	++m_size;
}

void CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}
	m_top = m_top->next;
	--m_size;
}

std::string CStringStack::GetTopElement()const
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}
	return m_top->value;
}

void CStringStack::Clear()
{
	while (m_top != nullptr)
	{
		Pop();
	}
}

bool CStringStack::IsEmpty()const
{
	return m_top == nullptr;
}

size_t CStringStack::GetSize()const
{
	return m_size;
}

CStringStack& CStringStack::operator=(CStringStack const& copiedStack)
{
	if (std::addressof(copiedStack) != this)
	{
		CStringStack temporaryStack(copiedStack);
		std::swap(*this, temporaryStack);
	}
	return *this;
}

CStringStack& CStringStack::operator=(CStringStack && removedStack)
{
	if (std::addressof(removedStack) != this)
	{
		m_top = removedStack.m_top;
		m_size = removedStack.m_size;
		removedStack.m_top = nullptr;
		removedStack.m_size = 0;
	}
	return *this;
}

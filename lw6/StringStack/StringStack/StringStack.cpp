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
{
	std::shared_ptr<Stack> tmp = copiedStack.m_top;
	std::shared_ptr<Stack> currentTop = std::make_shared<Stack>(tmp->value, nullptr);
	m_top = currentTop;
	tmp = tmp->next;
	while (tmp != nullptr)
	{
		currentTop->next = std::make_shared<Stack>(tmp->value, nullptr);
		currentTop = currentTop->next;
		tmp = tmp->next;
	}
	m_size = copiedStack.GetSize();
}

CStringStack::CStringStack(CStringStack && removedStack)
	: m_top(nullptr)
	, m_size(0)
{
	m_top = removedStack.m_top;
	m_size = removedStack.m_size;
	removedStack.m_top = nullptr;
	removedStack.m_size = 0;
}

void CStringStack::Push(std::string const& element)
{
	std::shared_ptr<Stack> tmp = m_top;
	m_top = std::make_shared<Stack>(element, tmp);
	++m_size;
}

void CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	std::shared_ptr<Stack> tmp = m_top;
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

CStringStack& CStringStack::operator=(CStringStack & copiedStack)
{
	if (std::addressof(copiedStack) != this)
	{
		std::shared_ptr<Stack> tmp = copiedStack.m_top;
		std::shared_ptr<Stack> currentTop = std::make_shared<Stack>(tmp->value, nullptr);
		m_top = currentTop;
		tmp = tmp->next;
		while (tmp != nullptr)
		{
			currentTop->next = std::make_shared<Stack>(tmp->value, nullptr);
			currentTop = currentTop->next;
			tmp = tmp->next;
		}
		m_size = copiedStack.GetSize();
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

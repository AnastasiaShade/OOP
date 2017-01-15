#pragma once
#include "stdafx.h"
#include <memory>
#include <string>

class CStringStack
{
	struct Node
	{
		Node(std::string const& value, std::shared_ptr<Node> const& next)
			: value(value)
			, next(next)
		{
		}
		std::string value;
		std::shared_ptr<Node> next;
	};

public:
	CStringStack();
	CStringStack(CStringStack const& copiedStack);
	CStringStack(CStringStack && removedStack);
	~CStringStack();
	void Push(std::string const& element);
	void Pop();
	std::string GetTopElement()const;
	void Clear();
	bool IsEmpty()const;
	size_t GetSize()const;
	CStringStack& operator=(CStringStack & copiedStack);
	CStringStack& operator=(CStringStack && removedStack);

private:
	std::shared_ptr<Node> m_top;
	size_t m_size;
};

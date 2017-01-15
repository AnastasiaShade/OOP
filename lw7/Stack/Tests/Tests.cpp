#include "stdafx.h"
#include <string>
#include <algorithm>
#include "../Stack/MyStack.h"

using namespace std;

struct StackOfInt
{
	CMyStack<int> stack;
};

BOOST_FIXTURE_TEST_SUITE(Stack_of_integer, StackOfInt)

BOOST_AUTO_TEST_CASE(is_empty_by_default)
{
	BOOST_CHECK(stack.IsEmpty());
}

BOOST_AUTO_TEST_CASE(cant_delete_or_get_last_element_if_stack_is_empty)
{
	BOOST_REQUIRE_THROW(stack.Pop(), std::logic_error);
	BOOST_REQUIRE_THROW(stack.GetTopElement(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(can_add_element)
{
	stack.Push(200);
	BOOST_CHECK(!stack.IsEmpty());
	BOOST_CHECK_EQUAL(stack.GetSize(), 1);
	BOOST_CHECK_EQUAL(stack.GetTopElement(), 200);
}

BOOST_AUTO_TEST_CASE(can_be_constructed_from_empty_stack)
{
	CMyStack<int> otherStack(stack);
	BOOST_CHECK_EQUAL(!stack.IsEmpty(), !otherStack.IsEmpty());
}

struct WithElements : StackOfInt
{
	WithElements()
	{
		stack.Push(0);
		stack.Push(-15);
		stack.Push(50);
		stack.Push(155);
		stack.Push(-70);
	}
};
BOOST_FIXTURE_TEST_SUITE(with_elements, WithElements)

BOOST_AUTO_TEST_CASE(contain_elements)
{

	BOOST_CHECK(!stack.IsEmpty());
	BOOST_CHECK_EQUAL(stack.GetSize(), 5);
}

BOOST_AUTO_TEST_CASE(can_return_last_element)
{
	BOOST_CHECK_EQUAL(stack.GetTopElement(), -70);
}

BOOST_AUTO_TEST_CASE(can_delete_last_element)
{
	stack.Pop();
	BOOST_CHECK(!stack.IsEmpty());
	BOOST_CHECK_EQUAL(stack.GetSize(), 4);
	BOOST_CHECK_EQUAL(stack.GetTopElement(), 155);
}

BOOST_AUTO_TEST_CASE(can_be_cleaned)
{
	stack.Clear();
	BOOST_CHECK(stack.IsEmpty());
	BOOST_CHECK_EQUAL(stack.GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(can_be_constructed_from_other_stack)
{
	CMyStack<int> otherStack(stack);
	BOOST_CHECK_EQUAL(otherStack.GetSize(), stack.GetSize());
	BOOST_CHECK_EQUAL(otherStack.GetTopElement(), stack.GetTopElement());
}

BOOST_AUTO_TEST_CASE(stack_is_independent_of_its_copies)
{
	CMyStack<int> stackCopy(stack);
	stackCopy.Pop();
	BOOST_CHECK_EQUAL((stack.GetSize() != stackCopy.GetSize()), true);
}

BOOST_AUTO_TEST_CASE(can_be_moved)
{
	CMyStack<int> otherStack = std::move(stack);
	BOOST_CHECK(stack.IsEmpty());
	BOOST_CHECK_EQUAL(otherStack.GetSize(), 5);
}

BOOST_AUTO_TEST_CASE(can_be_assigned)
{
	CMyStack<int> otherStack = stack;
	BOOST_CHECK_EQUAL(otherStack.GetSize(), stack.GetSize());
	BOOST_CHECK_EQUAL(otherStack.GetTopElement(), stack.GetTopElement());
}

BOOST_AUTO_TEST_CASE(can_be_assigned_by_itself)
{
	CMyStack<int> otherStack = stack;
	BOOST_CHECK_EQUAL(otherStack.GetSize(), stack.GetSize());
	BOOST_CHECK_EQUAL(otherStack.GetTopElement(), stack.GetTopElement());
}

BOOST_AUTO_TEST_CASE(can_be_assigned_by_empty_stack)
{
	CMyStack<int> otherStack;
	stack = otherStack;
	BOOST_CHECK_EQUAL(otherStack.IsEmpty(), stack.IsEmpty());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

struct StackOfString
{
	CMyStack<std::string> stack;
};

BOOST_FIXTURE_TEST_SUITE(Stack_of_string, StackOfString)

BOOST_AUTO_TEST_CASE(is_empty_by_default)
{
	BOOST_CHECK(stack.IsEmpty());
}

BOOST_AUTO_TEST_CASE(cant_delete_or_get_last_element_if_stack_is_empty)
{
	BOOST_REQUIRE_THROW(stack.Pop(), std::logic_error);
	BOOST_REQUIRE_THROW(stack.GetTopElement(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(can_add_element)
{
	stack.Push("hello");
	BOOST_CHECK(!stack.IsEmpty());
	BOOST_CHECK_EQUAL(stack.GetSize(), 1);
	BOOST_CHECK_EQUAL(stack.GetTopElement(), "hello");
}

BOOST_AUTO_TEST_CASE(can_be_constructed_from_empty_stack)
{
	CMyStack<string> otherStack(stack);
	BOOST_CHECK_EQUAL(!stack.IsEmpty(), !otherStack.IsEmpty());
}

struct WithElements : StackOfString
{
	WithElements()
	{
		stack.Push("");
		stack.Push("hello");
		stack.Push("h");
		stack.Push("");
		stack.Push("hello world!");
	}
};

BOOST_FIXTURE_TEST_SUITE(with_elements, WithElements)

BOOST_AUTO_TEST_CASE(can_contain_elements)
{
	BOOST_CHECK(!stack.IsEmpty());
	BOOST_CHECK_EQUAL(stack.GetSize(), 5);
}

BOOST_AUTO_TEST_CASE(can_return_last_element)
{
	BOOST_CHECK_EQUAL(stack.GetTopElement(), "hello world!");
}

BOOST_AUTO_TEST_CASE(can_delete_last_element)
{
	stack.Pop();
	BOOST_CHECK(!stack.IsEmpty());
	BOOST_CHECK_EQUAL(stack.GetSize(), 4);
	BOOST_CHECK_EQUAL(stack.GetTopElement(), "");
}

BOOST_AUTO_TEST_CASE(can_be_cleaned)
{
	stack.Clear();
	BOOST_CHECK(stack.IsEmpty());
	BOOST_CHECK_EQUAL(stack.GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(can_be_constructed_from_other_stack)
{
	CMyStack<string> otherStack(stack);
	BOOST_CHECK_EQUAL(otherStack.GetSize(), stack.GetSize());
	BOOST_CHECK_EQUAL(otherStack.GetTopElement(), stack.GetTopElement());
}

BOOST_AUTO_TEST_CASE(is_independent_of_its_copies)
{
	CMyStack<string> stackCopy(stack);
	stackCopy.Pop();
	BOOST_CHECK_EQUAL((stack.GetSize() != stackCopy.GetSize()), true);;
}

BOOST_AUTO_TEST_CASE(can_be_moved)
{
	CMyStack<string> otherStack = std::move(stack);
	BOOST_CHECK(stack.IsEmpty());
	BOOST_CHECK_EQUAL(otherStack.GetSize(), 5);
}

BOOST_AUTO_TEST_CASE(can_be_assigned)
{
	CMyStack<string> otherStack = stack;
	BOOST_CHECK_EQUAL(otherStack.GetSize(), stack.GetSize());
	BOOST_CHECK_EQUAL(otherStack.GetTopElement(), stack.GetTopElement());
}

BOOST_AUTO_TEST_CASE(can_be_assigned_by_itself)
{
	CMyStack<string> otherStack = stack;
	BOOST_CHECK_EQUAL(otherStack.GetSize(), stack.GetSize());
	BOOST_CHECK_EQUAL(otherStack.GetTopElement(), stack.GetTopElement());
}

BOOST_AUTO_TEST_CASE(can_be_assigned_by_empty_stack)
{
	CMyStack<string> otherStack;
	stack = otherStack;
	BOOST_CHECK_EQUAL(otherStack.IsEmpty(), stack.IsEmpty());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

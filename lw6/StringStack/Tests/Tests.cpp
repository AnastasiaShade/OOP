#include "stdafx.h"
#include <string>
#include <algorithm>
#include "../StringStack/StringStack.h"

using namespace std;

struct StackOfString
{
	CStringStack stack;
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
	CStringStack otherStack(stack);
	BOOST_CHECK_EQUAL(otherStack.GetSize(), stack.GetSize());
	BOOST_CHECK_EQUAL(otherStack.GetTopElement(), stack.GetTopElement());
}

BOOST_AUTO_TEST_CASE(stack_is_independent_of_its_copies)
{
	CStringStack stackCopy(stack);
	stackCopy.Pop();
	BOOST_CHECK_EQUAL((stack.GetSize() != stackCopy.GetSize()), true);;
}

BOOST_AUTO_TEST_CASE(can_be_moved)
{
	CStringStack otherStack = std::move(stack);
	BOOST_CHECK(stack.IsEmpty());
	BOOST_CHECK_EQUAL(otherStack.GetSize(), 5);
}

BOOST_AUTO_TEST_CASE(can_be_assigned)
{
	CStringStack otherStack = stack;
	BOOST_CHECK_EQUAL(otherStack.GetSize(), stack.GetSize());
	BOOST_CHECK_EQUAL(otherStack.GetTopElement(), stack.GetTopElement());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

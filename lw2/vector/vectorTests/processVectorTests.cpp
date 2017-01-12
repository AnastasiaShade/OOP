#include "stdafx.h"
#include "../vector/processVector.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}


BOOST_AUTO_TEST_SUITE(ProcessVectorTest)
	BOOST_AUTO_TEST_CASE(all_numbers_are_equal_and_positive)
	{
		vector<double> elements = { 4, 4, 4, 4, 4 };
		ProcessElements(elements);
		BOOST_CHECK(VectorsAreEqual(elements, { 8, -16, 8, -16, 8 }));
		SortElements(elements);
		BOOST_CHECK(VectorsAreEqual(elements, { -16, -16, 8, 8, 8 }));
	}

	BOOST_AUTO_TEST_CASE(all_numbers_are_equal_and_negative)
	{
		vector<double> elements = { -1.1, -1.1, -1.1, -1.1, -1.1 };
		ProcessElements(elements);
		BOOST_CHECK(VectorsAreEqual(elements, { -2.2, -1.1, -2.2, -1.1, -2.2 }));
		SortElements(elements);
		BOOST_CHECK(VectorsAreEqual(elements, { -2.2, -2.2, -2.2, -1.1, -1.1 }));
	}

	BOOST_AUTO_TEST_CASE(positive_and_negative_numbers)
	{
		vector<double> elements = { 15, -6, 3.15, 0 };
		ProcessElements(elements);
		BOOST_CHECK(VectorsAreEqual(elements, { 30, -24.15, 6.3, -18.15 }));
		SortElements(elements);
		BOOST_CHECK(VectorsAreEqual(elements, { -24.15, -18.15, 6.3, 30 }));
	}

	BOOST_AUTO_TEST_CASE(empty_vector)
	{
		vector<double> elements = { };
		ProcessElements(elements);
		BOOST_CHECK(VectorsAreEqual(elements, { }));
		SortElements(elements);
		BOOST_CHECK(VectorsAreEqual(elements, { }));
	}

BOOST_AUTO_TEST_SUITE_END()
#include "stdafx.h"
#include "../primeNumbers/processPrimeNumbers.h"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
BOOST_AUTO_TEST_SUITE(Tests_for_prime_numbers)

	BOOST_AUTO_TEST_CASE(User_upper_bound_less_than_min_value)
	{
		unsigned userUpperBound = 1;
		BOOST_CHECK(!IsCorrectUpperBound(userUpperBound));
	}

	BOOST_AUTO_TEST_CASE(User_upper_bound_more_than_max_value)
	{
		unsigned userUpperBound = 100000001;
		BOOST_CHECK(IsCorrectUpperBound(userUpperBound) == false);
	}

	BOOST_AUTO_TEST_CASE(Create_set_when_user_upper_bound_is_10)
	{
		set<unsigned> setForCheck = {2, 3, 5, 7};
		BOOST_CHECK(GeneratePrimeNumbersSet(10) == setForCheck);
	}

	BOOST_AUTO_TEST_CASE(Create_set_when_user_upper_bound_is_100)
	{
		set<unsigned> setForCheck = {2, 3, 5, 7, 11, 13, 17, 19, 23,
			29, 31, 37, 41, 43, 47, 53, 59,
			61, 67, 71, 73, 79, 83, 89, 97};
		BOOST_CHECK(GeneratePrimeNumbersSet(100) == setForCheck);
	}

	#ifdef NDEBUG
	BOOST_AUTO_TEST_CASE(Return_number_of_primes_when_user_upper_bound_is_max)
	{
		BOOST_CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
	}
	#endif

BOOST_AUTO_TEST_SUITE_END()
#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"

struct Athlete
{
	std::string fullName;
	double height;
	double weight;
};

struct ArrOfAthletes
{
	std::vector<Athlete> athletes = {};
};

bool IsLessWeight(Athlete const& lhs, Athlete const& rhs)
{
	return lhs.weight < rhs.weight;
}

bool IsLessHeight(Athlete const& lhs, Athlete const& rhs)
{
	return lhs.height < rhs.height;
}

void AreEquals(Athlete const& lhs, Athlete const& rhs)
{
	BOOST_CHECK_EQUAL(lhs.fullName, rhs.fullName);
	BOOST_CHECK_EQUAL(lhs.height, rhs.height);
	BOOST_CHECK_EQUAL(lhs.weight, rhs.weight);
}

BOOST_FIXTURE_TEST_SUITE(FindMax_function, ArrOfAthletes)

	BOOST_AUTO_TEST_CASE(cant_find_max_element_in_empty_vector)
	{
		Athlete highestAthlete = {};
		BOOST_CHECK(!FindMax(athletes, highestAthlete, IsLessHeight));
		AreEquals(highestAthlete, {});

		Athlete heaviestAthlete = {};
		BOOST_CHECK(!FindMax(athletes, heaviestAthlete, IsLessWeight));
		AreEquals(heaviestAthlete, {});
	}

	struct WithElements : ArrOfAthletes
	{
		Athlete Jay = { "Jay John Jamson", 202.7, 101.35 };
		Athlete Alexeyev = { "Alexeyev Ivan Ivanovich", 186.15, 97.5 };
		Athlete Petrov = { "Petrov Alexander Petrovich", 190.8, 102.9 };
		std::vector<Athlete> athletes = { Jay, Alexeyev, Petrov };
	};

	BOOST_FIXTURE_TEST_SUITE(with_elements, WithElements)

		BOOST_AUTO_TEST_CASE(can_find_max_element_in_nonempty_vector)
		{
			Athlete highestAthlete;
			BOOST_CHECK(FindMax(athletes, highestAthlete, IsLessHeight));
			AreEquals(highestAthlete, Jay);

			Athlete heaviestAthlete;
			BOOST_CHECK(FindMax(athletes, heaviestAthlete, IsLessWeight));
			AreEquals(heaviestAthlete, Petrov);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
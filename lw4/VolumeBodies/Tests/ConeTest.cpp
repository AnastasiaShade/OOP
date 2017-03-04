#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../VolumeBodies/Cone.h"
#include <math.h>


struct Cone_
{
	const double expectedRadius = 42.8;
	const double expectedHeight = 124.0;
	const double expectedDensity = 3.8;
	const double expectedVolume = pow(expectedRadius, 2) * M_PI * expectedHeight / 3;
	const CCone cone;
	Cone_()
		: cone(expectedDensity, expectedRadius, expectedHeight)
	{}
};
BOOST_FIXTURE_TEST_SUITE(Cone, Cone_)

BOOST_AUTO_TEST_CASE(is_a_body)
{
	BOOST_CHECK(static_cast<const CBody*>(&cone));
}

BOOST_AUTO_TEST_CASE(has_a_radius)
{
	BOOST_CHECK_EQUAL(cone.GetRadius(), expectedRadius);
}

BOOST_AUTO_TEST_CASE(has_a_height)
{
	BOOST_CHECK_EQUAL(cone.GetHeight(), expectedHeight);
}

BOOST_AUTO_TEST_CASE(has_a_density)
{
	BOOST_CHECK_EQUAL(static_cast<const CBody &>(cone).GetDensity(), expectedDensity);
}

BOOST_AUTO_TEST_CASE(has_a_volume)
{
	BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cone).GetVolume(), expectedVolume, 1e-7);
}

BOOST_AUTO_TEST_CASE(has_a_mass)
{
	BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cone).GetMass(), expectedVolume * expectedDensity, 1e-7);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const auto expectedString = R"(Cone:
	density = 3.8
	volume = 237868.9969
	mass = 903902.1883
	radius = 42.8
	height = 124
)";
	BOOST_CHECK_EQUAL(static_cast<const CBody &>(cone).ToString(), expectedString);
}
BOOST_AUTO_TEST_CASE(cant_have_negative_values)
{
	BOOST_REQUIRE_THROW(CCone(-1, 1, 3), std::invalid_argument);
	BOOST_REQUIRE_THROW(CCone(1, -1, 3), std::invalid_argument);
	BOOST_REQUIRE_THROW(CCone(1, 1, -3), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
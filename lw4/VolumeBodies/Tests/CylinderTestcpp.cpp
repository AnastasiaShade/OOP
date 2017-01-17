#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../VolumeBodies/Cylinder.h"
#include <math.h>


struct Cylinder_
{
	const double expectedRadius = 42.8;
	const double expectedHeight = 124.0;
	const double expectedDensity = 3.8;
	const double expectedVolume = 713606.9907;
	const CCylinder cylinder;
	Cylinder_()
		: cylinder(expectedDensity, expectedRadius, expectedHeight)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Cylinder, Cylinder_)

BOOST_AUTO_TEST_CASE(is_a_body)
{
	BOOST_CHECK(static_cast<const CBody*>(&cylinder));
}

BOOST_AUTO_TEST_CASE(has_a_radius)
{
	BOOST_CHECK_EQUAL(cylinder.GetRadius(), expectedRadius);
}

BOOST_AUTO_TEST_CASE(has_a_height)
{
	BOOST_CHECK_EQUAL(cylinder.GetHeight(), expectedHeight);
}

BOOST_AUTO_TEST_CASE(has_a_density)
{
	BOOST_CHECK_EQUAL(static_cast<const CBody &>(cylinder).GetDensity(), expectedDensity);
}

BOOST_AUTO_TEST_CASE(has_a_volume)
{
	BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetVolume(), expectedVolume, 1e-7);
}

BOOST_AUTO_TEST_CASE(has_a_mass)
{
	BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetMass(), expectedVolume * expectedDensity, 1e-7);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const auto expectedString = R"(Cylinder:
	density = 3.8
	volume = 713606.9907
	mass = 2711706.565
	radius = 42.8
	height = 124
)";
	BOOST_CHECK_EQUAL(static_cast<const CBody &>(cylinder).ToString(), expectedString);
}
BOOST_AUTO_TEST_CASE(cant_have_negative_values)
{
	BOOST_REQUIRE_THROW(CCylinder(-1, 1, 3), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()
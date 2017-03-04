#include "stdafx.h"
#include "../VolumeBodies/Controller.h"
#include "../VolumeBodies/Body.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;


struct ControllerDependencies
{
	vector<shared_ptr<CBody>> bodies;
	stringstream input;
	stringstream output;
};

struct ControllerFixture : ControllerDependencies
{
	CController controller;

	ControllerFixture()
		: controller(bodies, input, output)
	{
	}


	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		controller.HandleCommand();
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Controller, ControllerFixture)

BOOST_AUTO_TEST_CASE(can_handle_sphere)
{
	const string expectedOutput = R"(Sphere:
	density = 5
	volume = 4188.790205
	mass = 20943.95102
	radius = 10
)";
	VerifyCommandHandling("Sphere 5 10", "");
	BOOST_CHECK((*bodies.begin())->GetDensity() == 5);
	BOOST_CHECK((*bodies.begin())->ToString() == expectedOutput);
}

BOOST_AUTO_TEST_CASE(can_handle_cone)
{
	const string expectedOutput = R"(Cone:
	density = 3.8
	volume = 237868.9969
	mass = 903902.1883
	radius = 42.8
	height = 124
)";
	VerifyCommandHandling("Cone 3.8 42.8 124.0", "");
	BOOST_CHECK((*bodies.begin())->GetDensity() == 3.8);
	BOOST_CHECK((*bodies.begin())->ToString() == expectedOutput);
}

BOOST_AUTO_TEST_CASE(can_handle_cylinder)
{
	const string expectedOutput = R"(Cylinder:
	density = 3.8
	volume = 713606.9907
	mass = 2711706.565
	radius = 42.8
	height = 124
)";
	VerifyCommandHandling("Cylinder 3.8 42.8 124.0", "");
	BOOST_CHECK((*bodies.begin())->GetDensity() == 3.8);
	BOOST_CHECK((*bodies.begin())->ToString() == expectedOutput);
}

BOOST_AUTO_TEST_CASE(can_handle_parallelepiped)
{
	const string expectedOutput = R"(Parallelepiped:
	density = 8.8
	volume = 7789.6
	mass = 68548.48
	length = 10
	width = 42.8
	height = 18.2
)";
	VerifyCommandHandling("Parallelepiped 8.8 10 42.8 18.2", "");
	BOOST_CHECK((*bodies.begin())->GetDensity() == 8.8);
	BOOST_CHECK((*bodies.begin())->ToString() == expectedOutput);
}

BOOST_AUTO_TEST_CASE(cant_handle_invalid_input)
{
	VerifyCommandHandling("Sphere 5", "Invalid count of arguments\nUsage: Sphere <density> <radius>\n");
	BOOST_CHECK(bodies.empty());
}

BOOST_AUTO_TEST_CASE(cant_handle_negative_density)
{
	VerifyCommandHandling("Sphere -5 10", "Density should not be negative");
	BOOST_CHECK(bodies.empty());
}
BOOST_AUTO_TEST_CASE(cant_handle_negative_params)
{
	VerifyCommandHandling("Sphere 5 -10", "Radius should not be negative");
	BOOST_CHECK(bodies.empty());
}
BOOST_AUTO_TEST_SUITE_END()
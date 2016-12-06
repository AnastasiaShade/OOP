#include "stdafx.h"
#include "../Car/CarController.h"
#include "../Car/Car.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

struct CCarControllerDependencies
{
	CCar car;
	stringstream input;
	stringstream output;
};

struct CarControllerFixture : CCarControllerDependencies
{
	CCarController remoteControl;

	CarControllerFixture()
		: remoteControl(car, input, output)
	{
	}

	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Car_controller, CarControllerFixture)

BOOST_AUTO_TEST_CASE(cant_handle_EngineOff_command)
{
	VerifyCommandHandling("EngineOff", "Speed is non 0 and gear is non neutral or engine is already off\n");
}

BOOST_AUTO_TEST_CASE(can_handle_EngineOn_command)
{
	VerifyCommandHandling("EngineOn", "Engine is turned on\n");
}

BOOST_AUTO_TEST_CASE(can_handle_Info_command)
{
	VerifyCommandHandling("Info", "Engine is turned off\n");
}

BOOST_AUTO_TEST_CASE(can_print_errors_message)
{
	VerifyCommandHandling("SetGear 1", "Gear is out of range for current gear or engine is turned off\n");
}

BOOST_AUTO_TEST_SUITE_END()
#include "stdafx.h"
#include "../car/Car.h"


struct CarFixture
{
	CCar car;
};

bool IsSpeedChanged(CCar &car, int const &gear, int const &speed)
{
	car.SetGear(gear);
	return (car.SetSpeed(speed) ? true : false);
}

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

BOOST_AUTO_TEST_CASE(engine_should_be_turned_off_by_default)
{
	BOOST_CHECK(!car.IsEngineOn());
}

BOOST_AUTO_TEST_SUITE(if_engine_is_turned_off)

BOOST_AUTO_TEST_CASE(neutral_gear_should_be_set_by_default)
{
	BOOST_CHECK(car.GetCurrentGear() == 0);
}

BOOST_AUTO_TEST_CASE(speed_should_be_zero_by_default)
{
	BOOST_CHECK(car.GetCurrentSpeed() == 0);
}

BOOST_AUTO_TEST_CASE(can_set_neutral_gear)
{
	BOOST_CHECK(car.SetGear(0));
}

BOOST_AUTO_TEST_CASE(cant_set_non_neutral_gear)
{
	BOOST_CHECK(!car.SetGear(-1));
}

BOOST_AUTO_TEST_CASE(cant_change_speed)
{
	BOOST_CHECK(!car.SetSpeed(10));
}

BOOST_AUTO_TEST_CASE(engine_cant_be_turned_off)
{
	BOOST_CHECK(!car.TurnOffEngine());
}

BOOST_AUTO_TEST_CASE(engine_can_be_turned_on)
{
	BOOST_CHECK(car.TurnOnEngine());
}

BOOST_AUTO_TEST_SUITE_END()

struct when_turned_on_ : CarFixture
{
	when_turned_on_()
	{
		car.TurnOnEngine();
	}
};

BOOST_FIXTURE_TEST_SUITE(if_engine_is_turned_on, when_turned_on_)

BOOST_AUTO_TEST_CASE(engine_cant_be_turned_on)
{
	BOOST_CHECK(!car.TurnOnEngine());
}

BOOST_AUTO_TEST_CASE(neutral_gear_should_be_set_by_default)
{
	BOOST_CHECK(car.GetCurrentGear() == 0);
}

BOOST_AUTO_TEST_SUITE(set_gear)

BOOST_AUTO_TEST_SUITE(if_neutral_gear_is_set)

BOOST_AUTO_TEST_CASE(can_set_rear_gear)
{
	BOOST_CHECK(car.SetGear(-1));
}

BOOST_AUTO_TEST_CASE(can_set_first_gear)
{
	BOOST_CHECK(car.SetGear(1));
}

BOOST_AUTO_TEST_CASE(cant_set_gear_out_of_range)
{
	BOOST_CHECK(!car.SetGear(6));
	BOOST_CHECK(!car.SetGear(-2));
}

BOOST_AUTO_TEST_CASE(cant_set_gear_without_required_speed)
{
	BOOST_CHECK(!car.SetGear(3));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(set_rear_gear)

BOOST_AUTO_TEST_CASE(can_set_rear_gear)
{
	BOOST_CHECK(car.SetGear(-1));
}

BOOST_AUTO_TEST_CASE(can_set_first_gear)
{
	BOOST_CHECK(car.SetGear(1));
}

BOOST_AUTO_TEST_CASE(cant_set_gear_without_required_speed)
{
	BOOST_CHECK(!car.SetGear(2));
}

BOOST_AUTO_TEST_CASE(can_set_rear_gear_from_first_gear_and_zero_speed)
{
	car.SetGear(1);
	car.SetSpeed(0);
	BOOST_CHECK(car.SetGear(-1));
}

BOOST_AUTO_TEST_CASE(cant_set_rear_gear_from_other_gears_or_non_zero_speeds)
{
	car.SetGear(1);
	car.SetSpeed(30);
	BOOST_CHECK(!car.SetGear(-1));
	car.SetGear(2);
	BOOST_CHECK(!car.SetGear(-1));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(set_first_gear)

BOOST_AUTO_TEST_CASE(can_set_first_gear_from_rear_gear_and_zero_speed)
{
	car.SetGear(-1);
	car.SetSpeed(0);
	BOOST_CHECK(car.SetGear(1));
}

BOOST_AUTO_TEST_CASE(cant_set_first_gear_from_rear_gear_and_non_zero_speed)
{
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	BOOST_CHECK(!car.SetGear(1));
}

BOOST_AUTO_TEST_CASE(can_set_first_gear_from_rear_gear_and_non_zero_speed)
{
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	car.SetSpeed(0);
	BOOST_CHECK(car.SetGear(1));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(set_second_gear)
BOOST_AUTO_TEST_CASE(can_set_second_gear_from_first_gear)
{
	car.SetGear(1);
	car.SetSpeed(25);
	BOOST_CHECK(car.SetGear(2));
}

BOOST_AUTO_TEST_CASE(cant_set_second_gear_from_first_gear)
{
	car.SetGear(1);
	car.SetSpeed(15);
	BOOST_CHECK(!car.SetGear(2));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(set_speed)

BOOST_AUTO_TEST_CASE(can_set_allowed_speed_for_gear)
{
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 1, 10), true);
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 2, 30), true);
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 3, 50), true);
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 4, 50), true);
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 5, 70), true);
}

BOOST_AUTO_TEST_CASE(cant_set_speed_out_of_gear_speed_range)
{
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 1, 100), false);
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 5, 170), false);
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, -1, 40), false);
}

BOOST_AUTO_TEST_CASE(can_decrease_speed_at_neutral_gear)
{
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 1, 20), true);
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 0, 10), true);
}

BOOST_AUTO_TEST_CASE(cant_increase_speed_at_neutral_gear)
{
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 1, 20), true);
	BOOST_CHECK_EQUAL(IsSpeedChanged(car, 0, 30), false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Turn_off)

BOOST_AUTO_TEST_CASE(engine_can_be_turned_off_at_neutral_gear_and_with_zero_speed)
{
	car.SetGear(1);
	car.SetSpeed(0);
	car.SetGear(0);
	BOOST_CHECK(car.TurnOffEngine());
}

BOOST_AUTO_TEST_CASE(engine_cant_be_turned_off_at_neutral_gear_and_with_non_zero_speed)
{
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(0);
	BOOST_CHECK(!car.TurnOffEngine());
}

BOOST_AUTO_TEST_CASE(engine_cant_be_turned_off_at_non_neutral_gear)
{
	car.SetGear(1);
	BOOST_CHECK(!car.TurnOffEngine());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
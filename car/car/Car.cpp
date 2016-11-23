#include "stdafx.h"
#include "Car.h"


using namespace std;

CCar::CCar()
	: m_isTurnOn(false)
	, m_currentGear(Gear::NEUTRAL)
	, m_direction(Direction::STAY)
	, m_speed(0)
{
}

string CCar::Info()const
{
	return IsEngineOn() ?
		"Engine is turned on\nDirection is " + GetCurrentDirection() + "\nGear is " + to_string(GetCurrentGear())
		+ "\nSpeed is " + to_string(GetCurrentSpeed()) + "\n"
		: "Engine is turned off\n";
}

bool CCar::TurnOnEngine()
{
	if (!m_isTurnOn)
	{
		m_isTurnOn = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if ((m_isTurnOn) && (m_speed == 0) && (m_currentGear == Gear::NEUTRAL))
	{
		m_isTurnOn = false;
		return true;
	}
	return false;
}

bool CCar::SetGear(int gear)
{
	if (!m_isTurnOn)
	{
		if (gear == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (IsValidGear(gear) && IsValidSpeed(static_cast<Gear>(gear), m_speed))
	{
		if (ChangeGear(gear))
		{
			return true;
		}
	}
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_isTurnOn)
	{
		return false;
	}
	if (m_currentGear == Gear::REAR)
	{
		if (IsValidSpeed(m_currentGear, speed))
		{
			m_speed = speed;
			m_speed > 0 ? m_direction = Direction::BACKWARD : m_direction = Direction::STAY;
			return true;
		}
	}
	else if (m_currentGear == Gear::NEUTRAL)
	{
		if (speed < m_speed)
		{
			m_speed = speed;
			if (m_speed == 0)
			{
				m_direction = Direction::STAY;
			}
			return true;
		}
	}
	else if (IsValidSpeed(m_currentGear, speed))
	{
		m_speed = speed;
		m_direction = Direction::FORWARD;
		return true;
	}
	return false;
}

bool CCar::IsValidGear(int gear)const
{
	return (gear >= -1 && gear <= 5);
}

bool CCar::IsValidSpeed(const Gear &gear, const int &speed)const
{
	auto it = SpeedRange.find(gear);
	auto speedRange = it->second;
	return (speed >= speedRange.first && speed <= speedRange.second);

}

bool CCar::ChangeGear(int gear)
{
	switch (gear)
	{
	case -1:
		if (m_speed == 0 && (m_currentGear == Gear::NEUTRAL || m_currentGear == Gear::FIRST))
		{
			m_currentGear = static_cast<Gear>(gear);
			return true;
		}
		break;
	case 0:
		m_currentGear = static_cast<Gear>(gear);
		return true;
	case 1:
		if ((m_currentGear == Gear::REAR && m_speed == 0)
			|| (m_currentGear == Gear::NEUTRAL && m_direction == Direction::STAY)
			|| (m_direction == Direction::FORWARD))
		{
			m_currentGear = static_cast<Gear>(gear);
			return true;
		}
		break;
	case 2:
		m_currentGear = static_cast<Gear>(gear);
		return true;
	case 3:
		m_currentGear = static_cast<Gear>(gear);
		return true;
	case 4:
		m_currentGear = static_cast<Gear>(gear);
		return true;
	case 5:
		m_currentGear = static_cast<Gear>(gear);
		return true;
	default:
		break;
	}
	return false;
}


bool CCar::IsEngineOn()const
{
	return m_isTurnOn;
}

int CCar::GetCurrentGear()const
{
	return static_cast<int>(m_currentGear);
}

int CCar::GetCurrentSpeed() const
{
	return m_speed;
}

std::string CCar::GetCurrentDirection()const
{
	string direction = "";
	switch (m_direction)
	{
		case Direction::FORWARD:
			direction = "forward";
			break;
		case Direction::BACKWARD:
			direction = "backward";
			break;
		case Direction::STAY:
			direction = "stay";
			break;
		default:
			break;
	}

	return direction;
}

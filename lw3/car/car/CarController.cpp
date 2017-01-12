#include "stdafx.h"
#include "CarController.h"
#include "Car.h"

using namespace std;
using namespace std::placeholders;

CCarController::CCarController(CCar & car, std::istream & input, std::ostream & output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "Info", bind(&CCarController::Info, this, _1) },
	{ "EngineOn", bind(&CCarController::EngineOn, this, _1) },
	{ "EngineOff", bind(&CCarController::EngineOff, this, _1) },
	{ "SetGear", bind(&CCarController::SetGear, this, _1) },
	{ "SetSpeed", bind(&CCarController::SetSpeed, this, _1) }
})
{
}

bool CCarController::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it == m_actionMap.end())
	{
		m_output << "Usage:\nEngineOn - turn engine on\nEngineOff - turn engine off\nSetGear <gear value> - set gear\n"
			<< "SetSpeed <speed value> - set speed\nInfo - get info about current car sustain\n";
	}
	else
	{
		return it->second(strm);
	}

	return false;
}

bool CCarController::EngineOn(std::istream & /*args*/)
{
	!m_car.TurnOnEngine() ? m_output << "Engine is already on\n" : m_output << "Engine is turned on\n";

	return true;
}

bool CCarController::EngineOff(std::istream & /*args*/)
{
	!m_car.TurnOffEngine() ? m_output << "Speed is non 0 and gear is non neutral or engine is already off\n" : m_output << "Engine is turned off\n";

	return true;
}

bool CCarController::Info(std::istream & /*args*/)
{
	string info = (m_car.IsEngineOn())
		? ("Engine is turned on\nDirection is: " + m_car.GetCurrentDirection() + "\nGear is: " + to_string(m_car.GetCurrentGear()) + 
		"\nSpeed is: " + to_string(m_car.GetCurrentSpeed()) + "\n")
		: "Engine is turned off\n";

	m_output << info;

	return true;
}

bool CCarController::SetGear(std::istream &args)
{
	int gear;
	args >> gear;
	m_car.SetGear(gear) ? m_output << "Gear was changed on " << m_car.GetCurrentGear() << '\n'
		: m_output << "Gear is out of range for current gear or engine is turned off\n";

	return true;
}

bool CCarController::SetSpeed(std::istream &args)
{
	int speed;
	args >> speed;
	m_car.SetSpeed(speed) ? m_output << "Speed was successfully changed on " << m_car.GetCurrentSpeed() << '\n'
		: m_output << "Speed is out of range for current gear or engine is turned off\n";

	return true;
}

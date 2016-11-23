#pragma once
#include "Car.h"

class Ccar;

class CCarController
{
public:
	CCarController();
	~CCarController() = default;
	bool HandleCommand();
private:
	bool Info(istream & args)const;
	bool EngineOn(istream & args);
	bool EngineOff(istream & args);
	bool SetGear(istream & args);
	bool SetSpeed(istream & args);
	typedef std::map<std::string, function<bool(istream & args)>> ActionMap;
	CCar & m_car;
	istream & m_input;
	ostream & m_output;
	const ActionMap m_actionMap;
};


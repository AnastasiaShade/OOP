#pragma once
#include <string>
#include <map>
#include <iterator>

using namespace std;

enum struct Gear
{
	REAR = -1,
	NEUTRAL,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};


enum struct Direction
{
	BACKWARD = -1,
	STAY,
	FORWARD
};

using Speed = pair<int, int>;

static const map<Gear, Speed> SpeedRange = {
	{ Gear::REAR, Speed(0, 20) },
	{ Gear::NEUTRAL, Speed(0, 150) },
	{ Gear::FIRST, Speed(0, 30) },
	{ Gear::SECOND, Speed(20, 50) },
	{ Gear::THIRD, Speed(30, 60) },
	{ Gear::FOURTH, Speed(40, 90) },
	{ Gear::FIFTH, Speed(50, 150) }
};

class CCar
{
public:
	CCar();
	~CCar() = default;
	string Info()const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	bool IsEngineOn()const;
	int GetCurrentSpeed()const;
	int GetCurrentGear()const;
	string GetCurrentDirection()const;

private:
	bool IsValidGear(int gear)const;
	bool CCar::IsValidSpeed(const Gear &gear, const int &speed)const;
	bool ChangeGear(int gear);
	bool m_isTurnOn;
	Gear m_currentGear;
	Direction m_direction;
	int m_speed;
};


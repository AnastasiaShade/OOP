#include "stdafx.h"
#include "Controller.h"

using namespace std;
using namespace std::placeholders;

CController::CController(vector<shared_ptr<CBody>> &bodies, istream &input, ostream &output)
	: m_bodies(bodies)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "Info", bind(&CController::Info, this) },
		{ "Sphere", bind(&CController::CreateSphere, this, _1) },
		{ "Parallelepiped", bind(&CController::CreateParallelepiped, this, _1) },
		{ "Cone", bind(&CController::CreateCone, this, _1) },
		{ "Cylinder", bind(&CController::CreateCylinder, this, _1) },
})
{
}

bool CController::HandleCommand()
{
	string commandLine;
	if (getline(m_input, commandLine))
	{
		istringstream strm(commandLine);
		string action;
		strm >> action;
		auto it = m_actionMap.find(action);
		if (it != m_actionMap.end())
		{
			return it->second(strm);
		}
	}
	return false;
}

bool CController::Info()
{
	m_output << "available commands:\n"
		<< "1) Sphere <density> <radius>\n"
		<< "2) Parallelepiped <density> <width> <height> <depth>\n"
		<< "3) Cone <density> <radius> <height>\n"
		<< "4) Cylinder <density> <radius> <height>\n";
	return true;
}

bool CController::CreateSphere(istream &args)
{
	double density;
	double radius;
	if (!(args >> density) || !(args >> radius))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Sphere <density> <radius>\n";
		return false;
	}	
	try
	{
		shared_ptr<CBody> sphere = make_shared<CSphere>(density, radius);
		m_bodies.push_back(sphere);
	}
	catch (invalid_argument const &err)
	{
		m_output << err.what();
	}
	
	return true;
}

bool CController::CreateParallelepiped(istream &args)
{
	double width;
	double height;
	double length;
	double density;

	if (!(args >> density) || !(args >> length) || !(args >> width) || !(args >> height))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Parallelepiped <width> <height> <depth> <density>\n";
		return false;
	}
	try
	{
		shared_ptr<CBody> parallelepiped = make_shared<CParallelepiped>(density, length, width, height);
		m_bodies.push_back(parallelepiped);
	}
	catch (invalid_argument const &err)
	{
		m_output << err.what();
	}

	return true;
}

bool CController::CreateCone(istream &args)
{
	double density;
	double radius;
	double height;

	if (!(args >> density) || !(args >> radius) || !(args >> height))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Cone <density> <radius> <height>\n";
		return false;
	}
	try
	{
		shared_ptr<CBody> cone = make_shared<CCone>(density, radius, height);
		m_bodies.push_back(cone);
	}
	catch (invalid_argument const &err)
	{
		m_output << err.what();
	}

	return true;
}

bool CController::CreateCylinder(istream &args)
{
	double density;
	double radius;
	double height;

	if (!(args >> density) || !(args >> radius) || !(args >> height))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Cylinder <density> <radius> <height>\n";
		return false;
	}
	try
	{
		shared_ptr<CBody> cylinder = make_shared<CCylinder>(density, radius, height);
		m_bodies.push_back(cylinder);
	}
	catch (invalid_argument const &err)
	{
		m_output << err.what();
	}

	return true;
}

void CController::PrintAllBodies(vector<shared_ptr<CBody>> const &bodies, ostream &output)
{
	if (!bodies.empty())
	{
		for (auto &body : bodies)
		{
			output << body->ToString();
		}
	}
	else
	{
		output << "You have not entered figures\n";
	}
}

void CController::FindBodyWithMaxMass(vector<shared_ptr<CBody>> const &bodies)
{
	if (!bodies.empty())
	{
		auto IsMassLarger = [](shared_ptr<CBody> const &a, shared_ptr<CBody> const &b)
		{
			return a->GetMass() < b->GetMass();
		};
		cout << "Body with max mass is " << (*max_element(bodies.begin(), bodies.end(), IsMassLarger))->ToString();
	}
}

void CController::FindBodyWithSmallestWeight(vector<shared_ptr<CBody>> const &bodies)
{
	if (!bodies.empty())
	{
		static const double WATER_DENSITY = 1000;
		static const double GRAVITY_CONST = 9.8f;

		auto IsWeightLess = [](shared_ptr<CBody> const &a, shared_ptr<CBody> const &b)
		{
			return ((a->GetDensity() - WATER_DENSITY) * GRAVITY_CONST * a->GetVolume()) >
				((b->GetDensity() - WATER_DENSITY) * GRAVITY_CONST * b->GetVolume());
		};

		cout << "Body with smallest weight is " << (*min_element(bodies.begin(), bodies.end(), IsWeightLess))->ToString();
	}
}
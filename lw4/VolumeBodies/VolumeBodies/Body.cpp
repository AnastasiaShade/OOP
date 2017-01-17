#include "stdafx.h"
#include "Body.h"

CBody::CBody(const std::string & type, double density)
	: m_density(density)
	, m_type(type)
{
	if (m_density < 0)
	{
		throw std::invalid_argument("Density should not be negative");
	}
}

double CBody::GetDensity()const
{
	return m_density;
}

double CBody::GetMass()const
{
	return GetVolume() * m_density;
}

std::string CBody::ToString()const
{
	std::ostringstream strm;
	strm << m_type << ":" << std::endl << std::setprecision(10);
	strm << "\tdensity = " << GetDensity() << std::endl;
	strm << "\tvolume = " << GetVolume() << std::endl;
	strm << "\tmass = " << GetMass() << std::endl;
	AppendProperties(strm);
	return strm.str();
}
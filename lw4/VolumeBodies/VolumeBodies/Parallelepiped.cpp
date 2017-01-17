#include "stdafx.h"
#include "Parallelepiped.h"


CParallelepiped::CParallelepiped(double density, double length, double width, double height)
	: CBody("Parallelepiped", density)
	, m_length(length)
	, m_width(width)
	, m_height(height)
{
	if (m_length < 0)
	{
		throw std::invalid_argument("Length should not be negative");
	}
	if (m_width < 0)
	{
		throw std::invalid_argument("Width should not be negative");
	}
	if (m_height < 0)
	{
		throw std::invalid_argument("Height should not be negative");
	}
}

double CParallelepiped::GetLength() const
{
	return m_length;
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetVolume() const
{
	return m_length * m_height * m_width;
}

void CParallelepiped::AppendProperties(std::ostream & strm) const
{
	strm << "\tlength = " << GetLength() << std::endl
		<< "\twidth = " << GetWidth() << std::endl
		<< "\theight = " << GetHeight() << std::endl;
}
#pragma once
#include "Body.h"

class CParallelepiped final
	: public CBody
{
public:
	CParallelepiped(double density, double length, double width, double height);
	~CParallelepiped() = default;
	double GetWidth() const;
	double GetHeight() const;
	double GetLength() const;
	double GetVolume() const override;

protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	double m_height;
	double m_width;
	double m_length;
};


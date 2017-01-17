#pragma once
#include "Body.h"

class CCylinder final
	: public CBody
{
public:
	CCylinder(double density, double radius, double height);
	~CCylinder() = default;
	double GetRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

protected:
	void AppendProperties(std::ostream & strm) const override;
private:
	double m_height;
	double m_radius;
};

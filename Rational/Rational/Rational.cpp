#include "stdafx.h"
#include "Rational.h"
#include <sstream>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////
double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////
const CRational CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);;
}

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
//////////////////////////////////////////////////////////////////////////
const CRational operator+(const CRational & lRational, const CRational & rRational)
{
	int resultNumerator = lRational.GetNumerator() * rRational.GetDenominator() + rRational.GetNumerator() * lRational.GetDenominator();
	int resultDenominator = lRational.GetDenominator() * rRational.GetDenominator();
	return CRational(resultNumerator, resultDenominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////
const CRational operator-(const CRational & lRational, const CRational & rRational)
{
#pragma message("use +")
	return lRational + (-rRational);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator+=(const CRational & rRational)
{
	*this = *this + rRational;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator-=(const CRational & rRational)
{
#pragma message("use +=")
	*this = *this + CRational(-rRational.GetNumerator(), rRational.GetDenominator());
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////
const CRational operator*(const CRational & lRational, const CRational & rRational)
{
	int resultNumerator = lRational.GetNumerator() * rRational.GetNumerator();
	int resultDenominator = lRational.GetDenominator() * rRational.GetDenominator();
	return CRational(resultNumerator, resultDenominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////
const CRational operator/(const CRational & lRational, const CRational & rRational)
{
#pragma message("use *")
	if (rRational.GetNumerator() == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	return lRational * CRational(rRational.GetDenominator(), rRational.GetNumerator());
}

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator*=(const CRational & rRational)
{
	*this = *this * rRational;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator/=(const CRational & rRational)
{
#pragma message("use *=")
	if (rRational.GetNumerator() == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	*this = *this * CRational(rRational.GetDenominator(), rRational.GetNumerator());
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////
const bool operator==(const CRational & lRational, const CRational & rRational)
{
	return ((lRational.GetNumerator() == rRational.GetNumerator()) && (lRational.GetDenominator() == rRational.GetDenominator()));
}

const bool operator!=(const CRational & lRational, const CRational & rRational)
{
#pragma message("use ==")
	return !(lRational == rRational);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////
const bool operator<(const CRational & lRational, const CRational & rRational)
{
	return ((lRational.GetNumerator() * rRational.GetDenominator()) < (rRational.GetNumerator() * lRational.GetDenominator()));
}

const bool operator>(const CRational & lRational, const CRational & rRational)
{
	return ((lRational.GetNumerator() * rRational.GetDenominator()) > (rRational.GetNumerator() * lRational.GetDenominator()));
}

const bool operator<=(const CRational & lRational, const CRational & rRational)
{
#pragma message("use >")
	return !(lRational > rRational);
}

const bool operator>=(const CRational & lRational, const CRational & rRational)
{
#pragma message("use <")
	return !(lRational < rRational);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& stream, CRational const& rational)
{
	stream << std::to_string(rational.GetNumerator()) << "/" << std::to_string(rational.GetDenominator());
	return stream;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//////////////////////////////////////////////////////////////////////////
std::istream& operator>>(std::istream& stream, CRational & rational)
{
	int denominator = 1;
	int numerator = 0;
	if ((stream >> numerator) && (stream.get() == '/') && (stream >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
	}
	return stream;
}

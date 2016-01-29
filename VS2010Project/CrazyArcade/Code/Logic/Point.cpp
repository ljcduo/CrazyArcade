#include "Point.h"


Point::Point(float x, float y) : m_x(x),m_y(y)
{

}
 
Point::Point() : m_x(-1.0f),m_y(-1.0f)
{

}

Point::Point(int x, int y): m_x(static_cast<float>(x)),m_y(static_cast<float>(y))
{

}

float const& Point::GetX() const
{
	return m_x;
}

void Point::SetX(float val)
{
	m_x = val;
}

void Point::SetX(int val)
{
	m_x = static_cast<float>(val);
}

float const& Point::GetY() const
{
	return m_y;
}

void Point::SetY(float val)
{
	m_y = val;
}

void Point::SetY(int val)
{
	m_y = static_cast<float>(val);
}

int Point::GetXInt() const
{
	return static_cast<int>(m_x);
}

int Point::GetYInt() const
{
	return static_cast<int>(m_y);
}



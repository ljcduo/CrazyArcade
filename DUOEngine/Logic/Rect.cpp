#include "Rect.h"




LGRect::LGRect(float x, float y, float width, float height)
	:m_x(x), m_y(y), m_width(width),m_height(height)
{

}

float const& LGRect::GetX() const
{
	return m_x;
}

void LGRect::SetX(float val)
{
	m_x = val;
}

float const& LGRect::GetY() const
{
	return m_y;
}

float const& LGRect::GetWidth() const
{
	return m_width;
}

void LGRect::SetWidth(float val)
{
	m_width = val;
}

float const& LGRect::GetHeight() const
{
	return m_height;
}

void LGRect::SetHeight(float val)
{
	m_height = val;
}

void LGRect::SetY(float val)
{
	m_y = val;
}

int LGRect::GetXInt() const
{
	return static_cast<int>(m_x);
}

int LGRect::GetYInt() const
{
	return static_cast<int>(m_y);
}

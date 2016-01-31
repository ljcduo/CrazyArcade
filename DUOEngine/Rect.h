#pragma once

class LGRect
{
public:
	LGRect(float x = 0, float y = 0, float width = 0, float height = 0);
	float const& GetX() const;
	int GetXInt() const;
	void SetX(float val);
	float const& GetY() const;
	int GetYInt() const;
	void SetY(float val);
	float const& GetWidth() const;
	void SetWidth(float val);
	float const& GetHeight() const;
	void SetHeight(float val);
private:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
};
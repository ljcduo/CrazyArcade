#pragma once

#include "LGHead.h"

class Point
{
public:
	Point(float x, float y);
	Point(int x, int y);
	Point();
	float const& GetX() const;
	int GetXInt() const;
	void SetX(float val);
	void SetX(int val);
	float const& GetY() const;
	int GetYInt() const;
	void SetY(int val);
	void SetY(float val);
private:
	float m_x;
	float m_y;
};
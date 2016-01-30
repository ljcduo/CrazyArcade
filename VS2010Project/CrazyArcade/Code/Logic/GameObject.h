#pragma once
#include "Object.h"

class GameObject : public Object
{
public:
	Point CalPixelPos(int mapPosX, int mapPosY);
	Point CalMapPos(Point pixelPos);
	void UpdateMapPos();
	virtual int const& GetMapPosX() const;
	virtual void SetMapPosX(int val);
	virtual int const& GetMapPosY() const;
	virtual void SetMapPosY(int val);
};


#pragma once
#include "Object.h"

class GameObject : public Object
{
public:
	GameObject();
	GameObject(int mapPosX, int mapPoxY);
	Point CalPixelPos(int mapPosX, int mapPosY);
	Point CalMapPos(Point pixelPos);
	void UpdateMapPos();
	int const& MapPosX() const;
	void MapPosX(int val);
	int const& MapPosY() const;
	void MapPosY(int val);
private:
	//原点在左下角
	int m_mapPosX;
	int m_mapPosY;
};


#include "GameObject.h"
#include "GameUtil.h"

Point GameObject::CalPixelPos(int mapPosX, int mapPosY)
{
	return Point(Util::ORIGINPIX.GetX() + mapPosX * Util::MAPPIECEPIX,Util::ORIGINPIX.GetY() + mapPosY * Util::MAPPIECEPIX);
}


Point GameObject::CalMapPos(Point pixelPos)
{
	return Point( (pixelPos.GetX() + Util::MAPPIECEPIX/2 - Util::ORIGINPIX.GetX()) / Util::MAPPIECEPIX ,
		(pixelPos.GetY() + Util::MAPPIECEPIX/2 - Util::ORIGINPIX.GetY()) / Util::MAPPIECEPIX );
}

void GameObject::UpdateMapPos()
{
	Point MapPos = CalMapPos(m_pixelPos);
	m_mapPosX = static_cast<int>(MapPos.GetX());
	m_mapPosY = static_cast<int>(MapPos.GetY());
}

int const& GameObject::GetMapPosX() const
{
	return m_mapPosX;
}

void GameObject::SetMapPosX(int val)
{
	m_mapPosX = val;
}

int const& GameObject::GetMapPosY() const
{
	return m_mapPosY;
}

void GameObject::SetMapPosY(int val)
{
	m_mapPosY = val;
}


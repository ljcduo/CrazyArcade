#include "GameObject.h"
#include "GameUtil.h"

GameObject::GameObject(int mapPosX, int mapPoxY)
{
	MapPosX(mapPosX);
	MapPosY(mapPoxY);
}

GameObject::GameObject()
{

}

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
	if (m_mapPosX != m_LastMapPosX || m_mapPosY != m_LastMapPosY)
	{
		m_LastMapPosX = m_mapPosX;
		m_LastMapPosY = m_mapPosY;
		MapPosChanged(true);
	}
}

int const& GameObject::MapPosX() const
{
	return m_mapPosX;
}

void GameObject::MapPosX(int val)
{
	m_mapPosX = val;
}

int const& GameObject::MapPosY() const
{
	return m_mapPosY;
}

void GameObject::MapPosY(int val)
{
	m_mapPosY = val;
}


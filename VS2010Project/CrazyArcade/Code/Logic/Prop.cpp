#include "GameUtil.h"
#include "prop.h"
#include "PlayScene.h"

const float ANIMATESPEED = 5.0f;

Prop::Prop(int mapPosX, int mapPosY, std::wstring picPath, E_PropType propType)
{
	m_visiable = false;

	m_mapPosX = mapPosX;
	m_mapPosY = mapPosY;

	m_objName = Util::CreateMapName(mapPosX,mapPosY,L"Prop");

	m_currentSprite = Sprite(picPath,1,3,0,0,ANIMATESPEED);

	m_Layout = LayoutType::E_Props;

	m_pixelPos = CalPixelPos(mapPosX,mapPosY);

	m_ObjectType = ObjectType::E_Prop;

	m_dirty = false;

	m_RectCollision = LGRect(m_pixelPos.GetX(),m_pixelPos.GetY(),static_cast<float>(Util::MAPPIECEPIX),static_cast<float>(Util::MAPPIECEPIX));

	m_PropType = propType;
}

Prop::Prop() 
{
	m_visiable = false;
	m_dirty = false;
}

Prop::~Prop()
{
	
}

Prop::E_PropType const& Prop::GetPropType() const
{
	return m_PropType;
}

void Prop::SetPropType(E_PropType val)
{
	m_PropType = val;
}

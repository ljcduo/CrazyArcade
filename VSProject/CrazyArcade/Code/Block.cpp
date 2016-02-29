#include "Block.h"
#include "prop.h"
#include "Scene.h"
#include "PlayScene.h"
#include "LGCenter.h"

Prop* const& Block::GetInsideProp() const
{
	return m_pInsideProp;
}

void Block::SetInsideProp(Prop* val)
{
	m_pInsideProp = val;
}

Block::Block(int mapPosX, int mapPosY, MapType::E_MapType blockType) : GameObject(mapPosX,mapPosY),m_pInsideProp(NULL), m_Animate(false)
{
	m_objName = Util::CreateMapName(mapPosX,mapPosY,L"Block");
	m_pixelPos = CalPixelPos(MapPosX(),MapPosY());
	m_ObjectType = ObjectType::E_ObjBlock;
	UpdateRectCollision();

	switch(blockType)
	{
	case MapType::E_TownBlockRed:
		{
			m_currentSprite = Sprite(L"Resource\\TownBlockRed.bmp");
			m_Layout = LayoutType::E_Blocks;
			break;
		}
	case MapType::E_TownBlockYellow:
		{
			m_currentSprite = Sprite(L"Resource\\TownBlockYellow.bmp");
			m_Layout = LayoutType::E_Blocks;
			break;
		}
	case MapType::E_TownBox:
		{
			m_currentSprite = Sprite(L"Resource\\TownBox.bmp");
			m_Layout = LayoutType::E_Blocks;
			break;
		}
	case MapType::E_SandBox:
		{
			m_currentSprite = Sprite(L"Resource\\SandBox.png");
			m_Layout = LayoutType::E_Blocks;
			break;
		}
	case MapType::E_SandBlockBuff:
		{
			m_currentSprite = Sprite(L"Resource\\SandBlockBuff.png");
			m_Layout = LayoutType::E_Blocks;
			break;
		}
	case MapType::E_SandBlockYellow:
		{
			m_currentSprite = Sprite(L"Resource\\SandBlockYellow.png");
			m_Layout = LayoutType::E_Blocks;
			break;
		}
	case MapType::E_RedHouse:
		{
			m_currentSprite = Sprite(L"Resource\\TownHouseRed.png");
			m_Layout = LayoutType::E_Soild;
			break;
		}
	case MapType::E_YellowHouse:
		{
			m_currentSprite = Sprite(L"Resource\\TownHouseYellow.png");
			m_Layout = LayoutType::E_Soild;
			break;
		}
	case MapType::E_BlueHouse:
		{
			m_currentSprite = Sprite(L"Resource\\TownHouseBlue.png");
			m_Layout = LayoutType::E_Soild;
			break;
		}
	case MapType::E_Tree:
		{
			m_currentSprite = Sprite(L"Resource\\TownTree.png");
			m_Layout = LayoutType::E_Soild;
			break;
		}
	case MapType::E_TownWindmill:
		{
			m_currentSprite = Sprite(L"Resource\\TownWindmill.png");
			Point tempPoint = CalPixelPos(MapPosX(),MapPosY()-1);
			m_pixelPos = Point(tempPoint.GetX(),tempPoint.GetY() + 15);
			m_Layout = LayoutType::E_UnderBubbles;
			m_ObjectType = ObjectType::E_Build;
			break;
		}
	case MapType::E_TownWindmillAni:
		{
			m_currentSprite = Sprite(L"Resource\\TownWindmillAni.png",1,2,0,0,2);
			Point tempPoint = CalPixelPos(MapPosX()-1,MapPosY());
			m_pixelPos = Point(tempPoint.GetX(),tempPoint.GetY()+ 37);
			m_Animate = true;
			m_Layout = LayoutType::E_Soild;
			m_ObjectType = ObjectType::E_Build;
			break;
		}
	case MapType::E_Solid:
		{
			m_currentSprite = Sprite(L"Resource\\Soild.png");
			m_Layout = LayoutType::E_Soild;
			break;
		}
	}
	
	
	//初始化方块内的道具
	if (m_Layout == LayoutType::E_Blocks)
	{
		std::wstring picPath;
		Prop::E_PropType propType;
		switch(rand() % 5)
		{
		case Prop::E_Popo:
			{
				picPath = L"Resource\\GiftPoPo.png";
				propType = Prop::E_Popo;
				break;
			}
		case Prop::E_Power:
			{
				picPath = L"Resource\\GiftPower.png";
				propType = Prop::E_Power;
				break;
			}
		case Prop::E_Run1:
			{
				picPath = L"Resource\\GiftRun1.png";
				propType = Prop::E_Run1;
				break;
			}
		default:
			{
				return;
			}
		}

		m_pInsideProp = new Prop(MapPosX(),MapPosY(),picPath,propType);
		g_pLGCenter->GetCurrentScene()->InsertObject(m_pInsideProp);

	}
}

Block::~Block()
{
	if (g_pLGCenter->GetCurrentScene()->GetGameEnd())
	{
		return;
	}

	if (m_pInsideProp)
	{
		m_pInsideProp->SetVisiable(true);
		m_pInsideProp->SpreadDirty();
		static_cast<PlayScene*>(g_pLGCenter->GetCurrentScene())->ChangeMap(MapPosX(),MapPosY(),MapType::E_Prop);
	}
	else
	{
		static_cast<PlayScene*>(g_pLGCenter->GetCurrentScene())->ChangeMap(MapPosX(),MapPosY(),MapType::E_None);
	}
}

void Block::Update(float deltaTime)
{
	if (m_Animate)
	{
		UpdateAnimateFrame(deltaTime);
	}
}
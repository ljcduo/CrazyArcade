#include "GameUtil.h"
#include "Role.h"
#include "RoleState.h"
#include "LGInput.h"
#include "Prop.h"
#include "PlayScene.h"
#include "LGCenter.h"
#include <string>
using namespace std;

Point Role::m_standOnBubble = Point(-1,-1);

Role::Role(std::wstring objName, int mapPosX, int mapPosY, E_RoleSpriteType spriteType)
	:GameObject(mapPosX, mapPosY), m_direction(E_Down), m_CanMove(true), m_FullyEnter(false)
{

	m_objName = objName;

	switch (spriteType)
	{
	case E_RedBaby:
	{
		m_currentSprite = Sprite(L"Resource\\Role1.png", 4, 6, 0, 0, 24.0f);
		break;
	}
	case E_BrownPirate:
	{
		m_currentSprite = Sprite(L"Resource\\Role2.png", 4, 6, 0, 0, 24.0f);
		break;
	}
	}

	m_Layout = LayoutType::E_Roles;

	m_ObjectType = ObjectType::E_ObjRole;

	m_pStateMachine = new StateMachine<Role>(this);
	m_pStateMachine->SetCurrentState(IdleDown::Instance());
	Point tempPoint = CalPixelPos(mapPosX, mapPosY);
	m_pixelPos = Point(tempPoint.GetX() - 4, tempPoint.GetY() - 2);
	UpdateMapPos();
	UpdateRectCollision();
	m_pAbility = new Ability();
	m_WalkSpeed = 200.0f + m_pAbility->GetRunSpeed() * 50;
}

void Role::Update(float deltaTime)
{
	m_pStateMachine->Update(deltaTime);
	m_WalkSpeed = 200.0f + m_pAbility->GetRunSpeed() * 50;
}

float const& Role::GetWalkSpeed() const
{
	return m_WalkSpeed;
}

void Role::SetWalkSpeed(float val)
{
	m_WalkSpeed = val;
}

StateMachine<Role>* const& Role::GetStateMachine() const
{
	return m_pStateMachine;
}

void Role::Move(float deltaTime)
{
	//1、进行碰撞检测

	//当前贴合方格位置
	Point curFullyMap = CalPixelPos(MapPosX(), MapPosY());
	PlayScene* currentScene = static_cast<PlayScene*>(g_pLGCenter->GetCurrentScene());
	PlayScene::Map2DVec map = currentScene->MapBlock();
	const int DriftOffset = 20; //漂移偏差
	//判断前面障碍物
	switch (m_direction)
	{
	case Role::E_Up:
	{
		if (GetRectCollision().GetYInt() == curFullyMap.GetYInt()) //贴合
		{
			RecoveDirect(); //结束上次漂移
			if(MapPosY() + 1 >= YLENGTH || (map[MapPosX()][MapPosY()+1] != MapType::E_None && map[MapPosX()][MapPosY()+1] != MapType::E_Prop)) //撞墙不移动	
				return;

			int XOffset = GetRectCollision().GetXInt() - curFullyMap.GetXInt();
			
			if ( MapPosX() + 1 < XLENGTH && MapPosY() + 1 < YLENGTH &&
				map[MapPosX()+1][MapPosY()+1] != MapType::E_None 
				&& XOffset > 0 && XOffset <= DriftOffset && XOffset != 0 ) //符合左漂移
			{
				SetDirection(Role::E_Left);
			}
			else if ( MapPosX() - 1 >= 0 && MapPosY() + 1 < YLENGTH &&
				map[MapPosX() - 1][MapPosY() + 1] != MapType::E_None
				&& -XOffset > 0 && -XOffset <= DriftOffset && XOffset != 0) //符合右漂移
			{
				SetDirection(Role::E_Right);
			}

		}
		break;
	}
	case Role::E_Down:
	{
		if (GetRectCollision().GetYInt() == curFullyMap.GetYInt()) //贴合
		{
			RecoveDirect(); //结束上次漂移
			if(MapPosY() - 1 < 0 ||(map[MapPosX()][MapPosY()-1] != MapType::E_None && map[MapPosX()][MapPosY()-1] != MapType::E_Prop)) //撞墙不移动	
				return;

			int XOffset = GetRectCollision().GetXInt() - curFullyMap.GetXInt();

			if (MapPosX() + 1 < XLENGTH && MapPosY() - 1 >= 0 &&
				map[MapPosX() + 1][MapPosY() - 1] != MapType::E_None
				&& XOffset > 0 && XOffset <= DriftOffset && XOffset != 0) //符合左漂移
			{
				SetDirection(Role::E_Left);
			}
			else if (MapPosX() - 1 >= 0 && MapPosY() - 1 >= 0 &&
				map[MapPosX() - 1][MapPosY() - 1] != MapType::E_None
				&& -XOffset > 0 && -XOffset <= DriftOffset && XOffset != 0) //符合右漂移
			{
				SetDirection(Role::E_Right);
			}

		}

		break;
	}
	case Role::E_Left:
	{	
		if (GetRectCollision().GetXInt() == curFullyMap.GetXInt() )//贴合		
		{
			RecoveDirect(); //结束上次漂移
			if(MapPosX() - 1 < 0  || (map[MapPosX()-1][MapPosY()] != MapType::E_None && map[MapPosX()-1][MapPosY()] != MapType::E_Prop))	//撞墙不移动
				return;

			int YOffset = GetRectCollision().GetYInt() - curFullyMap.GetYInt();

			if (MapPosX() - 1 >= 0 && MapPosY() + 1 < YLENGTH &&
				map[MapPosX() - 1][MapPosY() + 1] != MapType::E_None
				&& YOffset > 0 && YOffset <= DriftOffset && YOffset != 0) //符合下漂移
			{
				SetDirection(Role::E_Down);
			}
			else if (MapPosX() - 1 >= 0 && MapPosY() - 1 >= 0 &&
				map[MapPosX() - 1][MapPosY() - 1] != MapType::E_None
				&& -YOffset > 0 && -YOffset <= DriftOffset && YOffset != 0) //符合上漂移
			{
				SetDirection(Role::E_Up);
			}

		}
		break;
	}
	case Role::E_Right:
	{
		if (GetRectCollision().GetXInt() == curFullyMap.GetXInt())  //贴合
		{
			RecoveDirect(); //结束上次漂移
			if (MapPosX() + 1 >= XLENGTH || (map[MapPosX()+1][MapPosY()] != MapType::E_None && map[MapPosX()+1][MapPosY()] != MapType::E_Prop) != MapType::E_None)	//撞墙不移动	
			{
				return;
			}

			int YOffset = GetRectCollision().GetYInt() - curFullyMap.GetYInt();

			if (MapPosX() + 1 < XLENGTH && MapPosY() + 1 < YLENGTH &&
				map[MapPosX() + 1][MapPosY() + 1] != MapType::E_None
				&& YOffset > 0 && YOffset <= DriftOffset && YOffset != 0) //符合下漂移
			{
				SetDirection(Role::E_Down);
			}
			else if (MapPosX() + 1 < XLENGTH && MapPosY() - 1 >= 0 &&
				map[MapPosX() + 1][MapPosY() - 1] != MapType::E_None
				&& -YOffset > 0 && -YOffset <= DriftOffset && YOffset != 0) //符合上漂移
			{
				SetDirection(Role::E_Up);
			}
		}
		break;
	}
	default:
		break;
	}



	//2、进行移动
	int move = m_WalkSpeed * deltaTime;

	switch (m_direction)
	{
	case Role::E_Up:
	{
		int newY = GetRectCollision().GetY() + move;
		if (newY > curFullyMap.GetYInt() && curFullyMap.GetYInt() > GetRectCollision().GetYInt()) //临界进行贴合
		{
			SetPixelPosY(GetPixelPosY() + (curFullyMap.GetYInt() - GetRectCollision().GetYInt()));
			Util::DebugOut() << "向上贴合！" << GetRectCollision().GetXInt();
		}
		else //非临界任意移动
		{
			SetPixelPosY(GetPixelPosY() + move);
			FullyEnter(false);
		}
		break;
	}
	case Role::E_Down:
	{
		int newY = GetRectCollision().GetY() - move;
		if (newY < curFullyMap.GetYInt() && curFullyMap.GetYInt() < GetRectCollision().GetYInt()) //临界进行贴合
		{
			SetPixelPosY(GetPixelPosY() - (GetRectCollision().GetYInt() - curFullyMap.GetYInt()));
			Util::DebugOut() << "向下贴合！" << GetRectCollision().GetXInt();
		}
		else //非临界任意移动
		{
			SetPixelPosY(GetPixelPosY() - move);
			FullyEnter(false);
		}
		break;
	}
	case Role::E_Left:
	{
		int newX = GetRectCollision().GetX() - move;
		if (newX < curFullyMap.GetXInt() && curFullyMap.GetXInt() < GetRectCollision().GetXInt()) //临界进行贴合
		{
			SetPixelPosX(GetPixelPosX() - (GetRectCollision().GetXInt() - curFullyMap.GetXInt()));
			Util::DebugOut() << "向左贴合！" << GetRectCollision().GetXInt();
		}
		else //非临界任意移动
		{
			SetPixelPosX(GetPixelPosX() - move);
		}
		break;
	}
	case Role::E_Right:
	{
		int newX = GetRectCollision().GetX() + move;
		if (newX > curFullyMap.GetXInt() && curFullyMap.GetXInt() > GetRectCollision().GetXInt()) //临界进行贴合
		{
			SetPixelPosX(GetPixelPosX() + (curFullyMap.GetXInt() - GetRectCollision().GetXInt()));
			Util::DebugOut() << "向右贴合！" << GetRectCollision().GetXInt();
		}
		else //非临界任意移动
		{
			SetPixelPosX(GetPixelPosX() + move);
		}
		break;
	}
	default:
		break;
	}

	UpdateMapPos();
	UpdateRectCollision();

	if (MapPosChanged())
	{
		SetStandOnBubble(false); //当位置改变，设置离开泡泡，避免放不出泡泡
		if (map[MapPosX()][MapPosY()] == MapType::E_Prop) //判断脚下是否有道具
		{
			EatProp(static_cast<Prop*>(currentScene->GetGameObject(MapPosX(), MapPosY())));
		}
	}

}

Role::E_RoleDirection const& Role::GetDirection() const
{
	return m_direction;
}

void Role::SetDirection(E_RoleDirection val)
{
	m_direction = val;
}


bool const& Role::GetCanMove() const
{
	return m_CanMove;
}

void Role::SetCanMove(bool val)
{
	m_CanMove = val;
}

Ability* const& Role::GetAbility() const
{
	return m_pAbility;
}

void Role::SetAbility(Ability* val)
{
	m_pAbility = val;
}

bool Role::HandleMessage(const Telegram& telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}

Point const& Role::GetStandOnBubble() const
{
	return m_standOnBubble;
}

void Role::SetStandOnBubble(bool val)
{
	if (val == true)
	{
		m_standOnBubble = Point(MapPosX(), MapPosY());
	}
	else
	{
		m_standOnBubble = Point(-1, -1);
	}
}

bool Role::IsStandOnBubble()
{
	if (m_standOnBubble.GetX() != -1
		&& m_standOnBubble.GetY() != -1)
	{
		return false;
	}
	else
		return true;
}

Role::~Role()
{
	delete m_pStateMachine;
	delete m_pAbility;
}

void Role::EatProp(Prop* prop)
{
	switch (prop->GetPropType())
	{
	case Prop::E_Popo:
	{
		m_pAbility->Crease(Ability::E_BubbleNum);
		break;
	}
	case Prop::E_Power:
	{
		m_pAbility->Crease(Ability::E_Power);
		break;
	}
	case Prop::E_Run1:
	{
		m_pAbility->Crease(Ability::E_RunSpeed);
		break;
	}
	default:
	{
		return;
	}
	}

	PlayScene* currentScene = static_cast<PlayScene*>(g_pLGCenter->GetCurrentScene());
	currentScene->DeleteObject(prop->GetObjID());
	currentScene->ChangeMap(MapPosX(), MapPosY(), MapType::E_None);
}

void Role::StopWalk()
{
	switch (this->GetDirection())
	{
	case E_RoleDirection::E_Up:
	{
		this->GetStateMachine()->ChangeState(IdleUp::Instance());
		break;
	}
	case E_RoleDirection::E_Down:
	{
		this->GetStateMachine()->ChangeState(IdleDown::Instance());
		break;
	}
	case E_RoleDirection::E_Left:
	{
		this->GetStateMachine()->ChangeState(IdleLeft::Instance());
		break;
	}
	case E_RoleDirection::E_Right:
	{
		this->GetStateMachine()->ChangeState(IdleRight::Instance());
		break;
	}
	}
}

bool Role::IsFullyArrive()
{
	return (GetPixelPosY() == Util::ORIGINPIX.GetX() + MapPosX()*Util::MAPPIECEPIX
		&& GetPixelPosY() == Util::ORIGINPIX.GetY() + MapPosY()*Util::MAPPIECEPIX);
}

void Role::FullyArrive()
{
	switch (this->GetDirection())
	{
	case E_RoleDirection::E_Up:
	{
		SetDirection(Role::E_Left);
		return;
	}
	case E_RoleDirection::E_Down:
	{
		SetPixelPosY(Util::ORIGINPIX.GetY() + MapPosY()*Util::MAPPIECEPIX);
		break;
	}
	case E_RoleDirection::E_Left:
	{
		SetPixelPosX(Util::ORIGINPIX.GetX() + MapPosX()*Util::MAPPIECEPIX);
		break;
	}
	case E_RoleDirection::E_Right:
	{
		SetPixelPosX(Util::ORIGINPIX.GetX() + MapPosX()*Util::MAPPIECEPIX);
		break;
	}
	}
}

void Role::UpdateRectCollision(int offsetX /*= 0*/, int offsetY /*= 0*/, int offsetWidth /*= 0*/, int offsetHeight /*= 0*/)
{
	Object::UpdateRectCollision(4, 2, -8, -24); //设置角色碰撞体
}

void Role::RecoveDirect()
{
	wstring roleState = static_cast<RoleState*>(GetStateMachine()->GetCurrentState())->GetRoleStateName();

	if (roleState == L"WalkUp")
	{
		SetDirection(Role::E_Up);
	}
	else if (roleState == L"WalkDown")
	{
		SetDirection(Role::E_Down);
	}
	else if (roleState == L"WalkLeft")
	{
		SetDirection(Role::E_Left);
	}
	else if (roleState == L"WalkRight")
	{
		SetDirection(Role::E_Right);
	}

}


#include "GameUtil.h"
#include "Role.h"
#include "RoleState.h"
#include "LGInput.h"
#include "Prop.h"
#include "PlayScene.h"

Role::Role(std::wstring objName, int mapPosX, int mapPosY, E_RoleSpriteType spriteType)
	:GameObject(mapPosX, mapPosY), m_direction(E_Down), m_CanMove(true)
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
	m_pixelPos = Point(tempPoint.GetX() - 4, tempPoint.GetY() + 2);
	UpdateRectCollision(4, -2);
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
	bool drift = false;

	if (m_direction != m_currentSprite.GetCurrentRow()) //判断是否“漂移”中，进而防止漂移过度
	{
		drift = true;
	}

	if (m_CanMove)
	{
		switch (m_direction)
		{
		case E_Up:
		{
			float newY = m_pixelPos.GetY() + m_WalkSpeed * deltaTime;
			float MaxY = m_CollsionPixelPos.GetY() + Util::MAPPIECEPIX + 2;
			if (drift && newY >= MaxY)
			{
				SetPixelPosY(MaxY);
			}
			else
			{
				SetPixelPosY(newY);
			}
			break;
		}
		case E_Down:
		{
			float newY = m_pixelPos.GetY() - m_WalkSpeed * deltaTime;
			float MinY = m_CollsionPixelPos.GetY() - Util::MAPPIECEPIX + 2;
			if (drift && newY <= MinY)
			{
				SetPixelPosY(MinY);
			}
			else
			{
				SetPixelPosY(newY);
			}
			break;
		}
		case E_Left:
		{
			float newX = m_pixelPos.GetX() - m_WalkSpeed * deltaTime;
			float MinX = m_CollsionPixelPos.GetX() - Util::MAPPIECEPIX - 4;
			if (drift && newX <= MinX)
			{
				SetPixelPosX(MinX);
			}
			else
			{
				SetPixelPosX(newX);
			}
			break;
		}
		case E_Right:
		{
			float newX = m_pixelPos.GetX() + m_WalkSpeed * deltaTime;
			float MaxX = m_CollsionPixelPos.GetX() + Util::MAPPIECEPIX - 4;
			if (drift && newX >= MaxX)
			{
				SetPixelPosX(MaxX);
			}
			else
			{
				SetPixelPosX(newX);
			}
			break;
		}
		}
		UpdateMapPos();
		UpdateRectCollision(4, -2);
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
	}
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

Point const& Role::GetCollsionPixelPos() const
{
	return m_CollsionPixelPos;
}

void Role::SetCollsionPixelPos(Point val)
{
	m_CollsionPixelPos = val;
}


#include "Bubble.h"
#include "BubbleState.h"
#include "PlayScene.h"
#include "DUOEngine.h"


Bubble::Bubble(int mapPosX, int mapPosY, 
	E_StateType bubbleType /*= E_Wait*/ , E_Direction direction /*= E_None*/,int power /*= 0*/, Role* role /*= NULL*/) 
	:GameObject(mapPosX,mapPosY),m_stateType(bubbleType),m_power(power),m_direction(direction),m_role(role)
{
	std::wstring bubbleName = Util::CreateMapName(mapPosX,mapPosY,L"Bubble");

	m_objName = bubbleName;

	m_Layout = LayoutType::E_Bubbles;

	m_pixelPos = CalPixelPos(mapPosX,mapPosY);


	UpdateRectCollision();
	m_pStateMachine = new StateMachine<Bubble>(this);
	if (bubbleType == E_Wait)
	{
		m_currentSprite = Sprite(L"Resource\\Popo.png",1,3,0,1,6.0f);
		m_pStateMachine->SetCurrentState(BubbleWait::Instance());
		m_ObjectType = ObjectType::E_Bubble;
	}
	else
	{
		std::wstring bubbleName = Util::CreateMapName(mapPosX,mapPosY,L"Bubble");
		m_currentSprite = Sprite(L"Resource\\Explosion.png",5,14,0,0,20.0f);
		m_pStateMachine->SetCurrentState(BubbleExplosion::Instance());
		m_ObjectType = ObjectType::E_ObjCommon;
	}

	switch(direction)
	{
	case E_Up:
		{
			m_currentSprite.SetCurrentRow(0);
			break;
		}
	case E_Down:
		{
			m_currentSprite.SetCurrentRow(1);
			break;
		}
	case E_Left:
		{
			m_currentSprite.SetCurrentRow(2);
			break;
		}
	case E_Right:
		{
			m_currentSprite.SetCurrentRow(3);
			break;
		}
	case E_None:
		{
			m_currentSprite.SetCurrentRow(4);
		}
	}

	if(m_stateType == E_Middle)
	{
		m_currentSprite.SetCurrentCol(4);
	}

	UpdateMapPos();
	UpdateRectCollision();
	
}


Bubble::~Bubble()
{
	SAFE_DELETE(m_pStateMachine);

	PlayScene* currentScene = dynamic_cast<PlayScene*>(g_pLGCenter->GetCurrentScene());

	if (m_stateType == E_Wait && !g_pLGCenter->GetCurrentScene()->GetGameEnd())
	{
		currentScene->Explosion(MapPosX(),MapPosY(),m_power);
		currentScene->ChangeMap(MapPosX(),MapPosY(),MapType::E_None);
		m_role->GetAbility()->Crease(Ability::E_BubbleNum);
	}
}

bool Bubble::UpdateAnimateFrame(float deltaTime, const int* frame /*= NULL*/, int frameCount /*= 0*/)
{
	PlayScene* currentScene = dynamic_cast<PlayScene*>(g_pLGCenter->GetCurrentScene());

	switch(m_stateType)
	{
	case E_Wait:
		{
			Object::UpdateAnimateFrame(deltaTime);
			break;
		}
	case E_Center:
		{
			const int frame[] = {0,1,2,3,0,1,2,3,0,4,4,4};
			if(Object::UpdateAnimateFrame(deltaTime,frame,ARRAYSIZE(frame)))
			{
				currentScene->ChangeMap(MapPosX(),MapPosY(),MapType::E_None);
				currentScene->DeleteObject(this->GetObjID());
				
				return true;
			}
			break;
		}
	case E_Middle:
		{
			const int frame[] = {3,4,3,4,3,4,8,9,10,11,12,13};
			if(Object::UpdateAnimateFrame(deltaTime,frame,ARRAYSIZE(frame)))
			{
				currentScene->DeleteObject(this->GetObjID());
				return true;
			}
			break;
		}
	case E_Tail:
		{
			const int frame[] = {0,1,2,5,6,7,8,9,10,11,12,13};
			if(Object::UpdateAnimateFrame(deltaTime,frame,ARRAYSIZE(frame)))
			{
				currentScene->DeleteObject(this->GetObjID());
				return true;
			}
			break;
		}
	}
	return false;
}

void Bubble::Update(float deltaTime)
{
	m_pStateMachine->Update(deltaTime);
}

Bubble::E_StateType const& Bubble::GetBubbleType() const
{
	return m_stateType;
}

void Bubble::SetBubbleType(E_StateType val)
{
	m_stateType = val;
}

StateMachine<Bubble>* const& Bubble::GetStateMachine() const
{
	return m_pStateMachine;
}

Bubble::E_Direction const& Bubble::GetDirection() const
{
	return m_direction;
}

void Bubble::SetDirection(E_Direction val)
{
	m_direction = val;
}

bool Bubble::HandleMessage(const Telegram& telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}

int const& Bubble::GetPower() const
{
	return m_power;
}

void Bubble::SetPower(int val)
{
	m_power = val;
}

Role* const& Bubble::GetRole() const
{
	return m_role;
}

void Bubble::SetRole(Role* val)
{
	m_role = val;
}


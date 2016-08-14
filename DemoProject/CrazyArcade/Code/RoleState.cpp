#include "RoleState.h"
#include "LGInput.h"

//------------------------------------------------------------------------RoleState类方法实现

bool RoleState::OnMessage(Role* agent, const Telegram& msg)
{
	return false;
}

std::wstring const& RoleState::GetRoleStateName() const
{
	return m_RoleStateName;
}

void RoleState::PreprocessState(Role* role, RoleState* roleState)
{
	roleState->Enter(role);
	role->GetStateMachine()->SetPreviousState(roleState);
}

//------------------------------------------------------------------------Idle类方法实现

void Idle::Execute(Role* role, float deltatime )
{

}

void Idle::Exit(Role* role)
{

}


//------------------------------------------------------------------------IdleUp类方法实现

void IdleUp::Enter(Role* role)
{
	role->HavaCurrentSprite().SetRowAndCol(0,0);
	role->SetDirection(Role::E_Up);
	m_RoleStateName = L"IdleUp";
}

//------------------------------------------------------------------------IdleDown类方法实现


void IdleDown::Enter(Role* role)
{
	role->HavaCurrentSprite().SetRowAndCol(1,0);
	role->SetDirection(Role::E_Down);
	m_RoleStateName = L"IdleDown";
}

//------------------------------------------------------------------------IdleLeft类方法实现



void IdleLeft::Enter(Role* role)
{
	role->HavaCurrentSprite().SetRowAndCol(2,0);
	role->SetDirection(Role::E_Left);
	m_RoleStateName = L"IdleLeft";
}

//------------------------------------------------------------------------IdleRight类方法实现


void IdleRight::Enter(Role* role)
{
	role->HavaCurrentSprite().SetRowAndCol(3,0);
	role->SetDirection(Role::E_Right);
	m_RoleStateName = L"IdleRight";
}

//------------------------------------------------------------------------Walk类方法实现

void Walk::Execute(Role* role, float deltatime )
{
	role->UpdateAnimateFrame(deltatime);
	role->Move(deltatime);
}

void Walk::Exit(Role* role)
{

}

//------------------------------------------------------------------------WalkUp类方法实现


void WalkUp::Enter(Role* role)
{
	PreprocessState(role,IdleUp::Instance());
	m_RoleStateName = L"WalkUp";
}



//------------------------------------------------------------------------WalkDown类方法实现


void WalkDown::Enter(Role* role)
{
	PreprocessState(role,IdleDown::Instance());
	m_RoleStateName = L"WalkDown";
}



//------------------------------------------------------------------------WalkLeft类方法实现


void WalkLeft::Enter(Role* role )
{
	PreprocessState(role,IdleLeft::Instance());
	m_RoleStateName = L"WalkLeft";
}



//------------------------------------------------------------------------WalkRight类方法实现


void WalkRight::Enter(Role* role )
{
	PreprocessState(role,IdleRight::Instance());
	m_RoleStateName = L"WalkRight";
}



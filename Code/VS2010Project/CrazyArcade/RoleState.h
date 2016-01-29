#pragma once

#include "LGHead.h"
#include "State.h"
#include "Role.h"

class RoleState : public State<Role>
{
public:
	bool OnMessage(Role* agent, const Telegram& msg);
	std::wstring const& GetRoleStateName() const;
protected:
	std::wstring m_RoleStateName;
	void PreprocessState(Role* role, RoleState* roleState);
};


class Idle : public RoleState
{
public:
	virtual void Enter(Role* role) = 0;
	virtual void Execute(Role* role,float deltatime = 0.0f);
	virtual void Exit(Role* role);

};


class IdleUp : public Idle
{
	SINGLETON(IdleUp);
public:
	void Enter(Role* role);
};


class IdleDown : public Idle
{
	SINGLETON(IdleDown);
public:
	void Enter(Role* role);
};


class IdleLeft : public Idle
{
	SINGLETON(IdleLeft);
public:
	void Enter(Role* role);
};


class IdleRight : public Idle
{
	SINGLETON(IdleRight);
public:
	void Enter(Role* role);
};


class Walk : public RoleState
{
public:
	virtual void Enter(Role* role) = 0;
	virtual void Execute(Role* role, float deltatime = 0.0f);
	virtual void Exit(Role* role);
};


class WalkUp : public Walk
{
	SINGLETON(WalkUp);
public:
	virtual void Enter(Role* role);
};


class WalkDown : public Walk
{
	SINGLETON(WalkDown);
public:
	virtual void Enter(Role* role);
};


class WalkLeft : public Walk
{
	SINGLETON(WalkLeft);
public:
	virtual void Enter(Role* role);
};


class WalkRight : public Walk
{
	SINGLETON(WalkRight);
public:
	virtual void Enter(Role* role);
};



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
	SINGLETON_CTOR(IdleUp);
public:
	void Enter(Role* role);
};


class IdleDown : public Idle
{
	SINGLETON_CTOR(IdleDown);
public:
	void Enter(Role* role);
};


class IdleLeft : public Idle
{
	SINGLETON_CTOR(IdleLeft);
public:
	void Enter(Role* role);
};


class IdleRight : public Idle
{
	SINGLETON_CTOR(IdleRight);
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
	SINGLETON_CTOR(WalkUp);
public:
	virtual void Enter(Role* role);
};


class WalkDown : public Walk
{
	SINGLETON_CTOR(WalkDown);
public:
	virtual void Enter(Role* role);
};


class WalkLeft : public Walk
{
	SINGLETON_CTOR(WalkLeft);
public:
	virtual void Enter(Role* role);
};


class WalkRight : public Walk
{
	SINGLETON_CTOR(WalkRight);
public:
	virtual void Enter(Role* role);
};



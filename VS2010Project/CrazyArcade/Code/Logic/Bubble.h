#pragma once

#include "LGHead.h"
#include "GameObject.h"
#include "StateMachine.h"

class Role;

class Bubble : public GameObject
{
public:
	static const float FRAMESPEED;
	enum E_StateType {E_Wait, E_Center, E_Middle, E_Tail};
	enum E_MessageType {E_Explode};
	enum E_Direction {E_Up, E_Down, E_Left, E_Right, E_None};
	Bubble(int mapPosX, int mapPosY, E_StateType bubbleType = E_Wait,
		E_Direction direction = E_None,int power = 0, Role* role = NULL);
	~Bubble();
	void Update(float deltaTime);
	bool UpdateAnimateFrame(float deltaTime, const int* frame = NULL, int frameCount = 0);
	bool HandleMessage(const Telegram& telegram);

	Bubble::E_StateType const& GetBubbleType() const;
	void SetBubbleType(Bubble::E_StateType val);
	StateMachine<Bubble>* const& GetStateMachine() const;
	Bubble::E_Direction const& GetDirection() const;
	void SetDirection(Bubble::E_Direction val);

	int const& GetPower() const;
	void SetPower(int val);

	int const& GetMapPosX() const;
	void SetMapPosX(int val);

	int const& GetMapPosY() const;
	void SetMapPosY(int val);

	Role* const& GetRole() const;
	void SetRole(Role* val);
private:
	E_StateType m_stateType;
	E_Direction m_direction;
	StateMachine<Bubble>* m_pStateMachine;
	int m_power;
	Role* m_role;
};
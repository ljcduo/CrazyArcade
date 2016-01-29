#pragma once

#include "Object.h"
#include "StateMachine.h"
#include "Ability.h"

class Prop;

class Role : public Object
{
public:
	enum E_RoleDirection {E_Up, E_Down, E_Left, E_Right};
	enum E_RoleSpriteType {E_RedBaby};
	Role(std::wstring objName, int mapPosX, int mapPosY, E_RoleSpriteType spriteType);
	~Role();
	void Update(float deltaTime);
	void Move(float deltaTime);
	bool HandleMessage(const Telegram& telegram);
	void EatProp(Prop* prop);
	//！！！！！！！！！！！！！！！！！！！！！！！！GetAndSet
	bool const& GetCanMove() const;
	void SetCanMove(bool val);

	int const& GetMapPosX() const;
	void SetMapPosX(int val);

	int const& GetMapPosY() const;
	void SetMapPosY(int val);

	float const& GetWalkSpeed() const;
	void SetWalkSpeed(float val);

	StateMachine<Role>* const& GetStateMachine() const;

	Role::E_RoleDirection const& GetDirection() const;
	void SetDirection(Role::E_RoleDirection val);

	Ability* const& GetAbility() const;
	void SetAbility(Ability* val);

	Point const& Role::GetStandOnBubble() const;
	void SetStandOnBubble(bool val);
	bool IsStandOnBubble();

	Point const& GetCollsionPixelPos() const;
	void SetCollsionPixelPos(Point val);
private:
	float m_WalkSpeed;
	StateMachine<Role>*  m_pStateMachine;
	E_RoleDirection m_direction;
	bool m_CanMove;		//泌惚囑欺嬾悪麗祥音嬬卞強
	Ability* m_pAbility;
	Point m_standOnBubble;
	Point m_CollsionPixelPos;
};
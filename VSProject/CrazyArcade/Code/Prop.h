#pragma once

#include "GameObject.h"

class Prop : public GameObject
{
public:
	enum E_PropType{E_Popo,E_Power,E_Run1};
	Prop(int mapPosX, int mapPosY, std::wstring picPath, E_PropType propType);
	Prop();
	~Prop();
	Prop::E_PropType const& GetPropType() const;
	void SetPropType(Prop::E_PropType val);
private:
	E_PropType m_PropType;
};

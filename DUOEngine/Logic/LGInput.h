#pragma once

#include "LGHead.h"

class LGInput
{
public:
	enum E_KeyName {E_KeyUp, E_KeyDown, E_KeyLeft, E_KeyRight, E_KeySpace, E_KeyNum};
private:
	LGInput();
	~LGInput();
	LGInput(const LGInput& rhs);
	LGInput& operator=(const LGInput& rhs);
public:
	static LGInput* Instance();
	void SetCurrentKey(int name, bool status);
	void SetPrevKey(int name, bool status);
	bool const GetCurrentKey(E_KeyName name);
	bool const GetPrevKey(E_KeyName name);
private:
	std::vector<bool> m_CurrentKey;
	std::vector<bool> m_PrevKey;
};

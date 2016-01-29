#pragma once

#include "LGHead.h"

class LGInput
{
private:
	LGInput();
	~LGInput();
	LGInput(const LGInput& rhs);
	LGInput& operator=(const LGInput& rhs);
public:
	enum E_KeyName {E_KeyUp, E_KeyDown, E_KeyLeft, E_KeyRight,E_KeySpace,E_KeyNum};
	static LGInput* Instance();
	void SetCurrentKey(E_KeyName name, bool status);
	void SetPrevKey(E_KeyName name, bool status);
	bool const& GetCurrentKey(E_KeyName name) const;
	bool const& GetPrevKey(E_KeyName name) const;
private:
	bool m_CurrentKey[E_KeyNum];
	bool m_PrevKey[E_KeyNum];
};

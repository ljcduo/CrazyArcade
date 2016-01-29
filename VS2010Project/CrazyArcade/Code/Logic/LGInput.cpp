#include "LGInput.h"




LGInput* LGInput::Instance()
{
	static LGInput instance;
	return &instance;
}

LGInput::LGInput()
{

}

LGInput::~LGInput()
{

}

void LGInput::SetCurrentKey(E_KeyName name, bool status)
{
	m_CurrentKey[name] = status;
}

void LGInput::SetPrevKey(E_KeyName name, bool status)
{
	m_PrevKey[name] = status;
}

bool const& LGInput::GetCurrentKey(E_KeyName name) const
{
	return m_CurrentKey[name];
}

bool const& LGInput::GetPrevKey(E_KeyName name) const
{
	return m_PrevKey[name];
}

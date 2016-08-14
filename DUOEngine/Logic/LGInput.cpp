#include "LGInput.h"
using namespace std;
LGInput* LGInput::Instance()
{
	static LGInput instance;
	return &instance;
}

LGInput::LGInput()
{
	m_CurrentKey.resize(E_KeyNum);
	m_PrevKey.resize(E_KeyNum);
}

LGInput::~LGInput()
{

}

void LGInput::SetCurrentKey(int name, bool status)
{
	m_CurrentKey[name] = status;
}

void LGInput::SetPrevKey(int name, bool status)
{
	m_PrevKey[name] = status;
}

bool const LGInput::GetCurrentKey(E_KeyName name)
{
	return m_CurrentKey[name];
}

bool const LGInput::GetPrevKey(E_KeyName name)
{
	return m_PrevKey[name];
}

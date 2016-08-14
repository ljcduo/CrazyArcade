#pragma once

#include "LGHead.h"
#include "StateMachine.h"
#include "Scene.h"
#include "MessageDispatcher.h"
#include <string>

using std::string;

class LGCenter
{
public:
	LGCenter();
	~LGCenter();
	static LGCenter* Instance();
	StateMachine<LGCenter>* const& GetStateMachine() const;
	void SetStateMachine(StateMachine<LGCenter>* val);
	Scene* GetCurrentScene();
	void SetCurrentScene(Scene* currentScene);
	void Update();
	float GetFPS(); //¸üÐÂFPS
	string WindowsTitle() const { return m_WindowsTitle; }
	void WindowsTitle(string val) { m_WindowsTitle = val; }
private:
	StateMachine<LGCenter>*  m_pStateMachine;
	float m_Deltatime;
	string m_WindowsTitle;
};

#define g_pLGCenter LGCenter::Instance()
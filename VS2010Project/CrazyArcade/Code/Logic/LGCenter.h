#pragma once

#include "LGHead.h"
#include "StateMachine.h"
#include "Scene.h"
#include "MessageDispatcher.h"

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
	float GetFPS();
private:
	StateMachine<LGCenter>*  m_pStateMachine;
	float m_deltatime;
};

#define g_pLGCenter LGCenter::Instance()
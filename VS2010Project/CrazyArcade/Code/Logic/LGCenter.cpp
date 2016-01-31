#include "LGCenter.h"
#include "PlayScene.h"

LGCenter::LGCenter() : m_deltatime(0)
{
	// 设置随机数种子
	srand(GetTickCount());
	// 设置状态机
	SetStateMachine(new StateMachine<LGCenter>(this));
}

LGCenter::~LGCenter()
{
	SAFE_DELETE(m_pStateMachine);
}

LGCenter* LGCenter::Instance()
{
	static LGCenter* instance = new LGCenter;
	return instance;
}

Scene* LGCenter::GetCurrentScene()
{
	return static_cast<Scene*>(GetStateMachine()->GetCurrentState());
}

void LGCenter::SetCurrentScene(Scene* currentScene)
{
	m_pStateMachine->SetCurrentState(currentScene);
}

void LGCenter::Update()
{
	// 更新FPS
	GetFPS();
	// 更新状态机里面的场景
	m_pStateMachine->Update(m_deltatime);
	// 处理电报消息
	MessageMachine->Update();
}

StateMachine<LGCenter>* const& LGCenter::GetStateMachine() const
{
	return m_pStateMachine;
}

void LGCenter::SetStateMachine(StateMachine<LGCenter>* val)
{
	m_pStateMachine = val;
}

float LGCenter::GetFPS()
{
	//定义四个静态变量
	static float  fps = 0; //我们需要计算的FPS值
	static int    frameCount = 0;//帧数
	static float  currentTime =0.0f;//当前时间

	frameCount++;//每调用一次GetFPS()函数，帧数自增1
	currentTime = timeGetTime()*0.001f;//获取系统时间，其中timeGetTime函数返回的是以毫秒为单位的系统时间，所以需要乘以0.001，得到单位为秒的时间

	static float  lastTime = currentTime;//持续时间

	//如果当前时间减去持续时间大于了1秒钟，就进行一次FPS的计算和持续时间的更新，并将帧数值清零
	if(currentTime - lastTime > 1.0f) //将时间控制在1秒钟
	{
		fps = (float)frameCount /(currentTime - lastTime);//计算这1秒钟的FPS值

		m_deltatime = 1 / fps;
		lastTime = currentTime; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间

		frameCount    = 0;//将本次帧数frameCount值清零
	}

	return fps;
}

#include "BubbleState.h"
#include "LGCenter.h"
#include "PlayScene.h"

//------------------------------------------------------------------------BubbleState类方法实现

void BubbleState::Execute(Bubble* bubble,float deltatime /* = 0.0f */)
{
	if(bubble->UpdateAnimateFrame(deltatime))
		return;
}

void BubbleState::Exit(Bubble * bubble)
{

}

bool BubbleState::OnMessage(Bubble* agent, const Telegram& msg)
{
	return false;
}

//------------------------------------------------------------------------BubbleWait类方法实现

void BubbleWait::Enter(Bubble* bubble)
{
	bubble->SetBubbleType(Bubble::E_Wait);
}


bool BubbleWait::OnMessage(Bubble* agent, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Bubble::E_Explode:
		{
			g_pLGCenter->GetCurrentScene()->DeleteObject(agent->GetObjID());
			return true;
		}
	default:
		return false;
	}
}

//------------------------------------------------------------------------BubbleCenter类方法实现


void BubbleExplosion::Enter(Bubble* bubble)
{

}

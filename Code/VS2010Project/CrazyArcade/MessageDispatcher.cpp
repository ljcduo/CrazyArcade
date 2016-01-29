#include "MessageDispatcher.h"
#include "CrudeTimer.h"
#include "Object.h"
#include "LGCenter.h"


#include <iostream>

using std::set;



//------------------------------ Instance -------------------------------------

MessageDispatcher* MessageDispatcher::Instance()
{
  static MessageDispatcher instance;

  return &instance;
}


//----------------------------- Dispatch ---------------------------------
//  
//  see description in header
//------------------------------------------------------------------------
void MessageDispatcher::Discharge(Object* pReceiver,
                                  const Telegram& telegram)
{
  if (!pReceiver->HandleMessage(telegram))
  {
    //telegram could not be handled
    OutputDebugStringW(L"Message not handled");
  }
}

//---------------------------- DispatchMessage ---------------------------
//
//  given a message, a receiver, a sender and any time delay , this function
//  routes the message to the correct agent (if no delay) or stores
//  in the message queue to be dispatched at the correct time
//------------------------------------------------------------------------
void MessageDispatcher::DispatchMessage(double  delay,
                                        int    sender,
                                        int    receiver,
                                        int    msg,
                                        void*  ExtraInfo)
{

  //get pointers to the sender and receiver
  Object* pSender   = LGCenter::Instance()->GetCurrentScene()->HavaObject(sender);
  Object* pReceiver = LGCenter::Instance()->GetCurrentScene()->HavaObject(receiver);

  //make sure the receiver is valid
  if (pReceiver == NULL)
  {
	assert(false);
    return;
  }
  
  //create the telegram
  Telegram telegram(0, sender, receiver, msg, ExtraInfo);
  
  //if there is no delay, route telegram immediately                       
  if (delay <= 0.0f)                                                        
  {
    //send the telegram to the recipient
    Discharge(pReceiver, telegram);
  }

  //else calculate the time when the telegram should be dispatched
  else
  {
    double CurrentTime = Clock->GetCurrentTime(); 

    telegram.DispatchTime = CurrentTime + delay;

    //and put it in the queue
    PriorityQ.insert(telegram);   
            
  }
}


//---------------------- DispatchDelayedMessages -------------------------
//
//  This function dispatches any telegrams with a timestamp that has
//  expired. Any dispatched telegrams are removed from the queue
//------------------------------------------------------------------------
void MessageDispatcher::DispatchDelayedMessages()
{
  //get current time
  double CurrentTime = Clock->GetCurrentTime();

  //now peek at the queue to see if any telegrams need dispatching.
  //remove all telegrams from the front of the queue that have gone
  //past their sell by date
  while( !PriorityQ.empty() &&
         (PriorityQ.begin()->DispatchTime < CurrentTime) && 
         (PriorityQ.begin()->DispatchTime > 0) )
  {
    //read the telegram from the front of the queue
    const Telegram& telegram = *PriorityQ.begin();

    //find the recipient
    Object* pReceiver = LGCenter::Instance()->GetCurrentScene()->HavaObject(telegram.Receiver);
	
	if (pReceiver != NULL)
	{
		//send the telegram to the recipient
		Discharge(pReceiver, telegram);
	}

    //remove it from the queue
    PriorityQ.erase(PriorityQ.begin());
  }
}




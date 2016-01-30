#include "PlayScene.h"
#include "Sprite.h"
#include "RoleState.h"
#include "LGInput.h"
#include <vector>
#include <algorithm>
#include "Bubble.h"
#include "MessageDispatcher.h"
#include "Prop.h"

using namespace std;

PlayScene::PlayScene() 
{

}

PlayScene::~PlayScene()
{
	SetGameEnd(true);
}



void PlayScene::Enter(LGCenter*)
{
	g_pCurrentScene = this;

	//生成地图
	CreateMapBlock();

	//载入框架背景图
	Object* pBackGround = new Object(L"BackGround",Sprite(L"Resource\\BG.png"), LayoutType::E_GUIs, Point(0.0f,0.0f));
	InsertObject(pBackGround);


	//载入道路
	Object* pRoad = new Object(L"Road",Sprite(L"Resource\\road.png"),LayoutType::E_Roads,Object::ORIGINPIX);
	InsertObject(pRoad);

	//载入方块
	for (int x = 0; x != XLENGTH; x++)
	{
		for (int y = 0; y != YLENGTH; y++)
		{
			if (m_MapBlock[x][y] != MapType::E_None)
			{
				Block* pBlock = new Block(x,y,m_MapBlock[x][y]);
				InsertObject(pBlock);
			}
		}
	}



	//载入角色
	m_pPlayer = new Role(L"Player",4,5,Role::E_RedBaby);

	InsertObject(m_pPlayer);
}

void PlayScene::Execute(LGCenter* lgCenter, float deltaTime)
{
	KeyboardControl();
	CollisionDetection(m_pPlayer, deltaTime);

	vector<Object*> tempVec = HaveAllObject();

	for (vector<Object*>::const_iterator itr = tempVec.begin(); itr != tempVec.end();)
	{
		(*itr)->Update(deltaTime);
		++itr;
	}

	/*DirtyRectInfect();*/
}

void PlayScene::Exit(LGCenter*)
{
	
}


void PlayScene::CreateMapBlock()
{
	memset(&m_MapBlock,0,sizeof(m_MapBlock));

	int copyMap[XLENGTH][YLENGTH] = 
	{
		0,0,0,5,4,5,5,5,4,5,0,0,0,
		2,0,2,4,6,0,6,0,6,4,1,0,1,
		4,5,4,5,4,9,4,9,4,5,4,5,4,
		2,4,2,4,6,0,6,0,6,4,1,4,1,
		4,5,4,6,9,0,0,0,9,6,4,5,4,
		6,4,6,9,9,6,5,6,9,9,6,4,6,
		0,0,9,9,6,4,7,4,6,9,9,0,0,
		6,0,6,4,5,4,8,0,0,4,6,0,6,
		0,0,9,9,6,4,10,4,6,9,9,0,0,
		6,4,6,9,9,6,5,6,9,9,6,4,6,
		4,5,4,6,9,0,0,0,9,6,4,5,4,
		3,4,3,4,6,0,6,0,6,4,2,4,2,
		4,5,4,5,4,9,4,9,4,5,4,5,4,
		3,0,3,4,6,0,6,0,6,4,2,0,2,
		0,0,0,5,4,5,5,5,4,5,0,0,0
	};


	for (int x = 0; x != XLENGTH; x++)
	{
		for (int y = 0; y != YLENGTH; y++)
		{
			MapType::E_MapType mapType;
			switch(copyMap[x][y])
			{
			case 0:
				{
					mapType = MapType::E_None;
					break;
				}
			case 1:
				{
					mapType = MapType::E_RedHouse;
					break;
				}
			case 2:
				{
					mapType = MapType::E_BlueHouse;
					break;
				}
			case 3:
				{
					mapType = MapType::E_YellowHouse;
					break;
				}
			case 4:
				{
					mapType = MapType::E_TownBlockRed;
					break;
				}
			case 5:
				{
					mapType = MapType::E_TownBlockYellow;
					break;
				}
			case 6:
				{
					mapType = MapType::E_Tree;
					break;
				}
			case 7:
				{
					mapType = MapType::E_TownWindmill;
					break;
				}
			case 8:
				{
					mapType = MapType::E_TownWindmillAni;
					break;
				}
			case 9:
				{
					mapType = MapType::E_TownBox;
					break;
				}
			case 10:
				{
					mapType = MapType::E_Solid;
					break;
				}
			default:
				{
					mapType = MapType::E_None;
					break;
				}
			}
			m_MapBlock[x][y] = mapType;
		}
	}


}




void PlayScene::KeyboardControl()
{
	//————————————————————————————————————处理方向键
	StateMachine<Role>* const& roleStateMachine = m_pPlayer->GetStateMachine();

	static std::vector<Role::E_RoleDirection> DirectionSeque;

	bool
	keyUp = LGInput::Instance()->GetCurrentKey(LGInput::E_KeyUp),
	keyDown = LGInput::Instance()->GetCurrentKey(LGInput::E_KeyDown),
	keyLeft = LGInput::Instance()->GetCurrentKey(LGInput::E_KeyLeft),
	keyRight = LGInput::Instance()->GetCurrentKey(LGInput::E_KeyRight);

	bool
	PrevkeyUp = LGInput::Instance()->GetPrevKey(LGInput::E_KeyUp),
	PrevkeyDown = LGInput::Instance()->GetPrevKey(LGInput::E_KeyDown),
	PrevkeyLeft = LGInput::Instance()->GetPrevKey(LGInput::E_KeyLeft),
	PrevkeyRight = LGInput::Instance()->GetPrevKey(LGInput::E_KeyRight);

	bool KeyChange = false;

	//处理按下
	if (keyUp && !PrevkeyUp)
	{
		DirectionSeque.push_back(Role::E_Up);
		KeyChange = true;
	}
	if (keyDown && !PrevkeyDown)
	{
		DirectionSeque.push_back(Role::E_Down);
		KeyChange = true;
	}
	if (keyLeft && !PrevkeyLeft)
	{
		DirectionSeque.push_back(Role::E_Left);
		KeyChange = true;
	}
	if (keyRight && !PrevkeyRight)
	{
		DirectionSeque.push_back(Role::E_Right);
		KeyChange = true;
	}

	//处理弹起
	if (!keyUp && PrevkeyUp)
	{
		DirectionSeque.erase(std::find(DirectionSeque.begin(),DirectionSeque.end(),Role::E_Up));
		KeyChange = true;
	}
	if (!keyDown && PrevkeyDown)
	{
		DirectionSeque.erase(std::find(DirectionSeque.begin(),DirectionSeque.end(),Role::E_Down));
		KeyChange = true;
	}
	if (!keyLeft && PrevkeyLeft)
	{
		DirectionSeque.erase(std::find(DirectionSeque.begin(),DirectionSeque.end(),Role::E_Left));
		KeyChange = true;
	}
	if (!keyRight && PrevkeyRight)
	{
		DirectionSeque.erase(std::find(DirectionSeque.begin(),DirectionSeque.end(),Role::E_Right));
		KeyChange = true;
	}



	//处理将最后放进容器的按键

	int Size = DirectionSeque.size();

	if (KeyChange)
	{
		if (Size != 0)
		{
			switch(DirectionSeque[Size-1])
			{
			case Role::E_Up:
				{
					roleStateMachine->ChangeState(WalkUp::Instance());
					break;
				}
			case Role::E_Down:
				{
					roleStateMachine->ChangeState(WalkDown::Instance());
					break;
				}
			case Role::E_Left:
				{
					roleStateMachine->ChangeState(WalkLeft::Instance());
					break;
				}
			case Role::E_Right:
				{
					roleStateMachine->ChangeState(WalkRight::Instance());
					break;
				}
			}
			m_pPlayer->SetCanMove(true);
		}
		else
		{
			if (KeyChange)
			{
				roleStateMachine->RevertToPreviousState();
				KeyChange = false;
				m_pPlayer->SetDirtySource();
			}
		}
		
	}


	//—————————————————————————————————————处理空格键
	if (LGInput::Instance()->GetCurrentKey(LGInput::E_KeySpace) && 
		!LGInput::Instance()->GetPrevKey(LGInput::E_KeySpace) &&
		m_pPlayer->IsStandOnBubble())
	{
		LGInput* test = LGInput::Instance();
		int rolePosX = m_pPlayer->GetMapPosX();
		int rolePosY = m_pPlayer->GetMapPosY();
		wstring bubbleName = Util::CreateMapName(m_pPlayer->GetMapPosX(),
			m_pPlayer->GetMapPosY(),L"Bubble");
		if(m_pPlayer->GetAbility()->GetBubbleNum() >= 1)
		{
			Bubble* bubble = new Bubble(rolePosX,rolePosY,Bubble::E_Wait,Bubble::E_None,
				m_pPlayer->GetAbility()->GetPower(),m_pPlayer);
			InsertObject(bubble);
			ChangeMap(rolePosX,rolePosY,MapType::E_Bubble);
			m_pPlayer->SetStandOnBubble(true);
			Dispatch->DispatchMessage(5.0f,m_pPlayer->GetObjID(),bubble->GetObjID(),Bubble::E_Explode,NULL);
			m_pPlayer->GetAbility()->Decrease(Ability::E_BubbleNum);
			//bubble->FreshRectDirty();
			//DirtyRectInfect();
		}
	}

}

void PlayScene::CollisionDetection(Role* role, float deltaTime)
{
	LGRect RoleMoveRect = role->GetRectCollision();
	

	wstring roleState = static_cast<RoleState*>(role->GetStateMachine()->GetCurrentState())->GetRoleStateName();

	if (roleState == L"WalkUp")
	{
		role->SetDirection(Role::E_Up);
		RoleMoveRect.SetY(RoleMoveRect.GetY() + role->GetWalkSpeed() * deltaTime);
	}
	else if(roleState == L"WalkDown")
	{
		role->SetDirection(Role::E_Down);
		RoleMoveRect.SetY(RoleMoveRect.GetY() - role->GetWalkSpeed() * deltaTime);
	}
	else if(roleState == L"WalkLeft")
	{
		role->SetDirection(Role::E_Left);
		RoleMoveRect.SetX(RoleMoveRect.GetX() - role->GetWalkSpeed() * deltaTime);
	}
	else if(roleState == L"WalkRight")
	{
		role->SetDirection(Role::E_Right);
		RoleMoveRect.SetX(RoleMoveRect.GetX() + role->GetWalkSpeed() * deltaTime);
	}



	bool collision = false;
	wstring standOnBubble = Util::CreateMapName(
		m_pPlayer->GetStandOnBubble().GetXInt(),
		m_pPlayer->GetStandOnBubble().GetYInt(),L"Bubble");


	//检测是否撞墙
	LGRect wall = LGRect(Object::ORIGINPIX.GetX(),Object::ORIGINPIX.GetY(),
		static_cast<float>(XLENGTH*Object::MAPPIECEPIX),
		static_cast<float>(YLENGTH*Object::MAPPIECEPIX) );

	if( !Util::CollisionInsideRect(role->GetRectCollision(),wall) )
	{
		//如果卡在墙里，修正位置
		if (role->GetRectCollision().GetX() < wall.GetX() )
		{
			role->SetPixelPosX(wall.GetX() - 4);
		}

		if (role->GetRectCollision().GetX() > wall.GetX() + wall.GetWidth() - Object::MAPPIECEPIX)
		{
			role->SetPixelPosX(wall.GetX() + wall.GetWidth() - Object::MAPPIECEPIX - 4);
		}

		if (role->GetRectCollision().GetY() > wall.GetY() + wall.GetHeight() - Object::MAPPIECEPIX )
		{
			role->SetPixelPosY(wall.GetY() + wall.GetHeight() - Object::MAPPIECEPIX + 2);
		}

		if (role->GetRectCollision().GetY() < wall.GetY() )
		{
			role->SetPixelPosY(wall.GetY() + 2);
		}
		return;
	}

	if( !Util::CollisionInsideRect(RoleMoveRect,wall) )
	{
		role->SetCanMove(false);
		m_pPlayer->SetCollsionPixelPos(Point());
		return;
	}

	for (vector<Object*>::iterator itr = HaveAllObject().begin(); itr != HaveAllObject().end(); itr++)
	{
		
		

		//检测是否撞方块
		if ( ((*itr)->GetObjectType() == ObjectType::E_ObjBlock || 
			(*itr)->GetObjectType() == ObjectType::E_Bubble || 
			(*itr)->GetObjectType() == ObjectType::E_Build )
			&& Util::isCollsionWithRect(RoleMoveRect,(*itr)->GetRectCollision())
			) 
		{

			
			//发生碰撞
			collision = true;

			if((*itr)->GetObjectType() == ObjectType::E_Build)
			{
				role->SetCanMove(false);
				break;
			}

			//踩在自己放的泡泡上，修正离开偏移
			if (standOnBubble == (*itr)->GetObjName())
			{


				float xOffset = static_cast<float>(role->GetRectCollision().GetX() - (*itr)->GetPixelPosX());
				float yOffset = static_cast<float>(role->GetRectCollision().GetY() - (*itr)->GetPixelPosY());
				const int OFFSET = 35;
				switch(role->GetDirection())
				{
				case Role::E_Up:
					{
						if (yOffset > OFFSET)
						{
							role->SetPixelPosY(static_cast<float>((*itr)->GetPixelPosY() + 2 + Object::MAPPIECEPIX));
							role->SetStandOnBubble(false);

						}
						return;
					}
				case Role::E_Down:
					{
						if (yOffset < -OFFSET)
						{
							role->SetPixelPosY(static_cast<float>((*itr)->GetPixelPosY() + 2 - Object::MAPPIECEPIX));
							role->SetStandOnBubble(false);

						}
						return;
					}
				case Role::E_Left:
					{
						if (xOffset < -OFFSET)
						{
							role->SetPixelPosX(static_cast<float>((*itr)->GetPixelPosX() - 4 - Object::MAPPIECEPIX));
							role->SetStandOnBubble(false);

						}
						return;
					}
				case Role::E_Right:
					{
						if (xOffset > OFFSET)
						{
							role->SetPixelPosX(static_cast<float>((*itr)->GetPixelPosX() - 4 + Object::MAPPIECEPIX));
							role->SetStandOnBubble(false);

						}
						return;
					}
				}
			}
			else //没有踩在自己放的泡泡上
			{
				//检查是否能够平移转弯

				m_pPlayer->SetCollsionPixelPos(Point((*itr)->GetPixelPosX(),(*itr)->GetPixelPosY()));

				float xOffset = static_cast<float>(role->GetPixelPosX() - (*itr)->GetPixelPosX());
				float yOffset = static_cast<float>(role->GetPixelPosY() - (*itr)->GetPixelPosY());

				const int OFFSET = 18;

				switch(role->GetDirection())
				{
				case Role::E_Up:
				case Role::E_Down:
					{
						if (xOffset <= -OFFSET)
						{
							role->SetDirection(Role::E_Left);
							return;
						}
						else if (xOffset >= OFFSET)
						{
							role->SetDirection(Role::E_Right);
							return;
						}
						break;
					}
				case Role::E_Left:
				case Role::E_Right:
					{
						if (yOffset <= -OFFSET)
						{
							role->SetDirection(Role::E_Down);
							return;
						}
						else if (yOffset >= OFFSET)
						{
							role->SetDirection(Role::E_Up);
							return;
						}
						break;
					}
				}
			

			role->SetCanMove(false);
			}
			
		}
		
		//检测是否吃道具
		if((*itr)->GetObjectType() == ObjectType::E_Prop && Util::isCollsionWithRect(RoleMoveRect,(*itr)->GetRectCollision()))
		{
			Prop* prop = dynamic_cast<Prop*>(HavaObject(Util::CreateMapName(m_pPlayer->GetMapPosX(),m_pPlayer->GetMapPosY(),L"Prop")));
			if (prop != NULL)
			{
				m_pPlayer->EatProp(prop);
				DeleteObject(prop->GetObjID());
				return;
			}
		}
		
		

	}

	if(collision)
		return;

	m_pPlayer->SetCollsionPixelPos(Point());
	role->SetStandOnBubble(false);
	role->SetCanMove(true);

	
}

bool PlayScene::OnMessage(LGCenter* agent, const Telegram& msg)
{
	return false;
}

void PlayScene::ChangeMap(int posX, int posY, MapType::E_MapType blockType)
{
	m_MapBlock[posX][posY] = blockType;
}

void PlayScene::Explosion(int x, int y, int power)
{
	bool UpEnd = false;
	bool DownEnd = false;
	bool LeftEnd = false;
	bool RightEnd = false;
	//中心
	Bubble* bubble = new Bubble(x,y,Bubble::E_Center,Bubble::E_None);
	m_MapBlock[x][y] = MapType::E_Danger;
	InsertObject(bubble);
	for (int i = 0; i < power; )
	{
		Bubble::E_StateType stateType;
		if (++i != power)
		{
			stateType = Bubble::E_Middle;
		}
		else
			stateType = Bubble::E_Tail;

		//上
		if(!UpEnd && y + i < YLENGTH)
		{
			if(DestoryMapPos(x,y+i,stateType,Bubble::E_Up))
				UpEnd = true;
		}
		//下
		if(!DownEnd && y - i >= 0)
		{
			if(DestoryMapPos(x,y-i,stateType,Bubble::E_Down))
				DownEnd = true;
		}
		//左
		if(!LeftEnd && x - i >= 0)
		{
			if(DestoryMapPos(x-i,y,stateType,Bubble::E_Left))
				LeftEnd = true;
		}
		//右
		if(!RightEnd && x + i < XLENGTH)
		{
			if(DestoryMapPos(x+i,y,stateType,Bubble::E_Right))
				RightEnd = true;
		}
	}
}

bool PlayScene::DestoryMapPos(int x, int y, Bubble::E_StateType stateType,Bubble::E_Direction direction)
{
	switch(m_MapBlock[x][y])
	{
	case MapType::E_TownBlockRed:
	case MapType::E_TownBlockYellow:
	case MapType::E_TownBox:
	case MapType::E_SandBox:
	case MapType::E_SandBlockBuff:
	case MapType::E_SandBlockYellow:
		{
			Bubble *bubble = new Bubble(x,y,stateType,direction);
			InsertObject(bubble);
			if(DeleteObject(Util::CreateMapName(x,y,L"Block")))
				return true;
			break;
		}
	case MapType::E_None:
		{
			Bubble *bubble = new Bubble(x,y,stateType,direction);
			InsertObject(bubble);
			return false;
		}
	case MapType::E_Bubble:
		{
			if(DeleteObject(Util::CreateMapName(x,y,L"Bubble")))
			{
				m_MapBlock[x][y] = MapType::E_Danger;
				return true;
			}
		}
	case MapType::E_Prop:
		{
			if(DeleteObject(Util::CreateMapName(x,y,L"Prop")))
			{
				m_MapBlock[x][y] = MapType::E_None;
				return false;
			}
		}
	default: //不可炸
		{
			return true;
		}
	}


	return true;
}
#pragma once

#include "LGHead.h"
#include "Scene.h"
#include "Block.h"
#include "Role.h"
#include "Bubble.h"
#include <vector>

using std::vector;

class AI;

const int XLENGTH = 15;
const int YLENGTH = 13;

class PlayScene : public Scene
{
	SINGLETON(PlayScene);
public:
	typedef vector<vector<MapType::E_MapType>> Map2DVec;

	//这三个是继承状态类的纯虚函数
	void Enter(LGCenter*);
	void Execute(LGCenter*, float deltaTime = 0.0f);
	void Exit(LGCenter*);

	void ChangeMap(int posX, int posY, MapType::E_MapType blockType);
	void Explosion(int x, int y, int power);
	bool MapChanged() const { return m_MapChanged; }
	void MapChanged(bool val) { m_MapChanged = val; }
	Map2DVec MapBlock() const { return m_MapBlock; }
	Role* Player() const { return m_pPlayer; }
	void Player(Role* val) { m_pPlayer = val; }
	GameObject* GetGameObject(int x, int y);
private:
	void CreateMapBlock();
	void KeyboardControl();
	void CollisionDetection(Role* obj, float deltaTime);
	bool OnMessage(LGCenter* agent, const Telegram& msg);
	bool DestoryMapPos(int x, int y, Bubble::E_StateType stateType,Bubble::E_Direction direction);
private:
	Map2DVec m_MapBlock; //方块地图，原点在左下角
	Role* m_pPlayer;
	AI* m_pEnemy;
	bool m_MapChanged;
};
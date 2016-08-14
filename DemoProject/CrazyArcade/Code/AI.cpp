#include "AI.h"
#include "RoleState.h"
#include "LGCenter.h"
#include "PlayScene.h"
#include <vector>
using namespace std;

AI::AI(std::wstring objName, int mapPosX, int mapPosY, E_RoleSpriteType spriteType)
	: Role(objName, mapPosX, mapPosY, spriteType), m_AISearcher(NULL)
{

}

AI::~AI()
{

}

void AI::Update(float deltaTime)
{
	Role::Update(deltaTime);
	UpdateAISearcher();
}

bool AI::IsGraphChange()
{
	return true;
}

void AI::UpdateAISearcher()
{
	PlayScene* currentScene = static_cast<PlayScene*>(g_pLGCenter->GetCurrentScene());
	if (currentScene->MapChanged())
	{
		SAFE_DELETE(m_AISearcher);
		m_AISearcher = new BFSearcher<MyGraphType>(CreateGraph(currentScene->MapBlock()));
		m_AISearcher->Search();
		Util::DebugOut() << "Æô¶¯ËÑË÷";
		currentScene->MapChanged(false);
	}
	if (m_AISearcher && m_AISearcher->Path().size())
	{
		int x, y;
		Util::Convert1Dto2D(m_AISearcher->Path().front().To(), YLENGTH, &x, &y);
		if (StepToDest(x,y))
		{
			m_AISearcher->HavePath().pop_front();
		}
	}
}

AI::MyGraphType* AI::CreateGraph(PlayScene::Map2DVec map)
{
	vector<pair<int, int>> moveVec = { make_pair(1,0), make_pair(0,1), make_pair(-1,0), make_pair(0, -1) };
	MyGraphType *graph = new MyGraphType(XLENGTH * YLENGTH);
	GraphAdjListVec adjListVec;
	for (int i = 0; i != XLENGTH; ++i)
	{
		for (int j = 0; j != YLENGTH; ++j)
		{
			GraphEdgeList currentEdgeList;

			for (int k = 0; k != moveVec.size(); ++k)
			{
				int posX = i + moveVec[k].first;
				int posY = j + moveVec[k].second;
				if (posX >= 0 && posY >= 0 && posX < XLENGTH && posY < YLENGTH 
					&& (map[i][j] == MapType::E_None || map[i][j] == MapType::E_Bubble ))
				{
					currentEdgeList.push_back(
						GraphEdge(
							Util::Convert2Dto1D(i, j, YLENGTH),
							Util::Convert2Dto1D(posX, posY, YLENGTH)
							)
						);
				}
			}

			adjListVec.push_back(currentEdgeList);
		}
	}
	
	//ÉèÖÃËÑË÷ÆðµãºÍÖÕµã
	PlayScene* currentScene = static_cast<PlayScene*>(g_pLGCenter->GetCurrentScene());
	Role* player = currentScene->Player();
	//Util::DebugOut() << MapPosX() << "," << MapPosY();
	graph->SourceNode(graph->GetNode(Util::Convert2Dto1D(MapPosX(), MapPosY(), YLENGTH)));
	//graph->DestNode(graph->GetNode(Util::Convert2Dto1D(14, 0, YLENGTH)));
	graph->DestNode(graph->GetNode(Util::Convert2Dto1D(player->MapPosX(), player->MapPosY(), YLENGTH)));
	//graph->DestNode(graph->GetNode(Util::Convert2Dto1D(10, 0, YLENGTH)));
	graph->AdjListVec(adjListVec);
	return graph;
}

bool AI::StepToDest(int x, int y)
{
	int xOffset = this->MapPosX() - x, yOffset = this->MapPosY() - y;
	//Util::DebugOut() << MapPosX() << ":" << MapPosY();
	//Util::DebugOut() << x << "," << y;
	if (xOffset != 0)
	{
		if (xOffset > 0)
			this->GetStateMachine()->ChangeState(WalkLeft::Instance());
		else
			this->GetStateMachine()->ChangeState(WalkRight::Instance());
	}
	else if (yOffset != 0)
	{
		if (yOffset > 0)
			this->GetStateMachine()->ChangeState(WalkDown::Instance());
		else
			this->GetStateMachine()->ChangeState(WalkUp::Instance());
	}
	else if (
	(GetRectCollision().GetXInt() - CalPixelPos(x, y).GetXInt() == 0
		&& GetRectCollision().GetYInt() - CalPixelPos(x, y).GetYInt() == 0)
		|| !this->GetCanMove()) //Åö×²Æ«²î
	{
		this->StopWalk();
		this->SpreadDirty();
		return true;
	}
	return false;
}

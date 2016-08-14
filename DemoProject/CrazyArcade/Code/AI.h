#pragma once
#include "Role.h"
#include "SparseGraph.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "GraphAlgorithm.h"
#include "Type.h"
#include "PlayScene.h"

class AI : public Role
{
	typedef SparseGraph<GraphNode, GraphEdge> MyGraphType;
	typedef typename MyGraphType::GraphEdgeList GraphEdgeList;
	typedef typename MyGraphType::GraphAdjListVec GraphAdjListVec;
public:
	AI(std::wstring objName, int mapPosX, int mapPosY, E_RoleSpriteType spriteType);
	virtual ~AI();
	virtual void Update(float deltaTime);

	GraphSearcher<MyGraphType>* AISearcher() const { return m_AISearcher; }
	void AISearcher(GraphSearcher<MyGraphType>* val) { m_AISearcher = val; }
	bool StepToDest(int x, int y);
protected:
	bool IsGraphChange();
	void UpdateAISearcher();
	AI::MyGraphType* CreateGraph(PlayScene::Map2DVec map);
private:
	GraphSearcher<MyGraphType>* m_AISearcher;
};
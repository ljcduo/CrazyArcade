#pragma once
#include <vector> 
#include <list>
#include "Util.h"

using std::vector;
using std::list;

template<typename NodeType, typename EdgeType>
class SparseGraph
{
public:
	typedef NodeType GraphNode;
	typedef EdgeType GraphEdge;
	typedef vector<GraphNode> GraphNodeVec;
	typedef list<GraphEdge> GraphEdgeList;
	typedef vector<GraphEdgeList> GraphAdjListVec;

	SparseGraph() :m_SourceNode(NULL), m_DestNode(NULL), m_Direct(false) {}
	SparseGraph(int nodeNum, bool direct = false);
	
	const vector<GraphNode>& NodeVec() const { return m_NodeVec; }
	void NodeVec(const vector<GraphNode>&  val) { m_NodeVec = val; } 
	const GraphAdjListVec& AdjListVec() const { return m_AdjListVec; }
	GraphAdjListVec& AdjListVec() { return m_AdjListVec; }
	void AdjListVec(const GraphAdjListVec& val) { m_AdjListVec = val; }
	GraphNode* SourceNode() const { return m_SourceNode; }
	void SourceNode(GraphNode* val) { m_SourceNode = val; }
	GraphNode* DestNode() const { return m_DestNode; }
	void DestNode(GraphNode* val) { m_DestNode = val; }
	GraphNode* GetNode(int index) {
		if (index < m_NodeVec.size()) return &m_NodeVec[index]; return NULL; }
	bool Direct() const { return m_Direct; }
	void Direct(bool val) { m_Direct = val; }
private:
	GraphNodeVec m_NodeVec;
	GraphAdjListVec m_AdjListVec;
	GraphNode* m_SourceNode;
	GraphNode* m_DestNode;
	bool m_Direct;
};

template<typename NodeType, typename EdgeType>
SparseGraph<NodeType, EdgeType>::SparseGraph(int nodeNum, bool direct /* = false */)
	: m_NodeVec(nodeNum), m_Direct(direct)
{
	for (int i = 0; i != nodeNum; ++i)
	{
		m_NodeVec[i].Index(i);
	}
}


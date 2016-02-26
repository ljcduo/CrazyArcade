#pragma once
#include <list>
#include "SparseGraph.h"

using std::list;

template<typename GraphType>
class GraphSearcher
{
public:
	typedef typename GraphType::GraphEdge GraphEdge;
	typedef typename GraphType::GraphEdgeList GraphEdgeList;
	typedef typename GraphType::GraphNodeVec GraphNodeVec;
	typedef typename GraphType::GraphAdjListVec GraphAdjListVec;

	GraphSearcher(GraphType* graph) :m_pGraph(graph), m_Route(m_pGraph->NodeVec().size(), -1) {}
	virtual bool Search() = 0;
	
	GraphType* Graph() const { return m_pGraph; }
	GraphEdgeList Path() const { return m_Path; }
protected:
	void Graph(GraphType* val) { m_pGraph = val; }
	void Path(GraphEdgeList val) { m_Path = val; }
	void AddRelateEdge(const GraphEdge& currentEdge, GraphEdgeList* retEdgeList);
	vector<int> Route() const { return m_Route; }
	vector<int>& Route() { return m_Route; }
	void CreatePath();
private:
	GraphType* m_pGraph;
	GraphEdgeList m_Path;
	vector<int> m_Route;
};

template<typename GraphType>
void GraphSearcher<GraphType>::CreatePath()
{
	int curIndex = m_pGraph->DestNode()->Index();
	while (curIndex != m_pGraph->SourceNode()->Index() && curIndex != -1)
	{
		int parentIndex = m_Route[curIndex];
		m_Path.push_front(GraphEdge(parentIndex, curIndex));
		curIndex = parentIndex;
	}
}

template<typename GraphType>
void GraphSearcher<GraphType>::AddRelateEdge(const GraphEdge& currentEdge, GraphEdgeList* retEdgeList)
{
		GraphEdgeList RelateEdgeList = Graph()->AdjListVec()[currentEdge.To()];
		for (GraphEdgeList::iterator itr = RelateEdgeList.begin(); itr != RelateEdgeList.end(); ++itr)
		{
			if (!itr->Visited() && !m_pGraph->GetNode(itr->To())->Visited())
			{
				retEdgeList->push_back(*itr);
				itr->Visited(true);
				m_pGraph->GetNode(itr->To())->Visited(true);
			}
		}
}

template<typename GraphType>
class BFSearcher : public GraphSearcher<GraphType>
{
public:
	BFSearcher(GraphType* graph) : GraphSearcher(graph){}
	bool Search();
};

template<typename GraphType>
bool BFSearcher<GraphType>::Search()
{
	if (Graph()->SourceNode() == NULL || Graph()->DestNode() ==  NULL)
		return false;
	Graph()->SourceNode()->Visited(true);
	GraphEdgeList SearchEdgeList;
	AddRelateEdge(GraphEdge(Graph()->SourceNode()->Index(), Graph()->SourceNode()->Index()), &SearchEdgeList);
	while (SearchEdgeList.size() != 0)
	{
		GraphEdge currentEdge = SearchEdgeList.front();
		SearchEdgeList.pop_front();
		Route()[currentEdge.To()] = currentEdge.From();
		if (currentEdge.To() == Graph()->DestNode()->Index())
		{
			CreatePath();
			return true;
		}
		AddRelateEdge(currentEdge, &SearchEdgeList);
	}
	return false;
}

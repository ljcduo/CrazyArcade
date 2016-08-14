#pragma once

#include "GraphNodeType.h"

class GraphNode
{
public:
	GraphNode() : m_Index(E_InvalidNode), m_Visited(false)  {}
	GraphNode(int index) : m_Index(index), m_Visited(false) {}

	virtual ~GraphNode() {}

	int Index() const { return m_Index; }
	void Index(int val) { m_Index = val; }
	bool Visited() const { return m_Visited; }
	void Visited(bool val) { m_Visited = val; }
private:
	int m_Index; // Starting with 0
	bool m_Visited; 
};

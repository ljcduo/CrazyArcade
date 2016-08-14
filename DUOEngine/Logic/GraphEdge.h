#pragma once

class GraphEdge
{
public:
	GraphEdge() :m_Visited(false) {}
	GraphEdge(int from, int to) : m_Visited(false), m_From(from), m_To(to) {}

	int From() const { return m_From; }
	void From(int val) { m_From = val; }
	int To() const { return m_To; }
	void To(int val) { m_To = val; }
	bool Visited() const { return m_Visited; }
	void Visited(bool val) { m_Visited = val; }
private:
	int m_From;
	int m_To;
	bool m_Visited;
};
#pragma once
#include <vector>

template<class T>
class Graph
{
public:
	Graph();
	Graph(const std::vector<T>& nodes);
	~Graph();

	int* edges = nullptr; //< 0 value means none; >= 0 values means there is an edge and the value is its weight
	std::vector<T>* nodes = nullptr;

	void AddEdge(int indexA, int indexB, int weight);
	void RemoveEdge(int indexA, int indexB);
};

template<class T>
Graph<T>::Graph()
{
	//TODO: Shouldn't be used but still
}

template<class T>
Graph<T>::Graph(const std::vector<T>& nodes)
{
	this->nodes = nodes;
	this->edges = new int[this->nodes->size()][this->nodes->size()];

	for (int y = 0; y < (sizeof(this->edges)); y++)
		for (int x = 0; x < (sizeof(this->edges[0])); x++)
			this->edges[x][y] = -1; //Default to -1, meaning there is no edge
}

template<class T>
Graph<T>::~Graph()
{
	delete edges, nodes;
}

template<class T>
void Graph<T>::AddEdge(int indexA, int indexB, int weight)
{
	this->edges[indexA][indexB] = weight;
	this->edges[indexB][indexA] = weight;
}

template<class T>
void Graph<T>::RemoveEdge(int indexA, int indexB)
{
	this->edges[indexA][indexB] = -1;
	this->edges[indexB][indexA] = -1;
}
#pragma once
#include <vector>
#include <iomanip>

template<class T>
class Graph
{
public:
	Graph();
	Graph(std::vector<T>& nodes);
	~Graph();

	double** adj = nullptr; //< 0 value means none; >= 0 values means there is an edge and the value is its weight
	std::vector<T>* nodes = nullptr;

	void AddEdge(int indexA, int indexB, double weight);
	void RemoveEdge(int indexA, int indexB);
};

template<class T>
Graph<T>::Graph()
{
	
}

template<class T>
Graph<T>::Graph(std::vector<T>& nodes)
{
	this->nodes = &nodes;
	this->adj = new double* [nodes.size()];

	for (size_t i = 0; i < nodes.size(); i++)
	{
		this->adj[i] = new double[this->nodes->size()];
		for (size_t j = 0; j < nodes.size(); j++)
			this->adj[i][j] = 0;
	}
}

template<class T>
Graph<T>::~Graph()
{
	delete adj, nodes;
}

template<class T>
void Graph<T>::AddEdge(int indexA, int indexB, double weight)
{
	this->adj[indexA][indexB] = weight;
	this->adj[indexB][indexA] = weight;
}

template<class T>
void Graph<T>::RemoveEdge(int indexA, int indexB)
{
	this->adj[indexA][indexB] = 0;
	this->adj[indexB][indexA] = 0;
}
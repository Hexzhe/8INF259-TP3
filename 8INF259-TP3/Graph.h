#pragma once
#include <vector>

template<class T>
class Graph
{
public:
	Graph();
	Graph(std::vector<T>& nodes);
	~Graph();

	int** adj = nullptr; //< 0 value means none; >= 0 values means there is an edge and the value is its weight
	std::vector<T>* nodes = nullptr;

	void AddEdge(int indexA, int indexB, int weight);
	void RemoveEdge(int indexA, int indexB);
	void PrintAdj();
};

template<class T>
Graph<T>::Graph()
{
	//TODO: Shouldn't be used, but still
}

template<class T>
Graph<T>::Graph(std::vector<T>& nodes)
{
	int V = nodes.size();

	this->nodes = &nodes;
	this->adj = new int* [V];

	for (int i = 0; i < V; i++)
	{
		this->adj[i] = new int[this->nodes->size()];
		memset(this->adj[i], -1, V*sizeof(int)); //TODO: What should we initialize the edges weight to?
	}
}

template<class T>
Graph<T>::~Graph()
{
	delete adj, nodes;
}

template<class T>
void Graph<T>::AddEdge(int indexA, int indexB, int weight)
{
	this->adj[indexA][indexB] = weight;
	this->adj[indexB][indexA] = weight;
}

template<class T>
void Graph<T>::RemoveEdge(int indexA, int indexB)
{
	this->adj[indexA][indexB] = -1;
	this->adj[indexB][indexA] = -1;
}

template<class T>
void Graph<T>::PrintAdj()
{
	for (int u = 0; u < this->nodes->size(); u++) //TODO: This is copied from https://www.geeksforgeeks.org/create-dynamic-2d-array-inside-class-c/ but the index vars are shit. Figure it out and replace them by x/y.
	{
		for (int v = 0; v < this->nodes->size(); v++)
			std::cout << this->adj[u][v] << " ";
		std::cout << std::endl;
	}
}
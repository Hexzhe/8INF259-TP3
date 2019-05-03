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
	void PrintAdj(bool detailed);
};

template<class T>
Graph<T>::Graph()
{
	//TODO: Shouldn't be used, but still
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
			this->adj[i][j] = -1;
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
	this->adj[indexA][indexB] = -1;
	this->adj[indexB][indexA] = -1;
}

template<class T>
void Graph<T>::PrintAdj(bool detailed)
{
	for (size_t y = 0; y < this->nodes->size(); y++)
	{
		std::cout << "        " << std::flush;

		if (detailed)
		{
			for (size_t x = 0; x < this->nodes->size(); x++)
				std::cout << std::setw(6) << this->adj[x][y] << " ";
		}
		else
		{
			for (size_t x = 0; x < this->nodes->size(); x++)
				std::cout << (this->adj[x][y] == -1 ? " " : "X") << " ";
		}

		std::cout << std::endl;
	}
}
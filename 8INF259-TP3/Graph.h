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
	this->nodes = &nodes;
	this->adj = new double* [(nodes.size())];

	for (int i = 0; i < (nodes.size()); i++)
	{
		this->adj[i] = new double[this->nodes->size()];
		memset(this->adj[i], 0, (nodes.size())*sizeof(double)); //No idea what's going on
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
void Graph<T>::PrintAdj()
{
	for (int y = 0; y < this->nodes->size(); y++)
	{
		std::cout << "        " << std::flush;
		for (int x = 0; x < this->nodes->size(); x++)
			std::cout << std::setw(6) << this->adj[x][y] << " ";

		std::cout << std::endl;
	}
}
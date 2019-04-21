#pragma once
#include <vector>
#include "GraphNode.h"

template<class T>
class Graph
{
public:
	Graph();
	Graph(std::vector<T>& items);
	~Graph();

	void Clear();

	//TODO: Check how do we implement a graph and do it
};

template<class T>
Graph<T>::Graph()
{
	//TODO: Initialize member values
}

template<class T>
Graph<T>::Graph(std::vector<T>& items)
{
	//TODO: Initialize the graph with the items provided
}

template<class T>
Graph<T>::~Graph()
{
	Clear();
}

template<class T>
void Graph<T>::Clear()
{
	//TODO: Remove all items, delete pointers and stuff
}
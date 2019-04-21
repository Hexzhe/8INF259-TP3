#pragma once
#include <string>

template<class T>
class GraphNode
{
public:
	GraphNode();
	GraphNode(std::string key, T& value);
	~GraphNode();

	std::string Key;
	T Value;
};

template<class T>
GraphNode<T>::GraphNode()
{
}

template<class T>
GraphNode<T>::GraphNode(std::string key, T& value)
{
	this->Key = key;
	this->Value = value;
}

template<class T>
GraphNode<T>::~GraphNode()
{
}

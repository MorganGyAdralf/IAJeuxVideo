#pragma once
#include <iostream>
#include <list>
#include <conio.h>

using namespace std;

enum class NodeType {	// Enum pour les types de Nodes, pour l'affichage de l'arbre
	Node,
	CompositeNode,
	Selector,
	Sequence,
	SpecializedNode
};

enum class NodeReturnType {
	Succes,
	Failure, 
	Running
};

class Node {
public:
	string nodeName_ = "Node Basique";	// Nom de la Node, pour l'affichage de l'arbre
	NodeType nodeType_ = NodeType::Node;
	bool wasRunning_ = false;	// Boolean pour savoir si la node a retourné Running

	~Node() = default;
	virtual NodeReturnType run() = 0;

	string getNodeName() const {
		return nodeName_;
	}

	NodeType getNodeType() const {
		return nodeType_;
	}
};

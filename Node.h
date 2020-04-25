#pragma once
#include <iostream>
#include <list>
#include <conio.h>

using namespace std;

enum class NodeType {
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

class Node {  // This class represents each node in the behaviour tree.
public:
	string nodeName = "Node Basique";
	NodeType nodeType = NodeType::Node;
	bool wasRunning = false;
	virtual NodeReturnType run() = 0;
	string getNodeName() {
		return nodeName;
	}
	NodeType getNodeType() {
		return nodeType;
	}
};

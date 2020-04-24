#pragma once
#include <iostream>
#include <list>

using namespace std;

enum class NodeType {
	Node,
	CompositeNode,
	Selector,
	Sequence,
	SpecializedNode
};

class Node {  // This class represents each node in the behaviour tree.
public:
	string nodeName = "Node Basique";
	NodeType nodeType = NodeType::Node;
	virtual bool run() = 0;
	string getNodeName() {
		return nodeName;
	}
	NodeType getNodeType() {
		return nodeType;
	}
};

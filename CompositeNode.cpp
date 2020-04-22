#include "CompositeNode.h"

const list<Node*>& CompositeNode::getChildren() const 
{ 
	return this->children;
}

void CompositeNode::addChild(Node* child) 
{ 
	children.emplace_back(child);
}
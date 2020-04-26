#include "CompositeNode.h"

const list<Node*>& CompositeNode::getChildren() const { 
	return this->children_;
}

void CompositeNode::addChild(Node* p_child) { 
	children_.emplace_back(p_child);
 }
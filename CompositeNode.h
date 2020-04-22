#pragma once
#include "Node.h"


class CompositeNode : public Node {
private:

	list<Node*> children;
public:
	const list<Node*>& getChildren() const;
	void addChild(Node* child);
};
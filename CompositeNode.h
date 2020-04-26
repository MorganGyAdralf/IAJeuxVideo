#pragma once
#include "Node.h"

class CompositeNode : public Node {	// Classe mère pour les nodes qui ont plusieurs enfants (Selector et Sequence)
private:
	list<Node*> children_;

public:
	~CompositeNode() = default;
	const list<Node*>& getChildren() const;
	void addChild(Node* p_child);
};
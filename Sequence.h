#pragma once
#include "CompositeNode.h"

class Sequence : public CompositeNode {
private:

public:
	Sequence() {
		nodeName = "Sequence";
		nodeType = NodeType::Sequence;
	}
	virtual NodeReturnType run() override {
		for (Node* child : getChildren()) {  // The generic Sequence implementation.
			if (child->run() == NodeReturnType::Failure)  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
				return NodeReturnType::Failure;
		}
		return NodeReturnType::Succes;  // All children suceeded, so the entire run() operation succeeds.
	}
};

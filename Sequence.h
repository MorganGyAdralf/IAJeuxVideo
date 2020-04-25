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
			if (!wasRunning || (wasRunning && child->wasRunning)) {
				wasRunning = false;
				NodeReturnType ret = child->run();
				if (ret == NodeReturnType::Failure)  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
					return NodeReturnType::Failure;
				else if (ret == NodeReturnType::Running) {
					wasRunning = true;
					return NodeReturnType::Running;
				}
			}
		}
		return NodeReturnType::Succes;  // All children suceeded, so the entire run() operation succeeds.
	}
};

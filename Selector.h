#pragma once
#include "CompositeNode.h"

class Selector : public CompositeNode {
public:
	Selector() {
		nodeName = "Selector";
		nodeType = NodeType::Selector;
	}
	virtual NodeReturnType run() override {
		for (Node* child : getChildren()) {  // The generic Selector implementation
			if (!wasRunning || (wasRunning && child->wasRunning)) {
				wasRunning = false;
				NodeReturnType ret = child->run();
				if (ret == NodeReturnType::Succes)  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
					return NodeReturnType::Succes;
				else if (ret == NodeReturnType::Running) {
					wasRunning = true;
					return NodeReturnType::Running;
				}
			}
		}
		return NodeReturnType::Failure;  // All children failed so the entire run() operation fails.
	}
};
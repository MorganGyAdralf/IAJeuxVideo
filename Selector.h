#pragma once
#include "CompositeNode.h"

class Selector : public CompositeNode {
public:
	Selector() {
		nodeName_ = "Selector";
		nodeType_ = NodeType::Selector;
	}

	virtual NodeReturnType run() override {
		for (Node* child : getChildren()) {
			if (!wasRunning_ || (wasRunning_ && child->wasRunning_)) {	// Condition pour pouvoir reprendre à partir de l'enfant en Running s'il y en avait un
				wasRunning_ = false;
				NodeReturnType ret = child->run();
				if (ret == NodeReturnType::Succes)
					return NodeReturnType::Succes;
				else if (ret == NodeReturnType::Running) {
					wasRunning_ = true;
					return NodeReturnType::Running;
				}
			}
		}
		return NodeReturnType::Failure;
	}
};
#pragma once
#include "CompositeNode.h"

class Sequence : public CompositeNode {
public:
	Sequence() {
		nodeName_ = "Sequence";
		nodeType_ = NodeType::Sequence;
	}

	virtual NodeReturnType run() override {
		for (Node* p_child : getChildren()) {
			if (!wasRunning_ || (wasRunning_ && p_child->wasRunning_)) {	// Condition pour pouvoir reprendre à partir de l'enfant en Running s'il y en avait un
				wasRunning_ = false;
				NodeReturnType ret = p_child->run();
				if (ret == NodeReturnType::Failure)
					return NodeReturnType::Failure;
				else if (ret == NodeReturnType::Running) {
					wasRunning_ = true;
					return NodeReturnType::Running;
				}
			}
		}
		return NodeReturnType::Succes;
	}
};

#pragma once
#include "CompositeNode.h"

class Selector : public CompositeNode {
public:
	virtual bool run() override {
		for (Node* child : getChildren()) {  // The generic Selector implementation
			if (child->run())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
				return true;
		}
		return false;  // All children failed so the entire run() operation fails.
	}
};
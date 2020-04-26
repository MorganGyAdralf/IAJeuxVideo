#pragma once
#include "Sequence.h"
#include "Selector.h"
#include "SpecializedNodes.h"

class Tree {
private:
	Player* treePlayer_;
	Sequence* root_;

public:
	Tree(Player* p_player);
	~Tree();
	void run() const;
};


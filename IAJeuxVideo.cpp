#pragma once
#include "Tree.h"

int main() {

    GameWorld* world = new GameWorld(15, 15);
    cout << "MAIN:: monde cree" << endl;
    Player* ourPlayer = new Player(world);
    cout << "MAIN:: joueur place" << endl;
    Tree behaviourTree = Tree(ourPlayer);
    cout << "MAIN:: arbre cree" << endl;
    system("pause");
    behaviourTree.run();
    system("pause");

    /*behaviourTree.~Tree();
    delete(ourPlayer);
    delete(world);*/

    return 0;
}

#pragma once
#include "Tree.h"

int main() {

    GameWorld* world = new GameWorld(15, 15);       // On règle la taille du monde de jeu ici, la largeur (x) d'abord, la hauteur (y) ensuite
    cout << "MAIN:: monde cree" << endl;
    Player* ourPlayer = new Player(world);
    cout << "MAIN:: joueur place" << endl;
    Tree* behaviourTree = new Tree(ourPlayer);
    cout << "MAIN:: arbre cree" << endl;
    system("pause");
    behaviourTree->run();
    system("pause");

    delete(world);
    delete(ourPlayer);
    delete(behaviourTree);

    return 0;
}

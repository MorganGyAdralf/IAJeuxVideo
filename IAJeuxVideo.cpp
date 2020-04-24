// IAJeuxVideo.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
#pragma once
#include <iostream>
#include "Tree.h"


int main() {

    GameWorld* world = new GameWorld(15, 15);
    cout << "monde cree" << endl;
    Player* ourPlayer = new Player(world);
    cout << "joueur place" << endl;
    Tree behaviourTree = Tree(ourPlayer);
    cout << "arbre cree" << endl;
    system("pause");
    behaviourTree.Run();
    system("pause");

    return 0;
}

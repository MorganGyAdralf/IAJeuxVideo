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

    /*bool tmp = ourPlayer.attackAMeleeTarget();
    cout << "le joueur a pu attacker : " << tmp << endl;
    tmp = ourPlayer.findClosestTarget();
    cout << "le joueur a pu trouver une target : " << tmp << endl;
    ourPlayer.turnTowardClosestTarget();
    cout << "le joueur a pu tourner vers sa target" << endl;
    while (ourPlayer.canAdvance().first && ourPlayer.hasNotAttainedObjective()) {
        ourPlayer.advance();
        cout << "le joueur a pu avancer d'une case" << endl;
    }
    tmp = (ourPlayer.canAdvance().second == SquareType::Target);
    cout << "le joueur est bloque par une target : " << tmp << endl;
    tmp = ourPlayer.turnForWall();
    cout << "le joueur a pu se tourner face au mur: " << tmp << endl;
    system("pause");*/

    system("pause");
    return 0;
}

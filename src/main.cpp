#include "gladiator.h"
#include "Vianney/creategraph.h"
#include <vector>
#include "Vianney/createPath.h"

#include "mouvement\movement.h"

int caseSize;
pathFinder coord_list;
pathFinder simplified_coord_list;
Gladiator *gladiator;

Position goal;

void reset();
void setup()
{
    // instanciation de l'objet gladiator
    gladiator = new Gladiator();
    // enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence

    gladiator->game->onReset(&reset); // GFA 4.4.1
}

void reset()
{
    // fonction de reset:
    caseSize = gladiator->maze->getSquareSize();
    std::vector<int> path = BFS();
    coord_list.size = path.size();
    simplified_coord_list = createCommands(coord_list);
    gladiator->log("_______PATH________");
    for (int i = 0; i < coord_list.size; i++)
    {
        coord_list.path_coord[i].i = path[i] % 12;
        coord_list.path_coord[i].j = path[i] / 12;
        gladiator->log(" i=%d; j=%d -------", coord_list.path_coord[i].i, coord_list.path_coord[i].j);
    }
    gladiator->log("_______PATH________");

    // initialisation de toutes vos variables avant le début d'un match
    goal = gladiator->robot->getData().position;
}
Position current;
void loop()
{
    static uint8_t count = 0;
    if(gladiator->game->isStarted()) { //tester si un match à déjà commencer
        //code de votre stratégie   
        current = gladiator->robot->getData().position;
        go_to(goal, current, gladiator);
        if (distance(current, goal) <= THRESHOLD && count < coord_list.size) {
            goal = getSquareCoor(coord_list.path_coord[count].i, coord_list.path_coord[count].j);
            ++count;
        }
        delay(200);
    }
}
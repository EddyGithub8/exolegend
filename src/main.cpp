#include "gladiator.h"
#include "Vianney/creategraph.h"
#include <vector>
#include "Vianney/createPath.h"
#include "Vianney/stateMachine.h"
#include "mouvement\movement.h"
#include "GameData\GameData.h"

GameState *game;
Gladiator *gladiator;
StateMachine *robot_state_machine;
void reset();
void setup()
{
    // instanciation de l'objet gladiator
    gladiator = new Gladiator();
    game = new GameState(gladiator);
    // enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence
    robot_state_machine = new StateMachine(game);
    gladiator->game->onReset(&reset); // GFA 4.4.1
}

void reset()
{
    // fonction de reset:
    game->reset();
    
    // initialisation de toutes vos variables avant le début d'un match
    game->goal = gladiator->robot->getData().position;
}
Position current;
uint8_t count = 0;
bool shit = true;
int f = 0;
void loop()
{

    if (gladiator->game->isStarted())
    { // tester si un match à déjà commencer
        // code de votre stratégie
        game->Update();
        robot_state_machine->transition();
    }
}
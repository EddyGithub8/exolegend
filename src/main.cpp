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
    robot_state_machine->currentState = StateMachine::State::ATTENTE;
    // initialisation de toutes vos variables avant le début d'un match
    game->goal = gladiator->robot->getData().position;
    liste.type = TYPE_DEPLACEMENT_IMMOBILE;
    liste.fin = game->goal;
    etat_automate_depl = INITIALISATION;

    // liste.type = TYPE_DEPLACEMENT_ROTATION;
    // liste.fin.a = PI/2;
    // // liste.type = TYPE_DEPLACEMENT_LIGNE_DROITE;
    // liste.fin.x = game->goal.x ; //+ 1./2. * gladiator->maze->getSquareSize();
    // liste.fin.y = game->goal.y ;//- 2 *  gladiator->maze->getSquareSize();
}
void loop()
{
    if (gladiator->game->isStarted())
    { // tester si un match à déjà commencer
        // code de votre stratégie
        game->Update();

        if (TempsEchantionnage(TE_10MS))
        {
            calcul();
        }
        
        robot_state_machine->transition();
    }
}
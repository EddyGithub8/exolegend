#include "stateMachine.h"
#include "GameData/GameData.h"
#include <vector>
#include "mouvement/goto.h"
#include "mouvement/movement.h"
#include "rocket.h"

StateMachine::StateMachine(GameState *game) : game(game), currentState(State::ATTENTE) {}

void StateMachine::switchState(State state)
{
    currentState = state;
    switch (state)
    {
    case State::RECHERCHE_FUSEE:
        game->count = 0;
        next_action = true;
        new_missile(game);
        break;
    case State::EXPLORATION:
        game->count = 0;
        next_action = true;
        new_mission(game);
        break;
    default:
        break;
    }
}

void StateMachine::transition()
{
    bool t_recherche_fusee = !game->gladiator->weapon->canLaunchRocket();
    bool t_ennemi_proche = ennemi_proche(game);
    bool t_recherche_cible = !t_recherche_fusee;

    switch (currentState)
    {
    case State::ATTENTE:
        if (t_recherche_cible)
        {
            currentState = State::RECHERCHE_CIBLE;
        }
        // if (t_recherche_fusee)
        // {
        //     switchState(State::RECHERCHE_FUSEE);
        // }
        else
        {
            switchState(State::EXPLORATION);
        }
        break;

    case State::RECHERCHE_FUSEE:
        if (game->gladiator->weapon->canLaunchRocket()) // cc garde
            currentState = State::ATTENTE;
        followPath(game);
        break;

    case State::EXPLORATION:
    {
        followPath(game);
        if (t_recherche_cible)
        {
            currentState = State::TIRER;
        }
        else if (game->count == game->coord_list.size)
        {
            currentState = State::ATTENTE;
        }
    }
    break;

    case State::PVP:
        executePVP();
        currentState = State::ATTENTE;
        break;

    case State::RECHERCHE_CIBLE:
        getTarget(game);
        if(!game->gladiator->weapon->canLaunchRocket())
            switchState(State::ATTENTE);
        break;

    case State::TIRER:
        getTarget(game);
        currentState = State::ATTENTE;
        break;
    }
}
void StateMachine::executePVP()
{
    RobotData my_data = game->gladiator->robot->getData();
    RobotData ally_data;
    RobotList ids_list = game->gladiator->game->getPlayingRobotsId();
    for (int i = 0; i < 4; i++)
    {
        if ((ids_list.ids[i] == 121 || ids_list.ids[i] != 120) && ids_list.ids[i] != my_data.id)
        {
            ally_data = game->gladiator->game->getOtherRobotData(ids_list.ids[i]);
        }
    }
    SpartanMode(game);
}

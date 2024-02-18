#include "goto.h"
#include "mouvement/movement.h"
#include "Vianney/createPath.h"
#include "Vianney/creategraph.h"
#include "Vianney/graphstrategy.h"
#include <vector>
using namespace std;

void followPath(GameState *game)
{    
    if (next_action && game->count < game->coord_list.size)
    {   
        next_action = false;
        game->goal = getSquareCoor(game->coord_list.path_coord[game->count].i, game->coord_list.path_coord[game->count].j, game->squareSize);
        game->count++;

        liste.fin = game->goal;
        liste.type = TYPE_DEPLACEMENT_LIGNE_DROITE;
        
    }
}

void new_missile(GameState *game)
{
    std::vector<int> path = BFS(game);
    game->coord_list.size = path.size();
    for (int i = 0; i < game->coord_list.size; i++)
    {
        game->coord_list.path_coord[i].i = path[i] % 12;
        game->coord_list.path_coord[i].j = path[i] / 12;
    }
    game->simplified_coord_list = createCommands(game->coord_list);
}

void new_mission(GameState *game){
    const MazeSquare* chosen = getBestSquare(game);
    std::vector<int> path = BFS(game, false, chosen->i, chosen->j);
    game->coord_list.size = path.size();
    for (int i = 0; i < game->coord_list.size; i++)
    {
        game->coord_list.path_coord[i].i = path[i] % 12;
        game->coord_list.path_coord[i].j = path[i] / 12;
    }
    game->simplified_coord_list = createCommands(game->coord_list);
}
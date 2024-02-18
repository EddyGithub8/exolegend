#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <tuple>
#include "getcaseneighboor.h"
#include "graphstrategy.h"
#include <unordered_map>
#include <algorithm>
#include "mouvement/movement.h"

using namespace std;

const MazeSquare* getBestSquare(GameState *game){
    int max = -5555;
    const MazeSquare* chosen_one = game->gladiator->maze->getSquare(6, 6);
    for(int i = 0; i < 12; ++i) {
        for(int j= 0; j < 12; ++j) {
            int heur = heuristic(game->gladiator->maze->getSquare(i, j), game);
            if(heur > max){
                max = heur;
                chosen_one = game->gladiator->maze->getSquare(i, j);
            }  
        }
    }
    return chosen_one;
}

int heuristic(const MazeSquare *sqr, GameState *game)
{
    // si c'est proche du bord
    int h = 0;
    uint32_t time = millis() / 1000; // temps en secondes
    int i = sqr->i;
    int j = sqr->j;
    uint32_t time_up=time-game->start_time_heur;
    //game->gladiator->log("TIME up %d : ", time_up);
    
     // temps à partir du quel il faut faire attention au shr
    uint32_t time_between_shrinking = 17;
    if (time_up >( time_between_shrinking-2))
    {
        int shrink_progress = time_up / time_between_shrinking;
        //game->gladiator->log("SCHRINK PROGRESS %d : ", shrink_progress);
        if (i <= shrink_progress || (12 - i) <= shrink_progress || j <= shrink_progress || (12 - j) <= shrink_progress)
        {
            //game->gladiator->log("case a eviter en %d,%d", i, j);
            h -= 5000000;
        }
    }
    uint8_t possession = sqr->possession;

    if(sqr->coin.value == 1) h += 100000;

    if(possession == 0)
        h += 1000;
    else if(possession == game->myData.teamId)
        h -= 1000;
    else
        h += 3000;
    // if (abs(i + j * 12 - game->allyData.position.x + game->allyData.position.y * 12) < 1)
    // {
    //     h -= 500;
    // }
    if(i == 0 && j == 0) h -= 999999;

    Position square = getSquareCoor(i, j, game->squareSize);

    float dx = abs(square.x-game->myData.position.x);
    float dy = abs(square.y-game->myData.position.y);


    if(sqrt(dx*dx - dy*dy) <= 0.01) h -= 8888888;
    if(dx >= 0.3 && dx <= 1)  h += 30;
    if(dy >= 0.3 && dy <= 1)  h += 30;

    if(sqrt(dx*dx - dy*dy) > 1.2) h -= 9875354;
    
    return h;
}
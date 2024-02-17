#include "math.h"
#include "guardConditions.h"
#define dist_thresh 1.7
using namespace std;

float distEucl(int ia, int ja, int ib, int jb)
{
    double dx = ia - ib;
    double dy = ja - jb;
    return sqrt(dx * dx + dy * dy);
}

bool ennemi_proche(GameState *game)
{
    if(game->er1Data.id == 0 || game->er2Data.id == 0) return false;

    Position me = game->myData.position;
    Position er1 = game->er1Data.position;
    Position er2 = game->er2Data.position;
    
    return distEucl(me.x, me.y, er1.x, er1.y) < dist_thresh  || distEucl(me.x, me.y, er2.x, er2.y)< dist_thresh;
}
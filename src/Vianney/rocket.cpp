#include "rocket.h"
#include "Gamedata/GameData.h"
#include "float.h"
#include "mouvement/movement.h"
using namespace std;

void getTarget(GameState *game)
{

    float dx = 1;
    float dy = 1;
    double alpha = atan2(dy, dx);
    float theta = game->myData.position.x;
    Position cons;
    Position pos;
    cons.a = alpha;
    pos.a = theta;
    go_to(cons, pos, game->gladiator);
}

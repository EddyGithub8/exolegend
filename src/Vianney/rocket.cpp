#include "rocket.h"
#include "Gamedata/GameData.h"
#include "float.h"
#include "mouvement/movement.h"
using namespace std;

void getTarget(GameState *game)
{
    Position me = game->myData.position;
    Position ally = game->allyData.position;
    Position er1 = game->er1Data.position;
    Position er2 = game->er2Data.position;
    // pos de l'allier
    float dxa = ally.x - me.x;
    float dya = ally.y - me.y;
    // dpos des ennemis
    float dx1 = er1.x - me.x;
    float dy1 = er1.y - me.y;
    float dx2 = er2.x - me.x;
    float dy2 = er2.y - me.y;

    // angles
    double alpha_allie = atan2(dya, dxa);
    double alpha_ennemi1 = atan2(dy1, dx1);
    double alpha_ennemi2 = atan2(dy2, dx2);

    // calcul des dist eucli
    float dist1 = sqrt(dx1 * dx1 + dy1 * dy1);
    float dist2 = sqrt(dx2 * dx2 + dy2 * dy2);
    float dista = sqrt(dxa * dxa + dya * dya);

    // on target le robot le plus proche sur lequel il n'y a pas de trajet
    Position *ennemy;
    if (dist1 < dist2 && dist1 < 4 && alpha_allie != alpha_ennemi1)
    {
        ennemy = &er1;
    }
    else if (dist2 < dist1 and dist2 < 4 && alpha_allie != alpha_ennemi2)
    {
        ennemy = &er2;
    }

    Position cons;
    Position pos;
    cons.a = 0;
    pos.a = me.a;
    // go_to(cons, pos, game->gladiator);
    liste.type = TYPE_DEPLACEMENT_LIGNE_DROITE;
    liste.fin = pos;
}

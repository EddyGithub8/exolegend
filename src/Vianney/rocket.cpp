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
    float dist1 = sqrt(dx1 * dx1 + dy1 * dy1) + (game->er1Data.id == 0)*99999;
    float dist2 = sqrt(dx2 * dx2 + dy2 * dy2) + (game->er2Data.id == 0)*99999;
    // float dista = sqrt(dxa * dxa + dya * dya);

    // on target le robot le plus proche sur lequel il n'y a pas de trajet
    if (dist1 < dist2)
    {
        go_to_angle(alpha_ennemi1, me.a, game);
    }
    else if (dist2 < dist1)
    {
        go_to_angle(alpha_ennemi2, me.a, game);
    }

}
void go_to_angle(float cons_angle, float pos_angle, GameState *game)
{
    double consvl, consvr;
    const float K = 0.9;
    float diff_angle = reductionAngle(cons_angle - pos_angle);
    if (abs(diff_angle) > 1 / 60)
    {
        // if(diff_angle > 0){
        //     consvl = -0.3;
        //     consvr = 0.3;
        // }else{
        //     consvl = 0.3;
        //     consvr = -0.3;
        // }
        consvl = -K * diff_angle;
        consvr = K * diff_angle;

        consvl = abs(consvl) > 0.3 ? (consvl > 0 ? 0.3 : -0.3) : consvl;
        consvr = abs(consvr) > 0.3 ? (consvr > 0 ? 0.3 : -0.3) : consvr;
    }
    else
    {
        consvr = 0;
        consvl = 0;
    }

    game->gladiator->control->setWheelSpeed(WheelAxis::RIGHT, consvr, false); // GFA 3.2.1
    game->gladiator->control->setWheelSpeed(WheelAxis::LEFT, consvl, false);
    if(abs(cons_angle - pos_angle) < 0.1){
        game->gladiator->weapon->launchRocket();
    }
}

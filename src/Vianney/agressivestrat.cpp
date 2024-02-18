// #include "agressivestrat.h"
// #include "Sparta/melee.h"
// #include "mouvement/movement.h"
// #include "creategraph.h"
// #include "createpath.h"
// #include <vector>
// using namespace std;
// float distEucl(int ia, int ja, int ib, int jb)
// {
//     double dx = ia - ib;
//     double dy = ja - jb;
//     return sqrt(dx * dx + dy * dy);
// }

// void agressivStrat(GameState *game)
// {
//     // on attaque le robot qui a l'id le plus petit
//     //  position des robot adverses
//     Position *ennemy;
//     Position me = game->myData.position;
//     Position ally = game->allyData.position;
//     Position er1 = game->er1Data.position;
//     Position er2 = game->er2Data.position;
//     if (game->er1Data.id < game->er2Data.id && game->er1Data.id != 0)
//     {
//         ennemy = &er1;
//     }
//     else
//     {
//         ennemy = &er2;
//     }

//     if (game->myData.id > game->allyData.id)
//     {
//         int goal_i = ennemy->x - 1;
//         int goal_j = ennemy->y;
//     }
//     else
//     {
//         int goal_i = ennemy->x + 1;
//         int goal_j = ennemy->y;
//     }

//     // si on est trop proche de l'allié
//     if (distEucl(me.x, me.y, ally.x, ally.y) < 1.2)
//     {
//         float dxa = ally.x - me.x;
//         float dya = ally.y - me.y;
//         double alpha_allie = atan2(dya, dxa);
//         Position cons;
//         Position pos;
//         cons.x = me.x;
//         cons.y = me.y;
//         cons.a = alpha_allie + PI;
//         go_to(cons, me);
//     }
//     if (distEucl(me.x, me.y, ennemy->x, ennemy->y) < 1.2)
//     {
//         SpartanMode(game);
//     }

//     std::vector<int> path = BFS(game, false, ennemy->x, ennemy->y);
//     game->coord_list.size = path.size();
//     for (int i = 0; i < game->coord_list.size; i++)
//     {
//         game->coord_list.path_coord[i].i = path[i] % 12;
//         game->coord_list.path_coord[i].j = path[i] / 12;
//     }
//     game->simplified_coord_list = createCommands(game->coord_list);
// }
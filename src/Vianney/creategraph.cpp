#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <tuple>
#include "getcaseneighboor.h"
#include "creategraph.h"
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<int> BFS()
{
    // Marquer tous les sommets comme non visités
    bool visited[144] = {false}; // les coordonnées des sommets sont codées en un int a, tq : a=i+j*12

    // position du robot comme case de départ

    const MazeSquare *square = gladiator->maze->getNearestSquare();
    uint8_t i_index = square->i; // indice colonne selon ma convention
    uint8_t j_index = square->j; // indice ligne selon ma convention
    int start_coord = i_index + j_index * 12;
    int end_coord;
    // Créer une file pour le BFS
    queue<int> q;
    // Marquer le sommet de départ comme visité et l'ajouter à la file
    visited[start_coord] = true;
    q.push(start_coord);
    unordered_map<int, int> path_dict;

    while (!q.empty())
    {
        // Extraire un sommet de la file
        int currentVertex = q.front();
        int i = currentVertex % 12;
        int j = currentVertex / 12;
        q.pop();
        int *result = getCaseNeighboor(i, j);
        const MazeSquare *sq = gladiator->maze->getSquare(i, j);
        Coin c = sq->coin;
        uint8_t rocket = c.value;
        if (rocket)
        {
            gladiator->log("FUSEE TROUVEE en %d,%d", i, j);

            end_coord = currentVertex;
            while (!q.empty())
            {
                q.pop();
            }
            break;
        }
        // Parcourir tous les sommets adjacents du sommet courant
        for (int i = 0; i < 4; ++i)
        {

            int adjacentVertex = result[i];
            gladiator->log("case visitée :%d,%d", adjacentVertex % 12, adjacentVertex / 12);
            // Si un sommet adjacent n'a pas encore été visité, le marquer comme visité
            // et l'ajouter à la file
            if (adjacentVertex != 200)
            {
                if (!visited[adjacentVertex])
                {
                    visited[adjacentVertex] = true;
                    q.push(adjacentVertex);
                    path_dict[adjacentVertex] = currentVertex;
                }
            }
        }
    }
    vector<int> path;
    int current = end_coord;
    while (current != start_coord)
    {
        path.push_back(current);
        current = path_dict.at(current);
    }
    path.push_back(start_coord);
    reverse(path.begin(), path.end()); // Inverser le chemin car on l'a construit de la fin au début
    return path;
}
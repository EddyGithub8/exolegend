#pragma once
#include "getcaseneighboor.h"
#include <vector>
#include "GameData/GameData.h"

std::vector<int> BFSPruned(GameState *game);
float heuristic(const MazeSquare *sqr, GameState *game);

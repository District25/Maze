#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "maze.h"
#include "Coord.h"
#include <set>
#include <algorithm>
#include <random>

class Algorithm
{
public:
    Algorithm();
    void findPath(Maze *maze, Coord currentPos, std::vector<Coord>& visited);
    void InitGrid(Maze *maze);
};

#endif // ALGORITHM_H

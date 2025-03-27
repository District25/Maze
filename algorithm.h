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
    void leftWallFollower(Maze *maze, Coord currentPos);
};

#endif // ALGORITHM_H

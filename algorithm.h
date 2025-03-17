#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "maze.h"
#include "Coord.h"

class Algorithm
{
public:
    Algorithm();
    Coord findPath(Maze* maze);
};

#endif // ALGORITHM_H

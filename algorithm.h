#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "maze.h"
#include "Coord.h"

class Algorithm
{
public:
    Algorithm();
    void leftWallFollower(Maze *maze, Coord currentPos);
    void findOptimalPath();
    const std::vector<Coord>& getOptimalPath() const;
    void resetPaths();
private:
    std::vector<Coord> fullPath;
    std::vector<Coord> optimalPath;
};

#endif // ALGORITHM_H

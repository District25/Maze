#include "algorithm.h"
#include <vector>
#include <algorithm>
Algorithm::Algorithm() {}

void Algorithm::findPath(Maze *maze, Coord currentPos, std::vector<Coord>& visited)
{
    Coord exit = maze->getExitPosition();
    visited.push_back(currentPos);

    if (currentPos == exit) { return; }

    std::vector<Coord> nextMove = {
        {currentPos.x + 1, currentPos.y},
        {currentPos.x, currentPos.y + 1},
        {currentPos.x - 1, currentPos.y},
        {currentPos.x, currentPos.y - 1}
    };

    for (auto move : nextMove) {

        if (maze->isCellFree(move.x, move.y) && !(move == visited[visited.size() - 2])) {
            maze->moveRobot(move);
            return;
        }


    }

    /*if (visited.size() >= 2) {
        Coord previous = visited[visited.size() - 2];

        if (maze->isCellFree(previous.x, previous.y)) {
            maze->moveRobot(previous);
            return;
        }
    }*/

}


void Algorithm::InitGrid(Maze *maze)
{

}

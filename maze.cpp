#include "maze.h"

Maze::Maze(){
    grid = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}
    };
    robotPosition = Coord(1, 1);
    exitPosition = Coord(3, 4);
}

Maze::Maze(int rows, int cols) {
    grid.resize(rows, std::vector<int>(cols, 0));
    robotPosition = Coord(0, 0);
}

Coord Maze::getRobotPosition() const { return robotPosition; }

Coord Maze::getExitPosition() const { return exitPosition; }

void Maze::moveRobot(Coord next)
{
    if(isCellFree(next.x, next.y)){
        robotPosition = next;
        notifyObservers();
    }
}

bool Maze::isCellFree(int x, int y) const
{
    return grid[x][y] == 0;
}

void Maze::subscribe(Observer* o) {
    observers.push_back(o);  // Ajouter un observer à la liste
}

void Maze::notifyObservers() {
    for (Observer* o : observers) {
        o->update();  // Appeler update() sur chaque observer
    }
}

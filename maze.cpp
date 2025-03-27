#include "maze.h"
#include <random>
#include <iostream>
#include <stack>

Maze::Maze(){
    grid = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1},
        {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    robotPosition = Coord(1,1);
    exitPosition = Coord(14, 14);
    Win = false;
}

Maze::Maze(int rows, int col)
{
    grid.resize(rows, std::vector<int>(col, 1));
    robotPosition = Coord(0, 0);
    exitPosition = Coord(getCol() - 1, getRows() - 1);
    //generateMaze();
}

Coord Maze::getRobotPosition() const { return robotPosition; }

Coord Maze::getExitPosition() const { return exitPosition; }

void Maze::moveRobot(Coord next)
{
    robotPosition = next;
    notifyObservers();
}

bool Maze::isCellFree(int x, int y) const
{
    return (Coord(y, x) == getRobotPosition() || Coord(y, x) == getExitPosition() || grid[x][y] == 0);
}

bool Maze::hasWon(){ return Win; }

void Maze::generateMaze()
{
    for(int i = 0; i<getRows(); i++){
        for(int j = 0; j<getCol(); j++){
            if((j % 2 == 1) && (i % 2 == 1)){
                grid[i][j] = 0;
            }
        }
    }
}


Coord Maze::placeRobotRandomly() const
{

}



void Maze::subscribe(Observer* o) {
    observers.push_back(o);  // Ajouter un observer à la liste
}

void Maze::notifyObservers() {
    for (Observer* o : observers) {
        o->update();  // Appeler update() sur chaque observer
    }
}

int Maze::getRows() const{ return grid.size();}

int Maze::getCol() const{ return grid[0].size();}

void Maze::setWin(bool state){ Win = state; }

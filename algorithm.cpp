#include "algorithm.h"
#include <vector>
#include <algorithm>
#include <QDebug>
Algorithm::Algorithm() {}

// THIS ALGO FOLLOW THE LEFT WALL
void Algorithm::leftWallFollower(Maze *maze, Coord currentPos)
{
    enum Direction {UP, RIGHT, DOWN, LEFT};

    static Direction currentDir = RIGHT; // ROBOT DIRECTION

    std::vector<Coord> moves = {
        {0, -1}, // UP -> y-1
        {1, 0}, // RIGHT -> x+1
        {0, 1}, // DOWN -> y+1
        {-1, 0} // LEFT -> x-1
    };

    if (fullPath.empty() || !(fullPath.back() == currentPos)) {
        fullPath.push_back(currentPos);
    }


    // NEW POSITION TO TEST
    Coord newPos = {currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y};

    switch(currentDir){
    case UP:
        if(!maze->isCellFree(currentPos.x + moves[LEFT].x, currentPos.y + moves[LEFT].y)){ // WALL on LEFT ?
            if(maze->isCellFree(newPos.x, newPos.y)) // FORWARD OK ?
                maze->moveRobot(newPos);
            else{ // FOWRWARD ISNT OK :

                // TURNING RIGHT IS OK ?
                if(maze->isCellFree(currentPos.x + moves[RIGHT].x, currentPos.y + moves[RIGHT].y)){
                    currentDir = RIGHT;
                }
                // NO, SO GO DOWN
                else{
                    currentDir = DOWN;
                }
            }
        }
        else{ // NO WALLS ON LEFT, THEN GO LEFT
            currentDir = LEFT;
        }
        break;

    case RIGHT:
        if(!maze->isCellFree(currentPos.x + moves[UP].x, currentPos.y + moves[UP].y)){ // WALL ABOVE ??
            if(maze->isCellFree(newPos.x, newPos.y)) // FORWARD OK ?
                maze->moveRobot(newPos);
            else{ // FORWARD ISN'T OK
                // TURNING DOWN IS OK ?
                if(maze->isCellFree(currentPos.x + moves[DOWN].x, currentPos.y + moves[DOWN].y)){
                    currentDir = DOWN;
                }
                // NO, SO GO LEFT
                else{
                    currentDir = LEFT;
                }
            }
        }
        else{ // NO WALLS ABOVE, THEN GO UP
            currentDir = UP;
        }
        break;

    case DOWN:
        if(!maze->isCellFree(currentPos.x + moves[RIGHT].x, currentPos.y + moves[RIGHT].y)){ // WALL ON RIGHT ??
            if(maze->isCellFree(newPos.x, newPos.y)) // FORWARD OK ?
                maze->moveRobot(newPos);
            else{ // FORWARD ISN'T OK
                // TURNING LEFT IS OK ?
                if(maze->isCellFree(currentPos.x + moves[LEFT].x, currentPos.y + moves[LEFT].y)){
                    currentDir = LEFT;
                }
                // NO, SO GO UP
                else{
                    currentDir = UP;
                }
            }
        }
        else{ // NO WALLS ON RIGHT, THEN GO RIGHT
            currentDir = RIGHT;
        }
        break;

    case LEFT:
        if(!maze->isCellFree(currentPos.x + moves[DOWN].x, currentPos.y + moves[DOWN].y)){ // WALL UNDER ?
            if(maze->isCellFree(newPos.x, newPos.y)) // FORWARD OK ?
                maze->moveRobot(newPos);
            else{ // FORWARD ISN'T OK
                // TURNING UP IS OK ?
                if(maze->isCellFree(currentPos.x + moves[UP].x, currentPos.y + moves[UP].y)){
                    currentDir = UP;
                }
                // NO, SO GO RIGHT
                else{
                    currentDir = RIGHT;
                }
            }
        }
        else{ // NO WALL UNDER, THEN GO UNDER
            currentDir = DOWN;
        }
        break;

    }
    maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
    if (maze->getRobotPosition() == maze->getExitPosition()) {
        fullPath.push_back(maze->getRobotPosition());
    }
}

// Remove iterations of fullPath and so get the direct way to the exit
void Algorithm::findOptimalPath() {
    std::vector<Coord> stack;
    for (const Coord& pos : fullPath) {
        // If Coord is already visited
        auto it = std::find(stack.begin(), stack.end(), pos);
        if (it != stack.end()) {
            stack.erase(it + 1, stack.end()); // remove backtracked path
        } else {
            stack.push_back(pos); // else, we move
        }
    }

    optimalPath = stack;
}

// Return the complete optimal path with the Coord value
const std::vector<Coord>& Algorithm::getOptimalPath() const { return optimalPath; }

// Clear the different vectors of this class, used when a reset is called
void Algorithm::resetPaths()
{
    optimalPath.clear();
    fullPath.clear();
}



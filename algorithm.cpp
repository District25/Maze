#include "algorithm.h"
#include <vector>
#include <algorithm>
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

    // NEW POSITION TO TEST
    Coord newPos = {currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y};

    switch(currentDir){
    case UP:
        if(!maze->isCellFree(currentPos.y + moves[LEFT].y, currentPos.x + moves[LEFT].x)){ // WALL on LEFT ?
            if(maze->isCellFree(newPos.y, newPos.x)) // FORWARD OK ?
                maze->moveRobot(newPos);
            else{ // FOWRWARD ISNT OK :

                // TURNING RIGHT IS OK ?
                if(maze->isCellFree(currentPos.y + moves[RIGHT].y, currentPos.x + moves[RIGHT].x)){
                    currentDir = RIGHT;
                    maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
                }
                // NO, SO GO DOWN
                else{
                    currentDir = DOWN;
                    maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
                }
            }
        }
        else{ // NO WALLS ON LEFT, THEN GO LEFT
            currentDir = LEFT;
            maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
        }
        break;
    case RIGHT:
        if(!maze->isCellFree(currentPos.y + moves[UP].y, currentPos.x + moves[UP].x)){ // mur en haut ?
            if(maze->isCellFree(newPos.y, newPos.x)) // devant OK ?
                maze->moveRobot(newPos);
            else{
                if(maze->isCellFree(currentPos.y + moves[DOWN].y, currentPos.x + moves[DOWN].x)){
                    currentDir = DOWN;
                    maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
                }
                else{
                    currentDir = LEFT;
                    maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
                }
            }
        }
        else{
            currentDir = UP;
            maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
        }
        break;
    case DOWN:
        if(!maze->isCellFree(currentPos.y + moves[RIGHT].y, currentPos.x + moves[RIGHT].x)){ // mur à droite ?
            if(maze->isCellFree(newPos.y, newPos.x)) // devant OK ?
                maze->moveRobot(newPos);
            else{
                if(maze->isCellFree(currentPos.y + moves[LEFT].y, currentPos.x + moves[LEFT].x)){
                    currentDir = LEFT;
                    maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
                }
                else{
                    currentDir = UP;
                    maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
                }
            }
        }
        else{
            currentDir = RIGHT;
            maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
        }
        break;
    case LEFT:
        if(!maze->isCellFree(currentPos.y + moves[DOWN].y, currentPos.x + moves[DOWN].x)){ // mur en bas ?
            if(maze->isCellFree(newPos.y, newPos.x)) // devant OK ?
                maze->moveRobot(newPos);
            else{
                if(maze->isCellFree(currentPos.y + moves[UP].y, currentPos.x + moves[UP].x)){
                    currentDir = UP;
                    maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
                }
                else{
                    currentDir = RIGHT;
                    maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
                }
            }
        }
        else{
            currentDir = DOWN;
            maze->moveRobot(Coord(currentPos.x + moves[currentDir].x, currentPos.y + moves[currentDir].y));
        }
        break;

    }
}


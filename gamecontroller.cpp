#include "gamecontroller.h"

GameController::GameController(Maze *maze, InputView *iv, OutputView *ov, Algorithm *algo)
{
    model = maze;
    inputView = iv;
    outputView = ov;
    algorithm = algo;
}
void GameController::startGame(){
    model -> notifyObservers();
}

void GameController::ComputeNextMove()
{

}

bool GameController::isMoveValid()
{

}

bool GameController::checkVictory()
{

}

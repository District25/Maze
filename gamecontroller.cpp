#include "gamecontroller.h"


GameController::GameController(Maze *maze, InputView *iv, OutputView *ov, Algorithm *algo)
{
    model = maze;
    inputView = iv;
    outputView = ov;
    algorithm = algo;

    model->subscribe(ov);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameController::ComputeNextMove);
}
void GameController::startGame(){
    outputView->show();
    timer->start(100);
}


void GameController::ComputeNextMove()
{
    if(!checkVictory()){
        algorithm->leftWallFollower(model, model->getRobotPosition());
        model->notifyObservers();
    }
    else
    {
        timer->stop();
    }
}

bool GameController::isMoveValid()
{
    return true;
}

bool GameController::checkVictory()
{
    Coord exitPos = model->getExitPosition();
    Coord robotPos = model->getRobotPosition();
    if(robotPos.x == exitPos.x && robotPos.y == exitPos.y){
        return true;
        model->setWin(true);
    }
    else
        return false;
}

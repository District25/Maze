#include "gamecontroller.h"

// Parameter constructor
GameController::GameController(Maze *maze, InputView *iv, OutputView *ov, Algorithm *algo)
{
    model = maze;
    inputView = iv;
    outputView = ov;
    algorithm = algo;

    model->subscribe(ov);
    indexAnim=0;
    outputView->setAlgorithm(algorithm);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameController::ComputeNextMove);
}
// Start the whole game
void GameController::startGame(){
    outputView->show();
    timer->start(5);
}

// The brain function that manage all the functions calls and conditions
void GameController::ComputeNextMove()
{
    checkVictory();
    // Still haven't found the exit
    if(!model->hasWon()){
        algorithm->leftWallFollower(model, model->getRobotPosition());
        model->notifyObservers();
    }
    else // exit found by robot !
    {
        timer->start(50);
        if(indexAnim==0)
            algorithm->findOptimalPath();
        // Manage the animation to show optimal Path
        if(indexAnim < (algorithm->getOptimalPath().size())){
            model->moveRobot((algorithm->getOptimalPath())[indexAnim]);
            model->notifyObservers();
            indexAnim++;
        }
        else
            timer->stop();
    }
}

// Check if robot has found the exit !
bool GameController::checkVictory()
{
    Coord exitPos = model->getExitPosition();
    Coord robotPos = model->getRobotPosition();
    if(robotPos == exitPos){
        model->setRobotPosition(model->getInitRobotPosition());
        model->setWin(true);
        return true;
    }
    else
        return false;
}

// Get the index of the optimal Path vector
size_t GameController::getIndexAnim() const { return indexAnim; }

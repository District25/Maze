#include "gamecontroller.h"

// Parameter constructor
GameController::GameController(Maze *maze, InputView *iv, OutputView *ov, Algorithm *algo, buttonView* bv)
{
    model = maze;
    inputView = iv;
    outputView = ov;
    algorithm = algo;
    btnView = bv;

    connect(btnView, &buttonView::saveRequested, this, &GameController::saveMazeToFile);
    connect(btnView, &buttonView::loadRequested, this, &GameController::loadMazeFromFile);
    connect(btnView, &buttonView::pauseRequested, this, &GameController::pauseSimulation);
    connect(btnView, &buttonView::randMazeRequested, this, &GameController::generateRandMaze);
    connect(btnView, &buttonView::randRobotPosRequested, this, &GameController::placeRobot);
    connect(btnView, &buttonView::startSimulRequested, this, &GameController::startSimulation);

    model->subscribe(ov);
    outputView->setAlgorithm(algorithm);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameController::ComputeNextMove);
}

// Reset attributes and simulation
void GameController::reset()
{
    pauseSimulation();
    indexAnim = 0;
    model->setWin(false);
    algorithm->resetPaths();
    model->setRobotPosition(Coord(1, 1)); // safety
}
// Start the whole game
void GameController::startGame(){
    timer->start(2);
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
        timer->start(50); // Lower the speed to admire the aniimation
        if(indexAnim==0)
            algorithm->findOptimalPath();
        // Manage the animation to show optimal Path
        if(indexAnim < (algorithm->getOptimalPath().size())){
            model->moveRobot((algorithm->getOptimalPath())[indexAnim]);
            model->notifyObservers();
            indexAnim++;
        }
        else{
            pauseSimulation();
        }
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

// Button permit to save a maze
void GameController::saveMazeToFile()
{
    QString filename = QFileDialog::getSaveFileName(nullptr, "Sauvegarder le labyrinthe", "", "Fichiers texte (*.txt)");
    if (filename.isEmpty()) return;

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& row : model->getGrid()) {
            for (int val : row) out << val;
            out << "\n";
        }
    }
}

// Button permit to load a maze file
void GameController::loadMazeFromFile()
{
    QString filename = QFileDialog::getOpenFileName(nullptr, "Charger un labyrinthe", "", "Fichiers texte (*.txt)");
    if (filename.isEmpty()) return;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::vector<std::vector<int>> newGrid;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            std::vector<int> row;
            for (QChar c : line) row.push_back(c.digitValue());
            newGrid.push_back(row);
        }
        reset();
        model->setGrid(newGrid);
        model->notifyObservers();
    }
}
// Button start the simulation
void GameController::startSimulation(){
    if(!model->hasWon())
        startGame();
}

// Button stop the simulation
void GameController::pauseSimulation(){ timer->stop(); }

// Button generate a new random Maze
void GameController::generateRandMaze(){
    reset();
    model->generateMaze(model->getRows(), model->getCol());
    model->notifyObservers();
}

// Button change robot position
void GameController::placeRobot(){
    reset();
    model->setRobotPosition(model->placeRobotRandomly());
    model->notifyObservers();
}

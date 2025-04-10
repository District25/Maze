#include "gamecontroller.h"

// Parameter constructor
GameController::GameController(Maze *maze, InputView *iv, OutputView *ov, Algorithm *algo, buttonView* bv)
{
    model = maze;
    inputView = iv;
    outputView = ov;
    algorithm = algo;
    btnView = bv;
    start_stop = false;
    timeOfAnimation = 0;

    connect(btnView, &buttonView::saveRequested, this, &GameController::saveMazeToFile);
    connect(btnView, &buttonView::loadRequested, this, &GameController::loadMazeFromFile);
    connect(btnView, &buttonView::randMazeRequested, this, &GameController::generateRandMaze);
    connect(btnView, &buttonView::randRobotPosRequested, this, &GameController::placeRobot);
    connect(btnView, &buttonView::start_stopSimulRequested, this, &GameController::start_stopSimulation);

    model->subscribe(ov);
    outputView->setAlgorithm(algorithm);
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameController::ComputeNextMove);
    connect(timer2, &QTimer::timeout, this, &GameController::handleAnimationTimer);
}

// Reset attributes and simulation
void GameController::reset()
{
    btnView->hideProcessingUI();
    timer->stop();
    timeOfAnimation = 0;
    indexAnim = 0;
    start_stop = false;
    model->setWin(false);
    algorithm->resetPaths();
    model->setRobotPosition(Coord(1, 1)); // safety
}
// Start the whole game
void GameController::startGame(){
    timer->start(1);
    timer2->start(1);
}

// The brain function that manage all the functions calls and conditions
void GameController::ComputeNextMove()
{
    checkVictory();
    // Still haven't found the exit
    if(!model->hasWon()){
        algorithm->leftWallFollower(model, model->getRobotPosition());
        btnView->showProcessingUI();
        //model->notifyObservers();
    }
    else // exit found by robot !
    {
        timer2->stop();
        timer->start(10); // Lower the speed to admire the animation
        btnView->winProcessingUI();
        if(indexAnim==0)
            algorithm->findOptimalPath();
        // Manage the animation to show optimal Path
        if(indexAnim < (algorithm->getOptimalPath().size())){
            model->moveRobot((algorithm->getOptimalPath())[indexAnim]);
            model->notifyObservers();
            indexAnim++;
        }
        else{
            timer->stop();
        }
    }
}

void GameController::handleAnimationTimer()
{
    timeOfAnimation++;
    btnView->setTimer(timeOfAnimation / 60000, (timeOfAnimation / 1000) % 60, timeOfAnimation % 1000);
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
        Coord foundExit(-1, -1);  // par défaut : pas trouvé

        int y = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            std::vector<int> row;

            for (int x = 0; x < line.length(); x++) {
                int val = line[x].digitValue();
                if (val == 2) {
                    foundExit = Coord(x, y);
                    val = 0; // remplace le 2 par 0 dans la grille
                }
                if (val != -1)
                    row.push_back(val);
            }

            if (!row.empty())
                newGrid.push_back(row);
            y++;
        }

        reset();
        model->setGrid(newGrid);
        model->placeExit(foundExit.x + 2, foundExit.y + 2); // définit la vraie sortie
        model->setRobotPosition(model->placeRobotRandomly());
        model->setGenerated(true);
        model->notifyObservers();
    }
}
// Button start the simulation
void GameController::start_stopSimulation(){
    start_stop=!start_stop;
    if(start_stop && model->getGenerated())
        startGame();
    else if(model->getGenerated()){
        timer2->stop();
        timer->stop();
        btnView->pauseProcessingUI();
    }
}

// Button generate a new random Maze
void GameController::generateRandMaze(){
    // Limite de taille minimale pour le Maze
    if(btnView->getRows() > 4 && btnView->getCols() > 4){
        reset();
        model->setGenerated(true);
        model->generateMaze(btnView->getRows(), btnView->getCols());
        model->setRobotPosition(model->placeRobotRandomly());
        model->notifyObservers();
    }
}

// Button change robot position
void GameController::placeRobot(){
    if(model->getGenerated()){
        reset();
        model->setRobotPosition(model->placeRobotRandomly());
        model->notifyObservers();
    }
}

#include "gamecontroller.h"

// Parameter constructor
GameController::GameController(Maze *maze, OutputView *ov, Algorithm *algo, buttonView* bv)
{
    // Initialize attributes
    model = maze;
    outputView = ov;
    algorithm = algo;
    btnView = bv;
    start_stop = false;
    timeOfAnimation = 0;

    // Connect button events to functions
    connect(btnView, &buttonView::saveRequested, this, &GameController::saveMazeToFile);
    connect(btnView, &buttonView::loadRequested, this, &GameController::loadMazeFromFile);
    connect(btnView, &buttonView::randMazeRequested, this, &GameController::generateRandMaze);
    connect(btnView, &buttonView::randRobotPosRequested, this, &GameController::placeRobot);
    connect(btnView, &buttonView::start_stopSimulRequested, this, &GameController::start_stopSimulation);
    connect(btnView, &buttonView::colorAnimationChanged, this, [=](QColor c){
        animationColor = c;
        model->notifyObservers();
    });
    connect(btnView, &buttonView::colorRobotChanged, this, [=](QColor c){
        robotColor = c;
        model->notifyObservers();
    });
    connect(btnView, &buttonView::colorWallChanged, this, [=](QColor c){
        wallColor = c;
        model->notifyObservers();
    });
    connect(btnView, &buttonView::colorExitChanged, this, [=](QColor c){
        exitColor = c;
        model->notifyObservers();
    });

    // Set the timers
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameController::ComputeNextMove);
    connect(timer2, &QTimer::timeout, this, &GameController::handleAnimationTimer);

    // Others
    model->subscribe(ov);
    outputView->setAlgorithm(algorithm);
}

// Reset attributes and simulation
void GameController::reset()
{
    btnView->hideProcessingUI(); // End UI graphic process
    // Stop the timers
    timer->stop();
    timer2->stop();
    timeOfAnimation = 0; // Reset the chronometer variable
    indexAnim = 0; // Reset the index for the animation when exit is found
    start_stop = false; // Not in start mode
    model->setWin(false); // Not in win mode
    algorithm->resetPaths(); // Clear the vector that contains the path and the optimal path
    model->setRobotPosition(Coord(1, 1)); // Place robot to initial position
}

// Start the whole game
void GameController::startGame(){
    // Configure the timers to 1ms and start them
    timer->start(1);
    timer2->start(1);
}

// The brain function that manage all the functions calls and conditions
void GameController::ComputeNextMove()
{
    checkVictory(); // Check if robot is on exit position
    // Still haven't found the exit
    if(!model->hasWon()){
        // Start the algorithm to search the exit and display the processing UI
        algorithm->leftWallFollower(model, model->getRobotPosition());
        btnView->showProcessingUI();
    }
    else // exit found by robot !
    {
        timer2->stop(); // Stop the timer that handle the chronometer
        timer->start(10); // Lower the speed to admire the animation
        btnView->winProcessingUI(); // Change the UI label
        // Used to call only once the algorithm to find the optimal path
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

// Handle the simulation chronometer
void GameController::handleAnimationTimer()
{
    timeOfAnimation++;
    btnView->setTimer(timeOfAnimation / 60000, (timeOfAnimation / 1000) % 60, timeOfAnimation % 1000);
}

// Check if robot has found the exit !
void GameController::checkVictory()
{
    // Collect the exit and the robot position
    Coord exitPos = model->getExitPosition();
    Coord robotPos = model->getRobotPosition();

    // Is robot on the exit position ?
    if(robotPos == exitPos){
        // Place robot at where he started to start the animation
        model->setRobotPosition(model->getInitRobotPosition());
        model->setWin(true); // We enter the "win" mode that will display the animation
    }
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

// Button "start/stop"
void GameController::start_stopSimulation(){
    start_stop=!start_stop; // Invert the variable when button is clicked
    // Variable is start, a maze has been generated and robot hasn't found the exit
    if(start_stop && model->getGenerated() && !(model->hasWon()))
        startGame();
    // Variable is stop, a maze has been generated and robot hasn't found the exit
    else if(model->getGenerated() && !(model->hasWon())){
        timer2->stop();
        timer->stop();
        btnView->pauseProcessingUI();
    }
}

// Button generate a new random Maze
void GameController::generateRandMaze(){
    // Minimum size for the maze generation
    if(btnView->getRows() > 4 && btnView->getCols() > 4){
        reset();
        model->setGenerated(true);
        model->generateMaze(btnView->getRows(), btnView->getCols());
        model->setRobotPosition(model->placeRobotRandomly());
        model->notifyObservers();
    }
}

// Button "change robot position"
void GameController::placeRobot(){
    if(model->getGenerated()){
        reset();
        model->setRobotPosition(model->placeRobotRandomly());
        model->notifyObservers();
    }
}

QColor GameController::getAnimationColor() const { return animationColor; }
QColor GameController::getRobotColor() const { return robotColor; }
QColor GameController::getWallColor() const { return wallColor; }
QColor GameController::getExitColor() const { return exitColor; }

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QTimer>
#include <QObject>
#include <QFileDialog>

#include "outputview.h"
#include "maze.h"
#include "inputview.h"
#include "algorithm.h"
#include "buttonview.h"

class GameController : public QObject{
    Q_OBJECT
private:
    QTimer* timer;
    Maze* model;
    InputView* inputView;
    OutputView* outputView;
    Algorithm* algorithm;
    buttonView* btnView;
    size_t indexAnim;

public:
    GameController(Maze* maze, InputView* iv, OutputView* ov, Algorithm* algo, buttonView* bv);
    void reset();
    void startGame();
    bool checkVictory();
    size_t getIndexAnim() const;
    Maze* getMaze();
public slots:
    void ComputeNextMove();
    void saveMazeToFile();
    void loadMazeFromFile();
    void pauseSimulation();
    void generateRandMaze();
    void placeRobot();
    void startSimulation();
};

#endif

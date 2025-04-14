#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QTimer>
#include <QObject>
#include <QFileDialog>

#include "outputview.h"
#include "maze.h"
#include "algorithm.h"
#include "buttonview.h"

class GameController : public QObject{
    Q_OBJECT
private:
    QTimer* timer;
    QTimer* timer2;
    Maze* model;
    OutputView* outputView;
    Algorithm* algorithm;
    buttonView* btnView;
    size_t indexAnim;
    bool start_stop; // true = start, false = stop
    int timeOfAnimation;
    QColor animationColor = Qt::cyan;
    QColor robotColor = Qt::red;
    QColor wallColor = Qt::black;
    QColor exitColor = Qt::green;
public:
    GameController(Maze* maze, OutputView* ov, Algorithm* algo, buttonView* bv);
    void reset();
    void startGame();
    void checkVictory();
    size_t getIndexAnim() const;
    Maze* getMaze();
    QColor getAnimationColor() const;
    QColor getRobotColor() const;
    QColor getWallColor() const;
    QColor getExitColor() const;
public slots:
    void ComputeNextMove();
    void handleAnimationTimer();
    void saveMazeToFile();
    void loadMazeFromFile();
    void generateRandMaze();
    void placeRobot();
    void start_stopSimulation();
};

#endif

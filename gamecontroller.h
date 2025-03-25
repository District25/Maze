#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QTimer>
#include <QObject>

#include "outputview.h"
#include "maze.h"
#include "inputview.h"
#include "algorithm.h"

class GameController : public QObject{
    Q_OBJECT
private:
    QTimer* timer;
    Maze* model;
    InputView* inputView;
    OutputView* outputView;
    Algorithm* algorithm;
    std::vector<Coord> visited;

public:
    GameController(Maze* maze, InputView* iv, OutputView* ov, Algorithm* algo);
    void startGame();
    bool isMoveValid();
    bool checkVictory();
    Maze* getMaze();
public slots:
    void ComputeNextMove();
};

#endif

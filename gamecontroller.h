#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Maze.h"
#include "InputView.h"
#include "OutputView.h"
#include "Algorithm.h"

class GameController {
private:
    Maze* model;
    InputView* inputView;
    OutputView* outputView;
    Algorithm* algorithm;

public:
    GameController(Maze* maze, InputView* iv, OutputView* ov, Algorithm* algo);
    void startGame();
    void ComputeNextMove();
    bool isMoveValid();
    bool checkVictory();
};

#endif

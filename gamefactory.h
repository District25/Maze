#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "inputview.h"
#include "outputview.h"
#include "algorithm.h"
#include "gamecontroller.h"
#include "Coord.h"
#include "maze.h"

#include <QWidget>

class GameFactory
{
public:
    static Maze* createMaze();
    static InputView* createInputView();
    static OutputView* createOutputView(Maze* maze, QWidget* parent);
    static Algorithm* createAlgorithm();
    static GameController* createGameController();
};

#endif // GAMEFACTORY_H

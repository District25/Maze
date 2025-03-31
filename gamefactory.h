#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "inputview.h"
#include "outputview.h"
#include "algorithm.h"
#include "gamecontroller.h"
#include "maze.h"
#include "buttonview.h"

#include <QWidget>
#include <QHBoxLayout>

class GameFactory
{
public:
    static Maze* createMaze();
    static InputView* createInputView();
    static OutputView* createOutputView(Maze* maze, QWidget* parent);
    static Algorithm* createAlgorithm();
    static GameController* createGameController();
    static buttonView* createButtonView(QWidget* parent);
};

#endif // GAMEFACTORY_H

#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "inputview.h"
#include "outputview.h"
#include "algorithm"
#include "gamecontroller.h"
#include "Coord.h"
#include "maze.h"

class GameFactory
{
public:
    static Maze* createMaze();
    static InputView* createInputView();
    static OutputView* createOutputView(Maze* maze);
    static Algorithm* createAlgorithm();
    static Coord* createCoord();
    static GameController* createGameController(Maze* maze, InputView* iv, OutputView* ov, Algorithm* algo);
};

#endif // GAMEFACTORY_H

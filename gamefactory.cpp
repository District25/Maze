#include "gamefactory.h"


Maze *GameFactory::createMaze()
{
    return new Maze();
}

InputView *GameFactory::createInputView()
{
    return new InputView();
}

OutputView *GameFactory::createOutputView(Maze *maze)
{
    return new OutputView(maze);
}

Algorithm *GameFactory::createAlgorithm()
{
    return new Algorithm();
}

Coord *GameFactory::createCoord()
{
    return new Coord();
}

GameController *GameFactory::createGameController(Maze *maze, InputView *iv, OutputView *ov, Algorithm *algo)
{
    return new GameController(maze, iv, ov, algo);
}

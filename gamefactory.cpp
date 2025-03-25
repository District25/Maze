#include "gamefactory.h"

GameController *GameFactory::createGameController()
{
    Maze* maze = createMaze();
    InputView* iv = createInputView();
    OutputView* ov = createOutputView(maze, nullptr);
    Algorithm* algo = createAlgorithm();
    return new GameController(maze, iv, ov, algo);
}
Maze *GameFactory::createMaze()
{
    return new Maze();
}

InputView *GameFactory::createInputView()
{
    return new InputView();
}

OutputView *GameFactory::createOutputView(Maze* maze, QWidget* parent)
{
    return new OutputView(maze, parent);
}

Algorithm *GameFactory::createAlgorithm()
{
    return new Algorithm();
}

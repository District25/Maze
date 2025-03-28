#include "gamefactory.h"

// Create the game controller
GameController *GameFactory::createGameController()
{
    Maze* maze = createMaze();
    InputView* iv = createInputView();
    OutputView* ov = createOutputView(maze, nullptr);
    Algorithm* algo = createAlgorithm();
    GameController* gc = new GameController(maze, iv, ov, algo);
    ov->setController(gc);
    return gc;
}

// Create the maze
Maze *GameFactory::createMaze()
{
    return new Maze(50, 50);
}


// Create the inputView
InputView *GameFactory::createInputView()
{
    return new InputView();
}

// Create the outputView
OutputView *GameFactory::createOutputView(Maze* maze, QWidget* parent)
{
    return new OutputView(maze, parent);
}

// Create the algorithm
Algorithm *GameFactory::createAlgorithm()
{
    return new Algorithm();
}

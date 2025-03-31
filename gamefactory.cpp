#include "gamefactory.h"

// Create the game controller
GameController *GameFactory::createGameController()
{
    Maze* maze = createMaze();
    InputView* iv = createInputView();
    OutputView* ov = createOutputView(maze, nullptr);
    Algorithm* algo = createAlgorithm();
    buttonView* bv = createButtonView(nullptr);

    GameController* gc = new GameController(maze, iv, ov, algo, bv);
    ov->setController(gc);

    QWidget* mainWidget = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(ov);
    layout->addWidget(bv);

    mainWidget->setLayout(layout);
    mainWidget->setWindowTitle("Maze Game");

    mainWidget->show();
    return gc;
}

buttonView *GameFactory::createButtonView(QWidget* parent)
{
    return new buttonView(parent);
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
